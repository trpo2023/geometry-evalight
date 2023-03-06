#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main_error;
struct figure {
    char name_x1[20];
    char x2_check[20];
    char x3_check[20];
    char loss_check[50];
};
int check_real_lenght(struct figure main_check_circle) {
    int k = 0;
    for (int i = 0; i < sizeof(main_check_circle.x3_check) / sizeof(main_check_circle.x3_check[0]); i++) {
        if ((int) main_check_circle.x3_check[i] != 32) {
            k++;
        } else {
            return k;
        }
    }
    return k;
}
int check_x(char string[], int n) {
    char dot[] = ".";
    int flag = 0;
    for (int i = 0; i < n - 1; i++) {
        if ((int) string[i] == (int) (dot[0])) {
            flag += 1;
        }
        if (flag > 1) {
            main_error = 9;
            return i + 1;
        }
        if (((int) string[i] > 57 || (int) string[i] < 48) && (int) string[i] != (int) (dot[0])) {
            main_error = 3;
            return i + 1;
        }
    }
    return 0;
}
int check_loss(struct figure main_check_circle, char str[]) {
    if (strlen(main_check_circle.x3_check) - strlen(str) > 2) {
        main_error = 8;
        return 1;
    }
    return 0;
}
int check_comma(struct figure main_check_circle) {
    if (main_check_circle.x2_check[strlen(main_check_circle.x2_check) - 1] != 44) {
        main_error = 5;
        return 3;
    }
    return 0;
}
int check_last_bracket(struct figure main_check_circle) {
    for (int i = 0; i < strlen(main_check_circle.x3_check); i++) {
        if (main_check_circle.x3_check[i] == 41) {
            return 0;
        }
    }

    main_error = 7;
    return 3;
}
int check_name(struct figure main_check_circle) {
    char check_name[] = "circle(";
    for (int i = 1; i <= strlen(check_name); i++) {
        if (strncmp(check_name, main_check_circle.name_x1, i) != 0) {
            if (i == 7) {
                main_error = 4;
            } else {
                main_error = 2;
            }

            return i;
        }
    }
    return 0;
}

void print_error(struct figure main_check_circle, int pointer) {
    printf("%s ", main_check_circle.name_x1);
    printf("%s ", main_check_circle.x2_check);
    printf("%s ", main_check_circle.x3_check);
    printf("\n");
    for (int i = 0; i < pointer; i++) {
        printf(" ");
    }
    printf("^\n");
    printf("Error at colum %d: ", pointer);
    if (main_error == 2) printf("expected 'circle', 'triangle' or 'polygon'");
    if (main_error == 3) printf("expected '<double>");
    if (main_error == 4) printf("expected '('");
    if (main_error == 5) printf("expected ','");
    if (main_error == 6) printf("expected '<double>");
    if (main_error == 7) printf("expected ')");
    if (main_error == 8) printf("unexpected token");
    if (main_error == 9) printf("double dot");

    printf("\n");
}
double mainCheck(struct figure main_check_circle) {
    if (check_name(main_check_circle) != 0) {
        print_error(main_check_circle, check_name(main_check_circle) - 1);
        return 0;
    }
    int length_name_x1 = strlen(main_check_circle.name_x1);
    char x1[20] = "";
    char x2[20] = "";
    char x3[20] = "";
    char check_name[] = "circle(";
    int length_name = strlen(check_name);
    int pointer;
    strcpy(x1, main_check_circle.name_x1 + strlen(main_check_circle.name_x1) - length_name_x1 + length_name);
    strncpy(x2, main_check_circle.x2_check, strlen(main_check_circle.x2_check) - 1);
    strncpy(x3, main_check_circle.x3_check, check_real_lenght(main_check_circle) - 1);
    pointer = check_x(x1, strlen(x1)) + strlen(check_name) - 1;
    if (check_x(x1, strlen(x1)) != 0) {
        print_error(main_check_circle, pointer);
        return 0;
    }
    pointer += check_x(x2, strlen(main_check_circle.x2_check)) + strlen(x1) + 1;
    if (check_x(x2, strlen(x2)) != 0) {
        print_error(main_check_circle, pointer);
        return 0;
    }
    pointer += strlen(main_check_circle.x2_check) + 1;
    if (check_comma(main_check_circle) != 0) {
        print_error(main_check_circle, pointer);
        return 0;
    }
    pointer += (check_x(x3, strlen(x3)));

    if (check_x(x3, strlen(x3)) != 0) {
        print_error(main_check_circle, pointer);
        return 0;
    }
    pointer += strlen(x3);
    if (check_last_bracket(main_check_circle) != 0) {
        print_error(main_check_circle, pointer);
        return 0;
    }
    pointer += strlen(main_check_circle.x3_check) - strlen(x3);
    if (check_loss(main_check_circle, x3) != 0) {
        print_error(main_check_circle, pointer);
        return 0;
    }
    return atof(x3);
}
int main() {
    FILE *file;
    struct figure circle[10];
    int i = 0;
    file = fopen("geometry.txt", "r");
    char str[100];
    double r;
    while (fgets(str, 100, file) != NULL) {
        char *token = strtok(str, " ");
        strcpy(circle[i].name_x1, token);
        strcpy(circle[i].x2_check, strtok(NULL, " "));
        strcpy(circle[i].x3_check, strtok(NULL, "\n"));
        if (mainCheck(circle[i]) != 0) {
            r = mainCheck(circle[i]);
            printf("%s %s %s \n", circle[i].name_x1, circle[i].x2_check, circle[i].x3_check);
            printf("   perimetr = %.3lf\n", r * 2 * 3.14);
            printf("   area = %.3lf\n", r * r * 3.14);
        }
        i++;
    }
}