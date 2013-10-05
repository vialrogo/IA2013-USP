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

#include <stdlib.h>
#include <string>
#include <queue>
#include <stack>
#include <set>
#include <vector>
#include "node.h"

using namespace std;

class NodeComparison
{
public:
    NodeComparison(){}
    bool operator() (const Node* lhs, const Node* rhs) const
    {
      return ((lhs->heuristicValue + lhs->path.size() - lhs->nuggetCaughtCount ) >= 
              (rhs->heuristicValue + rhs->path.size() - rhs->nuggetCaughtCount )); 
    }
};

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

class Agent
{
    typedef priority_queue <int,  vector<int>,   IntComparison> pqInt;
    typedef priority_queue <Node*,vector<Node*>,NodeComparison> pqNode;

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
    void calculeHeuristic(Node* &node, int nuggetCount);

public:
    Agent(char** matrixIn, int matrixSizeIn);
    ~Agent();
    string widthSearch (int nuggetCount);
    string depthSearch (int nuggetCount);
    string aStarSearch (int nuggetCount);
};

#endif // AGENT_H
