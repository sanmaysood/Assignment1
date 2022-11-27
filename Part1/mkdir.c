# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>


int main(int argc, char ** args){

    if(argc == 1){
        printf("No arguments passed\n");
    }

    else if(argc == 2){
        int m1 = mkdir(args[1], 0777);

        if(m1 == -1){
            printf("Directory already exists\n");
        }
    }

    else if(argc == 3){

        if(strcmp(args[1], "-v") == 0){
            int m2 = mkdir(args[2], 0777);

            if(m2 == -1){
                printf("Directory already exists\n");
            }

            else{
                printf("Created directory - %s\n", args[2]);
            }
        }

        else if(strcmp(args[1], "-p") == 0){
            char * path = (char *) malloc(128 * sizeof(char));
            path = args[2];
            char * current  = (char *) malloc(128 * sizeof(char));
            current = strtok(path,"/");

            while(current != NULL){

                int m3 = mkdir(current,0777);
                if(m3 == -1){
                    printf("Directory already exists\n");
                }
                
                chdir(current);
                current = strtok(NULL,"/");
                
            }
        }

        else{
            printf("Invalid command\n");
        }
    }

    else{
        printf("Too many arguments\n");
    }

    return 0;
}
