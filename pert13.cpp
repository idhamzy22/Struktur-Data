#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <windows.h>
#include <conio.h>

using namespace std;

struct Product {
    string kode;
    string nama;
    string kategori;
    string harga;
};

vector<Product> products;

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void animateText(const string& text, int delay = 100) {
    for (char c : text) {
        cout << c << flush;
        Sleep(delay);
    }
}

void animateClosing() {
    clearScreen();
    cout << "\033[1;32m";
    animateText("===========================================\n", 50);
    animateText("               PROGRAM BERAKHIR         \n", 50);
    animateText("===========================================\n", 50);
    animateText("\033[0m");
    animateText("\033[1;32mTerimakasih telah menggunakan program ini!\n\033[0m", 50);
    animateText("\033[1;32mMOHON MAAF JIKA ADA KESALAHAN TOLONG DI MAKLUMI KAMI PERINTIS BUKAN PEWARIS!\n\033[0m", 50);
    Sleep(1000);
}

void printHeader() {
    cout << "\033[1;34m"
         << "===========================================\n"
         << "            DATA PRIBADI NEGARA       \n"
         << "===========================================\n"
         << "\033[0m";
}

string getPassword() {
    string password;
    cout << "\033[1;33m" << "Login Password: " << "\033[0m";
    
    // hide input password
    char ch;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (!password.empty()) {
                cout << "\b \b"; // menghapus karakter dengan mundur
                password.pop_back(); // hapus karakter terakhir dari string kata sandi
            }
        } else {
            cout << ' ';
            password += ch;
        }
    }
    cout << endl;
    
    return password;
}

bool login() {
    clearScreen();
    printHeader();
    string inputID, inputPassword;
    const string correctID = "ADMIN";
    const string correctPassword = "ADMIN";

    cout << "\033[1;33m" << "Login ID: " << "\033[0m";
    cin >> inputID;
    inputPassword = getPassword();

    return inputID == correctID && inputPassword == correctPassword;
}

void createData() {
    Product p;
    clearScreen();
    printHeader();
    animateText("\033[1;32mMenambahkan Data Produk\n\033[0m", 50);
    cout << "Masukkan kode produk: ";
    cin.ignore();
    getline(cin, p.kode);
    cout << "Masukkan nama produk: ";
    getline(cin, p.nama);
    cout << "Masukkan harga: ";
    getline(cin, p.harga);
    cout << "Masukkan kategori: ";
    getline(cin, p.kategori);
    products.push_back(p);
    animateText("\033[1;32m\nData berhasil ditambahkan!\n\033[0m", 50);
}

void readData() {
    clearScreen();
    printHeader();
    animateText("\033[1;36mData Produk\n\033[0m", 50);
    cout << left << setw(15) << "Kode Produk" << setw(30) << "Nama Produk" << setw(15) << "Harga" << setw(20) << "Kategori" << endl;
    cout << "=============================================================================================" << endl;
    for (const auto& p : products) {
        cout << left << setw(15) << p.kode << setw(30) << p.nama << setw(15) << p.harga << setw(20) << p.kategori << endl;
    }
}

void updateData() {
    string kode;
    clearScreen();
    printHeader();
    animateText("\033[1;35mMengubah Data Produk\n\033[0m", 50);
    cout << "Masukkan kode produk yang akan diubah: ";
    cin.ignore();
    getline(cin, kode);
    
    for (auto& p : products) {
        if (p.kode == kode) {
            cout << left << setw(15) << "Kode Produk" << setw(30) << "Nama Produk" << setw(15) << "Harga" << setw(20) << "Kategori" << endl;
            cout << "=============================================================================================" << endl;
            cout << left << setw(15) << p.kode << setw(30) << p.nama << setw(15) << p.harga << setw(20) << p.kategori << endl;
            char confirm;
            cout << "\nApakah anda ingin mengubah data? (y/n): ";
            cin >> confirm;
            if (confirm == 'y') {
                cout << "1. Ubah kode produk: ";
                cin.ignore();
                getline(cin, p.kode);
                cout << "2. Ubah nama produk: ";
                getline(cin, p.nama);
                cout << "3. Ubah harga: ";
                getline(cin, p.harga);
                cout << "4. Ubah kategori: ";
                getline(cin, p.kategori);
                animateText("\033[1;32m\nData berhasil diubah!\n\033[0m", 50);
            } else {
                animateText("\033[1;31m\nData tidak jadi diubah.\n\033[0m", 50);
            }
            return;
        }
    }
    animateText("\033[1;31mKode produk tidak ditemukan.\n\033[0m", 50);
}

