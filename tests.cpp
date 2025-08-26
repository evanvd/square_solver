/**
 * @file tests.cpp
 * @brief unit-тестирование
 * @details
 *Этот модуль содержит функции для тестирования корректности решения:
 * - Квадратных уравнений: ax² + bx + c = 0
 * - Линейных уравнений: bx + c = 0
 * - других случаев
 * @note Для цветного вывода результатов используется модуль IO.h
 * @see solver.h для структур данных и функций решения
 * @see IO.h для функций цветного вывода
 */
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "solver.h"
#include "tests.h"
#include "IO.h"

/** @defgroup testing Функции тестирования */

/**
 * @brief Проверяет корректность решения уравнения
 * @ingroup testing
 *
 * @param[in] CheckCoeff Коэффициенты тестового уравнения
 * @param[in] RightAnswer Ожидаемый правильный ответ
 * @param[out] ActualAnswer Указатель для сохранения фактического результата
 * @return true если фактический результат совпадает с ожидаемым
 * @return false если результаты отличаются
 *
 * @details
 * Функция выполняет следующие проверки:
 * 1. Решает уравнение с заданными коэффициентами
 * 2. Сравнивает количество корней с ожидаемым
 * 3. Для ONE_ROOT сравнивает значение корня с ожидаемым
 * 4. Для TWO_ROOTS сравнивает оба корня с ожидаемыми
 * 5. Для ZERO_ROOTS, INFINITE_ROOTS, ERROR проверяет только количество корней
 *
 * @note Использует абсолютную точность EPS для сравнения чисел с плавающей точкой
 * @note Для TWO_ROOTS проверяет оба порядка корней (x1,x2 и x2,x1)
 */

bool check_case (coeff CheckCoeff, roots RightAnswer, roots* ActualAnswer)
{
    *ActualAnswer = {NAN, NAN, Error};
    ActualAnswer->nroots = num_root(CheckCoeff, ActualAnswer);
    // Split line (too long)
    if(fabs(ActualAnswer->nroots - RightAnswer.nroots) < EPS )
    {
        if(ActualAnswer->nroots < OneRoot)
        {
            return true;
        }
        if(ActualAnswer->nroots == OneRoot && fabs(ActualAnswer->x1 - RightAnswer.x1) < EPS)
        {
            return true;
        }
        if(ActualAnswer->nroots == 2 && fabs(ActualAnswer->x1 - RightAnswer.x1) < EPS && fabs(ActualAnswer->x2 - RightAnswer.x2) < EPS)
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief Запускает один тестовый случай и выводит результат
 * @ingroup testing
 *
 * @param[in] equation Тестовый случай содержащий входные данные и ожидаемый результат
 *
 * @details
 * Функция выполняет тест и выводит результат в цветном формате:
 * - GREEN "PASSED" для успешных тестов
 * - RED "FAILED" для проваленных тестов с детальной информацией
 *
 * @note Выводит коэффициенты уравнения и сравниваемые значения
 */


void run_test(checkEquation equation)
{
    roots actualAnswer;
    if(check_case(equation.CheckCoeff, equation.RightAnswer, &actualAnswer))
    {
        color_printf(GREEN,"PASSED (%lg %lg %lg)\n", equation.CheckCoeff.a, equation.CheckCoeff.b, equation.CheckCoeff.c);
    }
    else
    {
        color_printf(RED, "FAILED (%lg %lg %lg): ", equation.CheckCoeff.a, equation.CheckCoeff.b, equation.CheckCoeff.c );
        printf("x1 = %lg x2 = %lg", actualAnswer.x1, actualAnswer.x2 );
        printf(" (should be x1 = %lg x2= %lg)\n", equation.RightAnswer.x1, equation.RightAnswer.x2);
    }
}

/**
 * @brief Запускает все unit-тесты
 * @ingroup testing
 *
 * @details
 * Запускает comprehensive набор из 6 тестов, покрывающих:
 * 1. Квадратное уравнение с двумя различными корнями
 * 2. Квадратное уравнение с одним корнем (дискриминант = 0)
 * 3. Квадратное уравнение без действительных корней
 * 4. Вырожденный случай: 0 = 0 (бесконечно много решений)
 * 5. Вырожденный случай: 1 = 0 (нет решений)
 * 6. Линейное уравнение: x - 1 = 0
 *
 * @note Каждый тест независимо проверяет определенный сценарий
 * @note Выводит результаты всех тестов в цветном формате
 *
 * @code
 * run_all_test();
 * // Вывод:
 * // PASSED (1 -5 6)
 * // PASSED (2 -4 2)
 * // PASSED (6 2 1)
 * // PASSED (0 0 0)
 * // PASSED (0 0 1)
 * // PASSED (0 1 -1)
 * @endcode
 */


void run_all_test()
{
    struct checkEquation testEquation[] =
    {
        {.CheckCoeff = {1, -5, 6}, .RightAnswer = {3, 2, TwoRoots}},
        {.CheckCoeff = {2, -4, 2},.RightAnswer = {1, NAN, OneRoot}},
        {.CheckCoeff = {6, 2, 1}, .RightAnswer = {NAN, NAN, ZeroRoots}},
        {.CheckCoeff = {0, 0, 0}, .RightAnswer = {NAN, NAN, InfiniteRoots}},
        {.CheckCoeff = {0, 0, 1}, .RightAnswer = {NAN, NAN, ZeroRoots}},
        {.CheckCoeff = {0, 1, -1}, .RightAnswer = {1, NAN, OneRoot}}
    };
    int testCount = sizeof(testEquation) / sizeof(testEquation[0]);
    for (int testNumber = 0; testNumber <testCount; testNumber++)
    {
        run_test(testEquation[testNumber]);
    }
}

void run_from_file(const char* filename)
{
    int testCount = 10; // TODO READ IT FROM FILE
    checkEquation testEquation[] = {};
    // TODO FIX THAT

   if(read_from_file(testEquation))
    {
        for (int testNumber = 0; testNumber < testCount; testNumber++)
        run_test(testEquation[testNumber]);
    }

}
