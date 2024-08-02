#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <string.h>
#include <iomanip>
#include <ctime>
#include "tools.h"

class Admin
{
private:
    std::string _strID, _strPassword;
public:
    Admin(std::string strID = "", std::string strPassword = "");
    Admin(const Admin& admin);
    ~Admin();
    bool login();
    std::string getPassword();
    void renderXuLyDonHang();
    void renderQuanLyHangHoa();
    void renderMenuAdmin();
    void renderTaoHangHoa();
    void renderXoaHangHoa();
    void renderCapNhatSoLuong();
};