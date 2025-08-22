#include <stdio.h>
#include <cmath>
int num_root(double a, double b, double c, double*x1,double*x2)
{

    if (a==0)
    {
        *x1=-c/b;
        return 1;
    }
    else
    {
        double d = b*b-4*a*c;
        if(d < 0)
        {
            return 0;
        }
        if (d==0)
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
}


int main(void)
{
    printf("введите кенты квадратного уравнения вида ax^2+bx+c\n ");
    double a=0, b=0,c=0,x1=0,x2=0;
    scanf("%lg%lg%lg", &a,&b,&c);
    int nroot = num_root(a,b,c,&x1,&x2);
    if (nroot == 0)
    {
        printf("уравнение не имеет решений");
    }
    if (nroot == 1)
    {
        printf("уравнение имеет единственное решение %f ", x1);
    }
    if (nroot == 2 )
    {
     printf("уравнение имеет 2 решения %f %f", x1, x2);
    }
    return 0;
}
