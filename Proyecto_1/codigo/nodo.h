#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class Nodo
{
	int id;
	std::vector<Nodo> vecinos;
public:
	void crear_nodo (int,std::vector<Nodo>);
	void anadir_vecino(Nodo);
};