#include <iostream>
#include <string>
#include "librerias.h"
using namespace std;



void encriptacion(char origi[], int n, char k,char encrip[],int longi ) {


    for (int i = 0; i <longi; i++) {
        char caracter = origi[i];

        // Rotación circular de bits a la izquierda
        char rotado = (caracter << n) | ((unsigned char)caracter >> (8 - n));

        // Aplicamos el XOR con la clave
        char tem = rotado ^ k;

        encrip[i] = tem;
    }
    escribir_Archivo(encrip);
}
void desencriptar(char encrip[], int n, char k,char desem[],int longi){

    for (int i = 0; i < longi; i++) {
        unsigned char caracter = encrip[i]^ k;


        // Rotación circular de bits a la izquierda
        char rotado = (caracter >> n) | (caracter << (8 - n));

        // Aplicamos el XOR con la clave

        desem[i] = rotado;
    }
    desem[longi] = '\0';
    escribir_Archivo(desem);

}

bool validarN(int n){
    if (n < 1 || n > 7) {
        return false;
    }
    return true;
}
bool validarK(char k) {
    if ((int)k < -128 || (int)k > 127) {
        return false;
    }
    return true;
}
