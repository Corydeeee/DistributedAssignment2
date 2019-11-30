//
//  wordutility.h
//  MapperX
//
//  Created by Warren Zajac on 2019-11-29.
//  Copyright © 2019 Zajac. All rights reserved.
//

#ifndef wordutility_h
#define wordutility_h

char* getCombinedFilename(char *fName) ;
char* getSortedFilename(char *fName) ;
char* getOutputFilename(char *fName) ;

int compareString(char *string1, char *string2) ;
char* copyString(char *inputString) ;
void analyzeWordsCount(char *fName) ;
char* sortWords(char *fName, int wordCount) ;
int parseWords(char *fName);


#endif /* wordutility_h */
