#include <iostream>
using namespace std;

struct Entry {
    int prefix;
    char c;
};

// Buscar si (prefijo, carácter) ya existe
int findEntry(Entry* dict, int size, int prefix, char c) {
    for (int i = 1; i < size; i++) {
        if (dict[i].prefix == prefix && dict[i].c == c) {
            return i;
        }
    }
    return -1;
}

void compressLZ78(const char* input, Entry* dict, int &dictSize) {
    dictSize = 1; // índice 0 reservado/vacío
    int currentPrefix = 0;

    cout << "Salida (indice, caracter):\n";

    for (int i = 0; input[i] != '\0'; i++) {
        char c = input[i];

        int index = findEntry(dict, dictSize, currentPrefix, c);

        if (index != -1) {
            currentPrefix = index;
        } else {
            cout << "(" << currentPrefix << ", " << c << ")\n";

            dict[dictSize].prefix = currentPrefix;
            dict[dictSize].c = c;
            dictSize++;

            currentPrefix = 0;
        }
    }

    // Para no perder el último fragmento si el texto termina en coincidencia
    if (currentPrefix != 0) {
        cout << "(" << currentPrefix << ")"<<endl;
        dict[dictSize].prefix = currentPrefix;
        dict[dictSize].c = '\0';
        dictSize++;
    }
}

void descompres(Entry* dict, int dictSize, char descom[]) {
    int cunt = 0; // Índice global para llenar descom[]

    for (int i = 1; i < dictSize; i++) {
        char alma[1000];
        int cont = 0;
        int curr = i;
        // Recorremos la cadena de prefijos desde la hoja hasta la raíz
        while (curr != 0) {
            alma[cont] = dict[curr].c;
            cont++;
            curr = dict[curr].prefix;
        }

        // Copiamos al revés para invertir el texto y recuperar el orden original
        for (int e = cont - 1; e >= 0; e--) {
            descom[cunt] = alma[e];
            cunt++;
        }
    }

    descom[cunt] = '\0'; // Marcador de fin de cadena fundamental
}


bool veri(char oring[],char descom[]){
    char *ptr=oring;
    char *ptd=descom;
    while(*ptr!='\0'){
        if(*ptr!=*ptd){
            return false;
        }
        ptr++;
        ptd++;
    }
    return true;
}
