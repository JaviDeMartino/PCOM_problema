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

const int NUM_CASOS=10;

const int MIN_NUM_NENUFARES = 1;
const int MAX_NUM_NENUFARES = 100;

const double MIN_COOR = 0.01;
const double MAX_COOR = 1e3 - 0.01;

const int MIN_MOSCAS = 0;
const int MAX_MOSCAS = 1e5;

const int MIN_SALTO = 0;
const int MAX_SALTO = 1e3 - 0.01;


int main() {

    double N, M;//tamaño del rectangulo con esquina inferior izquierda en el origen
    int numNenufares;
    double L;//distancia de salto de la rana

    //coordenadas del nenufar
    double Xi, Yi; //valores con dos decimales de precision como mucho
    int numMoscas;//numero de moscas del nenufar

    //generador de numeros aleatorios en un rango
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distribIntNenufares(MIN_NUM_NENUFARES, MAX_NUM_NENUFARES);//para el numero de nenufares
    uniform_real_distribution<> distribDouble(MIN_COOR, MAX_COOR);//para N y M
    uniform_int_distribution<> distribIntMoscas(MIN_MOSCAS, MAX_MOSCAS);
    uniform_real_distribution<> distribDoubleSalto(MIN_SALTO, MAX_SALTO);

    
    cout<<NUM_CASOS<<"\n";
    for(int i = 0; i<NUM_CASOS; i++){

        set< pair<double, double> > mapaNenufares;//vamos guardando las coordenadas de los nenufares para que no hayan repetidos en un mismo caso

        numNenufares = distribIntNenufares(gen);
        N = distribDouble(gen);
        M = distribDouble(gen);
        L = distribDoubleSalto(gen);

        uniform_real_distribution<> distribDoubleEjeX(MIN_COOR, N - 0.01);//para coordenada x de los nenufares
        uniform_real_distribution<> distribDoubleEjeY(MIN_COOR, M - 0.01);//para coordenada y de los nenufares
        
        cout << fixed << setprecision(2) << N << " " << M << " " << numNenufares << " " << L << "\n";

        for(int j = 0; j<numNenufares; j++){

            Xi = distribDoubleEjeX(gen);
            Yi = distribDoubleEjeY(gen);

            if(mapaNenufares.count({Xi, Yi}) == 0){
                mapaNenufares.insert({Xi, Yi});
                numMoscas = distribIntMoscas(gen);

                cout << fixed << setprecision(2) << Xi << " " << Yi << " " << numMoscas << "\n";
            }
        }
    }

    cout << "\n";

    return 0;
}