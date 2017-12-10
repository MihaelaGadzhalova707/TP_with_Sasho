#ifndef _DUMB_SHM_STRUCT
#define _DUMB_SHM_STRUCT
#include <stdint.h>

struct chunk_t {
	volatile int array[4096];
};

struct buff_t {
	volatile uint64_t pos;
	volatile struct chunk_t buff[1000];
};
#endif
