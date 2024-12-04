// JAVIER MARTÍN FUENTES - ANTONINO SASU
// jmarti32@ucm.es - antosasu@ucm.es

// LA RANITA Y LOS NENÚFARES

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
using namespace std;

const int ID_FRAGIL = 0;   // ID del nenúfar frágil

struct tNenufar {
	int id;
	double x, y;
	int moscas;
	bool esFragil = false;
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
	
   // Si el nodo actual es el frágil
	if (s == ID_FRAGIL) {
		estados[s] = NO_ACCESIBLE;
      // Se suman las moscas porque se puede entrar en el nodo y salir
		numMoscas += nenufares[s].moscas;
	}
   // Si el nodo anterior era el frágil
	else if (lastNodo == ID_FRAGIL) {
		noAccesibles = {};
		estados[s] = NO_ACCESIBLE;
		noAccesibles.insert(s);
	}
   // Si el último nodo es accesible
	else if (lastEstado == ACCESIBLE) {
		estados[s] = ACCESIBLE;
		if (lastNodo != -1)
			numMoscas += nenufares[s].moscas;
	}
   // Si el último nodo no es accesible
	else if (lastEstado == NO_ACCESIBLE) {
		estados[s] = NO_ACCESIBLE;
		noAccesibles.insert(s);
	}

	for (int w : adjList[s]) {
		
      // Si desde un nodo no accesible se encuentra con uno accesible desde la orilla (o la orilla)
		if (estados[s] == NO_ACCESIBLE && estados[w] == ACCESIBLE && s != ID_FRAGIL) {

         // Se suman las moscas de la componente no accesible
			for (int nA : noAccesibles) {
				estados[nA] = ACCESIBLE;
				numMoscas += nenufares[nA].moscas;	
			}

         // Se reinicia el conjunto
			noAccesibles = {};
		}

		if (estados[w] == NO_VISITADO)
			numMoscas += dfs(w, s);
	}
	
	return numMoscas;
}

// Comprueba si la rana puede saltar de un nenúfar a otro
bool ranaAlcanza(double x1, double y1, double x2, double y2, double longMax) {
	double dist = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	return dist <= longMax;
}

void resuelveCaso() {


	double n, m, l;
	int v;
	cin >> n >> m >> v >> l;

	adjList.assign(v + 1, {});
	estados.assign(v + 1, NO_VISITADO);
	nenufares = {};
	
	int nodoOrilla = v;  // nodo fantasma que representa la orilla
	
	estados[nodoOrilla] = ACCESIBLE;
	noAccesibles = {};

	for (int i = 0; i < v; i++) {

		tNenufar nen;
		nen.id = i;
		cin >> nen.x >> nen.y >> nen.moscas;

		// el primer nenúfar siempre es el frágil
		nen.esFragil = i == ID_FRAGIL;
		nenufares.push_back(nen);
		
      // Calculamos conexiones con las orillas
		if (nen.x <= l || n - nen.x <= l || nen.y <= l || m - nen.y <= l) {
			adjList[nen.id].push_back(nodoOrilla);
			adjList[nodoOrilla].push_back(nen.id);
		}
	}
	
	// establecemos conexiones entre los nenúfares
	for (int i = 0; i < v - 1; i++) {

		tNenufar n1 = nenufares[i];
	
		// comprobamos con el resto de nenúfares
		for (int j = i + 1; j < v; j++) {

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

	int numCasos;
	cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	return 0;
}
