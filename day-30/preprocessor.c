#include <stdio.h>

#define PI          3.14159
#define SQUARE(x)   ((x) * (x))
#define MAX(a, b)   ((a) > (b) ? (a) : (b))

#if defined(DEBUG)
    #define LOG(msg)  printf("[debug] %s\n", msg)
#else
    #define LOG(msg)  ((void)0)
#endif

int main(void)
{
    printf("PI       = %.5f\n", PI);
    printf("SQUARE(5)= %d\n", SQUARE(5));
    printf("MAX(3,7) = %d\n", MAX(3, 7));
    LOG("hello");
    return 0;
}
