/* File: main.c
 * ------------
 * 校园网802.1X客户端命令行
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
/* 子函数声明 */
int Authentication(const char *UserName, const char *Password, const char *DeviceName);


/**
 * 函数：main()
 *
 * 检查程序的执行权限，检查命令行参数格式。
 * 允许的调用格式包括：
 * 若没有从命令行指定网卡，则默认将使用en0
 */
extern void MD5Calc(unsigned char *data, unsigned int len, unsigned char *output);

/* 检测程序是否已经运行  */
int checkProcessname(int pid){
    FILE *fp;
    char pname[100];
    char kpid[100];
    sprintf(kpid, "%d",pid);
    char query[200];
    
    strcat(query, "ps -p ");
    strcat(query, kpid);
    strcat(query," -o comm=");
    fp = popen(query, "r");
    if (fp == NULL) {
        printf("Failed to get PID\n" );
        exit(1);
    }
    if (fgets(pname, sizeof(pname)-1, fp) != NULL) {
        pclose(fp);
    }
    
    if (strstr(pname, "RealNode")) {
        fclose(fp);
        return 0;
    }
    fclose(fp);
    return -1;
}

int main(int argc, char *argv[])
{
	char *UserName;
	char *Password;
	char *DeviceName;
    
    FILE *fp;
    int lpid;
    char cpid[255];

	/* 检查当前是否具有root权限 */
	if (getuid() != 0) {
		fprintf(stderr, "抱歉，运行本客户端程序需要root权限\n");
		fprintf(stderr, "在命令前添加sudo\n");
		exit(-1);
	}

	/* 检查命令行参数格式 */
	if (argc<3 || argc>4) {
		fprintf(stderr, "命令行参数错误！\n");
		fprintf(stderr,	"正确的调用格式例子如下：\n");
		fprintf(stderr,	"    %s username password\n", argv[0]);
		fprintf(stderr,	"    %s username password en0\n", argv[0]);
		fprintf(stderr,	"    %s username password en1\n", argv[0]);
		fprintf(stderr, "(注：若不指明网卡，默认情况下将使用en0)\n");
		exit(-1);
	} else if (argc == 4) {
		DeviceName = argv[3]; // 允许从命令行指定设备名
	} else {
		DeviceName = "en0"; // 缺省情况下使用的设备
	}
	UserName = argv[1];
	Password = argv[2];

  
    sprintf(cpid, "%d",getpid());
    if((fp=fopen("/tmp/RealNode.pid", "r"))!=NULL)
    {
        fscanf(fp, "%d", &lpid);
        if(checkProcessname(lpid)==0){
            printf("RealNode is already running,Now I gotta kill him!");
            kill(lpid, SIGTERM);
        }
        
    }
    fclose(fp);
    
    fp = fopen("/tmp/RealNode.pid", "w+");
    fputs(cpid, fp);
    fclose(fp);
	/* 调用子函数完成802.1X认证 */
	Authentication(UserName, Password, DeviceName);

	return (0);
}
