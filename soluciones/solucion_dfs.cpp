// JAVIER MARTÍN FUENTES - ANTONINO SASU
// jmarti32@ucm.es - antosasu@ucm.es

//
//  LA RANITA Y LOS NENÚFARES
//  - Solución mediante DFS
//  

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <cmath>
using namespace std;

const double EPS = 1e-7;
const int ID_FRAGIL = 0;	// ID del nenúfar frágil

struct tNenufar {
	int id;
	double x, y;
	int moscas;
};

// estados de los nenúfares en la búsqueda
typedef enum { ACCESIBLE, NO_ACCESIBLE, NO_VISITADO } tEstado;

using vN = vector<tNenufar>;
vN nenufares;

using vi = vector<int>;
using vvi = vector<vi>;

vvi adjList;
vector<tEstado> estados;
unordered_set<int> noAccesibles;

int dfs(int s, int lastNodo) {
	
	int numMoscas = 0;
	tEstado lastEstado = estados[lastNodo];
	
	if (s == ID_FRAGIL) {
		estados[s] = NO_ACCESIBLE;
		numMoscas += nenufares[s].moscas;
	}
	else if (lastNodo == ID_FRAGIL) {
		noAccesibles = {};
		estados[s] = NO_ACCESIBLE;
		noAccesibles.insert(s);
	}
	else if (lastEstado == ACCESIBLE) {
		estados[s] = ACCESIBLE;
		if (lastNodo != -1)
			numMoscas += nenufares[s].moscas;
	}
	else if (lastEstado == NO_ACCESIBLE) {
		estados[s] = NO_ACCESIBLE;
		noAccesibles.insert(s);
	}

	for (int w : adjList[s]) {
		
		if (estados[s] == NO_ACCESIBLE && estados[w] == ACCESIBLE && s != ID_FRAGIL) {
			for (int nA : noAccesibles) {
				estados[nA] = ACCESIBLE;
				numMoscas += nenufares[nA].moscas;
				
			}
			noAccesibles = {};
		}

		if (estados[w] == NO_VISITADO)
			numMoscas += dfs(w, s);
	}
	
	return numMoscas;
}


bool ranaAlcanza(double x1, double y1, double x2, double y2, double longMax) {
	double dist = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	return dist <= longMax + EPS;
}

void resuelveCaso() {


	double n, m, l;
	int v;
	cin >> n >> m >> v >> l;

	adjList.assign(v + 1, {});
	estados.assign(v + 1, NO_VISITADO);
	nenufares = {};
	
	int nodoOrilla = v;
	
	estados[nodoOrilla] = ACCESIBLE;
	noAccesibles = {};

	for (int i = 0; i < v; i++) {

		tNenufar n1;
		n1.id = i;
		cin >> n1.x >> n1.y >> n1.moscas;

		// el primer nenúfar siempre es el frágil
		nenufares.push_back(n1);
		
		if (n1.x <= l + EPS || n - n1.x <= l + EPS || n1.y <= l + EPS || m - n1.y <= l + EPS) {
			adjList[n1.id].push_back(nodoOrilla);
			adjList[nodoOrilla].push_back(n1.id);
		}
		
		// establecemos conexiones entre los nenúfares
		for (int j = i - 1; j >= 0; j--) {
			
			tNenufar n2 = nenufares[j];
			
			if (ranaAlcanza(n1.x, n1.y, n2.x, n2.y, l)) {
				adjList[n1.id].push_back(n2.id);
				adjList[n2.id].push_back(n1.id);
			}
		}
	}

	
	int maxMoscas = dfs(nodoOrilla, -1);

	cout << maxMoscas << '\n';

}

int main() {

#ifndef DOMJUDGE
    std::ifstream in("CasoGrande2.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	unsigned t0 = clock();

    int num = 0; cin>>num;
    while (num--){
        resuelveCaso();
    }

	unsigned t1 = clock();

    double time = (double(t1-t0)/CLOCKS_PER_SEC);

    cout << "Tiempo de ejecución: "<<time <<" s\n";

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;

}