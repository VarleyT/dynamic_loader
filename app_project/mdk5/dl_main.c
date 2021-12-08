#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DL_EXPORT		__attribute__((visibility("default")))
#define DL_HIDDEN		__attribute__((visibility("hidden")))

__attribute__((aligned(1024))) int test_array[5000];

void Malloc_test(void){
	static const uint32_t m_size=1024*1024;
	void* ptr;
	printf("malloc test:try malloc %d byte.\r\n",m_size);
	ptr=malloc(m_size);
	if(ptr==NULL)
		printf("malloc fail.\r\n");
	else
		printf("malloc success.\r\n");
	printf("free memory.\r\n");
	free(ptr);
	printf("time:%d\r\n",time(NULL));
	printf("clock:%d\r\n",clock());
}


DL_EXPORT int test_func(int a){
	Malloc_test();
	memset(test_array,5,sizeof(test_array));
	return 5*a;
}

DL_EXPORT void test_cnt(int run_times,bool istart){
	static size_t start,total_run;
	if(istart){
		start=clock();
		total_run=run_times;
	}
	for(size_t i=0;i<100000;i++){
		__asm("nop");
	}
	if(run_times==0){
		printf("运行次数：%d\r\n",total_run);
		printf("动态加载函数运行时间：%d\r\n",clock()-start);
	}
	else
		test_cnt(run_times-1,false);
}

int dl_main(int argc, char *argv[]){
	printf("main test:hello world!\r\n");
	printf("command:\r\n");
	for(size_t i=0;i<argc;i++){
		printf("%s\r\n",argv[i]);
	}
	return 0;
}




