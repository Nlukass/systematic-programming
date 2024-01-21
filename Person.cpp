#include "Person.h"
#include <random>
#include <iomanip>

double Person::calculate_final_grade() {
    double hwFinalScore;
    if (average_or_median == 'a') {
        hwFinalScore = calculate_average(homeworks);
    } else {
        hwFinalScore = calculate_median(homeworks);
    }

    return (0.4 * hwFinalScore) + (0.6 * exam);
}

double Person::calculate_average(const vector<double>& numbers) {
    double sum = 0.0;

    for (const double& num : numbers) {
        sum += num;
    }

    return sum / numbers.size();
}

double Person::calculate_median(const vector<double>& numbers) {
    size_t size = numbers.size();
    if (size % 2 == 0) {
        double midNum1 = numbers[size / 2 - 1];
        double midNum2 = numbers[size / 2];
        return (midNum1 + midNum2) / 2;
    } else {
        return numbers[size / 2];
    }
}

double Person::generate_random_scores() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> distribution(1.0, 10.0);

    return distribution(gen);
}

Person::Person(char average_or_median) : average_or_median(average_or_median) {}

Person::Person(const Person& person) {
    firstname = person.firstname;
    lastname = person.lastname;
    exam = person.exam;
    homeworks = person.homeworks;
    average_or_median = person.average_or_median;
    sort(homeworks.begin(), homeworks.end());
    final_grade = calculate_final_grade();
}

Person::~Person() {}

Person& Person::operator=(const Person& person) {
    if (this != &person) {

        firstname = person.firstname;
        lastname = person.lastname;
        exam = person.exam;
        homeworks = person.homeworks;
        average_or_median = person.average_or_median;

        sort(homeworks.begin(), homeworks.end());
        final_grade = calculate_final_grade();
    }

    return *this;
}

istream& operator>>(istream& in, Person& person) {
    person.homeworks.resize(5);
    in >> person.firstname >> person.lastname >> person.homeworks[0] >> person.homeworks[1] >> person.homeworks[2] >> person.homeworks[3] >> person.homeworks[4] >> person.exam;
    person.final_grade = person.calculate_final_grade();
    return in;
}

ostream& operator<<(ostream& os, Person& person) {
    os << left << setw(25) << person.firstname << setw(25) << person.lastname << setw(25) << fixed << setprecision(2) << person.final_grade;
    return os;
}

bool Person::passed() {
    return final_grade >= 5.0;
}
