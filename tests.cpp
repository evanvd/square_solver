#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "solver.h"

bool check_case (coeff CheckCoeff, roots RightAnswer, roots* ActualAnswer)
{
    *ActualAnswer = {NAN, NAN, Error};
    ActualAnswer->nroots = num_root(CheckCoeff, ActualAnswer);
    // Split line (too long)
    if(fabs(ActualAnswer->nroots - RightAnswer.nroots) < EPS )
    {
        if(ActualAnswer->nroots < OneRoot)
        {
            return true;
        }
        if(ActualAnswer->nroots == OneRoot && fabs(ActualAnswer->x1 - RightAnswer.x1) < EPS)
        {
            return true;
        }
        if(ActualAnswer->nroots == 2 && fabs(ActualAnswer->x1 - RightAnswer.x1) < EPS && fabs(ActualAnswer->x2 - RightAnswer.x2) < EPS)
        {
            return true;
        }
    }
    return false;
}

void run_test(checkEquation equation)
{
    if(check_case(equation.CheckCoeff, equation.RightAnswer, &equation.ActualAnswer))
    {
        printf("PASSED (%lg %lg %lg)\n", equation.CheckCoeff.a, equation.CheckCoeff.b, equation.CheckCoeff.c);
    }
    else
    {
        printf("FAILED (%lg %lg %lg): ", equation.CheckCoeff.a, equation.CheckCoeff.b, equation.CheckCoeff.c );
        printf("x1 = %lg x2 = %lg", equation.ActualAnswer.x1, equation.ActualAnswer.x2 );
        printf(" (should be x1 = %lg x2= %lg)\n", equation.RightAnswer.x1, equation.RightAnswer.x2);
    }
}

void run_all_test()
{
    struct checkEquation testEquation[] =
    {
        {.CheckCoeff = {1, -5, 6}, .RightAnswer = {3, 2, TwoRoots}},
        {.CheckCoeff = {2, -4, 2},.RightAnswer = {1, NAN, OneRoot}},
        {.CheckCoeff = {6, 2, 1}, .RightAnswer = {NAN, NAN, ZeroRoots}},
        {.CheckCoeff = {0, 0, 0}, .RightAnswer = {NAN, NAN, InfiniteRoots}},
        {.CheckCoeff = {0, 0, 1}, .RightAnswer = {NAN, NAN, ZeroRoots}},
        {.CheckCoeff = {0, 1, -1}, .RightAnswer = {1, NAN, OneRoot}}
    };
    int testCount = sizeof(testEquation) / sizeof(testEquation[0]);
    for (int testNumber = 0; testNumber <testCount; testNumber++)
    {
        run_test(testEquation[testNumber]);
    }
}
