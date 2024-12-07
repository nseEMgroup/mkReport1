#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int wrongOption(){
	printf("잘못된 옵션을 선택하셨습니다. 'h' 옵션을 사용해 도움말을 확인하세요\n");
	exit(1);
	return 0;
}
int help(){
	printf("--- 도움말 ---\n");
	printf("이 프로그램은 CPU와 메모리에 대한 각종 지표를 출력하는 프로그램입니다.\n");
	printf("사용법: 1.out [OPTIONS]\n");
	printf("- 옵션 -\n");
	printf("-c\n");
	printf("	CPU에 대한 각종 지표를 출력합니다.\n");
	printf("	출력 지표: CPU 이름, 코어 수, 스레드 수, CPU 클럭\n");
	printf("-m\n");
	printf("	메모리에 대한 각종 지표를 출력합니다.\n");
	printf("	출력 지표: 메모리 용량, 스왑 메모리 용량\n");
	printf("-h\n");
	printf("	여러분들이 지금 보고 계신 이 도움말을 출력합니다.\n");
	return 0;
}

int main(int argc, char **argv){
	pid_t pidc, pidm;
	int n, status;
	int remain = 0;
	if(argc != 2){
		wrongOption();
	}
	while((n=getopt(argc,argv,"cmh"))!=-1){
		switch(n){
			case 'c':
				switch(pidc = fork()){
					case -1:
						perror("fork");
						exit(1);
						break;
					case 0:
						if(execl("./c.out","c.out", (char *) NULL) ==-1){
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
				while (remain > 0) { //chatgpt 사용
        			pid_t pid = waitpid(-1, &status, 0);  // 종료된 자식 중 하나 기다림
     		    	if (pid > 0) {
     					remain--;
       				}
    			}
				help();
				break;
			default:
				wrongOption();
				break;
		}
	}
	while (remain > 0) { //chatgpt 사용
        pid_t pid = waitpid(-1, &status, 0);  // 종료된 자식 중 하나 기다림
        if (pid > 0) {
            remain--;
        }
    }
	printf("실행 완료\n");
	return 0;
}
