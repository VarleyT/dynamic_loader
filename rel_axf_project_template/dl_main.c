#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//armlink 完整命令行
//--base_platform --entry=dl_main --export_dynamic  --no_comment_section --no_debug 
#define DL_EXPORT		__attribute__((visibility("default")))
#define DL_HIDDEN		__attribute__((visibility("hidden")))

DL_EXPORT int export_func(void){
	return printf("export func test\r\n");
}


int dl_main(int argc, char *argv[]){
	printf("main test:hello world!\r\n");
	printf("command:\r\n");
	for(size_t i=0;i<argc;i++){
		printf("%s\r\n",argv[i]);
	}
	return 5;
}

