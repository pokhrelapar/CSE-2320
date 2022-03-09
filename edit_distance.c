// Apar Pokhrel, 1001646558

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "edit_distance.h"

/*  Suggestions
- When you work with 2D arrays, be careful. Either manage the memory yourself, or
work with local 2D arrays. Note C99 allows parameters as array sizes as long as 
they are declared before the array in the parameter list. See: 
https://www.geeksforgeeks.org/pass-2d-array-parameter-c/

Worst case time complexity to compute the edit distance from T test words
 to D dictionary words where all words have length MaxLen:

Student answer:  Theta(T*D*MaxLen^(2))

*/

/* You can write helper functions here */

int findMin(int x, int y, int z)
{
	if((x<=y) && (x<=z) )
	{
		return x;
	}

	else if((y<=x) && (y<=z))
	{
		return y;

	}

	else
	{
		return z;
	}

}



int edit_distance(char * first_string, char * second_string, int print_table)
{
	// Dist: is the solution array

	int firstL = strlen(first_string);
	int secondL = strlen(second_string);
	int i,j,sLoop,k;
	int Dist[firstL+1][secondL+1];


		
	for (i = 0; i <= firstL; i++)
	{

		for (j = 0; j <= secondL; j++)
		{

			if (i == 0)
			{
				//base case : D(0,j) = j
				Dist[i][j] = j;

			}
			else if (j == 0)
			{
				//base case : D(i,0) = i
				Dist[i][j] = i;

			}
			else if (first_string[i - 1] == second_string[j - 1])
			{

				Dist[i][j] = Dist[i - 1][j - 1];

			}
			else
			{
				//down, left and diagonal
				Dist[i][j] = 1 + findMin(Dist[i][j-1],Dist[i-1][j], Dist[i-1][j-1]);

			}

		}

	}

	 // When to print the resulting matrix

	if (print_table == 1)
	{
		printf("  |   |");

		for (sLoop = 0; sLoop < strlen(second_string) ; sLoop++ ) 
		{
			printf("%3c|",second_string[sLoop]);
		}

		printf("\n");

		for(i=0; i <((secondL*4)+7);i++)
		{
			printf("-");
		}

		printf("\n");

		// pretty printing 

		for ( i = 0; i <= firstL; i++ )
 	    {

 		   for (j = 0; j <= secondL; j++)
 		   {

 			   if( i == 0 && j == 0)
 			   {
 				   printf("  |");
 			   }


 			   else if(i !=0 && j == 0)
 			   {
 				   printf(" %c|",first_string[i-1]);

 			   }

 				printf("%3d|",Dist[i][j]);
 		   }
 		   

 		   printf("\n");

 		   for ( k = 0 ; k < ((secondL * 4) + 7 ) ; k++)
 		   {
 			   printf("-");
 		   }



 		   printf("\n");
 	    }

	}

	return Dist[firstL][secondL];

}



	  
void spellcheck(char * dictname, char * testname)
{
	char buffer[101];
	char buffer1[101];
	
	
	int result[1000];

	int dictWords,testWords;
	int  l, m, n;
	int  editDistance, counter, compare;
	int y;

	FILE *Dict = fopen(dictname,"r");
	FILE *Test = fopen(testname,"r");

	if(Dict == NULL || Test == NULL)
	{
		perror("File cound not be opened!");
        exit(EXIT_FAILURE);

	}

	else
	{
		printf("\nLoading the dictionary file:%s\n",dictname);
		printf("Loading the dictionary file:%s\n",testname);

	}
	


	// Getting # of words from first file
	fscanf(Dict, "%d", &dictWords);

	int dic[dictWords];
	char *dictValues[dictWords];

	for(l=0; l < dictWords; l++)
	{
		fscanf(Dict,"%s", buffer);

		char *dicW = (char*) malloc((strlen(buffer)+1) * sizeof(char));
		strcpy(dicW,buffer);
		dictValues[l] = dicW;
 
	}

    fclose(Dict);

	
	

	// Getting # of words from second file
	fscanf(Test, "%d", &testWords);
	char *testValues[testWords];

	for(l=0; l< testWords; l++)
	{
		fscanf(Test,"%s", buffer1);

		char *testW = (char*) malloc((strlen(buffer1)+1) * sizeof(char));
		strcpy(testW,buffer1);
		testValues[l] = testW;

	}

    fclose(Test);


	for(l =0; l< testWords; l++)
	{

		for(m =0; m < dictWords; m++)
		{
			compare = edit_distance(testValues[l],dictValues[m],-1);
			dic[m] = compare;

		}

		editDistance = dic[0];

		for(m=1; m < dictWords;m++)
		{
				if(dic[m] < editDistance)
				{
					editDistance = dic[m];

				}

		}

		printf("\n------- Current test word = %s\n", testValues[l]);
		printf("Minimum distance = %d\n", editDistance);
		printf("Words that give minimum distance:");

		for(m = 0 ; m < dictWords ; m++)
       	{
				if(dic[m] == editDistance)
				{
					printf("%s\n",dictValues[m]);
				}
       	}

	}


	for(y = 0 ; y < dictWords; y++)
	{
		free(dictValues[y]);
	}

	for(y = 0 ; y < testWords; y++)
	{
		free(testValues[y]);
	}





	
    

//	res(dictValues,dictWords);
//	res(testValues, testWords);


}
