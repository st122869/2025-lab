#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <stdexcept>
#include <windows.h> // Для SetConsoleOutputCP

// Функция для чтения данных из файла в вектор
std::vector<double> readData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл " + filename);
    }

    std::vector<double> data;
    double value;
    while (file >> value) {
        data.push_back(value);
    }

    return data;
}

// Функция для расчета чувствительности
std::vector<double> calculateSensitivity(const std::vector<double>& L, const std::vector<double>& Ueff) {
    std::vector<double> sensitivity;

    for (size_t i = 0; i < L.size(); ++i) {
        double S = L[i] / (2 * std::sqrt(2) * Ueff[i]);
        sensitivity.push_back(S);
    }

    return sensitivity;
}

int main() {
    // Устанавливаем кодировку консоли в UTF-8 (опционально)
    SetConsoleOutputCP(CP_UTF8);

    // Массив значений L для первого и второго файлов
    std::vector<double> L_vertical_horizontal = { 10, 20, 30, 40, 50 };
    // Массив значений L для последнего файла (Ueff_max.txt)
    std::vector<double> L_max = { 10, 20, 30, 40 };

    // Чтение данных из файлов
    std::vector<double> Ueff_vertical;
    std::vector<double> Ueff_horizontal;
    std::vector<double> Ueff_max;

    try {
        // Чтение данных из файлов
        Ueff_vertical = readData("Ueff_vertical.txt");
        Ueff_horizontal = readData("Ueff_horizontal.txt");
        Ueff_max = readData("Ueff_max.txt");

        // Проверка на совпадение размеров данных
        if (Ueff_vertical.size() != L_vertical_horizontal.size() ||
            Ueff_horizontal.size() != L_vertical_horizontal.size()) {
            throw std::invalid_argument("Количество данных в файлах Ueff_vertical.txt или Ueff_horizontal.txt не совпадает с размером массива L.");
        }

        if (Ueff_max.size() != L_max.size()) {
            throw std::invalid_argument("Количество данных в файле Ueff_max.txt не совпадает с размером массива L для этого файла.");
        }

        // Расчет чувствительности для вертикальных и горизонтальных данных
        std::vector<double> S_vertical = calculateSensitivity(L_vertical_horizontal, Ueff_vertical);
        std::vector<double> S_horizontal = calculateSensitivity(L_vertical_horizontal, Ueff_horizontal);

        // Расчет чувствительности для данных из Ueff_max.txt
        std::vector<double> S_max = calculateSensitivity(L_max, Ueff_max);

        // Вывод результатов для вертикальных данных
        std::cout << "Чувствительность для вертикальных данных:" << std::endl;
        for (size_t i = 0; i < S_vertical.size(); ++i) {
            std::cout << "L = " << L_vertical_horizontal[i] << ", S = " << S_vertical[i] << std::endl;
        }

        // Вывод результатов для горизонтальных данных
        std::cout << "\nЧувствительность для горизонтальных данных:" << std::endl;
        for (size_t i = 0; i < S_horizontal.size(); ++i) {
            std::cout << "L = " << L_vertical_horizontal[i] << ", S = " << S_horizontal[i] << std::endl;
        }

        // Открытие файла для записи результатов для данных из Ueff_max.txt
        std::ofstream outputFile("output_max.txt");
        if (!outputFile.is_open()) {
            throw std::runtime_error("Не удалось открыть файл для записи.");
        }

        // Запись результатов для данных из Ueff_max.txt
        outputFile << "Чувствительность для данных из Ueff_max.txt:" << std::endl;
        for (size_t i = 0; i < S_max.size(); ++i) {
            outputFile << "L = " << L_max[i] << ", S = " << S_max[i] << std::endl;
        }

        // Закрытие файла
        outputFile.close();
        std::cout << "Результаты записаны в файл output_max.txt" << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
