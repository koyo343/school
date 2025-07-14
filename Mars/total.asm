    .data

.text
.globl main

main:
    li $t0, 1
    li $t1, 10
    li $t2, 0

sum_loop:
    add $t2, $t2, $t0
    addi $t0, $t0, 1
    ble $t0, $t1, sum_loop
    li $v0, 1
    move $a0, $t2
    syscall
    li $v0, 10
    syscall
