# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <pthread.h>
# include <string.h>
# include <unistd.h>
# include <sched.h>
# include <sys/types.h>
# include <sys/wait.h>


int interpret(char ** arguments);

int internal_commands(char ** arguments);

int external_commands(char ** arguments);

void * thread_function(void * args);



int main() {

    char * line;
    line = (char *) malloc(100*sizeof(char));
    char ** arguments;
    arguments = (char **) malloc(200*sizeof(char *));
    int s = 1;
    
    while(s){

    printf(">> "); 
    
    fgets(line, 100 , stdin);
       
    char * word;
    word = (char*) malloc(50*sizeof(char));
    int i = 0;
    word = strtok(line, "  \t\r\n\a");

    while(word != NULL){
        arguments[i] = word;
        i++;
        word = strtok(NULL, "  \t\r\n\a");
    }

    arguments[i] = NULL;
   
    s = interpret(arguments);

//     free(line);
//     free(arguments);

    } 

    return 0;
}
 


int interpret(char ** arguments){

       int size = 0;

        for(int i=0;arguments[i] != NULL; i++){
            size++;
        }

    if(strcmp(arguments[size - 1],"&t") == 0){
        pthread_t tid;
        char * str = (char *) malloc(1000*sizeof(char));
        for(int i=0; i < size - 2; i++){
            strcat(str, arguments[i]);
            strcat(str, " ");
        }
        strcat(str, arguments[size - 2]);
        pthread_create(&tid, NULL, &thread_function, &str);
        pthread_join(tid, NULL);
        return 1;
    }

    else {

        if(arguments[0] == NULL){
            return 1;
        }

        else if(strcmp(arguments[0],"cd") == 0 || strcmp(arguments[0],"echo") == 0 || strcmp(arguments[0],"pwd") == 0 || strcmp(arguments[0],"exit") == 0){

            int ret = internal_commands(arguments);
            return ret;
        }
    
        else {

            int ret = external_commands(arguments);
            return ret;
        }
    }
    return 1;
}


int internal_commands(char ** arguments){

       
    int number = 0;

        for(int i=0;arguments[i] != NULL; i++){
            number++;
        }

    if(strcmp(arguments[0],"cd") == 0){

        if(arguments[1] == NULL){

            printf("No arguments passed\n");
        }

        else if(number == 2 && strcmp(arguments[1],"~") == 0){
            chdir(getenv("HOME"));
        }

        else if(number == 2 && strcmp(arguments[1],"..") == 0){
            char * path = malloc(128 * sizeof(char));
            getcwd(path, 128);
            int i = strlen(path);
            while(path[i] != '/'){
                path[i] = '\0';
                i--;
            }
            path[i] = '\0';
            chdir(path);
        }

        else if(number == 2 && strcmp(arguments[1],"..") != 0 && strcmp(arguments[1],"~") != 0){
            char * path = malloc(128 * sizeof(char *));
            getcwd(path, 128);
            strcat(path, "/");
            strcat(path, arguments[1]);
            chdir(path);
        }

        else{
            
            printf("Too many arguments\n");
        }
    }



    else if(strcmp(arguments[0],"echo") == 0){
        
        if(arguments[1] == NULL){
            printf("No arguments passed\n");
        }
        else if(number == 2){
            printf("%s\n",arguments[1]);
        }

        else if(number > 2){
            if(strcmp(arguments[1],"-n") == 0){
                for(int i = 2; i < number; i++){
                    printf("%s ",arguments[i]);
                }
                printf("\n");
            }
            else if(strcmp(arguments[1],"-e") == 0){
                for(int i = 2; i < number; i++){
                    if(strcmp(arguments[i],"\\n") == 0){
                        printf("\n");
                    }
                    else if(strcmp(arguments[i],"\\t") == 0){
                        printf("\t");
                    }
                    else if(strcmp(arguments[i],"\\a") == 0){
                        printf("\a");
                    }
                    else if(strcmp(arguments[i],"\\b") == 0){
                        printf("\b");
                    }
                    else if(strcmp(arguments[i],"\\v") == 0){
                        printf("\v");
                    }
                    else if(strcmp(arguments[i],"\\r") == 0){
                        printf("\r");
                    }
                    else if(strcmp(arguments[i],"\\f") == 0){
                        printf("\f");
                    }
                    else if(strcmp(arguments[i],"\\'") == 0){
                        printf("\'");
                    }
                    else if(strcmp(arguments[i],"\\\"") == 0){
                        printf("\"");
                    }
                    else if(strcmp(arguments[i],"\\\\") == 0){
                        printf("\\");
                    }
                    else{
                        printf("%s\n",arguments[i]);
                    }
                }
            }

            else{

                for(int i = 1; i < number; i++){
                    printf("%s ",arguments[i]);
                }
                printf("\n");
            }
        }
    }



    else if(strcmp(arguments[0],"pwd") == 0){

        if(number == 1){
            char cwd[1024];
            getcwd(cwd, sizeof(cwd));
            printf("%s\n",cwd);
        }

        else if(number == 2){

            if(strcmp(arguments[1],"-L") == 0){
                char * str = malloc(128 * sizeof(char *));
                str = getenv("PWD");
                printf("%s\n",str);
            }

            else if(strcmp(arguments[1],"-P") == 0){
                char cwd[1024];
                getcwd(cwd, sizeof(cwd));
                printf("%s\n",cwd);
            }

            else{
                printf("Invalid flag used/ Invalid command.\n");
            }
        }

        else{
                printf("Too many arguments\n");

        }
    }


    else if(strcmp(arguments[0],"exit") == 0){
        if(number == 1){
            return 0;
        }

        else{
            printf("Too many arguments\n");
        }
                
    }

    return 1;
}


