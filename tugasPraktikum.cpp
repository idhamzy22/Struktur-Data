#include <iostream>

using namespace std;

// Struktur Node
struct Node {
    int data;
    Node* next;
};

// Kelas Linked list
class LinkedList {
private:
    Node* head;

public:
    // Constructor
    LinkedList() {
        head = nullptr;
    }

    // Destructor
    ~LinkedList() {
        clear();
    }

    // Hapus linked list
    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }

    // Sisipkan Node di awal
    void insertDepan(int value) {
        Node* newNode = new Node{value, head};
        head = newNode;
    }

    // Sisipkan Node di tengah setelah Node tertentu
    void insertTengah(int value, int afterValue) {
        Node* current = head;
        while (current != nullptr && current->data != afterValue) {
            current = current->next;
        }
        if (current != nullptr) {
            Node* newNode = new Node{value, current->next};
            current->next = newNode;
        } else {
            cout << "Node dengan nilai " << afterValue << " not found" << endl;
        }
    }

    // Masukkan Node di akhir
    void insertBelakang(int value) {
        Node* newNode = new Node{value, nullptr};
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    // Hapus Node dari awal
    void deleteDepan() {
        if (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        } else {
            cout << "LIST KOSONG" << endl;
        }
    }

    // Hapus Node dari tengah
    void deleteTengah(int value) {
        if (head == nullptr) {
            cout << "LIST KOSONG" << endl;
            return;
        }

        if (head->data == value) {
            deleteDepan();
            return;
        }

        Node* current = head;
        while (current->next != nullptr && current->next->data != value) {
            current = current->next;
        }

        if (current->next != nullptr) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        } else {
            cout << "Node dengan nilai " << value << " not found" << endl;
        }
    }

    // Hapus Node dari akhir
    void deleteBelakang() {
        if (head == nullptr) {
            cout << "LIST KOSONG" << endl;
            return;
        }

        if (head->next == nullptr) {
            delete head;
            head = nullptr;
            return;
        }

        Node* current = head;
        while (current->next->next != nullptr) {
            current = current->next;
        }

        delete current->next;
        current->next = nullptr;
    }

    // Tampilkan linked list
    void tampilan() const {
        Node* current = head;
        if (current == nullptr) {
            cout << "LIST KOSONG" << endl;
        } else {
            while (current != nullptr) {
                cout << current->data << " ";
                current = current->next;
            }
            cout << endl;
        }
    }
};

int main() {
    LinkedList list;
    char choice;
    int value, afterValue;

    do {
        cout << "Menu:" << endl;
        cout << "a. Insert depan" << endl;
        cout << "b. Insert tengah" << endl;
        cout << "c. Insert belakang" << endl;
        cout << "d. Delete depan" << endl;
        cout << "e. Delete tengah" << endl;
        cout << "f. Delete belakang" << endl;
        cout << "g. Tampilkan data" << endl;
        cout << "h. Keluar" << endl;
        cout << "Pilih: ";
        cin >> choice;

        switch (choice) {
            case 'a':
                cout << "Masukkan nilai: ";
                cin >> value;
                list.insertDepan(value);
                cout << "\n";
                break;
            case 'b':
                cout << "Masukkan nilai: ";
                cin >> value;
                cout << "Setelah nilai: ";
                cin >> afterValue;
                list.insertTengah(value, afterValue);
                cout << "\n";
                break;
            case 'c':
                cout << "Masukkan nilai: ";
                cin >> value;
                list.insertBelakang(value);
                cout << "\n";
                break;
            case 'd':
                list.deleteDepan();
                break;
            case 'e':
                cout << "Masukkan nilai yang ingin dihapus: ";
                cin >> value;
                list.deleteTengah(value);
                cout << "\n";
                break;
            case 'f':
                list.deleteBelakang();
                break;
            case 'g':
                cout << "Data linked list: ";
                list.tampilan();
                cout << "\n";
                break;
            case 'h':
                cout << "TERIMA KASIH SUDAH MENCOBA PROGRAM BY IDHAM!!!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    } while (choice != 'h');

    return 0;
}vscode-remote://wsl%2Bubuntu/root/perkuliahan/bhs_pemrograman/struktur-data/tugas%20Graph