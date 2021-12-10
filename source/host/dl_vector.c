/*
*   @File name: dl_vector.c
*   @Author: wzh
*   @Version: 1.0
*   @Date: 2021-12-3
*   @Description: 用于创建主程序与子程序可以共同访问的一块内存，主要用于存储主程序一些函数的函数地址
*                 使得子程序可以调用主程序的函数
*/
#include "dl_lib.h"
#include "../common/dl_extern_lib.h"
#include "../common/dl_stdio_lib.h"
#include "../common/dl_stdlib_lib.h"
#include "../common/dl_time_lib.h"
#include <time.h>

#define STDIO_DECLARE(func,index)	[index+DL_STDIO_LIB_BASE]=(void*)func,

#define STDLIB_DECLARE(func,index)	[index+DL_STDLIB_LIB_BASE]=(void*)func,
	
#define TIME_LIB_DECLARE(func,index) [index+DL_TIME_LIB_BASE]=(void*)func,


extern void *aligned_alloc(size_t align_byte,size_t size);
//用于共享给子程序的函数向量表
//注意这个函数表要和宏定义DL_VECTOR_BASE_ADDR中的数值一致哦，要不然APP程序找不到
//函数存在哪里了		
static __attribute__((section(".DL_Vector")))
	   __attribute__((used)) 
	   void* DL_Vector_Table[DL_VECTOR_SIZE/sizeof(void*)] =
{
//stdio.h
	STDIO_DECLARE(stdin,STDIN)
	STDIO_DECLARE(stdout,STDOUT)
	STDIO_DECLARE(stderr,STDERR)
	STDIO_DECLARE(vfprintf,VFPRINTF)
	STDIO_DECLARE(vfscanf,VFSCANF)
	STDIO_DECLARE(remove,REMOVE)
	STDIO_DECLARE(rename,RENAME)
	STDIO_DECLARE(fclose,FCLOSE)
	STDIO_DECLARE(fflush,FFLUSH)
	STDIO_DECLARE(fopen,FOPEN)
	STDIO_DECLARE(freopen,FREOPEN)
	STDIO_DECLARE(fread,FREAD)
	STDIO_DECLARE(fwrite,FWRITE)
	STDIO_DECLARE(fseek,FSEEK)
	STDIO_DECLARE(ftell,FTELL)
	STDIO_DECLARE(fgetc,FGETC)
	STDIO_DECLARE(fgets,FGETS)
	STDIO_DECLARE(fputc,FPUTC)
	STDIO_DECLARE(fputs,FPUTS)
	STDIO_DECLARE(fgetpos,FGETPOS)
	STDIO_DECLARE(fsetpos,FSETPOS)
	STDIO_DECLARE(getc,GETC)
	STDIO_DECLARE(gets,GETS)
	STDIO_DECLARE(putc,PUTC)
	STDIO_DECLARE(puts,PUTS)
//stdlib.h
	STDLIB_DECLARE(calloc,CALLOC)
	STDLIB_DECLARE(free,FREE)
	STDLIB_DECLARE(malloc,MALLOC)
	STDLIB_DECLARE(realloc,REALLOC)
	STDLIB_DECLARE(aligned_alloc,ALIGEND_ALLOC)
//time.h
	TIME_LIB_DECLARE(clock,CLOCK)
	TIME_LIB_DECLARE(time,TIME)
};
