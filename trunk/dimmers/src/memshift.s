;/**************************** (C) COPYRIGHT 2009 *******************************
;* File Name          : mem_shift.s
;* Author             : RS / GVO
;* Version            : V1.0
;* Date               : 04/2009
;* Description        : Shift buffer with 1 halfword to the right
;********************************************************************************/

.cpu cortex-m3
.fpu softvfp   
.syntax unified
.thumb
.text	
.global  mem_shift
.thumb_func

;/******************************************************************************
;* Function Name  : mem_shift
;* Description    : mem shift one half word to the right
;* Input          : - R0 buffer address to shift
;*                  - R1 buffer size in bytes
;* Output         : modified buffer content
;* Return         : None
;* Conditions	  : 2 * ( N - 1) must be a multiple of 4 
;*					with N the amount of buffer bytes
;*
;* Info			  : takes about 5,5 µs ( ca 50% faster than memmove )
;*
;* C interface	  : void mem_shift(void * buffer , u32 size) 
;*******************************************************************************/

mem_shift:
		STMDB   sp!, {r4-r11, lr}   /* save context */
        ADD		r1,r1,r0			/* r1 end of the buffer */
		SUB		r1,r1,#4            /* r1 points to second last halfword */
        ADD		r2,r1,#2            /* r2 points to last halfword */
shift1:
		ldr.w	r3,[r1],#-2				/* copy from second last to last word */
        str.W	r3,[r2],#-2
        CMP		r0,r2               /* dest = origin ? */
        BNE		shift1              /* if not cont moving */
		LDMIA   sp!, {r4-r11, pc}	/* recall context */
.end
		