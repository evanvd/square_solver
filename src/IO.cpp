/**
 * @file IO.cpp
 * @brief Модуль ввода-вывода для решателя квадратных уравнений
 * @details
 * Этот модуль предоставляет функции для:
 * - Цветного вывода в терминал
 * - Ввода и валидации коэффициентов уравнения
 * - Обработки аргументов командной строки
 * - Вывода результатов решения уравнений
 *  @note Для работы с цветным выводом используются ANSI escape codes
 *  @see solver.h для структур данных и констант
 */


#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "solver.h"
#include <stdarg.h>
#include <string.h>
#include "IO.h"

/**
 * @brief Выводит цветной текст в терминал
 * @ingroup input_output
 *
 * @param[in] color Цветовой код (RED, GREEN, YELLOW, BLUE, RESET)
 * @param[in] format Форматная строка в стиле printf
 * @param[in] ... Переменное количество аргументов для форматирования
 *
 * @note Использует variadic functions для поддержки форматирования
 * @note Автоматически сбрасывает цвет после вывода
 *
 */
void color_printf(const char* color, const char* format, ...)
{

    printf("%s", color);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    printf("%s", RESET);
}

/**
 * @brief Выводит приветственное сообщение программы
 * @ingroup input_output
 *
 * @details
 * Отображает красивый заголовок программы с использованием цветного вывода.
 * Сообщение включает название программы и разделители для улучшения читаемости.
 */

void print_welcome()
{
    color_printf(BLUE, "\t=========================================\n");
    color_printf(BLUE, "\t     РЕШАТЕЛЬ КВАДРАТНЫХ УРАВНЕНИЙ\n");
    color_printf(BLUE, "\t=========================================\n\n");
}
/**
 * @brief Читает и проверяет коэффициенты уравнения
 * @ingroup input_output
 *
 * @param[out] a  коэффициент a
 * @param[out] b  коэффициент b
 * @param[out] c  коэффициент c
 * @return true - коэффициенты успешно прочитаны
 * @return false - ввод содержит ошибки
 *
 * @note При обнаружении лишних символов выводит предупреждение, но возвращает true
 * @note При нечисловом вводе выводит ошибку и возвращает false
 */

bool scan_check(double* a, double* b, double* c)
{
    scanf("%lg %lg %lg", a, b, c);

    if (!isfinite(*a) || !isfinite(*b) || !isfinite(*c))
    {
        color_printf(RED, "Error: Non-numeric values entered\n");
        return false;
    }

    int next_char = getchar();
    if (next_char == '\n' || next_char == EOF)
    {
        return true;
    }

    else
    {
        color_printf(YELLOW, "Предупреждение: после чисел обнаружены лишние символы\n");
        while (getchar() != '\n');
        return true;
    }

    return false;
}

/**
 * @brief Ищет флаг в аргументах командной строки
 * @ingroup input_output
 *
 * @param[in] argc Количество аргументов командной строки
 * @param[in] argv Массив аргументов командной строки
 * @param[in] flags Искомый флаг (например, "--test")
 * @return true - флаг найден
 * @return false - флаг не найден
 *
 * @details
 * Функция ищет точное совпадение флага в массиве аргументов,
 */

bool search_flag(int argc, char** argv, const char* flags)
{
    for (int num_flags = 1; num_flags < argc; num_flags++)
    if (strcmp(argv[num_flags], flags) == 0)
    {
        return true;
    }
    return false;
}

/**
 * @brief Выводит корни уравнения с цветовой подсветкой
 * @ingroup input_output
 *
 * @param[in] roots Структура содержащая корни уравнения и информацию о их количестве
 *
 * @details
 * В зависимости от количества корней выводит соответствующее сообщение:
 * - ZeroRoots: сообщение об отсутствии решений (зеленый)
 * - OneRoot: одно решение с значением (зеленый)
 * - TwoRoots: два решения с значениями (зеленый)
 * - InfiniteRoots: сообщение о бесконечном числе решений (зеленый)
 * - Error: сообщение об ошибке вычислений (красный)
 *
 * @note Использует цветовой вывод для улучшения читаемости
 * @note Для неизвестного типа решения вывод отсутствует
 */

