#include <math.h>
#include <stdio.h>
#include <string.h>

#include "../libgeometry/geom_parser.h"

int main()
{
    FILE* file;
    struct Figure circle[10];
    struct Int_figure int_circle[10];
    int i = 0;
    int pointer = 0;
    file = fopen("geometry.txt", "r");
    char str[100];
    double r;
    while (fgets(str, 100, file) != NULL) {
        pointer = 0;
        char* token = strtok(str, " ");
        strcpy(circle[i].figure_firstx, token);
        strcpy(circle[i].secondx, strtok(NULL, " "));
        strcpy(circle[i].thirdx, strtok(NULL, "\n"));
        int error = mainCheck(circle[i], &pointer);
        if (error == 0) {
            load_x(&int_circle[i], circle[i]);
            r = int_circle[i].radius;
            printf("%s %s %s \n",
                   circle[i].figure_firstx,
                   circle[i].secondx,
                   circle[i].thirdx);
            printf("   perimetr = %.3lf\n", r * 2 * M_PI);
            printf("   area = %.3lf\n", r * r * M_PI);
            i++;
        } else {
            print_pointer(circle[i], pointer);
            print_error(error);
        }
    }
    for (int j = 1; j < i; j++) {
        isIntersection(int_circle[j - 1], int_circle[j]);
        circle_print(circle[j]);
        printf(" and ");
        circle_print(circle[j - 1]);
        printf("\n");
    }
}