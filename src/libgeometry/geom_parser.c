#include "geom_parser.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_real_lenght(struct Figure main_check_circle)
{
    int k = 0;
    for (int i = 0; i < (int)sizeof(main_check_circle.thirdx)
                 / (int)sizeof(main_check_circle.thirdx[0]);
         i++) {
        if ((int)main_check_circle.thirdx[i] != 32) {
            k++;
        } else {
            return k;
        }
    }
    return k;
}

void circle_print(struct Figure fig)
{
    printf("%s ", fig.figure_firstx);
    printf("%s ", fig.secondx);
    printf("%s", fig.thirdx);
}

int check_x(char string[], int n, int* main_error)
{
    int dot = '.';
    int minus = '-';
    int dot_flag = 0;
    int minus_flag = 0;
    for (int i = 0; i < n; i++) {
        if ((int)string[i] == dot) {
            dot_flag += 1;
        }
        if ((int)string[i] == minus) {
            minus_flag += 1;
        }
        if (dot_flag > 1) {
            *main_error = 9;
            return i + 1;
        }
        if (minus_flag > 1) {
            *main_error = 3;
            return i + 1;
        }
        if (((int)string[i] > (int)('9') || (int)string[i] < (int)('0'))
            && ((int)string[i] != minus && (int)string[i] != dot)) {
            *main_error = 3;
            return i + 1;
        }
    }
    return 0;
}

int check_radius(char string[], int n, int* main_error)
{
    int dot = '.';
    int minus = '-';
    int flag = 0;
    for (int i = 0; i < n - 1; i++) {
        if ((int)string[i] == dot) {
            flag += 1;
        }
        if ((int)string[i] == minus) {
            *main_error = 10;
            return i + 1;
        }
        if (flag > 1) {
            *main_error = 9;
            return i + 1;
        }
        if (((int)string[i] > (int)('9') || (int)string[i] < (int)('0'))
            && string[i] != (int)('.')) {
            *main_error = 3;
            return i + 1;
        }
    }
    return 0;
}

int check_loss(struct Figure main_check_circle, char str[], int* main_error)
{
    if (strlen(main_check_circle.thirdx) - strlen(str) > 2) {
        *main_error = 8;
        return 1;
    }
    return 0;
}

int check_comma(struct Figure main_check_circle, int* main_error)
{
    if (main_check_circle.secondx[strlen(main_check_circle.secondx) - 1]
        != 44) {
        *main_error = 5;
        return 3;
    }
    return 0;
}

int check_last_bracket(struct Figure main_check_circle, int* main_error)
{
    for (int i = 0; i < (int)strlen(main_check_circle.thirdx); i++) {
        if (main_check_circle.thirdx[i] == 41) {
            return 0;
        }
    }

    *main_error = 7;
    return 3;
}

int check_name(struct Figure main_check_circle, int* main_error)
{
    char check_name[] = "circle(";

    for (int i = 1; i <= (int)strlen(check_name); i++) {
        if (strncmp(check_name, main_check_circle.figure_firstx, i) != 0) {
            if (i == 7) {
                *main_error = 4;
            } else {
                *main_error = 2;
            }

            return i;
        }
    }
    return 0;
}
void print_pointer(struct Figure fig, int pointer)
{
    printf("%s ", fig.figure_firstx);
    printf("%s ", fig.secondx);
    printf("%s ", fig.thirdx);
    printf("\n");
    for (int i = 0; i < pointer; i++) {
        printf(" ");
    }
    printf("^\n");
    printf("Error at colum %d: ", pointer);
}
void print_error(int main_error)
{
    if (main_error == 2)
        printf("expected 'circle', 'triangle' or 'polygon'");
    if (main_error == 3)
        printf("expected '<double>");
    if (main_error == 4)
        printf("expected '('");
    if (main_error == 5)
        printf("expected ','");
    if (main_error == 6)
        printf("expected '<double>");
    if (main_error == 7)
        printf("expected ')");
    if (main_error == 8)
        printf("unexpected token");
    if (main_error == 9)
        printf("double dot");
    if (main_error == 10)
        printf("radius must be greater than zero");

    printf("\n");
}

void load_x(struct Int_figure* fig, struct Figure main_check_circle)
{
    char x1[20] = "";
    char x2[20] = "";
    char x3[20] = "";
    int length_figure_firstx = strlen(main_check_circle.figure_firstx);
    char check_name[] = "circle(";
    int length_name = strlen(check_name);
    strcpy(x1,
           main_check_circle.figure_firstx
                   + strlen(main_check_circle.figure_firstx)
                   - length_figure_firstx + length_name);
    strncpy(x2,
            main_check_circle.secondx,
            strlen(main_check_circle.secondx) - 1);
    strncpy(x3, main_check_circle.thirdx, strlen(main_check_circle.thirdx) - 1);

    fig->x1 = atof(x1);
    fig->x2 = atof(x2);
    fig->radius = atof(x3);
}

int isIntersection(struct Int_figure fig, struct Int_figure fig2)
{
    double d = sqrt(pow(fig.x1 - fig2.x1, 2) + pow(fig.x2 - fig2.x2, 2));
    if (pow(fig2.radius - fig.radius, 2) > pow(d, 2)) {
        printf("One circle in other\n");
        return 2;
    } else if (d < (fig.radius + fig2.radius)) {
        printf("There is a intersetion\n");
        return 1;
    }
    if (d > (fig.radius + fig2.radius)) {
        printf("There is no intersetion\n");
        return 0;
    }
    return 3;
}

int mainCheck(struct Figure main_check_circle, int* pointer)
{
    int main_error;
    if (check_name(main_check_circle, &main_error) != 0) {
        *pointer = check_name(main_check_circle, &main_error) - 1;
        return main_error;
    }
    int length_figure_firstx = strlen(main_check_circle.figure_firstx);
    char x1[20] = "";
    char x2[20] = "";
    char x3[20] = "";
    char check_name[] = "circle(";
    int length_name = strlen(check_name);
    strcpy(x1,
           main_check_circle.figure_firstx
                   + strlen(main_check_circle.figure_firstx)
                   - length_figure_firstx + length_name);
    strncpy(x2,
            main_check_circle.secondx,
            strlen(main_check_circle.secondx) - 1);
    strncpy(x3,
            main_check_circle.thirdx,
            check_real_lenght(main_check_circle) - 1);
    *pointer = check_x(x1, strlen(x1), &main_error) + strlen(check_name) + 1;
    if (check_x(x1, strlen(x1), &main_error) != 0) {
        return main_error;
    }
    *pointer += check_x(x2, strlen(main_check_circle.secondx), &main_error)
            + strlen(x1) + 1;
    if (check_x(x2, strlen(x2), &main_error) != 0) {
        return main_error;
    }
    *pointer += strlen(main_check_circle.secondx);
    if (check_comma(main_check_circle, &main_error) != 0) {
        return main_error;
    }
    *pointer += (check_x(x3, strlen(x3), &main_error)) + 1;
    if (check_radius(x3, strlen(x3) - 1, &main_error) != 0) {
        return main_error;
    }
    *pointer += strlen(x3) - 1;
    if (check_last_bracket(main_check_circle, &main_error) != 0) {
        return main_error;
    }
    *pointer += strlen(main_check_circle.thirdx) - strlen(x3) - 1;
    if (check_loss(main_check_circle, x3, &main_error) != 0) {
        return main_error;
    }
    return 0;
}