# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>


int main(int argc, char ** args){

    if(argc == 1){
        printf("rm : missing operand\n");
		printf("Try 'rm --help' for more information.\n");
    }

    else if(argc == 2){

        int r1 = remove(args[1]);
        if(r1 == -1){
            printf("rm : cannot remove '%s' : No such file or directory\n", args[1]);
        }
    }

    else if(argc == 3){

        if(strcmp(args[1], "-i") == 0){

            printf("Are you sure you want to delete this file - %s? (y/n): \n", args[2]);
            char c;
            scanf("%c", &c);

            if(c == 'y'){
                int r2 = remove(args[2]);
    
                if(r2 == -1){
                    printf("rm : cannot remove '%s' : No such file or directory\n", args[2]);
                }
            }
        }

        else if(strcmp(args[1], "-v") == 0){

            int r3 = remove(args[2]);
            if(r3 == -1){
                printf("rm : cannot remove '%s' : No such file or directory\n", args[2]);
			}
			
            else{
                printf("Removed this file - %s\n", args[2]);
            }
        }

        else{
            printf("rm : invalid option -- '%s'\n", args[1]);
			printf("Try 'rm --help' for more information.\n");
        }
    }
    return 0;
}
