
/********************************************************************
* 文件名: 	start.S
* 版本：	V1.0
* 作者:		李鑫
* 日期:		2021.11.31
* 说明:		本文件包含start的所有接口函数及宏定义
* 版权:		龙芯中科（太原）技术有限公司
*备注：
      1 这个start.s已经禁止了总中断
	2 禁止了TIMER中断使能，但是代码从头开始执行时，TMIER中断的标志位还是会存在的
	  因此在中断处理中 忽略TMER中断标志位就行。
********************************************************************/

#include "start.h"
.extern  Soft0_IRQHandler
.extern  Soft1_IRQHandler
.extern  Exint_IRQHandler
.extern  Wake_IRQHandler
.extern  ResValid_IRQHandler
.extern  BatFail_IRQHandler
.extern  C32kFail_IRQHandler
.extern  C8mFail_IRQHandler
.extern  Key_IRQHandler
.extern  Ring_IRQHandler
.extern  Rtc_IRQHandler
.extern  TIMER_IRQHandler
.extern  CpuTimer_IRQHandler
.extern  I2C_IRQHandler
.extern  UART1_IRQHandler
.extern  UART0_IRQHandler
.extern  FLASH_IRQHandler
.extern  SPI_IRQHandler
.extern  ADC_IRQHandler

#define PRINT_STR(x) \
	.section .rodata;98: .asciz x; .text; la a0, 98b; bl outputstring

/************************************/
/*			       C入口*/
.extern main
//.extern IRQ_Exception
/************************************/

/************************************/
/*  bss段起始地址和结束地址*/
.extern _sidata
.extern _sdata
.extern _edata
.extern _sbss
.extern _ebss
/************************************/

#-------------------------------------------------------------------
/* start address for the initialization values of the .data section. defined in ld.script */
.word  _sidata
/* start address for the .data section. defined in ld.script */
.word  _sdata
/* end address for the .data section. defined in ld.script */
.word  _edata
/* start address for the .bss section. defined in ld.script */
.word  _sbss
/* end address for the .bss section. defined in ld.script */
.word  _ebss

.section .text._start                   # begin code segment
.weak _start
.type _start, %function
.globl _start
#All Exception Entries

	  li.w    t0, 0x1feb0000				/* 将0x1feb0000的存入t0寄存器*/
        ld.w    t1, t0 , 0x04					/* 将command值读入t1寄存器*/
	  li.w    t2, 0xc000000					/* 将0xc000000值载入t2寄存器*/
        and     t1, t1, t2					/* 将t1 = 0xc000000&command，判断复位来源 */
#        beq     t1, t2, cpu_init_start   			/* 如果t1 == t2 ，即休眠唤醒，执行cpu_init_start，否则是复位，执行以下程序 */
        bne     t1,zero,cpu_init_start   			/* 如果t1 != 0 ，即非外部复位，执行cpu_init_start，否则，执行以下程序 */
_start:
        move     t1 , zero 		     			/* 如果t1 = 0 */
        b    LoopCopyDataInit					/* 跳转执行拷贝数据段 LoopCopyDataInit */
CopyDataInit:
        la.abs   t3, _sidata					/* t3 = &_sidata(LMA) */
        add.w    t4, t3, t1  					/* t4 = t3 + t1（地址）  */
        ld.w     t3, t4, 0x0					/* t3 = (t4)  */
        add.w    t4, t0, t1  					/* t4 = (t0 + t1)(VMA)  */
        st.w     t3, t4, 0x0					/* t4 + 0 = t3 从flash取数给到ram中 */
        addi.w   t1, t1, 0x4					/* t1 += 4  */
LoopCopyDataInit:
        la.abs   t0, _sdata					/* t0 = &_sdata(VMA) */
        la.abs   t3, _edata					/* t3 = &_edata(VMA) */
        add.w    t2, t0, t1					/* t2 = (t0 + t1) */
        bne      t2, t3, CopyDataInit			/* t2 != t3 ->  CopyDataInit*/

        la.abs  t0, _sbss					/* t0 = &_sbss(VMA)*/
        la.abs  t1, _ebss					/* t1 = &_ebss(VMA)*/
        beq     t1, t0, cpu_init_start			/* 如果t1 == t2 ，即休眠唤醒，执行cpu_init_start，否则是复位，执行以下程序 */
