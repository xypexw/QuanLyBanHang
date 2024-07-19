#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <iomanip>
#include <ctime>
#include "Admin.h"
#include "tools.h"


//Thiet ke class UI. Khai báo các bien và hàm trong class UI
class UI
{
public:
    UI();
    ~UI();
    void renderWelcomeScreen();    
    void renderGoodByeScreen();    

    //--------------------------------------------------------------
    void renderLoginScreen();       
    void renderMenuScreen();
    void renderDatHang();
    void renderTimKiem();
    void renderDSHangHoa();
};
