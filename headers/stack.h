#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXSIZE 1024    
typedef struct{
    long score1;
    char name1[4];
    long score2;
    char name2[4];
} Player;

void init_players(Player *player, char name1[], char name2[])
{
    player->score1 = 0;
    player->score2 = 0;
    strcpy(player->name1, name1);
    strcpy(player->name2, name2);
}

void set_score(Player *player, int score1, int score2)
{
    player->score1 = score1;
    player->score2 = score2;
}

void output_file(Player s, FILE *f)
{

    fprintf(f, "%s %d %s %d\n", s.name1, s.score1, s.name2, s.score2);
}

void insert_history(FILE* input, FILE* output){
    Player stack[MAXSIZE];
    int n = 0;
    char name1[4];
    char name2[4];
    int score1, score2;
    while(fscanf(input, "%s %d %s %d", name1, &score1, name2, &score2) == 4){
        Player temp;
        strcpy(temp.name1, name1);
        strcpy(temp.name2, name2);
        temp.score1 = score1;
        temp.score2 = score2;
        stack[n++] = temp;
    }

    for(int i = n-1; i>=0; i--){
        fprintf(output,"%s %d %s %d\n", stack[i].name1, stack[i].score1, stack[i].name2, stack[i].score2);
    }
}
