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
struct coeff
{
    double a;
    double b;
    double c;
}

enum RootsCount solve_linear(double b, double c, double* x1);
enum RootsCount solve_quadratic(double a, double b, double c, double* x1, double* x2);
enum RootsCount num_root(double a, double b, double c, double*x1,double*x2);
void print_roots(enum RootsCount nroot, double x1, double x2);
void TestSolve_quadratic();
void TestSolve_linear();

int main()
{
    TestSolve_linear();

    printf("введите кенты квадратного уравнения вида ax^2+bx+c\n ");

    double a = NAN, b = NAN, c = NAN;
    scanf("%lg%lg%lg", &a, &b, &c);

    double x1 = NAN, x2 = NAN;
    RootsCount nroot = num_root(a, b, c, &x1, &x2); // TODO num_root is unclear

    print_roots(nroot, x1, x2);
    return 0;
}

void TestSolve_quadratic()
{
    double x1 = 0, x2 = 0 ;
    RootsCount nroots = solve_quadratic(1, -5, 6, &x1, &x2); // 2,3
    if (!(nroots == TwoRoots && fabs(x1-3) < EPS && fabs(x2-2) < EPS ))
    {
        printf("FAILED: solve_quadratic(1 -5 6)-> 2, x1 = %lf, x2 = %lf (should be x1 = 2, x2 = 3)", x1, x2);
    }
    nroots = solve_quadratic(2, -4, 2, &x1, &x2);
    if (!(nroots == OneRoot && fabs(x1-1) < EPS ))
    {
        printf("FAILED: solve_quadratic(1 -5 6)-> 2, x1 = %lf, x2 = %lf (should be x1 = 2, x2 = 3)", x1, x2);
    }

    /*
    if (!checkCase(coeffs, rightAnswer, &actualAnswer)) {
        printTestFail(coeffs, rightAnswer, actualAnswer);
    }
    */
}

void TestSolve_linear()
{
    double x1 = 0;
    RootsCount nroots = solve_linear(1, -2, &x1); // 2
    if (!(nroots == OneRoot && fabs(x1-2) < EPS ))
    {
        printf("FAILED: solve_linear(1 -2), x = %lf(should be x = 2)", x1);
    }

}

RootsCount solve_linear(double b, double c, double* x1)
{
    assert(std::isfinite(b)); // TODO do not use std namespace
    assert(std::isfinite(c));

    assert(x1 != NULL);

    if (fabs(b) < EPS)
    {
        if (fabs(c) < EPS)
        {
            return InfiniteRoots;
        }

        if (fabs(c) > EPS)
        {
            return ZeroRoots;
        }

        return Error;
    }
    else
    {
        *x1 = -c/b;
        return OneRoot;
    }

    return Error;
}

RootsCount solve_quadratic(double a, double b, double c, double* x1, double* x2)
{
    assert(std::isfinite(a)); // TODO
    assert(std::isfinite(b));
    assert(std::isfinite(c));

    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);

    double d = b*b - 4*a*c;

    if(d < -EPS)
    {
        return ZeroRoots;
    }

    if (fabs(d) < EPS)
    {
        *x1= -b/(2*a);
        return OneRoot;
    }

    if (d > EPS)
    {

        *x1 = (-b + sqrt(d))/(2*a);
        *x2 = (-b - sqrt(d))/(2*a);
        return TwoRoots;
    }

    return Error;
}

RootsCount num_root(double a, double b, double c, double*x1,double*x2)
{
    if (fabs(a) < EPS)
    {
        return solve_linear(b,c,x1);
    }
    return solve_quadratic(a,b,c,x1,x2);
}

void print_roots(enum RootsCount nroot, double x1, double x2)
{
    // TODO use switch
    if (nroot == ZeroRoots)
    {
        printf("уравнение не имеет решений");
    }
    if (nroot == OneRoot)
    {
        printf("уравнение имеет единственное решение %lf ", x1);
    }
    if (nroot == TwoRoots)
    {
     printf("уравнение имеет 2 решения %lf %lf", x1, x2);
    }
    if (nroot == InfiniteRoots)
    {
        printf("бесконечное количество решений");
    }
}

// TODO main should be placed first

