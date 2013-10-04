/* IME-USP
** Mestrado em Ciência da Computação
** Disciplina: Inteligência Artificial
** Exercício-Programa 1 (Busca Informada)
** Alunos: 
** 	    Monna Cleide Santos   - n. USP 8477852
** 	    Victor Alberto Romero - n. USP 8405274
**
** 4 de outobro de 2013
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
            nodeTemp->nuggetCaughtCount++;
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
    //Create the auxiliar variables
    Node* nodeCatcher;
    totalSet->clear();
    int pathSize;
    int nuggetCaughtCount;
    int maxProfit = nuggetCount*matrixSize*4;
    int count=0;
	
    //Create the principal structure
    queue<Node*>* nodeQueue = new queue<Node*>();
	Node* firstNode = new Node(nuggetCaughtInitial, nuggetTotal, 0, 0, "");
	nodeQueue->push(firstNode); // Put the initial node

	while(!nodeQueue->empty())
    {
        // Capture the node
		nodeCatcher = nodeQueue->front();
		nodeQueue->pop();
        pathSize = nodeCatcher->path.size(); 
        nuggetCaughtCount = nodeCatcher->nuggetCaughtCount;

        // If it is a usefull node
        if(totalSet->count(nodeCatcher->state2String())==0 && (pathSize-nuggetCaughtCount)<maxProfit)
        {
            if(isNodeASolution(nodeCatcher, nuggetCount)) // If it is a solution
            {
                cout<<"Expanded nodes for "<<nuggetCount<<" nuggets objective: "<<count<<endl;
                return nodeCatcher->path; 
            }
            else
                expandChildren(nodeCatcher, nodeQueue); // Expand the children
            
            totalSet->insert(nodeCatcher->state2String()); // Remember this node
        }
        count++;
        delete nodeCatcher;
    }
    cout<<"Expanded nodes for "<<nuggetCount<<" nuggets objective: "<<count<<endl;
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

string Agent::depthSearch (int nuggetCount)
{
    int limit = 2*matrixSize*matrixSize; //###### who define this?

    //Create the auxiliar variables
    queue<Node*>* auxiliarQueue = new queue<Node*>();
    Node* nodeCatcher;
    totalSet->clear();
    int pathSize;
    int nuggetCaughtCount;
    int maxProfit = nuggetCount*matrixSize*4;
    int count=0;
	
    //Create the principal structure
    stack<Node*>* nodeStack = new stack<Node*>();
	Node* firstNode = new Node(nuggetCaughtInitial, nuggetTotal, 0, 0, "");
	nodeStack->push(firstNode); // Put the initial node

	while(!nodeStack->empty())
    {
        // Capture the node
		nodeCatcher = nodeStack->top();
		nodeStack->pop();
        pathSize = nodeCatcher->path.size(); 
        nuggetCaughtCount = nodeCatcher->nuggetCaughtCount;

        // If it is a usefull node
        if(totalSet->count(nodeCatcher->state2String())==0 && (pathSize-nuggetCaughtCount)<maxProfit && pathSize<limit)
        {
            if(isNodeASolution(nodeCatcher, nuggetCount)) // If it is a solution
            {
                cout<<"Expanded nodes for "<<nuggetCount<<" nuggets objective: "<<count<<endl;
                return nodeCatcher->path; 
            }
            else
            {
                expandChildren(nodeCatcher, auxiliarQueue); // Expand the children
                while(auxiliarQueue->size())
                {
                    nodeStack->push(auxiliarQueue->front());
                    auxiliarQueue->pop();
                }
            }
            totalSet->insert(nodeCatcher->state2String()); // Remember this node
        }
        count++;
        delete nodeCatcher;
    }
    cout<<"Expanded nodes for "<<nuggetCount<<" nuggets objective: "<<count<<endl;
    return "";

    //Deletes and free memory
    Node* temp;
    while(nodeStack->size())
    {
        temp = nodeStack->top();
        nodeStack->pop();
        delete temp;
    }
    delete nodeStack;
    delete auxiliarQueue;

    //Zering pointers
    auxiliarQueue=0;
    nodeStack=0;
    temp=0;
    firstNode=0;
    nodeCatcher=0;
    return "";
}

//This function implements... 
string Agent::aStarSearch (int nuggetCount)
{
    return "";
}
