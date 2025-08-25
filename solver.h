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


// TODO add docs
rootsCount solve_linear(coeff coeff, roots* roots);
rootsCount solve_quadratic(coeff coeff, roots* roots);
rootsCount num_root(coeff coeff, roots* roots);

