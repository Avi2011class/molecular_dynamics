#include <iostream>
#include <omp.h>
#include <ctime>
#include <cstdlib>
#include <vector>

void test();

int main(void)
{
    srand(time(0));
    test();

    return 0;
}
