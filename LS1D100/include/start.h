/********************************************************************
* 文件名:  start.h
* 版本： V1.0
* 作者:    李鑫
* 日期:    2021.09.30
* 说明:    本文件包含启动文件start涉及的宏定义
* 版权:    龙芯中科（太原）技术有限公司
********************************************************************/
#ifndef START_H_
#define START_H_

#define REGS_MEM          (0x10000ffc)
#define SP_BASE           (REGS_MEM-132)
#define CACHE_OP          (0xfffffff1)
#define ADDR_MAP          (0x76043210)
#define INT_VECTOR        (0x8bf)
#define INTC_VECTOR       (0x40)

/*
 * Symbolic register names for 32 bit ABI, General Register
 */
#define zero	$r0	/* wired zero */
#define ra	$r1	/* return address */
#define gp	$r2	/* global pointer - caller saved for PIC */
#define sp	$r3	/* stack pointer */
#define v0	$r4	/* return value - caller saved */
#define v1	$r5
#define a0	$r4	/* argument registers */
#define a1	$r5
#define a2	$r6
#define a3	$r7
#define a4	$r8
#define a5	$r9
#define a6	$r10
#define a7	$r11
#define t0	$r12	/* caller saved */
#define t1	$r13
#define t2	$r14
#define t3	$r15
#define t4	$r16
#define t5	$r17
#define t6	$r18
#define t7	$r19
#define t8	$r20
#define tp	$r21
#define fp	$r22	/* frame pointer */
#define s0	$r23	/* callee saved */
#define s1	$r24
#define s2	$r25
#define s3	$r26
#define s4	$r27
#define s5	$r28
#define s6	$r29
#define s7	$r30
#define s8	$r31

#define _zero	0	/* wired zero */
#define _ra     1	/* return address */
#define _gp     2	/* global pointer - caller saved for PIC */
#define _sp     3	/* stack pointer */
#define _v0     4	/* return value - caller saved */
#define _v1     5
#define _a0     4	/* argument registers */
#define _a1     5
#define _a2     6
#define _a3     7
#define _a4     8
#define _a5     9
#define _a6     10
#define _a7     11
#define _t0     12	/* caller saved */
#define _t1     13
#define _t2     14
#define _t3     15
#define _t4     16
#define _t5     17
#define _t6     18
#define _t7     19
#define _t8     20
#define _tp     21
#define _fp     22	/* frame pointer */
#define _s0     23	/* callee saved */
#define _s1     24
#define _s2     25
#define _s3     26
#define _s4     27
#define _s5     28
#define _s6     29
#define _s7     30
#define _s8     31


//状态寄存器
#define CSR_CRMD          0x0
#define CSR_PRMD          0x1
#define CSR_CU            0x2
#define CSR_Config        0x3
#define CSR_ExConfig      0x4
#define CSR_ExStatus      0x5
#define CSR_EPC           0x6
#define CSR_BadVAddr      0x7
#define CSR_EBase         0xc
#define CSR_ASID          0x18
#define CSR_CPUN          0x20
#define CSR_Config1       0x21
#define CSR_KScratch0     0x30
#define CSR_KScratch1     0x31
#define CSR_TimerID       0x40
#define CSR_TimerConfig   0x41
#define CSR_TimerTicks    0x42
#define CSR_TimerOffset   0x43
#define CSR_TimerClear    0x44
#define CSR_LLBit         0x60
#define CSR_GSConfig      0x80
#define CSR_ERRCTL        0x90
#define CSR_ERRINFO       0x91
#define CSR_ERRINFO1      0x92
#define CSR_ERRBase       0x93
#define CSR_ERREPC        0x94
#define CSR_CCSF          0x96  //only-132e
#define CSR_TAGLO         0x98
#define CSR_USERDEF       0xaf  //only-132e
#define CSR_ELUSION       0xff  //only-132e
#define CSR_MPU0_BASE     0x180 //only-132e
#define CSR_MPU0_MASK     0x181
#define CSR_MPU1_BASE     0x184
#define CSR_MPU1_MASK     0x185
#define CSR_MPU2_BASE     0x188
#define CSR_MPU2_MASK     0x189
#define CSR_MPU3_BASE     0x18c
#define CSR_MPU3_MASK     0x18d
#define CSR_SEGPA         0x190
#define CSR_SEGCA         0x191
#define CSR_DBConfig      0x300
#define CSR_DBState       0x301
#define CSR_DBA           0x310
#define CSR_DBM           0x311
#define CSR_DBC           0x312
#define CSR_DBT           0x313
#define CSR_IBConfig      0x380
#define CSR_IBState       0x381
#define CSR_IBA           0x390
#define CSR_IBM           0x391
#define CSR_IBC           0x392
#define CSR_IBT           0x393
#define CSR_DEBUG         0x500
#define CSR_DESAVE        0x501
#define CSR_DEPC          0x502
#define CSR_DEBUG2        0x508 //only-132e


