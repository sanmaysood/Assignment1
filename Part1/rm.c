# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>


int main(int argc, char ** args){

    if(argc == 1){
        perror("No arguments passed\n");
    }
    else if(argc == 2){
        int r = remove(args[1]);
        if(r == -1){
            perror("File not found\n");
        }
    }
    else if(argc == 3){
        if(strcmp(args[1], "-i") == 0){
            printf("Are you sure you want to delete this file - %s? (y/n): \n", args[2]);
            char c;
            scanf("%c", &c);
            if(c == 'y'){
                int r = remove(args[2]);
                if(r == -1){
                    perror("File not found\n");
                }
            }
        }
        else if(strcmp(args[1], "-v") == 0){
            int r = remove(args[2]);
            if(r == -1){
                perror("File not found\n");
            }
            else{
                printf("Removed this file - %s\n", args[2]);
            }
        }
        else{
            perror("Invalid command\n");
        }
    }
    else{
        perror("Too many arguments\n");
    }

    return 0;
}
