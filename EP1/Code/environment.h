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

class Environment
{
private:
    char** map;
    int size;
public:
    Environment(char** mapIn, int sizeIn);
    ~Environment();
};

#endif // ENVIRONMENT_H
