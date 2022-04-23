#include "src/dl_lib.h"



int main(void){
    DL_Handler use_handle;
    DL_Err_Type err;
    int(*export_func)(void);

    err=dl_load_file(&use_handle,"rel_axf_project_template/Objects/dll_generate.axf");
    export_func=dl_get_func(&use_handle,"export_func");
    export_func();
    dl_get_entry(&use_handle)(0,NULL);
    dl_destroy_lib(&use_handle);
    
    return 0;
}