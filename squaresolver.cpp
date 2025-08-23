#include <stdio.h>
#include <math.h>
#include <assert.h>

const double EPS = 1e-6;

// TODO naming style
enum RootsCount
{
    Error = -2,
    InfiniteRoots = -1,
    ZeroRoots = 0,
    OneRoot = 1,
    TwoRoots = 2
};

struct coeff { // TODO move { to next line
    double a;
    double b;
    double c;
};

struct roots { // TODO move { to next line
    double x1;
    double x2;
    enum RootsCount nroots;
};

RootsCount solve_linear(struct coeff coeff, struct roots* roots);
RootsCount solve_quadratic(struct coeff coeff, struct roots* roots);
RootsCount num_root(struct coeff coeff, struct roots* roots);
void print_roots(struct roots roots);
void TestSolve_quadratic();
void TestSolve_linear();
bool checkcase (struct coeff CheckCoeff, struct roots RightAnswer, struct roots* ActualAnswer);

int main(int argc, char **argv)
{
    //TestSolve_linear();
    //TestSolve_quadratic();

    printf("Введите коэффициенты квадратного уравнения вида ax^2+bx+c:\n ");

    struct coeff coeff = {NAN, NAN, NAN};
    scanf("%lg %lg %lg", &coeff.a, &coeff.b, &coeff.c);

    struct roots roots = {NAN, NAN, Error};
    roots.nroots = num_root(coeff, &roots);

    print_roots(roots);
    return 0;
}

RootsCount num_root(struct coeff coeff, struct roots* roots)
{
    if (fabs(coeff.a) < EPS)
    {
        return solve_linear(coeff, roots);
    }
    return solve_quadratic(coeff, roots);
}

RootsCount solve_linear(struct coeff coeff, struct roots* roots)
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

RootsCount solve_quadratic(struct coeff coeff, struct roots* roots)
{
    // assert on roots != NULL
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
            printf("Ошибка в вычислениях\n");
            break;
        default:
            printf("Неизвестный тип решения\n");
            break;
    }
}
// TODO blank line

// TODO split words in name
bool checkcase (struct coeff CheckCoeff, struct roots RightAnswer, struct roots* ActualAnswer)
{
    *ActualAnswer = {NAN, NAN, Error};
    ActualAnswer->nroots = num_root(CheckCoeff, ActualAnswer);
    // Split line (too long)
    if(fabs(ActualAnswer->nroots - RightAnswer.nroots) < EPS && (ActualAnswer->x1 - RightAnswer.x1) < EPS && (ActualAnswer->x2 - RightAnswer.x2) < EPS)
    {
        return 1; // true
    }
    return 0; // false
}
// TODO remove lines
//

// NAMING CASES:
// camelCase
// PascalCase
// snake_case
// kebab-case -- not available in C

// TODO test_solve_quadratic
void TestSolve_quadratic()
{
    // Тест 1: x^2 - 5x + 6 = 0 (корни: 2 и 3)
    struct coeff TestCoeff = {1, -5, 6};
    struct roots TestRoots = {2, 3, TwoRoots};
    struct roots Answer = {NAN, NAN, Error};
    if (!(checkcase(TestCoeff,TestRoots,&Answer)))
    {
        // TODO separate function
        printf("FAILED: solve_quadratic(1 -5 6) -> x1 = %lf, x2 = %lf (should be x1 = 3, x2 = 2)\n",Answer.x1, Answer.x2);
    }
    // Тест 2: 2x^2 - 4x + 2 = 0 (корень: 1)
    TestCoeff = {2, -4, 2};
    TestRoots = {2, 3, OneRoot};
    if (!(checkcase(TestCoeff,TestRoots,&Answer)))
    {
        printf("FAILED: solve_quadratic(2 -4 2) -> x1 = %lf, x2 =%lf (should be x = 1)\n",Answer.x1, Answer.x2);
    }
    TestCoeff = {6, 1, 2};
    TestRoots = {2, 3, ZeroRoots};
    if (!(checkcase(TestCoeff,TestRoots,&Answer)))
    {
        printf("FAILED: solve_quadratic(6 1 2) -> x1 = %lf, x2 = %lf (should be No Roots)\n",Answer.x1, Answer.x2);

    }

}
