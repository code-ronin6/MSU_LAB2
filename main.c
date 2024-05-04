#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>

#define MAX(A, B) (A>B)?A:B
#define MIN(A, B) (A<B)?A:B

static int iterations = 0;
static int iterations_[3] = {0};

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

// the pow of 10^(-n) should equal number of decimal points in "answer"
double root(double (*f)(double x), double (*g)(double x), double a, double b, double eps1) {
    iterations = 0;
    // method of dividing by two
    double delta = (b - a)/2;
    double new_b = b;
    do {
        // [a, a + (b-a)/2] and [a + (b-a)/2, b]
        iterations++;
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

    n = (!n) ? 1:n; //if max_der_second is 0, we have stright line, it has special formula for it's square

    double delta = (b - a)/n; //particle

    double res = (f(a) + f(b))/2 * delta;

    for (int i = 1; i < n-1; i++) 
        res += delta * f(a + i*delta);


    return res;
}
//TODO: change logic of -R and -I keys

//calculates roots and counts iterations
//you can't get number of iterations without getting roots!
void script_roots() {
    double res = 0;
    res = root(f1, f2, 4, 8, EPS1);
    printf("Root intersection points of f1 and f2 in [4, 8]\nx = %lf\n", res);
    if (res >= 6.096 - (EPS1*10) && res <= 6.096 + (EPS1*10)) {
        printf("Correct!\n\n");
    }
    else printf("Something went wrong!\n\n");


    iterations_[0] = iterations;

    res = root(f2, f3, 2.2, 8, EPS1);
    printf("Root intersection points of f2 and f3 in [2.2, 8]\nx = %lf\n", res);
    if (res <= 4.225 + (EPS1*10) && res >= 4.225 - (EPS1*10)) {
        printf("Correct!\n\n");
    }
    else printf("Something went wrong!\n\n");
    iterations_[1] = iterations;

    res = root(f1, f3, 2.1, 4, EPS1);
    printf("Root intersection points of f1 and f3 in [2.1, 4]\nx = %lf\n", res);
    if (res <= 2.192 + (EPS1*10) && res >= 2.192 - (EPS1*10)) {
        printf("Correct!\n\n");
    }
    else printf("Something went wrong!\n\n");
    iterations_[2] = iterations;
}

void count_iterations(void) {
    printf("Для вычисления первого корня понадобилось: %d итераций\n", iterations_[0]);
    printf("Для вычисления второго корня понадобилось: %d итераций\n", iterations_[1]);
    printf("Для вычисления третьего корня понадобилось: %d итераций\n\n", iterations_[2]);
}

void inf(void) {
    printf("Работу выполнил Хворов Андрей, 106 группа\n");
    printf("Вариант задания x x x x\n");
    printf("Как использовать:\n");
    printf("-H (--help) - Помощь, справка\n");
    printf("-R (--root) - Получить точки пересечения графиков функции, заданных вариантом задания\n");
    printf("-I (--iterations) - Количество итераций, потребовавшихся для примерного вычисления корней\n");
    printf("-A (--ans) - Вычислить площадь фигуры, определенной вариантом задания\n");
    printf("--testroot - Вычислить точку пересечения заданной функции (из трех, предусмторенных заданием)\nКак использовать: <Номер функции f> <Номер функции g> <a> <b> <eps1>\n");
    printf("--testintegral - Вычислить интеграл заданной функции (из трех, предусмотренных заданием)\nКак использовать: <Номер функции f> <a> <b> <eps2>\n");
}

void final_integral_script(void) {
    double x1 = root(f1, f3, 2.1, 4, EPS1);
    double x2 = root(f2, f3, 2.2, 8, EPS1);
    double x3 = root(f1, f2, 4, 8, EPS1);

    double s = integral(f3, x1, x2, EPS2, MAX(second_der_f3(x1), second_der_f3(x2)));

    s += integral(f2, x2, x3, EPS2, MAX(second_der_f2(x3), second_der_f2(x2)));

    s -= integral(f1, x1, x3, EPS2, MAX(second_der_f1(x3), second_der_f1(x1)));

    printf("The square is: %lf\n\n", s);

    if (s <= 11.236 + (100*EPS2) && s >= 11.236 - (100*EPS2)) printf("Correct!\n\n");
    else printf("Something went worng...\n\n");
}

void test_root(int fnum, int gnum, double a, double b, double eps1) {
    if (fnum == 1) {
        if (gnum == 2) {
            double res = root(f1, f2, a, b, eps1);
            printf("Root for function f1 - f2 = 0: %lf\n\n", res);
        }
        else if (gnum == 3) {
            double res = root(f1, f3, a, b, eps1);
            printf("Root for function f1 - f3 = 0: %lf\n\n", res);
        }
    }
    else if (fnum == 2) {
        if (gnum == 1) {
            double res = root(f2, f1, a, b, eps1);
            printf("Root for function f2 - f1 = 0: %lf\n\n", res);
        }
        else if (gnum == 3) {
            double res = root(f2, f3, a, b, eps1);
            printf("Root for function f2 - f3 = 0: %lf\n\n", res);
        }
    }
    else if (fnum == 3) {
        if (gnum == 1) {
            double res = root(f3, f1, a, b, eps1);
            printf("Root for function f3 - f1 = 0: %lf\n\n", res);
        }
        else if (gnum == 2) {
            double res = root(f3, f2, a, b, eps1);
            printf("Root for function f3 - f2 = 0: %lf\n\n", res);
        }
    }
    else if (fnum > 3 || gnum > 3) printf("Функци с таким номером не найдена. Для справки используйте -H (--help)\n");
}

void test_integral(int fnum, double a, double b, double eps2) {
    if (fnum == 1) {
        printf("Интеграл функции f1 на отрезке [%lf, %lf] равен: %lf\n", a, b, integral(f1, a, b, eps2, MAX(second_der_f1(a), second_der_f1(b))));
    }
    else if (fnum == 2) {
        printf("Интеграл функции f2 на отрезке [%lf, %lf] равен: %lf\n", a, b, integral(f2, a, b, eps2, MAX(second_der_f2(a), second_der_f2(b))));
    }
    else if (fnum == 3) {
        printf("Интеграл функции f3 на отрезке [%lf, %lf] равен: %lf\n", a, b, integral(f3, a, b, eps2, MAX(second_der_f3(a), second_der_f3(b))));
    }
    else printf("Функци с таким номером не найдена. Для справки используйте -H (--help)\n");
}


int main(int argc, char *argv[]) {

    int keys[6] = {0};
    //inf();

    for (int i = 1; i < argc; i++) {

        if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "-H")) {
            if (keys[0]) {
                printf("Повторное использование ключа. Для справки используйте -H (--help)\n\n");
            }
            else {
                inf();
                keys[0] = 1;
            }
        }

        else if (!strcmp(argv[i], "--root") || !strcmp(argv[i], "-R")) {
            if (keys[1]) {
                printf("Повторное использование ключа. Для справки используйте -H (--help)\n\n");
            }
            else {
                script_roots();
                keys[1] = 1;
            }
        }

        else if (!strcmp(argv[i], "--iterations") || !strcmp(argv[i], "-I")) {
            if (keys[2]) {
                printf("Повторное использование ключа. Для справки используйте -H (--help)\n\n");
            }
            else {
                if (keys[1]) {
                    count_iterations();
                    keys[2] = 1;
                }
                else printf("Сначала нужно вычислить корни (используйте флаг -R (--root))\n");
            }
        }

        else if (!strcmp(argv[i], "--ans") || !strcmp(argv[i], "-A")) {
            if (keys[3]) {
                printf("Повторное использование ключа. Для справки используйте -H (--help)\n\n");
            }
            else {
                final_integral_script();
                keys[3] = 1;
            }
        }

        else if (!strcmp(argv[i], "--testroot")) {
            if (keys[4]) {
                printf("Повторное использование ключа. Для справки используйте -H (--help)\n\n");
            }
            else {
                test_root(atoi(argv[i+1]), atoi(argv[i+2]), atof(argv[i+3]), atof(argv[i+4]), atof(argv[i+5]));
            }
        }
        else if (!strcmp(argv[i], "--testintegral")) {
            if (keys[5]) {
                printf("Повторное использование ключа. Для справки используйте -H (--help)\n\n");
            }
            else {
                test_integral(atoi(argv[i+1]), atof(argv[i+2]), atof(argv[i+3]), atof(argv[i+4]));
            }
        }
    }
    return 0;
}
