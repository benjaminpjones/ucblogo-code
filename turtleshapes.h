/*
 *      turtleshapes.h      shared turtle cursor shapes
 *
 *      Shapes are described once here and rendered by both the wx GUI
 *      (wxTurtleGraphics.cpp) and the X11/terminal backend (graphics.c).
 */

#ifndef TURTLESHAPES_H
#define TURTLESHAPES_H

#ifdef __cplusplus
extern "C" {
#endif

/* A vertex in turtle-local coordinates: f points forward along the turtle's
   heading, s points to the turtle's left. */
typedef struct {
    double f, s;
} turtle_vertex;

typedef struct {
    const char *name;
    int count;
    const turtle_vertex *verts;
} turtle_shape;

/* Upper bound on a shape's vertex count.  Renderers may size a fixed buffer
   with this; turtleshapes.c statically asserts every built-in shape fits. */
#define TURTLE_MAX_VERTS 32

/* The shape currently used to draw the turtle (never NULL). */
extern const turtle_shape *current_turtle_shape;

/* Look up a built-in shape by (lowercase) name, or NULL if there isn't one. */
const turtle_shape *turtle_shape_named(const char *name);

/* Select the named shape.  Returns 1 on success, 0 if the name is unknown. */
int set_turtle_shape_by_name(const char *name);

/* Name of the current shape, and iteration over all built-in shapes. */
const char *turtle_shape_current_name(void);
int turtle_shape_count(void);
const char *turtle_shape_name_at(int i);

#ifdef __cplusplus
}
#endif

#endif /* TURTLESHAPES_H */
