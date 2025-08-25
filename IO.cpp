#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "solver.h"
#include <string.h>
#include "IO.h"
#include <stdarg.h>

void color_printf(const char* color, const char* format, ...)
{
    printf("%s", color);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    printf("%s", RESET);
}

void print_welcome()
{
    color_printf(BLUE, "\t=========================================\n");
    color_printf(BLUE, "\t     РЕШАТЕЛЬ КВАДРАТНЫХ УРАВНЕНИЙ\n");
    color_printf(BLUE, "\t=========================================\n\n");
}

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

bool search_flag(int argc, char** argv, const char* flags)
{
    for (int num_flags = 1; num_flags < argc; num_flags++)
    if (strcmp(argv[num_flags], flags) == 0)
    {
        return true;
    }
    return false;
}

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