void deleteData() {
    string kode;
    clearScreen();
    printHeader();
    animateText("\033[1;31mMenghapus Data Produk\n\033[0m", 50);
    cout << "Masukkan kode produk yang akan dihapus: ";
    cin.ignore();
    getline(cin, kode);

    for (auto it = products.begin(); it != products.end(); ++it) {
        if (it->kode == kode) {
            cout << left << setw(15) << "Kode Produk" << setw(30) << "Nama Produk" << setw(15) << "Harga" << setw(20) << "Kategori" << endl;
            cout << "=============================================================================================" << endl;
            cout << left << setw(15) << it->kode << setw(30) << it->nama << setw(15) << it->harga << setw(20) << it->kategori << endl;
            char confirm;
            cout << "\nApakah anda ingin menghapus data? (y/n): ";
            cin >> confirm;
            if (confirm == 'y') {
                products.erase(it);
                animateText("\033[1;32m\nData berhasil dihapus!\n\033[0m", 50);
            } else {
                animateText("\033[1;31m\nData tidak jadi dihapus.\n\033[0m", 50);
            }
            return;
        }
    }
    animateText("\033[1;31mKode produk tidak ditemukan.\n\033[0m", 50);
}

int main() {
    clearScreen();
    int loginAttempts = 0; // penghitung untuk melacak jumlah percobaan login yang dilakukan oleh user
    const int maxAttempts = 3; // menetapkan nilai konstan untuk jumlah max percobaan login yang diperbolehkan hanya 3 kali login
    
    while (loginAttempts < maxAttempts) { // berjalan selama jumlah percobaan login kurang dari jumlah max yang diperbolehkan

        // memeriksa apakah fungsi login() mengembalikan true, yang menunjukkan login berhasil. Jika login berhasil, loop berhenti, dan program akan berlanjut
        if (login()) {
            break;

        // jika percobaan login gagal, penghitung percobaan login ditingkatkan.
        } else {
            loginAttempts++;

            // jika jumlah percobaan masih kurang dari jumlah maksimum yang diperbolehkan, pesan kesalahan ditampilkan.
            if (loginAttempts < maxAttempts) {

                // Panggilan fungsi ini menampilkan pesan kesalahan animasi dengan teks merah yang menunjukkan bahwa login gagal dan meminta pengguna untuk mencoba lagi
                animateText("\033[1;31mLogin gagal! Coba lagi.\n\033[0m", 50);
            }
        }
    }
    
    if (loginAttempts == maxAttempts) {
        animateText("\033[1;31mAnda telah mencoba login 3 kali. Program terblokir.\n\033[0m", 50);
        return 0;
    }

    int choice;
    do {
        clearScreen();
        printHeader();
        cout << "\n\033[1;34m"
             << "Menu Program:\n"
             << "1. Tambah data\n"
             << "2. Tampilkan data\n"
             << "3. Ubah data\n"
             << "4. Hapus data\n"
             << "5. Keluar\n"
             << "Pilih menu: "
             << "\033[0m";
        cin >> choice;

        switch (choice) {
            case 1:
                createData();
                break;
            case 2:
                readData();
                break;
            case 3:
                updateData();
                break;
            case 4:
                deleteData();
                break;
            case 5:
                animateClosing();
                break;
            default:
                animateText("\033[1;31mPilihan tidak valid. Silahkan coba lagi.\n\033[0m", 50);
        }
        if (choice != 5) {
            cout << "\nKlik Enter untuk melanjutkan...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    } while (choice != 5);

    return 0;
}
