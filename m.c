#include <stdio.h>
#include <sys/sysinfo.h>
#include <stdlib.h>
#include <time.h>

int main(){
	FILE *fp;
	struct sysinfo meminfo;
	struct tm *tm;
	time_t t;
	char *output = "%G년 %m월 %d일 %H:%M";
	char buf[BUFSIZ];
	time(&t);
	tm = localtime(&t);
	strftime(buf, BUFSIZ, output, tm);
	if((fp = fopen("memoryreport.txt", "w"))==NULL){
		perror("fopen");
		exit(1);
	}
	sysinfo(&meminfo);
	fprintf(fp, "--- 메모리 현황 ---\n");
	fprintf(fp, "총 메모리 용량: %.3fGB\n", (float)meminfo.totalram/(1024*1024*1024));
	//fprintf(fp, "사용자 사용 가능 메모리 용량: %.3fGB\n", (float)meminfo.totalhigh/(1024*1024*1024));
	fprintf(fp, "총 스왑 메모리 용량: %.3fGB\n", (float)meminfo.totalswap/(1024*1024*1024));
	fprintf(fp, "%s\n", buf);
	fclose(fp);
	printf("메모리 보고서 작성 완료\n");
	exit(0);
}
