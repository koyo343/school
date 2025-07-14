#include <stdio.h>
#include <stdlib.h>
struct student {
    char id[10];   // 学籍番号
    int score;     // 評点
};
int main() {
    struct student seito[10];   // 学生情報格納用配列
    FILE *fin, *fout;
    int count = 0;
    int sum = 0;
    double average;

    fin = fopen("input2.dat", "r");
    if (fin == NULL) {
        printf("Error: cannot open input2.dat\n");
        return 1;
    }
    while (fscanf(fin, "%s %d", seito[count].id, &seito[count].score) == 2) {
        sum += seito[count].score;
        count++;
        if (count >= 10) break;
    }
    fclose(fin);
    if (count > 0) {
        average = (double)sum / count;
    } else {
        average = 0.0;
    }
    fout = fopen("output.dat", "w");
    if (fout == NULL) {
        printf("Error: cannot open output.dat\n");
        return 1;
    }
    fprintf(fout, "学生数: %d\n", count);
    fprintf(fout, "平均点: %d\n", (int)(average + 0.5));
    fclose(fout);
    return 0;
}