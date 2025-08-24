#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "solver.h"
#include <string.h>



bool scan_check(double* a, double* b, double* c)
{
    scanf("%lg %lg %lg", a, b, c);

    if (!isfinite(*a) || !isfinite(*b) || !isfinite(*c))
    {
        printf("Error: Non-numeric values entered\n");
        return false;
    }

    return true;
}

bool search_flag(int argc, char** argv, const char* flags)
{
    for (int num_flags = 1; num_flags < argc; num_flags++)
    if (strcmp(argv[num_flags], flags) == 0)
    {
        return true;
    }
    return false;
}

void print_roots(roots roots)
{
    switch(roots.nroots)
    {
        case ZeroRoots:
            printf("Уравнение не имеет решений\n");
            break;
        case OneRoot:
            printf("Уравнение имеет единственное решение: x = %lf\n", roots.x1);
            break;
        case TwoRoots:
            printf("Уравнение имеет два решения: x1 = %lf, x2 = %lf\n", roots.x1, roots.x2);
            break;
        case InfiniteRoots:
            printf("Уравнение имеет бесконечно много решений\n");
            break;
        case Error:
            printf("ERROR\n");
            break;
        default:
            break;
    }
}
