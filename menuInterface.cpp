#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <iomanip>
#include <map>
#include "fileManagement.h"
#include "menuInterface.h"
#include "resources.h"
#include "subject.h"

MenuInterface::MenuInterface(Grade& gradeIn) {
    grade = &gradeIn;
    // std::string home = getenv("HOME");
    // std::string defaultDir = home + "/Documents/CRmanager";
    // grade = readOrCreateCSV(defaultDir, "notas.csv");
    // this->filePath = defaultDir + "/notas.csv";
}

void MenuInterface::run() {
    int choice;
    do {
        showMenu();
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\033[1;31m"  // Definir a cor para vermelho
                      << "Entrada inválida. Por favor, insira um número.\n"
                      << "\033[0m";  // Resetar a cor
            continue;
        }
        switch (choice) {
            case 1: showCRA(*grade); break;
            case 2: showCRAHighestGrade(*grade); break;
            case 3: showCRAPerPeriod(*grade); break;
            case 4: showGrade(*grade); break;
            case 5: addSubject(*grade); break;
            case 6: deleteSubject(*grade); break;
            case 7: editSubject(*grade); break;
            case 0: break;
            default: 
                std::cout << "\033[1;31m"  // Definir a cor para vermelho
                          << "Opção inválida. Por favor, escolha um número do menu.\n"
                          << "\033[0m";  // Resetar a cor
        }
    } while (choice != 0);
}

void MenuInterface::showMenu() {
    std::cout << "\n\033[1;36m"  // Definir a cor para ciano
              << "1) Mostrar CRA\n"
              << "2) Mostrar CRA (Apenas Notas Mais Altas)\n"
              << "3) Mostrar CRA Por Período\n"
              << "4) Mostrar Notas\n"
              << "5) Adicionar Matéria\n"
              << "6) Deletar Matéria\n"
              << "7) Editar Matéria\n"
              << "0) Sair\n"
              << "\033[0m\n";  // Resetar a cor
}





