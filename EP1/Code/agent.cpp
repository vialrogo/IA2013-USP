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

#include "agent.h"

Agent::Agent(char** matrixIn, int matrixSizeIn)
{
    matrix = matrixIn;
    matrixSize = matrixSizeIn;
    nuggetTotal = matrixSize/2;

    nuggetCachedInitial = new bool[nuggetTotal];
    for(int i=0; i<nuggetTotal; i++)
        nuggetCachedInitial[i] = true; //true means that the nugget is there
}

Agent::~Agent()
{
    delete nuggetCachedInitial;
    nuggetCachedInitial=0;
}

string Agent::widthSearch (int nuggetCount)
{
	//This function implements the width-search methods.

	queue<Node*>* nodeQueue = new queue<Node*>();
	Node* firstNode = new Node(nuggetCachedInitial, nuggetTotal, 0, 0);
	nodeQueue->push(firstNode);

	while(!nodeQueue->empty()) {
		// "catching" the top element of the queue
		Node* nodeCatcher = nodeQueue->front();
		nodeQueue->pop();

		// if (nuggetCount)

	}

}

string Agent::iterativeDepthSearch (int nuggetCount)
{
	//This function implements...
    return "";
}

string Agent::aStarSearch (int nuggetCount)
{
    //This function implements... 
    return "";
}
