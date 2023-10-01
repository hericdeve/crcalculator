#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "fileManagement.h"
#include "grade.h"
#include "subject.h"



// Helper function to trim whitespace from both ends of a string



#include <algorithm>
#include <cctype>
#include <string>

std::string trim(const std::string& str) {
    std::string copy = str;
    copy.erase(std::remove_if(copy.begin(), copy.end(), ::isspace), copy.end());
    return copy;
}


Grade readCSV(const std::string& filePath) {
    std::ifstream file(filePath);
    std::string line;
    Grade grade;

    while (std::getline(file, line)) {
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

            Subject newSubject(name, nota, peso, periodo);
            grade += newSubject;
        } catch (const std::invalid_argument& ia) {
            std::cerr << "Invalid data in CSV file: " << ia.what() << '\n';
        }
    }

    return grade;
}

