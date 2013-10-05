/* IME-USP
** Mestrado em Ciência da Computação
** Disciplina: Inteligência Artificial
** Exercício-Programa 1 (Busca Informada)
** Alunos: 
** 		Monna Cleide Santos   - n. USP 8477852
** 		Victor Alberto Romero - n. USP 8405274
**
** 4 de outobro de 2013
*/

#include "environment.h"

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
    int points = 0;
    string solution = "";
    string newSolution = "";

    for(int i=0; i< size/2; i++)
    {
        if(typeOfAlgorithm == 1) newSolution = agent->widthSearch(i+1);
        if(typeOfAlgorithm == 2) newSolution = agent->depthSearch(i+1);
        if(typeOfAlgorithm == 3) newSolution = agent->aStarSearch(i+1);
        
        if(evalSolution(newSolution)>points)
        {
            solution = newSolution;
            points = evalSolution(newSolution);
        }
    }
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
