/***********************Presentacion*************************
        PROGRAMA: Final_Project_PE_24A.cpp
        CENTRO UNIVERSITARIO DE LOS ALTOS / UNIVERSIDAD DE GUADALAJARA
        INGENIERIA EN COMPUTACION / 2DO SEMESTRE
        PROFESOR: Sergio Franco Casillas
        DESCRIPCION: Programa para universidad de prestigio
**************************************************************/
#include <iostream>
#include <fstream> // Para ofstream
#include <string>
#include <vector>
#include <cctype>
#include <sstream>
#include <algorithm> // Para transform
#include <limits>
using namespace std;


// Estructura para representar a un familiar
struct Familiar
{
    string nombre;
    string apellido_paterno;
    string apellido_materno;
    string vinculo_familiar;
    string numero_telefono;
};

// Estructura para representar a un estudiante
struct Estudiante
{
    char grupo;
    string nombre;
    string apellido_paterno;
    string apellido_materno;
    int id;
    Familiar familiar;
    vector<double> calificaciones;     // Vector para almacenar calificaciones
    static const int num_materias = 5; // Número de materias
    string materias[num_materias] = {"Espanol", "Calculo", "Historia", "Geografia", "Programacion"};

    // Método para calcular el promedio de las calificaciones
    double calcular_promedio() const
    {
        double suma = 0;
        for (double calificacion : calificaciones)
        {
            suma += calificacion;
        }
        return suma / num_materias;
    }

    // Método para obtener la leyenda del promedio
    string obtener_leyenda_promedio() const
    {
        double promedio = calcular_promedio();
        if (promedio <= 59)
        {
            return "Reprobado";
        }
        else if (promedio >= 60 && promedio <= 79)
        {
            return "Regular";
        }
        else if (promedio >= 80 && promedio <= 89)
        {
            return "Muy bien";
        }
        else // Promedio entre 90 y 100
        {
            return "Excelente";
        }
    }

    // Método para guardar los datos del estudiante en un archivo de texto
    void guardar_datos(string nombre_archivo)
    {
        ofstream archivo(nombre_archivo, ios::app); // Abre el archivo en modo de adición

        // Verifica si el archivo se abrió correctamente
        if (archivo.is_open())
        {
            // Escribe los datos del estudiante en el archivo
            archivo << "\t\t\t  DATOS DEL ESTUDIANTE" << endl;
            archivo << "GRUPO: " << grupo << endl;
            archivo << "NOMBRE DEL ESTUDIANTE: \t\t" << nombre << " " << apellido_paterno << " " << apellido_materno << endl;
            archivo << "ID DEL ESTUDIANTE: \t\t\t" << id << endl;
            archivo << "\t\t\tDATOS DE CONTACTO DEL FAMILIAR" << endl;
            archivo << "NOMBRE DEL PARIENTE: \t\t" << familiar.nombre << " " << familiar.apellido_paterno << " " << familiar.apellido_materno << endl;
            archivo << "VINCULO FAMILIAR: \t\t\t" << familiar.vinculo_familiar << endl;
            archivo << "NUMERO DE TELEFONO: \t\t" << familiar.numero_telefono << endl;
            archivo << "\t\t\tCALIFICACIONES: " << endl;
            for (int i = 0; i < num_materias; ++i)
            {
                string upper_materia = materias[i];
                transform(upper_materia.begin(), upper_materia.end(), upper_materia.begin(), ::toupper);
                if (upper_materia != "PROGRAMACION")
                {
                    archivo << upper_materia << ": \t\t\t\t\t\t" << calificaciones[i] << endl;
                }
                else
                {
                    archivo << upper_materia << ": \t\t\t\t\t\t" << calificaciones[i] << endl;
                }
            }
            archivo << "PROMEDIO DE CALIFICACIONES: \t\t\t\t" << calcular_promedio() << " (" << obtener_leyenda_promedio() << ")" << endl; // Agregar el promedio y la leyenda al archivo
            archivo << "------------------------------------------------" << endl;

            // Cierra el archivo
            archivo.close();
            cout << endl;
            cout << "Los datos se han guardado exitosamente en el archivo " << nombre_archivo << endl;
        }
        else
        {
            // Si hay un error al abrir el archivo
            cout << "Error al abrir el archivo " << nombre_archivo << endl;
        }
    }

