# データ領域開始の宣言
        .data
# int p
        .globl p
p:      .word  0

# int q
        .globl q
q:      .word  0

# テキスト領域開始の宣言
        .text

# int main ()
        .globl main
main:

# p = 1
    li    $s0, 1
    la    $t0, p
    sw    $s0, 0($t0)

# q = 0
    la    $t0, q
    sw    $zero, 0($t0)

# loop_begin
loop_begin:

# if (p > 100) goto loop_end
    la    $t0, p
    lw    $s0, 0($t0)
    li    $s1, 100
    sgt   $t0, $s0, $s1
    bnez  $t0, loop_end

# q = q + p
    la    $t0, q
    lw    $s0, 0($t0)
    la    $t1, p
    lw    $s1, 0($t1)
    add   $s0, $s0, $s1
    sw    $s0, 0($t0)

# p = p + 1
    la    $t0, p
    lw    $s0, 0($t0)
    addi  $s0, $s0, 1
    sw    $s0, 0($t0)


# goto loop_begin
    b     loop_begin

# loop_end
loop_end:

# return 0
    li    $v0, 0
    jr    $ra
