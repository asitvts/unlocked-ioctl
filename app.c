#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define IOCTL_MAGIC 'k'
#define IOCTL_CMD_GET _IOR(IOCTL_MAGIC,1,int)
#define IOCTL_CMD_SET _IOW(IOCTL_MAGIC,2,int)


int main(){

	int fd = open("/dev/my_device", O_RDWR);
	if(fd<0){
		printf("error opening device\n");
		return 1;
	}	
	
	int val = 1234;
	int ret=ioctl(fd, IOCTL_CMD_SET, &val);
	if(ret!=0){
		printf("some kind of error in CMD_SET\n");
		return 2;
	}
	
	printf("1234 set\n");
	
	int ret_val;
	ret=ioctl(fd, IOCTL_CMD_GET, &ret_val);
	if(ret!=0){
		printf("some kind of error in CMD_SET\n");
		return 3;
	}
	
	printf("received : %d\n", ret_val);
	
	close(fd);
	
	return 0;
}
