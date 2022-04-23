# dynamic_loader

#### 介绍
本项目是一个在单片机（如：STM32）上实现动态加载功能的函数库，与Windows中的dll，Linux中的so类似，可以将代码动态地从其他的存储介质，动态加载到RAM中

#### 软件架构
本项目文件夹有三个，其中common存储了用于生成可重定位的.axf文件的工程与动态加载器工程交互用的函数，src提供动态加载器的源码，rel_axf_project_template提供了一个简单的可重定位的.axf文件的工程示例，example.c是一个简单的使用示例，所有文件的主要功能如下：
- /common/dl_extern_lib.h 描述了app程序用于调用host程序的函数向量表的基地址，以及相关的一些宏定义
- /common/dl_stdio_lib.h 描述了app程序调用C库stdio.h中函数时，对应的函数在函数向量表中的索引
- /common/dl_stdlib_lib.h 描述了app程序调用C库stdlib.h中函数时，对应的函数在函数向量表中的索引
- /common/dl_time_lib.h 描述了app程序调用C库time.h中函数时，对应的函数在函数向量表中的索引

- /rel_axf_project_template/app/dl_stdio_lib.c 对于app程序调用到的C库stdio.h中的函数进行重定向
- /rel_axf_project_template/app/dl_stdlib_lib.c 对于app程序调用到的C库stdlib.h中的函数进行重定向
- /rel_axf_project_template/app/dl_time_lib.c 对于app程序调用到的C库time.h中的函数进行重定向

- /src/dl_arch.c 用于进行代码数据重定向与cache刷新，与芯片架构有关
- /src/dl_elf.h 用于elf格式文件解码
- /src/dl_lib.c 动态加载实现源码
- /src/dl_lib.h 动态加载供给应用程序使用的函数
- /src/dl_port.c 动态加载主机底层需要实现的函数接口，移植时主要修改的文件
- /src/dl_port.h 动态加载主机底层需要实现的函数声明，包含一些宏定义，移植时需要根据自己的芯片修改
- /src/dl_vector.c host程序供给app程序使用的函数声明，需要app调用的函数在这里声明

#### 安装教程
1.  首先确定好自己的硬件平台是否适配，目前本程序仅使用了Coretex-M7内核的STMH743单片机进行测试，理论上arm的Coretex-M系列可以直接使用，其他的arm系列芯片可能在重定位指令与Cache的支持的不够好
2.  确定自己的芯片中是否使用了Cache，若使用了Cache，请将/source/host/dl_port.h中的宏定义DL_CACHE_USE置为1
3.  根据自己的软件平台，修改/src/dl_port.c中相关函数的实现，本项目以FatFs文件系统作为例子进行实现，若文件系统不同需要修改函数实现
4.  移植完成后，使用rel_axf_project_template生成app程序的elf文件，默认编译生成的elf文件路径为rel_axf_project_template/Objects/dll_generate.axf
5.  使用诸如fromelf等工具确定生成的elf文件没问题后，就可以愉快的进行动态加载了

#### 使用说明
1.  在代码中首先使用DL_Handler定义一个句柄，类似Windows的dll的句柄
2.  将生成的dll_generate.axf加载到内存中
3.  在代码中包含dl_lib.h头文件，同时使用dl_load_lib将dll_generate.axf文件加载到句柄中同时确任返回值是否为DL_NO_ERR
4.  加载成功后，可使用dl_get_func通过函数名获得库中对应函数的首地址
5.  可使用dl_get_entry直接获得elf文件中的dl_main函数
6.  动态加载的程序执行完成后，可使用dl_destroy_lib释放句柄