; 定义代码段
    AREA SVC_HELPER_REGION, CODE, READONLY
    
    THUMB               ; 指定使用 Thumb 指令集
    PRESERVE8           ; 保证 8 字节栈对齐

    IMPORT SVC_Handler_Main  ; 声明 C 语言处理函数
    EXPORT SVC_IRQHandler    ; 导出符号

SVC_IRQHandler
    ; --- 针对 Cortex-M0 ---
    ; 1. 默认读取 MSP 到 R0
    MRS     R0, MSP
    
    ; 2. 检查 EXC_RETURN (LR) 的位 2
    ; M0 不支持直接 TST LR, #4，需要先搬移到低寄存器
    MOV     R1, LR          ; R1 = LR
    MOVS    R2, #4          ; R2 = 4 (注意使用 MOVS)
    TST     R1, R2          ; 检查 (LR & 4)
    
    ; 3. 如果结果为 0 (Z标志置位)，说明是 MSP，跳转
    BEQ     addr_found
    
    ; 4. 如果结果不为 0，说明是 PSP，读取 PSP 到 R0
    MRS     R0, PSP

addr_found
    ; 5. 跳转到 C 函数
    ; M0 建议使用寄存器间接跳转以确保地址合法性
    LDR     R1, =SVC_Handler_Main
    BX      R1
    
    ALIGN
    END