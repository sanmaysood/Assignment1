#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char ** args){
    struct dirent *dir;
    DIR *D;
    D = opendir(".");

    if(D == NULL){
        printf("ls : cannot access %s : No such file or directory\n", args[1]);
    }

   if(argc == 1){

        while((dir = readdir(D)) != NULL){
            if(strcmp(dir->d_name,".") != 0 && strcmp(dir->d_name,"..") != 0){
            printf("%s \n", dir->d_name);
            }
        }
//         closedir(D);
   }

   else if(argc == 2){

        if(strcmp(args[1],"-a") == 0){
    
            while((dir = readdir(D)) != NULL){
                printf("%s \n", dir->d_name);
            }

//             closedir(D);
        }

        else if(strcmp(args[1],"-m") == 0){
           
            while((dir = readdir(D)) != NULL){
                if(strcmp(dir->d_name,".") != 0 && strcmp(dir->d_name,"..") != 0){
                printf("%s, ", dir->d_name);
                }
            }
            
//             closedir(D);
        }

        else{
            printf("ls : invalid option -- '%s'\n", args[1]);
			printf("Try 'ls --help' for more information.\n");
	
        }
   }
   
   return 0;
}


