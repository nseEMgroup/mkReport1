#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv){
	pid_t pidc, pidm;
	int n, statusc, statusm;
	int remain = 0;
	while((n=getopt(argc,argv,"cmh"))!=-1){
		switch(n){
			case 'c':
				switch(pidc = fork()){
					case -1:
						perror("fork");
						exit(1);
						break;
					case 0:
						if(execl("./c.out","c.out",(char *) NULL) ==-1){
							perror("execl");
							exit(1);
						}
						exit(0);
						break;
					default:
						printf("cpu 보고서 작성 시작\n");
						remain++;
						break;
				}
				break;
			case 'm':
				switch(pidm = fork()){
					case -1:
						perror("fork");
						exit(1);
						break;
					case 0:
						if(execl("./m.out","m.out",(char *) NULL) ==-1){
							perror("execl");
							exit(1);
						}
						exit(0);
						break;
					default:
						printf("메모리 보고서 작성 시작\n");
						remain++;
						break;
				}
				break;
			case 'h':
				printf("도움말\n");
				break;
			default:
				printf("잘못된 옵션을 선택하셨습니다. 'h' 옵션을 사용해 도움말을 확인하세요\n");
				break;
		}
	}
	while (remain > 0) {
        int status;
        pid_t pid = waitpid(-1, &status, 0);  // 종료된 자식 중 하나 기다림
        if (pid > 0) {
            remain--;
        }
    }
	printf("실행 완료\n");
}
