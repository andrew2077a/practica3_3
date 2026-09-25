#include <iostream>
#include "librerias.h"

using namespace std;

int main(){
    int x;
    while(true){
        cout << "Seleccione una opcion: [1] RLE  |  [2] LZ78  |  [3] Salir " << endl;
        cin >> x;
        cin.ignore();
        switch (x) {
        case 1:
            RLE();
            break;
        case 2:
            LZ78();
            break;
        case 3:
            return 0;
        default:
            cout << "Seleccione otra: " << endl;
        }
    }
}
