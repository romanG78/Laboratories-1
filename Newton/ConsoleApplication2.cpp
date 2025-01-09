#include <iostream>
#include <cmath>
#include <chrono>
using namespace std;
using namespace chrono;

double function(double x)
{
    return 3 * sin(sqrt(x)) + 0.35*x - 3.8;
}

int main()
{
    setlocale(LC_ALL, "Rus");
    double fst = 2.0;
    double scnd = 3.0;
    double epsilon = 0.00001;
    double x;
    int iteration = 0;

    if (function(fst) * function(scnd) >= 0)
    {
        cout << "Нет корней на данном интервале." << endl;
        return 1;
    }

    auto start = high_resolution_clock::now();

    bool found = false;
    while ((scnd - fst) / 2 > epsilon && !found)
    {
        x = (fst + scnd) / 2;
        iteration++;
        cout << "Итерация " << iteration << ": x = " << x << endl;
        if (function(x) == 0.0)
        {
            found = true;
        }
        else if (function(x) * function(fst) < 0)
        {
            scnd = x;
        }
        else
        {
            fst = x;
        }
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();

    x = (a + b) / 2;

    cout << "Количество итераций: " << iteration << endl;
    cout << "Корень: " << x << endl;
    cout << "Затраченое время: " << duration << " микросекунд" << endl;

    return 0;
}
