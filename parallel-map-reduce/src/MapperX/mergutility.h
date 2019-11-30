//
//  mergutility.h
//  MapperX
//
//  Created by Warren Zajac on 2019-11-29.
//  Copyright © 2019 Zajac. All rights reserved.
//

#ifndef mergutility_h
#define mergutility_h



char* getMergeTaskName(int recordIndex) ;
char* generateMergeTask(char *inputArray) ;
void initializeMergeTask(int inputSize) ;
int getTotalMergeTask(int inputSize) ;

char* getFilename(char* param1, char* param2) ;

int getNumberOfWordsInFile(char *fName) ;
void mergeFiles(char *mergeTask);



#endif /* mergutility_h */
