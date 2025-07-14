.data
input_prompt: .asciiz "Enter a number: "
newline: .asciiz "\n"
buffer: .space 11

.text
.globl main

main:
    li $v0, 4
    la $a0, input_prompt
    syscall

    li $v0, 8
    la $a0, buffer
    li $a1, 11
    syscall

    # •¶š—ñ‚©‚ç”š‚Ö‚Ì•ÏŠ·‚Æ•\¦
    li $t0, 0
    la $t1, buffer

conv_loop:
    lb $t2, ($t1)
    beq $t2, $zero, conv_end
    sub $t2, $t2, '0'
    mul $t0, $t0, 10
    add $t0, $t0, $t2
    addi $t1, $t1, 1
    j conv_loop

conv_end:
    li $v0, 1
    move $a0, $t0
    syscall

    li $v0, 4
    la $a0, newline
    syscall

    li $v0, 10
    syscall
