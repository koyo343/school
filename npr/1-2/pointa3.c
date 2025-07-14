#include <stdio.h>
#include <string.h> // 関数 strcpy() の利用に必要なヘッダ
int main(){
// 1. 文字列配列と文字型ポインタの宣言と初期化
char s[] = “abc", *sp = “abc”;
printf(“s[] = %s, sp = %s ¥n”, s, sp);
// 文字列表示 ～ 配列名 sは文字列の先頭アドレスを示す
// 2. 文字列の代入（変更）
 strcpy(s,“123”);
// 文字型配列への代入 ～ 関数 strcpy() の利用
sp = “vwxyz";
// 文字列を別のメモリ空間に確保して先頭アドレスを代入
printf("s[] = %s, sp = %s ¥n", s, sp);
}