//S_* menas shift
//W_* menas width
//M_* menas mask

//0x0 CSR_CRMD
#define S_CSR_CRMD_PLV      0
#define W_CSR_CRMD_PLV      2
#define M_CSR_CRMD_PLV      (((1<<W_CSR_CRMD_PLV)-1)<<S_CSR_CRMD_PLV)
#define S_CSR_CRMD_IE       2
#define W_CSR_CRMD_IE       1
#define M_CSR_CRMD_IE       (((1<<W_CSR_CRMD_IE)-1)<<S_CSR_CRMD_IE)
#define S_CSR_CRMD_DA       3
#define W_CSR_CRMD_DA       1
#define M_CSR_CRMD_DA       (((1<<W_CSR_CRMD_DA)-1)<<S_CSR_CRMD_DA)
#define S_CSR_CRMD_PG       4
#define W_CSR_CRMD_PG       1
#define M_CSR_CRMD_PG       (((1<<W_CSR_CRMD_PG)-1)<<S_CSR_CRMD_PG)
#define S_CSR_CRMD_DACF     5
#define W_CSR_CRMD_DACF     2
#define M_CSR_CRMD_DACF     (((1<<W_CSR_CRMD_DACF)-1)<<S_CSR_CRMD_DACF)
#define S_CSR_CRMD_DACM     7
#define W_CSR_CRMD_DACM     2
#define M_CSR_CRMD_DACM     (((1<<W_CSR_CRMD_DACM)-1)<<S_CSR_CRMD_DACM)
#define S_CSR_CRMD_WE       9
#define W_CSR_CRMD_WE       1
#define M_CSR_CRMD_WE       (((1<<W_CSR_CRMD_WE)-1)<<S_CSR_CRMD_WE)

//0x1 CSR_PRMD
#define S_CSR_PRMD_PPLV     0
#define W_CSR_PRMD_PPLV     2
#define M_CSR_PRMD_PPLV     (((1<<W_CSR_PRMD_PPLV)-1)<<S_CSR_PRMD_PPLV)
#define S_CSR_PRMD_PIE      2
#define M_CSR_PRMD_PIE      0x4
#define S_CSR_PRMD_PWE      3
#define M_CSR_PRMD_PWE      0x8

//0x2
#define S_CSR_CU_FPen      0
#define S_CSR_CU_LSXen     1
#define S_CSR_CU_LASXen    2
#define S_CSR_CU_LBTen     3

//0x3
#define S_CSR_Config_DisRDT1	5
#define S_CSR_Config_DisRDT2	6
#define S_CSR_Config_DisRDT3	7
#define S_CSR_Config_ALC0  12
#define S_CSR_Config_ALC1  13
#define S_CSR_Config_ALC2  14
#define S_CSR_Config_ALC3  15
#define W_CSR_Config_ALC0  1
#define W_CSR_Config_ALC1  1
#define W_CSR_Config_ALC2  1
#define W_CSR_Config_ALC3  1
#define M_CSR_Config_Short 0xf
#define M_CSR_Config_ALC0     (((1<<W_CSR_Config_ALC0)-1)<<S_CSR_Config_ALC0)
#define M_CSR_Config_ALC1     (((1<<W_CSR_Config_ALC1)-1)<<S_CSR_Config_ALC1)
#define M_CSR_Config_ALC2     (((1<<W_CSR_Config_ALC2)-1)<<S_CSR_Config_ALC2)
#define M_CSR_Config_ALC3     (((1<<W_CSR_Config_ALC3)-1)<<S_CSR_Config_ALC3)
#define S_CSR_Config_NWP0  16
#define S_CSR_Config_NWP1  17
#define S_CSR_Config_NWP2  18

