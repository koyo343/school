#include <stdio.h>
#include <stdlib.h>

int fact(int x){
    if (x==1) return 1;
    else return x * fact(x-1);
}

int main(){
    int i = 1;
    char *data;

    printf("Content-type: text/html\n\n");
    // 1. ブラウザ表示のために必ず記述！
    printf("<pre>\n");
    do{
        printf("%3d! = %8d \n",i, fact(i)); i++;
    }while(i <= 10);
    printf("</pre>\n");
    return 0;
} // 2. <pre> .. </pre> ～整形テキスト表示