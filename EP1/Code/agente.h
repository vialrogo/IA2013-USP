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

#ifndef AGENTE_H
#define AGENTE_H

#include <string>

using namespace std;

class Agente
{
private:

public:
    string widthSearch (char** Matrix, int matrixSize, int nuggetCount);
    string iterativeDepthSearch (char** Matrix, int matrixSize, int nuggetCount);
    string aStarSearch (char** Matrix, int matrixSize, int nuggetCount);
};

#endif // AGENTE_H
