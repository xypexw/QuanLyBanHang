#pragma once
#include<iostream>
#include "Stack.h"
using namespace std;

class HangHoa {
private:
    char ma[5]; //size + 1 cho null terminator
    string name, origin, color, entryDate;
    int price, amount;
    HangHoa* next;
    static HangHoa* head;
    static int counter;
    static Stack<string> deletedIDs;
public:
    HangHoa(){}
        ~HangHoa(){}
        static void saveToFIle();
        void taoHangHoa(string name, string origin, string color, int price, string entryDate, int amount);
        static void xoaHangHoa(string ma);
};