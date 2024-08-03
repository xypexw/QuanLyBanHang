#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <iomanip>
#include <ctime>
#include <conio.h>
#include <thread>
#include <chrono>
#include "Admin.h"
#include "tools.h"
#include "UI.h"
#include "HangHoa.h"
#include "DonHang.h"
Admin::Admin(std::string strID, std::string strPassword) 
{}

Admin::Admin(const Admin& admin)
{}

Admin::~Admin() {}
std::string Admin::getPassword() {
    std::string password;
    char ch;

    std::cout << "Enter password (Enter ESC to Exit): ";
    while ((ch = _getch()) != '\r') { // '\r' l� k� t? k?t th�c (Enter)
        if (ch == 8) { // X? l� k� t? Backspace
            if (!password.empty()) {
                password.pop_back();
                std::cout << "\b \b"; // X�a k� t? cu?i c�ng tr�n m�n h�nh
            }
        }
        else {
            password += ch;
            std::cout << '*';
        }
    }
    std::cout << std::endl;
    std::cin.clear();
    return password;
}

bool Admin::login()
{
    UI ui;
    bool bCheck = false;
    std::ifstream ifAdminFile;
    int iCount = 0;
    while (iCount < 3)
    {
        ifAdminFile.open("admin.txt", std::ios::in);
        std::string strID;
        std::cout << "Enter ID: ";
        getline(std::cin, strID);
        std::string strPassword = getPassword();
        if (strPassword == "ESC") 
        {
            system("cls");
            ui.renderWelcomeScreen();
        }
        if (ifAdminFile.is_open())
        {
            std::string strFileLine;
            while (std::getline(ifAdminFile, strFileLine))
            {
                std::stringstream ss(strFileLine);
                std::string strfileID;
                std::string strfilePassword;
                ss >> strfileID;
                ss >> strfilePassword;
                if (strfileID == strID && strfilePassword == strPassword)
                {
                    bCheck = true;
                }
            }
            ifAdminFile.close();
        }
        if (bCheck)
        {
            std::cout << "login successfully" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            return true;
        }
        else
        {
            std::cout << "ID or password incorrect" << std::endl;
            iCount++;
        }
    }
    if(bCheck == false)
    std::cout << "login falied" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    system("cls");
    ui.renderWelcomeScreen();
    return false;
}
void Admin::renderXuLyDonHang()
{
    UI ui;
    system("cls");                                      //
    getDefaultAttribute();                              //
    std::ifstream iFileOpen;                            //
    iFileOpen.open("XuLyDonHang.txt", std::ios::in);    //
    alignTextPositionHeight(20);                        //
    textColor(14);                                      //
    if (iFileOpen.is_open())                            // Hien thi màn hình chuc nang xu lý don hang tu file XyLyDonHang.txt
    {                                                   //
        textColor(14);                                  //
        std::string strFileLine;                        //
        while (getline(iFileOpen, strFileLine))         //
        {                                               //
            alignTextPositionWidth(strFileLine, 2);     //
            std::cout << strFileLine << std::endl;      //
        }                                               //
    }

    std::cout << std::endl;
    DonHang a;
    std::ifstream orderFile("DonHang.txt");
    if (orderFile.is_open())
    {
        std::string orderInfo;
        std::cout << "Nhung don dat hang: \n";
        while (getline(orderFile, orderInfo))
        {
            std::cout << orderInfo << std::endl;
        }
        orderFile.close();
    }
    a.XuLyDonHang();
    int iChoice;
    std::cout << "Do you want go back to main menu ? press 1 for yes, 0 for no" << std::endl;
    std::cout << "Choise: ";
    std::cin >> iChoice;
    if (iChoice == 1)
    {
        system("cls");
        Admin::renderMenuAdmin();
    }
    else if (iChoice == 0)
        ui.renderGoodByeScreen();
}
void Admin::renderQuanLyHangHoa()
{
    UI ui;                                                  //
    system("cls");                                          //
    getDefaultAttribute();                                  //
    std::ifstream iFileOpen;                                //
    iFileOpen.open("QuanLyHangHoa.txt", std::ios::in);      //
    alignTextPositionHeight(20);                            //
    textColor(14);                                          //
    if (iFileOpen.is_open())                                // Hien thi màn hình chuc nang Quan lý hàng hóa tu file QuanLyHangHoa.txt
    {                                                       //
        textColor(14);                                      //
        std::string strFileLine;                            //
        while (getline(iFileOpen, strFileLine))             //
        {                                                   //
            alignTextPositionWidth(strFileLine, 2);         //
            std::cout << strFileLine << std::endl;          //
        }                                                   //
    }                                                       //
    std::cout << std::endl;

    std::cout << "Enter your choice: ";
    int iChoice;
    std::cin >> iChoice;
    if (iChoice == 1) {
        system("cls");
        Admin::renderTaoHangHoa();
    }
    if (iChoice == 2) {
        system("cls");
        Admin::renderXoaHangHoa();
    }
    if (iChoice == 3)
        Admin::renderCapNhatSoLuongHangHoa();

    if (iChoice == 4)
        Admin::renderMenuAdmin();
}
void Admin::renderMenuAdmin()
{
    UI ui;                                           //
    system("cls");                                   //
    getDefaultAttribute();                           //
    std::ifstream iFileOpen;                         //
    iFileOpen.open("Menu_Admin.txt", std::ios::in);  //
    alignTextPositionHeight(20);                     //
    textColor(14);                                   //
    if (iFileOpen.is_open())                         // Hien thi màn hình menu admin tu file Menu_Admin.txt
    {                                                //
        textColor(14);                               //
        std::string strFileLine;                     //
        while (getline(iFileOpen, strFileLine))      //
        {                                            //
            alignTextPositionWidth(strFileLine, 2);  //
            std::cout << strFileLine << std::endl;   //
        }                                            //
    }                                                //
    std::cout << std::endl;
    int iChoice;
    std::cout << "Enter your choice: ";
    std::cin >> iChoice;
    std::cin.ignore();
    if (iChoice == 4)
    {
        system("cls");
        ui.renderWelcomeScreen();
    }
    else
        if (iChoice == 3)
            ui.renderGoodByeScreen();
        else
            if (iChoice == 2)
                Admin::renderQuanLyHangHoa();
            else
                if (iChoice == 1)
                    Admin::renderXuLyDonHang();
}