//0x4
#define S_CSR_ExConfig_IM   0
#define M_CSR_ExConfig_IM   0x1fff
#define S_CSR_ExConfig_IM0  0
#define S_CSR_ExConfig_IM1  1
#define S_CSR_ExConfig_IM2  2
#define S_CSR_ExConfig_IM3  3
#define S_CSR_ExConfig_IM4  4
#define S_CSR_ExConfig_IM5  5
#define S_CSR_ExConfig_IM6  6
#define S_CSR_ExConfig_IM7  7
#define S_CSR_ExConfig_IM8  8
#define S_CSR_ExConfig_IM9  9
#define S_CSR_ExConfig_IM10 10
#define S_CSR_ExConfig_IM11 11
#define S_CSR_ExConfig_IM13 13
#define S_CSR_ExConfig_IM12 12
#define S_CSR_ExConfig_IM_SW0 0
#define S_CSR_ExConfig_IM_SW1 1
#define S_CSR_ExConfig_IM_HW0 2
#define S_CSR_ExConfig_IM_HW1 3
#define S_CSR_ExConfig_IM_HW2 4
#define S_CSR_ExConfig_IM_HW3 5
#define S_CSR_ExConfig_IM_HW4 6
#define S_CSR_ExConfig_IM_HW5 7
#define S_CSR_ExConfig_IM_HW6 8
#define S_CSR_ExConfig_IM_HW7 9
#define S_CSR_ExConfig_IM_PCOV 10
#define S_CSR_ExConfig_IM_TI   11
#define S_CSR_ExConfig_IM_IPI  12
#define S_CSR_ExConfig_IM_NMI  13

#define S_CSR_ExConfig_VS   16
#define W_CSR_ExConfig_VS   3
#define M_CSR_ExConfig_VS   (((1<<W_CSR_ExConfig_VS)-1)<<S_CSR_ExConfig_VS)

//0x5 CSR_ExStatus
#define S_CSR_ExStatus_IS       0
#define W_CSR_ExStatus_IS       15
#define S_CSR_ExStatus_IS0      0
#define S_CSR_ExStatus_IS1      1
#define S_CSR_ExStatus_IS2      2
#define S_CSR_ExStatus_IS3      3
#define S_CSR_ExStatus_IS4      4
#define S_CSR_ExStatus_IS5      5
#define S_CSR_ExStatus_IS6      6
#define S_CSR_ExStatus_IS7      7
#define S_CSR_ExStatus_IS8      8
#define S_CSR_ExStatus_IS9      9
#define S_CSR_ExStatus_IS10     10
#define S_CSR_ExStatus_IS11     11
#define S_CSR_ExStatus_IS12     12
#define S_CSR_ExStatus_IS13     13
#define S_CSR_ExStatus_SW0      0
#define S_CSR_ExStatus_SW1      1
#define S_CSR_ExStatus_HW0      2
#define S_CSR_ExStatus_HW1      3
#define S_CSR_ExStatus_HW2      4
#define S_CSR_ExStatus_HW3      5
#define S_CSR_ExStatus_HW4      6
#define S_CSR_ExStatus_HW5      7
#define S_CSR_ExStatus_HW6      8
#define S_CSR_ExStatus_HW7      9
#define S_CSR_ExStatus_PCOV     10
#define S_CSR_ExStatus_TI       11
#define S_CSR_ExStatus_IPI      12
#define S_CSR_ExStatus_NMI      13

#define S_CSR_ExStatus_Ecode    16
#define W_CSR_ExStatus_Ecode    6
#define S_CSR_ExStatus_EsubCode 22
#define W_CSR_ExStatus_EsubCode 9

//0x10 CSR_TLBIDX
#define S_CSR_TLBIDX_INDEX  0
#define W_CSR_TLBIDX_INDEX  12
#define M_CSR_TLBIDX_INDEX  (((1<<W_CSR_TLBIDX_INDEX)-1)<<S_CSR_TLBIDX_INDEX)
#define S_CSR_TLBIDX_PS     24
#define W_CSR_TLBIDX_PS     6
#define M_CSR_TLBIDX_PS     (((1<<W_CSR_TLBIDX_PS)-1)<<S_CSR_TLBIDX_PS)
#define S_CSR_TLBIDX_V      31
#define W_CSR_TLBIDX_V      1
#define M_CSR_TLBIDX_V      (((1<<W_CSR_TLBIDX_V)-1)<<S_CSR_TLBIDX_V)

