// JAVIER MARTÍN FUENTES - ANTONINO SASU
// jmarti32@ucm.es - antosasu@ucm.es

//
//  LA RANITA Y LOS NENÚFARES
//  SOLUCIÓN OFICIAL
//  - Solución mediante UFDS
//  

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

const double EPS = 1e-6;
const int ID_FRAGIL = 0;    // ID del nenúfar frágil

struct tNenufar {
	int id;
	double x, y;
	int moscas;
};

using vN = vector<tNenufar>;
vN nenufares;

struct UFDS {
	
	vector<int> p;
	vector<int> moscas;	// almacena la suma de las moscas de las componentes
	int numSets;

	UFDS(int n) : p(n), moscas(n, 0), numSets(n) {
		for (int i = 0; i < n; ++i) {
			p[i] = i;
		}
	}

	int find(int x) {
		return (p[x] == x) ? x : p[x] = find(p[x]);
	}
	
	// Une las componentes que contienen x e y
	void merge(int x, int y) {
		int i = find(x), j = find(y);
		if (i != j) {
			p[i] = j;
			moscas[j] += moscas[i];
			--numSets;
		}
	}
	
	// Establece el número de moscas de un nodo
	void setMoscas(int x, int m) {
		moscas[x] = m;
	}

	// Devuelve la suma de moscas en la componente de un nenufar dado
	int getMoscas(int x) {
		return moscas[find(x)];
	}
};

// Comprueba si la rana llega saltando de unas coordenadas a otras
bool ranaAlcanza(double x1, double y1, double x2, double y2, double longMax) {
	double dist = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	return dist <= longMax + EPS;
}

void resuelveCaso() {

	double n, m, l;
	int v;
	cin >> n >> m >> v >> l;

	nenufares = {};
	
	int nodoOrilla = v;
	
	UFDS uf(v + 1);

	for (int i = 0; i < v; i++) {

		tNenufar n1;
		n1.id = i;
		cin >> n1.x >> n1.y >> n1.moscas;

		// el primer nenúfar siempre es el frágil
		nenufares.push_back(n1);
		
		uf.setMoscas(i, n1.moscas);
		
		// establecemos conexiones entre los nenúfares y la orilla
		// EXCEPTO CON EL FRÁGIL
		
		if (i != ID_FRAGIL)
			if (n1.x <= l + EPS || n - n1.x <= l + EPS || n1.y <= l + EPS || m - n1.y <= l + EPS)
				uf.merge(n1.id, nodoOrilla);

		for (int j = i - 1; j > 0; j--) {
			
			tNenufar n2 = nenufares[j];
            
			if (ranaAlcanza(n1.x, n1.y, n2.x, n2.y, l)) {
				uf.merge(n1.id, n2.id);
			}
		}
	}
	
	// Nos quedamos con las moscas totales de la componente conexa de la orilla
	int maxMoscas = uf.getMoscas(nodoOrilla);
	
	// Comprobamos conexiones con el nodo frágil
	
	tNenufar nF = nenufares[ID_FRAGIL];

	if (nF.x <= l + EPS || n - nF.x <= l + EPS || nF.y <= l + EPS || m - nF.y <= l + EPS)
		uf.merge(nF.id, nodoOrilla);
	
	for (int i = 1; i < v; i++) {
		tNenufar n2 = nenufares[i];
		
		if (ranaAlcanza(nF.x, nF.y, n2.x, n2.y, l)) {
			uf.merge(nF.id, n2.id);
		}
	}
	
	// Si al añadirlo al UF las componentes conexas del nodo frágil y la orilla coinciden
	if (uf.find(ID_FRAGIL) == uf.find(nodoOrilla))
		maxMoscas += nF.moscas;		// sumamos las moscas del nodo frágil
	
	cout << maxMoscas << '\n';

}

int main() {

    int num = 0; cin>>num;
    while (num--){
        resuelveCaso();
    }

    return 0;

}
