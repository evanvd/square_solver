/**
 * @file tests.h
 * @brief Заголовочный файл модуля unit-тестирования решателя уравнений
 * @details
 * Этот файл содержит объявления функций и структур для модуля тестирования,
 * который проверяет корректность работы решателя квадратных уравнений.
 * @see solver.h для определения структур coeff и roots
 */
void run_from_file(const char* filename);
bool read_from_file(checkEquation * Equation, const char* filename, size_t* size);
void run_embedded_test();
void run_test(checkEquation equation);
bool check_solution(coeff CheckCoeff, roots RightAnswer, roots* ActualAnswer);