void print_roots(roots roots)
{
    switch(roots.nroots)
    {
        case ZeroRoots:
            color_printf( GREEN, "Уравнение не имеет решений\n");
            break;
        case OneRoot:
            color_printf(GREEN, "Уравнение имеет единственное решение: x = %lf\n", roots.x1);
            break;
        case TwoRoots:
            color_printf(GREEN, "Уравнение имеет два решения: x1 = %lf, x2 = %lf\n", roots.x1, roots.x2);
            break;
        case InfiniteRoots:
            color_printf(GREEN, "Уравнение имеет бесконечно много решений\n");
            break;
        case Error:
            color_printf(RED, "ERROR\n");
            break;
        default:
            break;
    }
}

void achievement()
{

    color_printf(BLUE, " ▄▄                              ▟▘                                               \n");
    color_printf(BLUE, "▝ ▝▌ ▄▖ ▗ ▗  ▄▖ ▗  ▖    ▗▄▄  ▄▖ ▐▄▖  ▄▖      ▄▖ ▗▄▄  ▄▖     ▗▄▄ ▗▄▖  ▄▖  ▄▄  ▄▖   \n");
    color_printf(BLUE, " ▗▄▘▝ ▐ ▐ ▐ ▐▘▐ ▐▌▐▌     ▐  ▐▘▐ ▐▘▜ ▐▘▐     ▝ ▜  ▐  ▝ ▐     ▐ ▐ ▐▘▜ ▐▘▜  ▌  ▝ ▐   \n");
    color_printf(BLUE, "  ▝▌▗▀▜ ▝▄▟ ▐▀▀ ▐▐▌▌     ▐  ▐▀▀ ▐ ▐ ▐▀▀      ▀▜  ▐  ▗▀▜     ▐ ▐ ▐ ▐ ▐ ▐  ▌  ▗▀▜   \n");
    color_printf(BLUE, "▝▄▟▘▝▄▜   ▐ ▝▙▞ ▐  ▌     ▐  ▝▙▞ ▝▙▛ ▝▙▞     ▝▄▛  ▐  ▝▄▜     ▐ ▐ ▐▙▛ ▝▙▛  ▌  ▝▄▜  ▐\n");
    color_printf(BLUE, "                                                                ▐                ▘\n");
    color_printf(BLUE, "                                                                ▝                 \n");

    color_printf(GREEN, " ▄▖  ▄▖ ▗▄▄ ▗ ▗     ▗▄▄ ▗  ▖     ▄▖  ▄▖ ▗  ▖    ▗▄▖  ▄▖ ▗▗▗ ▗ ▗ ▗▄▄\n");
    color_printf(GREEN, "▐▘▐ ▐▘▝ ▐ ▐ ▐ █      ▐  ▐  ▌    ▐▘▝ ▝ ▐ ▐▌▐▌    ▐▘▜ ▐▘▐ ▐▐▐ ▐ █ ▐ ▐\n");
    color_printf(GREEN, "▐▀▀ ▐   ▐ ▐ ▐▐▐      ▐  ▐▀▖▌    ▐   ▗▀▜ ▐▐▌▌    ▐ ▐ ▐▀▀ ▐▐▐ ▐▐▐ ▐ ▐\n");
    color_printf(GREEN, "▝▙▞ ▝▙▞ ▞ ▐ ▐▘▐      ▐  ▐▄▘▌    ▝▙▞ ▝▄▜ ▐  ▌    ▐▙▛ ▝▙▞ ▐▟▟ ▐▘▐ ▞ ▐\n");
    color_printf(GREEN, "                                                ▐                  \n");
    color_printf(GREEN, "                                                ▝                  \n");


    color_printf(RED,"▗▄   ▄▄  ▄▄  ▄▄                                      ▚▞  ▗▄ \n");
    color_printf(RED," ▐  ▗▘▝▖▗▘▝▖▗▘▝▖    ▗ ▗ ▗▄▖  ▄▖ ▗▄▖ ▗ ▗  ▄▖ ▗ ▗ ▗ ▗ ▗ ▗  ▘ ▌\n");
    color_printf(RED," ▐  ▐ ▖▌▐ ▖▌▐ ▖▌    ▝▖▞ ▐▘▜ ▝ ▐ ▐ ▐ ▐ ▐ ▐▘▐ ▐ ▐ ▐ █ ▐ █  ▗▛ \n");
    color_printf(RED," ▐  ▐  ▌▐  ▌▐  ▌     ▙▌ ▐ ▐ ▗▀▜ ▐▀▚ ▐▀▜ ▐▀▀ ▐▀▜ ▐▐▐ ▐▐▐  ▝  \n");
    color_printf(RED,"▗▟▄  ▙▟  ▙▟  ▙▟      ▜  ▐▙▛ ▝▄▜ ▐▄▞ ▐ ▐ ▝▙▞ ▐ ▐ ▐▘▐ ▐▘▐  ▐  \n");
    color_printf(RED,"                     ▞  ▐                                   \n");
    color_printf(RED,"                    ▝▘  ▝                                   \n");

    color_printf(GREEN,"⢀⡴⠑⡄⠀⠀⠀⠀⠀⠀⠀⣀⣀⣤⣤⣤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    color_printf(GREEN,"⠸⡇⠀⠿⡀⠀⠀⠀⣀⡴⢿⣿⣿⣿⣿⣿⣿⣿⣷⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    color_printf(GREEN,"⠀⠀⠀⠀⠑⢄⣠⠾⠁⣀⣄⡈⠙⣿⣿⣿⣿⣿⣿⣿⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀\n");
    color_printf(GREEN,"⠀⠀⠀⠀⢀⡀⠁⠀⠀⠈⠙⠛⠂⠈⣿⣿⣿⣿⣿⠿⡿⢿⣆⠀⠀⠀⠀⠀⠀⠀\n");
    color_printf(GREEN,"⠀⠀⠀⢀⡾⣁⣀⠀⠴⠂⠙⣗⡀⠀⢻⣿⣿⠭⢤⣴⣦⣤⣹⠀⠀⠀⢀⢴⣶⣆\n");
    color_printf(GREEN,"⠀⠀⢀⣾⣿⣿⣿⣷⣮⣽⣾⣿⣥⣴⣿⣿⡿⢂⠔⢚⡿⢿⣿⣦⣴⣾⠁⠸⣼⡿\n");
    color_printf(GREEN,"⠀⢀⡞⠁⠙⠻⠿⠟⠉⠀⠛⢹⣿⣿⣿⣿⣿⣌⢤⣼⣿⣾⣿⡟⠉⠀⠀⠀⠀⠀\n");
    color_printf(GREEN,"⠀⣾⣷⣶⠇⠀⠀⣤⣄⣀⡀⠈⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀\n");
    color_printf(GREEN,"⠀⠉⠈⠉⠀⠀⢦⡈⢻⣿⣿⣿⣶⣶⣶⣶⣤⣽⡹⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀\n");
    color_printf(GREEN,"⠀⠀⠀⠀⠀⠀⠀⠉⠲⣽⡻⢿⣿⣿⣿⣿⣿⣿⣷⣜⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀\n");
    color_printf(GREEN,"⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣷⣶⣮⣭⣽⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀\n");
    color_printf(GREEN,"⠀⠀⠀⠀⠀⠀⣀⣀⣈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇⠀⠀⠀⠀⠀⠀⠀\n");
    color_printf(GREEN,"⠀⠀⠀⠀⠀⠀⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀\n");
    color_printf(GREEN,"⠀⠀⠀⠀⠀⠀⠀⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    color_printf(GREEN,"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠻⠿⠿⠿⠿⠛⠉\n");
}
