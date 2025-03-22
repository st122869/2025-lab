#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <stdexcept>
#include <windows.h> // ��� SetConsoleOutputCP

// ������� ��� ������ ������ �� ����� � ������
std::vector<double> readData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("�� ������� ������� ���� " + filename);
    }

    std::vector<double> data;
    double value;
    while (file >> value) {
        data.push_back(value);
    }

    return data;
}

// ������� ��� ������� ����������������
std::vector<double> calculateSensitivity(const std::vector<double>& L, const std::vector<double>& Ueff) {
    std::vector<double> sensitivity;

    for (size_t i = 0; i < L.size(); ++i) {
        double S = L[i] / (2 * std::sqrt(2) * Ueff[i]);
        sensitivity.push_back(S);
    }

    return sensitivity;
}

int main() {
    // ������������� ��������� ������� � UTF-8 (�����������)
    SetConsoleOutputCP(CP_UTF8);

    // ������ �������� L ��� ������� � ������� ������
    std::vector<double> L_vertical_horizontal = { 10, 20, 30, 40, 50 };
    // ������ �������� L ��� ���������� ����� (Ueff_max.txt)
    std::vector<double> L_max = { 10, 20, 30, 40 };

    // ������ ������ �� ������
    std::vector<double> Ueff_vertical;
    std::vector<double> Ueff_horizontal;
    std::vector<double> Ueff_max;

    try {
        // ������ ������ �� ������
        Ueff_vertical = readData("Ueff_vertical.txt");
        Ueff_horizontal = readData("Ueff_horizontal.txt");
        Ueff_max = readData("Ueff_max.txt");

        // �������� �� ���������� �������� ������
        if (Ueff_vertical.size() != L_vertical_horizontal.size() ||
            Ueff_horizontal.size() != L_vertical_horizontal.size()) {
            throw std::invalid_argument("���������� ������ � ������ Ueff_vertical.txt ��� Ueff_horizontal.txt �� ��������� � �������� ������� L.");
        }

        if (Ueff_max.size() != L_max.size()) {
            throw std::invalid_argument("���������� ������ � ����� Ueff_max.txt �� ��������� � �������� ������� L ��� ����� �����.");
        }

        // ������ ���������������� ��� ������������ � �������������� ������
        std::vector<double> S_vertical = calculateSensitivity(L_vertical_horizontal, Ueff_vertical);
        std::vector<double> S_horizontal = calculateSensitivity(L_vertical_horizontal, Ueff_horizontal);

        // ������ ���������������� ��� ������ �� Ueff_max.txt
        std::vector<double> S_max = calculateSensitivity(L_max, Ueff_max);

        // ����� ����������� ��� ������������ ������
        std::cout << "���������������� ��� ������������ ������:" << std::endl;
        for (size_t i = 0; i < S_vertical.size(); ++i) {
            std::cout << "L = " << L_vertical_horizontal[i] << ", S = " << S_vertical[i] << std::endl;
        }

        // ����� ����������� ��� �������������� ������
        std::cout << "\n���������������� ��� �������������� ������:" << std::endl;
        for (size_t i = 0; i < S_horizontal.size(); ++i) {
            std::cout << "L = " << L_vertical_horizontal[i] << ", S = " << S_horizontal[i] << std::endl;
        }

        // �������� ����� ��� ������ ����������� ��� ������ �� Ueff_max.txt
        std::ofstream outputFile("output_max.txt");
        if (!outputFile.is_open()) {
            throw std::runtime_error("�� ������� ������� ���� ��� ������.");
        }

        // ������ ����������� ��� ������ �� Ueff_max.txt
        outputFile << "���������������� ��� ������ �� Ueff_max.txt:" << std::endl;
        for (size_t i = 0; i < S_max.size(); ++i) {
            outputFile << "L = " << L_max[i] << ", S = " << S_max[i] << std::endl;
        }

        // �������� �����
        outputFile.close();
        std::cout << "���������� �������� � ���� output_max.txt" << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "������: " << e.what() << std::endl;
    }

    return 0;
}
