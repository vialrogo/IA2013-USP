/* IME-USP
** Mestrado em Ciência da Computação
** Disciplina: Inteligência Artificial
** Exercício-Programa 1 (Busca Informada)
** Alunos: 
** 		Monna Cleide Santos   - n. USP 8477852
** 		Victor Alberto Romero - n. USP 8405274
**
** 27 de setembro de 2013
*/

#include "environment.h"
#include <iostream>
using namespace std;

Environment::Environment(char** mapIn, int sizeIn)
{
    map = mapIn;
    size = sizeIn;
    agent = new Agent(mapIn, sizeIn);
}

Environment::~Environment()
{
}

string Environment::solveEnvironment(int typeOfAlgorithm)
{
    string solution;
    
    //for(int)
    solution = agent->widthSearch(4);
    
    return solution; 
}

int Environment::evalSolution(string solution)
{
    int steps=0;
    int nuggets=0;

    for(int i=0; i<solution.size(); i++) //Count nuggets and steps
    {
        if(solution[i]!='P')
            steps++;
        else
            nuggets++;
    }
    return (4*nuggets*size - steps);
}
