/****************************************************************************
 * arch/arm/src/armv7-r/arm_vectors.S
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/irq.h>

#include "arm.h"
#include "cp15.h"

	.file	"arm_vectors.S"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Private Data
 ****************************************************************************/

/****************************************************************************
 * Assembly Macros
 ****************************************************************************/

/****************************************************************************
 * Private Functions
 ****************************************************************************/

	.text

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: arm_vectorirq
 *
 * Description:
 *   Interrupt exception. Entered in IRQ mode with spsr = SVC CPSR, lr = SVC PC
 *
 ****************************************************************************/

	.globl	arm_decodeirq
	.globl	arm_vectorirq
	.type	arm_vectorirq, %function

arm_vectorirq:
	/* On entry, we are in IRQ mode.  We are free to use the IRQ mode r13
	 * and r14.
	 */

#ifdef CONFIG_ARMV7A_DECODEFIQ
	mov		r13, #(PSR_MODE_SYS | PSR_I_BIT | PSR_F_BIT)
#else
	mov		r13, #(PSR_MODE_SYS | PSR_I_BIT)
#endif
	msr		cpsr_c, r13			/* Switch to SYS mode */

	/* Create a context structure.  First set aside a stack frame
	 * and store r0-r12 into the frame.
	 */

	sub		sp, sp, #XCPTCONTEXT_SIZE
	stmia		sp, {r0-r12}			/* Save the SYS mode regs */

#ifdef CONFIG_ARMV7A_DECODEFIQ
	mov		r0, #(PSR_MODE_IRQ | PSR_I_BIT | PSR_F_BIT)
#else
	mov		r0, #(PSR_MODE_IRQ | PSR_I_BIT)
#endif
	msr		cpsr_c, r0			/* Switch back IRQ mode */

	/* Get the values for r15(pc) and CPSR in r3 and r4 */

	sub		r3, lr, #4
	mrs		r4, spsr

	/* Then switch back to SYS mode */

#ifdef CONFIG_ARMV7A_DECODEFIQ
	orr		r0, r0, #(PSR_MODE_SYS | PSR_I_BIT | PSR_F_BIT)
#else
	orr		r0, r0, #(PSR_MODE_SYS | PSR_I_BIT)
#endif
	msr		cpsr_c, r0

	/* Get the correct values of USR/SYS r13(sp) and r14(lr) in r1 and r2 */

	add		r1, sp, #XCPTCONTEXT_SIZE
	mov		r2, r14

	/* Save r13(sp), r14(lr), r15(pc), and the CPSR */

	add		r0, sp, #(4*REG_SP)		/* Offset to pc, cpsr storage */
	stmia		r0, {r1-r4}

	/* Then call the IRQ handler with interrupts disabled. */

	mov		fp, #0				/* Init frame pointer */
	mov		r0, sp				/* Get r0=xcp */

