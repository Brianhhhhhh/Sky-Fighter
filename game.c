

#include <main.h>

//author: Brian Huang

QueueHandle_t Queue_game_info;
TaskHandle_t Task_game_play_Handle;

int enemy_array_width = 0;
int enemies[70][3] = { };
int bullet_array_width = 0;
int bullets[50][3] = { };
int x = 66;
int y = 100;
bool won = false;
bool play_once = false;

/* This provides the main functionality of the whole game.*/

void task_game_play(void *pvParameters)
{

    //initialize different values before game starts
    float lux = 0.0;
    int velocity[2] = { 0, 0 };
    int enemy_vel = 1;
    int bullet_vel = -10;
    int end_game = 0; //0 dont end, 1 win, 2 loss
    int cnt = 0;
    int thresh = 35;
    int phase = 0;
    int total_phases = 5;
    ACC_DIR_t dir;

    while (1)
    {
        lux = opt3001_read_lux();
        if (screen_update)
        {
            screen_update = false;
            x = (x + velocity[0]);
            y = (y - velocity[1]);

            //Add enemies at an increasing rate and increase their speed or spawn rate
            cnt++;
            if(cnt > thresh){
                cnt = 0;
                phase++;
                if(phase % 2 == 0 && thresh > 25){
                    thresh--;
                }
                else if(enemy_vel < 4){
                    enemy_vel++;
                }
                if(phase > total_phases){
                    //If you make it through all phases, you win
                    end_game = 1;
                }
                add_enemy();
            }

            //Don't let ship exceed screen boundaries
            x = x < 11 ? 11 : x;
            y = y < 11 ? 11 : y;
            x = x > 122 ? 122 : x;
            y = y > 122 ? 122 : y;

            int i;
            //Move enemies and check for collisions
            for (i = 0; i < enemy_array_width; i++)
            {
                if (collisionHandler(i))
                {
                    end_game = 2;
                }
                enemies[i][1] += enemy_vel;
                if(enemies[i][1] > 132){
                    //If an enemy reaches the bottom, end the game
                    end_game = 2;
                }
            }
            //Remove destroyed enemies
            for (i = 0; i < enemy_array_width; i++)
            {
                if (enemies[i][2] == 0)
                {
                    //If hit, remove. Must decrement i since the index is replaced and enemy_array_width is decremented
                    removeFromEnemies(i);
                    i--;
                }
            }
            for (i = 0; i < bullet_array_width; i++)
            {
                bullets[i][1] += bullet_vel;
                if(bullets[i][1] < 0){
                                    bullets[i][2] = 0;
                                }
            }

            //Remove destroyed bullets
                        for (i = 0; i < bullet_array_width; i++)
                        {
                            if (bullets[i][2] == 0)
                            {
                                //If hit, remove. Must decrement i since the index is replaced and bullet_array_width is decremented
                                removeFromBullets(i);
                                i--;
                            }
                        }


            for (i = 0; i < enemy_array_width; i++)
                        {
                            if (enemies[i][2] == 0)
                            {
                                //If hit, remove. Must decrement i since the index is replaced and enemy_array_width is decremented
                                removeFromEnemies(i);
                                i--;
                            }
                        }
            displayScreen(end_game);
        }
        if (end_game == 0 && !won)
        {

            xQueueReceive(Queue_game_info, &dir, 1);

            if (dir == ACC_DIR_UP)
            {
                velocity[1] = 8;

            }
            else if (dir == ACC_DIR_DOWN)
            {
                velocity[1] = -8;
            }
            if (dir == ACC_DIR_RIGHT)
            {
                velocity[0] = 8;
            }
            else if (dir == ACC_DIR_LEFT)
            {
                velocity[0] = -8;
            }

        }
        else
        {
            if (lux < 35.0)
            {
                x = 66;
                y = 100;
                velocity[0] = 0;
                velocity[1] = 0;
                end_game = 0;
                enemy_array_width = 0;
                bullet_array_width = 0;
                cnt = 0;
                enemy_vel = 1;
                thresh = 35;
                phase = 0;
                if(won){
                    total_phases++;//Makes game harder on next run if you won
                }

                won = false;
            }
        }
        dir = ACC_DIR_CENTER;

    }
}

