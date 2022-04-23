#include "../common/dl_stdlib_lib.h"

#define STDIB_EXTERN(func,index,ret,...)	DL_DECLARE_EXTERN_LIB_FUNC(func,DL_STDLIB_LIB_BASE,DL_STDLIB_FUNC_NUM,index,ret,##__VA_ARGS__)

__asm(".global __use_no_heap_region\n\t");

void *calloc(size_t nmemb, size_t size){
	STDIB_EXTERN(calloc,CALLOC,void *,size_t nmemb, size_t size);
	return DL_FUNC_NAME(calloc)(nmemb,size);
}

void free(void * ptr){
	STDIB_EXTERN(free,FREE,void,void * ptr);
	DL_FUNC_NAME(free)(ptr);
}

void *malloc(size_t size){
	STDIB_EXTERN(malloc,MALLOC,void *,size_t size);
	return DL_FUNC_NAME(malloc)(size);
}

void *realloc(void * ptr, size_t size){
	STDIB_EXTERN(realloc,REALLOC,void *,void * ptr, size_t size);
	return DL_FUNC_NAME(realloc)(ptr,size);
}

void *aligned_alloc(size_t align_byte,size_t size){
	STDIB_EXTERN(aligned_alloc,ALIGEND_ALLOC,void *,size_t align_byte,size_t size);
	return DL_FUNC_NAME(aligned_alloc)(align_byte,size);
}
