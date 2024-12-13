// JAVIER MARTÍN FUENTES - ANTONINO SASU
// jmarti32@ucm.es - antosasu@ucm.es

//
//  LA RANITA Y LOS NENÚFARES
//  - Generador de casos grandes 2
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

// En este caso vamos a poner una longitud de salto mayor al necesario para curzar el lago entero de un solo salto, por lo que todos los nenufares
// estaran conectados todos con todos. A cada nenufar le asignaremos 3 moscas y colocaremos 1e4 nenufares por todos el lago, por lo que solucion
// deberia ser 3*10000 = 30000 moscas. Con este caso se podra distinguir facilmente con el tiempos el algoritmo que emplea ufds con los que usan 
// max-flow, dfs, bfs o fuerza bruta. El ufds suele tadar 3 veces menos que el dfs y bfs. Al estar conectados todos con todos, el nenufar fragil no crea ningun problema y todos los nenufares son accesibles.


int main() {

    ofstream output("CasoGrande2.txt");

    double N, M;//tamaño del rectangulo con esquina inferior izquierda en el origen
    int numNenufares;
    double L;//distancia de salto de la rana

    //coordenadas del nenufar
    double Xi, Yi; //valores con dos decimales de precision como mucho
    int numMoscas;//numero de moscas del nenufar

    numNenufares = MAX_NUM_NENUFARES;
    N = 100;
    M = 100;
    L = 200;

    if(output.is_open()){
        output << 1 << "\n";
        output << fixed << setprecision(2) << N << " " << M << " " << numNenufares << " " << L << "\n";

        // Empezamos por la esquina inferior izquierda, y vamos sumadno a Yi 0.10 hasta que llegue a 99.90 (el siguiente seria 100 por
        // lo que estaria fuera del estanque), luego nos movemos con Xi 0.10 a la dercha y reiniciamos Yi a 0.10. Asi hasta que hayamos
        // colocado por 1e4 nenufares. Tampoco importa mucho la distribucion de los nenufares(mientras no se solapen o queden fuera del lago)
        // por que sabemos que van a estar conectados todos con todos.
        Xi = 0.10;
        Yi = 0.10;
        numMoscas = 3;

        for(int j = 0; j<numNenufares; j++){

            output << fixed << setprecision(2) << Xi << " " << Yi << " " << numMoscas << "\n";

            Yi += 0.10;

            if(Yi >= 99.90){
                Yi = 0.10;
                Xi += 0.10;
            }
        }

        output << "\n";

        output.close();
    }
    else cout<<"ERROR AL ABRIR FICHERO\n";

    return 0;
}