//0x11 CSR_TLBEHI
#define S_CSR_TLBEHI_VPN2   13
#define W_CSR_TLBEHI_VPN2   35
#define M_CSR_TLBEHI_VPN2   (((1<<W_CSR_TLBEHI_VPN2)-1)<<S_CSR_TLBEHI_VPN2)

//0x15 CSR_GuestTLB
#define S_CSR_GuestTLB_GVTLB    0
#define W_CSR_GuestTLB_GVTLB    6
#define M_CSR_GuestTLB_GVTLB    (((1<<W_CSR_GuestTLB_GVTLB)-1)<<S_CSR_GuestTLB_GVTLB)
#define S_CSR_GuestTLB_use_rid  12
#define W_CSR_GuestTLB_use_rid  1
#define M_CSR_GuestTLB_use_rid  (((1<<W_CSR_GuestTLB_use_rid)-1)<<S_CSR_GuestTLB_use_rid)
#define S_CSR_GuestTLB_RID      16
#define W_CSR_GuestTLB_RID      8
#define M_CSR_GuestTLB_RID      (((1<<W_CSR_GuestTLB_RID)-1)<<S_CSR_GuestTLB_RID)

//0x16 CSR_GTLBR
#define S_CSR_GTLBR_is_GTLB     0
#define W_CSR_GTLBR_is_GTLB     1
#define M_CSR_GTLBR_is_GTLB     (((1<<W_CSR_GTLBR_is_GTLB)-1)<<S_CSR_GTLBR_is_GTLB)
#define S_CSR_GTLBR_TLBR_RID    16
#define W_CSR_GTLBR_TLBR_RID    8
#define M_CSR_GTLBR_TLBR_RID    (((1<<W_CSR_GTLBR_TLBR_RID)-1)<<S_CSR_GTLBR_TLBR_RID)

//0x18 CSR_ASID
#define S_CSR_ASID_ASID     0
#define W_CSR_ASID_ASID     10
#define M_CSR_ASID_ASID     (((1<<W_CSR_ASID_ASID)-1)<<S_CSR_ASID_ASID)

//0x41 CSR_TimerConfig
#define S_CSR_TimerConfig_En 		0
#define S_CSR_TimerConfig_Period 	1

//0x50 CSR_GuestInfo
#define S_CSR_GuestInfo_PVM     1
#define W_CSR_GuestInfo_PVM     1
#define M_CSR_GuestInfo_PVM     (((1<<W_CSR_GuestInfo_PVM)-1)<<S_CSR_GuestInfo_PVM)
#define S_CSR_GuestInfo_GID     16
#define W_CSR_GuestInfo_GID     8
#define M_CSR_GuestInfo_GID     (((1<<W_CSR_GuestInfo_GID)-1)<<S_CSR_GuestInfo_GID)

//0x51 CSR_GuestConfig
#define S_CSR_GuestConfig_GPERFNum 24
#define M_CSR_GuestConfig_GPERFNum 0x7000000

//0x60
#define S_CSR_LLBit_ROLLB  0
#define S_CSR_LLBit_WCLLB  1
#define S_CSR_LLBit_KLO    2

//0x80 CSR_GSConfig
#define S_CSR_GSConfig_Stfill   8
#define W_CSR_GSConfig_Stfill   1
#define M_CSR_GSConfig_Stfill   (((1<<W_CSR_GSConfig_Stfill)-1)<<S_CSR_GSConfig_Stfill)

//0x81 CSR_Flush
#define M_CSR_Flush_VTLB    0x1
#define M_CSR_Flush_FTLB    0x2
#define M_CSR_Flush_DTLB    0x4
#define M_CSR_Flush_ITLB    0x8
#define M_CSR_Flush_BTAC    0x10

//0x8a
#define S_CSR_RFEPC_IsTLBR  0
#define M_CSR_REEPC_EPC     0xfffffffffffffffc

