//
//  splitutility.c
//  C-MapReduce
//
//  Created by jeffrey on 1/12/15.
//  Copyright © 2015 jeffrey. All rights reserved.
//  Update by : Warren Zajac 2019

//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Put all GLOBAL variables here
 */
const int MAX_WORDS_PER_FILE = 545; // maximum words for split

char* getSplitFilename(int count) {
    char *splitName = "split_";
    //printf("%lu\n", strlen(splitName));
    
    char splitCount = 'a' + count % 26 ;
    //printf("%lu\n", sizeof(splitCount));
    
    char *fExt = ".txt";
    //printf("%lu\n", strlen(fExt));
    
    char *newName = (char *) malloc(strlen(splitName) + 4 + strlen(fExt)); //one for extra char, one for trailing zero
    //printf("%lu\n", strlen(newName));
    
    strcpy(newName, splitName);
    newName[strlen(splitName)] = splitCount;
    newName[strlen(splitName)+1] = 'a' + (count / 26);
    newName[strlen(splitName)+2] = '\0';
    strcat(newName, fExt);
    
    printf("%lu\n", strlen(newName));
    printf("--> %s\n", newName);
    
    return newName;
}

int splitfile(char *fNameInput) {
	FILE *fpIn;
    fpIn = fopen(fNameInput, "r");
    
    printf("splitfile(char *fNameInput)-- \n");
    
    // counter for number of split
    int splitCount = 1;
    // prepare the split file Handle
    FILE *fpOut;
    
    
    char *fNameSplit = getSplitFilename(splitCount);
    fpOut = fopen(fNameSplit, "w+");
    
    char temp;
    char *string = malloc(sizeof(char));
    int charCount = 0;
    int wordCount = 0;
    
    while ((temp = fgetc(fpIn)) != EOF) {
        //printf("[%c]\n", temp);
        
        if ( temp == ':' || temp == '\t' || temp == '\n' || temp == ' ' || temp == '?' || temp == ',' || temp == '.' || temp == '\"' ||
            temp == '!' || temp == '@' || temp == '~' || temp == '#' || temp == '$' || temp == '%' ||
            temp == '%' || temp == '^' || temp == '&' || temp == '*' || temp == '(' || temp == ')' ||
            temp == '-' || temp == '_' || temp == '{' || temp == '}' || temp == '[' || temp == ']' ||
            temp == '<' || temp == '>' || temp == '\r' || temp == '/' || temp == '\'' || temp == '`'
        ){
            if (charCount > 0) {
                string[strlen(string)] = '\0'; //add the null-termination character '\0'
                
                //printf("[%s]-->\n",string);
                
                wordCount ++;
                
                //printf("@@ write to split file: %s\n", getSplitFilename(splitCount));
                fprintf(fpOut, "%s\n", string);
                
                if (wordCount % MAX_WORDS_PER_FILE == 0) {
                    // need to split, increment the split counter by 1
                    splitCount++;
                    
                    // close the file handle and re-open to next split file
                    fclose(fpOut);
                    
                    free(fNameSplit);
                    
                    fNameSplit = getSplitFilename(splitCount);
                    fpOut = fopen(fNameSplit, "w+");
                    
                    
                }
                
                charCount = 0;
                free(string);
                string = calloc(0, sizeof(char));
            }
        } else {
            if (charCount == 0) {
                free(string);
                string = calloc(0, sizeof(char));
            }
            string[charCount] = temp;
            string[strlen(string)] = '\0'; //add the null-termination character '\0'
            charCount ++;
        }
    }

    fclose(fpIn);
    fclose(fpOut);
    
    usleep(100);

    free(string);
    free(fNameSplit);
    

    return(splitCount);
}

// === for Debug only!!! ===
//int main() {
//	int count = 0;
//	count = splitfile("input.txt");
//	printf("number of splits: %d\n", count);
//	exit(0);
//}
