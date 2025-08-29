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

// --test_file
int main(int argc, char **argv)
{
    if (search_flag(argc, argv,"--embedded_test"))
    {
        run_embedded_test();
        return 0;
    }
    if (search_flag(argc, argv,"--test_file"))
    {
        run_from_file("test.txt");
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
