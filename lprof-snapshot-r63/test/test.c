#include <lprof.h>
#include <linux/lprof.h>

#include <stdio.h>

double d = 9.0;
void foo(void) {
    size_t i;
    for (i=0; i<10000000; i++) {
	d *= d + 8;
	if (i % 1000000 == 0) {
	    printf("%llu\n", lprofd());
	    sys_lprof_config(LPROF_DBG, 0, 0, 0);
	}
    }
}

int main(void) {
    int ctr = lprof_config(EV_CYCLES);
    foo();
    lprof_close(ctr);
    return 0;
}
