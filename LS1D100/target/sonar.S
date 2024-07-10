
/********************************************************************
* 文件名:	sonar.S
* 版本：	V1.0
* 作者:		李鑫
* 日期:		2021.11.31
* 说明:		本文件包含超声波时差处理Sonar的所有接口函数及宏定义
* 版权:		龙芯中科（太原）技术有限公司
********************************************************************/
#include "start.h"
#include "ls1d_std_cslreg.h"
#define TDCC(rd,rj,rk) .word (0x3fff<<18|rj<<5|rk<<10|rd<<0|0<<15)
#define SFA(rd,rj,rk)  .word (0x3fff<<18|rj<<5|rk<<10|rd<<0|2<<15)
#define FLTR           .word (0x3fff<<18|0 <<5|0 <<10|0 <<0|4<<15)

#if 0
#define TDCC(rd,rs,rt) .word (0x1c<<26|rs<<21|rt<<16|rd<<11|0<<6|0x27)
#define SFA(rd,rs,rt)  .word (0x1c<<26|rs<<21|rt<<16|rd<<11|2<<6|0x27)
#define FLTR           .word (0x1c<<26|0 <<21|0 <<16|0 <<11|4<<6|0x27)
/******************************时差测量函数********************************/

        .global tdc_calcc
        .ent    tdc_calcc
        //a0: cal1
        //a1: cal2
        //v0: C,    0.0000_0000_00_C[23:0] = 1.0/(cal2-cal1)
tdc_calcc:
        li      t0,  0x50800000 // 2^34 in single-precision floating point format
        mtc1    t0,  $f0
        subu    a0,  a1, a0
        mtc1    a0,  $f2
        cvt.s.w $f4, $f2
        div.s   $f6, $f0, $f4
        cvt.w.s $f8, $f6
        jr      ra
        mfc1    v0, $f8
        .end    tdc_calcc

        .global tdc_c_2_lsb
        .ent    tdc_c_2_lsb
        //a0: C
        //a1: T
tdc_c_2_lsb:
        li      t0,  0x2e800000 // 2^{-34} in single-precision floating point format
        mtc1    t0,  $f0
        mtc1    a0,  $f2
        cvt.s.w $f2, $f2
        mtc1    a1,  $f4
        cvt.s.w $f4, $f4

        mul.s   $f6, $f0, $f2
        mul.s   $f6, $f6, $f4

        cvt.w.s $f8, $f6
        jr      ra
        mfc1    v0, $f8
        .end    tdc_c_2_lsb

        .global tdc_tdcc
        .ent    tdc_tdcc
        //a0: tdcres
        //a1: C
tdc_tdcc:
        jr      ra
        TDCC   (_v0, _a0, _a1)
        .end    tdc_tdcc

        .global tdc_15p17_2_ps
        .ent    tdc_15p17_2_ps
        //a0: res
        //a1: period in ps
        //v0: = a0 * a1 / 2^{17}
tdc_15p17_2_ps:
        li      t0,  0x37000000 // 2^{-17} in single-precision floating point format
        mtc1    t0,  $f0
        mtc1    a0,  $f2
        cvt.s.w $f2, $f2
        mtc1    a1,  $f4
        cvt.s.w $f4, $f4
        mul.s   $f6, $f0, $f2
        mul.s   $f6, $f6, $f4
        cvt.w.s $f8, $f6
        jr      ra
        mfc1    v0, $f8
        .end    tdc_15p17_2_ps


        .global fltr
        .ent    fltr
fltr:
        FLTR
        jr      ra
        .end    fltr

        .global sfa
        .ent    sfa
        // a0:  tof_b
        // a1:  tof_f
        // v0:  sum_flt
sfa:
        move    v0, a2
        SFA     (_v0, _a0, _a1)
        jr      ra
        .end    sfa


/**************************************************************/
    .set    reorder
    .global readw
    .ent    readw
    // a0:  addr
readw:
    lw      v0,  (a0)
    jr      ra
    .end    readw

    /* a0:  cal1_addr */
    /* a1:  cal2_addr */
    /* v0:  C,  [ 0.0000_0000_00_C[23:0] = 1.0/(cal2-cal1) ] */
    .global cal_C
    .ent    cal_C
