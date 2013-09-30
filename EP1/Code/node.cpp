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

// construct
Node::Node(char** matrixIn, int matrixSizeIn, int agentOnXIn, int agentOnYIn) {
	matrix = matrixIn;
	matrixSize = matrixSizeIn;
	agentOnX = agentOnXIn;
	agentOnY = agentOnYIn;
}

// destruct
Node::~Node() {
	
}