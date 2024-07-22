#include <iostream>
#include <stack>
#include <string>

using namespace std;

void push(stack<string>& books) {
    string book;
    cout << "Masukkan judul buku yang akan ditambahkan: ";
    cin.ignore();  // Membersihkan buffer input
    getline(cin, book);
    books.push(book);
    cout << "Buku \"" << book << "\" telah ditambahkan ke tumpukan." << endl;
}

void pop(stack<string>& books) {
    if (books.empty()) {
        cout << "Tumpukan buku kosong. Tidak ada buku yang bisa dihapus." << endl;
    } else {
        cout << "Buku \"" << books.top() << "\" telah dihapus dari tumpukan." << endl;
        books.pop();
    }
}

void peek(const stack<string>& books) {
    if (books.empty()) {
        cout << "Tumpukan buku kosong." << endl;
    } else {
        cout << "Buku teratas di tumpukan: \"" << books.top() << "\"" << endl;
    }
}

void isEmpty(const stack<string>& books) {
    if (books.empty()) {
        cout << "Tumpukan buku kosong." << endl;
    } else {
        cout << "Tumpukan buku tidak kosong." << endl;
    }
}

void size(const stack<string>& books) {
    cout << "Jumlah buku di tumpukan: " << books.size() << endl;
}

int main() {
    stack<string> books;
    string command;
    
    while (true) {
        cout << "\nMasukkan operasi (push, pop, peek, isEmpty, size, exit): ";
        cin >> command;

        if (command == "push") {
            push(books);
        } else if (command == "pop") {
            pop(books);
        } else if (command == "peek") {
            peek(books);
        } else if (command == "isEmpty") {
            isEmpty(books);
        } else if (command == "size") {
            size(books);
        } else if (command == "exit") {
            break;
        } else {
            cout << "Perintah tidak dikenal. Silakan coba lagi." << endl;
        }
    }

    return 0;
}