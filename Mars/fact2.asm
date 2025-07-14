    .data
result: .word 0        

    .text
    .globl main

main:
    li $t0, 5		#ŠKæ‚³‚¹‚½‚¢”‚ğ“ü—Í
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
