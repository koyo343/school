#â€ëË1    
    .data
result: .word 0

    .text
    .globl main

main:
    li $t0, 5		#äKèÊÇ≥ÇπÇΩÇ¢êîÇì¸óÕ
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
    
    
#â€ëË2
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


#â€ëË3
    .data
result: .word 0        

    .text
    .globl main

main:
    li $t0, 5		#äKèÊÇ≥ÇπÇΩÇ¢êîÇì¸óÕ
    addi $t0, $t0, 1
    move $a0, $t0
    jal fact
    move $t1, $v0
    li $v0, 1
    move $a0, $t1
    syscall
    li $v0, 10           
    syscall              

fact:
    li $v0, 1            
    li $t2, 1            

fact_loop:
    mul $v0, $v0, $t2    
    addi $t2, $t2, 1     
    bne $t2, $a0, fact_loop  
    jr $ra               


#â€ëË4
    .data 
result: .word 0

   .text
   .globl main

main:
    li $a0, 6
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