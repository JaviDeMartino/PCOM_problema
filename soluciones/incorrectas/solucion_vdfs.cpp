// JAVIER MARTÍN FUENTES - ANTONINO SASU
// jmarti32@ucm.es - antosasu@ucm.es

//
//  LA RANITA Y LOS NENÚFARES
//  - Solución mediante DFS (v veces)
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

const double EPS = 1e-6;
const int MAX_NENUFARES = 1e4;
const int ID_FRAGIL = 0;	// ID del nenúfar frágil

struct tNenufar {
	int id;
	double x, y;
	int moscas;
};


using vN = vector<tNenufar>;
vN nenufares;

using vi = vector<int>;
using vvi = vector<vi>;

vvi adjList;
bool visited[MAX_NENUFARES];

bool dfs(int s, int nodoOrilla) {
	
	if (s == nodoOrilla) return true;
	
	visited[s] = true;
	
	bool alcanzaOrilla = false;
	
	for (int w : adjList[s]) {
		
		// Si es el frágil o ya está visitado
		if (w == ID_FRAGIL || visited[w]) continue;

		alcanzaOrilla = alcanzaOrilla || dfs(w, nodoOrilla);
		if (alcanzaOrilla) return true;
		
	}
	return false;
	
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
	nenufares = {};
	
	int nodoOrilla = v;

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
	
	int moscas = 0;
	for (int i = 0; i < v; i++) {
		
		memset(visited, false, sizeof(visited));
		bool orillaAlcanzable = dfs(i, nodoOrilla);
		if (orillaAlcanzable)
			moscas += nenufares[i].moscas;
	
	}
		
	cout << moscas << '\n';

}

int main() {

	int numCasos;
	cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	return 0;
}
