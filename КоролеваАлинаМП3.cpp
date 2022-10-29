#include <iostream>
#include <vector>
#include <string>

using namespace std;

int input_correct_number() {
	int n;
	cout << "Enter the number of elements in vector: ";
	while (!(cin >> n) || (cin.peek() != '\n') || (n < 2)) { //пока не введено n, или следующий символ не равен переводу строки, или введено меньше двух
		cin.clear(); //очищаем поток от флага ошибки
		cin.ignore(32767, '\n'); //очищаем поток от символов
		cout << "Error, enter a positive number bigger than 1: ";
	}
	return n;
}

void random_vector(vector<int>& v, int num) {
	int n;
	srand(time(NULL));
	for (int i = 1; i <= num; i++) {
		n = rand() % 1000;
		v.push_back(n);
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

void insertion_sort(vector <int>& v) {
	for (int i = 1; i < v.size(); i++) { //перебираем элементы вектора, начиная со второго элемента
		for (int j = i; (j > 0) && (v[j] < v[j - 1]); j-=1)// j - индекс элемента, который проходит вставку
			swap(v[j], v[j - 1]); //пока j>0 и элементы стоят в неправильном порядке, поменять элементы местами
	}
}

bool check_again() {
	cout << "Do you want to continue? Y/N: ";
	char anwser;
	while (!(cin>>anwser) || cin.peek() != '\n' || anwser != 'Y' && anwser != 'y' && anwser != 'N' && anwser != 'n') {
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
		int num_of_elements = input_correct_number(); //ввод числа элементов в массиве
		vector<int>vector; // создание вектора
		random_vector(vector, num_of_elements); //генерация вектора
		output_vector("Original vector:", vector); 
		insertion_sort(vector); //сортировка
		output_vector("Sorted vector:", vector);
		again = check_again(); //проверка, хочет ли пользователь продолжить
	}
}