#include "DonHang.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <string>
// Khởi tạo biến tĩnh orderNumber
int Order::orderNumber = 1;

// Constructor
DonHang::DonHang()
{
    head = nullptr;
    orderCount = 0;
}

// Destructor
DonHang::~DonHang()
{
    Order *current = head;
    while (current != nullptr)
    {
        Order *next = current->next;
        delete current;
        current = next;
    }
}
bool DonHang::KiemTraHangHoa(std::string productCodes)
{
    std::ifstream inFile("DanhSachHangHoa.txt");
    if (!inFile)
    {
        std::cerr << "Không thể mở file DanhSachHangHoa.txt để đọc!" << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(inFile, line))
    {
        std::istringstream iss(line);
        std::string code, ordernumber;
        if (iss >> ordernumber >> code)
        {
            if (code == productCodes)
            {
                return true; // Sản phẩm có sẵn
            }
        }
    }
    return false; // Sản phẩm không có sẵn
}
// Hàm đặt hàng
void DonHang::DatHang(std::string productCodes, int quantity, std::string Color, std::string Country, const std::string &customerName, const std::string &customerAddress, const std::string &phoneNumber, const std::string &orderDate)
{
    // Kiểm tra xem có đơn hàng nào có thông tin giống nhau hay không
        // Tạo đơn hàng mới
        if (!KiemTraHangHoa(productCodes))
        {
            std::cerr << "Hết hàng!" << std::endl;
            return;
        }
        Order *newOrder = new Order;
        newOrder->productCodes = productCodes;
        newOrder->quantity = quantity;
        newOrder->Color = Color;
        newOrder->Country = Country;
        newOrder->customerName = customerName;
        newOrder->customerAddress = customerAddress;
        newOrder->phoneNumber = phoneNumber;
        newOrder->orderDate = orderDate;
        newOrder->next = nullptr;

        // Định dạng orderNumber và lưu vào orderNumberStr
        snprintf(newOrder->orderNumberStr, sizeof(newOrder->orderNumberStr), "%04d", Order::orderNumber++);
        newOrder->orderNumber = Order::orderNumber;

        // Thêm đơn hàng mới vào danh sách liên kết
        if (head == nullptr)
        {
            head = newOrder;
        }
        else
        {
            Order *temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newOrder;
        }
        orderCount++;
        std::cout << "Don Hang Dang Cho Xu Ly.\n";
}

// Hàm lưu đơn hàng vào file
void DonHang::LuuDonHang() {
    std::ofstream outFile("DonHang.txt" , std::ios::app);
    if (!outFile) {
        std::cerr << "Không thể mở file để ghi!" << std::endl;
        return;
    }
    
    Order* current = head;
    while (current != nullptr) {
        outFile << current->orderNumberStr;
        outFile << " " << current->productCodes;
        outFile << " " << current->quantity;
        outFile << " " << current->Color;
        outFile << " " << current->Country;
        outFile << " " << current->customerName;
        outFile << " " << current->customerAddress;
        outFile << " " << current->phoneNumber;
        outFile << " " << current->orderDate << "\n";
        current = current->next;
    }

    outFile.close();

}

