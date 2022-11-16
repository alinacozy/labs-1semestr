//вариант 9
#include <iostream>
#include <vector>
#include <fstream>
#include <windows.h>
#include <ctype.h>
#include <string>
#include <chrono>
using namespace std;
using namespace chrono;

//заменить три последних символа у слов, больших определенной длины

const char new_symbol = 'x'; // символ, на который мы заменяем последние 3 символа в словах

vector <char> read_vector(ifstream& fin) {
	vector<char> str;
	char ch;
	while ((fin.peek()) != EOF) { //пока следующий символ - не конец файла, берем символ и добавляем его в конец вектора
		ch = fin.get();
		str.push_back(ch);
	}
	fin.close(); //закрываем файл
	return str;
}

string read_string(ifstream& fin) {
	string str="";
	char ch;
	while ((ch = fin.get()) != EOF) { //пока следующий символ - не конец файла, берем символ и добавляем его в конец строки
		str.push_back(ch);
	}
	fin.close(); //закрываем файл
	return str;
}

int input_cr_len() {
	int n;
	cout << "Введите число - минимальную длину слов, в которых произведется замена символов: ";
	while (!(cin >> n) || cin.peek() != '\n' || (n <= 3)) { //пока не введено n, или следующий символ не равен переводу строки, или введено меньше двух
		cin.clear(); //очищаем поток от флага ошибки
		cin.ignore(32767, '\n'); //очищаем поток от символов
		cout << "Ошибка, введите целое число больше 3: ";
	}
	return n;
}

void replacing(vector<char>& v, int cr_len) {
	int word_length = 0;
	int i = 0;
	for (; i < v.size(); i++) { //в цикле рассматриваем символы с первого по последний
		if (!isalpha(v[i])) {
			if (word_length > cr_len) //если длина слова больше критической, заменяем 3 символа перед разделителем
				v[i - 1] = v[i - 2] = v[i - 3] = new_symbol;
			word_length = 0; //сброс длины слова
		}
		else
			word_length++; //если i-ый символ не является разделителем, увеличиваем длину слова
	}
	if (word_length > cr_len) //если длина слова больше критической, заменяем 3 символа перед разделителем
		v[i - 1] = v[i - 2] = v[i - 3] = new_symbol;
}

void replacing(string& str, int cr_len) {
	int word_length = 0;
	int i = 0;
	for (; i < str.length(); i++) { //в цикле рассматриваем символы с первого по последний
		if (!isalpha(str[i])) {
			if (word_length > cr_len) //если длина слова больше критической, заменяем 3 символа перед разделителем
				str[i - 1] = str[i - 2] = str[i - 3] = new_symbol;
			word_length = 0; //сброс длины слова
		}
		else
			word_length++; //если i-ый символ не является разделителем, увеличиваем длину слова
	}
	if (word_length > cr_len) //если длина слова больше критической, заменяем 3 символа перед разделителем
		str[i - 1] = str[i - 2] = str[i - 3] = new_symbol;
}


void output_to_file(vector<char>& symbols, ofstream& fout, double time) {
	fout << "Результат выполнения программы с помощью vector char:\n";
	for (int i = 0; i < symbols.size(); i++)
		fout << symbols[i];
	fout << endl;
	fout << "Среднее время выполнения с помощью vector char: "<<time<<"ns.\n";
}

void output_to_file(string& str, ofstream& fout, double time) {
	fout << "Результат выполнения программы с помощью string:\n"<< str <<endl;
	fout << "Среднее время выполнения с помощью string: " << time << "ns.\n";
}

bool check_again() {
	cout << "Вы хотите продолжить? Y/N: ";
	char anwser;
	while (!(cin >> anwser) || cin.peek() != '\n' || anwser != 'Y' && anwser != 'y' && anwser != 'N' && anwser != 'n') {
		cin.clear(); //очищаем поток от флага ошибки
		cin.ignore(32767, '\n'); //очищаем поток от символов
		cout << "Ошибка, введите Y или N: ";
	}
	cin.ignore(32767, '\n'); //очищаем поток от символов
	return(anwser == 'Y' || anwser == 'y');
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	bool again = true;
	double time_vector = 0; //в этих переменных хранится время за все запуски цикла (чтобы потом считать среднее значение)
	double time_string = 0;
	ofstream f("output.txt", ios_base::trunc); //для очистки файла output перед выполнением программы
	for (int count = 1; again; count++) {
		cout << "Введите название файла, из которого нужно считать данные: ";
		char infile_name[100]; // создаем массив символов
		bool correct_file = false; //если введен правильный файл, то переменная true
		while (!correct_file) {
			//cin.clear();
			cin.getline(infile_name, 100); //использую cin.getline(), чтобы можно было считать название файла, содержащее пробел
			ifstream infile(infile_name);
			if (!infile.is_open())
				cout << "Ошибка, невозможно открыть файл.\nВведите название файла ещё раз: ";
			else if (infile.peek() == EOF)
				cout << "Ошибка, данный файл пустой.\nВведите название файла ещё раз: ";
			else
				correct_file = true;
		}
		int critical_length = input_cr_len();//ввод критической длины слова
		ifstream fin(infile_name); //создаем файловый поток ввода
		vector<char> vec_symbols = read_vector(fin); //вектор, в который считываем символы из файла
		ifstream fin2(infile_name);
		string str_symbols = read_string(fin2);

		steady_clock::time_point start_vector = steady_clock::now();
		replacing(vec_symbols, critical_length); //заменяем символы в векторе
		steady_clock::time_point end_vector = steady_clock::now();
		time_vector += duration_cast<nanoseconds>(end_vector - start_vector).count();

		steady_clock::time_point start_string = steady_clock::now();
		replacing(str_symbols, critical_length); //заменяем символы в строке
		steady_clock::time_point end_string = steady_clock::now();
		time_string += duration_cast<nanoseconds>(end_string - start_string).count();
		cout << str_symbols;

		ofstream fout("output.txt", ios_base::app); //создаем файловый поток вывода
		//константа ios_base::app чтобы запись выполнялась в конец файла
		fout << "-----------------------------------------\n";//для отделения разных выполнений программы в файле
		output_to_file(vec_symbols, fout, time_vector/count); //записать результат в файл
		fout << endl;
		output_to_file(str_symbols, fout, time_string/count);
		fout.close();

		cout << "Результат выполнения программы записан в файл output.txt.\n";
		again = check_again();
	}
}
