#include <stdio.h>
#include <stddef.h>

struct Example {
    char a;     // 1 byte
    int b;      // 4 bytes
    double c;   // 8 bytes
};

int main() {
    struct Example e;

    printf("Size of struct Example: %zu bytes\n", sizeof(struct Example));
    printf("Offset of 'a': %zu bytes\n", offsetof(struct Example, a));
    printf("Offset of 'b': %zu bytes\n", offsetof(struct Example, b));
    printf("Offset of 'c': %zu bytes\n", offsetof(struct Example, c));

    return 0;
}