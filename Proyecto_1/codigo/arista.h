#include <iostream>

class Arista
{
	int nodo1;
	int nodo2;
	int costo;
	int beneficio; 
public:
	void crear_arista(int,int,int,int);
	int extraer_beneficio() {return beneficio;}
	int extraer_costo() {return costo;}
};