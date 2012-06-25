#include <stdio.h>
#include <stdint.h>
#include <linux/lprof.h>

extern void test1(void);

static int j = -3;
void test2(void) {
    if (j < 0) {
	j *= -1;
	return;
    }

    j = 0;
    return;
}

int main(void) {
    int i;
    printf("starting test1\n");
    for (i=0; i<25; i++) {
	test1();
	j = i * 4;
    }
    printf("test1 complete\n");

    return 1;
}


uint64_t gpcount = 0;
uint64_t pcount = 1;

uint32_t rdpmc1 = 1;
uint32_t rdpmc2 = 1;
void bar(void) {
    uint64_t rdpmc = ((uint64_t)rdpmc2 << 32) | rdpmc1;
    pcount += rdpmc;
}
