#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include "solver.h"

int main(int argc, char **argv)
{
    if (search_flag(argc, argv,"--test"))
    {
        run_all_test();
        return 0;

    }
    printf("Введите коэффициенты квадратного уравнения вида ax^2+bx+c:\n ");

    struct coeff coeff = {NAN, NAN, NAN};
    scanf("%lg %lg %lg", &coeff.a, &coeff.b, &coeff.c); // TODO scanf check

    struct roots roots = {NAN, NAN, Error};
    roots.nroots = num_root(coeff, &roots);

    print_roots(roots);
    return 0;
}