cal_C:
    li      t0,  0x50800000  	/* 2^34 in single-precision floating point format */
    mtc1    t0,  $f0     		/* f0 = 0x50800000 */
    lw      t1,  (a0)			/* t1 = a0; */
    lw      t2,  (a1)	 		/* t2 = a1; */
    subu    t1,  t2,  t1 		/* t1 = t2 - t1; */
    mtc1    t1,  $f2	 		/* f2 = t1; */
    cvt.s.w $f2, $f2      		/* 转换指令用于浮点寄存器中的数据之间，将整形f2装换成单精度浮点型f2 */
    div.s   $f4, $f0, $f2 		/* f4 = f0 /f2 */
    cvt.w.s $f4, $f4      		/* 将单精度浮点型转换为整形  */
    mfc1    v0,  $f4
    jr      ra
    .end    cal_C



        .global tdc2time
        .ent    tdc2time
        // a0:  res_addr
        // a1:  C
        // v0:  time (15.17)
tdc2time:
        lw      t0, (a0)
        TDCC    (_v0, _t0, _a1)
        jr      ra
        .end    tdc2time

    .global tdc1517_2ps
    .ent    tdc1517_2ps
    // a0:  time (15.17)
    // a1:  period (ps)
    // v0:  ps  [ a0 * a1 / 2^{17} ]
tdc1517_2ps:
    li      t0,  0x37000000  // 2^{-17} in single-precision floating point format
    mtc1    t0,  $f4
    mtc1    a0,  $f0
    mtc1    a1,  $f2
    cvt.s.w $f0, $f0
    cvt.s.w $f2, $f2
    mul.s   $f6, $f0, $f2
    mul.s   $f6, $f6, $f4
    cvt.w.s $f6, $f6
    mfc1    v0,  $f6
    jr      ra
    .end    tdc1517_2ps

//--------------飞行时间差计算-------------------
    .set    at
    .global dtofcalc
    .ent    dtofcalc
    // a0:  hit_num
    // a1:  flt_num
    // v0:  ave_dtof
dtofcalc:
    move    t0,  $0           // i
    move    t1,  $0           // addr_offset
    lw      t2,  TdcCal       // C
    lw      t3,  StsFwd       // start_f
    lw      t4,  StsBwd       // start_b
    TDCC    (_t3, _t3, _t2)
    TDCC    (_t4, _t4, _t2)
    FLTR
1:
    lw      t5,  ResFwd(t1)   // end_f
    lw      t6,  ResBwd(t1)   // end_b
    TDCC    (_t5, _t5, _t2)
    TDCC    (_t6, _t6, _t2)
    subu    t5,  t5,  t3      // tof_f
    subu    t6,  t6,  t4      // tof_b
    SFA     (_t7, _t6, _t5)   // sum_flt
    addu    t0,  t0,  1       // i + 1
    addu    t1,  t1,  4       // addr + 1
    bne     t0,  a0,  1b      // for
    sll     a1,  a1,  1       // flt_num*2
    subu    a0,  a0,  a1
    div     v0,  t7,  a0      // ave_dtof
    //sw      t7,  0x1a00
    //sw      a0,  0x1a04
    //sw      v0,  0x1a08
    jr      ra
    .end    dtofcalc


#endif


/***************************operation addr************************************/
        .global tdc_calcc
tdc_calcc:
        li.w        t0,  0x50800000 // 2^34 in single-precision floating point format
        movgr2fr.w  $f0, t0
        sub.w       a0, a1, a0
        movgr2fr.w  $f2, a0
        ffint.s.w   $f4, $f2
        fdiv.s      $f6, $f0, $f4
        ftint.w.s   $f8, $f6
        movfr2gr.s  v0, $f8
        jr ra

        .global tdc_c_2_lsb
        //a0: C
        //a1: T
tdc_c_2_lsb:
        li.w        t0,  0x2e800000 // 2^{-34} in single-precision floating point format
        movgr2fr.w  $f0, t0
        movgr2fr.w  $f2, a0
        ffint.s.w   $f2, $f2
        movgr2fr.w   $f4, a1
        ffint.s.w   $f4, $f4

        fmul.s      $f6, $f0, $f2
        fmul.s      $f6, $f6, $f4

        ftint.w.s   $f8, $f6
        movfr2gr.s  v0, $f8
        jr      ra


        .global tdc_tdcc
        //a0: tdcres
        //a1: C
