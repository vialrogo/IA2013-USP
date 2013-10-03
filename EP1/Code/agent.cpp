/* IME-USP
** Mestrado em Ciência da Computação
** Disciplina: Inteligência Artificial
** Exercício-Programa 1 (Busca Informada)
** Alunos: 
** 	    Monna Cleide Santos   - n. USP 8477852
** 	    Victor Alberto Romero - n. USP 8405274
**
** 27 de setembro de 2013
*/

#include "agent.h"
#include <iostream>
using namespace std;

Agent::Agent(char** matrixIn, int matrixSizeIn)
{
    totalSet = new set<string>();
    matrix = matrixIn;
    matrixSize = matrixSizeIn;
    nuggetTotal = matrixSize/2;

    idXNuggets = new int[nuggetTotal];
    idYNuggets = new int[nuggetTotal];
    initializeIdNuggetsArray();

    nuggetCaughtInitial = new bool[nuggetTotal];
    for(int i=0; i<nuggetTotal; i++)
        nuggetCaughtInitial[i] = false; //false means that the nugget isn't still catched
}

Agent::~Agent()
{
    delete nuggetCaughtInitial;
    nuggetCaughtInitial=0;
}

void Agent::initializeIdNuggetsArray()
{
    int id=0;
    for(int i=0; i<matrixSize; i++)
    {
        for(int j=0; j<matrixSize; j++)
        {
            if(matrix[i][j]=='*')
            {
                idXNuggets[id]=i;
                idYNuggets[id]=j;
                id++;
            }
        }
    }
}

int Agent::getIdNuggetByPosition(int xPosition, int yPosition)
{
    //Search the idX and idY and return the nugget index or -1 if dont exist
    for(int i=0; i<nuggetTotal; i++)
        if(idXNuggets[i]==xPosition && idYNuggets[i]==yPosition)
            return i;
    
    return -1;
}

bool Agent::isNodeASolution(Node* node, int nuggetCount)
{
    //Total of nuggets caught in this node
    int totalNuggetCaught=0;
    for(int i=0; i<nuggetTotal; i++)
        if(node->nuggetCaught[i])
            totalNuggetCaught++;

    if(totalNuggetCaught == nuggetCount && node->agentOnX==0 && node->agentOnY==0)
        return true;
    else
        return false;
}

void Agent::expandChildren(Node* nodeInitial, queue<Node*>* &nodeQueue)
{
    int agentOnX = nodeInitial->agentOnX;
    int agentOnY = nodeInitial->agentOnY;
    int nuggetsTotal = nodeInitial->nuggetsTotal;
    string path = nodeInitial->path;
    
    //Try nugget (P)
    if(matrix[nodeInitial->agentOnX][nodeInitial->agentOnY] == '*') //if there has a nugget
    {
        int idNugget = getIdNuggetByPosition(nodeInitial->agentOnX, nodeInitial->agentOnY);
        if(nodeInitial->nuggetCaught[idNugget]==false) //if the nugget is still there
        {
            Node* nodeTemp = new Node(nodeInitial->nuggetCaught,nuggetsTotal,agentOnX,agentOnY,path+"P");
            nodeTemp->nuggetCaught[idNugget]=true;
            nodeQueue->push(nodeTemp);
        }
    }
    
    //Try up (C)
    if(nodeInitial->agentOnX > 0)
        if(matrix[agentOnX-1][agentOnY]!='1')
            nodeQueue->push(new Node(nodeInitial->nuggetCaught,nuggetsTotal,agentOnX-1,agentOnY,path+"C"));
    
    //Try left (E)
    if(nodeInitial->agentOnY > 0)
        if(matrix[agentOnX][agentOnY-1]!='1')
            nodeQueue->push(new Node(nodeInitial->nuggetCaught,nuggetsTotal,agentOnX,agentOnY-1,path+"E"));
    
    //Try right (D)
    if(nodeInitial->agentOnY < (matrixSize-1))
        if(matrix[agentOnX][agentOnY+1]!='1')
            nodeQueue->push(new Node(nodeInitial->nuggetCaught,nuggetsTotal,agentOnX,agentOnY+1,path+"D"));
    
    //Try down (B)
    if(nodeInitial->agentOnX < (matrixSize-1))
        if(matrix[agentOnX+1][agentOnY]!='1')
            nodeQueue->push(new Node(nodeInitial->nuggetCaught,nuggetsTotal,agentOnX+1,agentOnY,path+"B"));
}

string Agent::widthSearch (int nuggetCount)
{
    //Create the queue and auxiliar variables
	queue<Node*>* nodeQueue = new queue<Node*>();
	Node* firstNode = new Node(nuggetCaughtInitial, nuggetTotal, 0, 0, "");
	nodeQueue->push(firstNode); // Put the initial node
    Node* nodeCatcher;
    totalSet->clear();

    //int count=0;

	while(!nodeQueue->empty()) // ############### I can stop early??
    {
		nodeCatcher = nodeQueue->front();
		nodeQueue->pop();

        if(totalSet->count(nodeCatcher->state2String())==0)
        {
            if(isNodeASolution(nodeCatcher, nuggetCount)) //If it is a solution
                //{
                //cout<<"Numero de nodos expandido: "<<count<<endl;
                return nodeCatcher->path; 
            //}
            else
                expandChildren(nodeCatcher, nodeQueue); //Expand the children
            
            totalSet->insert(nodeCatcher->state2String());
        }
        //count++;
        delete nodeCatcher;
    }
    //cout<<"Numero de nodos expandido: "<<count<<endl;
    return "";

    //Deletes and free memory
    Node* temp;
    while(nodeQueue->size())
    {
        temp = nodeQueue->front();
        nodeQueue->pop();
        delete temp;
    }
    delete nodeQueue;

    //Zering pointers
    nodeQueue=0;
    temp=0;
    firstNode=0;
    nodeCatcher=0;
}

//This function implements...
string Agent::iterativeDepthSearch (int nuggetCount)
{
    return "";
}

//This function implements... 
string Agent::aStarSearch (int nuggetCount)
{
    return "";
}
