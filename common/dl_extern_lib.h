#ifndef DL_EXTERN_LIB_H__
#define DL_EXTERN_LIB_H__

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>

__attribute__((always_inline)) static inline void* dl_vector_get_lib_func_entry(size_t index){
	register size_t __r0 __asm("r0") = (size_t)index;
	__asm volatile ("svc 8":"=r"(__r0):"r"(__r0):"cc","memory");
	return (void*)__r0;
}

#define DL_STATIC_ASSERT(exp)	typedef int __ai[(exp)?1:-1]

#define DL_FUNC_NAME(name)		__dl_use_##name
#define DL_DECLARE_EXTERN_LIB_FUNC(func,base,max_func_num,index,ret,...) \
									ret (*DL_FUNC_NAME(func))(__VA_ARGS__)=dl_vector_get_lib_func_entry(index+base);\
									DL_STATIC_ASSERT(index<max_func_num)
									

#define DL_STDIO_LIB_BASE		(0)
#define DL_STDIO_FUNC_NUM		(25)

#define DL_STDLIB_LIB_BASE	 	(DL_STDIO_LIB_BASE+DL_STDIO_FUNC_NUM)
#define DL_STDLIB_FUNC_NUM		(5)

#define DL_TIME_LIB_BASE		(DL_STDLIB_LIB_BASE+DL_STDLIB_FUNC_NUM)
#define DL_TIME_LIB_NUM			(2)

#define DL_STRING_LIB_BASE		(DL_TIME_LIB_BASE+DL_TIME_LIB_NUM)
#define DL_STRING_LIB_NUM		(22)
								
//使用DL_EXPORT导出函数
#define DL_EXPORT		__attribute__((visibility("default")))
#define DL_HIDDEN		__attribute__((visibility("hidden")))

#endif
