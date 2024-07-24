<div align="center">
    <h1 class="animated-header">
        <img src="https://readme-typing-svg.herokuapp.com?font=Fira+Code&size=40&duration=4000&pause=1000&color=33FF33&center=true&vCenter=true&width=1000&lines=Hai...+with+me+Idham+Kholid+Nur+Azizi;NIM+20230801192;Welcome+to+my+GitHub+idhamzy22+profile;Explore+my+projects+UAS+struktur+data;Came+on!!" alt="Typing SVG"/>
    </h1>
</div>


# Book Management System

Ini adalah aplikasi CRUD (Create, Read, Update, Delete) sederhana untuk manajemen buku menggunakan C++ dan MySQL.

## Prasyarat

Pastikan Anda telah menginstal:
- MySQL Server
- MySQL Connector C++
- Compiler C++ (misalnya g++)

## Konfigurasi Database di Navicat

1. Buat database `cpp_crud` di MySQL:
    ```sql
    CREATE DATABASE cpp_crud;
    ```

2. Buat tabel `idham` di dalam database `cpp_crud`:
    ```sql
    USE cpp_crud;

    CREATE TABLE idham (
        id INT AUTO_INCREMENT PRIMARY KEY,
        title VARCHAR(255),
        author VARCHAR(255),
        publisher VARCHAR(255),
        year CHAR(4),
        genre VARCHAR(255),
        pages INT
    );
    ```

3. Konfigurasi koneksi database dalam kode:
    ```cpp
    const char* hostname = "127.0.0.1";
    const char* user = "root";
    const char* pass = "123";
    const char* dbname = "cpp_crud";
    unsigned int port = 31235;
    const char* unixsocket = NULL;
    unsigned long clientflag = 0;
    ```

## Kompilasi dan Menjalankan Program

1. Buat file `crud.cc` dan masukkan kode berikut:

    ```cpp
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
    ```

2. Instal `libmysqlclient-dev`:
    ```sh
    apt-get install libmysqlclient-dev   
    ```    

2. Kompilasi program:
    ```sh
    g++ -o crud_simple crud.cc -lmysqlclient
    ```

3. Jalankan program:
    ```sh
    ./crud_simple
    ```

## Struktur Program

### Fungsi dan Deskripsi

1. **Header Files dan Namespace**
    ```cpp
    #include <iostream>
    #include <mysql/mysql.h>
    #include <sstream>
    #include <string>
    #include <cctype>
    using namespace std;
    ```

    - `#include <iostream>`: Menyertakan library untuk input dan output.
    - `#include <mysql/mysql.h>`: Menyertakan library MySQL untuk koneksi dan operasi database.
    - `#include <sstream>`: Menyertakan library untuk manipulasi string dengan stringstream.
    - `#include <string>`: Menyertakan library untuk manipulasi string.
    - `#include <cctype>`: Menyertakan library untuk fungsi karakter (misalnya isdigit).
    - `using namespace std;`: Menghindari penggunaan prefix std:: pada objek-objek standar.

2. **Konstanta dan Koneksi Database**
    ```cpp
    const char* hostname = "127.0.0.1";
    const char* user = "root";
    const char* pass = "123";
    const char* dbname = "cpp_crud";
    unsigned int port = 31235;
    const char* unixsocket = NULL;
    unsigned long clientflag = 0;
    ```
    
    - Menyimpan informasi koneksi ke database MySQL: alamat server (`hostname`), nama pengguna (`user`), password (`pass`), nama database (`dbname`), port, dan konfigurasi lainnya.

3. **Fungsi `connect_db()`**
    ```cpp
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
    ```    

    - `mysql_init(0)`: Inisialisasi objek koneksi MySQL.
    - `mysql_real_connect(...)`: Mencoba untuk terhubung ke database dengan parameter yang diberikan.
    - Mengembalikan pointer ke objek koneksi jika berhasil, atau menampilkan pesan kesalahan jika gagal.

4. **Fungsi Validasi**
    ```cpp
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
    ```

    - `is_valid_year(const string& year)`: Memeriksa apakah string tahun terdiri dari 4 digit angka.
    - `is_valid_pages(const string& pages)`: Memeriksa apakah string jumlah halaman hanya berisi angka.

5. **Fungsi `create_book()`**
    ```cpp
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
    ```

    - Memeriksa validitas tahun sebelum melanjutkan.
    - Menyusun query SQL untuk menambahkan buku baru ke tabel `idham`.
    - Menjalankan query dan menampilkan hasilnya.

6. **Fungsi `get_idham()`**
    ```cpp
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
    ```

    - Mengambil dan menampilkan semua data buku dari tabel `idham`.
    - Menampilkan hasil setiap baris dalam tabel.

7. **Fungsi `update_book()`**
    ```cpp
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
    ```

    - Memperbarui data buku berdasarkan ID buku yang diberikan.
    - Menggunakan `stringstream` untuk menyusun query SQL.

8. **Fungsi `delete_book()`**
    ```cpp
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
    ```

    - Menghapus buku dari tabel `idham` berdasarkan ID buku yang diberikan.

9. **Menu Admin dan User**
    ```cpp
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
    ```

    - `admin_menu()`: Menampilkan menu admin yang memungkinkan admin untuk menambah, menampilkan, memperbarui, atau menghapus buku. Admin dapat memasukkan data buku baru, memperbarui informasi buku, atau menghapus buku berdasarkan ID.
    - `user_menu()`: Menampilkan menu untuk pengguna biasa yang hanya memungkinkan untuk melihat daftar buku.

10. **Fungsi `main()`**
    ```cpp
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
    ```

    - Menanyakan peran pengguna (Admin atau User).
    - Memanggil menu yang sesuai berdasarkan pilihan pengguna.
    - Jika peran tidak valid, program akan menampilkan pesan kesalahan dan keluar.

Program ini menyediakan antarmuka berbasis teks untuk mengelola buku dalam database MySQL, dengan fitur untuk admin menambah, memperbarui, menghapus, dan melihat buku, serta memungkinkan pengguna untuk melihat daftar buku.

## Penggunaan

1. Jalankan program dan pilih peran (Admin atau User).
2. Jika Anda adalah Admin, Anda dapat:
    - Menambah buku baru
    - Melihat semua buku
    - Memperbarui buku
    - Menghapus buku
3. Jika Anda adalah User, Anda hanya dapat melihat semua buku.

## Catatan

Pastikan MySQL server berjalan dan informasi koneksi sesuai dengan konfigurasi yang diberikan di atas.

## Lisensi

Proyek ini dilisensikan di bawah MIT License.
