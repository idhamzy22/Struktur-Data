#include <iostream>
#include <mysql/mysql.h>
#include <sstream>
#include <string>
#include <cctype>

using namespace std;

const char* hostname = "127.0.0.1";
const char* user = "root";
const char* pass = "123";
const char* dbname = "cpp_crud";
unsigned int port = 31235;
const char* unixsocket = NULL;
unsigned long clientflag = 0;

MYSQL* connect_db() {
    MYSQL* conn = mysql_init(0);
    if (conn) {
        conn = mysql_real_connect(conn, hostname, user, pass, dbname, port, unixsocket, clientflag);
        if (conn) {
            cout << "Terhubung ke database dengan sukses." << endl;
        } else {
            cerr << "Koneksi gagal: " << mysql_error(conn) << endl;
        }
    } else {
        cerr << "mysql_init gagal" << endl;
    }
    return conn;
}

bool is_valid_year(const string& year) {
    if (year.length() != 4) {
        return false;
    }
    for (char c : year) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

bool is_valid_pages(const string& pages) {
    for (char c : pages) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

void create_book(const string& title, const string& author, const string& publisher, const string& year, const string& genre, int pages) {
    if (!is_valid_year(year)) {
        cerr << "Year harus terdiri dari 4 digit angka." << endl;
        return;
    }

    MYSQL* conn = connect_db();
    if (conn) {
        string query = "INSERT INTO idham (title, author, publisher, year, genre, pages) VALUES ('" + title + "', '" + author + "', '" + publisher + "', '" + year + "', '" + genre + "', " + to_string(pages) + ")";
        if (mysql_query(conn, query.c_str())) {
            cerr << "INSERT gagal: " << mysql_error(conn) << endl;
        } else {
            cout << "Buku berhasil ditambahkan." << endl;
        }
        mysql_close(conn);
    }
}

void get_idham() {
    MYSQL* conn = connect_db();
    if (conn) {
        if (mysql_query(conn, "SELECT * FROM idham")) {
            cerr << "SELECT gagal: " << mysql_error(conn) << endl;
            mysql_close(conn);
            return;
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (res == nullptr) {
            cerr << "mysql_store_result gagal: " << mysql_error(conn) << endl;
            mysql_close(conn);
            return;
        }

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            cout << "ID: " << row[0] << ", Judul: " << row[1] << ", Pengarang: " << row[2] << ", Penerbit: " << row[3] << ", Tahun: " << row[4] << ", Genre: " << row[5] << ", Halaman: " << row[6] << endl;
        }

        mysql_free_result(res);
        mysql_close(conn);
    }
}

void update_book(int book_id, const string& title, const string& author, const string& publisher, const string& year, const string& genre, int pages) {
    if (!is_valid_year(year)) {
        cerr << "Year harus terdiri dari 4 digit angka." << endl;
        return;
    }

    MYSQL* conn = connect_db();
    if (conn) {
        stringstream query;
        query << "UPDATE idham SET title = '" << title << "', author = '" << author << "', publisher = '" << publisher << "', year = '" << year << "', genre = '" << genre << "', pages = " << pages << " WHERE id = " << book_id;
        if (mysql_query(conn, query.str().c_str())) {
            cerr << "UPDATE gagal: " << mysql_error(conn) << endl;
        } else {
            cout << "Buku berhasil diperbarui." << endl;
        }
        mysql_close(conn);
    }
}

void delete_book(int book_id) {
    MYSQL* conn = connect_db();
    if (conn) {
        stringstream query;
        query << "DELETE FROM idham WHERE id = " << book_id;
        if (mysql_query(conn, query.str().c_str())) {
            cerr << "DELETE gagal: " << mysql_error(conn) << endl;
        } else {
            cout << "Buku berhasil dihapus." << endl;
        }
        mysql_close(conn);
    }
}

void admin_menu() {
    int choice;
    while (true) {
        cout << "\nMenu Admin:\n";
        cout << "1. Tambah Buku\n";
        cout << "2. Tampilkan Semua Buku\n";
        cout << "3. Perbarui Buku\n";
        cout << "4. Hapus Buku\n";
        cout << "5. Keluar\n";
        cout << "Masukkan pilihan: ";
        cin >> choice;

        if (choice == 1) {
            string title, author, publisher, year, genre, pages;
            cout << "Masukkan judul: ";
            cin.ignore();
            getline(cin, title);
            cout << "Masukkan pengarang: ";
            getline(cin, author);
            cout << "Masukkan penerbit: ";
            getline(cin, publisher);
            cout << "Masukkan tahun: ";
            getline(cin, year);
            cout << "Masukkan genre: ";
            getline(cin, genre);
            cout << "Masukkan jumlah halaman: ";
            getline(cin, pages);
            if (!is_valid_pages(pages)) {
                cerr << "Jumlah halaman harus berupa angka." << endl;
            } else {
                create_book(title, author, publisher, year, genre, stoi(pages));
            }
        } else if (choice == 2) {
            get_idham();
        } else if (choice == 3) {
            int book_id;
            string title, author, publisher, year, genre, pages;
            cout << "Masukkan ID buku yang akan diperbarui: ";
            cin >> book_id;
            cin.ignore();
            cout << "Masukkan judul baru: ";
            getline(cin, title);
            cout << "Masukkan pengarang baru: ";
            getline(cin, author);
            cout << "Masukkan penerbit baru: ";
            getline(cin, publisher);
            cout << "Masukkan tahun baru: ";
            getline(cin, year);
            cout << "Masukkan genre baru: ";
            getline(cin, genre);
            cout << "Masukkan jumlah halaman baru: ";
            getline(cin, pages);
            if (!is_valid_pages(pages)) {
                cerr << "Jumlah halaman harus berupa angka." << endl;
            } else {
                update_book(book_id, title, author, publisher, year, genre, stoi(pages));
            }
        } else if (choice == 4) {
            int book_id;
            cout << "Masukkan ID buku yang akan dihapus: ";
            cin >> book_id;
            delete_book(book_id);
        } else if (choice == 5) {
            break;
        } else {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
}

void user_menu() {
    int choice;
    while (true) {
        cout << "\nMenu User:\n";
        cout << "1. Tampilkan Semua Buku\n";
        cout << "2. Keluar\n";
        cout << "Masukkan pilihan: ";
        cin >> choice;

        if (choice == 1) {
            get_idham();
        } else if (choice == 2) {
            break;
        } else {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
}

int main() {
    int role;
    cout << "Masukkan peran Anda (1 untuk Admin, 2 untuk User): ";
    cin >> role;

    if (role == 1) {
        admin_menu();
    } else if (role == 2) {
        user_menu();
    } else {
        cout << "Peran tidak valid. Program akan keluar." << endl;
    }

    return 0;
}