LoopFillZerobss:
        st.w    zero, t0, 0
        addi.w  t0, t0, 4
        bne t1, t0, LoopFillZerobss
#set up basic system function
        /* cpu init*/
cpu_init_start:
	  /* reset normal exception base and Ex config */
        li.w      t0, 0x1c001000				/* t0 = 0x1c001000*/
        csrwr     t0, CSR_EBase        			/* 写中断入口地址0x1c001000*/
        li.w      t0, (0<<S_CSR_ExConfig_VS)|(0x0000<<S_CSR_ExConfig_IM) #4 instruction gap /* 设置中断入口与异常入口一致*/
        csrwr     t0, CSR_ExConfig
        #set int masks
        li.w      t0, 0x1fff
        csrxchg t0, t0, CSR_ExConfig

        ### enable float unit
        li.w    t0, 1
        csrwr   t0, CSR_CU

#if 0
    ##set VSEG0(0x00000000~0x1fffffff) to cached, other VSEG to uncached
        li.w      t0, CACHE_OP
        csrwr     t0, CSR_SEGCA
    ##set VSEG5(0xa0000000~0xbfffffff) to PSEG0(0x00000000~0x1fffffff), other VSEG unchanged
        li.w      t0, ADDR_MAP
        csrwr     t0, CSR_SEGPA
    ##set DA=0(change DA-mode to AD-mode)
        li.w      t0, 0x8
        csrxchg   zero, t0, CSR_CRMD
#else
      ### set DACF&DACAM as uncached unmapped
      li.w      t0, 0x00
      li.w      t1, 0x1e0
      csrxchg   t0, t1, CSR_CRMD
#endif
        li.w    sp, SP_BASE
	  bl      main
        jirl      zero, ra, 0

1:
#	  bl     serial_init_0
#        PRINT_STR("non-int exception\n")
#        PRINT_STR("crmd: ");
#        csrrd    a0, CSR_CRMD
#        bl     outputaddr
#        PRINT_STR("exstatus: ");
#        csrrd    a0, CSR_ExStatus
#        bl     outputaddr
#        PRINT_STR("errpc: ");
#        csrrd    a0, CSR_EPC
#        bl     outputaddr
#        PRINT_STR("baddr: ");
#        csrrd    a0, CSR_BadVAddr
#        bl     outputaddr
loop:
	  b 		loop

#.section .text._start
        .org 0x1000
DEFAULT_INT_HANDLER:
	  SAVE_REGS_FAST(REGS_MEM)
        csrrd   t0, CSR_ExStatus
        andi    t1, t0, 0xfff
        beqz    t1, 1b
        andi    t1, t0, INT_VECTOR
        beqz    t1, exception_peripheral
exception_pmu:

        andi    t1,t0,0x800
        bnez    t1,cpu_timer_label  /*核定时器*/

        andi    t1,t0,0x80
        bnez    t1,extern_label  	/*EXTI-H5:line5 外部中断*/

        andi    t1,t0,0x20
        bnez    t1,krr_label  	/*EXTI-H3:line5 Krr中断*/

        andi    t1,t0,0x10
        bnez    t1,bcc_label  	/*EXTI-H2:line4  bcc中断*/

        andi    t1,t0,0x8
        bnez    t1,resvalid_label 	/*EXTI-H1:line3 pmu结果中断*/

        andi    t1,t0,0x4
        bnez    t1,wake_label 	/*EXTI-H0:line2 pmu唤醒中断*/

        andi    t1,t0,0x2
        bnez    t1,swi1_label       /*软件中断 1*/

        andi    t1,t0,0x1
        bnez    t1,swi0_label      	/*软件中断 0*/

	  b       exception_exit

swi0_label:
	bl      	Soft0_IRQHandler
	b       	exception_exit
swi1_label:
	bl     	Soft1_IRQHandler
	b      	exception_exit

wake_label:
	bl      	Wake_IRQHandler
	b       	exception_exit
