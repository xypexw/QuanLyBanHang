#include "HangHoa.h"
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <thread>
#include <chrono>

Stack<string> HangHoa::_deletedIDs;

int HangHoa::soHangHoa() {
    ifstream file("DanhSachHangHoa.txt");
    string line;
    int cnt = 0;
    while (getline(file, line)) {
        ++cnt;
    }
    file.close();
    return cnt;
}


void HangHoa::taoHangHoa(string name, string origin, string color, int price, string entryDate, int amount) {
    ofstream file("DanhSachHangHoa.txt", ios::app); 
    if (!file.is_open()) {
        cerr << "Failed to open file" << endl;
        return;
    }

    string id;
    int soHangHoa = HangHoa::soHangHoa();

    if(!_deletedIDs.isEmpty()){
        id = _deletedIDs.pop();
    } else{
        id = to_string(soHangHoa + 1);
        while(id.length() < 4){ 
            id = '0' + id;
        }
    }
    file << id << " " << name << " " << origin << " " << color << " "
         << price << " " << entryDate << " " << amount << endl;
    file.close();
}


void HangHoa::xoaHangHoa(string ma) {
    ifstream inputFile("DanhSachHangHoa.txt");
    ofstream tempFile("TempDanhSachHangHoa.txt");

    if (!inputFile.is_open() || !tempFile.is_open()) {
        cerr << "Failed to open file" << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string id;
        iss >> id;
        if (id != ma) {
            tempFile << line << endl;
        } else {
            found = true;
            _deletedIDs.push(id);
        }
    }

    inputFile.close();
    tempFile.close();

    if (found) {
        remove("DanhSachHangHoa.txt");
        rename("TempDanhSachHangHoa.txt", "DanhSachHangHoa.txt");
        cout << "Xoa Hang Hoa Thanh Cong" << endl;
    } else {
        remove("TempDanhSachHangHoa.txt");
        cout << "Khong Tim Thay Hang Hoa" << endl;
    }
}


void HangHoa::capNhatSoLuong(string ma, int soluong) {
    if (soluong <= 0) {
        cout << "So luong phai lon hon 0" << endl;
        return;
    }

    ifstream inputFile("DanhSachHangHoa.txt");
    ofstream tempFile("TempDanhSachHangHoa.txt");

    if (!inputFile.is_open() || !tempFile.is_open()) {
        cerr << "Failed to open file" << endl;
        return;
    }

    string line;
    bool found = false;

    while (getline(inputFile, line)) {
        istringstream iss(line);
        string id;
        iss >> id;
        if (id == ma) {
            string name, origin, color, entryDate;
            int price, amount;
            iss >> name >> origin >> color >> price >> entryDate >> amount;
            // Update so luong
            amount = soluong;
            tempFile << id << " " << name << " " << origin << " " << color << " " << price << " " << entryDate << " " << amount << endl;
            found = true;
        } else {
            tempFile << line << endl;
        }
    }

    inputFile.close();
    tempFile.close();

    if (found) {
        remove("DanhSachHangHoa.txt");
        rename("TempDanhSachHangHoa.txt", "DanhSachHangHoa.txt");
        cout << "Cap nhat so luong thanh cong" << endl;
    } else {
        remove("TempDanhSachHangHoa.txt");
        cout << "Ma hang hoa khong co trong danh sach hang hoa" << endl;
    }
}

void HangHoa::timkiemhoanghoa() {
    ifstream input("TiemKiemHangHoa.txt");
    ofstream output("TiemKiemHangHoa.txt");
    string tentimkiem;
    if (!input || !output) {
        cerr << "Không thể mở file!" << endl;
        return;
    }
    input >> tentimkiem;
    bool timthay = false;

    HangHoa* hangcantim = head;
    while (hangcantim != NULL) {
        if (hangcantim->name == tentimkiem) {
            timthay = true;
            break;
        }
        hangcantim = hangcantim->next;
    }

    if (!timthay) {
        output << "Không tìm thấy hàng hóa." << endl;
    }
    else {
        int dorongcuama = 10;
        int dorongcuaten = 20;
        int dorongcuaorigin = 20;
        int dorongcuacolor = 10;
        int dorongcuaentrydate = 15;
        output << std::left << std::setw(dorongcuama) << "Ma"
            << std::left << std::setw(dorongcuaten) << "Name"
            << std::left << std::setw(dorongcuaorigin) << "Origin"
            << std::left << std::setw(dorongcuacolor) << "Color"
            << std::left << std::setw(dorongcuaentrydate) << "EntryDate"
            << std::endl;

        output << std::setfill('-') << std::setw(dorongcuama) << ""
            << std::setw(dorongcuaten) << ""
            << std::setw(dorongcuaorigin) << ""
            << std::setw(dorongcuacolor) << ""
            << std::setw(dorongcuaentrydate) << ""
            << std::setfill(' ') << std::endl;

        output << std::left << std::setw(dorongcuama) << hangcantim->ma
            << std::left << std::setw(dorongcuaten) << hangcantim->name
            << std::left << std::setw(dorongcuaorigin) << hangcantim->origin
            << std::left << std::setw(dorongcuacolor) << hangcantim->color
            << std::left << std::setw(dorongcuaentrydate) << hangcantim->entryDate
            << std::endl;
    }
    input.close();
    output.close();
}
