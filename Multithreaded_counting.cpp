#include <iostream>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <mutex>

using namespace std;


int main() {
	long long size;
	int p; 
	vector<long long> rArr; //Массив рандомных чисел
	srand(time(0)); //Инициализация генератора случайных чисел

	cout << "Enter the size of array: ";
	cin >> size;

	while (size <= 0) { //Проверка на корректность ввода
		cout << "Error! Size must be positive. Try again: ";
		cin >> size;
	}
	rArr.resize(size);

	cout << "Enter the cout of threads: ";
	cin >> p;

	while (p > size || p <= 0) { //Проверка на корректность ввода
		cout << "Error! Number of threads must be less than array size and positive. Try again: ";
		cin >> p;
	}


	for (int i = 0; i < size; i++) { //Заполнение массива рандомными числами
		rArr[i] = rand() % 9 + 1;
	}
	

	int partSize = size / p; 
	int lPart = size % p;
	long long answ = 0;
	vector<thread> threads; //Инициализация массива потоков
	mutex mtx;

	for (int i = 0; i < p; i++) {
		int start = i * partSize;
		int end = (i == p - 1) ? (start + partSize + lPart) : (start + partSize);

		// Лямбда-функция с доступом к локальным переменным
		threads.emplace_back([start, end, &rArr, &answ, &mtx]() {
			int localSum = 0;
			for (int j = start; j < end; j++) {
				localSum += rArr[j];
			}

			// Синхронизация доступа к общей переменной
			lock_guard<mutex> lock(mtx); //Синхронизация обращения к данным
			answ += localSum;
			});
	}

	for (auto& t : threads) {
		t.join(); //Дожидаемся завершения каждого потока
	}

	cout << endl << "Your answ: " <<  answ <<  endl;
	cout << "Number of my cores: 14. Number of  my threads: 20." << endl;

	return 0;
}