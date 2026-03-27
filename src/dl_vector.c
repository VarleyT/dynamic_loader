/*
*   @file  dl_vector.c
*   @author  wzh
*   @version  1.0
*   @date 2021-12-3
*   @description  用于创建主程序与子程序可以共同访问的一块内存，主要用于存储主程序一些函数的函数地址
*                 使得子程序可以调用主程序的函数
*/
#include "dl_lib.h"
#include "../common/dl_extern_lib.h"
#include "../common/dl_stdio_lib.h"
#include "../common/dl_stdlib_lib.h"
#include "../common/dl_time_lib.h"
#include "../common/dl_string_lib.h"
#include <time.h>

#define STDIO_DECLARE(func,index)	[index+DL_STDIO_LIB_BASE]=(void*)func,

#define STDLIB_DECLARE(func,index)	[index+DL_STDLIB_LIB_BASE]=(void*)func,
	
#define TIME_LIB_DECLARE(func,index) [index+DL_TIME_LIB_BASE]=(void*)func,

#define STRING_LIB_DECLARE(func,index) [index+DL_STRING_LIB_BASE]=(void*)func,

extern void *aligned_alloc(size_t align_byte,size_t size);

//用于共享给子程序的内存
static __attribute__((used)) 
	   void* DL_Vector_Table[] =
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
//string.h
	STRING_LIB_DECLARE(memchr	,	MEMCHR)
	STRING_LIB_DECLARE(memcmp	,	MEMCMP)
	STRING_LIB_DECLARE(memcpy	,	MEMCPY)
	STRING_LIB_DECLARE(memmove	,	MEMMOVE)
	STRING_LIB_DECLARE(memset	,	MEMSET)
	STRING_LIB_DECLARE(strcat	,	STRCAT)
	STRING_LIB_DECLARE(strncat	,	STRNCAT)
	STRING_LIB_DECLARE(strchr	,	STRCHR)
	STRING_LIB_DECLARE(strcmp	,	STRCMP)
	STRING_LIB_DECLARE(strncmp	,	STRNCMP)
	STRING_LIB_DECLARE(strcoll	,	STRCOLL)
	STRING_LIB_DECLARE(strcpy	,	STRCPY)
	STRING_LIB_DECLARE(strncpy	,	STRNCPY)
	STRING_LIB_DECLARE(strcspn	,	STRCSPN)
	STRING_LIB_DECLARE(strerror	,	STRERROR)
	STRING_LIB_DECLARE(strlen	,	STRLEN)
	STRING_LIB_DECLARE(strpbrk	,	STRPBRK)
	STRING_LIB_DECLARE(strrchr	,	STRRCHR)
	STRING_LIB_DECLARE(strspn	,	STRSPN)
	STRING_LIB_DECLARE(strstr	,	STRSTR)
	STRING_LIB_DECLARE(strtok	,	STRTOK)
	STRING_LIB_DECLARE(strxfrm	,	STRXFRM)
};

void* svc_dl_vector_get_lib_func_entry(size_t index){
	if(index<sizeof(DL_Vector_Table)/sizeof(DL_Vector_Table[0])){
		uintptr_t addr = (uintptr_t)DL_Vector_Table[index];
		/*
		 * Cortex-M only supports Thumb state. BLX target address bit0 must be 1
		 * for function entries; otherwise it can HardFault on branch.
		 * Keep stdio stream objects as raw data pointers.
		 */
		if(index != (DL_STDIO_LIB_BASE + STDIN) &&
		   index != (DL_STDIO_LIB_BASE + STDOUT) &&
		   index != (DL_STDIO_LIB_BASE + STDERR)){
			addr |= 1u;
		}
		return (void*)addr;
	}
	else
		return NULL;
}


/**
 * @brief SVC 逻辑分发器
 * @param svc_args 指向硬件压栈后的起始地址 (R0 传入)
 */
void SVC_Handler_Main(uint32_t *svc_args) {
    // Hardware stack frame: R0, R1, R2, R3, R12, LR, PC, xPSR
    uint8_t *pc = (uint8_t *)(svc_args[6] & (~1u));
    uint8_t svc_num = pc[-2];
    if (svc_num == 8) {
        size_t index = (size_t)svc_args[0];
        // Write return value back to stacked R0.
        svc_args[0] = (uint32_t)svc_dl_vector_get_lib_func_entry(index);
    }
}
