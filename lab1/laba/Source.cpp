#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

// ������� ��� ���������� �������� ��������
double avarage(const vector<double>& data)
{
    double sum = 0.0;
    for (double u : data)
    {
        sum += u;
    }
    return sum / data.size();
}

vector<double> standartDeviation(vector<double>& randDevAr)
{
    vector<double> standAr;
    for (int i = 0; i < randDevAr.size(); i++)
    {
        double t = randDevAr[i];
        standAr.push_back(t * t);
    }
    return standAr;
}

vector<double> randomDeviation(const vector<double>& data, double avarage)
{
    vector<double> randDevAr;
    for (int i = 0; i < data.size(); i++)
    {
        randDevAr.push_back(data[i] - avarage);
    }

    return randDevAr;
}

vector<double> calculateDeltaT(const vector<double>& Tx_values, double gamma0, double T0, double T_avg)
{
    vector<double> deltaT_results;
    for (double Tx : Tx_values)
    {
        double gamma_T = gamma0 + (T0 / Tx);
        deltaT_results.push_back(gamma_T * T_avg);
    }
    return deltaT_results;
}

int main()
{
    setlocale(LC_ALL, "Ru");

    const double gamma0 = 5e-7;
    const double T0 = 1e-4;

    ifstream file("������.txt");
    string line;
    vector<double> values;

    if (!file.is_open())
    {
        cerr << "������ �������� �����!" << endl;
        return 1;
    }

    while (getline(file, line))
    {
        if (line.empty())
        {
            continue;  // ���������� ������ ������
        }

        values.push_back(stod(line));
    }

    // ��������� ���� ����� ������
    file.close();

    // ���������� �������� ��������
    double mean = avarage(values);
    cout << "������� �������� (������): " << mean << endl;

    // ���������� ���������� �� �������� ��� ������� ��������
    cout << "���������� �� ��������: " << endl;

    vector<double> ar1 = randomDeviation(values, mean);

    for (int i = 0; i < ar1.size(); i++)
    {
        cout << ar1[i] << "\n";
    }
    cout << endl;

    // ���������� ������������ ����������

    cout << "����������� ����������: " << endl;

    vector<double> ar2 = standartDeviation(ar1);
    for (int i = 0; i < ar2.size(); i++)
    {
        cout << ar2[i] << "\n";
    }
    cout << endl;

    // ���������� ������� ����������� �������
    cout << "������� ����������� �������: " << endl;

    cout<< (gamma0 + (T0 / mean))*mean << "\n";
    cout << endl;

    // ���������� ������������
    cout << "����������� (������): " << endl;

    vector<double> delta_T1 = calculateDeltaT(values, gamma0, T0, mean);
    for (int i = 0; i < delta_T1.size(); i++)
    {
        cout << delta_T1[i] << "\n";
    }
    cout << endl;

    //������ ������ ���������
    ifstream coarse_file("������.txt");
    string linee;
    vector<double> coarse_values;

    if (!coarse_file.is_open())
    {
        cerr << "������ �������� �����!" << endl;
        return 1;
    }

    while (getline(coarse_file, linee))
    {
        if (linee.empty())
        {
            continue;  // ���������� ������ ������
        }

        coarse_values.push_back(stod(linee));
    }
    coarse_file.close();

    double coarse_avg = avarage(coarse_values);
    cout << "������� �������� (������): " << coarse_avg << endl;

    double gamma_T;
    vector<double> delta_T = calculateDeltaT(coarse_values, gamma0, T0, coarse_avg);

    cout << "����������� (������): " << endl;

    for (int i = 0; i < delta_T.size(); i++)
    {
        cout << delta_T[i] << "\n";
    }
    cout << endl;

    return EXIT_SUCCESS;
}