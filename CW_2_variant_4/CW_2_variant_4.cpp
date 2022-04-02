#include <iostream>
#include <cmath>

using namespace std;
//Функція яку будемо інтегрувати
double f(double x)
{
    return log(x) / (1 - pow(x, 2));
}

//Метод лівих прямокутників S=h*sum(f(a))
double Left(double a, double b, int n)
{
    double h = (b - a) / n; //Крок
    double S = 0.0; //Площа
    for (int i = 0; i <= n - 1; i++) //Цикл суми всіх площ
    {
        S += h * f(a + i * h);
    }
    return S;
}

//Метод правих прямокутників S=h*sum(f(b))
double Right(double a, double b, int n)
{
    double h = (b - a) / n;  //Крок
    double S = 0.0;  //Площа
    for (int i = 1; i < n; i++) //Цикл суми всіх площ 
    {
        S += h * f(a + i * h);
    }
    return S;
}

//Метод центральних прямокутників S=h*sum((f((a+b)/2))
double Central(double a, double b, int n)
{
    double h = (b - a) / n; //Крок
    double S = 0.0; //Площа
    for (int i = 1; i < n; i++) // Цикл суми всіх площ
    {
        S += h * f((a + (a + i * h)) / 2);
    }
    return S;
}

//Метод трапецій S=h/2*(f(x1)+f(xn)+2sum(xi))
double Trapeze(double a, double b, int n)
{
    double h = (b - a) / n; //Крок
    double S = f(a) + f(b); // Сума при границях інтегралу
    for (int i = 1; i < n - 1; i++) // Цикл суми всіх значень 
    {
        S += 2 * f(a + i * h);
    }
    S *= h / 2; //Сума всіх площ
    return S;
}

//Метод Сімпсона S=h/6*(f(a)+4f((a+b)/2)+f(b))
double Simpson(double a, double b, int n)
{
    double h = (b - a) / n; //Крок
    double S = 0.0;
    for (int i = 0; i <= n - 1; i++)//Цикл суми всіх значень
    {
        S += (4 * f((a + (a + i * h)) / 2)) + f(a + i * h) + f(a + (i + 1) * h);
    }
    S *= h / 6;//площа
    return S;
}

//Ітераційна формула Сімпсона S=f(a)+4sum"i=1,n"(f(x2i-1))+2sum"i=1,n-1"(f()x2i)+f(b) 
double IterSimpson(double a, double b, int n)
{
    double h = (b - a) / n; //Крок
    double S = f(a) + f(b); //Сума при границях інтегралу
    int j;
    for (int i = 1; i <= n - 1; i++) //Цикл суми значень
    {
        j = 2 + 2 * (i % 2); // коефіцієнт перед сумою(4 для непарного х, 2 для парного)
        S += j * f(a + i * h);
    }
    S *= h / 3; //Площа
    return S;
}
int main()
{
    double a = 0.1, b = 0, e = 0.0001, runge; // а(нижня границя), b(змінна для верхньої границі), e(точність), runge(змінна для методу Рунге)
    int n, i = 0; //n()к-сть кроків
    cout << "RECTANGLES AND TRAPEZE" << endl << "" << endl;

    while (b < 1) //цикл обислення значення функції при різних х
    {
        double h = pow(e, 1.0 / 4); //знаходимо крок за провилом рунге
        n = ceil((b - a) / h); //найблище більше ціле число(для к-сті кроку)
        if (b <= a) //якщо верхня границя менша за нижню то обчислення неможливе
        {
            cout << "x = " << b << endl;
            cout << "Unable to determine!!!" << endl;
            cout << endl;
        }
        else
        {
            cout << "x = " << b << endl;
            do //використання методу Рунге для точності е
            {
                i++;
                runge = fabs((Left(a, b, n * (i + 1)) - Left(a, b, n * i)) / 3);//(I(h/2)-I(h))/3   3 для методу прямокутників і трапеції
            } while (runge > e);
            cout << "Left rectangles :  " << Left(a, b, n * (i + 1)) << ";   n = " << n * (i + 1) << endl; //виводимо якщо runge<e
            i = 0;

            do {
                i++;
                runge = fabs((Right(a, b, n * (i + 1)) - Right(a, b, n * i)) / 3);
            } while (runge > e);
            cout << "Right rectangles:  " << Right(a, b, n * (i + 1)) << ";   n = " << n * (i + 1) << endl;
            i = 0;

            do {
                i++;
                runge = fabs((Central(a, b, n * (i + 1)) - Central(a, b, n * i)) / 3);
            } while (runge > e);
            cout << "Central rectangles:" << Central(a, b, n * (i + 1)) << ";   n = " << n * (i + 1) << endl;
            i = 0;

            do {
                i++;
                runge = fabs((Trapeze(a, b, n * (i + 1)) - Trapeze(a, b, n * i)) / 3);
            } while (runge > e);
            cout << "Trapeze:           " << Trapeze(a, b, n * (i + 1)) << ";   n = " << n * (i + 1) << endl;
            i = 0;

            cout << endl;
        }
        b += 0.1;
    }
    b = 0;
    cout << "SIMPSON" << endl << "" << endl;
    while (b < 1) //цикл обислення значення функції при різних х методом Сімпона
    {
        double h = pow(e, 1.0 / 4);//знаходимо крок за провилом рунге
        n = ceil((b - a) / h);//найблище більше ціле число(для к-сті кроку)
        if (n % 2 != 0) //так як для методу Сімпона к-сть кроків має бути парною, то збільшуємо на один якщо n непарне
        {
            n += 1;
        }

        if (b <= a)
        {
            cout << "x = " << b << endl;
            cout << "Unable to determine!!!" << endl;
            cout << endl;
        }
        else
        {
            cout << "x = " << b << endl;

            do
            {
                i++;
                runge = fabs((Simpson(a, b, n * (i + 1)) - Simpson(a, b, n * i)) / 15);//(I(h/2)-I(h))/15   15 для методу Сімпсона
            } while (runge > e);
            cout << "Simpson     :  " << Simpson(a, b, n * (i + 1)) << ";   n = " << n * (i + 1) << endl;
            i = 0;

            do
            {
                i++;
                runge = fabs((IterSimpson(a, b, n * (i + 1)) - IterSimpson(a, b, n * i)) / 15);
            } while (runge > e);
            cout << "IterSimpson :  " << IterSimpson(a, b, n * (i + 1)) << ";   n = " << n * (i + 1) << endl;
            i = 0;

            cout << endl;
        }
        b += 0.1;
    }
    return 0;
}