resvalid_label:
	bl      	ResValid_IRQHandler
	b       	exception_exit
bcc_label:
	li.w		t0, 0x1feb0000
	ld.d		t1, t0, 0x4
	lu12i.w 	t2, 0x40
	and		t2, t2,t1
	bnez		t2, bat_label
	lu12i.w 	t2, 0x80
	and		t2, t2, t1
	bnez		t2, c32k_label
	lu12i.w 	t2, 0x100
	and		t2, t2, t1
	bnez		t2, c8m_label
	b 		exception_exit
krr_label:
	li.w		t0, 0x1feb0000
	ld.w		t1, t0,0x4
	lu12i.w 	t2, 0x200
	and		t2, t2, t1
	bnez		t2, key_label
	lu12i.w 	t2, 0x400
	and		t2, t2, t1
	bnez		t2, ring_label
	lu12i.w 	t2, 0x800
	and		t2, t2, t1
	bnez		t2, rtc_label
	b 		exception_exit

bat_label:
	bl 		BatFail_IRQHandler
	b 		exception_exit
c32k_label:
	bl 		C32kFail_IRQHandler
	b 		exception_exit
c8m_label:
	bl 		C8mFail_IRQHandler
	b 		exception_exit
key_label:
	bl 		Key_IRQHandler
	b 		exception_exit
ring_label:
	bl 		Ring_IRQHandler
	b 		exception_exit
rtc_label:
	bl 		Rtc_IRQHandler
	b 		exception_exit

extern_label:

      bl      	Exint_IRQHandler
      b      	exception_exit
#if 0
	li.w		t3, 0x1feb0000
	ld.w		t1, t3,0x20
	ld.w		t2, t3,0x2c
	and		t2, t2, t1

	andi.w	t1, t2,0x01
	bnez  	t1  1f
	b 		2f
1:
	bl		ExtGpioA0_IRQHandler

2:
	srl.w		t2, t2,0x01
	andi.w	t1, t2,0x01
	bnez  	t1,1f
	b		2f
1:
	bl		ExtGpioA1_IRQHandler
2:
	srl.w		t2, t2,0x01
	andi.w	t1, t2,0x01
	bnez  	t1,1f
	b		2f
1:
	bl 		ExtGpioA2_IRQHandler
2:
	srl.w		t2, t2,0x01
	andi.w	t1, t2,0x01
	bnez  	t1,1f
	b		2f
1:
	bl		ExtGpioA3_IRQHandler
2:
	srl.w		t2, t2,0x01
	andi.w	t1, t2,0x01
	bnez  	t1,1f
	b		2f
1:
	bl		ExtGpioA4_IRQHandler
2:
	srl.w		t2, t2,0x01
	andi.w	t1, t2,0x01
	bnez  	t1,1f
	b		2f
1:
	bl		ExtGpioA5_IRQHandler
2:
	srl.w		t2, t2,0x01
	andi.w	t1, t2,0x01
	bnez  	t1,1f
	b		2f
1:
	bl		ExtGpioA6_IRQHandler
2:
	srl.w		t2, t2,0x01
	andi.w	t1, t2,0x01
	bnez  	t1,1f
	b		2f
1:
	bl		ExtGpioA7_IRQHandler
2:
	srl.w		t2, t2,0x01
	andi.w	t1, t2,0x01
	bnez  	t1,1f
	b		2f
1:
	bl		ExtGpioA8_IRQHandler
2:
	srl.w		t2, t2,0x01
	andi.w	t1, t2,0x01
	bnez  	t1,1f
	b		2f
1:
	bl		ExtGpioA9_IRQHandler
2:
	srl.w		t2, t2,0x01
	andi.w	t1, t2,0x01
	bnez  	t1,1f
	b		2f
1:
	bl		ExtGpioA10_IRQHandler
2:
	srl.w		t2, t2,0x01
	andi.w	t1, t2,0x01
	bnez  	t1,1f
	b		2f
1:
	bl		ExtGpioA11_IRQHandler
2:
	srl.w		t2, t2,0x01
	andi.w	t1, t2,0x01
	bnez  	t1,1f
	b		2f
