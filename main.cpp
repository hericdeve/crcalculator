#include <iostream>
#include <getopt.h>
#include "menuInterface.h"
#include "fileManagement.h"
#include "grade.h"
#include "resources.h"

int main(int argc, char* argv[]) {
    Grade grade;
    MenuInterface menu(grade);
    int opt;
    static struct option long_options[] = {
    {"mostrarCRA", no_argument, 0, 's'},
    {"mostrarCRAMaiorNota", no_argument, 0, 'S'},
    {"mostrarCRAPorPeriodo", no_argument, 0, 'p'},
    {"mostrarNotas", no_argument, 0, 'g'},
    {"adicionarMateria", no_argument, 0, 'a'},
    {"deletarMateria", no_argument, 0, 'd'},
    {"editarMateria", no_argument, 0, 'e'},
    {"ajuda", no_argument, 0, 'h'},
    {0, 0, 0, 0}
    };


    std::string home = getenv("HOME");
    std::string defaultDir = home + "/Documents/CRmanager";
    grade = readOrCreateCSV(defaultDir, "notas.csv");
    // filePath = defaultDir + "/notas.csv";
    grade.setFilePath(defaultDir + "/notas.csv");

    if (argc >= 2){
        int option_index = 0;
        while ((opt = getopt_long(argc, argv, "sSpgadeh", long_options, &option_index)) != -1) {
            switch (opt) {
                case 's':
                    showCRA(grade);
                    break;
                case 'S':
                    showCRAHighestGrade(grade);
                    break;
                case 'p':
                    showCRAPerPeriod(grade);
                    break;
                case 'g':
                    showGrade(grade);
                    break;
                case 'a':
                    addSubject(grade);
                    break;
                case 'd':
                    deleteSubject(grade);
                    break;
                case 'e':
                    editSubject(grade);
                    break;
                case 'h':
                default:
                    std::cout << "Uso: nome_do_programa [OPÇÃO]...\n"
                    << "Gerencie suas notas e calcule seu CRA.\n"
                    << "\n"
                    << "Opções:\n"
                    << "  -s, --mostrarCRA                 Mostrar o CRA.\n"
                    << "  -S, --mostrarCRAMaiorNota        Mostrar o CRA usando apenas as notas mais altas para cada disciplina.\n"
                    << "  -p, --mostrarCRAPorPeriodo       Mostrar o CRA para cada período.\n"
                    << "  -g, --mostrarNotas               Mostrar os detalhes das notas.\n"
                    << "  -a, --adicionarMateria           Adicionar uma disciplina. Requer um argumento.\n"
                    << "  -d, --deletarMateria             Deletar uma disciplina. Requer um argumento.\n"
                    << "  -e, --editarMateria              Editar uma disciplina. Requer um argumento.\n"
                    << "  -h, --ajuda                      Exibir esta mensagem de ajuda e sair.\n";
                    return opt == 'h' ? 0 : 1;
                    
                    
                    
            }
        }
    }
    else
        menu.run();

   
    return 0;
}
