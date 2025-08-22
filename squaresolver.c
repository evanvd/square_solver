#include <stdio.h>
#include <cmath>


const double EPS = 1e-6;
enum RootsCount {
Error = -2,
InfiniteRoots = -1,
ZeroRoots = 0,
OneRoot = 1,
TwoRoots = 2
};
enum RootsCount solve_linear(double b, double c, double* x1);
enum RootsCount solveQuadratic (double a, double b, double c, double* x1, double* x2);
enum RootsCount num_root(double a, double b, double c, double*x1,double*x2);


enum RootsCount solve_linear(double b, double c, double* x1)
{
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

enum RootsCount solveQuadratic (double a, double b, double c, double* x1, double* x2)
{

    double d = b*b-4*a*c;
    if(d < 0)
    {
        return ZeroRoots;
    }
    if (fabs(d) < EPS)
    {
        *x1= -b/(2*a);
        return OneRoot;
    }
    if (d > 0)
    {
        *x1 = (-b + sqrt(d))/(2*a);
        *x2 = (-b - sqrt(d))/(2*a);
        return TwoRoots;
    }
    return Error;
}

// TODO blank line
enum RootsCount num_root(double a, double b, double c, double*x1,double*x2)
{
    if (fabs(a) < EPS)
    {
        return solve_linear(b,c,x1);
    }
    else
    {
        return solveQuadratic(a,b,c,x1,x2);
    }
}


int main()
{
    printf("введите кенты квадратного уравнения вида ax^2+bx+c\n ");

    double a = 0, b = 0, c = 0, x1 = 0, x2 = 0;
    scanf("%lg%lg%lg", &a,&b,&c);

    enum RootsCount nroot = num_root(a,b,c,&x1,&x2);

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

    return 0;
}