1:
	bl		ExtGpioA12_IRQHandler
2:
	srl.w		t2, t2,0x01
	andi.w	t1, t2,0x01
	bnez  	t1,1f
	b		2f
1:
	bl		ExtGpioA13_IRQHandler
2:
	srl.w		t2, t2,0x01
	andi.w	t1, t2,0x01
	bnez  	t1,1f
	b		2f
1:
	bl		ExtGpioA14_IRQHandler
2:
	srl.w		t2, t2,0x01
	andi.w	t1, t2,0x01
	bnez  	t1,1f
	b		2f
1:
	bl		ExtGpioA15_IRQHandler
2:
	srl.w		t2, t2,0x01
	andi.w	t1, t2,0x01
	bnez  	t1,1f
	b		2f
1:
	bl		ExtGpioB0_IRQHandler
2:
	srl.w		t2, t2,0x01
	andi.w	t1, t2,0x01
	bnez  	t1,1f
	b		2f
1:
	bl		ExtGpioB1_IRQHandler
2:
	srl.w		t2, t2,0x01
	andi.w	t1, t2,0x01
	bnez  	t1,1f
	b		2f
1:
	bl		ExtGpioB2_IRQHandler
2:
	srl.w		t2, t2,0x01
	andi.w	t1, t2,0x01
	bnez  	t1,1f
	b		2f
1:
	bl		ExtGpioB3_IRQHandler
2:
	srl.w		t2, t2,0x01
	andi.w	t1, t2,0x01
	bnez  	t1,1f
	b		2f
1:
	bl		ExtGpioB4_IRQHandler
2:
	srl.w		t2, t2,0x01
	andi.w	t1, t2,0x01
	bnez  	t1,1f
	b		2f
1:
	bl		ExtGpioB5_IRQHandler
2:
	srl.w		t2, t2,0x01
	andi.w	t1, t2,0x01
	bnez  	t1,1f
	b		2f
1:
	bl		ExtGpioB6_IRQHandler
2:
	srl.w		t2, t2,0x01
	andi.w	t1, t2,0x01
	bnez  	t1,1f
	b		2f
1:
	bl		ExtGpioB7_IRQHandler
2:
	srl.w		t2, t2,0x01
	andi.w	t1, t2,0x01
	bnez  	t1,1f
	b		2f
1:
	bl		ExtGpioB8_IRQHandler
2:
	srl.w		t2, t2,0x01
	andi.w	t1, t2,0x01
	bnez  	t1,1f
	b		2f
1:
	bl		ExtGpioB9_IRQHandler
2:
	srl.w		t2, t2,0x01
	andi.w	t1, t2,0x01
	bnez  	t1,1f
	b		2f
1:
	bl		ExtGpioB10_IRQHandler
2:
	srl.w		t2, t2,0x01
	andi.w	t1, t2,0x01
	bnez  	t1,1f
	b		2f
1:
	bl		ExtGpioB11_IRQHandler
2:
	srl.w		t2, t2,0x01
	andi.w	t1, t2,0x01
	bnez  	t1,1f
	b		2f
1:
	bl		ExtGpioB12_IRQHandler
2:
	srl.w		t2, t2,0x01
	andi.w	t1, t2,0x01
	bnez  	t1,1f
	b		2f
1:
	bl		ExtGpioB13_IRQHandler
2:
	srl.w		t2, t2,0x01
	andi.w	t1, t2,0x01
	bnez  	t1,1f
	b		2f
1:
	bl		ExtGpio14_IRQHandler
2:
	srl.w		t2, t2,0x01
	andi.w	t1, t2,0x01
	bnez  	t1,1f
	b		2f
1:
	bl		ExtGpioB15_IRQHandler
2:
      b       exception_exit
#endif

cpu_timer_label:
        bl      CpuTimer_IRQHandler
        b       exception_exit

