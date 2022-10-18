#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <vector>
using namespace std;

int n;
double summ_n;
double epsilon;
double x=10,new_x, alpha;//переменной x ставим значение, которое у нее никогда не может быть(чтобы при проверке в if при первом вводе x выдавалось false)
double current_a, next_a;
vector<int>numbers_of_elements; //создаем четыре вектора: номера элементов, элементы, суммы и погрешности
vector<double>elements;
vector<double>summs;
vector<double>epsilons;

double input_x() {
	cout << "*******************************************************************************\n";
	cout << "Enter x from -1 to 1: ";
	double input;
	while (!(cin >> input) || cin.peek() != '\n'|| input > 1 || input < -1) // проверка введенного x
	{
		cin.clear();
		cin.ignore(32767, '\n');//очистка потока ввода
		cout << "Error, enter x again: ";
	}
	cin.ignore(32767, '\n');// очищаем поток для следующего ввода
	return input; 
}

double input_alpha() {
	double input;
	cout << "Enter a positive alpha: ";
	while (!(cin >> input) || cin.peek() != '\n' || input < 0) // проверка введенного альфа
	{
		cin.clear();
		cin.ignore(32767, '\n');//очистка потока ввода
		cout << "Error, enter alpha again: ";
	}
	cin.ignore(32767, '\n'); // очищаем поток для следующего ввода
	return input;
}

void output(int n,double a,double s,double eps)
{
	cout << "n = " << setw(5) << n << " | "
		<< "An = " << setw(15) << a << " | " // вывод значений
		<< "Sn = " << setw(15) << s << " | "
		<< "En = " << setw(15) << eps << endl;
}

void calculation(double x, int n) { // вычисление новых значений, вывод их в консоль и добавление в массив
	numbers_of_elements.push_back(n);
	current_a = next_a;   //текущий элемент суммы-это бывший следующий член
	elements.push_back(current_a);
	summ_n += 2*current_a;//прибавляем 2 текущих члена, т.к. каждый член содержится в сумме дважды
	summs.push_back(summ_n);
	next_a = (pow(-1, n + 2) * pow(x, 2 * (n + 1) + 1)) / (4*(n+1)*(n+1) - 1);//следующее а
	epsilon = fabs(next_a / summ_n);// погрешность
	epsilons.push_back(epsilon);
	output(n, current_a, summ_n, epsilon);
}

bool check_again() {
	cout << "Do you want to continue? Y/N";
	char anwser;
	while (!(cin >> anwser) || cin.peek() != '\n' || (anwser != 'y' && anwser != 'Y' && anwser != 'n' && anwser != 'N')) {
		cin.clear();
		cin.ignore(32767, '\n');
		cout << "Error, enter Y or N: ";
	}
	if (anwser == 'y' || anwser == 'Y')
		return true;
	else
		return false;
}

int main()
{
	bool again=true; //переменная, обозначающая, хочет ли пользователь продолжить 
	while (again)
	{
		n = 0;
		epsilon = 1000; //погрешность изначально задаем большую, чтобы цикл while запустился
		new_x = input_x(); //ввод x
		alpha = input_alpha(); //ввод альфа
		if (new_x == x) {
			if ((alpha == (int)alpha && alpha < numbers_of_elements.back()) || (alpha != (int)alpha && epsilons.back() < alpha))
				cout << "The value has already been calculated with greater accuracy\n";
			cout << "Previous calculations:\n";
			for (int i = 0; i<numbers_of_elements.size(); i++)
				output(numbers_of_elements[i], elements[i], summs[i], epsilons[i]);
			n = numbers_of_elements.back(); //присваиваем переменным последние записанные значения
			summ_n = summs.back();
			epsilon = epsilons.back();
		}
		else{
			numbers_of_elements.clear(); //очищаем все векторы
			elements.clear();
			summs.clear();
			epsilons.clear();
			x = new_x; //заменяем переменную x последним введенным значением
			next_a= pow(x, 3) / 3;//рассчитываем первый элемент a, чтобы в функции присвоить это значение переменной current_a
			summ_n = x;//присваиваем сумме значение x, т.к. x стоит за знаком суммы (его мы прибавляем до начала цикла)
		}
		if (alpha == (int)alpha) //если введено целое альфа
		{
			if (n <= alpha) //условие входа в цикл означает что у нас будет хотя бы одно новое вычисление
				cout<<"New calculations:\n";
			for (n+=1; n <= alpha; n++)
				calculation(x, n);
		}
		else //если введено дробное альфа
		{
			if (epsilon>alpha)
				cout << "New calculations:\n";
			while (epsilon > alpha) {
				n++; // увеличить номер итерации
				calculation(x, n);
			}
		}
		again = check_again();
	}
}
