/*************************Presentacion*************************
        PROGRAMA: Final_Project_PE_24A.cpp
        CENTRO UNIVERSITARIO DE LOS ALTOS / UNIVERSIDAD DE GUADALAJARA
        INGENIERIA EN COMPUTACION / 2DO SEMESTRE
        PROFESOR: Sergio Franco Casillas
        DESCRIPCION: Programa para universidad de prestigio
**************************************************************/
#include <iostream>
#include <fstream>  // Para ofstream
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
            archivo << "------------------------------------------------" << endl;

            // Cierra el archivo
            archivo.close();
            cout << "Los datos se han guardado exitosamente en el archivo " << nombre_archivo;
        } else {
            // Si hay un error al abrir el archivo
            cout << "Error al abrir el archivo " << nombre_archivo << endl;
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
    cout << "Vinculo familiar: ";
    getline(cin >> ws, estudiante.familiar.vinculo_familiar);
    cout << "Numero de telefono: ";
    getline(cin >> ws, estudiante.familiar.numero_telefono); // Leer toda la línea, incluidos los espacios

    return estudiante;
}
/*class Estudiantes {
private:
    // Atributos
    char group;
    string student_name;
    string studentF_name;
    string studentS_name;
    int id_alumno;
    string relative_name;
    string relativeF_name;
    string relativeS_name;
    string family_link;
    string phone_str;

public:
    // Constructor por defecto
    Estudiantes() {}
    // Constructor con parametros
    Estudiantes(char grp, string std_name, string stdF_name, string stdS_name, int id, string rel_name, string relF_name, string relS_name, string fam_link, string phone) {
        group = grp;
        student_name = std_name;
        studentF_name = stdF_name;
        studentS_name = stdS_name;
        id_alumno = id;
        relative_name = rel_name;
        relativeF_name = relF_name;
        relativeS_name = relS_name;
        family_link = fam_link;
        phone_str = phone;
    }

    // Método para guardar los datos en un archivo de texto
    void guardar_datos(string nombre_archivo) {
        ofstream archivo(nombre_archivo, ios::app); // Abre el archivo en modo de adición

        // Verifica si el archivo se abrió correctamente
        if (archivo.is_open()) {
            // Escribe los datos del estudiante en el archivo
            archivo << "\t\t\t  DATOS DEL ESTUDIANTE" << endl;
            archivo << "GRUPO: " << group << endl;
            archivo << "NOMBRE DEL ESTUDIANTE: \t\t" << student_name << " " << studentF_name << " " << studentS_name << endl;
            archivo << "ID DEL ESTUDIANTE: \t\t\t" << id_alumno << endl;
            archivo << "\t\t\tDATOS DE CONTACTO DEL FAMILIAR" << endl;
            archivo << "NOMBRE DEL PARIENTE: \t\t" << relative_name << " " << relativeF_name << " " << relativeS_name << endl;
            archivo << "VINCULO FAMILIAR: \t\t\t" << family_link << endl;
            archivo << "NUMERO DE TELEFONO: \t\t" << phone_str << endl;
            archivo << "------------------------------------------------" << endl;

            // Cierra el archivo
            archivo.close();
            cout << "Los datos se han guardado exitosamente en el archivo " << nombre_archivo;
        } else {
            // Si hay un error al abrir el archivo
            cout << "Error al abrir el archivo " << nombre_archivo << endl;
        }
    }
    // Declaración de función amiga para permitir el acceso a la función obtenerDatosEstudiante()
    friend Estudiantes obtenerDatosEstudiante();
};

// Función para solicitar los datos del estudiante al usuario
Estudiantes obtenerDatosEstudiante(char group) {
    string student_name, studentF_name, studentS_name, relative_name, relativeF_name, relativeS_name, family_link, phone_str;
    int id_alumno;

    cout << "\nGrupo: " << group << endl;
    cout << "Nombre del estudiante: ";
    getline(cin >> ws, student_name); // Lee toda la linea incluyendo espacios
    cout << "Apellido paterno del estudiante: ";
    cin >> studentF_name;
    cout << "Apellido materno del estudiante: ";
    cin >> studentS_name;
    cout << "ID del estudiante: ";
    cin >> id_alumno;
    cout << "Nombre del pariente: ";
    getline(cin >> ws, relative_name); // Lee toda la linea incluyendo espacios
    cout << "Apellido paterno del pariente: ";
    cin >> relativeF_name;
    cout << "Apellido materno del pariente: ";
    cin >> relativeS_name;
    cout << "Vinculo familiar: ";
    getline(cin >> ws, family_link);
    cout << "Numero de telefono: ";
    getline(cin >> ws, phone_str); // Leer toda la línea, incluidos los espacios

    // Crear y retornar un objeto Estudiantes con los datos proporcionados por el usuario
    return Estudiantes(group, student_name, studentF_name, studentS_name, id_alumno, relative_name, relativeF_name, relativeS_name, family_link, phone_str);
}*/
/*//función para comprobar si el estudiante ingresado esta en el archivo
Estudiantes* buscarEstudiantePorNombre(string nombre, Estudiantes* grupo) {
    // Recorre el grupo de estudiantes para buscar el nombre proporcionado
    for (int i = 0; i < sizeof(grupo)/sizeof(grupo[0]); ++i) {
        if (grupo[i].student_name == nombre) {
            return &grupo[i]; // Devuelve el puntero al estudiante encontrado
        }
    }
    return nullptr; // Si no se encuentra el estudiante, devuelve nullptr
}

// Función para modificar un dato del estudiante
void modificarDatoEstudiante(Estudiantes* estudiante) {
    char opcion;
    cout << "\nSeleccione el dato que desea modificar: " << endl;
    cout << "a. Nombre del estudiante" << endl;
    cout << "b. ID del estudiante" << endl;
    cout << "c. Nombre del pariente" << endl;
    cout << "d. Vínculo familiar" << endl;
    cout << "e. Número de teléfono" << endl;
    cout << "Ingrese su opción: ";
    cin >> opcion;

    // Implementa la lógica para modificar el dato seleccionado
    switch(opcion) {
        case 'a':
            cout << "Nuevo nombre del estudiante: ";
            cin >> estudiante->student_name;
            break;
        case 'b':
            cout << "Nuevo ID del estudiante: ";
            cin >> estudiante->id_alumno;
            break;
        case 'c':
            cout << "Nuevo nombre del pariente: ";
            cin >> estudiante->relative_name;
            break;
        case 'd':
            cout << "Nuevo vínculo familiar: ";
            cin >> estudiante->family_link;
            break;
        case 'e':
            cout << "Nuevo número de teléfono: ";
            cin >> estudiante->phone_str;
            break;
        default:
            cout << "Opción inválida." << endl;
    }
}*/

