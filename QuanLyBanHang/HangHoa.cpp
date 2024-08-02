#include "HangHoa.h"
#include <fstream>
#include <cstdio>
#include <cstring>
#include "Stack.h"
#include <thread>
#include <chrono>

void HangHoa::saveToFIle() {
    ofstream file("DanhSachHangHoa.txt", ios::out);
    if (file.is_open()) {
        HangHoa* dummy = _pHead;
        while (dummy != NULL) {
            // ma, ten, noi sx, mau sac, gia ban, ngay nhap, so luong
            file << dummy->_cMa << " " << dummy->_StrName << " " << dummy->_StrOrigin << " " 
                 << dummy->_strColor << " " << dummy->_iPrice << " " << dummy->_strEntryDate << " " 
                 << dummy->_iAmount << endl;
            dummy = dummy->_pNext;
        }
        file.close();
    } else {
        cerr << "Failed to open file";
    }
}

int HangHoa::_iCounter = 1;
HangHoa* HangHoa::_pHead = NULL;
Stack<string> HangHoa::_deletedIDs;

void HangHoa::taoHangHoa(string name, string origin, string color, int price, string entryDate, int amount) {
    HangHoa* newNode = new HangHoa();
    newNode->_StrName = name;
    newNode->_StrOrigin = origin;
    newNode->_strColor = color;
    newNode->_iPrice = price;
    newNode->_strEntryDate = entryDate;
    newNode->_iAmount = amount;
    newNode->_pNext = NULL;       

    if (_pHead == NULL) {
        _pHead = newNode;
        if (!_deletedIDs.isEmpty()) {
            string id = _deletedIDs.pop();
            strncpy_s(newNode->_cMa, id.c_str(), sizeof(newNode->_cMa) - 1);
            newNode->_cMa[sizeof(newNode->_cMa) - 1] = '\0';
        } else {
            snprintf(newNode->_cMa, sizeof(newNode->_cMa), "%04d", _iCounter++);
        }
    } else {
        HangHoa* tmp = _pHead;
        bool flag = false;
        while (tmp != NULL) {
            if (newNode->_StrName == tmp->_StrName && newNode->_StrOrigin == tmp->_StrOrigin 
                && newNode->_strColor == tmp->_strColor && newNode->_strEntryDate == tmp->_strEntryDate) {
                tmp->_iAmount += newNode->_iAmount;
                delete newNode;
                flag = true;
                break;
            }
            if (tmp->_pNext == NULL) {
                break;
            }
            tmp = tmp->_pNext;
        }
        if (!flag) {
            tmp->_pNext = newNode;
            if (!_deletedIDs.isEmpty()) {
                string id = _deletedIDs.pop();
                strncpy_s(newNode->_cMa, id.c_str(), sizeof(newNode->_cMa) - 1);
                newNode->_cMa[sizeof(newNode->_cMa) - 1] = '\0';
            } else {
                snprintf(newNode->_cMa, sizeof(newNode->_cMa), "%04d", _iCounter++);
            }
        }
    }
    HangHoa::saveToFIle();
}    

void HangHoa::xoaHangHoa(string ma) {
    HangHoa *tmp = _pHead;
    HangHoa* prev = NULL;
    bool found = false;
    while (tmp != NULL) {
        if (ma == tmp->_cMa) {
            found = true;
            if (prev == NULL) {
                _pHead = tmp->_pNext;
            } else {
                prev->_pNext = tmp->_pNext;
            }
            break;
        }
        prev = tmp;
        tmp = tmp->_pNext;
    }
    if (found) {
       _deletedIDs.push(tmp->_cMa);
       delete tmp;
       HangHoa::saveToFIle();
       cout << "Xoa Hang Hoa Thanh Cong";
    } else {
        cout << "Khong Tim Thay Hang Hoa";
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
    HangHoa* tmp = _pHead;
    if (tmp == NULL) {
        cout << "Danh sach hang hoa dang trong!" << endl;
    } else {
        bool found = false;
        while (tmp != NULL) {
            if (tmp->_cMa == ma) {
                found = true;
                tmp->_iAmount = soluong;
                HangHoa::saveToFIle();
                cout << "Cap nhat so luong thanh cong" << endl;
                break;
            }
            tmp = tmp->_pNext;
        }
        if (!found) {
            cout << "Ma hang hoa khong co trong danh sach hang hoa" << endl;
        }
    }
}
