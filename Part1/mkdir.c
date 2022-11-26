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
        int m = mkdir(args[1], 0777);

        if(m == -1){
            printf("Directory already exists\n");
        }
    }

    else if(argc == 3){

        if(strcmp(args[1], "-v") == 0){
            int m = mkdir(args[2], 0777);

            if(m == -1){
                printf("Directory already exists\n");
            }

            else{
                printf("Created directory - %s\n", args[2]);
            }
        }

        else if(strcmp(args[1], "-p") == 0){
            
            char * path = args[2];
            char * current = strtok(path,"/");

            while(current != NULL){

                int m = mkdir(current,0777);
                if(m == -1){
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
