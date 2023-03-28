#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M_PI 3.14

struct Figure {
    char figure_firstx[20];
    char secondx[20];
    char thirdx[20];
};

int check_real_lenght(struct Figure main_check_circle) {
    int k = 0;
    for (int i = 0; i < sizeof(main_check_circle.thirdx) / sizeof(main_check_circle.thirdx[0]); i++) {
        if ((int) main_check_circle.thirdx[i] != 32) {
            k++;
        } else {
            return k;
        }
    }
    return k;
}

int check_x(char string[], int n,int *main_error) {
    char dot[] = ".";
    int flag = 0;
    for (int i = 0; i < n - 1; i++) {
        if ((int) string[i] == (int) (dot[0])) {
            flag += 1;
        }
        if (flag > 1) {
            *main_error = 9;
            return i + 1;
        }
        if (((int) string[i] > (int)('9') || (int) string[i] < (int)('0')) && (int) string[i] != (int)(dot[0])) {
            *main_error = 3;
            return i + 1;
        }
    }
    return 0;
}

int check_loss(struct Figure main_check_circle, char str[],int*main_error) {
    if (strlen(main_check_circle.thirdx) - strlen(str) > 2) {
        *main_error = 8;
        return 1;
    }
    return 0;
}

int check_comma(struct Figure main_check_circle,int *main_error) {
    if (main_check_circle.secondx[strlen(main_check_circle.secondx) - 1] != 44) {
        *main_error = 5;
        return 3;
    }
    return 0;
}

int check_last_bracket(struct Figure main_check_circle,int *main_error) {
    for (int i = 0; i < strlen(main_check_circle.thirdx); i++) {
        if (main_check_circle.thirdx[i] == 41) {
            return 0;
        }
    }

    *main_error = 7;
    return 3;
}

int check_name(struct Figure main_check_circle,int *main_error) {
    char check_name[] = "circle(";
    for (int i = 1; i <= strlen(check_name); i++) {
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

void print_error(struct Figure main_check_circle, int pointer,int *main_error) {
    printf("%s ", main_check_circle.figure_firstx);
    printf("%s ", main_check_circle.secondx);
    printf("%s ", main_check_circle.thirdx);
    printf("\n");
    for (int i = 0; i < pointer; i++) {
        printf(" ");
    }
    printf("^\n");
    printf("Error at colum %d: ", pointer);
    if (*main_error == 2) printf("expected 'circle', 'triangle' or 'polygon'");
    if (*main_error == 3) printf("expected '<double>");
    if (*main_error == 4) printf("expected '('");
    if (*main_error == 5) printf("expected ','");
    if (*main_error == 6) printf("expected '<double>");
    if (*main_error == 7) printf("expected ')");
    if (*main_error == 8) printf("unexpected token");
    if (*main_error == 9) printf("double dot");

    printf("\n");
}

double mainCheck(struct Figure main_check_circle) {
    int main_error;
    if (check_name(main_check_circle,&main_error) != 0) {
        print_error(main_check_circle, check_name(main_check_circle,&main_error) - 1,&main_error);
        return 0;
    }
    int length_figure_firstx = strlen(main_check_circle.figure_firstx);
    char x1[20] = "";
    char x2[20] = "";
    char x3[20] = "";
    char check_name[] = "circle(";
    int length_name = strlen(check_name);
    int pointer;
    strcpy(x1, main_check_circle.figure_firstx + strlen(main_check_circle.figure_firstx) - length_figure_firstx + length_name);
    strncpy(x2, main_check_circle.secondx, strlen(main_check_circle.secondx) - 1);
    strncpy(x3, main_check_circle.thirdx, check_real_lenght(main_check_circle) - 1);
    pointer = check_x(x1, strlen(x1),&main_error) + strlen(check_name) - 1;
    if (check_x(x1, strlen(x1),&main_error) != 0) {
        print_error(main_check_circle, pointer,&main_error);
        return 0;
    }
    pointer += check_x(x2, strlen(main_check_circle.secondx),&main_error) + strlen(x1) + 1;
    if (check_x(x2, strlen(x2),&main_error) != 0) {
        print_error(main_check_circle, pointer,&main_error);
        return 0;
    }
    pointer += strlen(main_check_circle.secondx) + 1;
    if (check_comma(main_check_circle,&main_error) != 0) {
        print_error(main_check_circle, pointer,&main_error);
        return 0;
    }
    pointer += (check_x(x3, strlen(x3),&main_error));

    if (check_x(x3, strlen(x3),&main_error) != 0) {
        print_error(main_check_circle, pointer,&main_error);
        return 0;
    }
    pointer += strlen(x3);
    if (check_last_bracket(main_check_circle,&main_error) != 0) {
        print_error(main_check_circle, pointer,&main_error);
        return 0;
    }
    pointer += strlen(main_check_circle.thirdx) - strlen(x3);
    if (check_loss(main_check_circle, x3,&main_error) != 0) {
        print_error(main_check_circle, pointer,&main_error);
        return 0;
    }
    return atof(x3);
}

int main() {
    FILE *file;
    struct Figure circle[10];
    int i = 0;
    file = fopen("geometry.txt", "r");
    char str[100];
    double r;
    while (fgets(str, 100, file) != NULL) {
        char *token = strtok(str, " ");
        strcpy(circle[i].figure_firstx, token);
        strcpy(circle[i].secondx, strtok(NULL, " "));
        strcpy(circle[i].thirdx, strtok(NULL, "\n"));
        if (mainCheck(circle[i]) != 0) {
            r = mainCheck(circle[i]);
            printf("%s %s %s \n", circle[i].figure_firstx, circle[i].secondx, circle[i].thirdx);
            printf("   perimetr = %.3lf\n", r * 2 * M_PI);
            printf("   area = %.3lf\n", r * r * M_PI);
        }
        i++;
    }

}