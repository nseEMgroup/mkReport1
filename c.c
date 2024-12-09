#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){
    FILE *rfp; 
    FILE *wfp;
    char *ptr;
    float cpuhz;
    int processor = 0, core_num = 0, coreid = 0, i, is;
    int core_id[BUFSIZ];
    char a[BUFSIZ], b[BUFSIZ], mn[BUFSIZ];
    struct tm *tm;
	time_t t;
	char *output = "%G년 %m월 %d일 %H:%M";
	char buf[BUFSIZ];
	time(&t);
	tm = localtime(&t);
	strftime(buf, BUFSIZ, output, tm);
    if((rfp = fopen("/proc/cpuinfo","r"))==NULL){
        perror("fopen");
        exit(1);
    }
    if((wfp = fopen("cpureport.txt","w"))==NULL){
        perror("fopen");
        exit(1);
    }
    while(fgets(a, BUFSIZ, rfp) != NULL){
        if (strlen(a) == 1 && a[0] == '\n') { //chatgpt 사용
            continue;
        }
        if(strncmp(a, "processor", 9)==0){ //https://blockdmask.tistory.com/391 완
            processor++;
        }
        if(strncmp(a, "model name", 10)==0){  //완
            ptr = strchr(a,':'); //https://www.ibm.com/docs/ko/i/7.3?topic=functions-strchr-search-character
            ptr += 2;
            strcpy(mn,ptr);//KERNIGHAN의 C언어 프로그래밍 p.149
        }
        if(strncmp(a, "cpu MHz", 7)==0){  //완
            ptr = strchr(a,':');
            ptr += 2;
            cpuhz = atof(ptr); //chatgpt 사용
            cpuhz = cpuhz / 1000;
        }
        if(strncmp(a, "core id", 7)==0){ 
            ptr = strchr(a,':');
            ptr += 2;
            coreid = atoi(ptr);
            is=0;
            for(i=0;i<core_num;i++){
                if(core_id[i]==coreid){
                    is=1;
                    break;
                }
            }
            if(is == 0){
                core_num++;
                core_id[core_num-1] = coreid;
            }
        }
    }
    fprintf(wfp, "--- CPU 보고서 ---\n");
    fprintf(wfp, "코어 갯수: %d, 스레드 갯수: %d\n", core_num, processor);
    fprintf(wfp, "모델 이름: %s",mn);
    fprintf(wfp, "CPU 클럭: %.2fGHz\n", cpuhz);
    fprintf(wfp, "%s\n", buf);
    fclose(rfp);
    fclose(wfp);
    printf("cpu 보고서 작성 완료\n");
	exit(0);
}