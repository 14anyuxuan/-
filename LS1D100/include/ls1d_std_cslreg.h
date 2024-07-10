
/********************************************************************
* �ļ���:  ls1d6_std_cslreg.h
* �汾��	  V1.0
* ����:    ����
* ����:    2021.10.18
* ˵��:    ���ļ������Ĵ���λ��ĵײ������⺯���������궨��
* ��Ȩ:    ��о�пƣ�̫ԭ���������޹�˾
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


/* val ����Ӧ��PER_REG_FIELD�Ĵ���λ��ֵ */
#define LS_RMK(PER_REG_FIELD, val)                                         \
    (((val) << PER_REG_FIELD##_SHIFT) & PER_REG_FIELD##_MASK)

/*ȡ�Ĵ���reg��PER_REG_FIELDλ���ֵ */
#define LS_REXT(reg, PER_REG_FIELD)                                        \
    (((reg) & PER_REG_FIELD##_MASK) >> PER_REG_FIELD##_SHIFT)

/*��reg �Ĵ����� PER_REG_FIELDλ�� ������Ӧ��ֵval */
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
/*��reg �Ĵ����� PER_REG_FIELDλ�� ������Ӧ��ֵval */
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