    // Método para ingresar las calificaciones de las materias
    void ingresar_calificaciones()
    {
        cout << "Ingrese las calificaciones de las siguientes materias (entre 0 y 100):" << endl;
        calificaciones.clear(); // Limpiar calificaciones anteriores

        for (int i = 0; i < num_materias; ++i)
        {
            double calificacion;
            string entrada;
            cout << materias[i] << ": ";

            // Validar la entrada
            while (true)
            {
                cin >> entrada;
                stringstream ss(entrada);

                // Intentar convertir la entrada a double
                if (ss >> calificacion && !(ss >> entrada) && calificacion >= 0 && calificacion <= 100)
                {
                    break; // Entrada válida
                }
                else
                {
                    cout << "La calificacion debe ser un numero entre 0 y 100. Intentalo de nuevo: ";
                    cin.clear(); // Limpiar el error
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar la entrada inválida
                }
            }

            calificaciones.push_back(calificacion);
        }
    }
};

// Función para cargar los datos de un archivo de texto
void cargar_datos(const string &nombre_archivo, vector<Estudiante> &grupo)
{
    ifstream archivo(nombre_archivo);
    if (archivo.is_open())
    {
        string linea;
        while (getline(archivo, linea))
        {
            if (linea.find("DATOS DEL ESTUDIANTE") != string::npos)
            {
                Estudiante estudiante;
                getline(archivo, linea); // Leer grupo
                estudiante.grupo = linea.back();
                getline(archivo, linea); // Leer nombre completo
                stringstream ss(linea.substr(linea.find(":") + 1));
                ss >> estudiante.nombre >> estudiante.apellido_paterno >> estudiante.apellido_materno;
                getline(archivo, linea); // Leer ID
                estudiante.id = stoi(linea.substr(linea.find(":") + 1));
                getline(archivo, linea); // Leer encabezado de datos de contacto del familiar
                getline(archivo, linea); // Leer nombre completo del familiar
                stringstream ss_familiar(linea.substr(linea.find(":") + 1));
                ss_familiar >> estudiante.familiar.nombre >> estudiante.familiar.apellido_paterno >> estudiante.familiar.apellido_materno;
                getline(archivo, linea); // Leer vínculo familiar
                estudiante.familiar.vinculo_familiar = linea.substr(linea.find(":") + 1);
                getline(archivo, linea); // Leer número de teléfono
                estudiante.familiar.numero_telefono = linea.substr(linea.find(":") + 1);
                getline(archivo, linea); // Leer encabezado de calificaciones
                estudiante.calificaciones.clear();
                for (int i = 0; i < Estudiante::num_materias; ++i)
                {
                    getline(archivo, linea);
                    estudiante.calificaciones.push_back(stod(linea.substr(linea.find(":") + 1)));
                }
                getline(archivo, linea); // Leer línea de separación
                if (!archivo.fail())
                {
                    grupo.push_back(estudiante);
                }
            }
        }
        archivo.close();
    }
}
// Funcion para validar ID
bool validarID(const string &id_str)
{
    // Verificar que la longitud sea 5
    if (id_str.length() != 5)
    {
        return false;
    }

    // Verificar que todos los caracteres sean dígitos
    for (char c : id_str)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }
    return true;
}
// Función para eliminar espacios en blanco de una cadena
string eliminarEspacios(const string &str) {
    string resultado;
    for (char ch : str) {
        if (!isspace(ch)) {
            resultado += ch;
        }
    }
    return resultado;
}
// Funcion para validar telefono
bool validarTel(const string &tel)
{
    string telSinEspacios = eliminarEspacios(tel);
    // Verificar que la longitud sea 5
    if (telSinEspacios.length() != 10)
    {
        return false;
    }

    // Verificar que todos los caracteres sean dígitos
    for (char ch : telSinEspacios)
    {
        if (!isdigit(ch))
        {
            return false;
        }
    }
    return true;
}
// Funcion para validar que la entrada sea solo una letra
bool validarEntradaGrupo(char group_switch) {
    if (cin.peek() != '\n') {
        cout << "\nSolo se puede ingresar un caracter." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada
        return false;
    }
    return true;
}
// Función para validar si un ID ya existe en un vector de estudiantes
bool idExiste(string id, const vector<Estudiante> &grupo)
{
     if(validarID(id)){
        for (const auto &estudiante : grupo)
        {
            if (estudiante.id == stoi(id))
            {
                return true; // El ID existe en el vector
            }
        }
    }
    return false; // El ID no existe en el vector
}
// Funcion para solicitar los datos del estudiante al usuario
Estudiante obtenerDatosEstudiante(char grupo)
{   
    Estudiante estudiante;
    estudiante.grupo = grupo;
    // Declarar y definir las variables de los grupos
    vector<Estudiante> grupoA, grupoB, grupoC;

    // Cargar los datos desde los archivos
    cargar_datos("Group_A.txt", grupoA);
    cargar_datos("Group_B.txt", grupoB);
    cargar_datos("Group_C.txt", grupoC);

    cout << "\nGrupo: " << grupo << endl
         << endl;
    cout << "Nombre del estudiante: ";
    getline(cin >> ws, estudiante.nombre); // Lee toda la línea incluyendo espacios
    cout << "Apellido paterno del estudiante: ";
    cin >> estudiante.apellido_paterno;
    cout << "Apellido materno del estudiante: ";
    cin >> estudiante.apellido_materno;
    string id_input;
    cout << "ID del estudiante (5 DIGITOS): ";
    cin >> id_input;
    // Validar que el ID no haya sido previamente ingresado
    while ((idExiste(id_input, grupoA) || idExiste(id_input, grupoB) || idExiste(id_input, grupoC)) && validarID(id_input))
    {
        cout << "El ID ingresado ya ha sido utilizado. Ingrese otro ID: ";
        cin >> id_input;
    }
    while (!validarID(id_input)) {  // Validar que sean 5 digitos y sean numeros
        cout << "ID invalido. Debe ser un numero de 5 digitos. Intentalo de nuevo: ";
        cin >> id_input;
    }
    estudiante.id = stoi(id_input);
    cout << endl;
    cout << "Ingrese los datos de contacto del pariente." << endl;
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
    while (!validarTel(estudiante.familiar.numero_telefono)) {  // Validar que sean 5 digitos y sean numeros
        cout << "Numero de telefono invalido. Debe ser un numero de 10 digitos. Intentalo de nuevo: ";
        getline(cin >> ws, estudiante.familiar.numero_telefono); // Leer toda la línea, incluidos los espacios
    }
    cout << endl;

    // Ingresar calificaciones
    estudiante.ingresar_calificaciones();

    return estudiante;
}
// Función para comprobar si el estudiante ingresado está en el archivo
Estudiante *buscarEstudiantePorId(int id, vector<Estudiante> &grupo)
{
    for (auto &estudiante : grupo)
    {
        if (estudiante.id == id)
        {
            return &estudiante;
        }
    }
    return nullptr;
}
bool validarEntradaChar(char &opcion)
{ // Leer la entrada del caracter
    cin >> opcion;
    // Verificar si se ingresó un solo caracter
    if (cin.peek() != '\n' || !isupper(opcion) && !islower(opcion))
    {
        system("cls");
        cout << "UndaPRO by UdeG\t\t\t\t\t\t\tUniversity Professional Data Management" << endl;
        cout << "\nERROR. Solo se puede ingresar un caracter." << endl;
        cout << "Presione enter para continuar...";

        // Limpiar el búfer de entrada
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        system("cls");
        return false;
    }
    // Si se ingresó un caracter válido, devolver true
    return true;
}
bool validarId(const string &id_str)
{
    // Verificar que la longitud sea 5
    if (id_str.length() != 5)
    {
        return false;
    }
    // Verificar que todos los caracteres sean dígitos
    for (char c : id_str)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }
    return true;
}

