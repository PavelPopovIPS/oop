// study.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

void CopyStream(std::istream& input, std::ostream& output)
{

}

int Add(int a, int b)
{

}

void Swap(int& a, int& b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

void AppendEndOfLine(std::string& s)
{
    s += '\n';
}

int main(int argc, char* argv[])
{
    std::string s = "hello";
    AppendEndOfLine(s);
    int x = 42;
    int y = 13;
    Swap(x, y);

    //Проверяем необходимое количество аргументов
    if (argc != 3) {
        std::cout << "Error was occured\n";
        std::cout << "Must be 2 arguments: study.exe <input file name> <output file name>\n";
        //Поменять название программы.
        return 1;
    }

    // Открываем файл для чтения
    std::ifstream input;
    input.open(argv[1]);
    if (!input.is_open())
    {
        std::cout << "File " << argv[1] << " did not opened for reading\n";
        return 1;
    }

    // Открываем файл для чтения
    std::ofstream output;
    output.open(argv[2]);
    if (!output.is_open())
    {
        std::cout << "File " << argv[2] << " did not opened for writining\n";
        return 1;
    }

    // Копируем содержимое файла 
    char ch;
    while (input.get(ch)) 
    {
        if (!output.put(ch)) 
        {
            break; 
        }
    }

    if (input.bad())
    {
        std::cout << "Failed to read data from file\n";
        return 1;
    }

    if (!output.flush())
    {
        std::cout << "Failed to write to file\n";
        return 1;
    }

    return 0;
}
