#ifndef OBJECTS_FUNCTIONS_H
#define OBJECTS_FUNCTIONS_H

#define MAX_OBJECTS 3

typedef enum {
    APPLE,
    GRAPES,
    WATERMELON,
    STRAWBERRY,
    HAPPY_FACE,
    SAD_FACE
} ObjectType;
typedef struct {
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
int find_object_collision(int x, int y);
ObjectType get_object_type(int index);

#endif