/** Universidad Simón Bolívar
*   CI5437 - Diseño de Algoritmos I
*   Trimestre Ene-Mar 2017
*
*   Proyecto II
*  
* 
*   Hecho por: Enrique Iglesias 11-10477
*              Gabriel Iglesias 11-10476
*
*   Última modificación: 
*/


#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <algorithm>

#include <time.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

bool cumple_actamiento(Arista a, deque<Arista> ){
	int beneficioE = a.beneficio - a.costo;
	int beneficioSolParcial = obtener_beneficio(solParcial) + beneficioE;
	int maxBeneficio = beneficioDisponible -  std::max_element(0,beneficioE) + beneficioSolParcial;
	if (maxBeneficio <= obtener_beneficio(mejorSol))
	{
		return false;
	}
	return true;
}