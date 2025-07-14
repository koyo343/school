    .data
    newline: .asciiz "\n"

    .text
    .globl main

main:
    li $a0, 3
    jal star
    
    li $v0, 4
    la $a0, newline
    syscall

    li $a0, 5
    jal star
    
    li $v0, 4
    la $a0, newline
    syscall

    li $a0, 10
    jal star

    li $v0, 10
    syscall

star:
    move $t0, $a0

star_loop:
    beq $t0, $zero, star_exit

    li $v0, 11
    li $a0, '*'
    syscall

    addi $t0, $t0, -1
    j star_loop

star_exit:
    jr $ra
