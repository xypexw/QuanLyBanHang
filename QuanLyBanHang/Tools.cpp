
#include <Windows.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "tools.h"

//Cac bien toan cuc
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbi;
WORD defaultWordAttributes; //Mau chu mac dinh cua cua so console
int width; //Chieu rong cua cua so console
int height; // Chieu cao cua cua so consele

void initRandomSeed()
{
    srand(time(0));
}

//Hàm thay doi mau chu Random
int getRandNum()
{
    return rand() % 5 + 10;
}

//Hàm can chinh vi tri van ban theo chieu rong
void alignTextPositionWidth(std::string text, float n)
{
    // Calculate the number of spaces to pad before the text
    float padding = (float)(width - text.length()) / n;

    // Print the padding and then the text
    for (int i = 0; i < padding; ++i)
        std::cout << " ";
}

//Hàm can chinh vi tri van ban theo chieu cao
void alignTextPositionHeight(float n)
{
    float padding = (float)height / n;
    for (int i = 0; i < padding; i++)
    {
        std::cout << '\n';
    }
}

//Hàm tính chieu cao heigh, chieu rong width va mau chu mac dinh cua cua so console    
void getDefaultAttribute()
{
    GetConsoleScreenBufferInfo(hConsole, &csbi); //Lay du lieu bo nho dem cua cua so console de tinh
    defaultWordAttributes = csbi.wAttributes; //Lay may chu mac dinh
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1; //Tính chieu cao
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1; //Tính chieu rong
}

//Hàm reset Color ve lai mau chu mac dinh
void resetColor()
{
    SetConsoleTextAttribute(hConsole, defaultWordAttributes);
}

//Hàm thay doi mau chu cho van ban
void textColor(int n)
{
    SetConsoleTextAttribute(hConsole, n);
}
