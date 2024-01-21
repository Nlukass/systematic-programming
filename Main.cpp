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
    cout << "Load file with (1) 10K (2) 100K records: ";
    int fileNum;
    cin >> fileNum;

    list<Person> passedStudents;
    deque<Person> failedStudents;

    cout << "Enter homework final score calculation type (`a` for average, `m` for median): ";
    string hwFinalScoreTypeInput;
    cin >> hwFinalScoreTypeInput;
    HomeworkFinalScoreType hwFinalScoreType;
    if (hwFinalScoreTypeInput == "a") {
        hwFinalScoreType = AVERAGE;
    } else if (hwFinalScoreTypeInput == "m") {
        hwFinalScoreType = MEDIAN;
    } else {
        throw invalid_argument("Homework final score calculation type should be either `a` (average) or `m` (median)");
    }

    ifstream file;
    string input_filename;
    try {
        if (fileNum == 1) {
            input_filename = "students10000.txt";
        } else if (fileNum == 2) {
            input_filename = "students100000.txt";
        } else {
            throw invalid_argument("File number should be in the acceptable range.");
        }  
    } catch(runtime_error &e) {
        cout << "Error: " << e.what() << endl;
    }
      

    cout << "Measuring time for file load operation:\n";
    MEASURE_TIME(openning_file, {
        file.open(input_filename);
    });


    string header;
    getline(file, header);

    string line;
    int numOfStudents = 0;
    while(getline(file, line)) {
        istringstream iss(line);
        Person student(hwFinalScoreType);
        iss >> student;
        ++numOfStudents;
        if (student.passed()) {
            passedStudents.push_back(student);
        } else {
            failedStudents.push_back(student);
        }
    }

    // Output students to standard output
    // string finalPointTitle;
    // if (hwFinalScoreType == AVERAGE) {
    //     finalPointTitle = "Final_Point(Ave.)";
    // } else {
    //         finalPointTitle = "Final_Point(Med.)";
    // }
    // cout << left << setw(25) << "Name" <<  setw(25) << "Surname" << setw(25) << finalPointTitle << endl;
    // cout << "------------------------------------------------------------------------------" << endl;

    // cout << "Measuring time for standard outputs:\n";
    // MEASURE_TIME(standard_output, {
    //     cout << "• Passed:\n";
    //     list<Person>::iterator it;
    //     for (it = passedStudents.begin(); it != passedStudents.end(); it++)
    //     {
    //         Person p = *it;
    //         cout << p << endl;
    //     }

    //     cout << "• Failed:\n";
    //     for (int i = 0; i < failedStudents.size(); i++) {
    //         cout << failedStudents[i] << endl;
    //     }
    // });

    cout << "Measuring time for file outputs:\n";
    MEASURE_TIME(file_output,{
        // Output students vector to files
        ofstream output_passed_file("./passed.txt");
        list<Person>::iterator it;
        for (it = passedStudents.begin(); it != passedStudents.end(); it++)
        {
            Person p = *it;
            output_passed_file << p << "\n";
        }
        cout << "File passed.txt was generated!" << endl;
        output_passed_file.close();

        ofstream output_failed_file("./failed.txt");
        for (int i = 0; i < failedStudents.size(); ++i) {
            output_failed_file << failedStudents[i] << "\n";
        }
        cout << "File failed.txt was generated!" << endl;
        output_failed_file.close();
    });

    
    file.close();

    return 0;
}
