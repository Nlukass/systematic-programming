# include <string>
# include <iostream>
# include <vector>
# include <algorithm>
# include <iomanip>
# include <random>
# include <fstream>
# include <sstream>
# include <iterator>
# include "Person.h"
# include <chrono>
# include <list>
# include <deque>
using namespace std;

#define MEASURE_TIME(tag, code) \
{ \
  auto start = chrono::high_resolution_clock::now (); \
  bool success = true; \
  try { \
    code \
  } \
  catch (...) { \
    success = false; \
  } \
  auto stop = chrono::high_resolution_clock::now (); \
  chrono::duration<double, milli> ms = stop - start; \
  if (success) { \
    cout << #tag << ": time taken " << ms.count () << " ms\n"; \
  } \
  else { \
    cout << #tag << ": time was not measured due to failure\n"; \
  } \
}

int main() {
    cout << "Loading file ...";

    list<Person> passed;
    deque<Person> failed;

    cout << "Enter homework final score calculation method (`a` for average, `m` for median): ";
    char average_or_median_input;
    cin >> average_or_median_input;

    ifstream file;

    cout << "Measuring time for file load operation:\n";
    MEASURE_TIME(openning_file, {
        file.open("students.txt");
    });


    string header;
    getline(file, header);

    string line;
    int numOfStudents = 0;
    while(getline(file, line)) {
        istringstream iss(line);
        Person student(average_or_median_input);
        iss >> student;
        ++numOfStudents;
        if (student.passed()) {
            passed.push_back(student);
        } else {
            failed.push_back(student);
        }
    }

    // Output students to standard output
    string finalPointTitle;
    if (average_or_median_input == 'a') {
        finalPointTitle = "Final_Point(Ave.)";
    } else {
            finalPointTitle = "Final_Point(Med.)";
    }
    cout << left << setw(25) << "Name" <<  setw(25) << "Surname" << setw(25) << finalPointTitle << endl;
    cout << "------------------------------------------------------------------------------" << endl;

    cout << "• Passed:\n";
        list<Person>::iterator it;
        for (it = passed.begin(); it != passed.end(); it++)
        {
            Person p = *it;
            cout << p << endl;
        }

        cout << "• Failed:\n";
        for (int i = 0; i < failed.size(); i++) {
            cout << failed[i] << endl;
        }
    cout << "Measuring time for file outputs:\n";
    MEASURE_TIME(file_output,{
        // Output students vector to files
        ofstream output_passed_file("./passed.txt");
        list<Person>::iterator it;
        for (it = passed.begin(); it != passed.end(); it++)
        {
            Person p = *it;
            output_passed_file << p << "\n";
        }
        output_passed_file.close();

        ofstream output_failed_file("./failed.txt");
        for (int i = 0; i < failed.size(); ++i) {
            output_failed_file << failed[i] << "\n";
        }
        output_failed_file.close();
    });


    file.close();

    return 0;
}