bool ciclo = true;
char op_switch, group_switch;

int main(){

    Estudiante nuevo_estudiante;

/*Estudiantes grupoA;
Estudiantes grupoB;
Estudiantes grupoC;*/

    while(ciclo){
        cout << "UndaPRO by UdeG\t\t\t\t\t\t\tUniversity Professional Data Management" << endl;
        cout << "\t1. Agregar estudiantes" << endl;
        cout << "Seleccione una opcion: ";
        cin >> op_switch;
        system("cls");

        switch(op_switch){
            case '1': // Case 1: Agregar estudiantes
                cout << "UndaPRO by UdeG\t\t\t\t\t\t\tUniversity Professional Data Management" << endl;
                cout << "//Agregar estudiantes" << endl;
                cout << "\nCompleta los siguientes campos para registrar los datos del estudiante en nuestro sistema." << endl;
                cout << "Ingrese el grupo al que pertenece el alumno (A, B, C): ";
                cin >> group_switch;
                if(isalpha(group_switch) && islower(group_switch)){
                    group_switch = toupper(group_switch);
                }
                if(isalpha(group_switch)){  // Validar si es letra
                    switch(group_switch){   //  Switch para ingresar el grupo del estudiante
                        case 'A':
                            // Datos del grupo A de estudiantes
                            nuevo_estudiante = obtenerDatosEstudiante('A');
                            nuevo_estudiante.guardar_datos("Group_A.txt");
                            /*grupoA = obtenerDatosEstudiante('A');*/
                            /*grupoA.guardar_datos("Group_A.txt");*/
                            cin.ignore();
                            break;
                        case 'B':
                            // Datos del grupo B de estudiantes
                            nuevo_estudiante = obtenerDatosEstudiante('B');
                            nuevo_estudiante.guardar_datos("Group_B.txt");
                            /*grupoB = obtenerDatosEstudiante('B');
                            grupoB.guardar_datos("Group_B.txt");*/
                            cin.ignore();
                            break;
                        case 'C':
                            // Datos del grupo C de estudiantes
                            nuevo_estudiante = obtenerDatosEstudiante('B');
                            nuevo_estudiante.guardar_datos("Group_C.txt");
                            /*grupoC = obtenerDatosEstudiante('C');
                            grupoC.guardar_datos("Group_C.txt");*/
                            cin.ignore();
                            break;
                        default:
                            system("cls");
                            cout << "UndaPRO by UdeG\t\t\t\t\t\t\tUniversity Professional Data Management" << endl;
                            cout << "Grupo invalido, seleccione una opcion correcta..." << endl;
                            cout << "Presione enter, para continuar...";
                            cin.ignore();
                            cin.get();
                    }   // Fin switch grupo
                }   // Fin validar si es letra
                system("cls");
                break;  // Fin case 1
                /*case '3': //Case 3 para modificar los datos principales del estudiante...
                cout << "Ingrese el nombre del estudiante: ";
                    string nombre_estudiante;
                    cin >> nombre_estudiante;
                    Estudiantes* estudiante = buscarEstudiantePorNombre(nombre_estudiante, grupo); // Busca el estudiante por nombre
                    if (estudiante != nullptr) {
                        modificarDatoEstudiante(estudiante); // Llama a la función para modificar los datos del estudiante encontrado
                        cout << "Los datos se han modificado correctamente." << endl;
                    } else {
                        cout << "Estudiante no encontrado." << endl;
                    }
                    break; //fin del case 3*/
            default:
                cout << "UndaPRO by UdeG\t\t\t\t\t\t\tUniversity Professional Data Management" << endl;
                cout << "Opcion invalida, seleccione una opcion correcta..." << endl;
                cout << "Presione enter, para continuar...";
                cin.ignore();
                cin.get();
                system("cls");
        }   // Fin switch principal del programa
    }   // Fin ciclo general del programa
    return 0;
}   // Fin main

/*********************************************
        INTEGRANTES:
        Eduardo Dominguez Padilla
        Diego Josuan Ornelas Duran
        Gerardo Esqueda Padilla
        Diego Munoz

**********************************************/
