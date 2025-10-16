#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define IOCTL_MAGIC 'k'
#define IOCTL_CMD_GET _IOR(IOCTL_MAGIC,1,int)
#define IOCTL_CMD_SET _IOW(IOCTL_MAGIC,2,int)
#define IOCTL_CMD_MEMSET_NEGATIVE_ONE _IO(IOCTL_MAGIC,3)
#define IOCTL_SEND_SIGNAL _IOW(IOCTL_MAGIC, 4, int)


void sig_handler(int signum){
	
	if(signum==SIGUSR1){
		printf("signal has been received: SIGUSR1, terminating\n");
		exit(1);
	}

}


int main(){

	signal(SIGUSR1, sig_handler);

	int fd = open("/dev/my_device", O_RDWR);
	printf("fd=%d, errno=%d\n", fd, errno);
	if(fd<0){
		printf("error opening device: errno=%d\n", errno);
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
	
	
	ret = ioctl(fd, IOCTL_CMD_MEMSET_NEGATIVE_ONE,0);
	if(ret!=0){
		printf("some kind of error in CMD_MEMSET_NEGATIVE_ONE\n");
		return 4;
	}
	
	int pid=(int)getpid();
	ret = ioctl(fd, IOCTL_SEND_SIGNAL, &pid);
	
	
	printf("sleeping\n");
	sleep(10);
	printf("sleep has ended\n");
	
	
	
	
	close(fd);
	
	return 0;
}
