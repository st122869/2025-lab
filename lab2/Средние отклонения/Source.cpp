#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Функция для вычисления среднего значения
double mean(const vector<double>& data) {
    double sum = 0.0;
    for (double value : data) {
        sum += value;
    }
    return sum / data.size();
}

// Функция для вычисления стандартного отклонения (деление на n(n-1))
double standard_deviation(const vector<double>& data) {
    double avg = mean(data);
    double sum_squared_diff = 0.0;

    // Суммируем квадраты отклонений
    for (double value : data) {
        sum_squared_diff += pow(value - avg, 2);
    }

    // Стандартное отклонение (деление на n(n-1))
    return sqrt(sum_squared_diff / (data.size() * (data.size() - 1)));
}

// Функция для выполнения расчетов стандартного отклонения и вывода результатов
void calculateAndPrintResults() {
    // Данные для первой группы (S_y)
    vector<double> group1 = { 0.785674, 0.648722, 0.606092, 0.601793, 0.55942 };

    // Данные для второй группы (S_x)
    vector<double> group2 = { 1.17851, 0.83189, 0.774205, 0.700106, 0.667082 };

    // Вычисляем среднее и стандартное отклонение для каждой группы
    double mean_group1 = mean(group1);
    double std_dev_group1 = standard_deviation(group1);

    double mean_group2 = mean(group2);
    double std_dev_group2 = standard_deviation(group2);

    // Выводим результаты
    cout << "Первая группа:" << endl;
    cout << "Среднее значение S_y: " << mean_group1 << endl;
    cout << "Стандартное отклонение S_y: " << std_dev_group1 << endl;

    cout << "\nВторая группа:" << endl;
    cout << "Среднее значение S_x: " << mean_group2 << endl;
    cout << "Стандартное отклонение S_x: " << std_dev_group2 << endl;
}

int main() {
    // Выполняем расчеты
    calculateAndPrintResults();

    return 0;
}
