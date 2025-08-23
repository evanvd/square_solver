#include <stdio.h>
#include <cmath>


// ⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠛⢉⢉⠉⠉⠻⣿⣿⣿⣿⣿⣿
// ⣿⣿⣿⣿⣿⣿⣿⠟⠠⡰⣕⣗⣷⣧⣀⣅⠘⣿⣿⣿⣿⣿
// ⣿⣿⣿⣿⣿⣿⠃⣠⣳⣟⣿⣿⣷⣿⡿⣜⠄⣿⣿⣿⣿⣿
// ⣿⣿⣿⣿⡿⠁⠄⣳⢷⣿⣿⣿⣿⡿⣝⠖⠄⣿⣿⣿⣿⣿
// ⣿⣿⣿⣿⠃⠄⢢⡹⣿⢷⣯⢿⢷⡫⣗⠍⢰⣿⣿⣿⣿⣿
// ⣿⣿⣿⡏⢀⢄⠤⣁⠋⠿⣗⣟⡯⡏⢎⠁⢸⣿⣿⣿⣿⣿
// ⣿⣿⣿⠄⢔⢕⣯⣿⣿⡲⡤⡄⡤⠄⡀⢠⣿⣿⣿⣿⣿⣿
// ⣿⣿⠇⠠⡳⣯⣿⣿⣾⢵⣫⢎⢎⠆⢀⣿⣿⣿⣿⣿⣿⣿
// ⣿⣿⠄⢨⣫⣿⣿⡿⣿⣻⢎⡗⡕⡅⢸⣿⣿⣿⣿⣿⣿⣿
// ⣿⣿⠄⢜⢾⣾⣿⣿⣟⣗⢯⡪⡳⡀⢸⣿⣿⣿⣿⣿⣿⣿
// ⣿⣿⠄⢸⢽⣿⣷⣿⣻⡮⡧⡳⡱⡁⢸⣿⣿⣿⣿⣿⣿⣿
// ⣿⣿⡄⢨⣻⣽⣿⣟⣿⣞⣗⡽⡸⡐⢸⣿⣿⣿⣿⣿⣿⣿
// ⣿⣿⡇⢀⢗⣿⣿⣿⣿⡿⣞⡵⡣⣊⢸⣿⣿⣿⣿⣿⣿⣿
// ⣿⣿⣿⡀⡣⣗⣿⣿⣿⣿⣯⡯⡺⣼⠎⣿⣿⣿⣿⣿⣿⣿
// ⣿⣿⣿⣧⠐⡵⣻⣟⣯⣿⣷⣟⣝⢞⡿⢹⣿⣿⣿⣿⣿⣿
// ⣿⣿⣿⣿⡆⢘⡺⣽⢿⣻⣿⣗⡷⣹⢩⢃⢿⣿⣿⣿⣿⣿
// ⣿⣿⣿⣿⣷⠄⠪⣯⣟⣿⢯⣿⣻⣜⢎⢆⠜⣿⣿⣿⣿⣿
// ⣿⣿⣿⣿⣿⡆⠄⢣⣻⣽⣿⣿⣟⣾⡮⡺⡸⠸⣿⣿⣿⣿
// ⣿⣿⡿⠛⠉⠁⠄⢕⡳⣽⡾⣿⢽⣯⡿⣮⢚⣅⠹⣿⣿⣿
// ⡿⠋⠄⠄⠄⠄⢀⠒⠝⣞⢿⡿⣿⣽⢿⡽⣧⣳⡅⠌⠻⣿
// ⠁⠄⠄⠄⠄⠄⠐⡐⠱⡱⣻⡻⣝⣮⣟⣿⣻⣟⣻⡺⣊

const double EPS = 1e-6;
enum RootsCount {
    Error = -2,
    InfiniteRoots = -1,
    ZeroRoots = 0,
    OneRoot = 1,
    TwoRoots = 2
};

enum RootsCount solve_linear(double b, double c, double* x1);
enum RootsCount solveQuadratic(double a, double b, double c, double* x1, double* x2);
enum RootsCount num_root(double a, double b, double c, double*x1,double*x2);
void print_roots(enum RootsCount nroot, double x1, double x2);

// TODO asserts

RootsCount solve_linear(double b, double c, double* x1)
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

RootsCount solveQuadratic(double a, double b, double c, double* x1, double* x2)
{
    double d = b*b - 4*a*c;

    if(d < EPS)
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
    return solveQuadratic(a,b,c,x1,x2);
}

void print_roots(enum RootsCount nroot, double x1, double x2)
{
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

int main()
{
    printf("введите кенты квадратного уравнения вида ax^2+bx+c\n ");

    // TODO init with nan
    double a = NAN, b = NAN, c = NAN;
    scanf("%lg%lg%lg", &a, &b, &c);

    double x1 = NAN, x2 = NAN;
    enum RootsCount nroot = num_root(a, b, c, &x1, &x2);

    print_roots(nroot, x1, x2);
    return 0;
}
