#include "HangHoa.h"
#include <fstream>
#include <cstdio>
#include <cstring>
#include "Stack.h"
#include <thread> 
#include <chrono>
void HangHoa::saveToFIle(){
    std::ofstream file("DanhSachHangHoa.txt",std::ios::out);
    if(file.is_open()){
        HangHoa* dummy = head;
        while(dummy != NULL){
            //ma, ten, noi sx, mau sac, gia ban, ngay nhap, so luong
            file<<dummy->ma<<", "<<dummy->name<<", "<<dummy->origin<<", "<<dummy->color<<", "<<dummy->price<<", "<<dummy->entryDate<<", "<<dummy->amount<<endl;
            dummy = dummy->next;
        }
        file.close();
    }else {
        std::cerr << "Failed to open file";
    }
}

int HangHoa::counter = 1;
HangHoa* HangHoa::head = NULL;
Stack<string> HangHoa::deletedIDs;
void HangHoa::taoHangHoa(string name, string origin, string color, int price, string entryDate, int amount){
    HangHoa* newNode = new HangHoa();
    newNode->name = name;
    newNode->origin = origin;
    newNode->color = color;
    newNode->price = price;
    newNode->entryDate = entryDate;
    newNode->amount = amount;
    newNode->next = NULL;       
    if(head == NULL){
        head = newNode;
        if(!deletedIDs.isEmpty()){
            string id = deletedIDs.pop();
            strncpy_s(newNode->ma, id.c_str(), sizeof(newNode->ma) - 1);
            newNode->ma[sizeof(newNode->ma) - 1] = '\0';
        }else{
            snprintf(newNode->ma, sizeof(newNode->ma), "%04d", counter++);
        }
    }else{
        HangHoa* tmp = head;
        bool flag = false;
        while(tmp != NULL){
            if(newNode->name == tmp->name && newNode->origin == tmp->origin && newNode->color == tmp->color && newNode->entryDate == tmp->entryDate){
                tmp->amount += newNode->amount;
                delete newNode;
                flag = true;
                break;
            }
            if(tmp->next == NULL){
                break;
            }
            tmp = tmp->next;
        }
            if(!flag){
                tmp->next = newNode;
                if(!deletedIDs.isEmpty()){
                    string id = deletedIDs.pop();
                    strncpy_s(newNode->ma, id.c_str(), sizeof(newNode->ma) - 1);
                    newNode->ma[sizeof(newNode->ma) - 1] = '\0';
                }else{
                    snprintf(newNode->ma, sizeof(newNode->ma), "%04d", counter++);
                }
            }
    }
    HangHoa::saveToFIle();
}    

void HangHoa::xoaHangHoa(string ma){
    HangHoa *tmp = head;
    HangHoa* prev = NULL;
    bool found = false;
    while(tmp != NULL){
        if(ma == tmp->ma){
            found = true;
            if(prev == NULL){
                head = tmp->next;
            }else{
                prev->next = tmp->next;
            }
            break;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    if(found){
       deletedIDs.push(tmp->ma);
       delete tmp;
       HangHoa::saveToFIle();
       cout << "Xoa Hang Hoa Thanh Cong";
    }
    else
    {
        cout<<"Khong Tim Thay Hang Hoa";
    }
}

void HangHoa::timkiemhoanghoa() {
    ifstream input("TiemKiemHangHoa.txt");
    ofstream output("TiemKiemHangHoa.txt");
    string tentimkiem;
    input >> tentimkiem;
    bool timthay = false;
    for (HangHoa* hangcantim = head; hangcantim != NULL; hangcantim = hangcantim->next) {
        if (hangcantim->name==tentimkiem) {
            output << hangcantim->ma << ", " << hangcantim->name << ", " << hangcantim->origin
                << ", " << hangcantim->color << ", " << hangcantim->price << ", " << hangcantim->entryDate << ", " << hangcantim->amount << endl;
            timthay = true;
        }
    }
    if (!timthay) {
        output << "Không tìm thấy hàng hóa." << endl;
    }
    input.close();
    output.close();
}

