#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> 

int randRange (int min, int max) {
    int range = max - min;
    return (rand() % range) + min;
}

void pattern1(int numOfProcesses, char output[]) {
    FILE *output_file = freopen(output, "w", stdout);
    printf("PATTERN 1, %d PROCESSES:\n", numOfProcesses);

    pid_t pid;
    for (int ix = 0; ix < numOfProcesses; ix++) {
        printf("Parent creating Process %d\n", ix);
        pid = fork();
        if (pid == 0) {
            int sleepTime = randRange(1, 9);
            printf("Process %d beginning, sleeping for %d seconds\n", ix, sleepTime);
            sleep(sleepTime);
            printf("Process %d ending\n", ix);
            exit(0);
        }
    }

    fclose(output_file);
    return;
}

void pattern2(int numOfProcesses, char output[]) {
    FILE *output_file = freopen(output, "w", stdout);
    printf("PATTERN 2, %d PROCESSES:\n", numOfProcesses);

    printf("Parent creating Process 0\n");
    pid_t pid = fork();
    printf("Process 0 created\n");
    
    for (int ix = 0; ix < numOfProcesses; ix++) {
        if (pid == 0) {
            int sleepTime = randRange(1, 9);
            printf("Process %d creating Process %d, sleeping for %d seconds\n", ix, ix + 1, sleepTime);
            pid = fork();
            sleep(sleepTime);
            waitpid(pid);
            printf("Process %d ending\n", ix);
            exit(0);
        }
    }

    fclose(output_file);
    return;
}


int main(int argc, char *argv[]) {
    int patternType;
    int numOfProcesses;

    sscanf(argv[1], "%d", &patternType);
    sscanf(argv[2], "%d", &numOfProcesses);

    srand(time(NULL));

    if (patternType == 1) {
        pattern1(numOfProcesses, "results.txt");
    }
    else if (patternType == 2) {
        pattern2(numOfProcesses, "results.txt");
    }
    else {
        printf("Invaled pattern type, must be 1/2/3.");
    }

    return 0;
}