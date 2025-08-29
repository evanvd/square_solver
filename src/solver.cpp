/**
 * @file solve.cpp
 * @brief Реализация функций решения квадратных и линейных уравнений
 *
 * @details
 * Этот модуль содержит реализации функций для решения:
 * - Квадратных уравнений: ax² + bx + c = 0
 * - Линейных уравнений: bx + c = 0
 * - Вырожденных случаев
 *
 * @note Использует точность EPS для сравнения чисел с плавающей точкой
 * @note Выполняет проверки входных данных с помощью assert
 */
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "solver.h"
#include "tests.h"
#include "IO.h"

/** @defgroup solving Функции решения уравнений */

/**
 * @brief Определяет тип уравнения и вызывает соответствующую функцию решения
 * @ingroup solving
 *
 * @param[in] coeff Структура с коэффициентами уравнения
 * @param[out] roots Указатель на структуру для записи корней
 * @return rootsCount Количество действительных корней
 *
 * @details
 * Функция анализирует коэффициент a чтобы определить тип уравнения:
 * - Если |a| < EPS: линейное уравнение → вызывает solve_linear()
 * - Если |a| >= EPS: квадратное уравнение → вызывает solve_quadratic()
 *
 * @note EPS = 1e-6 (точность сравнения чисел с плавающей точкой)
 * @see solve_linear()
 * @see solve_quadratic()
 *
 * @code
 * coeff equation = {1, -5, 6};
 * roots solution;
 * rootsCount result = num_root(equation, &solution);
 * // result = TwoRoots, solution.x1 = 3, solution.x2 = 2
 * @endcode
 */

rootsCount num_root(coeff coeff, roots* roots)
{
    if (fabs(coeff.a) < EPS)
    {
        return solve_linear(coeff, roots);
    }
    return solve_quadratic(coeff, roots);
}

rootsCount solve_linear(coeff coeff, roots* roots)
{
    if (fabs(coeff.b) < EPS)
    {
        if (fabs(coeff.c) < EPS)
        {
            return InfiniteRoots;
        }
        return ZeroRoots;
    }
    else
    {
        roots->x1 = -coeff.c / coeff.b;
        return OneRoot;
    }
}

rootsCount solve_quadratic(coeff coeff, roots* roots)
{
    assert(roots != NULL);
    assert(isfinite(coeff.a));
    assert(isfinite(coeff.b));
    assert(isfinite(coeff.c));

    double d = coeff.b * coeff.b - 4 * coeff.a * coeff.c;

    if (d < -EPS)
    {
        return ZeroRoots;
    }

    if (fabs(d) < EPS)
    {
        roots->x1 = -coeff.b / (2 * coeff.a);
        return OneRoot;
    }

    if (d > EPS)
    {
        roots->x2 = (-coeff.b - sqrt(d)) / (2 * coeff.a);
        roots->x1 = (-coeff.b + sqrt(d)) / (2 * coeff.a);
        return TwoRoots;
    }
    return Error;
}
