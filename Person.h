#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Person
{
private:
    string firstname;
    string lastname;
    double exam;
    vector<double> homeworks;
    double final_grade;
    char average_or_median;

    double calculate_final_grade();

    double calculate_average(const vector<double> &numbers);

    double calculate_median(const vector<double> &numbers);

    double generate_random_scores();

public:
    Person(char homeworkFinalScoreType);

    Person(const Person &person);

    ~Person();

    Person &operator=(const Person &person);

    friend istream &operator>>(istream &in, Person &person);

    friend ostream &operator<<(ostream &os, Person &person);

    bool passed();
};

#endif
