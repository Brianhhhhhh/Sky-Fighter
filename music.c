/*
 * music.c
 *
 * Author: <Brian Huang>
 *
 */
#include "music.h"
Note_t Song_Lose[] =
{
    {NOTE_G6,ONE_QUARTER,true},
    {NOTE_F6S,ONE_QUARTER,true},
    {NOTE_F6,ONE_QUARTER,true},

};
Note_t Song_Win[] =
{
    {NOTE_G6,ONE_QUARTER,true},
    {NOTE_A6S,ONE_QUARTER,true},
    {NOTE_C7S,ONE_QUARTER,true},


};
//***************************************************************
// This function returns how long an individual  notes is played
//***************************************************************
uint32_t music_get_time_delay(measure_time_t time)
{
    uint32_t time_return = 0;
    time_return  = MEASURE_DURATION * MEASURE_RATIO;
    switch(time)
    {
        case ONE_QUARTER:
        {
            time_return  = time_return / 4;
            break;
        }
        case ONE_HALF:
        {
            time_return  = time_return / 2;
            break;
        }
        case ONE_EIGTH:
        {
            time_return  = time_return / 8;
            break;
        }
        case THREE_EIGTH:
        {
            time_return = time_return * 3;
            time_return  = time_return / 8;
            break;
        }
        default:
        {
            break;
        }
    }
    return time_return - DELAY_AMOUNT;
}
//***************************************************************************
// Plays a single note of the song based on note_index.  After
// the note is played, there is an optional delay in between
// notes.
//
// Examples
// Song[note_index].period       -- Used to determine the period of the
//                                  PWM pulse.
//
// Song[note_index].time         -- 1/4 or 1/2 time note.  Call
//                                  music_get_time_delay() to determine how
//                                  long to play the note
//
// Song[note_index].delay        -- If true, add a period of silence for
//                                  DELAY_AMOUNT
//
//                                  If false, return without delaying.
//*************************************************************************
//first block is to initialize the timerA and make it generate the pwm signal for each note.
//Then the second block is to determine how long the signal should be generated.
//Finally the third block determines if there should be some silence after the note being played.
static void music_play_note_lose(uint16_t note_index)
{
    //initialize buzzer and timerA0
    ece353_MKII_Buzzer_Init(Song_Lose[note_index].period);

    //turn on the buzzer
    ece353_MKII_Buzzer_On();

    //play the note for specific time
    ece353_T32_1_wait(music_get_time_delay(Song_Lose[note_index].time));

    //turn off the buzzer
    ece353_MKII_Buzzer_Off();


    //if a period of silence should be added
    if(Song_Lose[note_index].delay){
        ece353_T32_1_wait(DELAY_AMOUNT);
    }
}

//***************************************************************
// Plays the lose song (loop through, playing each note)
// and then returns
//***************************************************************
void music_play_song_lose(void)
{
    int i = 0;
    for(i = 0; i < 3; i++){
        music_play_note_lose(i);
    }

}
static void music_play_note_win(uint16_t note_index)
{
    //initialize buzzer and timerA0
    ece353_MKII_Buzzer_Init(Song_Win[note_index].period);

    //turn on the buzzer
    ece353_MKII_Buzzer_On();

    //play the note for specific time
    ece353_T32_1_wait(music_get_time_delay(Song_Win[note_index].time));

    //turn off the buzzer
    ece353_MKII_Buzzer_Off();


    //if a period of silence should be added
    if(Song_Win[note_index].delay){
        ece353_T32_1_wait(DELAY_AMOUNT);
    }
}
//***************************************************************
// Plays the song (loop through, playing each note)
// and then returns
//***************************************************************
void music_play_song_win(void)
{
    int i = 0;
    for(i = 0; i < 3; i++){
        music_play_note_win(i);
    }

}
