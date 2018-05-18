#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <sys/ioctl.h> 
#include <time.h> 
#include <fcntl.h> 
#include <linux/input.h>
int main(int argc, char **argv) 
{
	int key_state; 
	int fd;
	int ret;
	int code; 
    int type;
	struct input_event buf;
	/*打开按键设备节点*/
	fd = open("/dev/input/event0", O_RDONLY);
	if (fd < 0) 
	{
		printf("Open Gpio_Keys failed!\n"); 
		return -1; 
	}
	/*打印成功打开按键设备节点提示信息*/ 
	printf("Open Gpio_Keys successed!\n");
	while(1) { 
		/*监听按键状态*/ 
		ret = read(fd, &buf, sizeof(struct input_event)); 
		if (ret <= 0)
		{
			 printf("read failed!\n");
			 return -1; 
		}
		code = buf.code;
        type = buf.type;
		key_state = buf.value;
		switch(code) 
		{
		 	case KEY_PROG1: 
			        code = '1';
			         break;
			case KEY_PROG2:
			         code = '2';
			         break; 
		}
		if(code != 0) 
			/*打印按键状态信息*/ 
			printf("KEY_PROG_%d type= %d state= %d.\n", code, type, key_state);
	}
		printf("Key test finished.\n"); 
		close(fd);
		return 0;
} 
