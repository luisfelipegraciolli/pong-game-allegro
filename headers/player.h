#ifndef _PLAYER_H
#define _PLAYER_H
#include <string.h>
typedef struct Player
{
    char player_initials[4];
    int score;
}Player;

Player init_player(char initials[]){
    Player player;
    strcpy(player.player_initials, initials);
    player.score = 0;
    return player;
}


#endif
