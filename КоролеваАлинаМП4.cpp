//вариант 9
#include <iostream>
#include <vector>
#include <fstream>
#include <windows.h>
#include <ctype.h>
using namespace std;

//заменить три последних символа у слов, больших определенной длины

const char new_symbol = 'x'; // символ, на который мы заменяем последние 3 символа в словах

vector <char> read_string(ifstream& fin) {
	vector<char> str;
	char ch;
	while ((fin.peek()) != EOF) { //пока следующий символ - не конец файла, берем символ и добавляем его в конец вектора
		ch = fin.get();
		str.push_back(ch);
	}
	fin.close(); //завкрываем файл
	return str;
}

int input_cr_len() {
	int n;
	cout << "Введите число - минимальную длину слов, в которых произведется замена символов: ";
	while (!(cin >> n) || cin.peek() != '\n' || (n <=3 )) { //пока не введено n, или следующий символ не равен переводу строки, или введено меньше двух
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

void output_to_file(vector<char>& symbols, ofstream& fout) {
	fout << "--------------------------------------------------\n";//для отделения результатов выполнения программы в файле output
	for (int i = 0; i < symbols.size(); i++)
		fout << symbols[i];
	fout << endl;
	fout.close();
	cout << "Результат выполнения программы записан в файл output.txt.\n";
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
	while(again) {
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
		ifstream fin(infile_name); //создаем файловый поток ввода
		vector<char> symbols = read_string(fin); //вектор, в который считываем символы из файла
		int critical_length = input_cr_len();
		replacing(symbols, critical_length); //заменяем символы в векторе согласно заданию
		ofstream fout("output.txt", ios_base::app); //создаем файловый поток вывода
		//константа ios_base::app чтобы запись выполнялась в конец файла
		output_to_file(symbols, fout); //записать результат в файл
		again = check_again();
	}
}