exception_peripheral:
	andi  t1, t0, INTC_VECTOR
	beqz  t1, exception_exit

	li.w	t2, 0x1fea0000
	ld.bu	t1, t2,0x5

	andi	t2, t1,0x1
	bnez	t2, timer_label

	andi 	t2, t1,0x2
	bnez	t2, i2c_label

	andi 	t2, t1,0x4
	bnez	t2, uart1_label

	andi 	t2, t1,0x8
	bnez	t2, uart0_label

	andi 	t2, t1,0x10
	bnez	t2, flash_label

	andi 	t2, t1,0x20
	bnez	t2, spi_label

	andi 	t2, t1,0x40
	bnez	t2, adc_label

      b       exception_exit

timer_label:
	bl 	  TIMER_IRQHandler
	b 	  exception_exit
i2c_label:
	bl 	  I2C_IRQHandler
	b 	  exception_exit
uart1_label:
	bl 	  UART1_IRQHandler
	b 	  exception_exit
uart0_label:
	bl 	 UART0_IRQHandler
	b 	 exception_exit
flash_label:
	bl 	 FLASH_IRQHandler
	b	 exception_exit
spi_label:
	bl 	 SPI_IRQHandler
	b	 exception_exit
adc_label:
	bl 	 ADC_IRQHandler
	b	exception_exit

exception_exit:
	RESTORE_REGS_FAST(REGS_MEM)
      ertn


#if 0

/********************************************************
*		作者：	lixin
*		功能：LA32 串口简单字符打印
*
********************************************************/
LEAF(outputstring)
//  or      s7,ra,$0
        addu    v1, $0, a0 			#字符串首地址传给V1
1:
        lbu     t0, 0x0(v1)			#将字符串的首个字符加载到t0
        beq     t0, $0, 1f			#如果首字符为0，则跳转1f，否则继续执行；
        nop
10:     la      v0, 0x00004000		#加载串口0的地址到V0
        lbu     v0, 0x5(v0)			#将线路状态寄存器的值加载到V0
        andi    v0, v0,0x20			#V0中的值&0x20，判断传输FIFO是否有数据
        beqz    v0, 10b 			#如果V0 ==0 ；表明有数据，等待；
        nop
//      lui     AT, 0xbfe0
        li      AT, 0x00004000		#加载基地址到临时寄存器at；
        sb      t0, 0x0(AT)			#将t0的值存入基地址寄存器的数据寄存器中；
/////////////////////////////
        addiu   v1, v1, 1			#字符地址自增1
        beq     $0, $0, 1b			#跳转1f，继续执行；
        nop
1:
        la      v0, 0x00004000  #如果首地址为0则加载串口基地址
        lbu     v0, 0x5(v0)			#将线路状态寄存器的值加载到V0
        andi    v0, v0,0x40			#提取 传输位
        beqz    v0, 1b 				#判断传输是否为空
        nop
        jr      ra				#返回函数
        nop
END(outputstring)

	li.d	a0, COM1_BASE_ADDR
	li.w	a1, 0x80
	st.b	a1, a0, 3

	li.w	a1, UART_DIV_HI
	st.b	a1, a0, 1
	li.w	a1, UART_DIV_LO
	st.b	a1, a0, 0
	li.w	a1, 3	#CFCR_8BITS
	st.b	a1, a0, 3

	li.w	a1, 71
	st.b	a1, a0, 2
	jirl	zero, ra, 0

LEAF(serial_init_0)
    lw      a1, %lo(ser8m_presc_param)($0)
    li      a0,0x00004000
    li      t1,128
    addiu   a2,a0,3
    sb      t1,3(a0)
    #srl    t1,t1,0x8
    andi    t1,a1, 0xff00
    li      t2,8
    srl     t1,t1,t2
    sb      t1,1(a0)
    andi    t1,a1, 0x00ff
    sb      t1,0(a0)
    li      t2,16
    srl     t1,a1, t2
    sb      t1,2(a0)
#        li      t1,3//11        #8bit
    li      t1,7//11        #8bit 2stopbit
    sb      t1,3(a0)
    li      t1,0x06   #4word int
    sb      t1,2(a0)
    jr      ra
END(initserial)


LEAF(serial_prescal)
    or      t1, a1, $0
    li      t2, 4
    divu    t1, a0, t1
    srl     t1, t1, t2
    li      t3, 100
    divu    v0, t1, t3
    mfhi    v1
    li      t1, 8
    sll     v1, v1, t1
    divu    v1, v1, t3
    li      t1, 16
    sll     v1, v1, t1
    or      v0, v0, v1
    sw      v0, %lo(ser8m_presc_param)($0)
