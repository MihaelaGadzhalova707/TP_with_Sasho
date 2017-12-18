#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>
#include "buffer.h"
#include "gen.h"

int main() {

	int fd = shm_open("shared", O_CREAT | O_RDWR, S_IRWXU);

	if(fd == -1) {
		perror("Can't open the file");
		return 1;
	}

	int res = ftruncate(fd, sizeof(struct buff_t));

	if(res == -1) {
		perror("Can't truncate file");
		return res;
	}

	struct buff_t *bufferr = mmap(NULL, sizeof(struct buff_t),PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0 );

	if(bufferr == NULL) {
		perror("Can't mmap");
		return -1;
	}

	bufferr -> pos = 0;
	uint32_t seed = 0;
	while(true) {
		generate((void*)bufferr->buff[bufferr->pos %= _COUNT], seed);
		printf("Generating array[%d] - seed: %d\n", bufferr -> pos %= _COUNT,seed);
		seed++;
		bufferr->pos++;
		//bufferr->pos = bufferr->pos % 1000;
	}
	return 0;

}

