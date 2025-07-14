　　　　.globl main
main:
        li      $t0, 5
loop:
        beq     $t0, $zero, exit        # if ($t0 ==  0) then end loop
        li      $v0, 11  # putchar
        li      $a0, '*'
        syscall
        addi    $t0, $t0, -1
        j       loop                            # jump to loop
    
exit:
        li      $v0, 10
        syscall