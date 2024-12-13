// JAVIER MARTÍN FUENTES - ANTONINO SASU
// jmarti32@ucm.es - antosasu@ucm.es

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

// Lo mismo que el GeneradorCasoGrande1, solo que en este el nodo fragil esta arriba y la cadena se vuelve a conectar a la orilla por abajo.
// Esto se hace por si un algoritmo que se veria perjudicado por pasar primero por un nodo fragil consigue ir primero en el otro
// caso (el que empieza con el fragil por abajo) por el nodo no fragil. Asi nos aseguramos que al menos en uno de los dos pase primero por 
// el no fragil

//LA SOLUCION DEBERIA DAR 10000, ya que el nodo fragil esta con altura 999.92, luego si sumamos 0.1 9999 veces mas llegamos a 0.02 que estara conectado
//con la orilla. Todos los nenufares tienen 1 mosca.

int main() {

    ofstream output("CasoGrande1.1.txt");

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
        Yi = 999.92;
        numMoscas = 1;

        for(int j = 0; j<numNenufares; j++){

            output << fixed << setprecision(2) << Xi << " " << Yi << " " << numMoscas << "\n";

            Yi -= 0.1;
        }

        output << "\n";

        output.close();
    }
    else cout<<"ERROR AL ABRIR FICHERO\n";


    return 0;
}