void Admin::renderTaoHangHoa()
{
    UI ui;
    system("cls");                                      //
    getDefaultAttribute();                              //
    std::ifstream iFileOpen;                            //
    iFileOpen.open("TaoHangHoa.txt", std::ios::in);    //
    alignTextPositionHeight(20);                        //
    textColor(14);                                      //
    if (iFileOpen.is_open())                            // Hien thi màn hình chuc nang xu lý don hang tu file TaoHangHoa.txt
    {                                                   //
        textColor(14);                                  //
        std::string strFileLine;                        //
        while (getline(iFileOpen, strFileLine))         //
        {                                               //
            alignTextPositionWidth(strFileLine, 2);     //
            std::cout << strFileLine << std::endl;      //
        }                                               //
    }
    std::cout << std::endl;
    std::cout << "Xin moi nhap thong tin cua san pham: " << std::endl;
        std::string name, origin, color, entryDate;
        int amount, price;
        std::cout << "Ten hang hoa: ";
        std::cin.ignore();
        getline(std::cin, name);
        std::cout << "Noi san xuat: ";
        getline(std::cin, origin);
        std::cout << "Mau sac: ";
        getline(std::cin, color);
        std::cout << "So luong: ";
        std::cin >> amount;
        std::cout << "Ngay nhap kho: ";
        std::cin.ignore();
        getline(std::cin, entryDate);
        std::cout << "Gia: ";
        std::cin >> price;
        HangHoa newHangHoa;
        newHangHoa.taoHangHoa(name, origin, color, price, entryDate, amount);
        std::cout << std::endl;
        std::cout << "Hang Hoa Da Duoc Them Thanh Cong" << std::endl;
        int iChoice;
        std::cout << "Do you want go back to main menu ? press 1 for yes, 0 for no" << std::endl;
        std::cout << "Choise: ";
        std::cin >> iChoice;
        if (iChoice == 1)
        {
            system("cls");
            Admin::renderQuanLyHangHoa();
        }
        else if (iChoice == 0)
            ui.renderGoodByeScreen();
}
void Admin::renderXoaHangHoa()
{
    UI ui;
    system("cls");                                      //
    getDefaultAttribute();                              //
    std::ifstream iFileOpen;                            //
    iFileOpen.open("XoaHangHoa.txt", std::ios::in);    //
    alignTextPositionHeight(20);                        //
    textColor(14);                                      //
    if (iFileOpen.is_open())                            // Hien thi màn hình chuc nang xu lý don hang tu file XoaHangHoa.txt
    {                                                   //
        textColor(14);                                  //
        std::string strFileLine;                        //
        while (getline(iFileOpen, strFileLine))         //
        {                                               //
            alignTextPositionWidth(strFileLine, 2);     //
            std::cout << strFileLine << std::endl;      //
        }                                               //
    }
    std::cout << std::endl;
    int iChoice;
    string ma;
    cout << "Nhap ma hang hoa ban muon xoa: ";
    cin.ignore();
    getline(std::cin, ma);
    HangHoa::xoaHangHoa(ma);
    std::cout << std::endl;
    std::cout << "Do you want go back to main menu ? press 1 for yes, 0 for no" << std::endl;
    std::cout << "Choise: ";
    std::cin >> iChoice;
    if (iChoice == 1)
    {
        system("cls");
        Admin::renderQuanLyHangHoa();
    }
    else if (iChoice == 0)
        ui.renderGoodByeScreen();
} 

void Admin::renderCapNhatSoLuongHangHoa(){
    UI ui;
    system("cls");                                      
    getDefaultAttribute();                              
    std::ifstream iFileOpen;                            
    iFileOpen.open("CapNhatSoLuongHangHoa.txt", std::ios::in);    
    alignTextPositionHeight(20);                        
    textColor(14);                                      
    if (iFileOpen.is_open())                            
    {                                                   
        textColor(14);                                  
        std::string strFileLine;                        
        while (getline(iFileOpen, strFileLine))         
        {                                               
            alignTextPositionWidth(strFileLine, 2);     
            std::cout << strFileLine << std::endl;      
        }                                               
    }
    cout << endl;
    string ma;
    int soluong;
    cout << "Nhap so ma hang hoa can cap nhat: ";
    cin.ignore();
    getline(cin,ma);
    cout << "Nhap so luong: ";
    cin >> soluong;
    HangHoa::capNhatSoLuong(ma,soluong);
    int iChoice;
    std::cout << std::endl;
    std::cout << "Do you want go back to main menu ? press 1 for yes, 0 for no" << std::endl;
    std::cout << "Choise: ";
    std::cin >> iChoice;
    if (iChoice == 1)
    {
        system("cls");
        Admin::renderQuanLyHangHoa();
    }
    else if (iChoice == 0)
        ui.renderGoodByeScreen();
}