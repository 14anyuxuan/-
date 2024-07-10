
/********************************************************************
* 文件名:  ls1d6_std_cslreg.h
* 版本：	  V1.0
* 作者:    李鑫
* 日期:    2021.10.18
* 说明:    本文件包含寄存器位域的底层驱动库函数声明及宏定义
* 版权:    龙芯中科（太原）技术有限公司
********************************************************************/

#ifndef INCLUDE_LSREG_H_
#define INCLUDE_LSREG_H_

#define CMem_RAM     0x00000000
#define ResFwd       0x10001f80
#define ResBwd       0x10001f00
#define ResPtr       0x10001efc
#define StsFwd       0x10001ee0
#define StsBwd       0x10001ec0
#define TdcCal       0x10001ebc
#define TdcRes       0x10001eb8
#define AdcVal       0x10001edc

/* the "expression" Exported_macro */
/* the "expression" Exported_macro */
#define RESPTR  *(volatile unsigned int*)(ResPtr)
#define TDCCAL  *(volatile unsigned int*)(TdcCal)
#define TDCRES  *(volatile unsigned int*)(TdcRes)

#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))


/* val 在相应的PER_REG_FIELD寄存器位域赋值 */
#define LS_RMK(PER_REG_FIELD, val)                                         \
    (((val) << PER_REG_FIELD##_SHIFT) & PER_REG_FIELD##_MASK)

/*取寄存器reg的PER_REG_FIELD位域的值 */
#define LS_REXT(reg, PER_REG_FIELD)                                        \
    (((reg) & PER_REG_FIELD##_MASK) >> PER_REG_FIELD##_SHIFT)

/*给reg 寄存器的 PER_REG_FIELD位域 插入相应的值val */
#define LS_RINS(reg, PER_REG_FIELD, val)                                   \
    ((reg) = ((reg) & ~PER_REG_FIELD##_MASK) | LS_RMK(PER_REG_FIELD, val))

//#define LS_WREG(VAR,BASE,OFFSET)						\
//	    __asm__ __volatile__("sw %0, %1($0)"::"r" (VAR), "I"(BASE+OFFSET))

#define LS_WREG(VAR,BASE,OFFSET)	*(volatile uint32_t*)(BASE+OFFSET) = VAR

#define LS_RREG(VAR,BASE,OFFSET) VAR = *(volatile uint32_t*)(BASE+OFFSET)

//#define LS_RREG(VAR,BASE,OFFSET)						\
//	    __asm__ __volatile__("lw %0, %1($0)":"=r" (VAR):"I"(BASE+OFFSET))








#if 0
/* the Field MaKe (Token) macro */
/*给reg 寄存器的 PER_REG_FIELD位域 插入相应的值val */
#define LS_FMKT(PER_REG_FIELD, TOKEN)                                      \
    LS_FMK(PER_REG_FIELD, LS_##PER_REG_FIELD##_##TOKEN)

/* the Field INSert (Token) macro */
#define LS_FINST(reg, PER_REG_FIELD, TOKEN)                                \
    LS_FINS((reg), PER_REG_FIELD, LS_##PER_REG_FIELD##_##TOKEN)
#endif
/* the "raw" macros */

/* the Field MaKe (Raw) macro */
#define LS_FMKR(msb, lsb, val)                                             \
    (((val) & ((1 << ((msb) - (lsb) + 1)) - 1)) << (lsb))

/* the Field EXTract (Raw) macro */
#define LS_FEXTR(reg, msb, lsb)                                            \
    (((reg) >> (lsb)) & ((1 << ((msb) - (lsb) + 1)) - 1))

/* the Field INSert (Raw) macro */
#define LS_FINSR(reg, msb, lsb, val)                                       \
    ((reg) = ((reg) &~ (((1 << ((msb) - (lsb) + 1)) - 1) << (lsb)))         \
    | LS_FMKR(msb, lsb, val))



#endif /* INCLUDE_LSREG_H_ */
