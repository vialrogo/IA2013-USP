/* IME-USP
** Mestrado em Ciência da Computação
** Disciplina: Inteligência Artificial
** Exercício-Programa 1 (Busca Informada)
** Alunos: 
** 	    Monna Cleide Santos - n. USP 8477852
** 	    Victor Alberto Romero - n. USP XXXXXXX
**
** 4 de outubro de 2013
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

void Node::expandChildren(queue<Node*>* &nodeQueue, char** matrix, int matrixSize, int* idXNuggets, int* idYNuggets)
{
    bool expandOnMove = true;

    //Try nugget (P)
    if(matrix[agentOnX][agentOnY] == '*') //if there has a nugget
    {
        int idNugget = getIdNuggetByPosition(agentOnX, agentOnY,idXNuggets,idYNuggets);
        if(nuggetCaught[idNugget]==false) //if the nugget is still there
        {
            Node* nodeTemp = new Node(nuggetCaught,nuggetsTotal,agentOnX,agentOnY,path+"P");
            nodeTemp->nuggetCaught[idNugget]=true;
            nodeTemp->nuggetCaughtCount++;
            nodeQueue->push(nodeTemp);
            expandOnMove = false;
        }
    }

    if(expandOnMove)
    {    
        //Try up (C)
        if(agentOnX > 0)
            if(matrix[agentOnX-1][agentOnY]!='1')
                nodeQueue->push(new Node(nuggetCaught,nuggetsTotal,agentOnX-1,agentOnY,path+"C"));
        
        //Try left (E)
        if(agentOnY > 0)
            if(matrix[agentOnX][agentOnY-1]!='1')
                nodeQueue->push(new Node(nuggetCaught,nuggetsTotal,agentOnX,agentOnY-1,path+"E"));
        
        //Try right (D)
        if(agentOnY < (matrixSize-1))
            if(matrix[agentOnX][agentOnY+1]!='1')
                nodeQueue->push(new Node(nuggetCaught,nuggetsTotal,agentOnX,agentOnY+1,path+"D"));
        
        //Try down (B)
        if(agentOnX < (matrixSize-1))
            if(matrix[agentOnX+1][agentOnY]!='1')
                nodeQueue->push(new Node(nuggetCaught,nuggetsTotal,agentOnX+1,agentOnY,path+"B"));
    }
}

int Node::getIdNuggetByPosition(int xPosition, int yPosition, int* idXNuggets, int* idYNuggets)
{
    //Search the idX and idY and return the nugget index or -1 if dont exist
    for(int i=0; i<nuggetsTotal; i++)
        if(idXNuggets[i]==xPosition && idYNuggets[i]==yPosition)
            return i;
    
    return -1;
}
