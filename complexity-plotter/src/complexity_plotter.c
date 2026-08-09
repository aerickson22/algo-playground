#include "complexity_plotter.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char** argv){
    FILE* gnuplotPipe;
    if(!(gnuplotPipe = popen("gnuplot -persist", "w"))){
        fprintf(stderr, "ERROR: COULDN'T OPEN GNUPLOT\n");
        return -1;
    }

    int min, max, step;
    if (argc < 5 || strcmp(argv[1], "--help") == 0) {
        fprintf(stderr, "USAGE: %s <program> <min> <max> <step>\n", argv[0]);
        pclose(gnuplotPipe);
        return -1;
    }
    min = atoi(argv[2]);
    max = atoi(argv[3]);
    step = atoi(argv[4]);

    int n = (max - min) / step + 1;
    int *xs = malloc(n * sizeof(int));
    double *ys = malloc(n * sizeof(double));
    int count = 0;

    struct timespec start, end;

    for (int i = min; i < max; i += step) {
        if (clock_gettime(CLOCK_MONOTONIC, &start)) {
            fprintf(stderr, "ERROR: start time failed\n");
            pclose(gnuplotPipe);
            return -1;
        }
        pid_t pid = fork();
        if (pid == 0) {
            pclose(gnuplotPipe);
            char sizeStr[32];
            snprintf(sizeStr, sizeof(sizeStr), "%d", i);
            char *args[] = { argv[1], sizeStr, NULL };
            execvp(argv[1], args);
            fprintf(stderr, "ERROR: Could not execute file\n");
            _exit(1);
        } else if (pid > 0) {
            int status;
            waitpid(pid, &status, 0);
            if (clock_gettime(CLOCK_MONOTONIC, &end)) {
                fprintf(stderr, "ERROR: end time failed");
                pclose(gnuplotPipe);
                return -1;
            }
            double time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
            if (time > 0) {
                xs[count] = i;
                ys[count] = time;
                count++;
            }
        } else {
            fprintf(stderr, "ERROR: Fork failed\n");
            free(xs); free(ys);
            return -1;
        }
    }

    fprintf(gnuplotPipe, "set terminal qt 0\n");
    fprintf(gnuplotPipe, "set title 'Runtime vs Input Size'\n");
    fprintf(gnuplotPipe, "set xlabel 'n'\n");
    fprintf(gnuplotPipe, "set ylabel 'Time (ms)'\n");
    fprintf(gnuplotPipe, "plot '-' with linespoints title 'runtime'\n");
    for (int j = 0; j < count; j++) {
        fprintf(gnuplotPipe, "%d %f\n", xs[j], ys[j]);
    }
    fprintf(gnuplotPipe, "e\n");
    fflush(gnuplotPipe);

    pclose(gnuplotPipe);
    free(xs);
    free(ys);
    return 0;
}
