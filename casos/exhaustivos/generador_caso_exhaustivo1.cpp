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

const int NUM_CASOS = 1003;

const int MIN_NUM_NENUFARES = 1;
const int MAX_NUM_NENUFARES = 1e3;

const double MIN_COOR = 0.02;
const double MAX_COOR = 1e3;

const int MIN_MOSCAS = 0;
const int MAX_MOSCAS = 1e5;

const int MIN_SALTO = 0;
const int MAX_SALTO = 1500;

//Generamos el numero y coordenadas de los nenufares(y su numero de moscas) una sola vez, 
//los fijamos, y luego para cada caso vamos generando valores de salto diferentes

//Creamos 1000 casos diferentes y para que el archivo de texto no quede muy grande hemos limitado el numero de nenufares a 1000

int main()
{
    double N, M; // tamaño del rectangulo con esquina inferior izquierda en el origen
    int numNenufares;
    double L; // distancia de salto de la rana

    // coordenadas del nenufar
    double Xi, Yi; // valores con dos decimales de precision como mucho
    int numMoscas; // numero de moscas del nenufar

    // generador de numeros aleatorios en un rango
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distribIntNenufares(MIN_NUM_NENUFARES, MAX_NUM_NENUFARES); // para el numero de nenufares
    uniform_real_distribution<> distribDoubleCoor(MIN_COOR, MAX_COOR);                    // para los valores de N y M
    uniform_int_distribution<> distribIntMoscas(MIN_MOSCAS, MAX_MOSCAS);                  // para el numero de moscas de cada nenufar
    uniform_real_distribution<> distribDoubleSalto(MIN_SALTO, MAX_SALTO);                 // para la longitud de salto de la rana

    ofstream output("CasoExhaustivo1.txt");

    if (output.is_open())
    {
        output << NUM_CASOS << "\n";

        //Hemos limitado el numero de nenufares a 1000 en vez de 10000 para que no nos salga muchas lineas en el archivo de texto
        numNenufares = distribIntNenufares(gen);
        N = distribDoubleCoor(gen);
        M = distribDoubleCoor(gen);

        uniform_real_distribution<> distribDoubleEjeX(0.01, N - 0.01); // para coordenada x de los nenufares
        uniform_real_distribution<> distribDoubleEjeY(0.01, M - 0.01); // para coordenada y de los nenufares

        set<pair<double, double>> mapaNenufares; // vamos guardando las coordenadas de los nenufares para que no hayan repetidos en un mismo caso

        //{ {Xi, Yi} , numMoscas }
        vector< pair<pair<double, double>, int>> nenufares;// guardamos los nenufares en un vector para luego mostrar los mismo por cada caso

        //Generamos una sola vez las coordenadas de cada nenufar con su cantidad de moscas
        for(int i = 0; i < numNenufares;i++){
            Xi = distribDoubleEjeX(gen);
            Yi = distribDoubleEjeY(gen);

            if (mapaNenufares.count({Xi, Yi}) == 0)
            {
                mapaNenufares.insert({Xi, Yi});
                numMoscas = distribIntMoscas(gen);

                nenufares.push_back({{Xi, Yi}, numMoscas});   
            }

            else
                i--; // si las coordenads han sido repetidas, no avanzamos en el bucle for para crear otras coordenadas
                     // La probabilidad de que dos coordenas(numero con dos decimales) sean iguales es infima
        }

        L = 0.00;// Empezamos con una distancia de salto de 0.00, luego por cada caso subimos 0.01 hasta que llegue a 1.01,
                 // luego sumamos de 0.11 en 0.11 hasta que llegue a 12,01, luego de 1,23 en 1,23 hasta que llegue a 135,01,
                 // de 2,01 en 2,01 hasta 336,01, luego de 1,71 en 1,71 hasta llegar a 1360,30 y acabamos con un ultimo caso
                 // que seria 1500 de salto. 

        for (int i = 0; i < NUM_CASOS; i++)
        {
            output << fixed << setprecision(2) << N << " " << M << " " << numNenufares << " " << L << "\n";

            if(numNenufares==nenufares.size()){//para comprobar que no ocurre nada raro
                for(auto nen: nenufares){
                    output << fixed << setprecision(2) << nen.first.first << " " << nen.first.second << " " << nen.second << "\n";
                }
            }
            else{
                cout << "ERROR AL CREAR EL CASO\n";
                break;
            }

            //actualizamos L respecto al valor que tiene ahora
            if(L>=1360.30){
                L = MAX_SALTO;
            }
            else if(L>=336.01){
                L += 1.71;
            }
            else if(L>=135.01){
                L += 2.01;
            }
            else if(L>=12.01){
                L += 1.23;
            }
            else if(L>=1.01){
                L += 0.11;
            }
            else L += 0.01;

            output << "\n";
        }

        output.close();
    }

    else cout<<"ERROR AL ABRIR ARCHIVO\n";

    return 0;
}




