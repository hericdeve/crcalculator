#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
#include <algorithm>
#include "fileManagement.h"
#include "grade.h"
#include "subject.h"

std::string trim(const std::string& str) {
    std::string copy = str;
    copy.erase(std::remove_if(copy.begin(), copy.end(), ::isspace), copy.end());
    return copy;
}

// Comparison function
bool compareSubjects(const Subject& a, const Subject& b) {
    if (a.getPeriodo() == b.getPeriodo()) {
        return a.getNome() < b.getNome();
    }
    return a.getPeriodo() < b.getPeriodo();
}


Grade readCSV(const std::string& filePath) {
    std::ifstream file(filePath);

    // Check if the file was successfully opened
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << '\n';
        return Grade();  // Return an empty Grade object
    }

    std::string line;
    Grade grade;

    while (std::getline(file, line)) {
        // Skip empty lines
        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);
        std::string name;
        std::string notaStr, pesoStr, periodoStr;

        std::getline(ss, name, ',');
        std::getline(ss, notaStr, ',');
        std::getline(ss, pesoStr, ',');
        std::getline(ss, periodoStr, ',');

        // Trim whitespace from the strings
        name = trim(name);
        notaStr = trim(notaStr);
        pesoStr = trim(pesoStr);
        periodoStr = trim(periodoStr);

        try {
            double nota = std::stod(notaStr);
            double peso = std::stod(pesoStr);
            long periodo = std::stol(periodoStr);

            // Validate the data
            if (nota < 0 || nota > 10) {
                throw std::invalid_argument("nota must be between 0 and 10");
            }
            if (peso < 0) {
                throw std::invalid_argument("peso must be positive");
            }
            if (periodo <= 0) {
                throw std::invalid_argument("periodo must be positive");
            }

            Subject newSubject(name, nota, peso, periodo);
            grade += newSubject;
        } catch (const std::invalid_argument& ia) {
            std::cerr << "Invalid data in CSV file: " << ia.what() << '\n';
        }
    }

    return grade;
}


void writeCSV(const std::string& filePath, Grade& grade) {
    std::ofstream file(filePath);

    // Check if the file was successfully opened
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << '\n';
        return;
    }

    // Get the subjects from the Grade object
    std::vector<Subject>& subjects = grade.getSubjectsForEditing();

    // Sort the subjects by period and then by name
    std::sort(subjects.begin(), subjects.end(), compareSubjects);

    // Write each subject to the file
    for (const Subject& subject : subjects) {
        try {
            file << subject.getNome() << ","
                 << subject.getNota() << ","
                 << subject.getPeso() << ","
                 << subject.getPeriodo() << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Error writing to file: " << e.what() << '\n';
            // Close the file and return after encountering an error
            file.close();
            return;
        }
    }

    // Close the file
    file.close();
}

