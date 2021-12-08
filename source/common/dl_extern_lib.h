#ifndef DL_EXTERN_LIB_H__
#define DL_EXTERN_LIB_H__

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define DL_VECTOR_BASE_ADDR		0x3800C000
#define DL_VECTOR_SIZE			(16*1024)
#define DL_VECTOR(index)		(*(volatile void**)(DL_VECTOR_BASE_ADDR+sizeof(void*)*(index)))
#define DL_STATIC_ASSERT(ex)	do { \
									typedef int ai[(ex) ? 1 : -1]; \
								} while(0)
#define DL_FUNC_NAME(name)		__dl_use_##name
#define DL_DECLARE_EXTERN_LIB_FUNC(func,base,max_func_num,index,ret,...) \
									ret (*DL_FUNC_NAME(func))(__VA_ARGS__)=DL_VECTOR(index+base);\
									DL_STATIC_ASSERT(index<max_func_num)
									

#define DL_STDIO_LIB_BASE		(0)
#define DL_STDIO_FUNC_NUM		(25)

#define DL_STDLIB_LIB_BASE	 	(DL_STDIO_LIB_BASE+DL_STDIO_FUNC_NUM)
#define DL_STDLIB_FUNC_NUM		(5)

#define DL_TIME_LIB_BASE		(DL_STDLIB_LIB_BASE+DL_STDLIB_FUNC_NUM)
#define DL_TIME_LIB_NUM			(2)

//使用DL_EXPORT导出函数
#define DL_EXPORT		__attribute__((visibility("default")))
#define DL_HIDDEN		__attribute__((visibility("hidden")))

#endif
