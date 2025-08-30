/**
 * @file IO.h
 * @brief Заголовочный файл модуля ввода-вывода решателя уравнений
 * @details
 * Этот файл содержит объявления функций и структур для модуля ввода-вывода,
 * @see solver.h для определения структур coeff и roots
 */


#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[0;33m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"

enum CompareResult
{
    GREATER = 1,
    LESS = -1,
    EQUAL = 0,
};

/**
 * @brief Выводит цветной текст в терминал
 * @ingroup input_output
 *
 * @param color Цветовой код (RED, GREEN, YELLOW, BLUE)
 * @param format Форматная строка
 * @param ... Аргументы для форматной строки
 */

void color_printf(const char* color, const char* format, ...);


/**
 * @brief Выводит приветственное сообщение
 * @ingroup input_output
 */

void print_welcome();

/**
 * @brief Читает и проверяет коэффициенты уравнения
 * @ingroup input_output
 *
 * @param a Указатель для коэффициента a
 * @param b Указатель для коэффициента b
 * @param c Указатель для коэффициента c
 * @return true если ввод корректен
 * @return false если ввод содержит ошибки
 *
 * @note Проверяет что введены 3 числа
 * @note Проверяет что числа конечные
 * @note Проверяет отсутствие лишних символов
 */

bool scan_check(double* a, double* b, double* c);

/**
 * @brief Выводит корни уравнения в читаемом формате
 * @ingroup input_output
 *
 * @param roots Структура с корнями уравнения
 */

void print_roots(roots roots);

/**
 * @brief Ищет флаг в аргументах командной строки
 * @ingroup input_output
 *
 * @param argc Количество аргументов
 * @param argv Массив аргументов
 * @param flags Искомый флаг
 * @return true если флаг найден
 * @return false если флаг не найден
 */

bool search_flag(int argc, char** argv, const char* flags);

bool read_from_file(checkEquation* Equation []);

void achievement();
