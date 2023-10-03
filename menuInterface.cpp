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
    std::string defaultDir = home + "/Documents/CRmanager";
    grade = readOrCreateCSV(defaultDir, "notas.csv");
    this->filePath = defaultDir + "/notas.csv";
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
            case 1: showCRA(); break;
            case 2: showCRAHighestGrade(); break;
            case 3: showCRAPerPeriod(); break;
            case 4: showGrade(); break;
            case 5: addSubject(); break;
            case 6: deleteSubject(); break;
            case 7: editSubject(); break;
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

void MenuInterface::showCRA() {
    if (grade.getSubjects().empty()) {
        std::cout << "\033[1;31m"  // Definir a cor para vermelho
                  << "Nenhuma matéria foi adicionada."
                  << "\033[0m"  // Resetar a cor
                  << "\n";
        return;
    }

    double cra = grade.calculateCRA();
    std::cout << "\033[1;33m"  // Definir a cor para amarelo
              << "O CRA atual é: " << std::fixed << std::setprecision(4) << cra
              << "\033[0m"  // Resetar a cor
              << "\n";
}

void MenuInterface::showCRAHighestGrade() {
    if (grade.getSubjects().empty()) {
        std::cout << "\033[1;31m"  // Definir a cor para vermelho
                  << "Nenhuma matéria foi adicionada."
                  << "\033[0m"  // Resetar a cor
                  << "\n";
        return;
    }

    double cra = grade.calculateCRAHighestGrade();
    std::cout << "\033[1;33m"  // Definir a cor para amarelo
              << "O CRA atual (apenas notas mais altas) é: " << std::fixed << std::setprecision(4) << cra
              << "\033[0m"  // Resetar a cor
              << "\n";
}

