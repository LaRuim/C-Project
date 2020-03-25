#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "./Stemmer.h"

#define MAX 100
#define MAX2 1000

char** readFile (char *, char**);
unsigned long int hashstring(unsigned char *str);
int dotproduct(int*, int*);
float rootsquaresum(int*);

int main(void){
    char filename[MAX];
    char *tab1[MAX2];
    char *tab2[MAX2];

    int bag1[524288] = {0};
    int bag2[524288] = {0};

    printf("Enter filename 1: ");
    scanf("%s", filename);
    char **words1 = readFile(filename, tab1);
    for (int i = 0; *(words1+i) != NULL; i++){
        char* word = stem(*(words1+i));
        //printf("%s ", word);
        unsigned long int index = hashstring(word);
        bag1[index]++;
    }

    printf("Enter filename 2: ");
    scanf("%s", filename);

    char **words2 = readFile(filename, tab2);
    for (int i = 0; *(words2+i) != NULL; i++){
        char* word = stem(*(words2+i));
        //printf("%s ", word);
        unsigned long int index = hashstring(word);
        bag2[index]++;
    }

    double similarity = (dotproduct(bag1, bag2))/(rootsquaresum(bag1)*rootsquaresum(bag2));

    printf("\nSimilarity Score: %f\n", similarity);
}

char** readFile (char *file, char** tab){
    int i = 0;
    int n = 1000;

    char line [1000];
    char *str[1000];
    const char s[2] = " ";
    char *token;
    FILE *myFile;
    char S[100] = "./SampleTexts/";
    char File[100];
    strcpy(File, file);
    strcat(S, File);
    myFile = fopen(S, "r");

    if(!myFile){
        printf("could not open file");
    }
    else{
        //printf("file opened\n");
        fgets(line,sizeof line,myFile);
        token = strtok(line, s);

        for(i = 0; (i < n) && (token != NULL); i++){
            int len = strlen(token);
            tab[i] = malloc(len);
            strncpy(tab[i], token, len);
            token = strtok(NULL, s);
            //printf( "%s\n", tab[i]);
        }
    }

    fclose(myFile);

    return tab;
}


unsigned long int hashstring(unsigned char *str){
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return (hash % 524288);
}


int dotproduct(int* a, int* b){
    int sum = 0;
    for (int i = 0; i < 524288; i++){
        sum += a[i] * b[i];
    }
    return sum;
}

float rootsquaresum(int* a){
    int sum = 0;
    for (int i = 0; i < 524288; i++){
        sum += a[i] * a[i];
    }
    double d = sqrt(sum);
    return d;
}