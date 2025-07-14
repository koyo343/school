#include <stdio.h>
// s = s1 + '_' + s2 を行う関数
void slink(char *s, char *s1, char *s2) {
    while (*s1 != '\0'){
        *s = *s1;
        s++;
        s1++;
    }
    *s = '_';
    s++;
    while (*s2 != '\0') {
        *s = *s2;
        s++;
        s2++;
    }
    *s = '\0';
}

int main(int argc, char *argv[]){
    char s[30], s1[] = "Etou", s2[] = "Kouhi"; // 苗字と名前を入れる
    slink(s, s1, s2); // s に "Etou_Kouhi" を格納
    printf("%s\n", s); // 出力: Etou_Kouhi
    return 0;
}
