#include <stdio.h>
void print_v(int n){
printf("Value = %d¥n",n);
n = 100; // 関数の仮引数 n に100を代入
}
int main(){
int i = 10;
print_v(i); // 関数の実引数は「i の値」
 printf("Value = %d¥n",i);
}
