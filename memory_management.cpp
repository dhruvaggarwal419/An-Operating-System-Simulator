#include <bits/stdc++.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#define max_size 10000000 

using namespace std;
namespace py = pybind11;

void firstFitAlgorithm(fstream &, int);
void printNotUsedMemory(fstream &);
void bestFitAlgorithm(fstream &, int);
void worstFitAlgorithm(fstream &, int);
void nextFitAlgorithm(fstream &, int, int &, fstream &);

int main() {
    long long size;
    fstream file1("allocated_variable.txt", ios::in | ios::out);
    int lastIndexAllocated = 0;
    file1 >> lastIndexAllocated;
    char size_unit;
    cout << "Enter the size : ";
    cin >> size;
    cout << "Enter the unit (K, M, G) : ";
    cin >> size_unit;
    fstream file("memory_management_storage_file.txt", ios::in | ios::out);
    if (size_unit == 'G') {
        size *= (1024 * 1024);
    } else if (size_unit == 'M') {
        size *= 1024;
    }
    file1.clear();
    printNotUsedMemory(file);
    // firstFitAlgorithm(file, size);
    // bestFitAlgorithm(file, size);
    // worstFitAlgorithm(file, size);
    nextFitAlgorithm(file, size, lastIndexAllocated, file1);
    printNotUsedMemory(file);
    file.close();
    return 0;
}

void firstFitAlgorithm(fstream & file, int sizeToAllocated) {
    char ch;
    int pos = 0;
    file.seekg(0, ios::beg);
    int currentSize = 0;
    while(file.get(ch)) {
        if (ch == '0') {
            currentSize++;
            if (currentSize == sizeToAllocated) {
                file.seekp(pos - sizeToAllocated + 1, ios::beg);
                for (int i=0; i<sizeToAllocated; i++) {
                    file.put('1');
                }
                cout << "Memory Allocated" << endl;
                return;
            }
        } else {
            currentSize = 0;
        }
        pos++;
    }
    cout << "No Space for Allocation" << endl;
    file.clear();
    file.seekg(0, std::ios::beg);
}

void printNotUsedMemory(fstream & file) {
    int currentSize = 0;
    int startIndex = -1;
    char ch;
    int pos = 0;
    file.seekg(0, ios::beg);
    while(file.get(ch)) {
        if (ch == '0') {
            if (currentSize == 0) startIndex = pos;
            currentSize++;
        } else {
            if (currentSize > 0) {
                cout << currentSize << " memory is available from " << startIndex << " to " << (pos - 1) << endl;
                currentSize = 0;
            }
        }
        pos++;
    }
    if (currentSize > 0) {
        cout << currentSize << " memory is available from " << startIndex << " to " << (max_size - 1) << endl;
    }
    file.clear();
    file.seekg(0, std::ios::beg);
}

void bestFitAlgorithm(fstream &file, int size) {
    int currentSize = 0;
    int index = -1;
    int findMinBlock = INT_MAX;
    char ch;
    file.seekg(0, ios::beg);
    file.seekp(0, ios::beg);
    int pos = 0;
    while(file.get(ch)) {
        if (ch == '0') {
            currentSize++;
            if (currentSize >= size) {
                if (findMinBlock > currentSize) {
                    findMinBlock = currentSize;
                    index = pos - currentSize + 1;
                }
            }
        } else {
            currentSize = 0;
        }
        pos++;
    }
    if (index != -1) {
        file.clear();
        file.seekp(index, ios::beg);
        for (int i = 0; i < size; i++) {
            file.put('1');
        }
        cout << "Memory Allocated" << endl;
    } else {
        cout << "No Space for Allocation!" << endl;
    }
    file.clear();
    file.seekg(0, ios::beg);
}

void worstFitAlgorithm(fstream & file, int size) {
    int currentSize = 0;
    int index = -1;
    int findMaxBlock = INT_MIN;
    char ch;
    file.seekg(0, ios::beg);
    file.seekp(0, ios::beg);
    int pos = 0;
    while(file.get(ch)) {
        if (ch == '0') {
            currentSize++;
            if (currentSize >= size) {
                if (findMaxBlock < currentSize) {
                    findMaxBlock = currentSize;
                    index = pos - currentSize + 1;
                }
            }
        } else {
            currentSize = 0;
        }
        pos++;
    }
    if (index != -1) {
        file.clear();
        file.seekp(index, ios::beg);
        for (int i = 0; i < size; i++) {
            file.put('1');
        }
        cout << "Memory Allocated" << endl;
    } else {
        cout << "No Space for Allocation!" << endl;
    }
    file.clear();
    file.seekg(0, ios::beg);
}

void nextFitAlgorithm(fstream & file, int sizeToAllocated, int & lastIndexAllocated, fstream & file1) {
    int currentSize = 0; 
    char ch;
    file.seekg(lastIndexAllocated, ios::beg);
    int pos = lastIndexAllocated;
    while(file.get(ch)) {
        if (ch == '0') {
            currentSize++;
            if (currentSize == sizeToAllocated) {
                file.seekp(pos - currentSize + 1, ios::beg);
                for (int i=0; i<sizeToAllocated; i++) {
                    file.put('1');
                }
                file1.seekp(0, ios::beg);
                file1 << pos + 1;
                lastIndexAllocated = file.tellp();
                cout << "Memory Allocated" << endl;
                return;
            }
        } else {
            currentSize = 0;
        }
        pos++;
    }
    cout << "No Space for Allocation" << endl;
    file1 << 0;
    file.clear();
    file.seekg(0, ios::beg);
}

PYBIND11_MODULE(memory_management, m) {
    m.def("firstFitAlgorithm", &firstFitAlgorithm);
    m.def("bestFitAlgorithm", &bestFitAlgorithm);
    m.def("worstFitAlgorithm", &worstFitAlgorithm);
    m.def("nextFitAlgorithm", nextFitAlgorithm);
    m.def("printNotUsedMemory", printNotUsedMemory);
}