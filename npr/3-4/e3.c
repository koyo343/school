#include <stdio.h>
#include <stdlib.h>
int main() {
    FILE *fin, *fout;
    char id[10];
    int score;
    int i;
    for (i = 0; i < 3; i++) { // 例えば3回繰り返す
        fin = fopen("input2.dat", "r");
        if (fin == NULL) {
            printf("Error: cannot open input2.dat\n");
            return 1;
        }
        fout = fopen("output2.dat", "a");
        if (fout == NULL) {
            printf("Error: cannot open output2.dat\n");
            fclose(fin);
            return 1;
        }
        fprintf(fout, "=== Round %d ===\n", i + 1);
        while (fscanf(fin, "%s %d", id, &score) == 2) {
            fprintf(fout, "%s %d\n", id, score);
        }
        fclose(fin);
        fclose(fout);
    }
    return 0;
}
