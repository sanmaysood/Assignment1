#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char ** args){
    
    FILE *fp;
    if(argc == 1){
        printf("No arguments passed\n");
    }

    else if(argc == 2){

        fp = fopen(args[1], "r");

        if(fp == NULL){
            printf("File not found\n");
        }

        else{

            char data[1024];
            while(fgets(data, 1024, fp) != NULL){
                printf("%s", data);
            }
        }

        fclose(fp);
    }

    else if(argc == 3){

        if(strcmp(args[1], "-n") == 0){

            fp = fopen(args[2], "r");
            if(fp == NULL){
                printf("File not found\n");
            }

            else{
                char data[1024];
                int i = 1;
                while(fgets(data, 1024, fp) != NULL){
                    printf("%d %s", i, data);
                    i++;
                }
            }

            fclose(fp);
        }

        else if(strcmp(args[1], "-E") == 0){
            fp = fopen(args[2], "r");

            if(fp == NULL){
                printf("File not found\n");
            }

            else{
                char data[1024];

                while(fgets(data, 1024, fp) != NULL){
                    char newstr[1000];
                    int ind = 0;

                    for(int i=0; i < strlen(data)-1 ;i++){
                    
                        newstr[ind++] = data[i];

                    }
                    printf("%s$\n", newstr);
                }
            }

            fclose(fp);
        }

        else{
            printf("Invalid command\n");
        }
    }

    else{
        printf("Too many arguments passed\n");
    }

    return 0;
}