//0x8f
#define S_CSR_RFState_PPLV 0
#define S_CSR_RFState_PIE  2
#define S_CSR_RFState_PVM  3
#define S_CSR_RFState_PWE  4
#define M_CSR_RFState_PPLV 0x3
#define M_CSR_RFState_PIE  0x4
#define M_CSR_RFState_PVM  0x8
#define M_CSR_RFState_PWE  0x10

//0x90
#define S_CSR_ERRCTL_ERRMode 0
#define S_CSR_ERRCTL_PPLV    2
#define S_CSR_ERRCTL_PIE     4
#define S_CSR_ERRCTL_PVM     5
#define S_CSR_ERRCTL_PWE     6
#define S_CSR_ERRCTL_PDA     7
#define S_CSR_ERRCTL_PPG     8
#define S_CSR_ERRCTL_PDACF   9
#define S_CSR_ERRCTL_PDACM   11
#define M_CSR_ERRCTL_PPLV    0xc
#define M_CSR_ERRCTL_PIE     0x10
#define M_CSR_ERRCTL_PVM     0x20
#define M_CSR_ERRCTL_PWE     0x40
#define M_CSR_ERRCTL_PDA     0x80
#define M_CSR_ERRCTL_PPG     0x100
#define M_CSR_ERRCTL_PDACF   0x600
#define M_CSR_ERRCTL_PDACM   0x1800

//0xaf userdef
#define S_CSR_USERDEF_DC     4

//0x200 CSR_PCCtl
#define S_CSR_PCCtl_EVENT 0
#define M_CSR_PCCtl_EVENT 0x3ff
#define S_CSR_PCCtl_PLV   16
#define M_CSR_PCCtl_PLV   0xf0000
#define S_CSR_PCCtl_GREN  21
#define M_CSR_PCCtl_GREN  0x600000



#define SAVE_REGS_ALL(BASE) \
	    csrwr   tp, CSR_KScratch1; \
        li.w    tp, BASE;\
        st.w    t0, tp, -0x4 ;\
        st.w    t1, tp, -0x8 ;\
        st.w    t2, tp, -0xc ;\
        st.w    t3, tp, -0x10;\
        st.w    t4, tp, -0x14;\
        st.w    t5, tp, -0x18;\
        st.w    t6, tp, -0x1c;\
        st.w    t7, tp, -0x20;\
        st.w    t8, tp, -0x24;\
        st.w    s0, tp, -0x28;\
        st.w    s1, tp, -0x2c;\
        st.w    s2, tp, -0x30;\
        st.w    s3, tp, -0x34;\
        st.w    s4, tp, -0x38;\
        st.w    s5, tp, -0x3c;\
        st.w    s6, tp, -0x40;\
        st.w    s7, tp, -0x44;\
        st.w    s8, tp, -0x48;\
        st.w    a0, tp, -0x4c;\
        st.w    a1, tp, -0x50;\
        st.w    a2, tp, -0x54;\
        st.w    a3, tp, -0x58;\
        st.w    a4, tp, -0x5c;\
        st.w    a5, tp, -0x60;\
        st.w    a6, tp, -0x64;\
        st.w    a7, tp, -0x68;\
        st.w    ra, tp, -0x6c;\
        st.w    sp, tp, -0x70;\
        st.w    gp, tp, -0x74;\
        st.w    fp, tp, -0x78;\
        addi.w  t0, tp, 0    ;\
        csrrd   tp, CSR_KScratch1; \
        st.w    tp, t0, -0x7c;


#define RESTORE_REGS_ALL(BASE) \
        li.w    tp, BASE;\
        ld.w    t0, tp, -0x4 ;\
        ld.w    t1, tp, -0x8 ;\
        ld.w    t2, tp, -0xc ;\
        ld.w    t3, tp, -0x10;\
        ld.w    t4, tp, -0x14;\
        ld.w    t5, tp, -0x18;\
        ld.w    t6, tp, -0x1c;\
        ld.w    t7, tp, -0x20;\
        ld.w    t8, tp, -0x24;\
        ld.w    s0, tp, -0x28;\
        ld.w    s1, tp, -0x2c;\
        ld.w    s2, tp, -0x30;\
        ld.w    s3, tp, -0x34;\
        ld.w    s4, tp, -0x38;\
        ld.w    s5, tp, -0x3c;\
        ld.w    s6, tp, -0x40;\
        ld.w    s7, tp, -0x44;\
        ld.w    s8, tp, -0x48;\
        ld.w    a0, tp, -0x4c;\
        ld.w    a1, tp, -0x50;\
        ld.w    a2, tp, -0x54;\
        ld.w    a3, tp, -0x58;\
        ld.w    a4, tp, -0x5c;\
        ld.w    a5, tp, -0x60;\
        ld.w    a6, tp, -0x64;\
        ld.w    a7, tp, -0x68;\
        ld.w    ra, tp, -0x6c;\
        ld.w    sp, tp, -0x70;\
        ld.w    gp, tp, -0x74;\
        ld.w    fp, tp, -0x78;\
	    ld.w    tp, tp, -0x7c;

