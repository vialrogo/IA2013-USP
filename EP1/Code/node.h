/* IME-USP
** Mestrado em Ciência da Computação
** Disciplina: Inteligência Artificial
** Exercício-Programa 1 (Busca Informada)
** Alunos: 
** 	    Monna Cleide Santos - n. USP 8477852
** 	    Victor Alberto Romero - n. USP XXXXXXX
**
** 4 de outubro de 2013
*/

#ifndef NODE_H
#define NODE_H

#include <stdlib.h>
#include <string>
#include <sstream>
#include <queue>

using namespace std;

class IntComparison
{
private:
  bool reverse;
public:
    IntComparison(const bool& revparam=false){ reverse=revparam; }
    bool operator() (const int& lhs, const int&rhs) const
    {
        if (reverse) return (lhs>rhs);
        else return (lhs<rhs);
    }
};

class Node
{
    typedef priority_queue <int,  vector<int>,   IntComparison> pqInt;

public:
	bool* nuggetCaught;
	int nuggetsTotal, agentOnX, agentOnY;
    string path;
    int nuggetCaughtCount;
    int heuristicValue;

    Node(bool* nuggetCaughtIn, int nuggetsTotalIn, int agentOnXIn, int agentOnYIn, string pathIn); 
	~Node();
    string state2String();
    bool isSolution(int nuggetCount);
    void calculeHeuristic(int nuggetCount, int* idXNuggets, int* idYNuggets);
    void expandChildren(queue<Node*>* &nodeQueue, char** matrix, int matrixSize, int* idXNuggets, int* idYNuggets);
    int getIdNuggetByPosition(int xPosition, int yPosition, int* idXNuggets, int* idYNuggets);
};

#endif // NODE_H
