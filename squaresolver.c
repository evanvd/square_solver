#include <stdio.h>
#include <cmath>
/*int square_solver(double a, double b, double c, double*x1,double*x2)
{

}*/


int main(void)
{
    printf("введите кенты квадратного уравнения вида ax^2+bx+c\n a:");
    double a=0, b=0,c=0,x1,x2;
    scanf("%lg",&a);
    printf("b: ");
    scanf("%lg",&b);
    printf("c: ");
    scanf("%lg",&c);
    double d = b*b-4*a*c;
    if(d<0)
    {
        printf("нет действительных корней");
    }
    if (d==0)
    {
        x1=-b/(2*a);
        printf("единственный корень %.2f\n",x1);
    }
    if (d>0)
    {
        x1= (-b + sqrt(d))/(2*a);
        x2= (-b - sqrt(d))/(2*a);
        printf("первый корень %.2f\nвторой корень %.2f\n",x1,x2);
    }
    return 0;
}
