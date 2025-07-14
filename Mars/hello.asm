#Hello Worldを表示するプログラム

#データ
        .data
msg:    .asciiz "Hello World\n"

#テキスト

        .text
        .globl main
main:
  li    $v0, 4
        la        $a0, msg
        syscall
        jr        $ra

# end
