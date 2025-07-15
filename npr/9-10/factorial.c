#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

long long factorial(int n) {
    if (n < 0) return -1;
    if (n == 0) return 1;
    long long res = 1;
    for (int i = 1; i <= n; i++) {
        if (i > LLONG_MAX / res)
            return -2;
        res *= i;
    }
    return res;
}

int main() {
    char *method;
    char buffer[2048];
    char *data = NULL;
    int num = -1;

    printf("Content-type: text/html\n\n");
    printf("<html><head><title>Factorial Calculator</title></head><body>\n");
    printf("<h1>Factorial Result</h1>\n");
    printf("<pre>\n");

    method = getenv("REQUEST_METHOD");

    if (method && strcmp(method, "POST") == 0) {
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            data = buffer;
        }
    } else {
        data = getenv("QUERY_STRING");
    }

    if (data && strlen(data) > 0) {
        char *pair = strtok(data, "&");
        while (pair) {
            char *value = strchr(pair, '=');
            if (value) {
                *value = '\0';
                value++;
                if (strcmp(pair, "number") == 0) {
                    num = atoi(value);
                    break;
                }
            }
            pair = strtok(NULL, "&");
        }
    }

    if (num >= 0) {
        long long result = factorial(num);
        if (result == -1) {
            printf("Error: Input must be a non-negative integer.\n");
        } else if (result == -2) {
            printf("Error: Result for %d! is too large to calculate (overflowed long long).\n", num);
        } else {
            printf("Factorial of %d is %lld\n", num, result);
        }
    } else {
        printf("Please provide a non-negative integer via 'number' parameter.\n");
        printf("Example: ?number=5 or POST with number=5\n");
    }

    printf("</pre>\n");
    printf("</body></html>\n");

    return 0;
}