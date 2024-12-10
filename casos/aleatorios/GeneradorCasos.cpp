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

const int NUM_CASOS = 10;

const int MIN_NUM_NENUFARES = 1;
const int MAX_NUM_NENUFARES = 1e4;

const double MIN_COOR = 0.01;
const double MAX_COOR = 1e3;

const int MIN_MOSCAS = 0;
const int MAX_MOSCAS = 1e5;

const int MIN_SALTO = 0;
const int MAX_SALTO = 1e3;

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

    ofstream output("CasoAleatorio1.txt");

    if (output.is_open())
    {
        output << NUM_CASOS << "\n";

        for (int i = 0; i < NUM_CASOS; i++)
        {
            set<pair<double, double>> mapaNenufares; // vamos guardando las coordenadas de los nenufares para que no hayan repetidos en un mismo caso

            numNenufares = distribIntNenufares(gen);
            N = distribDoubleCoor(gen);
            M = distribDoubleCoor(gen);
            L = distribDoubleSalto(gen);

            uniform_real_distribution<> distribDoubleEjeX(MIN_COOR, N - 0.01); // para coordenada x de los nenufares
            uniform_real_distribution<> distribDoubleEjeY(MIN_COOR, M - 0.01); // para coordenada y de los nenufares

            output << fixed << setprecision(2) << N << " " << M << " " << numNenufares << " " << L << "\n";

            for (int j = 0; j < numNenufares; j++)
            {
                Xi = distribDoubleEjeX(gen);
                Yi = distribDoubleEjeY(gen);

                if (mapaNenufares.count({Xi, Yi}) == 0)
                {
                    mapaNenufares.insert({Xi, Yi});
                    numMoscas = distribIntMoscas(gen);

                    output << fixed << setprecision(2) << Xi << " " << Yi << " " << numMoscas << "\n";
                }

                else
                    j--; // si las coordenads han sido repetidas, no avanzamos en el bucle for para crear otras coordenadas
            }

            output << "\n";
        }

        output << "\n";

        output.close();
    }

    else cout<<"ERROR AL ABRIR ARCHIVO\n";

    return 0;
}