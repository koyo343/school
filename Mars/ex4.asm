   .data 
result: .word 0

   .text
   .globl main

main:
    li $a0, 3
    jal fact
    move $t0, $v0
    li $v0, 1 
    move $a0, $t0
    syscall
    li $v0, 10
    syscall

fact:
    addi $sp, $sp, -8
    sw $ra, 4($sp)
    sw $a0, 0($sp)
    
    slti $t0, $a0, 1
    beq $t0, $zero, fact_rec
    li $v0, 1
    j fact_end
    
fact_rec:
    addi $a0, $a0, -1
    jal fact
    
    lw $a0, 0($sp)
    mul $v0, $v0, $a0
    
fact_end:
    lw $ra, 4($sp)
    addi $sp, $sp, 8
    jr $ra