void MenuInterface::showCRAPerPeriod() {
    if (grade.getSubjects().empty()) {
        std::cout << "\033[1;31m"  // Definir a cor para vermelho
                  << "Nenhuma matéria foi adicionada."
                  << "\033[0m"  // Resetar a cor
                  << "\n";
        return;
    }

    std::map<long, double> craPerPeriod = grade.calculateCRAPerPeriod();

    std::cout << "\033[1;36m"  // Definir a cor para ciano
              << std::left << std::setw(10) << "Período" 
              << std::setw(10) << "CRA" 
              << "\033[0m"  // Resetar a cor
              << "\n\n";

    for (const auto& pair : craPerPeriod) {
        std::cout << "\033[1;32m"  // Definir a cor para verde
                  << std::left << std::setw(10) << pair.first 
                  << "\033[1;33m"  // Definir a cor para amarelo
                  << std::fixed << std::setw(10) << std::setprecision(4)  << pair.second
                  << "\033[0m"  // Resetar a cor
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

    std::cout << "\033[1;32m"  // Definir a cor para verde
              << "Insira o nome da matéria: ";
    std::cin.ignore();  // Ignorar qualquer caractere de nova linha restante no buffer de entrada
    std::getline(std::cin, name);

    std::cout << "Insira a nota: ";
    while (!(std::cin >> nota)) {
        std::cout << "Entrada inválida. Por favor, insira um número para a nota: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Insira o peso: ";
    while (!(std::cin >> peso)) {
        std::cout << "Entrada inválida. Por favor, insira um número para o peso: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Insira o período: ";
    while (!(std::cin >> periodo)) {
        std::cout << "Entrada inválida. Por favor, insira um número para o período: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    Subject newSubject(name, nota, peso, periodo);
    grade += newSubject;

    // Salvar o objeto Grade atualizado no arquivo .csv
    writeCSV(filePath, grade);

    std::cout << "Matéria adicionada com sucesso.\n"
              << "\033[0m";  // Resetar a cor
}


void MenuInterface::deleteSubject() {
    std::string name;

    std::cout << "\033[1;32m"  // Definir a cor para verde
              << "Insira o nome da matéria: ";
    std::cin.ignore();  // Ignorar qualquer caractere de nova linha restante no buffer de entrada
    std::getline(std::cin, name);

    std::vector<Subject*> matches = grade.searchSubject(name);
    if (matches.empty()) {
        std::cout << "Nenhuma matéria correspondente encontrada.\n";
        return;
    }

    std::cout << "Encontradas " << matches.size() << " matérias correspondentes:\n";
    for (size_t i = 0; i < matches.size(); ++i) {
        std::cout << i + 1 << ". " << matches[i]->getNome() 
                  << " (Período: " << matches[i]->getPeriodo() << ")\n";  // Exibir o período
    }
    
    size_t choice;
    
    if (matches.size() > 1) {
        std::cout << "Insira o número da matéria que você deseja deletar: ";
        std::cin >> choice;
        
        if (choice <= 0 || choice > matches.size()) {
            std::cout << "Escolha inválida.\n";
            return;
        }
        
        char confirm;
        std::cout << "Você tem certeza que deseja deletar esta matéria? (s/n): ";
        std::cin >> confirm;
        
        if (confirm == 's' || confirm == 'S') {
            grade -= *matches[choice - 1];
            writeCSV(filePath, grade);  // Salvar o objeto Grade atualizado
            std::cout << "Matéria deletada com sucesso.\n"
                      << "\033[0m";  // Resetar a cor
        } else {
            std::cout << "Deleção cancelada.\n"
                      << "\033[0m";  // Resetar a cor
        }
                  
        return;
        
     } else if (matches.size() == 1) {
         char confirm;
         std::cout << "Você tem certeza que deseja deletar esta matéria? (s/n): ";
         std::cin >> confirm;
         
         if (confirm == 's' || confirm == 'S') {
             grade -= *matches[0];
             writeCSV(filePath, grade);  // Salvar o objeto Grade atualizado
             std::cout << "Matéria deletada com sucesso.\n"
                       << "\033[0m";  // Resetar a cor
         } else {
             std::cout << "Deleção cancelada.\n"
                       << "\033[0m";  // Resetar a cor
         }
                   
         return;
     }
}

void MenuInterface::editSubject() {
    std::string name;

    std::cout << "\033[1;32m"  // Definir a cor para verde
              << "Insira o nome da matéria: ";
    std::cin.ignore();  // Ignorar qualquer caractere de nova linha restante no buffer de entrada
    std::getline(std::cin, name);

    std::vector<Subject*> matches = grade.searchSubject(name);
    if (matches.empty()) {
        std::cout << "Nenhuma matéria correspondente encontrada.\n";
        return;
    }

    std::cout << "Encontradas " << matches.size() << " matérias correspondentes:\n";
    for (size_t i = 0; i < matches.size(); ++i) {
        std::cout << i + 1 << ". " << matches[i]->getNome() 
                  << " (Período: " << matches[i]->getPeriodo() << ")\n";  // Exibir o período
    }
    
    size_t choice;
    
    if (matches.size() > 1) {
        std::cout << "Insira o número da matéria que você deseja editar: ";
        std::cin >> choice;
        
        if (choice <= 0 || choice > matches.size()) {
            std::cout << "Escolha inválida.\n";
            return;
        }
        
        char confirm;
        std::cout << "Você tem certeza que deseja editar esta matéria? (s/n): ";
        std::cin >> confirm;
        
        if (confirm == 's' || confirm == 'S') {
            // Obter novos detalhes para a matéria
            std::string newName;
            long newPeriod;
            // ... (adicionar mais variáveis conforme necessário)

            std::cout << "Insira o novo nome para a matéria: ";
            std::cin.ignore();  // Ignorar qualquer caractere de nova linha restante no buffer de entrada
            std::getline(std::cin, newName);

            std::cout << "Insira o novo período para a matéria: ";
            std::cin >> newPeriod;

            // ... (obter mais detalhes conforme necessário)

            // Atualizar os detalhes da matéria
            matches[choice - 1]->setNome(newName);
            matches[choice - 1]->setPeriodo(newPeriod);
            // ... (atualizar mais detalhes conforme necessário)

            writeCSV(filePath, grade);  // Salvar o objeto Grade atualizado

            std::cout << "Matéria editada com sucesso.\n"
                      << "\033[0m";  // Resetar a cor
        } else {
            std::cout << "Edição cancelada.\n"
                      << "\033[0m";  // Resetar a cor
        }
                  
        return;
        
     } else if (matches.size() == 1) {
         char confirm;
         std::cout << "Você tem certeza que deseja editar esta matéria? (s/n): ";
         std::cin >> confirm;
         
         if (confirm == 's' || confirm == 'S') {
             // Obter novos detalhes para a matéria
             std::string newName;
             long newPeriod;
             // ... (adicionar mais variáveis conforme necessário)

             std::cout << "Insira o novo nome para a matéria: ";
             std::cin.ignore();  // Ignorar qualquer caractere de nova linha restante no buffer de entrada
             std::getline(std::cin, newName);

             std::cout << "Insira o novo período para a matéria: ";
             std::cin >> newPeriod;

             // ... (obter mais detalhes conforme necessário)

             // Atualizar os detalhes da matéria
             matches[0]->setNome(newName);
             matches[0]->setPeriodo(newPeriod);
             // ... (atualizar mais detalhes conforme necessário)

             writeCSV(filePath, grade);  // Salvar o objeto Grade atualizado

             std::cout << "Matéria editada com sucesso.\n"
                       << "\033[0m";  // Resetar a cor
         } else {
             std::cout << "Edição cancelada.\n"
                       << "\033[0m";  // Resetar a cor
         }
                   
         return;
     }
}





