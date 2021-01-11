#include <bits/stdc++.h> 
using namespace std; 

#define MAX 4
int rowA=0;
int colA=0;
int i=0,j=0,k=0;
int setp_i = 0;
typedef struct parameters {
    int x,y,i,j;
}args;
int MAX_THREAD;
int step_i = 0; 
string line;
ifstream myfile;

char loc[25];
FILE *output;
int numb; 
int x;
int y;
int arrayA[100][100] = {{0}};
int arrayB[100][100] = {{0}};
int arrayC[100][100] = {{0}};
void* multi(void* arg)
{
	int core = step_i++;
	if(MAX_THREAD == 1){
	for(i=0;i<3;i++)
        {
                for(j=0;j<3;j++)
                {

                        for(k=0;k<3;k++)
                        {
                               arrayC[i][j]+=arrayA[i+1][k]*arrayB[k][j];
                        }
               }
        }
	}else{
        for(i=core*MAX / 4;i<(core+1)*MAX/4;i++)
        {
                for(j=0;j<MAX;j++)
                {

                        for(k=0;k<MAX;k++)
                        {
                               arrayC[i][j]+=arrayA[i+1][k]*arrayB[k][j];
                        }
               }
        }
	}
pthread_exit(NULL);
} 
   
int main(int argc, char *argv[]) 
{
if(argv[3] != NULL){
     MAX_THREAD = atoi(argv[3]);
    } else{
      MAX_THREAD = 4;
    }

if(argc < 3){
     puts("Not enough arguments.");
     puts("parallelCopy sourceFile targetFile");
     return -1;
}

//reading arguments
strcpy(loc, argv[1]);
myfile.open(loc);

strcpy(loc, argv[2]);
output=fopen(loc,"w");
{
        if(myfile.fail())
{
cerr<<"file does not exist";

}
while(myfile.good())
{
while(getline(myfile,line))
{
istringstream stream(line);
colA=0;
while(stream >> x)
{
arrayA[rowA][colA]=x;
colA ++;
}
rowA ++;
}
}
//reading matrix from file 
for(i=0;i<=2;i++)
        {
                for(j=0;j<=2;j++)
                {
                        arrayB[i][j] = arrayA[i+5][j];
                }
        }
 
    // declaring four threads 
    pthread_t threads[MAX_THREAD]; 
  
    // Creating four threads, each evaluating its own part 
    for (int i = 0; i < MAX_THREAD; i++) { 
        int* p;	
       pthread_create(&threads[i], NULL, multi, (void *)p);
       pthread_join(threads[i], NULL);
       cout << "count of threads : " << i+1 << endl;	
    }
  
    // Displaying the result matrix 
    cout << endl 
         << "Multiplication of A and B" << endl; 
    for (int i = 0; i < 3; i++) { 
        for (int j = 0; j < 3; j++)  
            cout << arrayC[i][j] << "  ";         
        cout << endl; 
    }
//print multiplication in the destination file
for(i=0;i<3;i++)
        {
                for(j=0;j<3;j++)
                {
                        fprintf(output,"%d  ",arrayC[i][j]);

                        if(j==2){
                                fprintf(output,"\n");
                        }
                }
        }

    return 0; 

}
}

