#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/mouse_cursor.h>
#include "headers/consts.h"
#include "headers/stack.h"

#include <stdio.h>
#include <stdbool.h>

// Fun��es
void initializeGame();
void updateGame();
void drawGame();
void cleanupGame();
void updateMenu();
void drawnMenu();

// Vari�veis globais
ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_EVENT_QUEUE* event_queue = NULL;
ALLEGRO_TIMER* timer = NULL;
ALLEGRO_FONT* font = NULL;
ALLEGRO_SAMPLE* bounce = NULL;
ALLEGRO_SAMPLE* point = NULL;
Paddle paddle1, paddle2;
Ball ball;
Player players;



int main() {
    // Inicializa a Allegro
    al_init();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(10);
    al_install_keyboard();
    al_install_mouse();
    
    initializeGame();

    al_start_timer(timer);

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    
    //Player manipulations
    
    char pName1[4];
    char pName2[4];

    FILE* inputName = fopen("score/name.txt", "r");
    //Leitura
    fscanf(inputName, "%s %s", pName1, pName2);
    //apaga o conetudo do arquivo para o proximo jogador
    // inputName = fopen("score/name.txt", "w");
    fclose(inputName);

    init_players(&players, pName1, pName2);
    


    while (1) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER) {
            updateGame();
            drawGame();
        }
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {

            
            break;
        }
    }

    FILE* output = fopen("score/mat.txt", "a");
    output_file(players, output);
    fclose(output);
    FILE* inputFinal = fopen("score/mat.txt", "r");
    FILE* outputFinal = fopen("score/matchhistory.txt", "w");
    insert_history(inputFinal, outputFinal);

    cleanupGame();

    return 0;
}
void updateMenu(){


}
void drawnMenu(){
    al_draw_filled_rounded_rectangle(SCREEN_WIDTH/2-OFFSET, SCREEN_HEIGHT/2+OFFSET, SCREEN_WIDTH/2-OFFSET+50, SCREEN_HEIGHT/2+OFFSET+50, 1,1, al_map_rgb(255,255,255));
    al_flip_display();
}
void initializeGame() {

    
    init_players(&players, "LFG\0", "AAA\0");

    // Configura��o do display
    display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    al_set_window_title(display, "Pong Game");

    // Configura��o do timer
    timer = al_create_timer(1.0 / FPS);

    // Configura��o da fila de eventos
    event_queue = al_create_event_queue();

    //Configuracao font
    font = al_load_font("font/MINE.ttf", 20, 0);

    //Sounds
    bounce = al_load_sample("music&fx/bounce.wav");
    point = al_load_sample("music&fx/point.wav");
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    
    // Inicializa��o das posi��es iniciais das raquetes e da bola
    paddle1.x = 10;
    paddle1.y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
    paddle1.speedY = 5;

    paddle2.x = SCREEN_WIDTH - PADDLE_WIDTH - 10;
    paddle2.y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
    paddle2.speedY = 5;

    ball.x = SCREEN_WIDTH / 2;
    ball.y = SCREEN_HEIGHT / 2;
    ball.speedX = 6;
    ball.speedY = 6;
}
void updateGame() {


    // Atualiza a posicao da bola
    ball.x += ball.speedX;
    ball.y += ball.speedY;

    // Verifica colisoes com as bordas da tela
    if (ball.y - BALL_SIZE / 2 < 0+OFFSET || ball.y + BALL_SIZE / 2 > SCREEN_HEIGHT-OFFSET) {
        ball.speedY = -ball.speedY;
    }

    //Verifica se a bola foi para fora
    if (ball.x - BALL_SIZE / 2 < 0) {
        ball.x = SCREEN_WIDTH/2;
        ball.y = SCREEN_HEIGHT/2;
        players.score2 += 100;
        al_play_sample(point, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
        
    }
    if(ball.x + BALL_SIZE / 2 > SCREEN_WIDTH){
        ball.x = SCREEN_WIDTH/2;
        ball.y = SCREEN_HEIGHT/2;
        players.score1 += 100;
        al_play_sample(point, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);

    }

    // Verifica colis�es com as raquetes
    if (ball.x - BALL_SIZE / 2 < paddle1.x + PADDLE_WIDTH+5 &&
        ball.x + BALL_SIZE / 2 > paddle1.x &&
        ball.y - BALL_SIZE / 2 < paddle1.y + PADDLE_HEIGHT+5 &&
        ball.y + BALL_SIZE / 2 > paddle1.y)
    {
        ball.speedX = -ball.speedX;
        al_play_sample(bounce, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);

    }

    if (ball.x - BALL_SIZE / 2 < paddle2.x + PADDLE_WIDTH+5 &&
        ball.x + BALL_SIZE / 2 > paddle2.x &&
        ball.y - BALL_SIZE / 2 < paddle2.y + PADDLE_HEIGHT+5 &&
        ball.y + BALL_SIZE / 2 > paddle2.y)
    {
        ball.speedX = -ball.speedX;
        
        al_play_sample(bounce, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
    }

    // Movimenta as raquetes
    ALLEGRO_KEYBOARD_STATE keyState;

    if (al_is_keyboard_installed()) {
        al_get_keyboard_state(&keyState);
        if (al_key_down(&keyState, ALLEGRO_KEY_W) && paddle1.y > 0) {
            paddle1.y -= paddle1.speedY;
        }

        if (al_key_down(&keyState, ALLEGRO_KEY_S) && paddle1.y + PADDLE_HEIGHT < SCREEN_HEIGHT) {
            paddle1.y += paddle1.speedY;
        }

        if (al_key_down(&keyState, ALLEGRO_KEY_UP) && paddle2.y > 0) {
            paddle2.y -= paddle2.speedY;
        }

        if (al_key_down(&keyState, ALLEGRO_KEY_DOWN) && paddle2.y + PADDLE_HEIGHT < SCREEN_HEIGHT) {
            paddle2.y += paddle2.speedY;
        }
    }

}
void drawGame() {
    al_clear_to_color(al_map_rgb(0, 0, 0));

    // Desenha as raquetes
    al_draw_filled_rectangle(paddle1.x, paddle1.y, paddle1.x + PADDLE_WIDTH, paddle1.y + PADDLE_HEIGHT, al_map_rgb(255, 255, 255));
    al_draw_filled_rectangle(paddle2.x, paddle2.y, paddle2.x + PADDLE_WIDTH, paddle2.y + PADDLE_HEIGHT, al_map_rgb(255, 255, 255));

    // Desenha a bola
    al_draw_filled_circle(ball.x, ball.y, BALL_SIZE / 2, al_map_rgb(255, 255, 255));
    al_draw_textf(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH/2, 20, ALLEGRO_ALIGN_CENTER, "- SCORE: %d | %d -", players.score1, players.score2);
    al_flip_display();
}

void cleanupGame() {
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_font(font);
}
