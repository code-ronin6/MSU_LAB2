#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define MAX(A, B) (A>B)?A:B
static double EPS1 = 0.001;
static double EPS2 = 0.001;

extern double f1(double x);
extern double f2(double x);
extern double f3(double x);

extern double example1(double x);
extern double example2(double x);

extern double second_der_f1(double x);
extern double second_der_f2(double x);
extern double second_der_f3(double x);

extern double second_der_example1(double x);


double root(double (*f)(double x), double (*g)(double x), double a, double b, double eps1) {
    // method of dividing by two
    double delta = (b - a)/2;
    double new_b = b;
    do {
        // [a, a + (b-a)/2] and [a + (b-a)/2, b]

        new_b = a + delta;
        double F_a = g(a) - f(a);
        double F_b = g(b) - f(b);
        double F_new_b = g(new_b) - f(new_b);

        if (F_a * F_new_b < 0) b = new_b;
        else if (F_new_b * F_b < 0) a = new_b;
        else if (F_new_b == 0) return new_b;
        delta = b - a;
        delta /= 2;
    } while ((b - a) > eps1);


    return (a+b)/2;
}

double integral(double (*f)(double x), double a, double b, double eps2, double max_der_second) { //integral(f, a, b, esp, sup(f''(x)))

    // Kotes for-la
    // the biggest value of der is f''(a) 
    double n = sqrt(fabs(max_der_second*(a - b)/(12*eps2*eps2)));

    double delta = (b - a)/n; //particle

    double res = (f(a) + f(b))/2 * delta;

    for (int i = 1; i < n-1; i++) 
        res += delta * f(a + i*delta);


    return res;
}

int main(void) {
    //printf("first example (must be 1): %lf\n", );
    printf("TEST_1:\n");
    double res = root(example1, example2, 0.99, 3, EPS1);
    if (res <= 1 + EPS1 && res >= 1 - EPS1) printf("Correct!\n\n");
    else printf("Something went wrong!\n\n");

    printf("TEST_2:\nExample1 integral in [1, 4.24]\n");
    res = integral(example1, 1, 4.24, EPS2, second_der_example1(4.24));
    if (res <= 1.44456 + (EPS2*10) && res >= 1.44456 - (EPS2*10)) printf("Correct!\n\n");
    else printf("Something went wrong!\n\n");

    printf("TEST_3:\nRoot for f1 & f2 on [4, 8]\n");
    res = root(f1, f2, 4, 8, EPS1);
    if (res >= 6.096 - (EPS1*10) && res <= 6.096 + (EPS1*10)) printf("Correct!\n\n");
    else printf("Something went wrong!\n\n");

    printf("TEST_4:\nRoot for f2 & f3 on [2, 8]\n");
    res = root(f2, f3, 2.2, 8, EPS1);
    if (res <= 4.225 + (EPS1*10) && res >= 4.225 - (EPS1*10)) printf("Correct!\n\n");
    else printf("Something went wrong!\n\n");

    printf("TEST_5:\nRoot for f1 & f3 on [2.1, 4]\n");
    res = root(f1, f3, 2.1, 4, EPS1);
    if (res <= 2.192 + (EPS1*10) && res >= 2.192 - (EPS1*10)) printf("Correct!\n\n");
    else printf("Something went wrong!\n\n");
    // the pow of 10^(-n) should equal number of decimal points in "answer"


    return 0;

}