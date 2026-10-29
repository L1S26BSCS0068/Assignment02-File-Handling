/*
 * Name       : Ahmed Nissar
 * Reg No     : L1S26BSCS0068
 * Assignment : 02 - File Handling
 * Question   : Q3 - Scholarship
 */

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
int main() {
    // The file name is typed by the user and may contain spaces, so use getline
    char path[100];
    cout << "Enter the file name: ";
    cin.getline(path, 100);

    // Open -> Check
    ifstream inFile(path);
    if (!inFile.is_open()) {
        cout << "Could not open " << path << "!" << endl;
        return 1;
    }

    int n = 0;
    inFile >> n;
    inFile.ignore(100, '\n');   // rest of line 1, otherwise the first name starts with a new line

    if (n > 30) {
        cout << "Too many students!" << endl;
        inFile.close();
        return 1;
    }

    // scholarship.txt is created fresh (overwritten) on every run
    ofstream out("scholarship.txt");

    char name[30];
    double cgpa;
    int count = 0, eligible = 0;
    double sum = 0;
    double top = -1;
    char topName[30] = "";

    for (int i = 0; i < n; i++) {
        // if either read fails, the file ended before n records
        if (!inFile.getline(name, 30, ','))
            break;
        if (!(inFile >> cgpa))
            break;
        inFile.ignore(100, '\n');

        count++;
        sum += cgpa;

        cout << "[" << name << "] CGPA: " << cgpa << endl;

        if (cgpa >= 3.50) {
            eligible++;
            out << name << "," << cgpa << endl;
        }

        // strictly greater, so on a tie the earlier student in the file stays
        if (cgpa > top) {
            top = cgpa;
            strcpy(topName, name);
        }
    }
    inFile.close();
    out.close();

    if (count < n)
        cout << "Warning: only " << count << " of " << n << " records found." << endl;

    if (count == 0) {
        cout << "No students found!" << endl;
        return 0;
    }

    cout << "Students: " << count << endl;
    cout << "Average CGPA: " << sum / count << endl;
    cout << "Eligible for scholarship: " << eligible << endl;
    cout << "Top student: " << topName << " (" << top << ")" << endl;
    return 0;
}