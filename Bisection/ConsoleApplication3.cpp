#include <iostream>
#include <cmath>
#include <chrono>

using namespace std;
using namespace chrono;

double function(double x) {
    return 3 * sin(sqrt(x)) + 0.35 * x - 3.8;
}

double first_derivative(double x, double h = 1e-5) {
    return (function(x + h) - function(x - h)) / (2 * h);
}

double second_derivative(double x, double h = 1e-5) {
    return (function(x + h) - 2 * function(x) + function(x - h)) / (h * h);
}

int main()
{
    setlocale(LC_ALL, "Rus");
    double epsilon = 0.00001;
    double x0 = 2.0;
    bool found = false;

    // Поиск начального значения x0
    for (x0 = 2.0; x0 <= 3.0 && !found; x0 += 0.01)
    {
        if (function(x0) * second_derivative(x0) > 0)
        {
            found = true;
        }
    }

    if (!found)
    {
        cout << "Не удалось найти подходящее начальное значение x0 на отрезке [2;3]." << endl;
        return 1;
    }

    x0 -= 0.01; // Коррекция x0 после завершения цикла
    double x = x0;
    int iteration = 0;

    auto start = high_resolution_clock::now();

    while (fabs(function(x)) > epsilon)
    {
        x = x - function(x) / first_derivative(x);
        iteration++;
        cout << "Итерация " << iteration << ": x = " << x << endl;
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();

    cout << "Начальное значение x0: " << x0 << endl;
    cout << "Количество итераций: " << iteration << endl;
    cout << "Корень: " << x << endl;
    cout << "Затраченное время: " << duration << " микросекунд" << endl;

    return 0;
}
