#include <stdio.h>
#include <math.h>
#include <assert.h>


const double EPS = 1e-6;

enum rootsCount
{
    Error = -2,
    InfiniteRoots = -1,
    ZeroRoots = 0,
    OneRoot = 1,
    TwoRoots = 2
};

struct coeff
{
    double a;
    double b;
    double c;
};

struct roots
{
    double x1;
    double x2;
    enum rootsCount nroots;
};

struct checkEquation
{
    struct coeff CheckCoeff;
    struct roots RightAnswer;
    struct roots ActualAnswer;
};


rootsCount solve_linear(struct coeff coeff, struct roots* roots);
rootsCount solve_quadratic(struct coeff coeff, struct roots* roots);
rootsCount num_root(struct coeff coeff, struct roots* roots);
void print_roots(struct roots roots);

void run_test();
void print_test(checkEquation equation);
bool check_case (struct coeff CheckCoeff, struct roots RightAnswer, struct roots* ActualAnswer);


int main(char **argv)
{
    //if (argv[1] == "test")
    {
        run_test();
    }
    //printf(argv[1],"\n");
    printf("Введите коэффициенты квадратного уравнения вида ax^2+bx+c:\n ");

    struct coeff coeff = {NAN, NAN, NAN};
    scanf("%lg %lg %lg", &coeff.a, &coeff.b, &coeff.c);

    struct roots roots = {NAN, NAN, Error};
    roots.nroots = num_root(coeff, &roots);

    print_roots(roots);
    return 0;
}


rootsCount num_root(struct coeff coeff, struct roots* roots)
{
    if (fabs(coeff.a) < EPS)
    {
        return solve_linear(coeff, roots);
    }
    return solve_quadratic(coeff, roots);
}

rootsCount solve_linear(struct coeff coeff, struct roots* roots)
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

rootsCount solve_quadratic(struct coeff coeff, struct roots* roots)
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

void print_roots(struct roots roots) // struct keyword not needed
{
    switch(roots.nroots)
    {
        case ZeroRoots:
            printf("Уравнение не имеет решений\n");
            break;
        case OneRoot:
            printf("Уравнение имеет единственное решение: x = %lf\n", roots.x1);
            break;
        case TwoRoots:
            printf("Уравнение имеет два решения: x1 = %lf, x2 = %lf\n", roots.x1, roots.x2);
            break;
        case InfiniteRoots:
            printf("Уравнение имеет бесконечно много решений\n");
            break;
        case Error:
            printf("ERROR\n");
            break;
        default:
            break;
    }
}
// TODO blank line

bool check_case (struct coeff CheckCoeff, struct roots RightAnswer, struct roots* ActualAnswer)
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
// TODO remove lines
// NAMING CASES:
// camelCase
// PascalCase
// snake_case
// kebab-case -- not available in C
void print_test(checkEquation equation)
{
    if(check_case(equation.CheckCoeff, equation.RightAnswer, &equation.ActualAnswer))
    {
        printf("PASSED (%lg %lg %lg)\n", equation.CheckCoeff.a, equation.CheckCoeff.b, equation.CheckCoeff.c);
    }
    else
    {
        printf("FAILED (%lg %lg %lg): ", equation.CheckCoeff.a, equation.CheckCoeff.b, equation.CheckCoeff.c );
        printf("x1 = %lg x2 = %lg", equation.ActualAnswer.x1, equation.ActualAnswer.x2 );
        printf(" (should be x1 = %lg x2= %lg)\n", equation.RightAnswer.x1, equation.RightAnswer.x2);
    }
}

void run_test()
{
    struct checkEquation TestEquation[] =
    {
        {.CheckCoeff = {1, -5, 6}, .RightAnswer = {3, 2, TwoRoots}},
        {.CheckCoeff = {2, -4, 2},.RightAnswer = {1, NAN, OneRoot}},
        {.CheckCoeff = {6, 2, 1}, .RightAnswer = {NAN, NAN, ZeroRoots}},
        {.CheckCoeff = {0, 0, 0}, .RightAnswer = {NAN, NAN, InfiniteRoots}},
        {.CheckCoeff = {0, 0, 1}, .RightAnswer = {NAN, NAN, ZeroRoots}},
        {.CheckCoeff ={0, 1, -1}, .RightAnswer = {1, NAN, OneRoot}}
    };
    for (int i = 0; i < 6; i++)
    {
        print_test(TestEquation[i]);
    }
}
