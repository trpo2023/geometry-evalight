#pragma once
#include <stdio.h>

struct Figure {
    char figure_firstx[20];
    char secondx[20];
    char thirdx[20];
};

struct Int_figure {
    double x1;
    double x2;
    double radius;
};

void circle_print(struct Figure fig);
int check_real_lenght(struct Figure main_check_circle);
int check_x(char string[], int n, int* main_error);
int check_radius(char string[], int n, int* main_error);
int check_loss(struct Figure main_check_circle, char str[], int* main_error);
int check_comma(struct Figure main_check_circle, int* main_error);
int check_last_bracket(struct Figure main_check_circle, int* main_error);
int check_name(struct Figure main_check_circle, int* main_error);
void print_pointer(struct Figure fig, int pointer);
void print_error(int main_error);
void load_x(struct Int_figure* fig, struct Figure main_check_circle);
int isIntersection(struct Int_figure fig, struct Int_figure fig2);
int mainCheck(struct Figure main_check_circle, int* pointer);