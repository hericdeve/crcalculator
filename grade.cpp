#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <unordered_map>
#include <map>
#include "subject.h"
#include "grade.h"

using namespace std;

Grade::Grade() {}

bool operator==(const Subject &subject1, const Subject &subject2) {
    return subject1.getNome() == subject2.getNome() && subject1.getPeriodo() == subject2.getPeriodo();
}

const vector<Subject>& Grade::getSubjects() const {
    return this->subjects;
}

std::vector<Subject>& Grade::getSubjectsForEditing() {
    return this->subjects;
}


Grade& Grade::operator+=(Subject &subject) {
    for (const Subject& existingSubject : this->subjects) {
        if (subject == existingSubject) {
            std::cout << "Subject with the same name and period already cataloged.\n";
            return *this;
        }
    }
    try {
        this->subjects.emplace_back(subject);
        std::cout << "Discipline added.\n";
    } catch (const std::exception& e) {
        std::cerr << "Error adding subject: " << e.what() << '\n';
    }
    return *this;
}


Grade& Grade::operator-=(const Subject &subject) {
    subjects.erase(std::remove(subjects.begin(), subjects.end(), subject), subjects.end());
    return *this;
}



std::ostream& operator<<(std::ostream &os, const Grade &grade) {   
    const std::vector<Subject>& subjects = grade.getSubjects();
    
    os << "\033[1;36m"  // Set color to cyan
       << std::left << std::setw(45) << "Disciplina" 
       << std::setw(10) << "Nota" 
       << std::setw(10) << "Peso" 
       << std::setw(10) << "Período" 
       << "\033[0m"  // Reset color
       << "\n\n";

    os << std::string(75, '-') << "\n";

    for (const Subject& subject : subjects) {
        os << "\033[1;32m"  // Set color to green
           << std::left << std::setw(45) << subject.getNome() 
           << "\033[1;33m"  // Set color to yellow
           << std::fixed << std::setw(10) << std::setprecision(1)  << subject.getNota() 
           << "\033[1;35m"  // Set color to magenta
           << std::setw(10) << subject.getPeso() 
           << "\033[1;34m"  // Set color to blue
           << std::setw(10) << subject.getPeriodo() 
           << "\033[0m"  // Reset color
           << "\n";
    }

    return os;
}



double Grade::calculateCRA() const {
    double totalGrade = 0.0;
    double totalWeight = 0.0;
    try {
        for (const Subject& subject : subjects) {
            totalGrade += subject.getNota() * subject.getPeso();
            totalWeight += subject.getPeso();
        }
        if (totalWeight == 0) {
            throw std::invalid_argument("Total weight cannot be zero");
        }
    } catch (const std::exception& e) {
        std::cerr << "Error calculating CRA: " << e.what() << '\n';
        return 0.0;
    }
    return totalGrade / totalWeight;
}

double Grade::calculateCRAHighestGrade() const {
    std::unordered_map<std::string, double> highestGrades;
    std::unordered_map<std::string, double> weights;
    double totalWeight = 0.0;

    for (const Subject& subject : subjects) {
        std::string name = subject.getNome();
        double grade = subject.getNota();
        double weight = subject.getPeso();

        if (highestGrades.find(name) == highestGrades.end()) {
            highestGrades[name] = grade;
            weights[name] = weight;
            totalWeight += weight;
        } else if (grade > highestGrades[name]) {
            highestGrades[name] = grade;
        }
    }

    double totalGrade = 0.0;
    for (const auto& pair : highestGrades) {
        totalGrade += pair.second * weights[pair.first];
    }

    if (totalWeight == 0) {
        throw std::invalid_argument("Total weight cannot be zero");
    }

    return totalGrade / totalWeight;
}

std::map<long, double> Grade::calculateCRAPerPeriod() const {
    std::map<long, std::pair<double, double>> gradesAndWeightsPerPeriod;

    for (const Subject& subject : subjects) {
        long period = subject.getPeriodo();
        double grade = subject.getNota();
        double weight = subject.getPeso();

        if (gradesAndWeightsPerPeriod.find(period) == gradesAndWeightsPerPeriod.end()) {
            gradesAndWeightsPerPeriod[period] = std::make_pair(grade * weight, weight);
        } else {
            gradesAndWeightsPerPeriod[period].first += grade * weight;
            gradesAndWeightsPerPeriod[period].second += weight;
        }
    }

    std::map<long, double> craPerPeriod;
    for (const auto& pair : gradesAndWeightsPerPeriod) {
        craPerPeriod[pair.first] = pair.second.first / pair.second.second;
    }

    return craPerPeriod;
}

