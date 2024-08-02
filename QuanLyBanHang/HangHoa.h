#pragma once
#include<iostream>
#include "Stack.h"
using namespace std;

class HangHoa {
private:
    char _cMa[5]; //size + 1 cho null terminator
    string _StrName, _StrOrigin, _strColor, _strEntryDate;
    int _iPrice, _iAmount;
    HangHoa* _pNext;
    static HangHoa* _pHead;
    static int _iCounter;
    static Stack<string> _deletedIDs;
public:
    HangHoa(){}
    ~HangHoa(){}
    static void saveToFIle();
    void taoHangHoa(string name, string origin, string color, int price, string entryDate, int amount);
    static void xoaHangHoa(string ma);
    static void capNhatSoLuong(string ma, int soluong);
    void timkiemhoanghoa();
};
