/* IME-USP
** Mestrado em Ciência da Computação
** Disciplina: Inteligência Artificial
** Exercício-Programa 1 (Busca Informada)
** Alunos: 
** 	    Monna Cleide Santos   - n. USP 8477852
** 	    Victor Alberto Romero - n. USP 8405274
**
** 4 de outubro de 2013
*/

#include "agent.h"

#include <iostream> //###################################### temporal!!
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

string Agent::widthSearch (int nuggetCount)
{
    //Create the auxiliar variables
    Node* nodeCatcher;
    totalSet->clear();
    int pathSize;
    int nuggetCaughtCount;
    int maxProfit = nuggetCount*matrixSize*4;
    int count=0;
    string solution="";
    bool hasSolution=false;
	
    //Create the principal structure
    queue<Node*>* nodeQueue = new queue<Node*>();
	Node* firstNode = new Node(nuggetCaughtInitial, nuggetTotal, 0, 0, "");
	nodeQueue->push(firstNode); // Put the initial node

	while(!nodeQueue->empty() && !hasSolution)
    {
        // Capture the node
		nodeCatcher = nodeQueue->front();
		nodeQueue->pop();
        pathSize = nodeCatcher->path.size(); 
        nuggetCaughtCount = nodeCatcher->nuggetCaughtCount;

        // If it is a usefull node
        if(totalSet->count(nodeCatcher->state2String())==0 && (pathSize-nuggetCaughtCount)<maxProfit)
        {
            if(nodeCatcher->isSolution(nuggetCount)) // If it is a solution
            {
                hasSolution=true;
                solution = nodeCatcher->path; 
            }
            else
                nodeCatcher->expandChildren(nodeQueue, matrix, matrixSize, idXNuggets, idYNuggets); // Expand the children
            
            totalSet->insert(nodeCatcher->state2String()); // Remember this node
        }
        count++;
        delete nodeCatcher;
    }

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

    cout<<"Expanded nodes for "<<nuggetCount<<" nuggets objective: "<<count<<endl;
    
    if(hasSolution) return solution;
    else            return "";
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
    string solution="";
    bool hasSolution=false;
	
    //Create the principal structure
    stack<Node*>* nodeStack = new stack<Node*>();
	Node* firstNode = new Node(nuggetCaughtInitial, nuggetTotal, 0, 0, "");
	nodeStack->push(firstNode); // Put the initial node

	while(!nodeStack->empty() && !hasSolution)
    {
        // Capture the node
		nodeCatcher = nodeStack->top();
		nodeStack->pop();
        pathSize = nodeCatcher->path.size(); 
        nuggetCaughtCount = nodeCatcher->nuggetCaughtCount;

        // If it is a usefull node
        if(totalSet->count(nodeCatcher->state2String())==0 && (pathSize-nuggetCaughtCount)<maxProfit && pathSize<limit)
        {
            if(nodeCatcher->isSolution(nuggetCount)) // If it is a solution
            {
                hasSolution=true;
                solution = nodeCatcher->path; 
            }
            else
            {
                nodeCatcher->expandChildren(auxiliarQueue, matrix, matrixSize, idXNuggets, idYNuggets); // Expand the children
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
    
    cout<<"Expanded nodes for "<<nuggetCount<<" nuggets objective: "<<count<<endl;
    
    if(hasSolution) return solution;
    else            return "";
}

string Agent::aStarSearch (int nuggetCount)
{
    //Create the auxiliar variables
    queue<Node*>* auxiliarQueue = new queue<Node*>();
    Node* nodeCatcher;
    totalSet->clear();
    int pathSize;
    int nuggetCaughtCount;
    int maxProfit = nuggetCount*matrixSize*4;
    int count=0;
    string solution="";
    bool hasSolution=false;
	
    //Create the principal structure
    pqNode* nodeQueue = new pqNode();
	Node* firstNode = new Node(nuggetCaughtInitial, nuggetTotal, 0, 0, "");
	nodeQueue->push(firstNode); // Put the initial node

	while(!nodeQueue->empty() && !hasSolution)
    {
        // Capture the node
		nodeCatcher = nodeQueue->top();
		nodeQueue->pop();
        pathSize = nodeCatcher->path.size(); 
        nuggetCaughtCount = nodeCatcher->nuggetCaughtCount;

        // If it is a usefull node
        if(totalSet->count(nodeCatcher->state2String())==0 && (pathSize-nuggetCaughtCount)<maxProfit)
        {
            if(nodeCatcher->isSolution(nuggetCount)) // If it is a solution
            {
                hasSolution=true;
                solution = nodeCatcher->path; 
            }
            else
            {
                nodeCatcher->expandChildren(auxiliarQueue, matrix, matrixSize, idXNuggets, idYNuggets); // Expand the children
                while(auxiliarQueue->size())
                {
                    auxiliarQueue->front()->calculeHeuristic(nuggetCount, idXNuggets, idYNuggets);
                    nodeQueue->push(auxiliarQueue->front());
                    auxiliarQueue->pop();
                }
            }
            totalSet->insert(nodeCatcher->state2String()); // Remember this node
        }
        count++;
        delete nodeCatcher;
    }

    //Deletes and free memory
    Node* temp;
    while(nodeQueue->size())
    {
        temp = nodeQueue->top();
        nodeQueue->pop();
        delete temp;
    }
    delete nodeQueue;
    delete auxiliarQueue;

    //Zering pointers
    auxiliarQueue=0;
    nodeQueue=0;
    temp=0;
    firstNode=0;
    nodeCatcher=0;
    
    cout<<"Expanded nodes for "<<nuggetCount<<" nuggets objective: "<<count<<endl;
    
    if(hasSolution) return solution;
    else            return "";
}
