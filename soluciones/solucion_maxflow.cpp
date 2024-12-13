// JAVIER MARTÍN FUENTES - ANTONINO SASU
// jmarti32@ucm.es - antosasu@ucm.es

//
//  LA RANITA Y LOS NENÚFARES
//  - Solución mediante MAX-FLOW
//

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <cstring>
#include <queue>
#include <cstdint>
using namespace std;

const double EPS = 1e-6;
const int ID_FRAGIL = 0;	// ID del nenúfar frágil

struct tNenufar {
	int id;
	double x, y;
	int moscas;
};

vector<tNenufar> nenufares;

// MAX-FLOW

const int MAX = 10005;
const int INF = 1e9;

bool visited[MAX];
int parent[MAX];
int cap[MAX][MAX];
using vi = vector<int>;
using vvi = vector<vi>;

vvi adj;

// En parent dejamos el anterior en el recorrido BFS
void bfs(int s, int t) {
	queue<int> q;
	memset(visited, 0, sizeof(visited));
	q.push(s);
	parent[s] = -1;
	visited[s] = true;

	while (!q.empty()) {
		int u = q.front();
		q.pop();
		if (u == t) break;

		for (int i = 0; i < adj[u].size(); ++i) {
			int v = adj[u][i];
			if (!visited[v] && (cap[u][v] > 0)) {
				parent[v] = u;
				visited[v] = true;
				q.push(v);
			}
		}
	}
}

int sendFlow(int s, int t) {
	// Intentamos llegar de s a t
	bfs(s, t);
	if (!visited[t])
		return 0; // No pudimos

	// Buscamos la capacidad más pequeña en el camino
	int flow = INT32_MAX, v = t;
	while (v != s) {
		flow = min(cap[parent[v]][v], flow);
		v = parent[v];
	}

	// Mandamos flujo
	v = t;
	while (v != s) {
		cap[parent[v]][v] -= flow;
		cap[v][parent[v]] += flow; // INVERSA
		v = parent[v];
	}

	return flow;
}

int edmondsKarp(int s, int t) {
	int ret = 0;
	int flow = 0;
	do {
		flow = sendFlow(s, t);
		ret += flow;
	} while (flow > 0);

	return ret;
}


bool ranaAlcanza(double x1, double y1, double x2, double y2, double longMax) {
	double dist = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	return dist <= longMax + EPS;
}

void resuelveCaso() {


	double n, m, l;
	int v;
	cin >> n >> m >> v >> l;

	adj.assign(v + 2, {});
	memset(cap, 0, sizeof(cap));
	nenufares = {};
	
	int nodoOrilla = v;			// representa las 4 orillas del estanque
	int nodoOrigen = v + 1;		// nodo fantasma origen


	for (int i = 0; i < v; i++) {

		tNenufar n1;
		n1.id = i;
		cin >> n1.x >> n1.y >> n1.moscas;

		nenufares.push_back(n1);
		
		// el nodo fantasma origen se conecta con todos los nenúfares
		// la capacidad de la arista es el número de moscas del nenúfar al que se conecta
		
		adj[nodoOrigen].push_back(n1.id);
		adj[n1.id].push_back(nodoOrilla);
		
		cap[nodoOrigen][n1.id] = n1.moscas;
		
		// conectamos con las orillas
		if (n1.x <= l + EPS || n - n1.x <= l + EPS || n1.y <= l + EPS || m - n1.y <= l + EPS) {
			
			adj[n1.id].push_back(nodoOrilla);
			adj[nodoOrilla].push_back(n1.id);
			
			// la capacidad es infinita entre los distintos nenúfares y la orilla
			cap[n1.id][nodoOrilla] = INF;
		}
		
		// establecemos conexiones entre los nenúfares
		for (int j = i - 1; j >= 0; j--) {
			
			tNenufar n2 = nenufares[j];
			
			if (ranaAlcanza(n1.x, n1.y, n2.x, n2.y, l)) {
				adj[n1.id].push_back(n2.id);
				adj[n2.id].push_back(n1.id);
				
				// si el nodo es frágil entonces no admite moscas, pero sí permite que salgan
				// en caso contrario la capacidad de moscas es ilimitada
				cap[n1.id][n2.id] = n2.id != ID_FRAGIL ? INF : 0;
				cap[n2.id][n1.id] = INF;
			}
		}
	}

	int maxMoscas = edmondsKarp(nodoOrigen, nodoOrilla);

	cout << maxMoscas << '\n';

}

int main() {

#ifndef DOMJUDGE
    std::ifstream in("CasoGrande2.1.txt");
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
