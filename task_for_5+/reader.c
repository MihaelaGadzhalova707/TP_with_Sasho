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

	uint64_t this_pos = bufferr -> pos;
	printf("starting at %ld\n", this_pos);
	uint64_t this_seed;
	uint64_t other_seed;
	int count = 0;
	while(1) {
	
		while(bufferr -> pos != this_pos) {

			this_seed = verify((void*)bufferr -> buff[this_pos %= _COUNT]);
			
			if(bufferr -> pos >= this_pos + _COUNT) {
				return 3;;
			}

			if(this_seed < 0) {
				printf("error");
			}

			if(count == 0) {
				other_seed = this_seed;
				count = 1;
			} else if(other_seed + 1 != this_seed) {
				return 4;
			}else {
				other_seed++;
			}	
		}
		//old_seed = this_seed;
		printf("Verified at %d with seed %d\n",this_pos %= _COUNT, this_seed);
		this_pos++;
	}	
	
	return 0;
}
