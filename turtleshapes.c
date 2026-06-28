/*
 *      turtleshapes.c      shared turtle cursor shapes
 *
 *      The vertex data is adapted from CPython's turtle.py built-in shapes
 *      (Python Software Foundation license).  turtle.py describes each shape
 *      as a polygon in (x = right, y = forward) coordinates; here we store
 *      (f = forward, s = left), so each turtle.py point (x, y) becomes
 *      (f, s) = (y, -x).
 */

#include "turtleshapes.h"
#include <string.h>

/* The classic recognizable turtle. */
static const turtle_vertex turtle_verts[] = {
    { 16,  0}, { 14,  2}, { 10,  1}, {  7,  4}, {  9,  7}, {  8,  9},
    {  5,  6}, {  1,  7}, { -3,  5}, { -6,  8}, { -8,  6}, { -5,  4},
    { -7,  0}, { -5, -4}, { -8, -6}, { -6, -8}, { -3, -5}, {  1, -7},
    {  5, -6}, {  8, -9}, {  9, -7}, {  7, -4}, { 10, -1}, { 14, -2}
};

/* The small arrowhead that older Logos / Python's default use. */
static const turtle_vertex classic_verts[] = {
    { 0, 0}, { -9, 5}, { -7, 0}, { -9, -5}
};

static const turtle_vertex triangle_verts[] = {
    { 11.55, 0}, { -5.77, -10}, { -5.77, 10}
};

static const turtle_vertex square_verts[] = {
    { -10, -10}, { 10, -10}, { 10, 10}, { -10, 10}
};

/* A 20-gon standing in for a circle. */
static const turtle_vertex circle_verts[] = {
    {   0, -10}, { 3.09, -9.51}, { 5.88, -8.09}, { 8.09, -5.88},
    { 9.51, -3.09}, {  10,  0}, { 9.51,  3.09}, { 8.09,  5.88},
    { 5.88,  8.09}, { 3.09,  9.51}, {   0,  10}, { -3.09,  9.51},
    { -5.88,  8.09}, { -8.09,  5.88}, { -9.51,  3.09}, {  -10,  0},
    { -9.51, -3.09}, { -8.09, -5.88}, { -5.88, -8.09}, { -3.09, -9.51}
};

#define NVERTS(a) ((int)(sizeof(a) / sizeof((a)[0])))

static const turtle_shape shapes[] = {
    { "turtle",   NVERTS(turtle_verts),   turtle_verts   },
    { "classic",  NVERTS(classic_verts),  classic_verts  },
    { "triangle", NVERTS(triangle_verts), triangle_verts },
    { "square",   NVERTS(square_verts),   square_verts   },
    { "circle",   NVERTS(circle_verts),   circle_verts   }
};

#define NSHAPES NVERTS(shapes)

/* Guarantee at compile time that every shape fits in a TURTLE_MAX_VERTS
   buffer, so renderers can use a fixed-size array without truncating. */
_Static_assert(NVERTS(turtle_verts)   <= TURTLE_MAX_VERTS, "turtle shape too big");
_Static_assert(NVERTS(classic_verts)  <= TURTLE_MAX_VERTS, "classic shape too big");
_Static_assert(NVERTS(triangle_verts) <= TURTLE_MAX_VERTS, "triangle shape too big");
_Static_assert(NVERTS(square_verts)   <= TURTLE_MAX_VERTS, "square shape too big");
_Static_assert(NVERTS(circle_verts)   <= TURTLE_MAX_VERTS, "circle shape too big");

const turtle_shape *current_turtle_shape = &shapes[0];   /* default: turtle */

const turtle_shape *turtle_shape_named(const char *name) {
    int i;
    for (i = 0; i < NSHAPES; i++)
        if (strcmp(name, shapes[i].name) == 0)
            return &shapes[i];
    return 0;
}

int set_turtle_shape_by_name(const char *name) {
    const turtle_shape *s = turtle_shape_named(name);
    if (s == 0) return 0;
    current_turtle_shape = s;
    return 1;
}

const char *turtle_shape_current_name(void) {
    return current_turtle_shape->name;
}

int turtle_shape_count(void) {
    return NSHAPES;
}

const char *turtle_shape_name_at(int i) {
    if (i < 0 || i >= NSHAPES) return 0;
    return shapes[i].name;
}
