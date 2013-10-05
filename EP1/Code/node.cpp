/* IME-USP
** Mestrado em Ciência da Computação
** Disciplina: Inteligência Artificial
** Exercício-Programa 1 (Busca Informada)
** Alunos: 
** 	    Monna Cleide Santos - n. USP 8477852
** 	    Victor Alberto Romero - n. USP XXXXXXX
**
** 4 de outobro de 2013
*/ 

#include "node.h"

Node::Node(bool* nuggetCaughtIn, int nuggetsTotalIn, int agentOnXIn, int agentOnYIn, string pathIn)
{
	nuggetsTotal  = nuggetsTotalIn;
	agentOnX = agentOnXIn;
	agentOnY = agentOnYIn;
    path = pathIn;
    heuristicValue=0;

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

bool Node::isSolution(int nuggetCount)
{
    //Total of nuggets caught in this node
    int totalNuggetCaught=0;
    for(int i=0; i<nuggetsTotal; i++)
        if(nuggetCaught[i])
            totalNuggetCaught++;

    if(totalNuggetCaught == nuggetCount && agentOnX==0 && agentOnY==0)
        return true;
    else
        return false;
}

void Node::calculeHeuristic(int nuggetCount, int* idXNuggets, int* idYNuggets)
{
    if(nuggetCaughtCount < nuggetCount)
    {
        int farther;
        pqInt* queueInt = new pqInt(IntComparison(true));
        
        for(int i=0; i<nuggetsTotal; i++)
            if(!nuggetCaught[i])
                queueInt->push( abs(idXNuggets[i]-agentOnX) 
                              + abs(idYNuggets[i]-agentOnY)
                              + idXNuggets[i] + idYNuggets[i]);

        for(int i=0; i<(nuggetCount-nuggetCaughtCount); i++)
        {
            farther=queueInt->top();
            queueInt->pop();
        }
        heuristicValue = farther;
    }
    else
        heuristicValue = agentOnX + agentOnY;
}
