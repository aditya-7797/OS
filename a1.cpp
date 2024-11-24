#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Define a structure to hold an address record
struct Record {
    string name;
    string phone;
    string email;
};

// Function prototypes
void createAddressBook(vector<Record> &addressBook);
void viewAddressBook(const vector<Record> &addressBook);
void insertRecord(vector<Record> &addressBook);
void deleteRecord(vector<Record> &addressBook);
void modifyRecord(vector<Record> &addressBook);

int main() {
    vector<Record> addressBook;
    int choice;

    do {
        cout << "\nAddress Book Menu\n";
        cout << "1. Create Address Book\n";
        cout << "2. View Address Book\n";
        cout << "3. Insert a Record\n";
        cout << "4. Delete a Record\n";
        cout << "5. Modify a Record\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: createAddressBook(addressBook); break;
            case 2: viewAddressBook(addressBook); break;
            case 3: insertRecord(addressBook); break;
            case 4: deleteRecord(addressBook); break;
            case 5: modifyRecord(addressBook); break;
            case 6: cout << "Exiting program.\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}

void createAddressBook(vector<Record> &addressBook) {
    addressBook.clear();
    cout << "Address book created successfully.\n";
}

void viewAddressBook(const vector<Record> &addressBook) {
    if (addressBook.empty()) {
        cout << "Address book is empty.\n";
        return;
    }

    cout << "\nAddress Book Records:\n";
    for (size_t i = 0; i < addressBook.size(); ++i) {
        cout << i + 1 << ". Name: " << addressBook[i].name
             << ", Phone: " << addressBook[i].phone
             << ", Email: " << addressBook[i].email << endl;
    }
}

void insertRecord(vector<Record> &addressBook) {
    Record newRecord;
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, newRecord.name);
    cout << "Enter phone: ";
    cin >> newRecord.phone;
    cout << "Enter email: ";
    cin >> newRecord.email;

    addressBook.push_back(newRecord);
    cout << "Record added successfully.\n";
}

void deleteRecord(vector<Record> &addressBook) {
    if (addressBook.empty()) {
        cout << "Address book is empty.\n";
        return;
    }

    int index;
    cout << "Enter the record number to delete: ";
    cin >> index;

    if (index < 1 || index > (int)addressBook.size()) {
        cout << "Invalid record number.\n";
    } else {
        addressBook.erase(addressBook.begin() + index - 1);
        cout << "Record deleted successfully.\n";
    }
}

void modifyRecord(vector<Record> &addressBook) {
    if (addressBook.empty()) {
        cout << "Address book is empty.\n";
        return;
    }

    int index;
    cout << "Enter the record number to modify: ";
    cin >> index;

    if (index < 1 || index > (int)addressBook.size()) {
        cout << "Invalid record number.\n";
    } else {
        Record &record = addressBook[index - 1];
        cout << "Enter new name (current: " << record.name << "): ";
        cin.ignore();
        getline(cin, record.name);
        cout << "Enter new phone (current: " << record.phone << "): ";
        cin >> record.phone;
        cout << "Enter new email (current: " << record.email << "): ";
        cin >> record.email;
        cout << "Record modified successfully.\n";
    }
}
