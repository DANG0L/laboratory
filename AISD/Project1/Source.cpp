#include <iostream>
#include "Header.h"

using namespace std;


void split(const char* fileName, const char* fileOut1, const char* fileOut2) {
    ifstream file(fileName);
    ofstream F[2];
    F[0].open(fileOut1);
    F[1].open(fileOut2);

    int x1, x2, n = 0;
    file >> x1;

    while (!file.eof()) {
        F[n] << x1 << " ";
        file >> x2;

        if (x1 > x2)
            n = 1 - n;

        x1 = x2;
    }
    file.close();
    F[0].close(); F[1].close();
}


void merge(const char* fileIn1, const char* fileIn2, const char* fileOut1, const char* fileOut2) {
    ifstream f1(fileIn1), f2(fileIn2);
    ofstream f3(fileOut1), f4(fileOut2);

    int x1, x2, y1, y2;

    f1 >> y1;
    f2 >> y2;

    while (!f1.eof() && !f2.eof()) {
        x1 = y1;
        x2 = y2;

        while (x1 <= y1 && x2 <= y2 && !f1.eof() && !f2.eof()) {

            if (y1 < y2) {
                f3 << y1 << " ";
                x1 = y1;
                f1 >> y1;
            }
            else {
                f3 << y2 << " ";
                x2 = y2;
                f2 >> y2;
            }
        }

        while (x1 <= y1 && !f1.eof()) {
            f3 << y1 << " ";
            x1 = y1;
            f1 >> y1;
        }

        while (x2 <= y2 && !f2.eof()) {
            f3 << y2 << " ";
            x2 = y2;
            f2 >> y2;
        }

        //---

        x1 = y1;
        x2 = y2;

        while (x1 <= y1 && x2 <= y2 && !f1.eof() && !f2.eof()) {

            if (y1 < y2) {
                f4 << y1 << " ";
                x1 = y1;
                f1 >> y1;
            }
            else {
                f4 << y2 << " ";
                x2 = y2;
                f2 >> y2;
            }
        }

        while (x1 <= y1 && !f1.eof()) {
            f4 << y1 << " ";
            x1 = y1;
            f1 >> y1;
        }

        while (x2 <= y2 && !f1.eof()) {
            f4 << y2 << " ";
            x2 = y2;
            f2 >> y2;
        }

    }

    while (!f1.eof()) {
        f4 << y1 << " ";
        f1 >> y1;
    }

    while (!f2.eof()) {
        f4 << y2 << " ";
        f2 >> y2;
    }

    f1.close(); f2.close();
    f3.close(); f4.close();

    f3.open(fileIn1, ios_base::trunc);
    f4.open(fileIn2, ios_base::trunc);
    f3.close(); f4.close();
}



const char* whatFileIsSorted(const char* file1, const char* file2, const char* file3, const char* file4) {
    ifstream file;

    file.open(file1);
    if (!(file.peek() == EOF)) return file1;
    file.close();

    file.open(file2);
    if (!(file.peek() == EOF)) return file2;
    file.close();

    file.open(file3);
    if (!(file.peek() == EOF)) return file3;
    file.close();

    file.open(file4);
    if (!(file.peek() == EOF)) return file4;
    file.close();

}

bool checkForEmpty(const char* file1, const char* file2, const char* file3, const char* file4) {
    ifstream file;
    int count = 0;

    file.open(file1);
    if (file.peek() == EOF) count++;
    file.close();

    file.open(file2);
    if (file.peek() == EOF) count++;
    file.close();

    file.open(file3);
    if (file.peek() == EOF) count++;
    file.close();

    file.open(file4);
    if (file.peek() == EOF) count++;
    file.close();

    if (count == 3)
        return true;

    return false;
}

void sort(const char* fileName) {
    split(fileName, "f1.txt", "f2.txt");

    while (!checkForEmpty("f1.txt", "f2.txt", "f3.txt", "f4.txt")) {
        merge("f1.txt", "f2.txt", "f3.txt", "f4.txt");
        merge("f3.txt", "f4.txt", "f1.txt", "f2.txt");
    }
}

int createAndSortFile(const char* fileName, const int numbersCount, const int maxNumberValue) {
    if (!createFileWithRandomNumbers(fileName, numbersCount, maxNumberValue))
        return -1;

    int q = 0;
    cout << "begin? ";
    cin >> q;

    sort(fileName);

    cout << "File " << whatFileIsSorted("f1.txt", "f2.txt", "f3.txt", "f4.txt") << " is sorted" << endl;

    if (!isFileContainsSortedArray(whatFileIsSorted("f1.txt", "f2.txt", "f3.txt", "f4.txt")))
        return -2;

    return 1;
}

int main() {
    const char* fileName = "file.txt";
    const int numbersCount = 10;
    const int maxNumberValue = 10;

    switch (createAndSortFile(fileName, numbersCount, maxNumberValue))
    {
    case 1:
        cout << "Test passed." << std::endl;
        break;

    case -1:
        cout << "Test failed: can't create file." << std::endl;
        break;

    case -2:
        cout << "test failed: file isn't sorted." << std::endl;
        break;
    }

    return 0;
}