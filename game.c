#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define GRID_WIDTH   40
#define GRID_HEIGHT  30
#define MAX_WORM_LEN (GRID_WIDTH * GRID_HEIGHT)
#define NUM_OBJECTS  3
#define START_TIME_SEC 60

typedef enum { UP, DOWN, LEFT, RIGHT, NONE } Direction;

typedef enum {
    APPLE, GRAPES, WATERMELON, STRAWBERRY,
    EMOJI_HAPPY, EMOJI_SAD,
    OBJECT_TYPE_COUNT
} ObjectType;

typedef struct { int x, y; } Position;

typedef struct {
    Position pos;
    ObjectType type;
} GameObject;

typedef struct {
    Position segments[MAX_WORM_LEN];
    int length;
    Direction dir;
} Worm;

typedef struct {
    Worm worm;
    GameObject objects[NUM_OBJECTS];
    int score;
    int speed_ms;        // delay per tick; lower = faster
    int time_left_sec;
    int game_over;
    char face;            // 'H' happy, 'S' sad, 'N' neutral
} GameState;

static int cell_occupied(const GameState *g, int x, int y) {
    for (int i = 0; i < g->worm.length; i++)
        if (g->worm.segments[i].x == x && g->worm.segments[i].y == y) return 1;
    for (int i = 0; i < NUM_OBJECTS; i++)
        if (g->objects[i].pos.x == x && g->objects[i].pos.y == y) return 1;
    return 0;
}

static void spawn_object(GameState *g, int slot) {
    int x, y;
    do {
        x = rand() % GRID_WIDTH;
        y = rand() % GRID_HEIGHT;
    } while (cell_occupied(g, x, y));

    g->objects[slot].pos.x = x;
    g->objects[slot].pos.y = y;
    g->objects[slot].type = rand() % OBJECT_TYPE_COUNT;
}

void game_init(GameState *g) {
    g->worm.length = 3;
    for (int i = 0; i < g->worm.length; i++) {
        g->worm.segments[i].x = GRID_WIDTH / 2 - i;
        g->worm.segments[i].y = GRID_HEIGHT / 2;
    }
    g->worm.dir = RIGHT;

    g->score = 0;
    g->speed_ms = 150;
    g->time_left_sec = START_TIME_SEC;
    g->game_over = 0;
    g->face = 'N';

    for (int i = 0; i < NUM_OBJECTS; i++) spawn_object(g, i);
}

// Returns 0 if still playing, 1 if game just ended (collision)
int game_step(GameState *g, Direction input) {
    if (g->game_over) return 1;
    if (input != NONE) g->worm.dir = input;

    Position head = g->worm.segments[0];
    switch (g->worm.dir) {
        case UP:    head.y--; break;
        case DOWN:  head.y++; break;
        case LEFT:  head.x--; break;
        case RIGHT: head.x++; break;
        default: break;
    }

    // Wall collision
    if (head.x < 0 || head.x >= GRID_WIDTH || head.y < 0 || head.y >= GRID_HEIGHT) {
        g->game_over = 1;
        return 1;
    }

    // Self collision
    for (int i = 0; i < g->worm.length; i++)
        if (g->worm.segments[i].x == head.x && g->worm.segments[i].y == head.y) {
            g->game_over = 1;
            return 1;
        }

    // Object collision
    int ate_slot = -1;
    for (int i = 0; i < NUM_OBJECTS; i++)
        if (g->objects[i].pos.x == head.x && g->objects[i].pos.y == head.y) ate_slot = i;

    int grow = 0;
    if (ate_slot != -1) {
        switch (g->objects[ate_slot].type) {
            case APPLE:      g->score += 1; grow = 1; break;
            case GRAPES:     g->score += 5; grow = 1; break;
            case WATERMELON: if (g->speed_ms > 50) g->speed_ms -= 20; grow = 1; break;
            case STRAWBERRY: g->speed_ms += 20; grow = 1; break;
            case EMOJI_HAPPY: g->face = 'H'; break;
            case EMOJI_SAD:   g->face = 'S'; break;
            default: break;
        }
        spawn_object(g, ate_slot);
    }

    // Shift body: insert new head, drop tail unless growing
    for (int i = g->worm.length; i > 0; i--) g->worm.segments[i] = g->worm.segments[i - 1];
    g->worm.segments[0] = head;
    if (grow) g->worm.length++;

    return 0;
}

static char object_char(ObjectType t) {
    switch (t) {
        case APPLE: return 'A';
        case GRAPES: return 'G';
        case WATERMELON: return 'M';
        case STRAWBERRY: return 'S';
        case EMOJI_HAPPY: return ':';
        case EMOJI_SAD: return ';';
        default: return '?';
    }
}

void render_console(const GameState *g) {
    char grid[GRID_HEIGHT][GRID_WIDTH];
    for (int y = 0; y < GRID_HEIGHT; y++)
        for (int x = 0; x < GRID_WIDTH; x++) grid[y][x] = '.';

    for (int i = 0; i < NUM_OBJECTS; i++)
        grid[g->objects[i].pos.y][g->objects[i].pos.x] = object_char(g->objects[i].type);

    for (int i = 0; i < g->worm.length; i++)
        grid[g->worm.segments[i].y][g->worm.segments[i].x] = (i == 0) ? 'O' : 'o';

    printf("\033[H\033[J"); // clear terminal
    printf("Score: %d  Time: %ds  Face: %c\n", g->score, g->time_left_sec, g->face);
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) putchar(grid[y][x]);
        putchar('\n');
    }
}

// Simple demo loop: worm moves right automatically, no real input yet.
int main(void) {
    srand((unsigned) time(NULL));
    GameState g;
    game_init(&g);

    while (!g.game_over && g.time_left_sec > 0) {
        render_console(&g);
        game_step(&g, NONE); // swap NONE for real joystick input later
        usleep(g.speed_ms * 1000);
    }

    render_console(&g);
    printf("Game over! Final score: %d\n", g.score);
    return 0;
}