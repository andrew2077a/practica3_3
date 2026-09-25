#ifndef LIBRERIAS_H
#define LIBRERIAS_H
#endif // LIBRERIAS_H
void encriptacion(char origi[], int n, char k,char encrip[],int longi);
void desencriptar(char encrip[], int n, char k,char desem[],int longi);
void  leer_arch(char oring[]);
void escribir_Archivo(const char texto[]);
int contar(char cadena[]);
void RLE();
void LZ78();
bool validarN(int n);
bool validarK(char k);
