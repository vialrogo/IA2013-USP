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
#include <sstream>

using namespace std;

class Node
{
private:

public:
	bool* nuggetCaught;
	int nuggetsTotal, agentOnX, agentOnY;
    string path;

    Node(bool* nuggetCaughtIn, int nuggetsTotalIn, int agentOnXIn, int agentOnYIn, string pathIn); 
	~Node();
    string state2String();
};

#endif // NODE_H