tdc_tdcc:
        TDCC   (_v0, _a0, _a1)
        jr      ra

        .global tdc_15p17_2_ps
        //a0: res
        //a1: period in ps
        //v0: = a0 * a1 / 2^{17}
tdc_15p17_2_ps:
        li.w        t0,  0x37000000 // 2^{-17} in single-precision floating point format
        movgr2fr.w  $f0, t0
        movgr2fr.w  $f2, a0
        ffint.s.w   $f2, $f2
        movgr2fr.w  $f4, a1
        ffint.s.w   $f4, $f4
        fmul.s      $f6, $f0, $f2
        fmul.s      $f6, $f6, $f4
        ftint.w.s   $f8, $f6
        movfr2gr.s  v0, $f8
        jr      ra
/***************************operation data************************************/
        .global fltr
fltr:
        FLTR
        jr      ra

        .global sfa
        // a0:  tof_b
        // a1:  tof_f
        // v0:  sum_flt
sfa:
        //move    v0, a2
        SFA     (_v0, _a0, _a1)
        jr      ra


       .global readw
        // a0:  addr
readw:
        ld.w     v0, a0, 0
        jr       ra


    /* a0:  cal1_addr */
    /* a1:  cal2_addr */
    /* v0:  C,  [ 0.0000_0000_00_C[23:0] = 1.0/(cal2-cal1) ] */
        .global cal_C
cal_C:
        li.w        t0,  0x50800000 // 2^34 in single-precision floating point format
        movgr2fr.w  $f0, t0
        ld.w        t1, a0, 0
        ld.w        t2, a1, 0
        sub.w       t1, t2, t1
        movgr2fr.w  $f2, t1
        ffint.s.w   $f4, $f2
        fdiv.s      $f6, $f0, $f4
        ftint.w.s   $f8, $f6
        movfr2gr.s  v0, $f8
        jr ra

        .global tdc2time
        // a0:  res_addr
        // a1:  C
        // v0:  time (15.17)
tdc2time:
        ld.w   t0, a0, 0
        TDCC   (_v0, _t0, _a1)
        jr      ra

        .global tdc1517_2ps
        // a0:  time (15.17)
        // a1:  period (ps)
        // v0:  ps  [ a0 * a1 / 2^{17} ]
tdc1517_2ps:
        li.w        t0,  0x37000000 // 2^{-17} in single-precision floating point format
        movgr2fr.w  $f0, t0
        movgr2fr.w  $f2, a0
        movgr2fr.w  $f4, a1
        ffint.s.w   $f2, $f2
        ffint.s.w   $f4, $f4
        fmul.s      $f6, $f0, $f2
        fmul.s      $f6, $f6, $f4
        ftint.w.s   $f8, $f6
        movfr2gr.s  v0, $f8
        jr      ra

        .global dtofcalc
        // a0:  hit_num
        // a1:  flt_num
        // v0:  ave_dtof
dtofcalc:
        move    t0, zero           // i
        move    t1, zero           // addr_offset
        li.w    t2, TdcCal
        li.w    t3, StsFwd
        li.w    t4, StsBwd
        ld.w    t2, t2, 0      // C
        ld.w    t3, t3, 0       // start_f
        ld.w    t4, t4, 0       // start_b
        TDCC    (_t3, _t3, _t2)
        TDCC    (_t4, _t4, _t2)
        FLTR
1:
        li.w    t5, ResFwd
        li.w    t6, ResBwd
        ld.w    t5, t5, 0   // end_f
        ld.w    t6, t6, 0   // end_b
        TDCC    (_t5, _t5, _t2)
        TDCC    (_t6, _t6, _t2)
        sub.w   t5,  t5,  t3      // tof_f
        sub.w   t6,  t6,  t4      // tof_b
        SFA     (_t7, _t6, _t5)   // sum_flt
        addi.w  t0,  t0,  1       // i + 1
        addi.w  t1,  t1,  4       // addr + 1
        bne     t0,  a0,  1b      // for
        slli.w  a1,  a1,  1       // flt_num*2
        sub.w   a0,  a0,  a1
        div.w     v0,  t7,  a0      // ave_dtof
        jr      ra