void modificarDatoEstudiante(Estudiante *estudiante)
{
    char opcion;
    do
    {

        cout << "UndaPRO by UdeG\t\t\t\t\t\t\tUniversity Professional Data Management" << endl;
        cout << "\nSeleccione el dato que desea modificar: " << endl;
        cout << "a. Nombre del estudiante" << endl;
        cout << "b. Apellido paterno del estudiante" << endl;
        cout << "c. Apellido materno del estudiante" << endl;
        cout << "d. ID del estudiante" << endl;
        cout << "e. Nombre del pariente" << endl;
        cout << "f. Apellido paterno del pariente" << endl;
        cout << "g. Apellido materno del pariente" << endl;
        cout << "h. Vinculo familiar" << endl;
        cout << "i. Numero de telefono" << endl;
        cout << "j. Calificaciones" << endl;
        cout << "Ingrese su opcion: ";
    } while (!validarEntradaChar(opcion));
    opcion = tolower(opcion); // Convertir la opción a minúscula

    cin.ignore();
    system("cls");
    switch (opcion)
    {
    case 'a':
        cout << "UndaPRO by UdeG\t\t\t\t\t\t\tUniversity Professional Data Management○\n"
             << endl;
        cout << "Nuevo nombre del estudiante: ";
        getline(cin, estudiante->nombre);
        break;
    case 'b':
        cout << "UndaPRO by UdeG\t\t\t\t\t\t\tUniversity Professional Data Management○\n"
             << endl;
        cout << "Nuevo apellido paterno del estudiante: ";
        getline(cin, estudiante->apellido_paterno);
        break;
    case 'c':
        cout << "UndaPRO by UdeG\t\t\t\t\t\t\tUniversity Professional Data Management○\n"
             << endl;
        cout << "Nuevo apellido materno del estudiante: ";
        getline(cin, estudiante->apellido_materno);
        break;
    case 'd':
    {
        cout << "UndaPRO by UdeG\t\t\t\t\t\t\tUniversity Professional Data Management○\n"
             << endl;
        cout << "Nuevo ID del estudiante: ";
        string input_id;
        getline(cin >> ws, input_id);
        if (validarId(input_id))
        {
            estudiante->id = stoi(input_id);
        }
        else
        {
            cout << "ID invalido. Ingrese un numero." << endl;
            cout << "Presione enter para continuar...";
            cin.get();
            system("cls");
            return;
        }
        break;
    }
    case 'e':
        cout << "UndaPRO by UdeG\t\t\t\t\t\t\tUniversity Professional Data Management○\n"
             << endl;
        cout << "Nuevo nombre del pariente: ";
        getline(cin, estudiante->familiar.nombre);
        break;
    case 'f':
        cout << "UndaPRO by UdeG\t\t\t\t\t\t\tUniversity Professional Data Management○\n"
             << endl;
        cout << "Nuevo apellido paterno del pariente: ";
        getline(cin, estudiante->familiar.apellido_paterno);
        break;
    case 'g':
        cout << "UndaPRO by UdeG\t\t\t\t\t\t\tUniversity Professional Data Management○\n"
             << endl;
        cout << "Nuevo apellido materno del pariente: ";
        getline(cin, estudiante->familiar.apellido_materno);
        break;
    case 'h':
        cout << "UndaPRO by UdeG\t\t\t\t\t\t\tUniversity Professional Data Management○\n"
             << endl;
        cout << "Nuevo vinculo familiar: ";
        getline(cin, estudiante->familiar.vinculo_familiar);
        break;
    case 'i':
        cout << "UndaPRO by UdeG\t\t\t\t\t\t\tUniversity Professional Data Management○\n"
             << endl;
        cout << "Nuevo numero de telefono: ";
        getline(cin, estudiante->familiar.numero_telefono);
        break;
    case 'j':
        estudiante->ingresar_calificaciones();
        break;
    default:
        cout << "UndaPRO by UdeG\t\t\t\t\t\t\tUniversity Professional Data Management○\n"
             << endl;
        cout << "Opcion invalida." << endl;
        cout << "Presione enter para continuar...";
        cin.get();
        system("cls");
        break;
    }
}
//Función para actualizar los datos de un estudiante
void actualizarArchivo(const string &nombre_archivo, const vector<Estudiante> &grupo)
{
    ofstream archivo(nombre_archivo);
    if (archivo.is_open())
    {
        for (const auto &estudiante : grupo)
        {
            // Escribe los datos del estudiante en el archivo
            archivo << "\t\t\t  DATOS DEL ESTUDIANTE" << endl;
            archivo << "GRUPO: " << estudiante.grupo << endl;
            archivo << "NOMBRE DEL ESTUDIANTE: \t\t" << estudiante.nombre << " " << estudiante.apellido_paterno << " " << estudiante.apellido_materno << endl;
            archivo << "ID DEL ESTUDIANTE: \t\t\t" << estudiante.id << endl;
            archivo << "\t\t\tDATOS DE CONTACTO DEL FAMILIAR" << endl;
            archivo << "NOMBRE DEL PARIENTE: \t\t" << estudiante.familiar.nombre << " " << estudiante.familiar.apellido_paterno << " " << estudiante.familiar.apellido_materno << endl;
            archivo << "VINCULO FAMILIAR: \t\t\t" << estudiante.familiar.vinculo_familiar << endl;
            archivo << "NUMERO DE TELEFONO: \t\t" << estudiante.familiar.numero_telefono << endl;
            archivo << "\t\t\tCALIFICACIONES: " << endl;
            for (int i = 0; i < Estudiante::num_materias; ++i)
            {
                string upper_materia = estudiante.materias[i];
                transform(upper_materia.begin(), upper_materia.end(), upper_materia.begin(), ::toupper);
                if (upper_materia != "PROGRAMACION")
                {
                    archivo << upper_materia << ": \t\t\t\t\t\t" << estudiante.calificaciones[i] << endl;
                }
                else
                {
                    archivo << upper_materia << ": \t\t\t\t\t\t" << estudiante.calificaciones[i] << endl;
                }
            }
            archivo << "PROMEDIO DE CALIFICACIONES: \t\t\t\t" << estudiante.calcular_promedio() << " (" << estudiante.obtener_leyenda_promedio() << ")" << endl; // Agregar el promedio y la leyenda al archivo
            archivo << "------------------------------------------------" << endl;
        }
        archivo.close();
        cout << "Los datos se han actualizado exitosamente en el archivo " << nombre_archivo << endl;
    }
    else
    {
        cout << "Error al abrir el archivo " << nombre_archivo << endl;
    }
}

