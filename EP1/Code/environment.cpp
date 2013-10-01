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

Environment::Environment(char** mapIn, int sizeIn)
{
    map = mapIn;
    size = sizeIn;
}

Environment::~Environment()
{
}

string Environment::solveEnvironment(int typeOfAlgorithm)
{
    return string("DDDBBEEEBPDBDDDDCCCCDDPEEBBBDDBBBBPCCCEEEEBBDDPEECCEECCDDCCEEE");
}