#if 0
//-----------------------------------------------
        .global cal_speed
        .ent    cal_speed
        // a0:  cal1_addr  k
        // a1:  cal2_addr  b
        // v0:  C,  [ 0.0000_0000_00_C[23:0] = 1.0/(cal2-cal1) ]
cal_speed:
        mtc1    a0,  $f0
        cvt.s.w $f0, $f0

//		move    t1,a1
        addu    t1,  a1, 0
        mtc1    t1,  $f2

        addu    t2,  a2, 0
        mtc1    t2,  $f4

        mul.s   $f6, $f0,$f2
        add.s   $f6, $f4,$f6
        cvt.w.s $f6, $f6
        mfc1    v0,  $f6
        nop
        jr      ra
        .end    cal_speed
//-----------------------------------------------
//        mtc1    a1,  $f2
//        cvt.w.s $f2, $f2
//        mfc1    v0,  $f2
        .global cal_q
        .ent    cal_q
        // a0:  cal1_addr
        // a1:  cal2_addr
        // v0:  C,  [ 0.0000_0000_00_C[23:0] = 1.0/(cal2-cal1) ]
cal_q:
        mtc1    a0,  $f0
        cvt.s.w $f0, $f0

        addu    t1,  a1, 0
        mtc1    t1,  $f2

        addu    t2,  a2, 0
        mtc1    t2,  $f4

        mul.s   $f6, $f0,$f2
        mul.s   $f6, $f6,$f4
        cvt.w.s $f6, $f6
//        cvt.w.s $f4, $f4
//        mfc1    v0,  $f4
        mfc1    v0,  $f6
        nop
        jr      ra
        .end    cal_q
//-----------------------------------------------
        .global cal_fq
        .ent    cal_fq
cal_fq:
 	li t3 , 10000
 	mtc1    t3,  $f5
 	cvt.s.w $f5,$f5
#	li t1 , 10


	#mtc1    a1,  $f4
	#cvt.s.w $f2,$f2

	div.s	$f0,$f12,$f14

      mul.s   $f0, $f0,$f5

	cvt.w.s $f0,$f0
	mfc1    v0,  $f0
	nop
 	jr      ra
      .end    cal_fq


    .global cal_Ctime
    .ent    cal_Ctime
cal_Ctime:
    lw      t1,  (a0)			/* t1 = a0; */
    lw      t2,  (a1)	 		/* t2 = a1; */
    subu    v0,  t2,  t1 		/* t1 = t2 - t1; */
    jr      ra
    .end    cal_C


#if 0


cal_fq:
 	li t3 , 10000
 	mtc1    t3,  $f5
 	cvt.s.w $f5,$f5
#	li t1 , 10
	mtc1    a0,  $f1  #100.0
	cvt.s.w $f1,$f1

	mtc1    a1,  $f3
	cvt.s.w $f3,$f3
	#mtc1    a1,  $f4
	#cvt.s.w $f2,$f2

	div.s	$f0,$f3,$f1

      mul.s   $f0, $f0,$f5

	cvt.w.s $f0,$f0
	mfc1    v0,  $f0
	nop
 	jr      ra
      .end    cal_fq
#endif


        .global cpu_di
        .ent    cpu_di
cpu_di:
        .set    mips32r2
        di
        .set    mips2
        jr      ra
        nop
        .end    cpu_di

        .global cpu_ei
        .ent    cpu_ei
cpu_ei:
        .set    mips32r2
        ei
        .set    mips2
        jr      ra
        nop
        .end    cpu_ei

        .global cpu_eiwait
        .ent    cpu_eiwait
cpu_eiwait:
        .set    mips32r2
        ei
        wait
        .set    mips2
        jr      ra
        nop
        .end    cpu_eiwait

        .global cpu_diwait
        .ent    cpu_diwait
cpu_diwait:
        .set    mips32r2
        di
        wait
        .set    mips2
        jr      ra
        nop
        .end    cpu_diwait


#endif

