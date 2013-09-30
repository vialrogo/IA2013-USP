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

string Agent::widthSearch (char** Matrix, int matrixSize, int nuggetCount) {
	//This function implements the width-search methods.

	queue<Node*>* nodeQueue = new queue<Node*>();
	Node* firstNode = new Node(Matrix, matrixSize, 0, 0);
	nodeQueue->push(firstNode);

	while(!nodeQueue->empty()) {
		// "catching" the top element of the queue
		Node* nodeCatcher = nodeQueue->front();
		nodeQueue->pop();

		if (nuggetCount)		



	}

}

string Agent::iterativeDepthSearch (char** Matrix, int matrixSize, int nuggetCount) {
	//This function implements...
    return "";
}

string Agent::aStarSearch (char** Matrix, int matrixSize, int nuggetCount) {
    //This function implements... 
    return "";
}
