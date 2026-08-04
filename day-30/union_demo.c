#include <stdio.h>

union Value {
    int    i;
    float  f;
    char   bytes[4];
};

int main(void)
{
    union Value v;
    v.f = 1.0f;
    printf("as float: %f\n", v.f);

    v.i = 0x41414141;
    printf("as int  : %d (0x%X)\n", v.i, v.i);
    printf("as bytes: %c%c%c%c\n",
           v.bytes[0], v.bytes[1], v.bytes[2], v.bytes[3]);

    printf("sizeof(union Value) = %zu\n", sizeof(union Value));
    return 0;
}
