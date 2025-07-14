#include <stdio.h>
int main(){
// 1.変数の宣言
 int a, b; // 通常変数
 int *pt; // ポインタ変数
 printf("a = %d, b = %d, *pt = %d¥n", a, b, *pt);
// 2.変数の初期化
 a = 123; // 直接指示：変数に直接値を代入
 pt = &a; // 間接指示：ポインタ変数にアドレスを代入
 b = *pt; // 〜 間接的に値を代入
 printf("a = %d, b = %d, *pt = %d¥n", a, b, *pt);
// 3.ポインタ変数を介した値の代入
 pt = &b;
 *pt = 999; // bに間接的に999を代入するには？
printf("a = %d, b = %d, *pt = %d¥n", a, b, *pt);
}