int external_commands(char ** arguments){
    
    if(strcmp(arguments[0],"ls") == 0){
        pid_t pid;
        pid = fork();

        if(pid == 0){
            int ret = execvp(arguments[0],arguments);
            if(ret == -1){
                printf("Error in execvp\n");
                return 0;
            }
        }
        else if(pid < 0){
            printf("Fork failed\n");
            return 0;
        }
        else{
            waitpid(-1, NULL, 0);
        }
    }
    else if(strcmp(arguments[0],"cat") == 0){
        pid_t pid;
        pid = fork();
        if(pid == 0){
            int ret = execvp(arguments[0],arguments);
            if(ret == -1){
                printf("Error in execvp\n");
                return 0;
            }
        }
        else if(pid < 0){
            printf("Fork failed\n");
            return 0;
        }
        else{
            waitpid(-1, NULL, 0);
        }
    }

    else if(strcmp(arguments[0],"date") == 0){
        pid_t pid;
        pid = fork();
        if(pid == 0){
            int ret = execvp(arguments[0],arguments);
            if(ret == -1){
                printf("Error in execvp\n");
                return 0;
            }
        }
        else if(pid < 0){
            printf("Fork failed\n");
            return 0;
        }
        else{
            waitpid(-1, NULL, 0);
        }
    }

    else if(strcmp(arguments[0],"rm") == 0){
        pid_t pid;
        pid = fork();
        if(pid == 0){
            int ret =  execvp(arguments[0],arguments);
            if(ret == -1){
                printf("Error in execvp\n");
                return 0;
            }
        }
        else if(pid < 0){
            printf("Fork failed\n");
            return 0;
        }
        else{
            waitpid(-1, NULL, 0);
        }
    }
    else if(strcmp(arguments[0],"mkdir") == 0){
        pid_t pid;
        pid = fork();
        if(pid == 0){
            int ret = execvp(arguments[0],arguments);
            if(ret == -1){
                printf("Error in execvp\n");
                return 0;
            }
        }
        else if(pid < 0){
            printf("Fork failed\n");
            return 0;
        }
        else{
            waitpid(-1, NULL, 0);
        }
    }
    
    return 1;
}


// void * thread_function(void * args){

//     char ** arguments = (char **) args;
//     char command[1000];

//     for(int i = 0; arguments[i] != NULL; i++){
//         strcat(command,arguments[i]);
//         strcat(command," ");
//     }

//     system(command);    
//     pthread_exit(NULL);
// }

void * thread_function(void * args){
    char * arguments = (char *) malloc(1000 * sizeof(char *));
    arguments = *(char **) args;
 
    int index = 0;
    for(int i=0 ; arguments[i] != NULL; i++){
        if(arguments[i] == ' '){
            index = i;
            break;
        }
    }
    char * test = (char *) malloc(1000 * sizeof(char *));
    for(int i=0;i<index;i++){
        test[i] = arguments[i];
    }
    if(strcmp(test,"ls") == 0){
        system("gcc ls.c -o ls");
        system(arguments);
    }

    else if(strcmp(test,"cat") == 0){
        system("gcc cat.c -o cat");
        system(arguments);
    }

    else if(strcmp(test,"date") == 0){
        system("gcc date.c -o date");
        system(arguments);
    }

    else if(strcmp(test,"rm") == 0){
        system("gcc rm.c -o rm");
        system(arguments);
    }

    else if(strcmp(test,"mkdir") == 0){
        system("gcc mkdir.c -o mkdir");
        system(arguments);
    }

    pthread_exit(NULL);
}
