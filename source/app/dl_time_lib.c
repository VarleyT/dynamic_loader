#include "../common/dl_time_lib.h"

#define TIME_EXTERN(func,index,ret,...)	DL_DECLARE_EXTERN_LIB_FUNC(func,DL_TIME_LIB_BASE,DL_TIME_LIB_NUM,index,ret,##__VA_ARGS__)

clock_t clock(void){
	TIME_EXTERN(clock,CLOCK,clock_t,void);
	return DL_FUNC_NAME(clock)();
}

time_t time(time_t *t){
	TIME_EXTERN(time,TIME,time_t,time_t *t);
	return DL_FUNC_NAME(time)(t);
}
