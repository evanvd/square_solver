#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "solver.h"

rootsCount num_root(coeff coeff, roots* roots)
{
    if (fabs(coeff.a) < EPS)
    {
        return solve_linear(coeff, roots);
    }
    return solve_quadratic(coeff, roots);
}

rootsCount solve_linear( coeff coeff, roots* roots)
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

rootsCount solve_quadratic(coeff coeff, roots* roots)
{
    assert(roots != NULL);
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
