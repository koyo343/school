	.file	1 "main.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	softfloat
	.module	oddspreg
	.section	.text,code
	.align	2
	.globl	main
	.set	nomips16
	.set	nomicromips
	.ent	main
	.type	main, @function
main:
	.frame	$fp,24,$31		# vars= 16, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
# End mchp_output_function_prologue
	addiu	$sp,$sp,-24
	sw	$fp,20($sp)
	move	$fp,$sp
	li	$2,11			# 0xb
	sw	$2,0($fp)
	li	$2,7			# 0x7
	sw	$2,4($fp)
	lw	$3,0($fp)
	lw	$2,4($fp)
	addu	$2,$3,$2
	sw	$2,8($fp)
	lui	$2,%hi(TRISBCLR)
	li	$3,15			# 0xf
	sw	$3,%lo(TRISBCLR)($2)
	lui	$2,%hi(PORTB)
	li	$3,6			# 0x6
	sw	$3,%lo(PORTB)($2)
	move	$2,$0
	move	$sp,$fp
	lw	$fp,20($sp)
	addiu	$sp,$sp,24
	jr	$31
	nop

	.set	macro
	.set	reorder
# Begin mchp_output_function_epilogue
# End mchp_output_function_epilogue
	.end	main
	.size	main, .-main
	.ident	"GCC: (Microchip XC32 Compiler v4.40) 8.3.1"
