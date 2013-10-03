/* IME-USP
** Mestrado em Ciência da Computação
** Disciplina: Inteligência Artificial
** Exercício-Programa 1 (Busca Informada)
** Alunos: 
**      Monna Cleide Santos - n. USP 8477852
**      Victor Alberto Romero - n. USP XXXXXXX
**
** 27 de setembro de 2013
*/

#ifndef AGENT_H
#define AGENT_H

#include <string>
#include <queue>
#include "node.h"

using namespace std;

class Agent
{
private:
    char** matrix;
    int matrixSize;
    int nuggetTotal;
    bool* nuggetCachedInitial;

public:
    Agent(char** matrixIn, int matrixSizeIn);
    ~Agent();
    string widthSearch (int nuggetCount);
    string iterativeDepthSearch (int nuggetCount);
    string aStarSearch (int nuggetCount);
};

#endif // AGENT_H
