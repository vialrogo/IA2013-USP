/* IME-USP
** Mestrado em Ciência da Computação
** Disciplina: Inteligência Artificial
** Exercício-Programa 1 (Busca Informada)
** Alunos: 
** 	    Monna Cleide Santos - n. USP 8477852
** 	    Victor Alberto Romero - n. USP XXXXXXX
**
** 27 de setembro de 2013
*/

#ifndef NODE_H
#define NODE_H

#include <string>

using namespace std;

class Node
{
private:
	bool* nuggetCatched;
	int nuggetsTotal, agentOnX, agentOnY;

public:
    Node(bool* nuggetCatchedIn, int nuggetsTotalIn, int agentOnXIn, int agentOnYIn); 
	~Node();
};

#endif // NODE_H
