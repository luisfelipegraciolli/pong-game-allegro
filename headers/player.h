#pragma once
#include <string.h>


typedef struct{
    long score1;
    char name1[4];
    long score2;
    char name2[4];
}Player;

typedef struct{
    Player* leaderboard;
    int n;
    int capacity;
} StackScores;



void init_players(Player* player, char name1[], char name2[]) {
    player->score1 = 0;
    player->score2 = 0;
    strcpy(player->name1, name1);
    strcpy(player->name2, name2);
}