//in future, SAVE/RESTORE_REGS_FAST can no care s0~s8
#define SAVE_REGS_FAST(BASE) \
	    csrwr   tp, CSR_KScratch1; \
        li.w    tp, BASE;\
        st.w    t0, tp, -0x4 ;\
        st.w    t1, tp, -0x8 ;\
        st.w    t2, tp, -0xc ;\
        st.w    t3, tp, -0x10;\
        st.w    t4, tp, -0x14;\
        st.w    t5, tp, -0x18;\
        st.w    t6, tp, -0x1c;\
        st.w    t7, tp, -0x20;\
        st.w    t8, tp, -0x24;\
        /*st.w    s0, tp, -0x28;*/\
        /*st.w    s1, tp, -0x2c;*/\
        /*st.w    s2, tp, -0x30;*/\
        /*st.w    s3, tp, -0x34;*/\
        /*st.w    s4, tp, -0x38;*/\
        /*st.w    s5, tp, -0x3c;*/\
        /*st.w    s6, tp, -0x40;*/\
        /*st.w    s7, tp, -0x44;*/\
        /*st.w    s8, tp, -0x48;*/\
        st.w    a0, tp, -0x4c;\
        st.w    a1, tp, -0x50;\
        st.w    a2, tp, -0x54;\
        st.w    a3, tp, -0x58;\
        st.w    a4, tp, -0x5c;\
        st.w    a5, tp, -0x60;\
        st.w    a6, tp, -0x64;\
        st.w    a7, tp, -0x68;\
        st.w    ra, tp, -0x6c;\
        st.w    sp, tp, -0x70;\
        /*st.w    gp, tp, -0x74;*/\
        /*st.w    fp, tp, -0x78;*/\


#define RESTORE_REGS_FAST(BASE) \
        li.w    tp, BASE;\
        ld.w    t0, tp, -0x4 ;\
        ld.w    t1, tp, -0x8 ;\
        ld.w    t2, tp, -0xc ;\
        ld.w    t3, tp, -0x10;\
        ld.w    t4, tp, -0x14;\
        ld.w    t5, tp, -0x18;\
        ld.w    t6, tp, -0x1c;\
        ld.w    t7, tp, -0x20;\
        ld.w    t8, tp, -0x24;\
        /*ld.w    s0, tp, -0x28;*/\
        /*ld.w    s1, tp, -0x2c;*/\
        /*ld.w    s2, tp, -0x30;*/\
        /*ld.w    s3, tp, -0x34;*/\
        /*ld.w    s4, tp, -0x38;*/\
        /*ld.w    s5, tp, -0x3c;*/\
        /*ld.w    s6, tp, -0x40;*/\
        /*ld.w    s7, tp, -0x44;*/\
        /*ld.w    s8, tp, -0x48;*/\
        ld.w    a0, tp, -0x4c;\
        ld.w    a1, tp, -0x50;\
        ld.w    a2, tp, -0x54;\
        ld.w    a3, tp, -0x58;\
        ld.w    a4, tp, -0x5c;\
        ld.w    a5, tp, -0x60;\
        ld.w    a6, tp, -0x64;\
        ld.w    a7, tp, -0x68;\
        ld.w    ra, tp, -0x6c;\
        ld.w    sp, tp, -0x70;\
        /*ld.w    gp, tp, -0x74;*/\
        /*ld.w    fp, tp, -0x78;*/\
	    csrrd   tp, CSR_KScratch1;

/****************************************************************************/
#endif

