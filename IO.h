#include <stdio.h>

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[0;33m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"

void color_printf(const char* color, const char* format, ...);

void print_welcome();

bool scan_check(double* a, double* b, double* c);
void print_roots(roots roots);
bool search_flag(int argc, char** argv, const char* flags);