#if CONFIG_ARCH_INTERRUPTSTACK > 7
	/* Call arm_decodeirq() on the interrupt stack */

	ldr		sp, .Lirqstacktop		/* SP = interrupt stack top */
	str		r0, [sp, #-4]!			/* Save the xcp address at SP-4 then update SP */
	mov		r4, sp				/* Save the SP in a preserved register */
	bic		sp, sp, #7			/* Force 8-byte alignment */
	bl		arm_decodeirq			/* Call the handler */
	ldr		sp, [r4]			/* Restore the user stack pointer */
#else
	/* Call arm_decodeirq() on the user stack */

	mov		r4, sp				/* Save the SP in a preserved register */
	bic		sp, sp, #7			/* Force 8-byte alignment */
	bl		arm_decodeirq			/* Call the handler */
	mov		sp, r4				/* Restore the possibly unaligned stack pointer */
#endif

	/* Switch back IRQ mode and return with shadow SPSR */

#ifdef CONFIG_ARMV7A_DECODEFIQ
	mov		r4, #(PSR_MODE_IRQ | PSR_I_BIT | PSR_F_BIT)
#else
	mov		r4, #(PSR_MODE_IRQ | PSR_I_BIT)
#endif
	msr		cpsr_c, r4			/* Switch back IRQ mode */

	/* Upon return from arm_decodeirq, r0 holds the pointer to the register
	 * state save area to use to restore the registers.  This may or may not
	 * be the same value that was passed to arm_decodeirq:  It will differ if a
	 * context switch is required.
	 */

	/* Restore the CPSR, IRQ mode registers and return */

	ldr		r1, [r0, #(4*REG_CPSR)]		/* Fetch the return SPSR */
	msr		spsr_cxsf, r1			/* Set the return mode SPSR */

	/* Life is simple when everything is IRQ mode */

	mov		r14, r0				/* (IRQ) r14=Register storage area */
	ldmia		r14!, {r0-r12}			/* Restore common r0-r12 */
	ldmia		r14, {r13, r14}^		/* Restore user mode r13/r14 */
	add		r14, r14, #(4*2)		/* (IRQ) r14=address of r15 storage */
	ldmia		r14, {r15}^			/* Return */

#if CONFIG_ARCH_INTERRUPTSTACK > 7
.Lirqstacktop:
	.word	g_intstacktop
#endif
	.size	arm_vectorirq, . - arm_vectorirq

	.align	5

/****************************************************************************
 * Function: arm_vectorsvc
 *
 * Description:
 *   SVC interrupt. We enter the SVC in SYS mode.
 *
 ****************************************************************************/

	.globl	arm_syscall
	.globl	arm_vectorsvc
	.type	arm_vectorsvc, %function

arm_vectorsvc:

#ifdef CONFIG_ARMV7A_DECODEFIQ
	mov		r13, #(PSR_MODE_SYS | PSR_I_BIT | PSR_F_BIT)
#else
	mov		r13, #(PSR_MODE_SYS | PSR_I_BIT)
#endif
	msr		cpsr_c, r13			/* Switch to SYS mode */

	/* Create a context structure.  First set aside a stack frame
	 * and store r0-r12 into the frame.
	 */

	sub		sp, sp, #XCPTCONTEXT_SIZE
	stmia		sp, {r0-r12}			/* Save the SYS mode regs */

#ifdef CONFIG_ARMV7A_DECODEFIQ
	mov		r0, #(PSR_MODE_SVC | PSR_I_BIT | PSR_F_BIT)
#else
	mov		r0, #(PSR_MODE_SVC | PSR_I_BIT)
#endif
	msr		cpsr_c, r0			/* Switch back SVC mode */

	/* Get the values for r15(pc) and CPSR in r3 and r4 */

	mov		r3, r14				/* Save r14 as the PC as well */
	mrs		r4, spsr			/* Get the saved CPSR */

#ifdef CONFIG_ARMV7A_DECODEFIQ
	orr		r0, r0, #(PSR_MODE_SYS | PSR_I_BIT | PSR_F_BIT)
#else
	orr		r0, r0, #(PSR_MODE_SYS | PSR_I_BIT)
#endif
	msr		cpsr_c, r0

	/* Get the correct values of USR/SYS r13(sp) and r14(lr) in r1 and r2 */

	add		r1, sp, #XCPTCONTEXT_SIZE
	mov		r2, r14

	/* Save r13(sp), r14(lr), r15(pc), and the CPSR */

	add		r0, sp, #(4*REG_SP)		/* Offset to pc, cpsr storage */
	stmia		r0, {r1-r4}

	/* Then call the SVC handler with interrupts disabled.
	 * void arm_syscall(struct xcptcontext *xcp)
	 */

	mov		fp, #0				/* Init frame pointer */
	mov		r0, sp				/* Get r0=xcp */

#if CONFIG_ARCH_INTERRUPTSTACK > 7
	/* Call arm_syscall() on the interrupt stack */

	ldr		sp, .Lirqstacktop		/* SP = interrupt stack top */
	str		r0, [sp, #-4]!			/* Save the xcp address at SP-4 then update SP */
	mov		r4, sp				/* Save the SP in a preserved register */
	bic		sp, sp, #7			/* Force 8-byte alignment */
	bl		arm_syscall			/* Call the handler */
	ldr		sp, [r4]			/* Restore the user stack pointer */
#else
	/* Call arm_syscall() on the user stack */

	mov		r4, sp				/* Save the SP in a preserved register */
	bic		sp, sp, #7			/* Force 8-byte alignment */
	bl		arm_syscall			/* Call the handler */
	mov		sp, r4				/* Restore the possibly unaligned stack pointer */
#endif

	/* Switch back SVC mode and return with shadow SPSR */

#ifdef CONFIG_ARMV7A_DECODEFIQ
	mov		r4, #(PSR_MODE_SVC | PSR_I_BIT | PSR_F_BIT)
#else
	mov		r4, #(PSR_MODE_SVC | PSR_I_BIT)
#endif
	msr		cpsr_c, r4			/* Switch back SVC mode */

	/* Upon return from arm_syscall, r0 holds the pointer to the register
	 * state save area to use to restore the registers.  This may or may not
	 * be the same value that was passed to arm_syscall:  It will differ if a
	 * context switch is required.
	 */

	/* Restore the CPSR, SYS mode registers and return */

	ldr		r1, [r0, #(4*REG_CPSR)]		/* Fetch the return SPSR */
	msr		spsr_cxsf, r1			/* Set the return mode SPSR */

	/* Life is simple when everything is SVC mode */

	mov		r14, r0				/* (SVC) r14=Register storage area */
	ldmia		r14!, {r0-r12}			/* Restore common r0-r12 */
	ldmia		r14, {r13, r14}^		/* Restore user mode r13/r14 */
	add		r14, r14, #(4*2)		/* (SVC) r14=address of r15 storage */
	ldmia		r14, {r15}^			/* Return */
	.size	arm_vectorsvc, . - arm_vectorsvc

	.align	5

/****************************************************************************
 * Name: arm_vectordata
 *
 * Description:
 *   This is the data abort exception dispatcher. The ARM data abort exception occurs
 *   when a memory fault is detected during a data transfer.  This handler saves the
 *   current processor state and gives control to data abort handler.  This function
 *   is entered in ABORT mode with spsr = SVC CPSR, lr = SVC PC
 *
 ****************************************************************************/

	.globl	arm_dataabort
	.globl	arm_vectordata
	.type	arm_vectordata, %function

arm_vectordata:
	/* On entry we are free to use the ABORT mode registers
	 * r13 and r14
	 */

#ifdef CONFIG_ARMV7A_DECODEFIQ
	mov		r13, #(PSR_MODE_SYS | PSR_I_BIT | PSR_F_BIT)
#else
	mov		r13, #(PSR_MODE_SYS | PSR_I_BIT)
#endif
	msr		cpsr_c, r13			/* Switch to SYS mode */

	/* Create a context structure.  First set aside a stack frame
	 * and store r0-r12 into the frame.
	 */

	sub		sp, sp, #XCPTCONTEXT_SIZE
	stmia		sp, {r0-r12}			/* Save the SYS mode regs */

#ifdef CONFIG_ARMV7A_DECODEFIQ
	mov		r0, #(PSR_MODE_ABT | PSR_I_BIT | PSR_F_BIT)
#else
	mov		r0, #(PSR_MODE_ABT | PSR_I_BIT)
#endif
	msr		cpsr_c, r0			/* Switch back ABT mode */

	/* Get the values for r15(pc) and CPSR in r3 and r4 */

	sub		r3, lr, #8
	mrs		r4, spsr

	/* Then switch back to SYS mode */

#ifdef CONFIG_ARMV7A_DECODEFIQ
	mov		r0, #(PSR_MODE_SYS | PSR_I_BIT | PSR_F_BIT)
#else
	mov		r0, #(PSR_MODE_SYS | PSR_I_BIT)
#endif
	msr		cpsr_c, r0

	/* Get the correct values of USR/SYS r13(sp) and r14(lr) in r1 and r2 */

	add		r1, sp, #XCPTCONTEXT_SIZE
	mov		r2, r14

	/* Save r13(sp), r14(lr), r15(pc), and the CPSR */

	add		r0, sp, #(4*REG_SP)		/* Offset to pc, cpsr storage */
	stmia		r0, {r1-r4}

	/* Then call the data abort handler with interrupts disabled.
	 * void arm_dataabort(struct xcptcontext *xcp)
	 */

	mov		fp, #0				/* Init frame pointer */
	mov		r0, sp				/* Get r0=xcp */
	mrc		CP15_DFAR(r1)			/* Get R1=DFAR */
	mrc		CP15_DFSR(r2)			/* Get r2=DFSR */
	mov		r4, sp				/* Save the SP in a preserved register */
	bic		sp, sp, #7			/* Force 8-byte alignment */
	bl		arm_dataabort			/* Call the handler */
	mov		sp, r4				/* Restore the possibly unaligned stack pointer */

	/* Switch back ABT mode and return with shadow SPSR */

#ifdef CONFIG_ARMV7A_DECODEFIQ
	mov		r4, #(PSR_MODE_ABT | PSR_I_BIT | PSR_F_BIT)
#else
	mov		r4, #(PSR_MODE_ABT | PSR_I_BIT)
#endif
	msr		cpsr_c, r4			/* Switch back ABT mode */

	/* Upon return from arm_dataabort, r0 holds the pointer to the register
	 * state save area to use to restore the registers.  This may or may not
	 * be the same value that was passed to arm_dataabort:  It will differ if a
	 * context switch is required.
	 */

	/* Restore the CPSR, ABT mode registers and return */

	ldr		r1, [r0, #(4*REG_CPSR)]		/* Fetch the return SPSR */
	msr		spsr_cxsf, r1			/* Set the return mode SPSR */

	/* Life is simple when everything is ABT mode */

	mov		r14, r0				/* (ABT) r14=Register storage area */
	ldmia		r14!, {r0-r12}			/* Restore common r0-r12 */
	ldmia		r14, {r13, r14}^		/* Restore user mode r13/r14 */
	add		r14, r14, #(4*2)		/* (ABT) r14=address of r15 storage */
	ldmia		r14, {r15}^			/* Return */
	.size	arm_vectordata, . - arm_vectordata

	.align	5

/****************************************************************************
 * Name: arm_vectorprefetch
 *
 * Description:
 *   This is the prefetch abort exception dispatcher. The ARM prefetch abort exception
 *   occurs when a memory fault is detected during an an instruction fetch.  This
 *   handler saves the current processor state and gives control to prefetch abort
 *   handler.  This function is entered in ABT mode with spsr = SVC CPSR, lr = SVC PC.
 *
 ****************************************************************************/

	.globl	arm_prefetchabort
	.globl	arm_vectorprefetch
	.type	arm_vectorprefetch, %function

arm_vectorprefetch:
	/* On entry we are free to use the ABORT mode registers
	 * r13 and r14
	 */

	mov		r13, #(PSR_MODE_SYS | PSR_I_BIT | PSR_F_BIT)
	msr		cpsr_c, r13			/* Switch to SYS mode */

	/* Create a context structure.  First set aside a stack frame
	 * and store r0-r12 into the frame.
	 */

	sub		sp, sp, #XCPTCONTEXT_SIZE
	stmia		sp, {r0-r12}			/* Save the SYS mode regs */

	mov		r0, #(PSR_MODE_ABT | PSR_I_BIT | PSR_F_BIT)
	msr		cpsr_c, r0			/* Switch back ABT mode */

	/* Get the values for r15(pc) and CPSR in r3 and r4 */

	sub		r3, lr, #4
	mrs		r4, spsr

	/* Then switch back to SYS mode */

	mov		r0, #(PSR_MODE_SYS | PSR_I_BIT | PSR_F_BIT)
	msr		cpsr_c, r0

	/* Get the correct values of USR/SYS r13(sp) and r14(lr) in r1 and r2 */

	add		r1, sp, #XCPTCONTEXT_SIZE
	mov		r2, r14

	/* Save r13(sp), r14(lr), r15(pc), and the CPSR */

	add		r0, sp, #(4*REG_SP)		/* Offset to pc, cpsr storage */
	stmia		r0, {r1-r4}

	/* Then call the prefetch abort handler with interrupts disabled.
	 * void arm_prefetchabort(struct xcptcontext *xcp)
	 */

	mov		fp, #0				/* Init frame pointer */
	mov		r0, sp				/* Get r0=xcp */
	mrc		CP15_IFAR(r1)			/* Get R1=IFAR */
	mrc		CP15_IFSR(r2)			/* Get r2=IFSR */
	mov		r4, sp				/* Save the SP in a preserved register */
	bic		sp, sp, #7			/* Force 8-byte alignment */
	bl		arm_prefetchabort		/* Call the handler */
	mov		sp, r4				/* Restore the possibly unaligned stack pointer */

	/* Switch back ABT mode and return with shadow SPSR */

#ifdef CONFIG_ARMV7A_DECODEFIQ
	mov		r4, #(PSR_MODE_ABT | PSR_I_BIT | PSR_F_BIT)
#else
	mov		r4, #(PSR_MODE_ABT | PSR_I_BIT)
#endif
	msr		cpsr_c, r4			/* Switch back ABT mode */

	/* Upon return from arm_prefetchabort, r0 holds the pointer to the register
	 * state save area to use to restore the registers.  This may or may not
	 * be the same value that was passed to arm_prefetchabort:  It will differ if a
	 * context switch is required.
	 */

	/* Restore the CPSR, ABT mode registers and return */

	ldr		r1, [r0, #(4*REG_CPSR)]		/* Fetch the return SPSR */
	msr		spsr_cxsf, r1			/* Set the return mode SPSR */

	/* Life is simple when everything is ABT mode */

	mov		r14, r0				/* (ABT) r14=Register storage area */
	ldmia		r14!, {r0-r12}			/* Restore common r0-r12 */
	ldmia		r14, {r13, r14}^		/* Restore user mode r13/r14 */
	add		r14, r14, #(4*2)		/* (ABT) r14=address of r15 storage */
	ldmia		r14, {r15}^			/* Return */
	.size	arm_vectorprefetch, . - arm_vectorprefetch

	.align	5

/****************************************************************************
 * Name: arm_vectorundefinsn
 *
 * Description:
 *   Undefined instruction entry exception.  Entered in UND mode, spsr = SVC  CPSR,
 *   lr = SVC PC
 *
 ****************************************************************************/

	.globl	arm_undefinedinsn
	.globl	arm_vectorundefinsn
	.type	arm_vectorundefinsn, %function

arm_vectorundefinsn:
	/* On entry we are free to use the UND mode registers
	 * r13 and r14
	 */

	mov		r13, #(PSR_MODE_SYS | PSR_I_BIT | PSR_F_BIT)
	msr		cpsr_c, r13			/* Switch to SYS mode */

	/* Create a context structure.  First set aside a stack frame
	 * and store r0-r12 into the frame.
	 */

	sub		sp, sp, #XCPTCONTEXT_SIZE
	stmia		sp, {r0-r12}			/* Save the SYS mode regs */

	mov		r0, #(PSR_MODE_UND | PSR_I_BIT | PSR_F_BIT)
	msr		cpsr_c, r0			/* Switch back UND mode */

	/* Get the values for r15(pc) and CPSR in r3 and r4 */

	mov		r3, lr
	mrs		r4, spsr

	/* Then switch back to SYS mode */

	mov		r0, #(PSR_MODE_SYS | PSR_I_BIT | PSR_F_BIT)
	msr		cpsr_c, r0

	/* Get the correct values of USR/SYS r13(sp) and r14(lr) in r1 and r2 */

	add		r1, sp, #XCPTCONTEXT_SIZE
	mov		r2, r14

	/* Save r13(sp), r14(lr), r15(pc), and the CPSR */

	add		r0, sp, #(4*REG_SP)		/* Offset to pc, cpsr storage */
	stmia		r0, {r1-r4}

	/* Then call the undef insn handler with interrupts disabled.
	 * void arm_undefinedinsn(struct xcptcontext *xcp)
	 */

	mov		fp, #0				/* Init frame pointer */
	mov		r0, sp				/* Get r0=xcp */
	mov		r4, sp				/* Save the SP in a preserved register */
	bic		sp, sp, #7			/* Force 8-byte alignment */
	bl		arm_undefinedinsn		/* Call the handler */
	mov		sp, r4				/* Restore the possibly unaligned stack pointer */

	/* Switch back UND mode and return with shadow SPSR */

#ifdef CONFIG_ARMV7A_DECODEFIQ
	mov		r4, #(PSR_MODE_UND | PSR_I_BIT | PSR_F_BIT)
#else
	mov		r4, #(PSR_MODE_UND | PSR_I_BIT)
#endif
	msr		cpsr_c, r4			/* Switch back UND mode */

	/* Upon return from arm_undefinedinsn, r0 holds the pointer to the register
	 * state save area to use to restore the registers.  This may or may not
	 * be the same value that was passed to arm_undefinedinsn:  It will differ if a
	 * context switch is required.
	 */

	/* Restore the CPSR, UND mode registers and return */

	ldr		r1, [r0, #(4*REG_CPSR)]		/* Fetch the return SPSR */
	msr		spsr_cxsf, r1			/* Set the return mode SPSR */

	/* Life is simple when everything is UND mode */

	mov		r14, r0				/* (UND) r14=Register storage area */
	ldmia		r14!, {r0-r12}			/* Restore common r0-r12 */
	ldmia		r14, {r13, r14}^		/* Restore user mode r13/r14 */
	add		r14, r14, #(4*2)		/* (UND) r14=address of r15 storage */
	ldmia		r14, {r15}^			/* Return */
	.size	arm_vectorundefinsn, . - arm_vectorundefinsn

	.align	5

/****************************************************************************
 * Name: arm_vectorfiq
 *
 * Description:
 *   Shouldn't happen unless a arm_decodefiq() is provided.  FIQ is primarily used
 *   with the TrustZone feature in order to handle secure interrupts.
 *
 ****************************************************************************/

#ifdef CONFIG_ARMV7R_DECODEFIQ
	.globl	arm_decodefiq
#endif
	.globl	arm_vectorfiq
	.type	arm_vectorfiq, %function

arm_vectorfiq:
#ifdef CONFIG_ARMV7R_DECODEFIQ
	/* On entry we are free to use the FIQ mode registers r8 through r14 */

	mov		r13, #(PSR_MODE_SYS | PSR_I_BIT | PSR_F_BIT)
	msr		cpsr_c, r13			/* Switch to SYS mode */

	/* Create a context structure.  First set aside a stack frame
	 * and store r0-r12 into the frame.
	 */

	sub		sp, sp, #XCPTCONTEXT_SIZE
	stmia		sp, {r0-r12}			/* Save the SYS mode regs */

	mov		r0, #(PSR_MODE_FIQ | PSR_I_BIT | PSR_F_BIT)
	msr		cpsr_c, r0			/* Switch back FIQ mode */

	/* Get the values for r15(pc) and CPSR in r3 and r4 */

	sub		r3, lr, #4
	mrs		r4, spsr

	/* Then switch back to SYS mode */

	mov		r0, #(PSR_MODE_SYS | PSR_I_BIT | PSR_F_BIT)
	msr		cpsr_c, r0

	/* Get the correct values of USR/SYS r13(sp) and r14(lr) in r1 and r2 */

	add		r1, sp, #XCPTCONTEXT_SIZE
	mov		r2, r14

	/* Save r13(sp), r14(lr), r15(pc), and the CPSR */

	add		r0, sp, #(4*REG_SP)		/* Offset to pc, cpsr storage */
	stmia		r0, {r1-r4}

	/* Then call the FIQ handler with interrupts disabled. */

	mov		fp, #0				/* Init frame pointer */
	mov		r0, sp				/* Get r0=xcp */

#if CONFIG_ARCH_INTERRUPTSTACK > 7
	/* Call arm_decodefiq() on the interrupt stack */

	ldr		sp, .Lfiqstacktop		/* SP = interrupt stack top */
	str		r0, [sp, #-4]!			/* Save the xcp address at SP-4 then update SP */
	mov		r4, sp				/* Save the SP in a preserved register */
	bic		sp, sp, #7			/* Force 8-byte alignment */
	bl		arm_decodefiq			/* Call the handler */
	ldr		sp, [r4]			/* Restore the user stack pointer */
#else
	/* Call arm_decodefiq() on the user stack */

	mov		r4, sp				/* Save the SP in a preserved register */
	bic		sp, sp, #7			/* Force 8-byte alignment */
	bl		arm_decodefiq			/* Call the handler */
	mov		sp, r4				/* Restore the possibly unaligned stack pointer */
#endif

	/* Switch back FIQ mode and return with shadow SPSR */

#ifdef CONFIG_ARMV7A_DECODEFIQ
	mov		r4, #(PSR_MODE_FIQ | PSR_I_BIT | PSR_F_BIT)
#else
	mov		r4, #(PSR_MODE_FIQ | PSR_I_BIT)
#endif
	msr		cpsr_c, r4			/* Switch back FIQ mode */

	/* Upon return from arm_decodefiq, r0 holds the pointer to the register
	 * state save area to use to restore the registers.  This may or may not
	 * be the same value that was passed to arm_decodefiq:  It will differ if a
	 * context switch is required.
	 */

	/* Restore the CPSR, FIQ mode registers and return */

	ldr		r1, [r0, #(4*REG_CPSR)]		/* Fetch the return SPSR */
	msr		spsr_cxsf, r1			/* Set the return mode SPSR */

	/* Life is simple when everything is FIQ mode */

	mov		r14, r0				/* (FIQ) r14=Register storage area */
	ldmia		r14!, {r0-r7}			/* Restore common r0-r7 */
	ldmia		r14, {r8-r14}^			/* Restore user mode r8-r14 */
	add		r14, r14, #(4*7)		/* (FIQ) r14=address of r15 storage */
	ldmia		r14, {r15}^			/* Return */

#if CONFIG_ARCH_INTERRUPTSTACK > 7
.Lfiqstacktop:
	.word	g_fiqstacktop
#endif

#else
	subs	pc, lr, #4
#endif
	.size	arm_vectorfiq, . - arm_vectorfiq

/****************************************************************************
 *  Name: g_intstackalloc/g_intstacktop
 ****************************************************************************/

#if CONFIG_ARCH_INTERRUPTSTACK > 7
	.bss
	.balign	8

	.globl	g_intstackalloc
	.type	g_intstackalloc, object
	.globl	g_intstacktop
	.type	g_intstacktop, object

g_intstackalloc:
	.skip	((CONFIG_ARCH_INTERRUPTSTACK + 4) & ~7)
g_intstacktop:
	.size	g_intstacktop, 0
	.size	g_intstackalloc, (CONFIG_ARCH_INTERRUPTSTACK & ~7)

/****************************************************************************
 *  Name: g_fiqstackalloc/g_fiqstacktop
 ****************************************************************************/

	.globl	g_fiqstackalloc
	.type	g_fiqstackalloc, object
	.globl	g_fiqstacktop
	.type	g_fiqstacktop, object

g_fiqstackalloc:
	.skip	((CONFIG_ARCH_INTERRUPTSTACK + 4) & ~7)
g_fiqstacktop:
	.size	g_fiqstacktop, 0
	.size	g_fiqstackalloc, (CONFIG_ARCH_INTERRUPTSTACK & ~7)

#endif /* CONFIG_ARCH_INTERRUPTSTACK > 7 */
	.end
