#include <iostream>
#include <fstream>
#include "librerias.h"

using namespace std;

// Contar manualmente la cantidad de caracteres de una cadena
int contar(char cadena[]){
    char *ptr = cadena;
    int cont = 0;
    while(*ptr != '\0'){
        cont++;
        ptr++;
    }
    return cont;
}

// Abrir el archivo de entrada y validar que exista
ifstream leer_Archivo(string nombre_archivo){
    ifstream fin;
    try {
        fin.open(nombre_archivo);
        if (!fin){
            throw "Error en la lectura del archivo";
        }
        else{
            return fin;
        }
    }
    catch(char const* msg){
        cerr << msg << endl;
    }
    fin.close();
    return fin;
}

// Leer linea por linea del archivo y copiar su contenido al arreglo oring
void lecturalinea(ifstream& instancia, char oring[]){
    string lectura;
    instancia.clear();
    instancia.seekg(0);
    int i = 0;

    while (getline(instancia, lectura)){
        for (size_t j = 0; j < lectura.length(); j++) {
            oring[i] = lectura[j];
            i++;
        }
        oring[i]='\n';
        i++;
    }
    oring[i] = '\0';
}

// Coordinar el flujo completo para abrir, leer y cerrar el archivo fuente
void leer_arch(char oring[]){
    string nombre = "C:/Users/gisel/OneDrive/Escritorio/practi_c++/fina2.0/practica3_3/frases";
    ifstream archivo = leer_Archivo(nombre);
    lecturalinea(archivo, oring);
    archivo.close();
}

// Agregar el texto entregado al final del archivo con un separador visual
void escribir_Archivo(const char texto[]) {
    const char nombre_archivo[] = "C:/Users/gisel/OneDrive/Escritorio/practi_c++/fina2.0/practica3_3/frases";

    try {
        ofstream archivo(nombre_archivo, ios::app);
        if (!archivo.is_open()) {
            throw "Error al abrir el archivo para escritura";
        }
        archivo << "-----------------------------" << endl;
        archivo << texto << endl;
        archivo.close();
    }
    catch(char const* msg){
        cerr << msg << endl;
    }
}
