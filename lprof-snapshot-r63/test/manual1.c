#include "common.h"
#include <stdio.h>
#include <lprof.h>
#include <math.h>

long double d = 9;
void burn(size_t l) {
    size_t i;
    for (i=0; i<l; i++) {
	//Let's see how this affects the branch predictor
	if (d > 10000)
	    d = 7*sqrt(d/7) + 81;
	else
	    d += 5000;
    }
}

int main(void) {
    size_t i;
    uint64_t br_last=0, brm_last=0;

    //setcore(3);  //Optional: select the core to run on
    
    // Counter 1: Core Clock Cycles
    // Counter 2: Branches
    // Counter 3: Branch Misprediction
    lprof_init(3, EV_CYCLES, EV_BRANCH, EV_BRANCH_MISS);

    printf("  %16s,   %16s,   %16s, %4s(%%), %5s, %5s\n",
	   "Cum. Cycles", "Branches",
	   "Branch Misses", "MR", "Ints", "CSs");
    for (i=0; i<30; i++) {
	uint64_t cycles, br, brm;

	//Optional: sample just before call
	lprof(2, br_last);
	lprof(3, brm_last);

	//Optional: reset kernel stat counters
	__lp_stats.timer_interrupts = 0;
	__lp_stats.context_switches = 0;


	//Burn for some number of cycles proportional to 2^i
	burn(pow(2, 3*(int)(i/3)));


	//Get total number of cycles since init
	lprof(1, cycles);

	//Get number of branches since last loop
	lprofd(2, br,  br_last);

        //Get number of branch mispreds since last loop
	lprofd(3, brm, brm_last);

	printf("0x%016lx, 0x%016lx, 0x%016lx, %0.4lf%%, %5lu, %5lu\n",
	       cycles, br, brm, 100*((double)brm/(double)br),
	       __lp_stats.timer_interrupts,
	       __lp_stats.context_switches);
	if (i%3 == 2)
	    printf("\n");
    }
    
    //Close all counters
    lprof_close();
    return 0;
}
