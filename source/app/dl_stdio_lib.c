#include "../common/dl_stdio_lib.h"

#define STDIO_EXTERN(func,index,ret,...)	DL_DECLARE_EXTERN_LIB_FUNC(func,DL_STDIO_LIB_BASE,DL_STDIO_FUNC_NUM,index,ret,##__VA_ARGS__)

__asm(".global __use_no_semihosting\n\t");

void _sys_exit(int code){
	
}

void _ttywrch(int ch){
	
}

int vfprintf(FILE * __restrict stream,const char * __restrict fmt, va_list arg){
	STDIO_EXTERN(vfprintf,VFPRINTF,int,FILE * __restrict stream,const char * __restrict fmt, va_list arg);
	return DL_FUNC_NAME(vfprintf)(stream,fmt,arg);
}

int vfscanf(FILE * __restrict stream, const char * __restrict fmt, va_list arg){
	STDIO_EXTERN(vfscanf,VFPRINTF,int,FILE * __restrict stream, const char * __restrict fmt, va_list arg);
	return DL_FUNC_NAME(vfscanf)(stream,fmt,arg);
}

int vprintf(const char * __restrict fmt, va_list arg){
	return vfprintf((FILE *)DL_VECTOR(STDOUT),fmt,arg);
}

int printf(const char * __restrict fmt, ...){
	va_list arg;
	int ret;
	va_start(arg,fmt);
	ret=vprintf(fmt,arg);
	va_end(arg);
	return ret;
}

int vscanf(const char * __restrict fmt, va_list arg){
	return vfscanf((FILE *)DL_VECTOR(STDIN),fmt,arg);
}

int scanf(const char * __restrict fmt,...){
	va_list arg;
	int ret;
	va_start(arg,fmt);
	ret=vscanf(fmt,arg);
	va_end(arg);
	return ret;
}

int fprintf(FILE * __restrict stream,const char * __restrict fmt, ...){
	va_list arg;
	int ret;
	va_start(arg,fmt);
	ret=vfprintf(stream,fmt,arg);
	va_end(arg);
	return ret;
}

int remove(const char * filename){
	STDIO_EXTERN(remove,REMOVE,int,const char * filename);
	return DL_FUNC_NAME(remove)(filename);
}

int rename(const char * old_name, const char * new_name){
	STDIO_EXTERN(rename,RENAME,int,const char * old_name, const char * new_name);
	return DL_FUNC_NAME(rename)(old_name,new_name);
}

int fclose(FILE * pfile){
	STDIO_EXTERN(fclose,FCLOSE,int,FILE * pfile);
	return DL_FUNC_NAME(fclose)(pfile);
}

int fflush(FILE * pfile){
	STDIO_EXTERN(fflush,FFLUSH,int,FILE * pfile);
	return DL_FUNC_NAME(fflush)(pfile);
}

FILE *fopen(const char * __restrict file_name,const char * __restrict mode){
	STDIO_EXTERN(fopen,FOPEN,FILE *,const char * __restrict file_name,const char * __restrict mode);
	return DL_FUNC_NAME(fopen)(file_name,mode);
}

FILE *freopen(const char * __restrict filename,const char * __restrict mode,FILE * __restrict stream){
	STDIO_EXTERN(freopen,FREOPEN,FILE *,const char * __restrict filename,const char * __restrict mode,FILE * __restrict stream);
	return DL_FUNC_NAME(freopen)(filename,mode,stream);
}

size_t fread(void * __restrict ptr,size_t size, size_t nmemb, FILE * __restrict stream){
	STDIO_EXTERN(fread,FREAD,size_t,void * __restrict ptr,size_t size, size_t nmemb, FILE * __restrict stream);
	return DL_FUNC_NAME(fread)(ptr,size,nmemb,stream);
}

size_t fwrite(const void * __restrict ptr,size_t size, size_t nmemb, FILE * __restrict stream){
	STDIO_EXTERN(fwrite,FWRITE,size_t,const void * __restrict ptr,size_t size, size_t nmemb, FILE * __restrict stream);
	return DL_FUNC_NAME(fwrite)(ptr,size,nmemb,stream);
}

int fseek(FILE * stream, long int offset, int whence){
	STDIO_EXTERN(fseek,FSEEK,int,FILE * stream, long int offset, int whence);
	return DL_FUNC_NAME(fseek)(stream,offset,whence);
}

long int ftell(FILE * stream){
	STDIO_EXTERN(ftell,FTELL,long int,FILE * stream);
	return DL_FUNC_NAME(ftell)(stream);
}

int fgetc(FILE * stream){
	STDIO_EXTERN(fgetc,FGETC,int,FILE * stream);
	return DL_FUNC_NAME(fgetc)(stream);
}

char *fgets(char * __restrict s, int n,FILE * __restrict stream){
	STDIO_EXTERN(fgets,FGETS,char *,char * __restrict s, int n,FILE * __restrict stream);
	return DL_FUNC_NAME(fgets)(s,n,stream);
}

int fputc(int c, FILE * stream){
	STDIO_EXTERN(fputc,FPUTC,int,int c, FILE * stream);
	return DL_FUNC_NAME(fputc)(c,stream);
}

int fputs(const char * __restrict s, FILE * __restrict stream){
	STDIO_EXTERN(fputs,FPUTS,int,const char * __restrict s, FILE * __restrict stream);
	return DL_FUNC_NAME(fputs)(s,stream);
}

int getc(FILE * stream){
	STDIO_EXTERN(getc,GETC,int,FILE * stream);
	return DL_FUNC_NAME(getc)(stream);
}

int (getchar)(void){
	return getc((FILE *)DL_VECTOR(STDIN));
}

char *gets(char * s){
	STDIO_EXTERN(gets,GETS,char *,char * s);
	return DL_FUNC_NAME(gets)(s);
}

int putc(int c, FILE * stream){
	STDIO_EXTERN(putc,PUTC,int,int c, FILE * stream);
	return DL_FUNC_NAME(putc)(c,stream);
}

int (putchar)(int c){
	return putc(c,(FILE *)DL_VECTOR(STDOUT));
}

int puts(const char * s){
	STDIO_EXTERN(puts,PUTS,int,const char * s);
	return DL_FUNC_NAME(puts)(s);
}





