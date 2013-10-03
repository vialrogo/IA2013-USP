/* IME-USP
** Mestrado em Ciência da Computação
** Disciplina: Inteligência Artificial
** Exercício-Programa 1 (Busca Informada)
** Alunos: 
**      Monna Cleide Santos   - n. USP 8477852
**      Victor Alberto Romero - n. USP 8405274
**
** 27 de setembro de 2013
*/

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string>
#include "agent.h"

using namespace std;

class Environment
{
private:
    char** map;
    int size;
    Agent* agent;

public:
    Environment(char** mapIn, int sizeIn);
    ~Environment();
    string solveEnvironment(int typeOfAlgorithm);
    int evalSolution(string solution);
};

#endif // ENVIRONMENT_H
