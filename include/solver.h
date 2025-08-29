/**
 * @file solver.h
 * @brief Заголовочный файл модуля решателя уравнений
 * @details
 * @see solver.h для определения структур coeff и roots
 */

#include <stdio.h>

/** @defgroup constants Константы программы */

/**
 * @brief Точность сравнения чисел с плавающей точкой
 * @ingroup constants
 */
const double EPS = 1e-10;

/**
 * @brief Перечисление возможных количеств корней
 * @ingroup constants
 */
enum rootsCount
{
    Error = -2,
    InfiniteRoots = -1,
    ZeroRoots = 0,
    OneRoot = 1,
    TwoRoots = 2
};
/**
 * @brief Структура коэффициентов уравнения
 *
 * @details Содержит коэффициенты квадратного уравнения вида ax^2 + bx + c = 0
 */
struct coeff
{
    double a;
    double b;
    double c;
};
/**
 * @brief Структура для хранения корней уравнения
 */

struct roots
{
    double x1;
    double x2;
    rootsCount nroots;
};

struct checkEquation
{
    coeff CheckCoeff;
    roots RightAnswer;
};

rootsCount solve_linear(coeff coeff, roots* roots);
rootsCount solve_quadratic(coeff coeff, roots* roots);
rootsCount num_root(coeff coeff, roots* roots);

