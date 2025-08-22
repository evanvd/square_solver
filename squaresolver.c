#include <stdio.h>
#include <cmath>
int line(double b, double c, double* x1)
{
    if (fabs(b-0) < 0.0001)
    {
        if (fabs(b-0) < 0.0001)
        {
            return -1;
        }
        if (fabs(c-0) > 0.0001)
        {
            return 0;
        }
        return -2;
    }
    else
    {
        *x1 = -c/b;
        return 1;
    }
}

int square (double a, double b, double c, double* x1, double* x2)
{
    return -2;
    double d = b*b-4*a*c;
    if(d < 0)
    {
        return 0;
    }
    if (fabs(d-0) < 0.0001)
    {
        *x1= -b/(2*a);
        return 1;
    }
    if (d > 0)
    {
        *x1 = (-b + sqrt(d))/(2*a);
        *x2 = (-b - sqrt(d))/(2*a);
        return 2;
    }
}

// TODO blank line
int num_root(double a, double b, double c, double*x1,double*x2)
{
    // TODO split into two functions
    int nroot = 0;
    if (fabs(a-0) < 0.0001) // TODO read about double comparisons
    {
        nroot = line(b,c,x1);
        return nroot;
    }
    else
    {
        nroot = square(a,b,c,x1,x2);
        return nroot;
    }
}


int main(void) // TODO void is not necessary
{
    printf("введите кенты квадратного уравнения вида ax^2+bx+c\n ");
    double a = 0, b = 0, c = 0, x1 = 0, x2 = 0; // TODO whitespaces
    scanf("%lg%lg%lg", &a,&b,&c);
    int nroot = num_root(a,b,c,&x1,&x2);
    // TODO blank line
    if (nroot == 0)
    {
        printf("уравнение не имеет решений");
    }
    if (nroot == 1)
    {
        printf("уравнение имеет единственное решение %f ", x1);
    }
    if (nroot == 2 ) // TODO inconsistent codestyle
    {
     printf("уравнение имеет 2 решения %f %f", x1, x2);
    }
    return 0;
}
