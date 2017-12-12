#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include "buffer.h"
#include "gen.h"

int main() {

	int fd = shm_open("shared", O_RDONLY, 0);

	if(fd == -1) {
		perror("Can't open the file");
		return 1;
	}

	struct buff_t *bufferr = mmap(NULL, sizeof(struct buff_t), PROT_READ, MAP_SHARED, fd, 0);

	if(bufferr == NULL) {
		perror("Can't mmap");
		return -1;
	}

	uint64_t this_pos = 0;
	printf("starting at %ld\n", this_pos);
	uint64_t old_seed = -1;
	while(1) {
		if(bufferr -> pos == this_pos) {
			sleep(1);
			continue;
		}
		if(bufferr -> pos >= this_pos + 1000) {
			break;
		}

		uint32_t this_seed = verify((void*)bufferr -> buff[this_pos].array);
		//
		if(this_seed == -1) {
			break;
		}

		if(old_seed + 1 != this_seed) {
			break;
		}
		old_seed = this_seed;
		printf("Verified at %d with seed %d\n",this_pos, this_seed);
		this_pos++;	
	}	
	
	return 0;
}
