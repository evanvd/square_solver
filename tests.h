/**
 * @file tests.h
 * @brief Заголовочный файл модуля unit-тестирования решателя уравнений
 * @details
 * Этот файл содержит объявления функций и структур для модуля тестирования,
 * который проверяет корректность работы решателя квадратных уравнений.
 * @see solver.h для определения структур coeff и roots
 */
#include <stdio.h>

struct checkEquation
{
    coeff CheckCoeff;
    roots RightAnswer;
};

void run_all_test();
void run_test(checkEquation equation);
bool check_case(coeff CheckCoeff, roots RightAnswer, roots* ActualAnswer);
