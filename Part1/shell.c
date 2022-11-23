# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <pthread.h>
# include <string.h>
# include <unistd.h>
# include <sched.h>
# include <sys/types.h>
# include <sys/wait.h>


void shell_loop();

char * readline();

char ** parse_line(char * line);

int interpret(char ** arguments);

int internal_commands(char ** arguments);

int external_commands(char ** arguments);


int main(int argc, char ** argv) {

    shell_loop();

    return 0;
}

void shell_loop(){
    char * line;
    char ** arguments;
    int s;
    line = readline();
    arguments = parse_line(line);
    s = run(arguments);

    free(line);
    free(arguments);

    while(s){
    line = readline();
    arguments = parse_line(line);
    s = run(arguments);

    free(line);
    free(arguments);

    }  
}

char * readline(){
    char * line = NULL;
    fgets(line, 1024, stdin);
    return line;
}

char ** parse_line(char * line){
    char ** arguments = malloc(128 * sizeof(char *));
    char * token;
    int i = 0;
    token = strtok(line, "  \t\r\n\a");
    while(token != NULL){
        arguments[i] = token;
        i++;
        token = strtok(NULL, "  \t\r\n\a");
    }
    arguments[i] = NULL;
    return arguments;
}

int interpret(char ** arguments){
    if(arguments[0] == NULL){
        return 1;
    }

    else if(strcmp(arguments[0],"cd") == 0 || strcmp(arguments[0],"echo") == 0 || strcmp(arguments[0],"pwd") == 0 || strcmp(arguments[0],"exit") == 0){
        return internal_commands(arguments);
    }
    
    else {
            return external_commands(arguments);
        }
}

int internal_commands(char ** arguments){
    int number = sizeof(arguments)/sizeof(char *);
    if(strcmp(arguments[0],"cd") == 0){
        if(arguments[1] == NULL){
            printf("Error: No directory specified");
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
        else if(number == 2){
            char * path = malloc(128 * sizeof(char *));
            getcwd(path, 128);
            strcat(path, "/");
            strcat(path, arguments[1]);
            chdir(path);
        }
        else{
            printf("Error: Too many arguments");
        }
    }
    else if(strcmp(arguments[0],"echo") == 0){
        if(arguments[1] == NULL){
            printf("Error: No argument specified");
        }
        else if(number == 2){
            printf("%s",arguments[1]);
        }
        else if(number > 2){
            if(strcmp(arguments[1],"-n") == 0){
                for(int i = 2; i < number; i++){
                    printf("%s",arguments[i]);
                }
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
                        printf("%s",arguments[i]);
                    }
                }
            }
            else{
                for(int i = 1; i < number; i++){
                    printf("%s",arguments[i]);
                }
            }
        }
    }

    else if(strcmp(arguments[0],"pwd") == 0){
        if(number == 1){
            char cwd[1024];
            getcwd(cwd, sizeof(cwd));
            printf("%s\n",cwd);
        }
        else{
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
                printf("Error: Too many arguments");
            }
        }
    }
    else if(strcmp(arguments[0],"exit") == 0){
        if(number == 1){
            return 0;
        }
        else{
            printf("Error: Too many arguments");
        }
    }
    return 1;
}


int external_commands(char ** arguments){
    if(strcmp(arguments[0],"ls") == 0){
        pid_t pid;
        pid = fork();

        if(pid == 0){
            execvp(arguments[0],arguments);
        }
        else if(pid < 0){
            printf("Error: Fork failed");
        }
        else{
            waitpid(-1, NULL, 0);
        }
    }
    else if(strcmp(arguments[0],"cat") == 0){
        pid_t pid;
        pid = fork();
        if(pid == 0){
            execvp(arguments[0],arguments);
        }
        else if(pid < 0){
            printf("Error: Fork failed");
        }
        else{
            waitpid(-1, NULL, 0);
        }
    }

    else if(strcmp(arguments[0],"date") == 0){
        pid_t pid;
        pid = fork();
        if(pid == 0){
            execvp(arguments[0],arguments);
        }
        else if(pid < 0){
            printf("Error: Fork failed");
        }
        else{
            waitpid(-1, NULL, 0);
        }
    }

    else if(strcmp(arguments[0],"rm") == 0){
        pid_t pid;
        pid = fork();
        if(pid == 0){
            execvp(arguments[0],arguments);
        }
        else if(pid < 0){
            printf("Error: Fork failed");
        }
        else{
            waitpid(-1, NULL, 0);
        }
    }
    else if(strcmp(arguments[0],"mkdir") == 0){
        pid_t pid;
        pid = fork();
        if(pid == 0){
            execvp(arguments[0],arguments);
        }
        else if(pid < 0){
            printf("Error: Fork failed");
        }
        else{
            waitpid(-1, NULL, 0);
        }
    }
    
    return 1;
}



