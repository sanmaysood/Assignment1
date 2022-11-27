#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>


int main(int argc, char ** args){

    if(argc == 1){
        char * week_day1 = (char *) malloc(sizeof(char) * 20);
        char * month_name1 = (char *) malloc(sizeof(char) * 20);
        time_t sec1 = time(NULL);
        struct tm *time1 = localtime(&sec1);
        strftime(week_day1, 100, "%a", time1);
        strftime(month_name1, 100, "%b", time1);
        printf("%s %s %d %d:%d:%d IST 2022\n", week_day1, month_name1,time1->tm_mday, time1->tm_hour, time1->tm_min, time1->tm_sec);
    }

    else if(argc == 2){

        if(strcmp(args[1],"-u") == 0){
            char * week_day2 = (char *) malloc(sizeof(char) * 20);
            char * month_name2 = (char *) malloc(sizeof(char) * 20);
            time_t sec2 = time(NULL);
            struct tm *time2 = gmtime(&sec2);
            strftime(week_day2, 100, "%a", time2);
            strftime(month_name2, 100, "%b", time2);
            printf("%s %s %d %d:%d:%d UTC 2022\n", week_day2, month_name2,time2->tm_mday, time2->tm_hour, time2->tm_min, time2->tm_sec);
        }

        else if(strcmp(args[1],"-R") == 0){
            char * week_day3 = (char *) malloc(sizeof(char) * 20);
            char * month_name3 = (char *) malloc(sizeof(char) * 20);
            time_t sec3 = time(NULL);
            struct tm *time3 = localtime(&sec3);
            strftime(week_day3, 100, "%a", time3);
            strftime(month_name3, 100, "%b", time3);
            printf("%s, %d %s 2022 %d:%d:%d +0530\n", week_day3,time3->tm_mday,month_name3 , time3->tm_hour, time3->tm_min, time3->tm_sec);
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
