#include <stdio.h>
#include <sys/sysinfo.h>
#include <stdlib.h>

int main(){
	FILE *fp;
	struct sysinfo meminfo;
	fp = fopen("memoryreport.txt", "w");
	sysinfo(&meminfo);
	fprintf(fp, "총 메모리 용량: %.3fGB\n", (float)meminfo.totalram/(1024*1024*1024));
	fprintf(fp, "사용자 사용 가능 메모리 용량: %.3fGB\n", (float)meminfo.totalhigh/(1024*1024*1024));
	fprintf(fp, "총 스왑 메모리 용량: %.3fGB\n", (float)meminfo.totalswap/(1024*1024*1024));
	fclose(fp);
	printf("메모리 보고서 작성 완료\n");
	exit(0);
}
