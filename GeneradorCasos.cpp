// JAVIER MARTÍN FUENTES - ANTONINO SASU
// jmarti32@ucm.es - antosasu@ucm.es

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <unordered_set>
#include <random>
using namespace std;

const int NUM_CASOS=100;
const int MIN_NUM_NENUFARES=1;
const int MAX_NUM_NENUFARES=1e1;

using us = unordered_set<pair<double, double>>;


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
    uniform_int_distribution<> distrib(MIN_NUM_NENUFARES, MAX_NUM_NENUFARES);//para el numero de nenufares

    
    cout<<NUM_CASOS<<"\n";
    for(int i = 0; i<NUM_CASOS; i++){
        us mapaNenufares;//vamos guardando las coordenadas de los nenufares para que no hayan repetidos en un mismo caso

        numNenufares = distrib(gen);
        
        for(int j = 0; j<numNenufares; j++){
            
        }
    }

    cout<<"\n";

    return 0;
}