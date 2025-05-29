#ifndef GAME_MACRO_H
#define GAME_MACRO_H

#define GRID_ROWS 10
#define GRID_COLS 10
#define GRID_HEIGHT 378
#define GRID_WIDTH 396

#define CELL_WIDTH 33
#define CELL_HEIGHT 33

#define NUM_SHIPS 8

#define SHIP_TYPE_TO_SIZE(type) ((type == NO_SHIP) ? 0 : (int)type)


#define ESC_KEY 0x81
#define Q_KEY 0x10
#define SPACE_KEY 0x39
#define M_KEY 0x32
#define ENTER_KEY 0x1C
#define R_KEY 0x13
#define S_KEY 0x1F
#define UP_ARROW_KEY 0x48
#define DOWN_ARROW_KEY 0x50


#define BLACK 0x000000
#define RED 0xFF0000
#define PINK 0xFF00FF
#define BLUE 0x0000FF
#define BETTER_BLUE 0x4f80a8
#define YELLOW 0xFFFF00
#define PURPLE 0x800080
#define HOVER_COLOR 0xAAAAFF
#define SHIP_HOVER_COLOR 0xdb67b8
#define ORANGE 0xFFA500
#define NAVY_BLUE 0x293f87
#define TEAL 0x297487



typedef enum {
    NO_SHIP,
    SHIP_1,
    SHIP_2,
    SHIP_3,
    SHIP_4,
} ShipType;


typedef enum {
    ALIVE,
    SUNK
} ShipStatus;


typedef struct {
    ShipType type;
    int size;
    int orientation; // 0->horizontal and 1->vertical ?
    int start_row, start_col;
    ShipStatus status; 
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
    int ships_remaining; //to check if player has ships left (if 0 then player lost)
    int sprite_x, sprite_y; //position of grid sprite (it has coordinates etc)
    int x, y; //position of the actual first cell
} Grid;


typedef struct {
    Grid player1_grid;
    Grid player2_grid;
} Arena;


typedef enum {
  SETUP_PLAYER1,
  SETUP_PLAYER2,
  READY_PHASE
} ArenaPhase;


typedef enum {
  PLAYER_1,
  PLAYER_2
} PlayerTurn;






#endif
