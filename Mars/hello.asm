#Hello World��\������v���O����

#�f�[�^
        .data
msg:    .asciiz "Hello World\n"

#�e�L�X�g

        .text
        .globl main
main:
  li    $v0, 4
        la        $a0, msg
        syscall
        jr        $ra

# end
