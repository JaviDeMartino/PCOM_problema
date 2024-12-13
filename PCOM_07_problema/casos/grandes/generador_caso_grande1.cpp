// JAVIER MARTÍN FUENTES - ANTONINO SASU
// jmarti32@ucm.es - antosasu@ucm.es

//
//  LA RANITA Y LOS NENÚFARES
//  - Generador de casos grandes 1
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <set>
#include <random>
using namespace std;

const int MAX_NUM_NENUFARES = 1e4;
const double MAX_COOR = 1e3;

//Caso en el que tenemos un nodo fragil conectado con la orilla por abajo, depues de ese nodo le siguen 9999 nodos conectados para luego esa
//cadena conectarse con la orilla por arriba.

//LA SOLUCION DEBERIA DAR 10000, ya que el nodo fragil esta con altura 0.02, luego si sumamos 0.1 9999 veces mas llegamos a 999.92 que estara conectado
//con la orilla. Todos los nenufares tienen 1 mosca.

int main() {

    ofstream output("CasoGrande1.txt");

    double N, M;//tamaño del rectangulo con esquina inferior izquierda en el origen
    int numNenufares;
    double L;//distancia de salto de la rana

    //coordenadas del nenufar
    double Xi, Yi; //valores con dos decimales de precision como mucho
    int numMoscas;//numero de moscas del nenufar

    numNenufares = MAX_NUM_NENUFARES;
    N = MAX_COOR;
    M = MAX_COOR;
    L = 0.1;

    if(output.is_open()){
        output << 1 << "\n";
        output << fixed << setprecision(2) << N << " " << M << " " << numNenufares << " " << L << "\n";

        Xi = 500;
        Yi = 0.02;
        numMoscas = 1;

        for(int j = 0; j<numNenufares; j++){

            output << fixed << setprecision(2) << Xi << " " << Yi << " " << numMoscas << "\n";

            Yi += 0.1;
        }

        output << "\n";

        output.close();
    }
    else cout<<"ERROR AL ABRIR FICHERO\n";

    return 0;
}