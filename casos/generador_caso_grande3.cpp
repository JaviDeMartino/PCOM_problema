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

const double MIN_SALTO = 0.01;

// En este vamos a poner la distancia de salto al minimo (0.01). Creamos una fila desde la orilla izquierda de 2000 nenufares conectados
// con distancia 0.01 entre ellos. Luego abajo de cada nenufar de la fila colocamos de forma alternada nenufares a distancia 0.01 y 0.02(estos no 
// están contados en la solucion final). Para ampliar el número de nenufares creamos otra fila igual un poco más abajo.
// El nenufar fragil lo colocamos en la esquina inferior derecha apartado porque no nos interesa
// en este caso.

// Los nenufares de la fila tienen 1 mosca, los que colocamos alternados tienen 3 cada uno. 

// La solucion seria sumar 1 por cada nenufar de la fila (1*2000) y sumar 3 por cada nenufar conectado a esta fila (3*(2000/2)), 
// luego multiplicamos el valor de la suma por las dos filas que tenemos.
// Lo que daria 2*(2000 + 1000*3) = 10000.

int main() {

    ofstream output("CasoGrande3.txt");

    double N, M;//tamaño del rectangulo con esquina inferior izquierda en el origen
    int numNenufares;
    double L;//distancia de salto de la rana

    //coordenadas del nenufar
    double Xi, Yi; //valores con dos decimales de precision como mucho
    int numMoscasFila;//numero de moscas de los nenufares de la fila de 0.01 de dist
    int numMoscasAbajo;//numero de moscas para los que estan justo debajo de los de la fila

    numNenufares = 8001;//2000 de la fila + 2000 de las de abajo correspondientes + 1 fragil apartado
    N = 100;
    M = 100;
    L = 0.01;

    if(output.is_open()){
        output << 1 << "\n";
        output << fixed << setprecision(2) << N << " " << M << " " << numNenufares << " " << L << "\n";

        //Primero colocamos el nenufar fragil abajo a la izquierda del lago apartado del resto a distancia 0.02 de los bordes(no conectado) y
        //con 100 moscas
        output << 99.98 << " "<< 0.02 << " " << 100 << "\n";

        Xi = 0.01;
        Yi = 70;
        numMoscasFila = 1;

        numMoscasAbajo = 3;

        for(int i=0; i<2;i++){

            for(int j = 0; j<2000; j++){

                //mostramos el nenufar de la fila
                output << fixed << setprecision(2) << Xi << " " << Yi << " " << numMoscasFila << "\n";

                //ponemos a distancia 0.02(no conectado) del de arriba
                if(j%2==1){
                    output << fixed << setprecision(2) << Xi << " " << Yi-0.02 << " " << numMoscasAbajo << "\n";
                }
            
                //ponemos a distancia 0.01 (conectado) del de arriba
                else{
                    output << fixed << setprecision(2) << Xi << " " << Yi-0.01 << " " << numMoscasAbajo << "\n";
                }

                Xi += 0.01;

            }

            Xi = 0.01;
            Yi = 50;
        }

        output << "\n";

        output.close();
    }
    else cout<<"ERROR AL ABRIR FICHERO\n";

    return 0;
}