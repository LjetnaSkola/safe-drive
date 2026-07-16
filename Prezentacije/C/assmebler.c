#include <stdio.h>

int func(int in) {
    int res;

    asm (
        "movl %1, %%eax; \n\t"
        "add $1, %%eax; \n\t"
        "movl %%eax, %0;"

        : "=r"(res) // output
        : "r"(in) // input
        : "%eax"
    );

    return res;
}

int main() {
    int value = 15;

    int result = func(value);
    printf("Result: %d\n", result);

    return 0;
}
