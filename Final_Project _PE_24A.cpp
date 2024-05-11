/*************************Presentacion*************************
        PROGRAMA: Final_Project_PE_24A.cpp
        CENTRO UNIVERSITARIO DE LOS ALTOS / UNIVERSIDAD DE GUADALAJARA
        INGENIERIA EN COMPUTACION / 2DO SEMESTRE
        PROFESOR: Sergio Franco Casillas
        DESCRIPCION: Programa para universidad de prestigio
**************************************************************/
#include <iostream>
using namespace std;

bool ciclo = true;
char op_switch;

int main(){

while(ciclo){
    cout << "UndaPRO by UdeG\t\t\t\t\t\t\tUniversity Professional Data Management" << endl;
    cout << "\t1. Agregar estudiantes" << endl;
    cin >> op_switch;
    system("cls");
    switch(op_switch){
        case '1': // Case 1: Agregar estudiantes
            cout << "UndaPRO by UdeG\t\t\t\t\t\t\tUniversity Professional Data Management" << endl;
            cout << "//Agregar estudiantes" << endl;
            cout << "\nCompleta los siguientes campos para registrar los datos del estudiante en nuestro sistema." << endl;
            cin >> op_switch;
            system("cls");
        break;  // Fin case 1
        default:
            cout << "Opcion invalida, seleccione una opcion correcta..." << endl;
        }   // Fin switch principal del programa
    }   // Fin ciclo general del programa
return 0;
}   // Fin main
