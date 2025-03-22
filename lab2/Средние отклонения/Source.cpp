#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// ������� ��� ���������� �������� ��������
double mean(const vector<double>& data) {
    double sum = 0.0;
    for (double value : data) {
        sum += value;
    }
    return sum / data.size();
}

// ������� ��� ���������� ������������ ���������� (������� �� n(n-1))
double standard_deviation(const vector<double>& data) {
    double avg = mean(data);
    double sum_squared_diff = 0.0;

    // ��������� �������� ����������
    for (double value : data) {
        sum_squared_diff += pow(value - avg, 2);
    }

    // ����������� ���������� (������� �� n(n-1))
    return sqrt(sum_squared_diff / (data.size() * (data.size() - 1)));
}

// ������� ��� ���������� �������� ������������ ���������� � ������ �����������
void calculateAndPrintResults() {
    // ������ ��� ������ ������ (S_y)
    vector<double> group1 = { 0.785674, 0.648722, 0.606092, 0.601793, 0.55942 };

    // ������ ��� ������ ������ (S_x)
    vector<double> group2 = { 1.17851, 0.83189, 0.774205, 0.700106, 0.667082 };

    // ��������� ������� � ����������� ���������� ��� ������ ������
    double mean_group1 = mean(group1);
    double std_dev_group1 = standard_deviation(group1);

    double mean_group2 = mean(group2);
    double std_dev_group2 = standard_deviation(group2);

    // ������� ����������
    cout << "������ ������:" << endl;
    cout << "������� �������� S_y: " << mean_group1 << endl;
    cout << "����������� ���������� S_y: " << std_dev_group1 << endl;

    cout << "\n������ ������:" << endl;
    cout << "������� �������� S_x: " << mean_group2 << endl;
    cout << "����������� ���������� S_x: " << std_dev_group2 << endl;
}

int main() {
    // ��������� �������
    calculateAndPrintResults();

    return 0;
}
