#include <stdio.h>

struct checkEquation
{
    coeff CheckCoeff;
    roots RightAnswer;
};

void run_all_test();
void run_test(checkEquation equation);
bool check_case(coeff CheckCoeff, roots RightAnswer, roots* ActualAnswer);
