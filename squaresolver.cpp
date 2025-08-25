#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include "solver.h"
#include "tests.h"
#include "IO.h"

/**
 * @file squaresolver.cpp
 * @brief Решение квадратных и линейных уравнений
 * @details
 * решение уравнений вида:
 * - Квадратные: ax^2 + bx + c = 0
 * - Линейные: bx + c = 0
 */

int main(int argc, char **argv)
{
    if (search_flag(argc, argv,"--test"))
    {
        run_all_test();
        return 0;

    }
    print_welcome();
    color_printf(BLUE,"Введите коэффициенты квадратного уравнения вида ax^2+bx+c:\n ");

    coeff coeff = {NAN, NAN, NAN};
    bool isCorrectInput = scan_check(&coeff.a, &coeff.b, &coeff.c);
    if (!isCorrectInput)
    {
        return 0;
    }

    roots roots = {NAN, NAN, Error};
    roots.nroots = num_root(coeff, &roots);

    print_roots(roots);
    return 0;
}
