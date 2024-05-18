/*************************Presentacion*************************
        PROGRAMA: Final_Project_PE_24A.cpp
        CENTRO UNIVERSITARIO DE LOS ALTOS / UNIVERSIDAD DE GUADALAJARA
        INGENIERIA EN COMPUTACION / 2DO SEMESTRE
        PROFESOR: Sergio Franco Casillas
        DESCRIPCION: Programa para universidad de prestigio
**************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Estructura para representar a un familiar
struct Familiar {
    string nombre;
    string apellido_paterno;
    string apellido_materno;
    string vinculo_familiar;
    string numero_telefono;
};

// Estructura para representar a un estudiante
struct Estudiante {
    char grupo;
    string nombre;
    string apellido_paterno;
    string apellido_materno;
    int id;
    Familiar familiar;
    vector<double> calificaciones; // Vector para almacenar calificaciones
    static const int num_materias = 5; // Número de materias
    string materias[num_materias] = {"Español", "Cálculo", "Historia", "Geografía", "Programación"};

    // Método para guardar los datos del estudiante en un archivo de texto
    void guardar_datos(string nombre_archivo) {
        ofstream archivo(nombre_archivo, ios::app); // Abre el archivo en modo de adición

        // Verifica si el archivo se abrió correctamente
        if (archivo.is_open()) {
            // Escribe los datos del estudiante en el archivo
            archivo << "\t\t\t  DATOS DEL ESTUDIANTE" << endl;
            archivo << "GRUPO: " << grupo << endl;
            archivo << "NOMBRE DEL ESTUDIANTE: \t\t" << nombre << " " << apellido_paterno << " " << apellido_materno << endl;
            archivo << "ID DEL ESTUDIANTE: \t\t\t" << id << endl;
            archivo << "\t\t\tDATOS DE CONTACTO DEL FAMILIAR" << endl;
            archivo << "NOMBRE DEL PARIENTE: \t\t" << familiar.nombre << " " << familiar.apellido_paterno << " " << familiar.apellido_materno << endl;
            archivo << "VINCULO FAMILIAR: \t\t\t" << familiar.vinculo_familiar << endl;
            archivo << "NUMERO DE TELEFONO: \t\t" << familiar.numero_telefono << endl;
            archivo << "CALIFICACIONES: " << endl;
            for (int i = 0; i < num_materias; ++i) {
                archivo << materias[i] << ": " << calificaciones[i] << endl;
            }
            archivo << "------------------------------------------------" << endl;

            // Cierra el archivo
            archivo.close();
            cout << "Los datos se han guardado exitosamente en el archivo " << nombre_archivo << endl;
        } else {
            // Si hay un error al abrir el archivo
            cout << "Error al abrir el archivo " << nombre_archivo << endl;
        }
    }

    // Método para ingresar las calificaciones de las materias
    void ingresar_calificaciones() {
    cout << "Ingrese las calificaciones de las siguientes materias (entre 0 y 100):" << endl;
    calificaciones.clear(); // Limpiar calificaciones anteriores

    for (int i = 0; i < num_materias; ++i) {
        double calificacion;
        cout << materias[i] << ": ";
        cin >> calificacion;
        
        // Validar que la calificación esté dentro del rango
        while (calificacion < 0 || calificacion > 100) {
            cout << "La calificación debe estar entre 0 y 100. Inténtalo de nuevo: ";
            cin >> calificacion;
        }

        calificaciones.push_back(calificacion);
    }
}
};

// Función para solicitar los datos del estudiante al usuario
Estudiante obtenerDatosEstudiante(char grupo) {
    Estudiante estudiante;
    estudiante.grupo = grupo;

    cout << "\nGrupo: " << grupo << endl;
    cout << "Nombre del estudiante: ";
    getline(cin >> ws, estudiante.nombre); // Lee toda la línea incluyendo espacios
    cout << "Apellido paterno del estudiante: ";
    cin >> estudiante.apellido_paterno;
    cout << "Apellido materno del estudiante: ";
    cin >> estudiante.apellido_materno;
    cout << "ID del estudiante: ";
    cin >> estudiante.id;
    cout << "Nombre del pariente: ";
    getline(cin >> ws, estudiante.familiar.nombre); // Lee toda la línea incluyendo espacios
    cout << "Apellido paterno del pariente: ";
    cin >> estudiante.familiar.apellido_paterno;
    cout << "Apellido materno del pariente: ";
    cin >> estudiante.familiar.apellido_materno;
    cout << "Vínculo familiar: ";
    getline(cin >> ws, estudiante.familiar.vinculo_familiar);
    cout << "Número de teléfono: ";
    getline(cin >> ws, estudiante.familiar.numero_telefono); // Leer toda la línea, incluidos los espacios

    // Ingresar calificaciones
    estudiante.ingresar_calificaciones();

    return estudiante;
}

int main() {
    Estudiante nuevo_estudiante;

    while(true) {
        cout << "UndaPRO by UdeG" << endl;
        cout << "\t1. Agregar estudiantes" << endl;
        cout << "Seleccione una opcion: ";
        char opcion;
        cin >> opcion;
        system("cls");

        switch(opcion) {
            case '1': // Agregar estudiantes
                cout << "UndaPRO by UdeG" << endl;
                cout << "//Agregar estudiantes" << endl;
                cout << "\nCompleta los siguientes campos para registrar los datos del estudiante en nuestro sistema." << endl;
                cout << "Ingrese el grupo al que pertenece el alumno (A, B, C): ";
                char grupo;
                cin >> grupo;
                grupo = toupper(grupo);
                if (grupo == 'A' || grupo == 'B' || grupo == 'C') {
                    nuevo_estudiante = obtenerDatosEstudiante(grupo);
                    nuevo_estudiante.guardar_datos("Group_" + string(1, grupo) + ".txt");
                    cin.ignore();
                } else {
                    cout << "Grupo inválido. Seleccione una opción correcta." << endl;
                }
                system("cls");
                break;
            default:
                cout << "Opción inválida. Seleccione una opción correcta." << endl;
                break;
        }
    }

    return 0;
}
/********************************************* 
        INTEGRANTES: 
        Eduardo Dominguez Padilla
        Diego Josuan Ornelas Duran
        Gerardo Esqueda Padilla
        Diego Munoz
        chat gpt 3.5

**********************************************/