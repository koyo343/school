    .data
result: .word 0

    .text
    .globl main

main:
    li $t0, 5		#ŠKæ‚³‚¹‚½‚¢”‚ğ“ü—Í
    li $t1, 1
    li $t2, 1
    addi $t0, $t0, 1

fact_loop:
    mul $t1, $t1, $t2
    addi $t2, $t2, 1
    bne $t2, $t0, fact_loop

    sw $t1, result

    li $v0, 1            
    lw $a0, result
    syscall

    li $v0, 10
    syscall
