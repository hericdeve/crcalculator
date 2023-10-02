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
    this->filePath = home + "/Documents/CRmanager/notas.csv";
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
    std::cin.ignore();  // Ignore any leftover newline character in the input buffer
    std::getline(std::cin, name);

    std::cout << "Enter grade: ";
    while (!(std::cin >> nota)) {
        std::cout << "Invalid input. Please enter a number for the grade: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Enter weight: ";
    while (!(std::cin >> peso)) {
        std::cout << "Invalid input. Please enter a number for the weight: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Enter period: ";
    while (!(std::cin >> periodo)) {
        std::cout << "Invalid input. Please enter a number for the period: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    Subject newSubject(name, nota, peso, periodo);
    grade += newSubject;

    // Save the updated Grade object to the .csv file
    writeCSV(filePath, grade);

    std::cout << "Subject added successfully.\n"
              << "\033[0m";  // Reset color
}


void MenuInterface::deleteSubject() {
    std::string name;

    std::cout << "\033[1;32m"  // Set color to green
              << "Enter subject name: ";
    std::cin.ignore();  // Ignore any leftover newline character in the input buffer
    std::getline(std::cin, name);

    std::vector<Subject*> matches = grade.searchSubject(name);
    if (matches.empty()) {
        std::cout << "No matching subjects found.\n";
        return;
    }

    std::cout << "Found " << matches.size() << " matching subjects:\n";
    for (size_t i = 0; i < matches.size(); ++i) {
        std::cout << i + 1 << ". " << matches[i]->getNome() 
                  << " (Period: " << matches[i]->getPeriodo() << ")\n";  // Display the period
    }
    
    size_t choice;
    
    if (matches.size() > 1) {
        std::cout << "Enter the number of the subject you want to delete: ";
        std::cin >> choice;
        
        if (choice <= 0 || choice > matches.size()) {
            std::cout << "Invalid choice.\n";
            return;
        }
        
        char confirm;
        std::cout << "Are you sure you want to delete this subject? (y/n): ";
        std::cin >> confirm;
        
        if (confirm == 'y' || confirm == 'Y') {
            grade -= *matches[choice - 1];
            writeCSV(filePath, grade);  // Save the updated Grade object
            std::cout << "Subject deleted successfully.\n"
                      << "\033[0m";  // Reset color
        } else {
            std::cout << "Deletion cancelled.\n"
                      << "\033[0m";  // Reset color
        }
                  
        return;
        
     } else if (matches.size() == 1) {
         char confirm;
         std::cout << "Are you sure you want to delete this subject? (y/n): ";
         std::cin >> confirm;
         
         if (confirm == 'y' || confirm == 'Y') {
             grade -= *matches[0];
             writeCSV(filePath, grade);  // Save the updated Grade object
             std::cout << "Subject deleted successfully.\n"
                       << "\033[0m";  // Reset color
         } else {
             std::cout << "Deletion cancelled.\n"
                       << "\033[0m";  // Reset color
         }
                   
         return;
     }
}


void MenuInterface::editSubject() {
    std::string name;

    std::cout << "\033[1;32m"  // Set color to green
              << "Enter subject name: ";
    std::cin.ignore();  // Ignore any leftover newline character in the input buffer
    std::getline(std::cin, name);

    std::vector<Subject*> matches = grade.searchSubject(name);
    if (matches.empty()) {
        std::cout << "No matching subjects found.\n";
        return;
    }

    std::cout << "Found " << matches.size() << " matching subjects:\n";
    for (size_t i = 0; i < matches.size(); ++i) {
        std::cout << i + 1 << ". " << matches[i]->getNome() 
                  << " (Period: " << matches[i]->getPeriodo() << ")\n";  // Display the period
    }
    
    size_t choice;
    
    if (matches.size() > 1) {
        std::cout << "Enter the number of the subject you want to edit: ";
        std::cin >> choice;
        
        if (choice <= 0 || choice > matches.size()) {
            std::cout << "Invalid choice.\n";
            return;
        }
        
        char confirm;
        std::cout << "Are you sure you want to edit this subject? (y/n): ";
        std::cin >> confirm;
        
        if (confirm == 'y' || confirm == 'Y') {
            // Get new details for the subject
            std::string newName;
            long newPeriod;
            // ... (add more variables as needed)

            std::cout << "Enter new name for the subject: ";
            std::cin.ignore();  // Ignore any leftover newline character in the input buffer
            std::getline(std::cin, newName);

            std::cout << "Enter new period for the subject: ";
            std::cin >> newPeriod;


            // ... (get more details as needed)

            // Update the subject details
            matches[choice - 1]->setNome(newName);
            matches[choice - 1]->setPeriodo(newPeriod);
            // ... (update more details as needed)

            writeCSV(filePath, grade);  // Save the updated Grade object

            std::cout << "Subject edited successfully.\n"
                      << "\033[0m";  // Reset color
        } else {
            std::cout << "Edit cancelled.\n"
                      << "\033[0m";  // Reset color
        }
                  
        return;
        
     } else if (matches.size() == 1) {
         char confirm;
         std::cout << "Are you sure you want to edit this subject? (y/n): ";
         std::cin >> confirm;
         
         if (confirm == 'y' || confirm == 'Y') {
             // Get new details for the subject
             std::string newName;
             long newPeriod;
             // ... (add more variables as needed)

             std::cout << "Enter new name for the subject: ";
             std::cin.ignore();  // Ignore any leftover newline character in the input buffer
             std::getline(std::cin, newName);

             std::cout << "Enter new period for the subject: ";
             std::cin >> newPeriod;

             // ... (get more details as needed)

             // Update the subject details
             matches[0]->setNome(newName);
             matches[0]->setPeriodo(newPeriod);
             // ... (update more details as needed)

             writeCSV(filePath, grade);  // Save the updated Grade object

             std::cout << "Subject edited successfully.\n"
                       << "\033[0m";  // Reset color
         } else {
             std::cout << "Edit cancelled.\n"
                       << "\033[0m";  // Reset color
         }
                   
         return;
     }
}




