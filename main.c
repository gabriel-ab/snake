#include <raylib.h>
#define SPACE 20
#define HEIGHT_GRID 30*SPACE
#define WIDTH_GRID 50*SPACE

bool passed(double seconds){
    double tempo_atual = GetTime();
    static double tempo_anterior = 0;

    if(tempo_atual - tempo_anterior >= seconds){
        tempo_anterior = tempo_atual;
        return 1;
    }
    else return 0;

}

int main(){
    InitWindow(WIDTH_GRID,HEIGHT_GRID,"SNAKE");

    Vector2 snake_pos[100] = {
        20*SPACE,20*SPACE,
        20*SPACE,21*SPACE,
        20*SPACE,22*SPACE,
        20*SPACE,23*SPACE
    };
    int snake_tail = 4;
    int score = 0;
    Vector2 direction = {1*SPACE,0};
    Vector2 food = {GetRandomValue(1,49)*SPACE, GetRandomValue(1,29)*SPACE};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // UPDATE
        if(passed(0.1)){
            for( int i = snake_tail -1; i > 0; i--){
                snake_pos[i] = snake_pos[i-1];
            }
            snake_pos[0].x += direction.x;
            snake_pos[0].y += direction.y;
        }
        // Growing
        if(food.x == snake_pos[0].x && food.y == snake_pos[0].y){
            snake_pos[snake_tail] = snake_pos[snake_tail-1];
            snake_tail++;
            score = 20*snake_tail;
            food = (Vector2){GetRandomValue(1,49)*SPACE, GetRandomValue(1,29)*SPACE};
        }
        // Damage
        for(int i = 1; i < snake_tail; i++){
            if(snake_pos[0].x == snake_pos[i].x && snake_pos[0].y == snake_pos[i].y){
                snake_tail = i;
                score = 20*snake_tail;
                break;
            }
        }
        // End Game
        if( 
            snake_pos[0].x <= 0 || 
            snake_pos[0].y <= 0 || 
            snake_pos[0].x >= WIDTH_GRID || 
            snake_pos[0].y >= HEIGHT_GRID
        ){
            break;
        }
        // INPUT
        if(IsKeyPressed(KEY_W) && direction.y !=  SPACE) direction = (Vector2){ 0,-SPACE};
        if(IsKeyPressed(KEY_A) && direction.x !=  SPACE) direction = (Vector2){-SPACE, 0};
        if(IsKeyPressed(KEY_S) && direction.y != -SPACE) direction = (Vector2){ 0, SPACE};
        if(IsKeyPressed(KEY_D) && direction.x != -SPACE) direction = (Vector2){ SPACE, 0};

        if(IsKeyPressed(KEY_SPACE)) snake_tail++;
        
        BeginDrawing();
            ClearBackground(BLACK);
            DrawCircleV(food,8,GREEN);
            DrawCircleV(snake_pos[0],10,YELLOW);
            for (int i = 1; i < snake_tail; i++){
                DrawCircleV(snake_pos[i],10,PURPLE);
            }
            DrawRectangleLinesEx((Rectangle){0,0,WIDTH_GRID,HEIGHT_GRID},3,RED);
            DrawText(TextFormat("SCORE: %i", score),20,20,20,YELLOW);
            DrawText("Made by Gabriel", WIDTH_GRID - 180, HEIGHT_GRID - 30, 20, (Color){100,100,100,50});
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}