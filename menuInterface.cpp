#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <iomanip>
#include <map>
#include "fileManagement.h"
#include "menuInterface.h"
#include "subject.h"

MenuInterface::MenuInterface() {
    std::string home = getenv("HOME");
    std::string filePath = home + "/Documents/CRmanager/notas.csv";
    std::ifstream file(filePath);
    if (!file.good()) {
        std::cout << "\033[1;31m"  // Set color to red
                  << "Could not find notas.csv in the default directory.\n"
                  << "Please enter the path to notas.csv: "
                  << "\033[0m";  // Reset color
        std::cin >> filePath;
    }
    grade = readCSV(filePath);
}

void MenuInterface::run() {
    int choice;
    do {
        showMenu();
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\033[1;31m"  // Set color to red
                      << "Invalid input. Please enter a number.\n"
                      << "\033[0m";  // Reset color
            continue;
        }
        switch (choice) {
            case 1: showCRA(); break;
            case 2: showCRAHighestGrade(); break;
            case 3: showCRAPerPeriod(); break;
            case 4: showGrade(); break;
            case 5: addSubject(); break;
            case 6: deleteSubject(); break;
            case 7: editSubject(); break;
            case 0: break;
            default: 
                std::cout << "\033[1;31m"  // Set color to red
                          << "Invalid option. Please choose a number from the menu.\n"
                          << "\033[0m";  // Reset color
        }
    } while (choice != 0);
}

void MenuInterface::showMenu() {
    std::cout << "\n\033[1;36m"  // Set color to cyan
              << "1) Show CRA\n"
              << "2) Show CRA (Highest Grades Only)\n"
              << "3) Show CRA Per Period\n"
              << "4) Show Grade\n"
              << "5) Add Subject\n"
              << "6) Delete Subject\n"
              << "7) Edit Subject\n"
              << "0) Exit\n"
              << "\033[0m\n";  // Reset color
}



void MenuInterface::showCRA() {
    double cra = grade.calculateCRA();
    std::cout << "\033[1;33m"  // Set color to yellow
              << "The current CRA is: " << std::fixed << std::setprecision(4) << cra
              << "\033[0m"  // Reset color
              << "\n";
}

void MenuInterface::showCRAHighestGrade() {
    double cra = grade.calculateCRAHighestGrade();
    std::cout << "\033[1;33m"  // Set color to yellow
              << "The current CRA (highest grades only) is: " << std::fixed << std::setprecision(4) << cra
              << "\033[0m"  // Reset color
              << "\n";
}

void MenuInterface::showCRAPerPeriod() {
    std::map<long, double> craPerPeriod = grade.calculateCRAPerPeriod();

    std::cout << "\033[1;36m"  // Set color to cyan
              << std::left << std::setw(10) << "Period" 
              << std::setw(10) << "CRA" 
              << "\033[0m"  // Reset color
              << "\n\n";

    for (const auto& pair : craPerPeriod) {
        std::cout << "\033[1;32m"  // Set color to green
                  << std::left << std::setw(10) << pair.first 
                  << "\033[1;33m"  // Set color to yellow
                  << std::fixed << std::setw(10) << std::setprecision(4)  << pair.second
                  << "\033[0m"  // Reset color
                  << "\n";
    }
}



void MenuInterface::showGrade() {
    std::cout << grade;
}

void MenuInterface::addSubject() {
    std::string name;
    double nota, peso;
    long periodo;

    std::cout << "\033[1;32m"  // Set color to green
              << "Enter subject name: ";
    std::cin >> name;

    std::cout << "Enter grade: ";
    std::cin >> nota;

    std::cout << "Enter weight: ";
    std::cin >> peso;

    std::cout << "Enter period: ";
    std::cin >> periodo;

    Subject newSubject(name, nota, peso, periodo);
    grade += newSubject;

    std::cout << "Subject added successfully.\n"
              << "\033[0m";  // Reset color
}

void MenuInterface::deleteSubject() {
    std::string name;
    std::cout << "\033[1;32m"  // Set color to green
              << "Enter subject name to delete: ";
    std::cin >> name;

    for (const Subject& subject : grade.getSubjects()) {
        if (subject.getNome() == name) {
            grade -= subject;
            std::cout << "Subject deleted successfully.\n"
                      << "\033[0m";  // Reset color
            return;
        }
    }

    std::cout << "\033[1;31m"  // Set color to red
              << "Subject not found.\n"
              << "\033[0m";  // Reset color
}



void MenuInterface::editSubject() {
    std::string name;
    double nota, peso;
    long periodo;

    std::cout << "\033[1;32m"  // Set color to green
              << "Enter subject name to edit: ";
    std::cin >> name;

    for (Subject& subject : grade.getSubjectsForEditing()) {
        if (subject.getNome() == name) {
            std::cout << "Enter new grade: ";
            std::cin >> nota;
            subject.setNota(nota);

            std::cout << "Enter new weight: ";
            std::cin >> peso;
            subject.setPeso(peso);

            std::cout << "Enter new period: ";
            std::cin >> periodo;
            subject.setPeriodo(periodo);

            std::cout << "Subject edited successfully.\n"
                      << "\033[0m";  // Reset color
            return;
        }
    }

    std::cout << "\033[1;31m"  // Set color to red
              << "Subject not found.\n"
              << "\033[0m";  // Reset color
}

