#ifndef _DUMB_SHM_STRUCT
#define _DUMB_SHM_STRUCT

#define _SIZE 4096
#define _COUNT 8192

#include <stdint.h>



struct buff_t {
	volatile uint64_t pos;
	volatile buff[_COUNT][_SIZE];
};
#endif
