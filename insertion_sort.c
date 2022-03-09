/**
 * @author [Apar Pokhre;]
 * @email [apu8467@gmail.com]
 * @create date 2020-02-21 19:25:14
 * @modify date 2020-02-21 19:25:14
 * @desc [description]
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int comp_length(const char *leftStr, const char *rightStr )	
{

    return(strlen(leftStr)- strlen(rightStr));  
	
}


int comp_mixt(const char *leftStr, const char *rightStr )	
{	

    if(strlen(leftStr)== strlen(rightStr))
    {
        return strcmp(leftStr,rightStr);
       
    }

    else
    {
        return comp_length(leftStr,rightStr);
    }

}



int comp_greater(const char *leftStr, const char *rightStr )	
{	
	return -strcmp(leftStr, rightStr);
}


void printData(char **data, int counter)
{
    int k=0;
     for(k=0;  k < counter; k++)
    {
        printf("%s\n",data[k]);

    }

}



void res(char** a, int size)
{
    int z = 0;
     for ( z = 0; z < size; z++)
    {
        free(a[z]);
    }

    free(a);

}


void generic_sort(char **file, int size, int given_func(const char *leftStr, const char *rightStr))
{

    int i, j;
    char *value;

    for (i = 1; i < size; i++)
    { 
        value = file[i]; 
        j = i - 1; 
  
        while (j >= 0 && given_func(value,file[j])<0)
        {

            file[j + 1] = file[j]; 
            j = j - 1; 
        } 

        file[j + 1] = value; 
    } 
}





int main(int argc, char** argv[])
{

    FILE *readFile;

    char fileName[101];
    char buffer[101];
    char currentC;
    char **data = NULL;

   

    int lineLen=0;
    int counter = 0;
    int Lines=0;
    int temp=0;
    int totalChar = 0;
    int totalBytes = 0;
    int i = 0;
    
    printf("\n");
    printf("Enter the filename: ");
    scanf("%s", fileName);

    readFile = fopen(fileName,"r");

    if(readFile == NULL)
    {
        printf("Could not open file %s\n",fileName);
        printf("Exiting program.......\n");
        exit(EXIT_FAILURE);

    }

    //while (fgets(buffer,sizeof(buffer),readFile)) 
    while (fscanf(readFile,"%s",buffer)!=EOF) 
	{

        data = realloc(data,(counter+1) * sizeof(char *));
        lineLen = (strlen(buffer));
        data[counter] = calloc(sizeof(char),lineLen+1);

         //data[counter] = malloc(lineLen+1);

        strcpy(data[counter],buffer);

        // printf("%d characters in line %d \n",lineLen,counter);

        counter++;

    }


    
    

    fclose(readFile);

    Lines = counter;

    readFile = fopen(fileName,"r");

    while((currentC = fgetc(readFile))!= EOF)
    {
        if(currentC == '\n')
        {
            temp++;    
        }
        else
        {
            totalChar++;
            
        }  

    }



    // size of pointer = 8 bytes       size of char  = 1 byte
    totalBytes = ((Lines)*8) + ((totalChar+1)*1);

    printf("\n Data is loaded");    
    printf("\n Allocated space for storing the data: %7d B ( %d char and %d pointers)",totalBytes, totalChar+1, Lines);
    printf("\n Pointer size: %d Bytes\n", sizeof(void*));

    printf("\nOriginal data: \n");
    printData(data,counter);
     
    
    printf("\n\n--------  compare by LENGTH only --------------\n");
    generic_sort(data, counter,comp_length);
    printData(data,counter);

    
    printf("\n\n--------  compare by strcmp --------------\n");    
    generic_sort(data, counter,strcmp);
    printData(data,counter);

    printf("\n\n--------  compare by GREATER --------------\n");
    generic_sort(data, counter,comp_greater);
    printData(data,counter);
     
    printf("\n--------  compare by LENGTH and lexicografic --------------\n");    
    generic_sort(data, counter,comp_mixt);
    printData(data,counter);
    printf("\n\n");



     fclose(readFile);
     res(data,counter);
   

    return 0;


}



