#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Record {
    int id;
    string name;
    int age;
};

void insertRecord(fstream &file, int pos, Record record) {
    file.seekp(pos * sizeof(Record), ios::beg);
    file.write(reinterpret_cast<char*>(&record), sizeof(Record));
    cout << "Record inserted successfully at position " << pos << endl;
}

void deleteRecord(fstream &file, int pos) {
    Record blankRecord = {0, "", 0};
    file.seekp(pos * sizeof(Record), ios::beg);
    file.write(reinterpret_cast<char*>(&blankRecord), sizeof(Record));
    cout << "Record deleted successfully from position " << pos << endl;
}

void displayFileContents(fstream &file) {
    file.seekg(0, ios::beg);
    Record record;
    int position = 0;
    while (file.read(reinterpret_cast<char*>(&record), sizeof(Record))) {
        if (record.id != 0) {
            cout << "Position " << position << ": ID = " << record.id
                 << ", Name = " << record.name << ", Age = " << record.age << endl;
        }
        position++;
    }
}

int main() {
    fstream file("records.dat", ios::in | ios::out | ios::binary | ios::trunc);

    if (!file) {
        cout << "File could not be created!" << endl;
        return 1;
    }

    Record r1 = {1, "Rutja", 25};
    Record r2 = {2, "Saisha", 30};
    Record r3 = {3, "Shrinidhi", 22};

    insertRecord(file, 0, r1);
    insertRecord(file, 1, r2);
    insertRecord(file, 2, r3);

    cout << "\nFile contents after insertion:" << endl;
    displayFileContents(file);

    deleteRecord(file, 1);

    cout << "\nFile contents after deletion:" << endl;
    displayFileContents(file);

    file.close();
    return 0;
}
