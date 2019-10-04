/*******************************************************************************************
*
*   raylib [core] example - basic window
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/
#include "raylib.h"
typedef enum GameScreen {EMPRESA, LOGO, TITLE, GAMEPLAY, ENDING, EASTEREGG } GameScreen;
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "SuperMegaUltraGigaDeadlyPong");
   
   // Textures
    Texture2D jugador = LoadTexture ("resources/jugador.png");
    Texture2D enemigo = LoadTexture ("resources/enemigo.png");
    Texture2D pelota = LoadTexture ("resources/pelota.png");
    Texture2D campo = LoadTexture ("resources/campo.png");
    Texture2D fondo= LoadTexture ("resources/Logo.png");
    Texture2D menu = LoadTexture ("resources/fondo.png");
    Texture2D dance = LoadTexture ("resources/dancers.png");
    Texture2D lul = LoadTexture ("resources/lul.png");
    
    // Rectangles 
    Rectangle botonstart=  { screenWidth/2 - 100, screenHeight/2, 200, 80};
    Rectangle botonquit= {0,0, 70, 30};
    Rectangle botonoptions= { screenWidth/2 - 50, screenHeight/1.2, 100, 30 };
    Rectangle back= {screenWidth/2, screenHeight/2+150, 200, 30};
    Rectangle player= {0, screenHeight/2-100, 20, 120};
    Rectangle versus= {780, screenHeight/2-100, 20,120};
    Rectangle baile= {0,0, dance.width/6, dance.height/7};
    Rectangle dificl= {500,100,100,100};
    
    // Floats
    float rotation = 0;
    float radius= (20);
    float alpha = 0.0f;
    float beta = 1.0f;
    
    // Vectors2
    Vector2 bola= {screenWidth/2, screenHeight/2};
    Vector2 speed= {5,6}; 
    
    // Bools
    bool pause = true;
    bool fade = false;
    bool fade2 = false;    
    bool pesadilla = false;
    
    
    //ints
    int framseCounter= 30;
    int Victory = 0;
    int Lose = 0;
    int canvio = 10;
    int currentFrameX = 0;
    int currentFrameY = 0;
    int animacion = 0;
    
    //So
    InitAudioDevice();
    
    Sound impac = LoadSound ("resources/pelotavsrectangulo.wav");
    Sound start = LoadSound ("resources/startboton.wav");
    Sound egg = LoadSound ("resources/eastereggboton.wav");
    Music music = LoadMusicStream ("resources/musica.ogg");
    Sound score = LoadSound ("resources/score.wav");
    Music comedi = LoadMusicStream ("resources/comedi.ogg");
    
    GameScreen currentScene = EMPRESA;
   
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------
    // Main game lo
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
       if(fade) alpha += 0.01f;
       else if(!fade) alpha -= 0.01f;
      
       if(alpha >= 1.0f) alpha = 1.0f;
       else if (alpha <= 0.0f) alpha = 0.0f;
       
       if(fade2) beta += 0.01f;
       else if(!fade2) beta -= 0.01f;
      
       if(beta >= 1.0f) beta = 1.0f;
       else if (beta <= 0.0f) beta = 0.0f;
       
       framseCounter++;
       canvio++; 
        
        switch(currentScene)
        {
            case EMPRESA:
            
            if (IsKeyPressed(KEY_ENTER))
            {
                fade = !fade;
            }
                if (alpha == 1.0f)
                {
                   fade = !fade; 
                   currentScene=LOGO;
                }

            break;
            
            case LOGO:
            if(IsKeyPressed(KEY_ENTER)) 
            {
                fade= !fade;
            }
            if (alpha == 1.0f)
                {
                   fade = !fade; 
                   currentScene=TITLE;
                }
            break;
            
            case TITLE:
            
            if (CheckCollisionPointRec (GetMousePosition(), botonstart))
            {
                if(IsMouseButtonDown(0)) 
                {
                    PlaySound (start);
                    fade= !fade;
                }
            }
                if (alpha == 1.0f)
                {
                    fade = !fade; 
                    currentScene = GAMEPLAY;
                }
            
            if (CheckCollisionPointRec (GetMousePosition(), botonquit))
            {
                if(IsMouseButtonReleased(0)) 
                {
                   CloseWindow();     
                }
            }
            if (CheckCollisionPointRec (GetMousePosition(), botonoptions))
            {
                if(IsMouseButtonPressed(1))                    
                {
                   fade2= !fade2;
                   PlaySound (egg);
                }
            }
                if (beta == 1.0f)
                {
                    fade2 = !fade2; 
                    currentScene = EASTEREGG;
                }
            
            
            break;

            case GAMEPLAY:
            UpdateMusicStream(music);
            PlayMusicStream (music);
                if (IsKeyPressed (KEY_SPACE))
                {
                    pause=!pause;
                    framseCounter=30;
                }
                if (!pause)
                {
                   
                    bola.x += speed.x;
                    bola.y += speed.y;
                    rotation +=5;
                        if(bola.x + radius >= screenWidth || bola.x - radius <= 0)
                            {
                                speed.x *= -1;
                                rotation *=-1;
                            }
                        if(bola.y + radius >= screenHeight || bola.y - radius <= 0)
                            {
                                speed.y *= -1;
                            }
                        if (bola.x - radius <=0 )
                                Victory++, PlaySound (score);
                                else if (Victory >=5)
                                {
                                    fade= !fade;
                                    Victory=0;
                                }
                                    if (alpha == 1.0f)
                                    {
                                        fade = !fade; 
                                        currentScene=ENDING;
                                    }
                        if (bola.x + radius >= screenWidth)
                                Lose++, PlaySound (score);
                                else if (Lose >=5)
                                {
                                    fade= !fade;
                                    Lose=0;
                                }
                                    if (alpha == 1.0f)
                                    {
                                        fade = !fade; 
                                        currentScene=ENDING;
                                    }
                        if(CheckCollisionCircleRec(bola, radius, player))
                        {
                            if(bola.x + radius >= player.x || bola.x - radius <= player.x + player.width)
                            {
                                speed.x *=-1;
                                rotation *=-1;
                                PlaySound (impac);                                
                            }
                        }
                        if(CheckCollisionCircleRec(bola, radius, versus))
                        {
                            if(bola.x + radius >= versus.x || bola.x - radius <= versus.x + versus.width)
                            {
                                speed.x *=-1;
                                rotation *=-1;
                                PlaySound (impac);
                            }
                        }
                        if(bola.x >= screenWidth/2)
                        {
                            if(speed.x >= 0)
                            {
                                if(bola.y <= versus.y + versus.height/2) versus.y -= 5;
                                else if(bola.y >= versus.y + versus.height/2) versus.y += 5;
                            }
                    }
            
                if(IsKeyDown(KEY_UP)) player.y -= 5;
                if(IsKeyDown(KEY_DOWN)) player.y += 5;
                
                if (player.y <= 0) player.y = 0;
                else if (player.y + player.height >= screenHeight) player.y = screenHeight - player.height;
                
                if (versus.y <= 0) versus.y = 0;
                else if (versus.y + versus.height >= screenHeight) versus.y = screenHeight - versus.height;
            }
                else
                {
                    framseCounter++;
                }
                

        
            break;
           
            case ENDING:
                if(IsKeyPressed(KEY_SPACE)) 
                    {
                        fade= !fade;      
                    }
                    if (alpha == 1.0f)
                        {
                        fade = !fade; 
                        currentScene = TITLE;
                        }
            break;
            
            case EASTEREGG:
                animacion++;
                UpdateMusicStream(comedi);
                PlayMusicStream (comedi);
                if(animacion>2)
                {
                    animacion=0;
                    currentFrameX++;
                    if (currentFrameX >= 6)
                    {
                        currentFrameX = 0,
                        currentFrameY++;
                            if (currentFrameY>=5)
                            {
                                currentFrameY = 0;
                            }
                    }
                }
                if (CheckCollisionPointRec (GetMousePosition(), back))
                {
                    if(IsMouseButtonReleased(0)) 
                    {
                        fade= !fade;
                    }
                }
                        if (alpha == 1.0f)
                        {
                        fade = !fade; 
                        currentScene = TITLE;
                        }
                baile.x = currentFrameX*dance.width/6;
                baile.y = currentFrameY*dance.height/7;
                
            break;
        }
        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
           ClearBackground(RAYWHITE);
           
          
          switch(currentScene)
            { 
                case EMPRESA:
                DrawTexture(fondo, 0,0, WHITE);
                break;
            
                case LOGO:
                DrawRectangle(0, 0, screenWidth, screenHeight, WHITE);
                DrawText ("A Sant Marc Production", screenWidth-570, screenHeight/2+80, 30, YELLOW);
                DrawText ("SuperMegaUltraGigaDeadlyPong", screenWidth-780, screenHeight/2, 49, YELLOW);
                if((framseCounter/30)%2) DrawText("Preasure ENTER to continue", (screenWidth - MeasureText("Preasure ENTER to continue", 30))/2, screenHeight -30, 30, RED);
                break;
            
            
                case TITLE:
                DrawTexture (menu,0,0,WHITE);
                DrawRectangleRec (botonquit, ORANGE);
                DrawRectangleRec(botonstart, RED);
                if (CheckCollisionPointRec (GetMousePosition(), botonstart))
                {
                    if (IsMouseButtonDown(0)) DrawRectangleRec (botonstart, WHITE);
                }
                if (CheckCollisionPointRec (GetMousePosition(), botonquit))
                {
                    if (IsMouseButtonDown(0)) DrawRectangleRec (botonquit, BLACK);
                }
                DrawRectangleRec (botonoptions, BLUE);
                if (CheckCollisionPointRec (GetMousePosition(), botonoptions))
                {
                    if (IsMouseButtonDown(0)) DrawRectangleRec (botonoptions, PINK);
                }
                DrawText ("Start", botonstart.x, botonstart.y, 70, YELLOW);
                DrawText ("Quit", botonquit.x, botonquit.y, 30, WHITE);
                DrawText ("Options", botonoptions.x, botonoptions.y,28, WHITE);

                break;
               
                case GAMEPLAY:
                DrawTexture (campo, 0,0, WHITE);
                DrawTexture (jugador, player.x, player.y, WHITE);
                DrawTexture (enemigo, versus.x,versus.y, WHITE);
                DrawTexturePro (pelota, (Rectangle){0,0, pelota.width, pelota.height}, (Rectangle){bola.x, bola.y, pelota.width, pelota.height}, (Vector2){pelota.width/2, pelota.height/2}, rotation, WHITE );
                if(pause)
                    {
                        if((framseCounter/30)%2) DrawText("PREASURE SPACE TO PLAY", (screenWidth - MeasureText("PREASURE SPACE TO PLAY", 30))/2, screenHeight/2 - 5, 30, RED);
                        DrawText ("<---- Score or be socored 5 Times to end the game ----->",( screenWidth - MeasureText ("<---- Score or be socored 5 Times to end the game ----->", 25))/2, screenHeight -420, 25, BLACK);
                        DrawText ("P\nR\nE\nS\nS\n U\nP\n P\nR\nE\nS\nS\n D\nO\nW\nN", 100, ( screenHeight - MeasureText ("P\nR\nE\nS\nS\n U\nP\n P\nR\nE\nS\nS\n D\nO\nW\nN", 15))/4 ,15, BLACK);
                        DrawText ("T\nO\nM\nO\nV\nE\nU\nP\n\nT\nO\nM\nO\nV\nE\nD\nO\nW\nN",120,( screenHeight - MeasureText ("T\nO\nM\nO\nV\nE\nU\nP\n\nT\nO\nM\nO\nV\nE\nD\nO\nW\nN", 12))/4 ,12, BLACK);
                    }
                
                
                break;
               
                case ENDING:
                DrawRectangle(0, 0, screenWidth, screenHeight, RED);
                DrawText ("GAME OVER", screenWidth/2, screenHeight/2, 25, WHITE);
                break;
                
                case EASTEREGG:
                DrawRectangle (0, 0, screenWidth, screenHeight, RED);
                DrawRectangleRec (back, BLUE);
                if (CheckCollisionPointRec (GetMousePosition(), back))
                    {
                        if (IsMouseButtonDown(0)) DrawRectangleRec (back, WHITE);
                    }
                DrawText ("Return Title", back.x, back.y, 30, BLACK);
                DrawTextureRec(dance, baile,(Vector2){ screenWidth/2 - baile.width/2, screenHeight/2 - baile.height/2 }, WHITE );
                DrawTexture (lul, 150,150,WHITE);
                DrawRectangleRec (dificl,BLACK);
                DrawText("Do Not Press--->", 300, 100, 20, BLACK); 
                if (CheckCollisionPointRec (GetMousePosition(), dificl))
                {
                    if (IsMouseButtonReleased(0)) DrawRectangleRec (dificl,WHITE), DrawText ("Really???", 300,100,20, BLACK), pesadilla = true;
                    
                }
                if (pesadilla = true)
                {
                    DrawText ("Told ya", 30,30,60,YELLOW);
                }
                
                break;
            }
            
            DrawRectangle (0,0, screenWidth, screenHeight, Fade(BLACK, alpha));
            DrawRectangle (0,0, screenWidth, screenHeight ,Fade(BLACK, beta));
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------  
    UnloadTexture (jugador);
    UnloadTexture (enemigo);
    UnloadTexture (pelota);
    UnloadTexture (campo);
    UnloadTexture (fondo);
    UnloadTexture (menu);
    UnloadTexture (dance);
    UnloadTexture (lul);
    
    UnloadSound (impac);
    UnloadSound (start);
    UnloadSound (egg);
    UnloadMusicStream (music);
    UnloadSound (score);
    UnloadMusicStream (comedi);
    CloseWindow();  
    
    // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    return 0;
}