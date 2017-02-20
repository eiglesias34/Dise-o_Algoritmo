#include <grafo.h>

void grafo::crear_grafo(char identificador, std::vector<Nodo> ns, std::vector<Arista> as){
	id = identificador;
	nodos = nodos;
	aristas = as;
}

void grafo::anadir_nodos(Nodo n){
	nodos.push_back(n);
}

void grafo::anadir_arista(Arista a){
	aristas.push_back(a);  
}

bool grafo::existe_nodo(int id){
	for (std::vector<T>::iterator it = nodos.begin(); it != nodos.end(); ++it)
	{
		if (it.id == id)
		{
			return true;
		}
	}
	return false;
}

bool grafo::existe_arista(int n1,int n2){
	for (std::vector<T>::iterator it = aristas.begin(); it != aristas.end(); ++it)
	{
		if ((n1 == it.nodo1) and (n2 == it.nodo2))
		{
			return true;
		}
	}
	return false;
}

Arista grafo::extraer_arista(int n1, int n2){
	if (grafo::existe_arista(n1,n2))
	{
		if ((n1 == it.nodo1) and (n2 == it.nodo2))
		{
			return it;
		}
	}else{
		return NULL;
	}
}