END(serial_prescal)

LEAF(serial_init_1)
    li      t0, 32768
    li      t1, 100
    li      t2, 3
    divu    v0, t0, a1    //a1: baud rate
    srl     v0, v0, t2
    divu    v0, v0, t1    //v0: integer  of prescale
    mfhi    v1
    li      t2, 8
    sll     v1, v1, t2
    divu    v1, v1, t1    //v1: fraction of prescale
    li      a0, 0x00004400
    li      t1,128
    addiu   a2,a0,3
    sb      t1,3(a0)
    #srl    t1,t1,0x8
    li      t1,0      #frx divider low
    sb      t1,1(a0)
#        li      t1,0x4      # divider, highest possible baud rate
    sb      v0,0(a0)
#        li      t1,0x57
    sb      v1,2(a0)
    li      t1,3//11        #8bit
    sb      t1,3(a0)
    li      t1,0x38
    sb      t1,4(a0)
    li      t1,0x06   #4word int
    sb      t1,2(a0)
    jr      ra
END(serial_init_1)


LEAF(get_inte8m_freq)
    li      t0, 0x5800
    li      t1, 0x6800
    sw      $0, 0x0(t1)
    sw      $0, 0x4(t1)
    li      t2, 0x1
    li      t3, 0xfffff   //mask for PMU_COUNT
    lw      t4, 0x08(t0)
    sw      t2, 0x0(t1)
    addiu   t4, t4, 0x40    //wait 1/4 s
    and     t3, t3, t4
1:  lw      t2, 0x08(t0)
    bne     t2, t3, 1b
    nop
    lw      v0, 0x08(t1)
    li      t2, 0x2
    sll     v0, v0, t2
    sw      v0, %lo(inte8m)($0)
    sw      $0, 0x0(t1)
    sw      $0, 0x4(t1)
    jr      ra
END(get_inte8m_freq)



#endif


#if 0
/*
 * Simple character printing routine used before full initialization
 */
/* baud rate definitions, matching include/termios.h */
#define B0	0
#define B50	50
#define B75	75
#define B110	110
#define B134	134
#define B150	150
#define B200	200
#define B300	300
#define B600	600
#define B1200	1200
#define B1800	1800
#define B2400	2400
#define B4800	4800
#define B9600	9600
#define B19200	19200
#define B38400	38400
#define B57600	57600
#define B115200	115200

#define UART_REF_CLK	100000000
#define UART_DIV_HI	(((UART_REF_CLK + (115200*8)) / (115200*16)) >> 8)
#define UART_DIV_LO	(((UART_REF_CLK + (115200*8)) / (115200*16)) & 0xff)
/*************************************
 *used: a0~a1
 *************************************/
LEAF(initserial)
	li.d	a0, COM1_BASE_ADDR
	li.w	a1, 0x80
	st.b	a1, a0, 3

	li.w	a1, UART_DIV_HI
	st.b	a1, a0, 1
	li.w	a1, UART_DIV_LO
	st.b	a1, a0, 0
	li.w	a1, 3	#CFCR_8BITS
	st.b	a1, a0, 3

	li.w	a1, 71
	st.b	a1, a0, 2
	jirl	zero, ra, 0
END(initserial)

#define UART_REF_CLK_PLL	(GMAC_FREQ * GMAC_DIV / SB_DIV * 1000000)	//SB PLL
#define UART_DIV_HI_2		(((UART_REF_CLK_PLL + (115200*8)) / (115200*16)) >> 8)
#define UART_DIV_LO_2		(((UART_REF_CLK_PLL + (115200*8)) / (115200*16)) & 0xff)
LEAF(initserial_later)
	li.d	a0, COM1_BASE_ADDR
	li.w	a1, 0x80
	st.b	a1, a0, 3

	li.w	a1, UART_DIV_HI_2
	st.b	a1, a0, 1
	li.w	a1, UART_DIV_LO_2
	st.b	a1, a0, 0