//Función para limpiar la base de datos con los datos de los estudiantes
void vaciardatos(vector<Estudiante> &grupo, const string &nombreArchivo)
{
    // Vaciar el vector
    grupo.clear();

    // Abrir el archivo en modo truncado para eliminar los datos
    ofstream archivo(nombreArchivo, ios::trunc);
    if (archivo.is_open())
    {
        archivo.close();
        cout << "\nSe han eliminado los datos del archivo " << nombreArchivo << endl;
    }
    else
    {
        cout << "Error al abrir el archivo " << nombreArchivo << " para eliminar los datos." << endl;
    }
}

//Función para imprimir y mostrar los datos del estudiante registrado
void mostrarDetalles(const vector<Estudiante>& grupoA, const vector<Estudiante>& grupoB, const vector<Estudiante>& grupoC) {
    char opcion;
    cout << "Seleccione una opcion para mostrar detalles:" << endl;
    cout << "a. Mostrar detalles de un estudiante por ID" << endl;
    cout << "b. Mostrar todos los estudiantes de un grupo" << endl;
    cout << "c. Mostrar calificaciones de una materia para todos los estudiantes" << endl;
    cout << "d. Mostrar todos los estudiantes registrados en todos los grupos" << endl;
    cout << "Ingrese su opcion: ";
    if (validarEntradaChar(opcion))
    {
    opcion = tolower(opcion); // Convertir la opción a minúscula

    cin.ignore(); // Limpiar el buffer de entrada

    switch (opcion) {
        case 'a': {
            string input;
            int id;
            string id_input;
            bool valido = false;

            while (!valido) {
                cout << "Ingrese el ID del estudiante que desea ver: ";
                //cin >> input;
                cin >> id_input;

                while(!validarID(id_input)){
                    cout << "ID invalido. Por favor, ingrese un numero: ";
                    cin >> id_input;
                }

                input = id_input;

                valido = all_of(input.begin(), input.end(), ::isdigit);
                if (valido) {
                    id = stoi(input);
                } else {
                    cout << "ID invalido. Por favor, ingrese un numero." << endl;
                }
            }

            const Estudiante* estudiante = nullptr;
            char grupo;

            for (const auto& est : grupoA) {
                if (est.id == id) {
                    estudiante = &est;
                    grupo = 'A';
                    break;
                }
            }

            if (!estudiante) {
                for (const auto& est : grupoB) {
                    if (est.id == id) {
                        estudiante = &est;
                        grupo = 'B';
                        break;
                    }
                }
            }

            if (!estudiante) {
                for (const auto& est : grupoC) {
                    if (est.id == id) {
                        estudiante = &est;
                        grupo = 'C';
                        break;
                    }
                }
            }

            if (estudiante) {
                cout << "\n\t\t\t  DATOS DEL ESTUDIANTE\n";
                cout << "GRUPO: " << grupo << endl;
                cout << "NOMBRE DEL ESTUDIANTE: \t\t" << estudiante->nombre << " " << estudiante->apellido_paterno << " " << estudiante->apellido_materno << endl;
                cout << "ID DEL ESTUDIANTE: \t\t\t" << estudiante->id << endl;
                cout << "\n\t\t\tDATOS DE CONTACTO DEL FAMILIAR\n";
                cout << "NOMBRE DEL PARIENTE: \t\t" << estudiante->familiar.nombre << " " << estudiante->familiar.apellido_paterno << " " << estudiante->familiar.apellido_materno << endl;
                cout << "VINCULO FAMILIAR: \t\t\t" << estudiante->familiar.vinculo_familiar << endl;
                cout << "NUMERO DE TELEFONO: \t\t" << estudiante->familiar.numero_telefono << endl;
                cout << "\n\t\t\tCALIFICACIONES\n";
                for (int i = 0; i < Estudiante::num_materias; ++i) {
                    cout << estudiante->materias[i] << ": \t\t" << estudiante->calificaciones[i] << endl;
                }
                cout << "PROMEDIO DE CALIFICACIONES: \t" << estudiante->calcular_promedio() << " (" << estudiante->obtener_leyenda_promedio() << ")" << endl;
            } else {
                cout << "Estudiante con ID " << id << " no encontrado." << endl;
            }
            break;
        }
        case 'b': {
            char grupo;
            cout << "Ingrese el grupo que desea ver (A, B, C): ";
            cin >> grupo;
            grupo = toupper(grupo); // Convertir el grupo a mayúscula

            const vector<Estudiante>* grupo_estudiantes = nullptr;
            switch (grupo) {
                case 'A':
                    grupo_estudiantes = &grupoA;
                    break;
                case 'B':
                    grupo_estudiantes = &grupoB;
                    break;
                case 'C':
                    grupo_estudiantes = &grupoC;
                    break;
                default:
                    cout << "Grupo invalido." << endl;
                    return;
            }

            if (grupo_estudiantes) {
                cout << "\n\t\t\t  DATOS DEL GRUPO " << grupo << "\n";
                for (const auto& estudiante : *grupo_estudiantes) {
                    cout << "NOMBRE DEL ESTUDIANTE: \t\t" << estudiante.nombre << " " << estudiante.apellido_paterno << " " << estudiante.apellido_materno << endl;
                    cout << "ID DEL ESTUDIANTE: \t\t\t" << estudiante.id << endl;
                    cout << "\n";
                }
            }
            break;
        }
        case 'c': {
            cout << "Seleccione la materia para ver las calificaciones:" << endl;
            for (int i = 0; i < Estudiante::num_materias; ++i) {
                cout << i + 1 << ". " << Estudiante().materias[i] << endl;
            }
            int materia_index;
            cout << "Ingrese el numero de la materia: ";
            cin >> materia_index;

            if (materia_index < 1 || materia_index > Estudiante::num_materias) {
                cout << "Materia invalida." << endl;
                return;
            }

            materia_index -= 1; // Convertir a índice de array

            cout << "\n\t\t\tCALIFICACIONES DE " << Estudiante().materias[materia_index] << "\n";

            auto mostrarCalificaciones = [&](const vector<Estudiante>& grupo) {
                for (const auto& estudiante : grupo) {
                    cout << "NOMBRE DEL ESTUDIANTE: \t\t" << estudiante.nombre << " " << estudiante.apellido_paterno << " " << estudiante.apellido_materno << endl;
                    cout << "CALIFICACION: \t\t\t" << estudiante.calificaciones[materia_index] << endl;
                    cout << "\n";
                }
            };

            cout << "\nGrupo A:\n";
            mostrarCalificaciones(grupoA);
            cout << "\nGrupo B:\n";
            mostrarCalificaciones(grupoB);
            cout << "\nGrupo C:\n";
            mostrarCalificaciones(grupoC);
            break;
        }
        case 'd': {
            auto mostrarGrupo = [&](const vector<Estudiante>& grupo, char grupo_nombre) {
                cout << "\n\t\t\t  DATOS DEL GRUPO " << grupo_nombre << "\n";
                for (const auto& estudiante : grupo) {
                    cout << "NOMBRE DEL ESTUDIANTE: \t\t" << estudiante.nombre << " " << estudiante.apellido_paterno << " " << estudiante.apellido_materno << endl;
                    cout << "ID DEL ESTUDIANTE: \t\t\t" << estudiante.id << endl;
                    cout << "NOMBRE DEL PARIENTE: \t\t" << estudiante.familiar.nombre << " " << estudiante.familiar.apellido_paterno << " " << estudiante.familiar.apellido_materno << endl;
                    cout << "VINCULO FAMILIAR: \t\t\t" << estudiante.familiar.vinculo_familiar << endl;
                    cout << "NUMERO DE TELEFONO: \t\t" << estudiante.familiar.numero_telefono << endl;
                    cout << "\n";
                }
            };

            mostrarGrupo(grupoA, 'A');
            mostrarGrupo(grupoB, 'B');
            mostrarGrupo(grupoC, 'C');
            break;
        }
        default:
            cout << "Opcion invalida." << endl;
    }
    }
}
void eliminarEstudiantePorId(int id, vector<Estudiante> &grupo, const string &filename)
{
    auto it = remove_if(grupo.begin(), grupo.end(), [id](const Estudiante &estudiante)
                        { return estudiante.id == id; });
    if (it != grupo.end())
    {
        grupo.erase(it, grupo.end());
        actualizarArchivo(filename, grupo);
        cout << "Estudiante eliminado correctamente." << endl;
        cout<<"Presione enter para continuar...";
        cin.ignore();
        cin.get();
        system("cls");
    }
    else
    {
        cout << "Estudiante no encontrado." << endl;
    }
}