// Hàm nhập thông tin đơn hàng từ người dùng
void DonHang::NhapThongTinDonHang()
{
    std::string productCodes;
    int quantity;
    std::string Color;
    std::string Country;
    std::string customerName;
    std::string customerAddress;
    std::string phoneNumber;
    std::string orderDate;

    std::cout << "Nhap ma san pham: ";
    std::cin >> productCodes;
    std::cout << "Nhap so luong: ";
    std::cin >> quantity;
    std::cout << "Nhap mau sac: ";
    std::cin >> Color;
    std::cout << "Nhap quoc gia: ";
    std::cin >> Country;
    std::cin.ignore(); // Bỏ qua ký tự newline còn lại trong bộ đệm
    std::cout << "Nhap ten khach hang: ";
    std::getline(std::cin, customerName);
    std::cout << "Nhap dia chi khach hang: ";
    std::getline(std::cin, customerAddress);
    std::cout << "Nhap so dien thoai khach hang: ";
    std::getline(std::cin, phoneNumber);
    std::cout << "Nhap ngay dat hang: ";
    std::getline(std::cin, orderDate);

    DatHang(productCodes, quantity, Color, Country, customerName, customerAddress, phoneNumber, orderDate);
}
void DonHang::CapNhatSoLuongHangHoa(std::string productCodes, int quantityChange)
{
    std::ifstream inFile("DanhSachHangHoa.txt");
    if (!inFile)
    {
        std::cerr << "Khong the mo file DanhSachHangHoa.txt de doc!" << std::endl;
        return;
    }

    std::ofstream tempFile("TempDanhSachHangHoa.txt");
    if (!tempFile)
    {
        std::cerr << "Khong the mo file TempDanhSachHangHoa.txt de ghi!" << std::endl;
        return;
    }

    std::string orderNumber, code, country, color, date;
    int quantity;
    double totalamount;

    while (inFile >> orderNumber >> code >> country >> color >> totalamount >> date >> quantity)
    {
        if (code == productCodes)
        {
            quantity += quantityChange;
        }
        if (quantity) tempFile << orderNumber << " " << code << " " << country << " " << color << " " << totalamount << " " << date << " " << quantity << "\n";
    }

    inFile.close();
    tempFile.close();

    // Xoa thong tin trong file "DanhSachHangHoa.txt"
    std::ofstream danhSachHangHoaFile("DanhSachHangHoa.txt", std::ios::trunc);

    // Copy du lieu tu "TempDanhSachHangHoa.txt" vao "DanhSachHangHoa.txt"
    std::ifstream tempFileRead("TempDanhSachHangHoa.txt");
    std::string line;
    while (std::getline(tempFileRead, line))
    {
        danhSachHangHoaFile << line << "\n";
    }

    tempFileRead.close();
    danhSachHangHoaFile.close();

    // Xoa du lieu trong "TempDanhSachHangHoa.txt"
    std::ofstream tempFileClear("TempDanhSachHangHoa.txt", std::ios::trunc);
}

void DonHang::XuLyDonHang()
{
    std::ifstream inFile("DonHang.txt");
    std::string line;
    Order *newOrder = new Order();
    while (std::getline(inFile, line))
    {
        std::istringstream iss(line);
        int orderNumber;
        std::string productCodes;
        int quantity;
        std::string Color;
        std::string Country;
        std::string customerName;
        std::string customerAddress;
        std::string phoneNumber;
        std::string orderDate;
        if (iss >> orderNumber >> productCodes >> quantity >> Color >> Country >> customerName >> customerAddress >> phoneNumber >> orderDate)
        {
            Order *newOrder = new Order();
            newOrder->orderNumber = orderNumber;
            newOrder->productCodes = productCodes;
            newOrder->quantity = quantity;
            newOrder->Color = Color;
            newOrder->Country = Country;
            newOrder->customerName = customerName;
            newOrder->customerAddress = customerAddress;
            newOrder->phoneNumber = phoneNumber;
            newOrder->orderDate = orderDate;
            snprintf(newOrder->orderNumberStr, sizeof(newOrder->orderNumberStr), "%04d", Order::orderNumber++);
            newOrder->orderNumber = Order::orderNumber;

            // Them don hang moi vao danh sach lien ket
            if (head == nullptr)
            {
                head = newOrder;
            }
            else
            {
                Order *current = head;
                while (current->next != nullptr)
                {
                    current = current->next;
                }
                current->next = newOrder;
            }
        }
    }
    inFile.close();

    Order *current = head;
    Order *previous = nullptr;

    while (current != nullptr)
    {
        // Xu ly don hang o day
        // Vi du: Hien thi thong tin don hang
        std::cout << "Xu ly don hang: " << current->orderNumberStr << std::endl;

        // Cap nhat so luong hang hoa trong file DanhSachHangHoa.txt
        CapNhatSoLuongHangHoa(current->productCodes, -current->quantity);

        // Doc don hang tiep theo
        previous = current;
        current = current->next;

        // Xoa don hang da xu ly khoi danh sach
        delete previous;
    }

    // Doi ten file tam thanh ten file goc
    std::rename("TempDanhSachHangHoa.txt", "DanhSachHangHoa.txt");
    std::ofstream tempFileClear("DonHang.txt", std::ios::trunc);
}
