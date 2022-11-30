//вариант 9
#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <map>

#include <vector>
#include <algorithm>
#include <utility>

std::string input_filename() {
	std::cout << "Input a filename>";
	std::string infile_name;
	bool correct_file = false; //если введен правильный файл, то переменная true
	while (!correct_file) {
		getline(std::cin, infile_name); //использую getline(), чтобы можно было считать название файла, содержащее пробел
		std::ifstream infile(infile_name);
		if (!infile.is_open())
			std::cout << "Error, the file cannot be opened.\nEnter the filename again>";
		else if (infile.peek() == EOF)
			std::cout << "Error, this file is empty.\nEnter the filename again>";
		else
			correct_file = true;
	}
	return infile_name;
}

std::string read_string(const std::string& fin_name) {
	std::ifstream fin(fin_name);
	std::string result="";
	char ch;
	while (fin.peek()!=EOF) { //пока следующий символ - не конец файла, берем символ и добавляем его в конец строки
		ch = fin.get();
		result+=ch;
	}
	fin.close(); //закрываем файл
	return result;
}

std::map<char, double> counting_chars(const std::string& str) {
	std::map<char, double> chars;
	for (char i : str) //подсчитываем количество каждого символа
		chars[i]++; 
	int length = str.length(); //вычисление длины строки
	std::map<char, double> ::iterator it = chars.begin();
	for (it; it != chars.end(); it++)
		it->second /= length; //делим каждое значение на длину строки, чтобы посчитать частоту

	return chars;
}

void output(const std::map<char, double>& chars) {
	std::map<char, double>::const_iterator it=chars.begin();
	for (it; it != chars.end(); it++)
		if (it->first == '\n')
			std::cout << "'\\n': " << it->second << '\n';
		else
			std::cout << "'" << it->first << "': " << it->second << '\n';
}

bool check_again() {
	std::cout << "Continue? (Y/N)>";
	char anwser;
	while (!(std::cin >> anwser) || std::cin.peek() != '\n' || anwser != 'Y' && anwser != 'y' && anwser != 'N' && anwser != 'n') {
		std::cin.clear(); //очищаем поток от флага ошибки
		std::cin.ignore(32767, '\n'); //очищаем поток от символов
		std::cout << "Error, enter Y or N>";
	}
	std::cin.ignore(32767, '\n'); //очищаем поток от символов
	return(anwser == 'Y' || anwser == 'y');
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	bool again = true;
	std::cout << "Letter frequency\n";
	while (again) {
		std::string fin_name = input_filename();
		std::string str = read_string(fin_name);
		std::map<char, double>characters=counting_chars(str);
		output(characters);
		again = check_again();
	}
}