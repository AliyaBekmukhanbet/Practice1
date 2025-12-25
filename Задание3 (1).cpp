#include <iostream>
#include <cstdlib>  // Для rand() и srand()
#include <ctime>    // Для time()
#include <omp.h>    // Для OpenMP

// Функция для вычисления среднего значения элементов массива (последовательная версия)
double calculateAverage(int* arr, int size) {
    double sum = 0.0;
    for (int i = 0; i < size; ++i) {
        sum += arr[i];
    }
    return sum / size;
}

int main() {
    int size;
    std::cout << "Введите размер массива: ";
    std::cin >> size;

    // Создание динамического массива с помощью указателя
    int* arr = new int[size];

    // Инициализация генератора случайных чисел
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Заполнение массива случайными числами (от 0 до 99)
    for (int i = 0; i < size; ++i) {
        arr[i] = std::rand() % 100;
    }

    // Вывод массива для проверки
    std::cout << "Массив: ";
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // Вычисление среднего значения с помощью функции (последовательная версия)
    double avg = calculateAverage(arr, size);
    std::cout << "Среднее значение (последовательное): " << avg << std::endl;

    // Параллельный подсчёт среднего значения с использованием OpenMP
    double sum = 0.0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < size; ++i) {
        sum += arr[i];
    }
    double par_avg = sum / size;
    std::cout << "Среднее значение (параллельное с OpenMP): " << par_avg << std::endl;

    // Освобождение динамической памяти
    delete[] arr;

    return 0;
}