#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct{
    long score1;
    char name1[4];
    long score2;
    char name2[4];
} Player;

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

void set_score(Player* player, int score1, int score2){
    player->score1 = score1;
    player->score2 = score2;
    
}


void init_stack(StackScores* s){
    s->n = 0;
    s->capacity = 1;
    s->leaderboard = (Player*) malloc(sizeof(Player));
}

void output_file(Player s, FILE* f){

    fprintf(f,"%s %d %s %d\n", s.name1, s.score1, s.name2, s.score2);
    
}

void push_to_stack(StackScores* s, Player player){
    if(s->capacity == s->n){
        s->capacity *= 2;
        s->leaderboard = (Player*) realloc(s->leaderboard, sizeof(Player)*s->capacity);
    }
    s->leaderboard[s->n++] = player;
}

Player pop(StackScores* s){
    return s->leaderboard[--s->n];
}

void free_stack(StackScores* s){
    free(s->leaderboard);
}

void reverse(StackScores* s, FILE* f, FILE* out){
    
    int line = 1;
    char c;
    do{
        c = fgetc(f);
        if(c == '\n'){
            line++;
        }
    }while(c != EOF);
    Player temp;
    for (int i = 0; i < line; i++)
    {
        char name1[4];
        char name2[4];
        int score1 = 0;
        int score2 = 0;

        fscanf(f, "%s %d %s %d", &name1, &score1, &name2, &score2);
        init_players(&temp, name1, name2);
        set_score(&temp, score1, score2);
        push_to_stack(s, temp);
    }
    //print to final file
    printf("wtf\n");

    for (int i = s->n-1; i>0; i--)
    {
        fprintf(out, "%s %d VS %s %d\n", s->leaderboard[i].name1, s->leaderboard[i].score1,s->leaderboard[i].name2, s->leaderboard[i].score2);
    }


}


