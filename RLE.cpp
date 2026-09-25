#include <iostream>
#include <string>
#include "librerias.h"
using namespace std;

string rleCompress(const string& input){
    string compri="";
    int contador=1;

    // Contar caracteres consecutivos y formatear la compresion RLE
    for(unsigned int i=0; i<input.length();i++){
        if(i+1<input.length() && input[i]==input[i+1]){
            contador++;
        }
        else{
            if(input[i]>=48&&input[i]<=57){
                compri += to_string(contador);
                compri+="#";
                compri+= input[i];

            }
            else{
                compri += to_string(contador);
                compri += input[i];
            }
            contador=1;
        }
    }
    escribir_Archivo(compri.c_str());
    return compri;

}

string rledescompres(string compri){
    char *ptr=&compri[0];

    string descomprin="",cunt="";

    // Recorrer la cadena comprimida para reconstruir el texto original
    while(*ptr!='\0'){
        if (*ptr>=48&&*ptr<=57){
            cunt+=*ptr;
        }
        else if (*ptr != '#' || (*(ptr + 1) < '0' || *(ptr + 1) > '9')){
            // Repetir el caracter segun la cantidad acumulada
            for(int i =stoi(cunt);i>0;i--){
                descomprin+=*ptr;
            }
            cunt="";
        }
        else{
            // Repetir el digito escapado tras el caracter '#'
            for(int i =stoi(cunt);i>0;i--){
                descomprin+=*(ptr+1);
            }
            cunt="";
            ptr++;
        }
        ptr++;
    }
    escribir_Archivo(descomprin.c_str());
    return descomprin;
}

bool veri( string oring,string descomprin){
    unsigned int num=oring.length();
    if (num!=descomprin.length()){
        return false;
    }

    // Comparar caracter por caracter para validar que ambas cadenas sean iguales
    for(unsigned int i=0;i<num;i++){
        if(oring[i]!=descomprin[i]){
            return false;
        }
    }
    return true;

}

void RLE(){
    char oring[10000];
    int n;
    string descomprin = "";
    char k, encrip[10000], desem[10000];

    // Cargar el texto original desde el archivo
    leer_arch(oring);

    // Comprimir el texto original mediante RLE y obtener su longitud
    string compri = rleCompress(oring);
    int longi = compri.length();

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

    // Encriptar la cadena comprimida y asegurar el fin de cadena
    encriptacion((char*)compri.c_str(), n, k, encrip, longi);
    encrip[longi] = '\0';

    // Desencriptar el texto y cerrar la cadena
    desencriptar(encrip, n, k, desem, longi);
    desem[longi] = '\0';

    // Descomprimir el texto resultante para recuperar el original
    descomprin = rledescompres(desem);

    // Verificar si el texto recuperado coincide exactamente con el original
    if(veri(oring, descomprin)){
        cout<<"esta igualitooo"<<endl<<endl;
    }
}
