/* IME-USP
** Mestrado em Ciência da Computação
** Disciplina: Inteligência Artificial
** Exercício-Programa 1 (Busca Informada)
** Alunos: 
** 	    Monna Cleide Santos - n. USP 8477852
** 	    Victor Alberto Romero - n. USP XXXXXXX
**
** 27 de setembro de 2013
*/ 

#include "node.h"

// constructor
Node::Node(bool* nuggetCatchedIn, int nuggetsTotalIn, int agentOnXIn, int agentOnYIn)
{
	nuggetsTotal  = nuggetsTotalIn;
	agentOnX = agentOnXIn;
	agentOnY = agentOnYIn;

    //create the own vector for delete it in destructor
	nuggetCatched = new bool[nuggetsTotal];
    for(int i=0; i<nuggetsTotal; i++)
        nuggetCatched[i] = nuggetCatchedIn[i];
}

// destructor
Node::~Node()
{
    delete nuggetCatched;
    nuggetCatched=0;
}
