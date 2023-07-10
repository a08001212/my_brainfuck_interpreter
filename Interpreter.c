//
// Created by USER on 2023/7/10.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Interpreter.h"

int Interpreter(char *filename){
    char *fileString = openFile(filename);
    char *readFilePoint = fileString;
    char *workspace = calloc(1, WorkSpaceSize);
    char *workspacePoint = workspace;
    int nowWorkSpaceSize = WorkSpaceSize;
    while (*readFilePoint){
        // newline or space
        if(*readFilePoint == '\n' || *readFilePoint == ' ' || *readFilePoint == '\t' || *readFilePoint == '\r'){
            ++readFilePoint;
            continue;
        }else if(*readFilePoint == '+'){
            (*workspacePoint)++;
            ++readFilePoint;
        }else if(*readFilePoint == '-'){
            (*workspacePoint)--;
            ++readFilePoint;
        }else if(*readFilePoint == '.'){
//            printf("%d\n", *workspacePoint);
            printf("%c", *workspacePoint);
            ++readFilePoint;
        }else if(*readFilePoint == '>'){
            if(workspacePoint - workspace >= nowWorkSpaceSize){
                long long diff = workspacePoint - workspace;
                workspace = realloc(workspace, nowWorkSpaceSize + WorkSpaceSize);
                nowWorkSpaceSize += WorkSpaceSize;
                workspacePoint = workspace + diff;
            }
            ++workspacePoint;
            ++readFilePoint;
        }else if(*readFilePoint == '<'){
            if(workspacePoint == workspace){
                printf("Can't running < command in %lld char", readFilePoint - fileString);
                exit(2);
            }
            workspacePoint--;
            readFilePoint++;
        } else if(*readFilePoint == ','){
            *workspacePoint = (char)getchar();
            ++readFilePoint;
        }else if(*readFilePoint == '['){
            // has value at workspacePoint running loop
            if(*workspacePoint) {
                ++readFilePoint;
            }else{  // find ']' then exit loop
                while(*readFilePoint != ']'){
                    ++readFilePoint;
                }
                ++readFilePoint;
            }
        }else if(*readFilePoint == ']'){
            if(!(*workspacePoint)){
                ++readFilePoint;
                continue;
            }
            while(*readFilePoint != '['){
                --readFilePoint;

            }
        }else{
            printf("Unknown command %c\n", *readFilePoint);
            exit(2);
        }
    }
    free(fileString);
    free(workspace);
    return 0;
}

char* openFile(char *filename){

    FILE *fp;
    long lSize;
    char *buffer;

    fp = fopen ( filename , "rb" );
    if( !fp ) perror("blah.txt"),exit(1);

    fseek( fp , 0L , SEEK_END);
    lSize = ftell( fp );
    rewind( fp );

/* allocate memory for entire content */
    buffer = calloc( 1, lSize+1 );
    if( !buffer ) fclose(fp),fputs("memory alloc fails",stderr),exit(1);

/* copy the file into the buffer */
    if( 1!=fread( buffer , lSize, 1 , fp) )
        fclose(fp),free(buffer),fputs("entire read fails",stderr),exit(1);

/* do your work here, buffer is a string contains the whole text */

    fclose(fp);
//    free(buffer);
    return buffer;
}