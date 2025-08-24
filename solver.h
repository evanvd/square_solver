#include <stdio.h>

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
    rootsCount nroots;
};

struct checkEquation
{
    coeff CheckCoeff;
    roots RightAnswer;
    roots ActualAnswer;
};


rootsCount solve_linear(coeff coeff, roots* roots);
rootsCount solve_quadratic(coeff coeff, roots* roots);
rootsCount num_root(coeff coeff, roots* roots);

bool scan_check(double* a, double* b, double* c);
void print_roots(roots roots);
bool search_flag(int argc, char** argv, const char* flags);

void run_all_test();
void run_test(checkEquation equation);
bool check_case (coeff CheckCoeff, roots RightAnswer, roots* ActualAnswer);
