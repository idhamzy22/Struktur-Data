# Book Management System

Ini adalah aplikasi CRUD (Create, Read, Update, Delete) sederhana untuk manajemen buku menggunakan C++ dan MySQL.

## Prasyarat

Pastikan Anda telah menginstal:
- MySQL Server
- MySQL Connector C++
- Compiler C++ (misalnya g++)

## Konfigurasi Database

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

1. Kompilasi program:
    ```sh
    g++ -o book_management book_management.cpp -lmysqlclient
    ```

2. Jalankan program:
    ```sh
    ./book_management
    ```

## Struktur Program

### Fungsi dan Deskripsi

1. **Header Files dan Namespace**
    - `#include <iostream>`
    - `#include <mysql/mysql.h>`
    - `#include <sstream>`
    - `#include <string>`
    - `#include <cctype>`
    - `using namespace std;`

2. **Konstanta dan Koneksi Database**
    - Mendefinisikan konstanta untuk koneksi database dan konfigurasi koneksi.

3. **Fungsi `connect_db()`**
    - Menginisialisasi dan menghubungkan ke database MySQL.

4. **Fungsi Validasi**
    - `is_valid_year(const string& year)`: Memeriksa validitas tahun.
    - `is_valid_pages(const string& pages)`: Memeriksa validitas jumlah halaman.

5. **Fungsi `create_book()`**
    - Menambahkan buku baru ke database setelah validasi input.

6. **Fungsi `get_idham()`**
    - Mengambil dan menampilkan semua data buku dari tabel `idham`.

7. **Fungsi `update_book()`**
    - Memperbarui data buku berdasarkan ID buku yang diberikan.

8. **Fungsi `delete_book()`**
    - Menghapus buku dari tabel `idham` berdasarkan ID buku yang diberikan.

9. **Menu Admin dan User**
    - `admin_menu()`: Menampilkan menu admin untuk menambah, menampilkan, memperbarui, atau menghapus buku.
    - `user_menu()`: Menampilkan menu user untuk melihat daftar buku.

10. **Fungsi `main()`**
    - Menanyakan peran pengguna (Admin atau User) dan memanggil menu yang sesuai.

### Urutan Bagian dalam Kode

1. Header Files dan Namespace
2. Konstanta dan Koneksi Database
3. Fungsi `connect_db()`
4. Fungsi Validasi (`is_valid_year` dan `is_valid_pages`)
5. Fungsi `create_book()`
6. Fungsi `get_idham()`
7. Fungsi `update_book()`
8. Fungsi `delete_book()`
9. Menu Admin (`admin_menu()`)
10. Menu User (`user_menu()`)
11. Fungsi `main()`

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