int main()
{
    vector<Estudiante> grupoA, grupoB, grupoC;
        bool ciclo = true;
        char group_switch;
    // Cargar datos desde los archivos
    cargar_datos("Group_A.txt", grupoA);
    cargar_datos("Group_B.txt", grupoB);
    cargar_datos("Group_C.txt", grupoC);

    while (ciclo)
    {
        cout << "UndaPRO by UdeG\t\t\t\t\t\t\tUniversity Professional Data Management" << endl;
        cout << "\t1. Agregar estudiantes" << endl;
        cout << "\t2. Buscar datos de estudiantes" << endl;
        cout << "\t3. Modificar datos de estudiantes" << endl;
        cout << "\t4. Eliminar datos de estudiantes" << endl;
        cout << "\t5. Vaciar bases de datos" << endl;
        cout << "\t6. Salir" << endl;
        cout << "Seleccione una opcion: ";
       string op_switch_input;
        cin >> op_switch_input;
        if (op_switch_input.length() != 1 || !isdigit(op_switch_input[0]))
        {
            cout << "Opcion invalida, seleccione una opcion correcta..." << endl;
            cout << "Presione enter, para continuar...";
            cin.ignore();
            cin.get();
            system("cls");
            continue;
        }

        char op_switch = op_switch_input[0];
        system("cls");
        switch (op_switch)
        {
        case '1': // Case 1: Agregar estudiantes
            cout << "UndaPRO by UdeG\t\t\t\t\t\t\tUniversity Professional Data Management" << endl;
            cout << "//Agregar estudiantes" << endl;
            cout << "\nCompleta los siguientes campos para registrar los datos del estudiante en nuestro sistema." << endl;
            cout << "Ingrese el grupo al que pertenece el alumno (A, B, C): ";
            cin >> group_switch;
            while(!validarEntradaGrupo(group_switch)){
                cout << "Grupo incorrecto, ingrese solo un caracter: ";
                cin >> group_switch;
            }
            if (isalpha(group_switch) && islower(group_switch) && validarEntradaGrupo(group_switch))
            {
                group_switch = toupper(group_switch);
            }
            if (isalpha(group_switch) && validarEntradaGrupo(group_switch))
            { // Validar si es letra
                Estudiante nuevo_estudiante;
                switch (group_switch)
                { //  Switch para ingresar el grupo del estudiante
                case 'A':
                    nuevo_estudiante = obtenerDatosEstudiante('A');
                    nuevo_estudiante.guardar_datos("Group_A.txt");
                    grupoA.push_back(nuevo_estudiante);
                    break;
                case 'B':
                    nuevo_estudiante = obtenerDatosEstudiante('B');
                    nuevo_estudiante.guardar_datos("Group_B.txt");
                    grupoB.push_back(nuevo_estudiante);
                    break;
                case 'C':
                    nuevo_estudiante = obtenerDatosEstudiante('C');
                    nuevo_estudiante.guardar_datos("Group_C.txt");
                    grupoC.push_back(nuevo_estudiante);
                    break;
                default:
                    cout << "Grupo invalido, seleccione una opcion correcta..." << endl;
                    cout << "Presione enter, para continuar...";
                    cin.get();
                    break;
                } // Fin switch grupo
            } // Fin validar si es letra
            system("cls");
            break; // Fin case 1

            case '2':
                mostrarDetalles(grupoA, grupoB, grupoC);
                cout << "Presione enter para continuar: " << endl;
                cin.ignore();
                cin.get();
                system("cls");
                break;

            case '3':
        { // Modificar datos de estudiantes
            char opcion;
            cout << "UndaPRO by UdeG\t\t\t\t\t\t\tUniversity Professional Data Management" << endl;
            cout << "\nIngrese el ID del estudiante: ";
            string input_id;
            getline(cin >> ws, input_id);
            system("cls");
            // Verificar si todos los caracteres son dígitos y si la longitud es 5
            if (validarId(input_id))
            {
                int id_estudiante = stoi(input_id); // Convertir el input a entero
                Estudiante *estudiante = nullptr;
                cout << "UndaPRO by UdeG\t\t\t\t\t\t\tUniversity Professional Data Management" << endl;
                cout << "\nIngrese el grupo del estudiante (A, B, C): ";

                if (validarEntradaChar(group_switch))
                {
                    system("cls");
                    if (isalpha(group_switch) && islower(group_switch))
                    {
                        group_switch = toupper(group_switch);
                    }

                    if (isalpha(group_switch))
                    {
                        switch (group_switch)
                        {
                        case 'A':
                            estudiante = buscarEstudiantePorId(id_estudiante, grupoA);
                            break;
                        case 'B':
                            estudiante = buscarEstudiantePorId(id_estudiante, grupoB);
                            break;
                        case 'C':
                            estudiante = buscarEstudiantePorId(id_estudiante, grupoC);
                            break;
                        default:
                            cout << "UndaPRO by UdeG\t\t\t\t\t\t\tUniversity Professional Data Management" << endl;
                            cout << "\nGrupo invalido, seleccione una opcion correcta..." << endl;
                            cout << "Presione enter, para continuar...";
                            cin.get();
                            system("cls");
                            break;
                        }
                    }
                }

                if (estudiante != nullptr)
                {
                    modificarDatoEstudiante(estudiante);
                    if (group_switch == 'A')
                    {
                        actualizarArchivo("Group_A.txt", grupoA);
                    }
                    else if (group_switch == 'B')
                    {
                        actualizarArchivo("Group_B.txt", grupoB);
                    }
                    else if (group_switch == 'C')
                    {
                        actualizarArchivo("Group_C.txt", grupoC);
                    }
                    cout << "UndaPRO by UdeG\t\t\t\t\t\t\tUniversity Professional Data Management" << endl;
                    cout << "\nLos datos se han modificado correctamente." << endl;
                    cout << "Presione enter, para continuar...";
                    cin.get();
                    system("cls");
                }
                else
                {
                    cout << "UndaPRO by UdeG\t\t\t\t\t\t\tUniversity Professional Data Management" << endl;
                    cout << "\nEstudiante no encontrado." << endl;
                    cout << "Presione enter, para continuar...";
                    cin.ignore();
                    cin.get();

                    system("cls");
                }
            }
            else
            {
                cout << "UndaPRO by UdeG\t\t\t\t\t\t\tUniversity Professional Data Management" << endl;
                cout << "\nID invalido. Ingrese un numero de 5 digitos.\n";
                cout << "Presione enter, para continuar...";
                cin.get();
                system("cls");
            }
            system("cls"); // Limpiar la pantalla

            break;
        }
                case '4':
        {
            cout << "UndaPRO by UdeG\t\t\t\t\t\t\tUniversity Professional Data Management" << endl;
            cout << "\nIngrese el ID del estudiante a eliminar: ";
            string input_id;
            getline(cin >> ws, input_id);
            system("cls");
            if (validarId(input_id))
            {
                int id_estudiante = stoi(input_id);
                cout << "UndaPRO by UdeG\t\t\t\t\t\t\tUniversity Professional Data Management" << endl;
                cout << "\nIngrese el grupo del estudiante (A, B, C): ";
                if (validarEntradaChar(group_switch))
                {
                    system("cls");
                    if (isalpha(group_switch) && islower(group_switch))
                    {
                        group_switch = toupper(group_switch);
                    }

                    if (isalpha(group_switch))
                    {
                        switch (group_switch)
                        {
                        case 'A':
                            eliminarEstudiantePorId(id_estudiante, grupoA, "Group_A.txt");
                            break;
                        case 'B':
                            eliminarEstudiantePorId(id_estudiante, grupoB, "Group_B.txt");
                            break;
                        case 'C':
                            eliminarEstudiantePorId(id_estudiante, grupoC, "Group_C.txt");
                            break;
                        default:
                            cout << "UndaPRO by UdeG\t\t\t\t\t\t\tUniversity Professional Data Management" << endl;
                            cout << "\nGrupo invalido, seleccione una opcion correcta..." << endl;
                            cout << "Presione enter, para continuar...";
                            cin.get();
                            break;
                        }
                    }
                }
            }
            else
            {
                cout << "UndaPRO by UdeG\t\t\t\t\t\t\tUniversity Professional Data Management" << endl;
                cout << "\nID invalido. Ingrese un numero de 5 digitos.\n";
                cout << "Presione enter, para continuar...";
                cin.get();
                system("cls");
            }
            break;
        }
        case '5':
            char opceliminar;
            cout << "UndaPRO by UdeG\t\t\t\t\t\t\tUniversity Professional Data Management\n" << endl;
            cout << "Seleccione el grupo que sea eliminar (A, B, C): ";
            if (validarEntradaChar(opceliminar))
            {
                if (isalpha(opceliminar) && islower(opceliminar))
                {
                    opceliminar = toupper(opceliminar);
                }
                if (isalpha(opceliminar))
                {
                    switch (opceliminar)
                    {
                    case 'A':
                        vaciardatos(grupoA, "Group_A.txt");
                        cout << "Presione enter, para continuar...";
                        cin.ignore();
                        cin.get();
                        system("cls");
                        break;
                    case 'B':
                        vaciardatos(grupoB, "Group_B.txt");
                        cout << "Presione enter, para continuar...";
                        cin.ignore();
                        cin.get();
                        system("cls");
                        break;
                    case 'C':
                        vaciardatos(grupoC, "Group_C.txt");
                        cout << "Presione enter, para continuar...";
                        cin.ignore();
                        cin.get();
                        system("cls");
                        break;
                    default:
                        cout << "\nGrupo invalido, seleccione una opcion correcta..." << endl;
                        cout << "Presione enter, para continuar...";
                        cin.get();
                        break;
                    }
                }
            }
            break;
        case '6': // Case 5: Salir
            ciclo = false;
            break; // Fin case 5

        default:
            cout << "UndaPRO by UdeG\t\t\t\t\t\t\tUniversity Professional Data Management" << endl;
            cout << "Opcion invalida, seleccione una opcion correcta..." << endl;
            cout << "Presione enter, para continuar...";
            cin.ignore();
            cin.get();
            system("cls");
        } // Fin switch principal del programa
    } // Fin ciclo general del programa
    return 0;
} // Fin main

/*********************************************
        INTEGRANTES:
        Eduardo Dominguez Padilla
        Diego Josuan Ornelas Duran
        Gerardo Esqueda Padilla
        Diego Munoz Cisneros
        chat gpt 3.5
**********************************************/
