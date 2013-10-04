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

//################ Color definitions #######################//
const string consoleReset     = "\033[0m";

// Color bold
const string blackBold  = "\033[1;30m";
const string redBold    = "\033[1;31m";
const string greenBold  = "\033[1;32m";
const string yellowBold = "\033[1;33m";
const string blueBold   = "\033[1;34m";
const string purpleBold = "\033[1;35m";
const string cyanBold   = "\033[1;36m";
const string grayBold   = "\033[1;37m";

// Background color
const string blackBackground  = "\033[40m";
const string redBackground    = "\033[41m";
const string greenBackground  = "\033[42m";
const string yellowBackground = "\033[43m";
const string blueBackground   = "\033[44m";
const string purpleBackground = "\033[45m";
const string cyanBackground   = "\033[46m";
const string grayBackground   = "\033[47m";
//##########################################################//

void readInputFile(char* inputFileName, char** &matrix, int &n)
{
    char c;
    FILE* fileIn = fopen (inputFileName, "r");
    fscanf (fileIn, "%d", &n);

    //Inialize matrix
    matrix = new char*[n];
    for (int i=0; i<n; i++)
        matrix[i] = new char[n];

    fscanf (fileIn, "%c", &c); //Because linebreak
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        { 
            fscanf (fileIn, "%c", &c);
            matrix[i][j]=c;
        }
        fscanf (fileIn, "%c", &c); //Because linebreak
    }

    // Close file, and zering pointer
    fclose(fileIn);
    fileIn=0;
}

void printSolution(string solution, int points)
{
    cout<<points<<" pontos"<<endl;

    for(int i=0; i<solution.size(); i++)
        cout<<solution[i]<<" ";

    cout<<endl;
}

void printMatrixWithAgent(char** matrix, int n, int xAgent, int yAgent, bool color)
{
    string console = "";
    string agent   = "@";
    string nugget  = "*";
    string wall    = "#";
    string limit   = "$";
    string path    = " ";

    if(color) //Define the string in color choise
    {
        console = consoleReset;
        agent   = consoleReset + cyanBold + "@";
        nugget  = consoleReset + redBold + "*";
        wall    = consoleReset + grayBackground + " ";
        limit   = consoleReset + blueBackground + " ";
        path    = consoleReset + " ";
    }

    for(int i=-1; i<=n; i++)// -1 to n because the print of border
    {
        for(int j=-1; j<=n; j++)// -1 to n because the print of border
        {
            if(i<0 || j<0 || i==n || j==n) //if it's in the border
                cout<<limit;
            else
            {
                if(i==xAgent && j==yAgent) //print the agent position
                    cout<<agent;
                else
                {
                    if(matrix[i][j]=='0') cout<<path;
                    if(matrix[i][j]=='1') cout<<wall;
                    if(matrix[i][j]=='*') cout<<nugget;
                }
            }
        }
        cout<<console<<endl; //print the linebreaak
    }
}

void graphicSolution(string solution, int points, char** matrix, int n, bool color)
{
    int xAgent=0;
    int yAgent=0;
    int usteepTime=50000;

    for(int i=0; i<= solution.size(); i++) //print the moviments and initial state
    {
        system("clear");
        printMatrixWithAgent(matrix, n, xAgent, yAgent, color);
        usleep(usteepTime);
       
        if(i<solution.size())//if has more moviments
        {
            if(solution[i]=='D') yAgent++;
            if(solution[i]=='E') yAgent--;
            if(solution[i]=='C') xAgent--;
            if(solution[i]=='B') xAgent++;
            if(solution[i]=='P') matrix[xAgent][yAgent]='0';//delete the nugget
        }
    }
    cout<<endl;
    printSolution(solution,points);
}

int main(int argc, char *argv[])
{
    int n;
    int algorithmOption;
    bool color=false;
    bool graphic=false;
    char** matrix;
    char* inputFileName;

    // Minimum number of parameters?
    if(argc<3)
    {
        printf("Don't have the minimum  number of parameters!\n");
        return 1;
    }

    //Read file
    inputFileName = argv[1];
    readInputFile(inputFileName, matrix, n);

    //Capture the Algorithm Options
    if(string(argv[2]) == "L") algorithmOption = 1;
    if(string(argv[2]) == "P") algorithmOption = 2;
    if(string(argv[2]) == "A") algorithmOption = 3;

    // Extra options
    for(int i=3; i<argc; i++)
    {
        if(string(argv[i]) == "--c") color=true;
        if(string(argv[i]) == "--g") graphic=true;
    }

    // Processing
    Environment* env = new Environment(matrix, n);
    string solution = env->solveEnvironment(algorithmOption);
    int points = env->evalSolution(solution);

    // Print the solution
    if(graphic) graphicSolution(solution, points, matrix, n, color);
    else        printSolution(solution, points);

    //Deletes and free memory
    for(int i=0; i<n; i++) delete matrix[i];
    delete matrix;
    delete env;

    return 0;
}