1:
	ld.b	a0, a0, 0
	bne	a1, a0, 1b

	li.d	a0, COM1_BASE_ADDR
	li.w	a1, 3	#CFCR_8BITS
	st.b	a1, a0, 3

	li.w	a1, 71
	st.b	a1, a0, 2
	jirl	zero, ra, 0
END(initserial_later)

/******************************************************
 *used: a0~a2
 ******************************************************/
LEAF(tgt_putchar)
	li.d	a1, COM1_BASE_ADDR
1:
	ld.bu	a2, a1, 0x5
	andi	a2, a2, 0x20
	beqz	a2, 1b

	st.b	a0, a1, 0
	//	or	a2, zero, a1

	jirl	zero, ra, 0
END(tgt_putchar)

/******************************************************
 *used: a0~a4, s0
 ******************************************************/
LEAF(stringserial)
	or	a4, ra, zero
	sub.d	a3, a0, s0
	ld.bu	a0, a3, 0
1:
	beqz	a0, 2f

	bl	tgt_putchar

	addi.d	a3, a3, 1
	ld.bu	a0, a3, 0
	b	1b

2:
	ori	ra, a4, 0
	jirl	zero, ra, 0
END(stringserial)

/*****************************************************
 *used: a0~a5, s0
 *****************************************************/
LEAF(hexserial)
	ori	a4, ra, 0
	ori	a3, a0, 0
	li.d	a5, 8
1:
	rotri.w a0, a3, 28
	or	a3, a0, zero
	andi	a0, a0, 0xf

	la	a1, hexchar
	sub.d	a1, a1, s0

	add.d	a1, a1, a0
	ld.bu	a0, a1, 0

	bl	tgt_putchar

	addi.d	a5, a5, -1
	bnez	a5, 1b

	ori	ra, a4, 0
	jirl	zero, ra, 0
END(hexserial)


/*****************************************************
 *used: a0~a5, s0
 *****************************************************/
LEAF(hexserial64)
	ori	a4, ra, 0
	ori	a3, a0, 0
	li.d	a5, 16
1:
	rotri.d a0, a3, 60
	or	a3, a0, zero
	andi	a0, a0, 0xf

	la	a1, hexchar
	sub.d	a1, a1, s0

	add.d	a1, a1, a0
	ld.bu	a0, a1, 0

	bl	tgt_putchar

	addi.d	a5, a5, -1
	bnez	a5, 1b

	ori	ra, a4, 0
	jirl	zero, ra, 0
END(hexserial64)

	.section .rodata
hexchar:
	.ascii	"0123456789abcdef"
	.text
	.align 5

LEAF(tgt_testchar)
	li.d	a0, COM1_BASE_ADDR
	ld.bu	a1, a0, NSREG(NS16550_LSR)
	andi	a0, a1, LSR_RXRDY
	jirl	zero, ra, 0
END(tgt_testchar)

LEAF(tgt_getchar)
	li.d	a0, COM1_BASE_ADDR
1:
	ld.bu	a1, a0, NSREG(NS16550_LSR)
	andi	a1, a1, LSR_RXRDY
	beqz	a1, 1b
	ld.b	a0, a0, NSREG(NS16550_DATA)
	jirl	zero, ra, 0
END(tgt_getchar)

#endif


        .globl cpu_wait
cpu_wait:
        idle 	0
        jr      ra



        .global cpu_sleep
cpu_sleep:
        SAVE_REGS_ALL(REGS_MEM)
        dbar 0
        li.w    t1, 0x1feb0000
1:
        ld.w    t0, t1, 0x3c
        andi    t0, t0, 0x1
        beqz    t0, 1b
        st.w    t0, t1, 0x3c
        idle 0

       .global wakeup_reset
wakeup_reset:
        //la      a0, msg_wakeup
        //bl      outputstring
        RESTORE_REGS_ALL(REGS_MEM)
        csrwr   t0, CSR_KScratch1
        /*enable interrupt*/
        li.w    t0, 0x4
        csrxchg t0, t0, CSR_CRMD //enter pmu_handler
        csrrd   t0, CSR_KScratch1
        jirl zero, ra, 0
