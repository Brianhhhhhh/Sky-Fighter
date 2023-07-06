//author: Brian Huang

#ifndef GAME_H_
#define GAME_H_

#include <main.h>

extern TaskHandle_t Task_game_play_Handle;
extern QueueHandle_t Queue_game_info;


#define SCREEN_X            132
#define SCREEN_Y            132

#define SCREEN_CENTER_COL    ((SCREEN_X/2)-1)
#define SCREEN_CENTER_ROW    ((SCREEN_Y/2)-1)

#define LINE_WIDTH          4
#define LINE_LENGTH         (SCREEN_X - 1)

#define SQUARE_SIZE         32

#define PADDING             2

#define LEFT_COL                      (SCREEN_CENTER_COL - SQUARE_SIZE - (2*PADDING) - LINE_WIDTH)
#define CENTER_COL                    (SCREEN_CENTER_COL)
#define RIGHT_COL                     (SCREEN_CENTER_COL + SQUARE_SIZE + (2*PADDING) + LINE_WIDTH)

#define UPPER_ROW                     (SCREEN_CENTER_ROW - SQUARE_SIZE - (2*PADDING) - LINE_WIDTH)
#define CENTER_ROW                    (SCREEN_CENTER_ROW)
#define LOWER_ROW                     (SCREEN_CENTER_ROW + SQUARE_SIZE + (2*PADDING) + LINE_WIDTH)

void task_game_play(void *pvParameters);

void displayScreen(int end_game);

bool removeFromEnemies(int index);

bool removeFromBullets(int index);

bool collisionHandler(int index);

void add_enemy();

#endif /* GAME_H_ */
