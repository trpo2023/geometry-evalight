#ifndef CIRCLE_TEST
#define CIRCLE_TEST

#include "../src/libgeometry/geom_parser.h"
#include "ctest.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

CTEST(FIND_INTERSECTION, isIntersection)
{
    struct Int_figure One_in_other[2];
    One_in_other[0].x1 = 10;
    One_in_other[0].x2 = 10;
    One_in_other[0].radius = 1;
    One_in_other[1].x1 = 10;
    One_in_other[1].x2 = 10;
    One_in_other[1].radius = 2;

    struct Int_figure Intersec_circles[2];
    Intersec_circles[0].x1 = 1;
    Intersec_circles[0].x2 = 2;
    Intersec_circles[0].radius = 3;
    Intersec_circles[1].x1 = 2;
    Intersec_circles[1].x2 = 2;
    Intersec_circles[1].radius = 3;

    struct Int_figure No_intersec_circles[2];
    No_intersec_circles[0].x1 = 1;
    No_intersec_circles[0].x2 = 50;
    No_intersec_circles[0].radius = 3;
    No_intersec_circles[1].x1 = 2;
    No_intersec_circles[1].x2 = 2;
    No_intersec_circles[1].radius = 3;

    int a = isIntersection(One_in_other[0], One_in_other[1]);
    ASSERT_EQUAL(a, 2);

    int b = isIntersection(Intersec_circles[0], Intersec_circles[1]);
    ASSERT_EQUAL(b, 1);

    int c = isIntersection(No_intersec_circles[0], No_intersec_circles[1]);
    ASSERT_EQUAL(c, 0);
}

CTEST(FIND_INVALID_INPUT, mainCheck)
{
    int pointer;
    struct Figure circle[4];
    char exampls[4][25]
            = {"circle(10.4 10, 10)",
               "crcle(10.3 10.6, 10)",
               "circle(10 10, 10",
               "circle(10 aa, 10)"};
    for (int i = 0; i < 4; i++) {
        char* token = strtok(exampls[i], " ");
        strcpy(circle[i].figure_firstx, token);
        strcpy(circle[i].secondx, strtok(NULL, " "));
        strcpy(circle[i].thirdx, strtok(NULL, " "));
    }

    int a = mainCheck(circle[0], &pointer);
    ASSERT_EQUAL(a, 0);

    a = mainCheck(circle[1], &pointer);
    ASSERT_EQUAL(a, 2);

    a = mainCheck(circle[2], &pointer);
    ASSERT_EQUAL(a, 7);

    a = mainCheck(circle[3], &pointer);
    ASSERT_EQUAL(a, 3);
}

#endif