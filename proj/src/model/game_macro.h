#ifndef GAME_MACRO_H
#define GAME_MACRO_H

#define GRID_ROWS 10
#define GRID_COLS 10


#define CELL_WIDTH 33
#define CELL_HEIGHT 33

#define NUM_SHIPS 5

#define SHIP_TYPE_TO_SIZE(type) ((type == NO_SHIP) ? 0 : (int)type)


#define ESC_KEY 0x81
#define Q_KEY 0x10
#define SPACE_KEY 0x39
#define M_KEY 0x32
#define ENTER_KEY 0x1C
#define R_KEY 0x13
#define S_KEY 0x1F




typedef enum {
    NO_SHIP,
    SHIP_1,
    SHIP_2,
    SHIP_3,
    SHIP_4,
} ShipType;


typedef struct {
    ShipType type;
    int size;
    int orientation; // 0->horizontal and 1->vertical ?
    int start_row, start_col;
    //what else?
} Ship;


typedef enum {
    EMPTY,
    SHIP,
    HIT,
    MISS,
} CellState;


typedef struct {
    CellState state;
    int ship_id; //-1 if no ship
} Cell;


typedef struct {
    Cell cells[GRID_ROWS][GRID_COLS];
    Ship ships[NUM_SHIPS];
    int sprite_x, sprite_y; //position of grid sprite (it has coordinates etc)
    int x, y; //position of the actual first cell
} Grid;


typedef struct {
    Grid player1_grid;
    Grid player2_grid;
} Arena;





#endif
