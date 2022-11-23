#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>


int main(int argc, char ** args){
    if(argc == 1){
        char week_day[100];
        char month_name[100];
        time_t sec = time(NULL);
        struct tm *time = localtime(&sec);
        strftime(week_day, 100, "%a", time);
        strftime(month_name, 100, "%b", time);
        printf("%s %s %d %d:%d:%d IST 2022\n", week_day, month_name,time->tm_mday, time->tm_hour, time->tm_min, time->tm_sec);
    }
    else if(argc == 2){
        if(strcmp(args[1],"-u") == 0){
            char week_day[100];
            char month_name[100];
            time_t sec = time(NULL);
            struct tm *time = gmtime(&sec);
            strftime(week_day, 100, "%a", time);
            strftime(month_name, 100, "%b", time);
            printf("%s %s %d %d:%d:%d UTC 2022\n", week_day, month_name,time->tm_mday, time->tm_hour, time->tm_min, time->tm_sec);
        }
        else if(strcmp(args[1],"-R") == 0){
            char week_day[100];
            char month_name[100];
            time_t sec = time(NULL);
            struct tm *time = localtime(&sec);
            strftime(week_day, 100, "%a", time);
            strftime(month_name, 100, "%b", time);
            printf("%s, %d %s 2022 %d:%d:%d +0530\n", week_day,time->tm_mday,month_name , time->tm_hour, time->tm_min, time->tm_sec);
        }
        else{
            printf("Invalid command\n");
        }
    }
    else{
        printf("Invalid command\n");
    }
    return 0;
}
