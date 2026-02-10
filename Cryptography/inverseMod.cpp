#include <stdio.h>

int main() {
    long secret = 15211009989869998005UL;  // force 64-bit wrap
    printf("%li\n", secret * 4823);
    return 0;
}
