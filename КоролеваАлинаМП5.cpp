#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class WorkTime {
private:
    std::string date, time1,time2;
    bool check_date()
    {
        if (date.size() != 5) //сначала проверяем формат строки дд:мм
            return false;
        if (!isdigit(date[0]) || !isdigit(date[1]) || date[2] != '.' || !isdigit(date[3]) || !isdigit(date[4]))
            return false;
        int day = stoi(date.substr(0, 2)); //после проверки формата переводим день и месяц в int и проверяем их величину
        int month = stoi(date.substr(3, 2));
        if (month < 1 || month > 12) //проверяем месяц
            return false;
        int days_in_month[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if (day <1 || day > days_in_month[month - 1]) //проверяем день
            return false;
        return true;
    }

    bool check_time()
    {
        if (time1.size() != 5 || time2.size() != 5) //сначала проверяем формат строки чч:мм
            return false;
        if (!isdigit(time1[0]) || !isdigit(time1[1]) || time1[2] != ':' || !isdigit(time1[3]) || !isdigit(time1[4]))
            return false;
        if (!isdigit(time2[0]) || !isdigit(time2[1]) || time2[2] != ':' || !isdigit(time2[3]) || !isdigit(time2[4]))
            return false;
        int hour1 = stoi(time1.substr(0, 2)); //переводим часы и минуты в int
        int hour2 = stoi(time2.substr(0, 2));
        int minute1 = stoi(time1.substr(3, 2));
        int minute2 = stoi(time2.substr(3, 2));
        if (hour1 < 0 || hour1>23 || hour2 < 0 || hour2>23) //проверка часов
            return false;
        if (minute1 < 0 || minute1>59 || minute2 < 0 || minute2>59) //проверка минут
            return false;
        if (hour1 > hour2 || (hour1 == hour2 && minute1 > minute2)) //проверка, чтобы начальное время не было больше конечного
            return false;
    }
    
public:
    WorkTime()
    {
        date = "01.01";
        time1 = "00:00";
        time2 = "23:59";
    }
    WorkTime(std::string d, std::string t1, std::string t2)
    {
        date = d;
        time1 = t1;
        time2 = t2;
    }
    ~WorkTime() //деструктор
    {
    }

    std::string get_date() { return date; }
    std::string get_start() { return time1; }
    std::string get_end() { return time2; }

    void set_date(std::string new_date) { date = new_date; }
    void set_start(std::string new_start) { time1 = new_start; }
    void set_end(std::string new_end) { time2 = new_end; }

    std::string work_hours()
    {
        int hour1 = stoi(time1.substr(0, 2)); //инициализируем целочисленные переменные часов и минут начала и конца
        int hour2 = stoi(time2.substr(0, 2));
        int minute1 = stoi(time1.substr(3, 2));
        int minute2 = stoi(time2.substr(3, 2)); 
        int minute_result, hour_result;
        if (minute2 - minute1 >= 0) { //если минут конца больше или = минут начала, считаем обычным образом
            minute_result = minute2 - minute1;
            hour_result = hour2 - hour1;
        }
        else { //если минут конца меньше чем минут начала, мы "занимаем" один час
            minute_result = minute2 - minute1+60;
            hour_result = hour2 - hour1-1;
        }
        std::string result; //создаем строку для вывода результата
        result += (hour_result < 10) ? ("0" + std::to_string(hour_result)) : (std::to_string(hour_result));
        result += ":";
        result += (minute_result < 10) ? ("0" + std::to_string(minute_result)) : (std::to_string(minute_result));
        return result;
    }

    friend std::ostream& operator<<(std::ostream&, WorkTime&);
    friend std::istream& operator>>(std::istream&, WorkTime&);
    friend std::ofstream& operator<<(std::ofstream&, WorkTime&);
    friend std::ifstream& operator>>(std::ifstream&, WorkTime&);
};

std::istream& operator>>(std::istream& in, WorkTime& c)
{
    std::cout << "Input date in format (dd.mm): ";
    while ( !(in>>c.date) || in.peek()!='\n'|| !c.check_date()) {
        std::cout << "Incorrect date format. Enter date again: ";
        in.clear();
        while (in.get() != '\n'); // очистка потока после неправильно введенной даты
    }
    std::cout << "Input start time in format (hh.mm): ";
    while (!(in >> c.time1) || in.peek() != '\n' || !c.check_time()) {
        std::cout << "Incorrect time format. Enter start time again: ";
        in.clear();
        while (in.get() != '\n'); // очистка потока после неправильно введенного времени
    }
    std::cout << "Input end time in format (hh.mm): ";
    while (!(in >> c.time2) || in.peek() != '\n' || !c.check_time()) {
        std::cout << "Incorrect time format. Enter end time again: ";
        in.clear();
        while (in.get() != '\n'); // очистка потока после неправильно введенной даты
    }
    return in;
}
    

std::ostream& operator << (std::ostream& out, WorkTime& c)
{
    out << c.date << ' ' << c.time1 << ' ' << c.time2;
    return out;
}

std::ifstream& operator>>(std::ifstream& in, WorkTime& obj)
{
    in >> obj.date; //сначала берем дату из потока
    in >> obj.time1;
    in >> obj.time2;
    if (!obj.check_date())
        obj.date = "error";
    if (!obj.check_time())
        obj.time1 = obj.time2 = "error";
    return in;
}

std::ofstream& operator << (std::ofstream& fout, WorkTime& c)
{
    fout << c.date << ' ' << c.time1 << ' ' << c.time2;
    return fout;
}

