#include <stdio.h>
int main(int argc, char *argv[]){
int i;
printf("argc = %d ¥n",argc);
 // 引数の個数表示
 for(i=0; i<argc; i++)
printf("argv[%d] = %s¥n",i, argv[i]);
// 引数(文字列)を表示
}


/*
#Linux（仮想）端末上の操作
[net]% gcc “左図プログラム” #コンパイル
[net]% a.out network 2025 #実行
argc = 3
argv[0] = a.out
argv[1] = network
argv[2] = 2025
[net]%
*/