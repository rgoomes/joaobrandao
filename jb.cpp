#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#define D 127

typedef uint8_t Number;

Number seq[D+1], sol[D+1], *beg = seq, *end, *bound_end, ones[D+1], *one_beg = ones;
int n, best = 0, best_end;
long int paths;

int ubound[D+1], bests[D+1] = {
	 1,  2,  2,  3,  4,  4,  4,  4,  5,  5,
	 6,  6,  7,  8,  8,  8,  8,  8,  8,  9,
	 9,  9,  9, 10, 10, 11, 11, 11, 11, 12,
	12, 13, 13, 13, 13, 14, 14, 14, 14, 15,
	16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
	17, 17, 17, 18, 18, 18, 18, 19, 19, 19,
	19, 19, 20, 20, 20, 20, 20, 20, 20, 20,
	21, 21, 21, 22, 22, 22, 22, 22, 22, 22,
	22, 23, 23, 24, 24, 24, 24, 24, 24, 24,
	24, 25, 25, 25, 26, 26, 26, 26, 26, 27,
	27, 27, 27, 28, 28, 28, 28, 28, 28, 28,
	29, 29, 29, 30, 30, 30,
	/*     FROM HERE BESTS NOT KNOWN     */
							 0,  0,  0,	 0,
	 0,  0,  0,  0,  0,  0,  0,  0
};

inline int distance(Number *cur, Number *cur_beg){ return cur - cur_beg; }
inline void set_bit(Number *cur){ *cur = 1; }
inline void clr_bit(Number *cur){ *cur = 0; }

void bin_solution(Number *first, Number *last){
	for(Number *it = first; it-first != (n-1); ++it)
		printf("%d ", *it); printf("\n");
}

void int_solution(Number *first, Number *last){
	for(Number *it = first; it-first != (n-1); ++it)
		if(*it) printf("%d ", int(it-first)+1); printf("\n");
}

inline bool fast_isvalid(Number *end, Number *it){
	int cmp = distance(end, beg), max_ind = cmp / 2;
	while(it-- != one_beg && *it >= max_ind)
		if(seq[*it*2 - cmp + 1])
			return false;

	return true;
}

void store_solution(Number *it, int nlen){
	paths++;

	if(nlen > 30)
		int_solution(beg, it);
	if(nlen > best){
		best = nlen;
		best_end = distance(it, beg);
		std::copy(beg, it, sol);
	}
}

inline bool bound1(Number *it, int nlen){
	return (bound_end - it) / 2 + 1 + nlen <= best;
}

inline bool bound2(Number *it, int nlen){
	int best_sequence = ubound[bound_end - it];
	return best_sequence && (best_sequence + nlen <= best);
}

inline void dfs(Number *it, Number *ot, int depth){
	if(it > end)
		return;
	if(depth <= 0)
		return;

	int dit = distance(it, beg);
	int don = distance(ot, one_beg);

	if(dit && seq[dit-1]){
		if(fast_isvalid(it, ot-1))
			store_solution(it, don);
		else
			return;
	}

	if(bound1(it, don))
		return;
	if(bound2(it, don))
		return;

	*ot = dit;

	set_bit(it);
	dfs(it+1, ot+1, depth-1);

	clr_bit(it);
	dfs(it+1, ot, depth-1);
}

void idd(int depth){
	depth = std::min(depth, D);

	for(int d = 1; d < depth; d++){
		paths = 0;
		bound_end = beg + d+1;
		dfs(beg, one_beg, d+1);

		ubound[d-1] = best;
		printf("depth %d - best so far %d - valid paths tested %ld\n", d, best, paths);
	}

	std::cout << std::endl;
	int_solution(sol, sol+best_end);
	bin_solution(sol, sol+best_end);
	std::cout << std::endl;
}

int main(int argc, char **argv){
	if(argc < 2)
		return 0;

	n = atoi(*++argv) + 1;
	end = seq+n;

	idd(n);
	return 0;
}
