#include <stdio.h>
#include <math.h>
#include <assert.h>

const double EPS = 1e-6;

enum RootsCount
{
    Error = -2,
    InfiniteRoots = -1,
    ZeroRoots = 0,
    OneRoot = 1,
    TwoRoots = 2
};

struct coeff {
    double a;
    double b;
    double c;
};

struct roots {
    double x1;
    double x2;
    enum RootsCount nroots;
};

enum RootsCount solve_linear(struct coeff coeff, struct roots* roots);
enum RootsCount solve_quadratic(struct coeff coeff, struct roots* roots);
enum RootsCount num_root(struct coeff coeff, struct roots* roots);
void print_roots(enum RootsCount nroot, double x1, double x2);
void TestSolve_quadratic();
void TestSolve_linear();

int main()
{
    TestSolve_linear();
    TestSolve_quadratic();

    printf("Введите коэффициенты квадратного уравнения вида ax^2+bx+c:\n ");

    struct coeff coeff = {NAN, NAN, NAN};
    scanf("%lg %lg %lg", &coeff.a, &coeff.b, &coeff.c);

    struct roots roots = {NAN, NAN, Error};
    roots.nroots = num_root(coeff, &roots);

    print_roots(roots.nroots, roots.x1, roots.x2);
    return 0;
}

enum RootsCount num_root(struct coeff coeff, struct roots* roots)
{
    if (fabs(coeff.a) < EPS)
    {
        return solve_linear(coeff, roots);
    }
    return solve_quadratic(coeff, roots);
}

enum RootsCount solve_linear(struct coeff coeff, struct roots* roots)
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

enum RootsCount solve_quadratic(struct coeff coeff, struct roots* roots)
{
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

void print_roots(enum RootsCount nroot, double x1, double x2)
{
    switch(nroot)
    {
        case ZeroRoots:
            printf("Уравнение не имеет решений\n");
            break;
        case OneRoot:
            printf("Уравнение имеет единственное решение: x = %lf\n", x1);
            break;
        case TwoRoots:
            printf("Уравнение имеет два решения: x1 = %lf, x2 = %lf\n", x1, x2);
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

bool checkcase ()
{

}

void TestSolve_quadratic()
{
    struct roots TestRoots;

    // Тест 1: x^2 - 5x + 6 = 0 (корни: 2 и 3)
    struct coeff TestCoeff1 = {1, -5, 6};
    TestRoots.nroots = solve_quadratic(TestCoeff1, &TestRoots);
    if (!(TestRoots.nroots == TwoRoots && fabs(TestRoots.x1 - 3) < EPS && fabs(TestRoots.x2 - 2) < EPS))
    {
        printf("FAILED: solve_quadratic(1 -5 6) -> x1 = %lf, x2 = %lf (should be x1 = 3, x2 = 2)\n",
               TestRoots.x1, TestRoots.x2);
    }

    // Тест 2: 2x^2 - 4x + 2 = 0 (корень: 1)
    struct coeff TestCoeff2 = {2, -4, 2};
    TestRoots.nroots = solve_quadratic(TestCoeff2, &TestRoots);
    if (!(TestRoots.nroots == OneRoot && fabs(TestRoots.x1 - 1) < EPS))
    {
        printf("FAILED: solve_quadratic(2 -4 2) -> x = %lf (should be x = 1)\n", TestRoots.x1);
    }

}

void TestSolve_linear()
{
    struct roots TestRoots;

    // Тест: x - 2 = 0 (корень: 2)
    struct coeff TestCoeff = {0, 1, -2};
    TestRoots.nroots = solve_linear(TestCoeff, &TestRoots);
    if (!(TestRoots.nroots == OneRoot && fabs(TestRoots.x1 - 2) < EPS))
    {
        printf("FAILED: solve_linear(0 1 -2) -> x = %lf (should be x = 2)\n", TestRoots.x1);
    }
}
