/* IME-USP
** Mestrado em Ciência da Computação
** Disciplina: Inteligência Artificial
** Exercício-Programa 1 (Busca Informada)
** Alunos: 
** 	Monna Cleide Santos - n. USP 8477852
** 	Victor Alberto Romero - n. USP XXXXXXX
**
** 27 de setembro de 2013
*/

#include<iostream>
#include <stdio.h>

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
            //cout<<"Read: "<<c<<endl;
        }
        fscanf (fileIn, "%c", &c); //Because linebreak
    }

    // Close file, and zering pointer
    fclose(fileIn);
    fileIn=0;
}

int main(int argc, char *argv[])
{
    int n;
    char** matrix;

    // Correct number of parameters?
    if(argc<2)
    {
        printf("Incorrect number of parameters!\n");
        return 1;
    }
    char* inputFileName  = argv[1];
    readInputFile(inputFileName, matrix, n);
                    
    // Processing
    cout<<"The read data was:"<<endl<<endl;
    cout<<n<<endl;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }

    return 0;
}
