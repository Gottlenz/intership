#include <iostream>
using namespace std;

// Вывод системы линейных уравнений
void sysout(double** a, double* y, int n)
{
    cout << "Система уравнений:" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << a[i][j] << "*x" << j;
            if (j < n - 1)
                cout << " + ";
        }
        cout << " = " << y[i] << endl;
    }
    cout << endl;
}

double* gauss(double** a, double* y, int n)
{
    double* x, max;
    int k, index;
    const double eps = 0.00001; // Точность
    x = new double[n];
    k = 0;

    while (k < n)
    {
        // Поиск строки с максимальным значением a[i][k]
        max = abs(a[k][k]);
        index = k;
        for (int i = k + 1; i < n; i++)
        {
            if (abs(a[i][k]) > max)
            {
                max = abs(a[i][k]);
                index = i;
            }
        }

        // Перестановка строк
        if (max < eps)
        {
            // Проверка отсутствия нулевых диагональных элементов 
            cout << "Решение невозможно из-за нулевого столбца ";
            cout << index << " матрицы A" << endl;
            delete[] x;
            return nullptr;
        }

        for (int j = 0; j < n; j++)
        {
            double temp = a[k][j];
            a[k][j] = a[index][j];
            a[index][j] = temp;
        }

        double temp = y[k];
        y[k] = y[index];
        y[index] = temp;

        // Нормализация уравнений
        for (int i = k; i < n; i++)
        {
            double temp = a[i][k];
            if (abs(temp) < eps)
                continue; // Пропутить для нулевого коэффициента

            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] / temp;

            y[i] = y[i] / temp;

            if (i == k)
                continue; // Не вычитать уравнение само из себя

            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] - a[k][j];

            y[i] = y[i] - y[k];
        }

        k++;
    }

    // Обратная подстановка
    for (k = n - 1; k >= 0; k--)
    {
        x[k] = y[k];
        for (int i = 0; i < k; i++)
            y[i] = y[i] - a[i][k] * x[k];
    }

    return x;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    double** a, * y, * x;
    int n;

    cout << "Введите количество уравнений: ";
    cin >> n;

    // Проверка правильности ввода
    while (n <= 0)
    {
        cout << "Число уравнений должно быть целым положительным числом." << endl;
        cout << "Пожалуйста, попробуйте еще раз:";
        cin >> n;
    }

    a = new double* [n];
    y = new double[n];

    // Ввод матрицы A
    cout << endl << "Введите коэффициенты матрицы A:" << endl;
    for (int i = 0; i < n; i++)
    {
        a[i] = new double[n];
        for (int j = 0; j < n; j++)
        {
            cout << "a[" << i << "][" << j << "]= ";
            cin >> a[i][j];
        }
    }

    // Ввод вектора y
    cout << endl << "Введите значения вектора y:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "y[" << i << "]= ";
        cin >> y[i];
    }

    cout << endl;

    sysout(a, y, n);

    x = gauss(a, y, n);

    if (x != nullptr)
    {
        cout << "Решение:" << endl;
        for (int i = 0; i < n; i++)
            cout << "x[" << i << "]=" << x[i] << endl;
        delete[] x;
    }

    for (int i = 0; i < n; i++)
        delete[] a[i];
    delete[] a;
    delete[] y;

    cin.ignore();
    cin.get();
    return 0;
}