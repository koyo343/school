#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// URLデコードを行う関数
void print_decoded_str(const char* str) {
    while (*str) {
        if (*str == '+') {
            putchar(' ');
        } else if (*str == '%') {
            int val;
            // %に続く2桁の16進数を整数に変換
            if (sscanf(str + 1, "%2x", &val) == 1) {
                putchar(val);
                str += 2;
            }
        } else {
            putchar(*str);
        }
        str++;
    }
}

int main() {
    char *method;
    char buffer[2048]; // データ格納用のバッファ
    char *data;

    // CGIのヘッダ
    printf("Content-type: text/html\n\n");
    printf("<html><head><title>CGI Input Extractor</title></head><body>\n");
    printf("<h1>Extracted User Input</h1>\n");
    printf("<pre>\n");

    // リクエストメソッドを取得
    method = getenv("REQUEST_METHOD");

    if (method && strcmp(method, "POST") == 0) {
        // POSTの場合、標準入力からデータを読み込む
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            data = buffer;
        } else {
            data = "";
        }
    } else {
        // GETの場合、環境変数 QUERY_STRING からデータを取得
        char *query_string = getenv("QUERY_STRING");
        if (query_string) {
            // strtokが文字列を書き換えるため、バッファにコピーする
            strncpy(buffer, query_string, sizeof(buffer) - 1);
            buffer[sizeof(buffer) - 1] = '\0';
            data = buffer;
        } else {
            data = "";
        }
    }

    if (strlen(data) > 0) {
        // `&` で各パラメータペアに分割
        char *pair = strtok(data, "&");
        while (pair) {
            // `=` でキーと値を分離
            char *value = strchr(pair, '=');
            if (value) {
                *value = '\0'; // キーと値の間にNULL文字を挿入して文字列を分割
                value++;      // 値の開始ポインタ
                printf("Input: ");
                print_decoded_str(value); // デコードして値を表示
                printf("\n");
            }
            // 次のペアへ
            pair = strtok(NULL, "&");
        }
    } else {
        printf("No input data received.\n");
    }

    printf("</pre>\n");
    printf("</body></html>\n");

    return 0;
}