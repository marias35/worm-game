#ifndef OBJECTS_FUNCTIONS_H
#define OBJECTS_FUNCTIONS_H

#define MAX_OBJECTS 3

typedef enum ObjectType {
    APPLE,
    GRAPES,
    WATERMELON,
    STRAWBERRY
} ObjectType;
typedef struct Object{
    int x;
    int y;
    ObjectType type;
    int active;
} Object;

void init_objects();
void spawn_object();
void random_free_position(int *x, int *y);
void respawn_object(int index);
void apply_fruit_effect(ObjectType type);
void draw_objects();
#endif