/* IME-USP
** Mestrado em Ciência da Computação
** Disciplina: Inteligência Artificial
** Exercício-Programa 1 (Busca Informada)
** Alunos: 
**      Monna Cleide Santos   - n. USP 8477852
**      Victor Alberto Romero - n. USP 8405274
**
** 4 de outobro de 2013
*/

#ifndef AGENT_H
#define AGENT_H

#include <string>
#include <queue>
#include <stack>
#include <set>
#include "node.h"

using namespace std;

class Agent
{
private:
    set<string>* totalSet;
    char** matrix;
    int matrixSize;
    int nuggetTotal;
    bool* nuggetCaughtInitial;
    int* idXNuggets;
    int* idYNuggets;
    bool isNodeASolution(Node* node, int nuggetCount);
    void expandChildren(Node* nodeInitial, queue<Node*>* &nodeQueue);
    void initializeIdNuggetsArray();
    int getIdNuggetByPosition(int xPosition, int yPosition);

public:
    Agent(char** matrixIn, int matrixSizeIn);
    ~Agent();
    string widthSearch (int nuggetCount);
    string depthSearch (int nuggetCount);
    string aStarSearch (int nuggetCount);
};

#endif // AGENT_H
