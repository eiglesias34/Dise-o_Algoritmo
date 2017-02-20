#include <iostream>
#include <nodo.h>
#include <arista.h>
#include <cmath>
#include <vector>
using namespace std;

class grafo
{
	char id;
	std::vector<Nodo> nodos;
	std::vector<Arista> aristas;  
public:
	void crear_grafo(char,std::vector<Nodo>, std::vector<Arista>);
	void anadir_nodos(Nodo);
	void anadir_arista(Arista);
	bool existe_nodo(int);
	bool existe_arista(int,int);
	Arista extraer_arista(int,int);	
};