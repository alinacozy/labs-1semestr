#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;

int input_correct_number() {
	int n;
	cout << "Enter the number of elements in vector: ";
	while (!(cin >> n) || cin.peek() != '\n' || (n < 2)) { //пока не введено n, или следующий символ не равен переводу строки, или введено меньше двух
		cin.clear(); //очищаем поток от флага ошибки
		cin.ignore(32767, '\n'); //очищаем поток от символов
		cout << "Error, enter a positive number bigger than 1: ";
	}
	return n;
}

char input_option() { //способ ввода вектора. 1 - случаные данные, 2 - случайные данные с малым числом уникальных значений, 3 - ручной ввод
	cout << "How do you want to enter the vector?\n"
		<< "1 - Random data\n" << "2 - Random data with few unique values\n" << "3 - Enter vector from keyboard\n";
	char opt;
	cout << "Enter 1, 2 or 3: ";
	while (!(cin >> opt) || cin.peek() != '\n' || opt != '1' && opt != '2' && opt != '3') {
		cin.clear(); //очищаем поток от флага ошибки
		cin.ignore(32767, '\n'); //очищаем поток от символов
		cout << "Error, enter 1, 2 or 3: ";
	}
	return opt;
}

void random_vector(vector<int>& v, int num, int interval) { //интервал - до какого числа мы будем генерировать случайные данные
	int n;
	srand(time(NULL));
	for (int i = 1; i <= num; i++) {
		n = rand() % interval;
		v.push_back(n);
	}
}

void input_vector(vector<int>& v, int num) {
	for (int i = 1; i <= num; i++) {
		int element;
		cout << "Enter the element of vector number "<<i<<": ";
		while (!(cin >> element) || (cin.peek() != '\n')) { //пока не введено n, или следующий символ не равен переводу строки, или введено меньше двух
			cin.clear(); //очищаем поток от флага ошибки
			cin.ignore(32767, '\n'); //очищаем поток от символов
			cout << "Error, enter an integer: ";
		}
		v.push_back(element);
	}
}

void output_vector(string description, vector <int>& v) { // вывод вектора
	cout << description << endl;
	if (v.size() <= 30) { // если кол-во элементов меньше или равно 30, то выводим все элементы
		for (int i = 0; i < v.size(); i++)
			cout << v[i] << " ";
	}
	else { // если кол-во элементов больше 30, выводим первые 28 элементов и последние 2 элемента
		for (int i = 0; i < 28; i++)
			cout << v[i] << " ";
		cout << "... ";
		cout << v[v.size() - 2] << " " << v[v.size() - 1];
	}
	cout << endl;
}

vector<int> insertion_sort(vector<int> v) {
	for (int i = 1; i < v.size(); i++) { //перебираем элементы вектора, начиная со второго элемента
		for (int j = i; (j > 0) && (v[j] < v[j - 1]); j -= 1)// j - индекс элемента, который проходит вставку
			swap(v[j], v[j - 1]); //пока j>0 и элементы стоят в неправильном порядке, поменять элементы местами
	}
	return v;
}

bool check_again() {
	cout << "Do you want to continue? Y/N: ";
	char anwser;
	while (!(cin >> anwser) || cin.peek() != '\n' || anwser != 'Y' && anwser != 'y' && anwser != 'N' && anwser != 'n') {
		cin.clear(); //очищаем поток от флага ошибки
		cin.ignore(32767, '\n'); //очищаем поток от символов
		cout << "Error, enter Y or N: ";
	}
	return(anwser == 'Y' || anwser == 'y');
}

int main()
{
	bool again = true;
	while (again) {
		cout << "*********************************************************\n";
		int num_of_elements = input_correct_number(); //ввод числа элементов в массиве
		char option = input_option(); //способ ввода вектора
		vector<int>vec; // создание вектора
		switch (option) {
		case '1':
			random_vector(vec, num_of_elements, 1000); //генерация вектора с значениями от 0 до 999
			break;
		case '2':
			random_vector(vec, num_of_elements, 5); //вектор с значениями от 0 до 4
			break;													
		case '3':
			input_vector(vec, num_of_elements);
			break;
		}
		output_vector("Original vector:", vec);

		steady_clock::time_point start_insertion = steady_clock::now();
		vector<int>my_sort_vec = insertion_sort(vec); //сортировка вставками
		steady_clock::time_point end_insertion = steady_clock::now();
		double time_insertion = duration_cast<nanoseconds>(end_insertion - start_insertion).count(); //время в наносекундах
		output_vector("Vector sorted by insertion:", my_sort_vec);
		
		steady_clock::time_point start_sort = steady_clock::now();
		sort(vec.begin(), vec.end());
		steady_clock::time_point end_sort = steady_clock::now();
		double time_sort = duration_cast<nanoseconds>(end_sort - start_sort).count(); //время в наносекундах
		output_vector("Vector sorted by sort():", vec);

		cout << "Time for insertion sort is: " << time_insertion/1000 << " mcs\n";
		cout << "Time for sort() is: " << time_sort/1000 << " mcs\n";
		cout << "The acceleration is: " << time_insertion / time_sort << endl;

		again = check_again(); //проверка, хочет ли пользователь продолжить
	}
}