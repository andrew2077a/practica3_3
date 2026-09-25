#include <iostream>
#include "librerias.h"
using namespace std;

struct Entry {
    int prefix;
    char c;
};

// Buscar si el par (prefijo, carácter) ya se encuentra en el diccionario
int findEntry(Entry* dict, int size, int prefix, char c) {
    for (int i = 1; i < size; i++) {
        if (dict[i].prefix == prefix && dict[i].c == c) {
            return i;
        }
    }
    return -1;
}

void compressLZ78(const char* input, Entry* dict, int &dictSize, char compri[]) {
    dictSize = 1;
    int currentPrefix = 0;
    int pos = 0;

    // Procesar la cadena caracter por caracter para construir el diccionario y la salida
    for (int i = 0; input[i] != '\0'; i++) {
        char c = input[i];
        int index = findEntry(dict, dictSize, currentPrefix, c);

        if (index != -1) {
            currentPrefix = index;
        }
        else {
            string temp = "(" + to_string(currentPrefix) + "," + c + ")";
            // Guardar la pareja formateada en el arreglo de salida
            for (unsigned int j = 0; j < temp.length(); j++) {
                compri[pos++] = temp[j];
            }

            dict[dictSize].prefix = currentPrefix;
            dict[dictSize].c = c;
            dictSize++;

            currentPrefix = 0;
        }
    }

    // Agregar el ultimo prefijo acumulado si el texto termina en coincidencia
    if (currentPrefix != 0) {
        string temp = "(" + to_string(currentPrefix) + ")";
        for (unsigned int j = 0; j < temp.length(); j++) {
            compri[pos++] = temp[j];
        }
        dict[dictSize].prefix = currentPrefix;
        dict[dictSize].c = '\0';
        dictSize++;
    }

    compri[pos] = '\0';
    escribir_Archivo(compri);
}

void descompres(Entry* dict, int dictSize, char descom[]) {
    int cunt = 0;

    // Reconstruir el texto original recorriendo las ramas del diccionario
    for (int i = 1; i < dictSize; i++) {
        char alma[1000];
        int cont = 0;
        int curr = i;

        // Recorrer la secuencia de prefijos hacia atras hasta la raiz
        while (curr != 0) {
            alma[cont] = dict[curr].c;
            cont++;
            curr = dict[curr].prefix;
        }

        // Invertir el camino recuperado para escribirlo en orden correcto
        for (int e = cont - 1; e >= 0; e--) {
            descom[cunt] = alma[e];
            cunt++;
        }
    }

    descom[cunt] = '\0';
    escribir_Archivo(descom);
}

bool veri(char oring[],char descom[]){
    char *ptr=oring;
    char *ptd=descom;

    // Comparar caracter por caracter para verificar la igualdad exacta
    while(*ptr!='\0'){
        if(*ptr!=*ptd){
            return false;
        }
        ptr++;
        ptd++;
    }
    return true;
}

void LZ78(){
    char oring[10000];
    int n, dictSize = 0;
    char k, compri[10000], encrip[10000], desem[10000], descomprin[10000];
    // Leer el texto original de entrada
    leer_arch(oring);
    int longa = contar(oring);
    Entry* dict= new Entry[longa*2];

    // Comprimir con LZ78 y calcular la longitud del resultado
    compressLZ78(oring, dict, dictSize, compri);
    int longi = contar(compri);

    cout << "Ingrese el n para la rotacion tiene que ser de (1-7)" << endl;
    cin >> n;
    while (!validarN(n)) {
        cout << "Valor invalido. Ingrese n (1-7): ";
        cin >> n;
    }

    cout << "Ingrese la clave: " << endl;
    cin >> k;
    while (!validarK(k)) {
        cout << "Clave invalida. Ingrese la clave nuevamente: ";
        cin >> k;
    }
    cin.ignore();

    // Encriptar la cadena comprimida y marcar el fin de cadena
    encriptacion(compri, n, k, encrip, longi);
    encrip[longi] = '\0';

    // Desencriptar el texto y delimitar el final del buffer
    desencriptar(encrip, n, k, desem, longi);
    desem[longi] = '\0';

    // Reconstruir el texto original usando el diccionario
    descompres(dict, dictSize, descomprin);

    // Validar que el texto descomprimido coincida exactamente con el original
    if(veri(oring, descomprin)){
        cout << "esta igualitooo" << endl;
    }
    delete[] dict;
}
