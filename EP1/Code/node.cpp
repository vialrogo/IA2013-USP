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
Node::Node(bool* nuggetCaughtIn, int nuggetsTotalIn, int agentOnXIn, int agentOnYIn, string pathIn)
{
	nuggetsTotal  = nuggetsTotalIn;
	agentOnX = agentOnXIn;
	agentOnY = agentOnYIn;
    path = pathIn;

    //create the own vector for delete it in destructor
	nuggetCaught = new bool[nuggetsTotal];
    nuggetCaughtCount=0;
    for(int i=0; i<nuggetsTotal; i++)
    {
        nuggetCaught[i] = nuggetCaughtIn[i];
        if(nuggetCaught[i])
            nuggetCaughtCount++;
    }
}

// destructor
Node::~Node()
{
    delete nuggetCaught;
    nuggetCaught=0;
}

string Node::state2String()
{
    ostringstream output;

    output << agentOnX << "_";
    output << agentOnY << "_";

    for(int i=0; i<nuggetsTotal; i++)
        if(nuggetCaught[i]) output << "1";
        else                output << "0";

    return output.str();
}
