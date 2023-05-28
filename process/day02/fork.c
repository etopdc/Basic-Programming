#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// 子进程会将父进程的地址空间（包括缓冲区）一起拷贝
int main(void)
{
	pid_t cpid;
	// 文件io不带缓冲区
	write(STDOUT_FILENO,"Hello",6);  // 只有父进程打印
	// 标准io自带缓冲区，stdout行缓存，不带\n，存进缓冲区
	fputs("Hello",stdout); // 此处父子进程都会打印

	cpid = fork();

	if (cpid == -1){
		perror("fork(): ");
		return -1;
	}

	return 0;
}