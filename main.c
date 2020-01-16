#include <raylib.h>
#define SPACE 20
#define GRID_HEIGHT 30
#define GRID_WIDTH 50
#define WINDOW_HEIGHT GRID_HEIGHT*SPACE
#define WINDOW_WIDTH GRID_WIDTH*SPACE

bool has_passed(double seconds){
    double tempo_atual = GetTime();
    static double tempo_anterior = 0;

    if(tempo_atual - tempo_anterior >= seconds){
        tempo_anterior = tempo_atual;
        return 1;
    }
    else return 0;

}

int main(){
    InitWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"SNAKE");

    Vector2 snake[100] = {
        20*SPACE,20*SPACE,
        20*SPACE,21*SPACE,
        20*SPACE,22*SPACE,
        20*SPACE,23*SPACE
    };
    int snake_tail = 4;
    int score = 0;
    float speed = 12;
    Vector2 old_direction = {0,0};
    Vector2 direction = {1*SPACE,0};
    Vector2 food = {GetRandomValue(1,GRID_WIDTH -1)*SPACE, GetRandomValue(1,GRID_HEIGHT -1)*SPACE};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // UPDATE
        if(has_passed(1/speed)){
            for( int i = snake_tail -1; i > 0; i--){
                snake[i] = snake[i-1];
            }
            if(old_direction.x == -direction.x) direction.x = old_direction.x;
            else if(old_direction.y == -direction.y) direction.y = old_direction.y;
            
            snake[0].x += direction.x;
            snake[0].y += direction.y;
            
            old_direction = direction;
        }
        // Growing
        if(food.x == snake[0].x && food.y == snake[0].y){
            snake[snake_tail] = snake[snake_tail-1];
            snake_tail++;
            speed += 0.2;
            score = 10*snake_tail;
            food = (Vector2){GetRandomValue(1,GRID_WIDTH -1)*SPACE, GetRandomValue(1,GRID_HEIGHT -1)*SPACE};
        }
        // Damage
        for(int i = 1; i < snake_tail; i++){
            if(snake[0].x == snake[i].x && snake[0].y == snake[i].y){
                snake_tail = i;
                score = 20*snake_tail;
                break;
            }
        }
        // End Game
        if( 
            snake[0].x <= 0 || 
            snake[0].y <= 0 || 
            snake[0].x >= WINDOW_WIDTH || 
            snake[0].y >= WINDOW_HEIGHT ||
            score == 1000
        ){
            break;
        }
        // INPUT
        if(IsKeyPressed(KEY_W)) direction = (Vector2){ 0,-SPACE};
        else if(IsKeyPressed(KEY_A)) direction = (Vector2){-SPACE, 0};
        else if(IsKeyPressed(KEY_S)) direction = (Vector2){ 0, SPACE};
        else if(IsKeyPressed(KEY_D)) direction = (Vector2){ SPACE, 0};

        BeginDrawing();
            ClearBackground(BLACK);
            DrawCircleV(food,8,GREEN);
            DrawCircleV(snake[0],10,YELLOW);
            for (int i = 1; i < snake_tail; i++){
                DrawCircleV(snake[i],10,PURPLE);
            }
            DrawRectangleLinesEx((Rectangle){0,0,WINDOW_WIDTH,WINDOW_HEIGHT},3,RED);
            DrawText(TextFormat("SCORE: %i", score),20,20,20,YELLOW);
            DrawText("Made by Gabriel", WINDOW_WIDTH - 180, WINDOW_HEIGHT - WINDOW_HEIGHT, 20, (Color){100,100,100,50});
        EndDrawing();
    }
    while(!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(BLACK);
            DrawLineEx((Vector2){0,GetScreenHeight()},(Vector2){GetScreenWidth(),0},200,(Color){10,10,10,255});
            DrawText("END GAME",GetScreenWidth()/2 -MeasureText("END GAME",30)/2,GetScreenHeight()/2 - 20, 30, WHITE);
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}