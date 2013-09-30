/* IME-USP
** Mestrado em Ciência da Computação
** Disciplina: Inteligência Artificial
** Exercício-Programa 1 (Busca Informada)
** Alunos: 
** 	Monna Cleide Santos   - n. USP 8477852
** 	Victor Alberto Romero - n. USP 8405274
**
** 27 de setembro de 2013
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include "environment.h"

using namespace std;

void readInputFile(char* inputFileName, char** &matrix, int &n)
{
    FILE* fileIn = fopen (inputFileName, "r");
    
    // Read
    fscanf (fileIn, "%d", &n);

    //Inialize matrix
    matrix = new char*[n];
    for (int i=0; i<n; i++)
        matrix[i] = new char[n];

    char c;
    fscanf (fileIn, "%c", &c); //Because linebreak
    
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++){ 
            fscanf (fileIn, "%c", &c);
            matrix[i][j]=c;
        }
        fscanf (fileIn, "%c", &c); //Because linebreak
    }

    // Close file, and zering pointer
    fclose(fileIn);
    fileIn=0;
}

void printSolution(string solution, int n)
{
    int steps=0;
    int nuggets=0;

    for(int i=0; i<solution.size(); i++)
    {
        if(solution[i]!='P')
            steps++;
        else
            nuggets++;
    }

    cout<<(4*nuggets*n - steps)<<" pontos"<<endl;
    
    for(int i=0; i<solution.size(); i++)
        cout<<solution[i]<<" ";

    cout<<endl;
}

void printMatrixWithAgent(char** matrix, int n, int xAgent, int yAgent)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(i==xAgent && j==yAgent)
            {
                cout<<"@";
            }
            else
            {
                if(matrix[i][j]=='0')
                    cout<<' ';
                if(matrix[i][j]=='1')
                    cout<<'#';
                if(matrix[i][j]=='*')
                    cout<<'*';
            }
        }
        cout<<endl;
    }
}

void graphicSolution(string solution, char** matrix, int n)
{
    //The idea is graphic the moviment :)
    int xAgent=0;
    int yAgent=0;
    int usteepTime=200000;

    system("clear");
    printMatrixWithAgent(matrix, n, xAgent, yAgent);
    usleep(usteepTime);

    for(int i=0; i< solution.size(); i++)
    {
        if(solution[i]=='D') yAgent++;
        if(solution[i]=='E') yAgent--;
        if(solution[i]=='C') xAgent--;
        if(solution[i]=='B') xAgent++;
        if(solution[i]=='P') matrix[xAgent][yAgent]='0';

        system("clear");
        printMatrixWithAgent(matrix, n, xAgent, yAgent);
        usleep(usteepTime);
    }

    cout<<endl;
    printSolution(solution,n);
}

int main(int argc, char *argv[])
{
    int n;
    char** matrix;
    char* inputFileName;
    string extraOption(" ");
    string algorithmOption;

    // Correct number of parameters?
    if(argc<3)
    {
        printf("Incorrect number of parameters!\n");
        return 1;
    }
    inputFileName   = argv[1];
    algorithmOption = argv[2];
    readInputFile(inputFileName, matrix, n);

    //Only one more action: --i
    if(argc==4)
        extraOption = argv[3];
    
    // Processing
    Environment* env = new Environment(matrix, n);
    string solution = env->solveEnvironment(1);

    if(extraOption=="--i")
        graphicSolution(solution, matrix, n);
    else
        printSolution(solution, n);

    return 0;
}