/* Updates the screen based on different scenarios*/
void displayScreen(int end_game)
{

    //if the game is not end
    if (end_game == 0)
    {
        play_once = false;
        //clear screen
        lcd_draw_rectangle(CENTER_COL, CENTER_ROW, SCREEN_X, SCREEN_Y,
                           LCD_COLOR_BLACK);
        //draw spaceship
        lcd_draw_image(x, y, SPACESHIP_WIDTH, SPACESHIP_HEIGHT,
                       Bitmaps_Spaceship, LCD_COLOR_CYAN, LCD_COLOR_BLACK);

        //draw enemies
        int i;
        for (i = 0; i < enemy_array_width; i++)
        {
            lcd_draw_image(enemies[i][0], enemies[i][1], ENEMY_WIDTH,
                           ENEMY_HEIGHT, Bitmaps_Enemy, LCD_COLOR_RED,
                           LCD_COLOR_BLACK);
        }

        //draw bullets
        for (i = 0; i < bullet_array_width; i++)
        {
            lcd_draw_rectangle(bullets[i][0], bullets[i][1], 3, 3,
                               LCD_COLOR_WHITE);
        }
    }
    //If the player has lost the game
    else if(end_game == 2 && !won)
    {
        //Loss screen
        lcd_draw_rectangle(40, CENTER_ROW, 20, 90, LCD_COLOR_RED);
        lcd_draw_rectangle(60, CENTER_ROW + 45, 60, 20, LCD_COLOR_RED);

        if(play_once == false){
            music_play_song_lose();
            play_once = true;
        }
    }
    //If the player has won the game
    else if(end_game == 1){
        //Win Screen
        won = true;
        lcd_draw_rectangle(25, CENTER_ROW, 20, 90, LCD_COLOR_GREEN);
        lcd_draw_rectangle(65, CENTER_ROW + 45, 100, 20, LCD_COLOR_GREEN);
        lcd_draw_rectangle(105, CENTER_ROW, 20, 90, LCD_COLOR_GREEN);
        lcd_draw_rectangle(65, CENTER_ROW + 20, 20, 50, LCD_COLOR_GREEN);
        if(play_once == false){
            music_play_song_win();
            play_once = true;
        }
    }
}

/* Add the enemy to the screen*/
void add_enemy(void)
{
    int i;
    for(i = 0; i < 6; i++){
        enemies[enemy_array_width][0] = 11 + 20 * i;
        enemies[enemy_array_width][1] = 10;
        enemies[enemy_array_width][2] = 1;
        enemy_array_width++;
    }
}

/* Remove the enemy when they're shot by bullet*/

bool removeFromEnemies(int index)
{
    if (enemy_array_width <= 0)
    {
        return false;
    }
    enemies[index][0] = enemies[enemy_array_width - 1][0];
    enemies[index][1] = enemies[enemy_array_width - 1][1];
    enemies[index][2] = enemies[enemy_array_width - 1][2];
    enemies[enemy_array_width - 1][0] = 0;
    enemies[enemy_array_width - 1][1] = 0;
    enemies[enemy_array_width - 1][2] = 0;
    enemy_array_width--;
    return true;
}

/* Remove the enemy when they shot the enemy on target*/

bool removeFromBullets(int index)
{
    if (bullet_array_width <= 0)
    {
        return false;
    }
    bullets[index][0] = bullets[bullet_array_width - 1][0];
    bullets[index][1] = bullets[bullet_array_width - 1][1];
    bullets[index][2] = bullets[bullet_array_width - 1][2];
    bullets[bullet_array_width - 1][0] = 0;
    bullets[bullet_array_width - 1][1] = 0;
    bullets[bullet_array_width - 1][2] = 0;
    bullet_array_width--;
    return true;
}

//enemies are the only place where collisions matter, so I'm only checking them
//returns true if game is ended
bool collisionHandler(int index)
{
    //check for collision with ship
    //I gave a little extra space to make it feel more fair
    if (abs(x - enemies[index][0]) <= 13)
    {
        if (abs(y - enemies[index][1] <= 14))
        {
            //the enemy is touching the spaceship
            return true;
        }
    }
    int i;
    for (i = 0; i < bullet_array_width; i++)
    {
        if (abs(bullets[i][0] - enemies[index][0]) <= 8)
        {
            if (abs(bullets[i][1] - enemies[index][1]) <= 7)
            {
                //The enemy was hit, so remove the bullet and set the enemy to be removed.
                removeFromBullets(i);
                enemies[index][2] = 0;
                return false;
            }
        }
    }
    return false;
}

