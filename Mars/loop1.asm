        .data
        
newln:  .asciiz "\n"

        .globl p
p:      .word  0


        .globl q
q:      .word  0

        .text

        .globl main
main:

    li    $s0, 1
    la    $t0, p
    sw    $s0, 0($t0)

    la    $t0, q
    sw    $zero, 0($t0)

loop_begin:

    la    $t0, p
    lw    $s0, 0($t0)
    li    $s1, 100
    sgt   $t0, $s0, $s1
    bnez  $t0, loop_end

    la    $t0, q
    lw    $s0, 0($t0)
    la    $t1, p
    lw    $s1, 0($t1)
    add   $s0, $s0, $s1
    sw    $s0, 0($t0)

    la    $t0, p
    lw    $s0, 0($t0)
    addi  $s0, $s0, 1
    sw    $s0, 0($t0)


    b     loop_begin

loop_end:

    li    $v0, 1
    la    $a0, p
    lw    $a0, 0($a0)
    syscall
    
    li        $v0,4
    la        $a0,newln
    syscall
    
    li    $v0, 1
    la    $a0, q
    lw	  $a0, 0($a0)
    syscall
    
    li    $v0,10
    syscall
