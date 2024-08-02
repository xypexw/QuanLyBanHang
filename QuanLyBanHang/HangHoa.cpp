#include "HangHoa.h"
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <thread>
#include <chrono>

HangHoa* HangHoa::_pHead = NULL;
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

void HangHoa::timkiemhoanghoa() {
    ifstream input("TiemKiemHangHoa.txt");
    ofstream output("TiemKiemHangHoa.txt");
    string tentimkiem;
    input >> tentimkiem;
    bool timthay = false;
    for (HangHoa* hangcantim = _pHead; hangcantim != NULL; hangcantim = hangcantim->_pNext) {
        if (hangcantim->_StrName == tentimkiem) {
            output << hangcantim->_cMa << ", " << hangcantim->_StrName << ", " << hangcantim->_StrOrigin
                << ", " << hangcantim->_strColor << ", " << hangcantim->_iPrice << ", "
                << hangcantim->_strEntryDate << ", " << hangcantim->_iAmount << endl;
            timthay = true;
        }
    }
    if (!timthay) {
        output << "Không tìm thấy hàng hóa." << endl;
    }
    input.close();
    output.close();
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
