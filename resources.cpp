#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <iomanip>
#include <map>
#include "grade.h"
#include "fileManagement.h"


void showCRA(Grade &grade) {
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

void showCRAHighestGrade(Grade &grade) {
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

void showCRAPerPeriod(Grade &grade) {
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


void showGrade(Grade &grade) {
    std::cout << grade;
}

void addSubject(Grade &grade) {
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
    writeCSV(grade.getFilePath(), grade);

    std::cout << "Matéria adicionada com sucesso.\n"
              << "\033[0m";  // Resetar a cor
}


void deleteSubject(Grade &grade) {
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
            writeCSV(grade.getFilePath(), grade);  // Salvar o objeto Grade atualizado
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
             writeCSV(grade.getFilePath(), grade);  // Salvar o objeto Grade atualizado
             std::cout << "Matéria deletada com sucesso.\n"
                       << "\033[0m";  // Resetar a cor
         } else {
             std::cout << "Deleção cancelada.\n"
                       << "\033[0m";  // Resetar a cor
         }
                   
         return;
     }
}

void editSubject(Grade &grade) {
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

            writeCSV(grade.getFilePath(), grade);  // Salvar o objeto Grade atualizado

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

             writeCSV(grade.getFilePath(), grade);  // Salvar o objeto Grade atualizado

             std::cout << "Matéria editada com sucesso.\n"
                       << "\033[0m";  // Resetar a cor
         } else {
             std::cout << "Edição cancelada.\n"
                       << "\033[0m";  // Resetar a cor
         }
                   
         return;
     }
}

