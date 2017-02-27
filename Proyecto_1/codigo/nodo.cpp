#include <nodo.h>
using namespace std;

void Nodo::crear_nodo (int identificador, std::vector<Nodo> vecino){
	id = identificador;
	vecinos = vecino;
}

void Nodo::anadir_vecino (Nodo vecino){
	vecinos.push_back(vecino);
}