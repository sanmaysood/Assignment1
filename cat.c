#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char ** args){
    
    FILE *fp;

    if(argc == 2){

        fp = fopen(args[1], "r");

        if(fp == NULL){
            printf("cat : %s : No such file or directory\n", args[1]);
        }

        else{

            char data1[1024];
            while(fgets(data1, 1024, fp) != NULL){
                printf("%s", data1);
            }
        }

        fclose(fp);
    }

    else if(argc == 3){

        if(strcmp(args[1], "-n") == 0){

            fp = fopen(args[2], "r");
            if(fp == NULL){
                printf("cat : %s : No such file or directory\n", args[2]);
            }

            else{

                char data2[1024];
                int i = 1;
                while(fgets(data2, 1024, fp) != NULL){
                    printf("%d %s", i, data2);
                    i++;
                }
            }

            fclose(fp);
        }

        else if(strcmp(args[1], "-E") == 0){
            fp = fopen(args[2], "r");

            if(fp == NULL){
                printf("cat : %s : No such file or directory\n", args[2]);
			}

            else{
                char data3[1024];

                while(fgets(data3, 1024, fp) != NULL){
                    char newstr[1000];
                    int ind = 0;

                    for(int i=0; i < strlen(data3)-1 ;i++){
                    
                        newstr[ind++] = data3[i];

                    }
                    printf("%s$\n", newstr);
                }
            }

            fclose(fp);
        }

        else{
            printf("cat : invalid option -- '%s'\n", args[1]);
			printf("Try 'cat --help' for more information.\n");
		}

    }
    return 0;
}

