#include <iostream>
#include <vector>

int input_num_of_elements()
{
    int n;
    std::cout << "Input the number of integers>";
    while (!(std::cin >> n) || std::cin.peek() != '\n' || n <= 1) {
        std::cout << "Error, enter an integer greater than 1>";
        std::cin.clear();
        while (std::cin.get() != '\n');
    }
    return n;
}

std::vector<int> input_array(std::string num_of_array)
{
    std::cout << num_of_array << " array\n";
    int num_of_elements = input_num_of_elements(); //ввод числа элементов
    std::vector<int>array;
    for (int i = 1; i <= num_of_elements; i++) { //ввод элементов
        std::cout << "Input the integer #" << i << ">";
        int n;
        while (!(std::cin >> n) || std::cin.peek() != '\n' ) {
            std::cout << "Error, enter an integer>";
            std::cin.clear();
            while (std::cin.get() != '\n');
        }
        array.push_back(n);
    }
    return array;
}

bool find_in_array(int n, std::vector<int>& v)
{
    for (int i : v)
        if (i == n)
            return true;
    return false;
}

std::vector<int> common_numbers(const std::vector<int>& array1, const std::vector<int>& array2)
{
    std::vector<int>result;
    for (int i : array1)
        for (int j : array2) 
            if ( (i == j)&&(!find_in_array(i,result)) )
                result.push_back(i);
    return result;
}

void output(const std::vector<int>& v)
{
    std::cout << "Result: ";
    for (int i=0;i<v.size()-1;i++) //выводим в цикле элементы с первого по предпоследний, потому что после последнего элемента не нужна запятая
        std::cout << v[i] << ", ";
    std::cout << v[v.size() - 1] << std::endl;
}

bool check_again()
{
    std::cout << "Continue? (Y/N)>";
    char anwser;
    while (!(std::cin >> anwser) || std::cin.peek() != '\n' || (anwser != 'Y' && anwser != 'y' && anwser != 'N' && anwser != 'n')) {
        std::cout << "Error, enter Y or N>";
        std::cin.clear();
        while (std::cin.get() != '\n');
    }
    return(anwser == 'Y' || anwser == 'y');
}

int main()
{
    std::cout << "Arrays intersection\n";
    bool again = true;
    while (again) {
        std::vector<int>array1 = input_array("First");
        std::vector<int>array2 = input_array("Second");
        std::vector<int>result = common_numbers(array1, array2);
        output(result);
        again = check_again();
    }
}