char input_option(std::string description) {
    std::cout << description;
    char opt;
    std::cout << "Enter 1 or 2: ";
    while (!(std::cin >> opt) || std::cin.peek() != '\n' || opt != '1' && opt != '2' && opt != '3') {
        std::cin.clear(); //очищаем поток от флага ошибки
        std::cin.ignore(32767, '\n'); //очищаем поток от символов
        std::cout << "Error, enter 1 or 2: ";
    }
    return opt;
}

int input_num_of_elements() {
    int n;
    std::cout << "Enter the number of elements in array: ";
    while (!(std::cin >> n) || std::cin.peek() != '\n' || (n < 2)) { //пока не введено n, или следующий символ не равен переводу строки, или введено меньше двух
        std::cin.clear(); //очищаем поток от флага ошибки
        std::cin.ignore(32767, '\n'); //очищаем поток от символов
        std::cout << "Error, enter a positive number bigger than 1: ";
    }
    return n;
}

std::vector<WorkTime> input_vector(int length) {
    std::vector<WorkTime> array;
    for (int i = 1; i <= length; i++) {
        WorkTime a;
        std::cout << "Object " << i << std::endl;
        std::cin >> a;
        array.push_back(a);
    }
    return array;
}

std::string input_filename() {
    //std::cin.get(); //убираем из потока символ перевода строки, оставшийся там после предыдущего ввода (для getline)
    std::cout << "Enter the file name: ";
    std::string filename;
    bool correct_file = false;
    while (!correct_file) {
        getline(std::cin, filename);
        std::ifstream infile(filename);
        if (!infile.is_open())
            std::cout << "Error, the file cannot be opened.\nEnter the file name again: ";
        else if (infile.peek() == EOF)
            std::cout << "Error, this file is empty.\nEnter the file name again: ";
        else
            correct_file = true;
    }
    return filename;
}

std::vector<WorkTime> input_vector_from_file() {
    std::vector<WorkTime> array;
    bool correct_file = false;
    std::cin.get(); //убираем из потока символ перевода строки, оставшийся там после предыдущего ввода (для getline)
    while (!correct_file) {
        std::string filename = input_filename();
        std::ifstream fin(filename);
        bool correct_elements = true;
        for (int i = 1; fin.peek() != EOF && correct_elements; i++) {
            WorkTime a;
            fin >> a;
            if (a.get_date() == "error"){
                std::cout << "Error on line " << i << " (wrong date format). ";
                correct_elements = false;
            }
            else if (a.get_start() == "error" || a.get_end() == "error"){
                std::cout << "Error on line " << i << " (wrong time format). ";
                correct_elements = false;
            }
            else
                array.push_back(a);
        }
        if (correct_elements)
            correct_file = true;
        else
            array.clear(); //если ввод состоялся неправильно, очищаем массив
    }
    std::cout << "Input was successful.\n";
    return array;
}

std::vector<std::string> calculating_results(std::vector<WorkTime>& v){
    std::vector<std::string> results;
    for (int i = 0; i < v.size(); i++) {
        results.push_back(v[i].work_hours());
    }
    return results;
}

void output(std::vector<WorkTime>& v) { //вывод в консоль вектора экземпляров класса
    std::cout << "Array of class objects:\n";
    for (int i = 0; i < v.size(); i++) {
        std::cout << i + 1 << ". " << v[i] << std::endl;
    }
}

void output(const std::vector<std::string>& v) { //вывод в консоль вектора результатов
    std::cout << "Array of results:\n";
    for (int i = 0; i < v.size(); i++) {
        std::cout << i + 1 << ". " << v[i] << std::endl;
    }
}

void output(std::ofstream& fout, std::vector<WorkTime>& v) { //вывод в файл вектора экземпляров класса
    fout << "Array of class objects:\n";
    for (int i = 0; i < v.size(); i++) {
        fout << i + 1 << ". " << v[i] << std::endl;
    }
}

void output(std::ofstream& fout, const std::vector<std::string>& v) { //вывод в файл вектора результатов
    fout << "Array of results:\n";
    for (int i = 0; i < v.size(); i++) {
        fout << i + 1 << ". " << v[i] << std::endl;
    }
}

bool check_again() {
    std::cout << "Do you want to continue? Y/N: ";
    char anwser;
    while (!(std::cin >> anwser) || std::cin.peek() != '\n' || anwser != 'Y' && anwser != 'y' && anwser != 'N' && anwser != 'n') {
        std::cin.clear(); //очищаем поток от флага ошибки
        std::cin.ignore(32767, '\n'); //очищаем поток от символов
        std::cout << "Error, enter Y or N: ";
    }
    return(anwser == 'Y' || anwser == 'y');
}

int main()
{
    bool again = true;
    std::vector<WorkTime> objects; //создаем наш вектор экземпляров класса
    std::vector<std::string> results; //вектор результатов задания
    while (again) {
        char in_option = input_option("How do you want to input the elements?\n1 - From keyboard\n2 - From file\n");
        if (in_option == '1') { //ввод с консоли
            int num_of_elements = input_num_of_elements();
            objects = input_vector(num_of_elements);
        }
        else { //ввод из файла
            std::cout << "Each element must be on a separate line in the format (dd.mm hh:mm hh:mm)\n";
            objects = input_vector_from_file();
        }
        results = calculating_results(objects);
        char out_option = input_option("How do you want to output the elements?\n1 - To console\n2 - To file\n");
        if (out_option == '1') { //вывод в консоль
            output(objects);
            output(results);
        }
        else {
            std::ofstream fout("output.txt", std::ios_base::app);
            output(fout, objects);
            output(fout, results);
            std::cout<<"Results are output to file output.txt\n";
        }
        objects.clear(); //очищаем векторы
        results.clear();
        again = check_again();
    }
}