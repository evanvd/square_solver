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
struct coeff{
    double a;
    double b;
    double c;
    };
struct roots{
    double x1;
    double x2;
    enum RootsCount nroots;
};

RootsCount solve_linear(struct coeff coeff, struct roots roots);
RootsCount solve_quadratic(struct coeff coeff, struct roots* roots);
RootsCount num_root(struct coeff coeff, struct roots* roots);
void print_roots(RootsCount nroot, double x1, double x2);
void TestSolve_quadratic();
void TestSolve_linear();



int main()
{
    TestSolve_linear();

    printf("введите кенты квадратного уравнения вида ax^2+bx+c\n ");

    struct coeff coeff = {NAN,NAN,NAN};
    scanf("%lg%lg%lg", &coeff.a, &coeff.b, &coeff.c);

    struct roots roots = {NAN, NAN};
    roots.nroots = num_root(coeff, &roots); // TODO num_root is unclear

    print_roots(roots.nroots, roots.x1, roots.x2);
    return 0;
}

RootsCount num_root(struct coeff coeff, struct roots* roots)
{
    if (fabs(coeff.a) < EPS)
    {
        return solve_linear(coeff,roots);
    }
    return solve_quadratic(coeff,roots);
}

RootsCount solve_linear(struct coeff coeff, struct roots* roots)
{
    /*assert(isfinite(coeff.b));
    assert(isfinite(coeff.c));

    assert(roots.x1 != NULL);*/

    if (fabs(coeff.b) < EPS)
    {
        if (fabs(coeff.c) < EPS)
        {
            return InfiniteRoots;
        }

        if (fabs(coeff.c) > EPS)
        {
            return ZeroRoots;
        }

        return Error;
    }
    else
    {
        roots.x1 = -coeff.c/coeff.b;
        return OneRoot;
    }

    return Error;
}

RootsCount solve_quadratic(struct coeff coeff, struct roots* roots)
{
    assert(isfinite(coeff.a));
    assert(isfinite(coeff.b));
    assert(isfinite(coeff.c));

    assert(roots.x1 != NULL);
    assert(roots.x2 != NULL);
    assert(roots.x1 != roots.x2);

    double d = coeff.b*coeff.b - 4*coeff.a*coeff.c;

    if(d < -EPS)
    {
        return ZeroRoots;
    }

    if (fabs(d) < EPS)
    {
        *roots.x1= -coeff.b/(2*coeff.a);
        return OneRoot;
    }

    if (d > EPS)
    {

        *roots.x1 = (-coeff.b + sqrt(d))/(2*coeff.a);
        *roots.x2 = (-coeff.b - sqrt(d))/(2*coeff.a);
        return TwoRoots;
    }

    return Error;
}



void print_roots(RootsCount nroot, double x1, double x2)
{
   switch(nroot)
   {
    case ZeroRoots:
        printf("уравнение имеет 2 решения %lf %lf", x1, x2);
        break;
    case OneRoot:
        printf("уравнение имеет единственное решение %lf ", x1);
        break;
    case TwoRoots:
        printf("уравнение имеет 2 решения %lf %lf", x1, x2);
        break;
    case InfiniteRoots:
        printf("уравнение имеет 2 решения %lf %lf", x1, x2);
        break;
   }
}

void TestSolve_quadratic()
{
    struct roots TestRoots;
    struct coeff TestCoeff = {1,-5,6};
    TestRoots.nroots = solve_quadratic(TestCoeff, TestRoots); // 2,3
    if (!(nroots == TwoRoots && fabs(roots.x1-3) < EPS && fabs(roots.x2-2) < EPS ))
    {
        printf("FAILED: solve_quadratic(1 -5 6)-> 2, x1 = %lf, x2 = %lf (should be x1 = 2, x2 = 3)", x1, x2);
    }
    nroots = solve_quadratic(2, -4, 2, TestRoots);
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
