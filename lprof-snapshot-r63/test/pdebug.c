#include <linux/lprof.h>

int main(void) {
    return sys_lprof_config(LPROF_DBG, 0, 0, 0);
}
