#include "include/ONF.h"
#include <iostream>
#include <locale>


int main()
{
    setlocale(LC_ALL, "rus");
    std::wcout << L"Привет!" << std::endl;
    return 0;
}
