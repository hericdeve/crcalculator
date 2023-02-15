#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include <getopt.h>
#include "grade.h"
#include "subject.h"
#include "groupby.h"

using namespace std;

// static void test()
// {
//   vector<Foo> foos;
//   foos.push_back({5,"bill",2.1});
//   foos.push_back({5,"rick",3.7});
//   foos.push_back({3,"tom",2.5});
//   foos.push_back({7,"joe",3.4});
//   foos.push_back({5,"bob",7.2});

//   ostringstream out;

//   for (auto group : group_by(foos.begin(),foos.end(),FooX())) {
//     out << group.value << ":";
//     for (auto elem : group.range) {
//       out << " " << elem.y;
//     }
//     out << "\n";
//   }

//   assert(out.str()==
//     "5: bill rick\n"
//     "3: tom\n"
//     "7: joe\n"
//     "5: bob\n"
//   );
// }

int
main(int argc, char **argv){
    char *shortOpt = "s::S::a::A::d::D::hH";
    int opt, command;
    opterr = 0;  
    fstream entrada;
    int indice;
    vector <double> notas;
    vector <double> pesos;
    double soma = 0;
    double cra = 0;
    double divisor = 0;
    // cout << argv[argc-1] << endl;

    
    entrada.open("notas.csv", ios::in);
    string linha;
    Grade grade;
    // cout << "AA" << endl;
    vector<string> row;
    string line, word, temp;

    while(entrada)
    {   

        // cout << "temp: " << entrada << endl;
        row.clear();
        getline(entrada, line);
        if (line != "")
        {

        // cout << "line: " << line << endl;
        stringstream s(line);
        while (getline(s, word, ',')) {
            // cout << word << endl;
            // add all the column data
            // of a row to a vector
            row.push_back(word);
        }
        
        // cout << row.front() << endl;
        Subject subject;
        // cout << "BB" << endl;
        // entrada >> linha;
        // cout << linha << endl;
        subject.setNome(row[0]);
        // entrada >> linha;
        subject.setNota(stod(row[1]));
        // entrada >> linha;
        subject.setPeso(stod(row[2]));
        // entrada >> linha;
        subject.setPeriodo(stol(row[3]));
        // cout << linha << endl;
        // cout << "nome: " << subject.getNome() << endl;
        grade+=subject;
        }
        else{
            break;
        }
    
    }
   
    

    // cout << grade.subjects.front().getNome();
    // notas.pop_back();

    // for (indice = 1; indice < argc - 1 ; indice+=2)
    // {
    
    //     notas.push_back(stod(argv[indice]));
    //     pesos.push_back(stod(argv[indice+1]));
    // }

    // for (indice = 0; static_cast<unsigned long> (indice) < notas.size(); indice++)
    // {
    //     cout << "nota: " << indice << " : " << notas.at(indice) << endl;
    //     cout << "peso: " << indice << " : " << pesos.at(indice) << endl;
    //     soma += notas.at(indice) * pesos.at(indice);
    //     divisor += pesos.at(indice);

    // }
    // cra = soma/divisor;
    // cout << "CRA: " << cra << endl;

    // cout << "Cálculo do CRA" << endl << endl;
    //    for (vector<Subject>::iterator it = grade.subjects.begin(); it != grade.subjects.end(); it++)
    //     {
            
    //         cout << it->getNome() << endl;
    //         cout << it->getNota() << endl;
        
    //     }

    // ostringstream out;

    // for (auto group : group_by(grade.getSubjects().begin(),grade.getSubjects().end(), )) {
    //     out << group.value << ":";
    //     for (auto elem : group.range) {
    //     out << " " << elem.getNome();
    //     }
    //     out << "\n";
    // }

    // assert(out.str()==
    // "5: bill rick\n"
    // "3: tom\n"
    // "7: joe\n"
    // "5: bob\n"
    // );

    // cout << out.str();
    

    

    while ((opt = getopt (argc, argv, shortOpt)) != -1)
    {
       
        // cout << "Menu de opções: " << endl << endl;
        // cout << "1)Add subject" << endl;
        // cout << "2)Del subject" << endl;
        // cout << "3)Mostrar CR" << endl;
        // cout << "4)*" << endl;
        // cout << "0)Sair" << endl;
        // cin >> opt;
        switch (opt){
            case 's':
            case 'S':
                cout<<grade;
            case 3:
            case 0:
                break;

            default:
                break;

        }
     
       
    }
  

    return 0;

}