#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

	int fd;
	char *myfifo = "/tmp/myfifo";
	
	//create the FIFO (namerd pipe)
	mkfifo(myfifo, 0666);
	
	//write "Hi" to the FIFO
	for(int i = 0; i < 7; i++) {	
		fd = open(myfifo, O_WRONLY);
		write(fd, "So tired", sizeof("So tired"));
		close(fd);

	unlink(myfifo);
	}

	return 0; 
}

