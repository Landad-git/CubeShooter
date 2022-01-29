#include <allegro.h> 
#include <math.h>
#include <iostream>
#include <stdio.h>

using namespace std;

void init();
void deinit();
void moveplayer();
void checkinput();
void drawplayer();

void eraseplayer();
void checkplayerbounds();
void shoot();
void updateBullets();
void eraseBullet(int i);

void drawBullet(int i);
void spawnEnemy();
void eraseEnemy(int i);
void drawEnemy(int i);
void updateEnemy();

void killBullet(int i);
void killEnemy(int i);
int checkEnemy(int i);
int findEnemy(int i);
int getDistance(int x1, int y1, int x2, int y2);

void displayScore();
void scoreDigit(int val, int x, int y);
void drawHeart(int x, int y);
void drawScore(int x, int y);
void draw1(int x, int y);

void draw2(int x, int y);
void draw3(int x, int y);
void draw4(int x, int y);
void draw5(int x, int y);
void draw6(int x, int y);

void draw7(int x, int y);
void draw8(int x, int y);
void draw9(int x, int y);
void draw0(int x, int y);
void drawl(int x, int y);

void drawv(int x, int y);
void hurt();
void printLevel(int x, int y);
void drawLevelText(int x, int y);


const int CHARSIZE = 10;
const int CHARBUFFER = 5;

const int POINTS_PER_LEVEL = 100;
const int LEVEL_POSITION = 360;
const int LEVEL_POSITION_TEXT = 315;

//enetity maxes
const int MAXSHOTS = 25;
const int MAX_ENEMIES = 5;
//rates of fire
const int ROF = 500;
const int ROF2 = 20;

//useless
const int REST = 0;

//enemy contol   1/1200
const int ENEMY_HP_PER_LEVEL = 5;
const int ENEMY_SPEED_PER_LEVEL = 1;
int ENEMY_SPAWN_BASE = 8000;
const int ENEMY_SPAWN_RATE = 2;//out of above const ^

//control variables
const int ENEMY_MOVE = 250;
const int UPDATE_BULLET_COUNTER = 1;
const int UPDATE_PLAYER_COUNTER = 25;
const int SUPL = 1;//amount of shots that get updated per loop

int rofc = 30;//rate of fire counter
int emc = 0;//enemy move counter
int ubc = 0;//update bullet counter
int upc = 0;//update player counter


int sc = 0; //shot counter for how many shots per loop
int currentShots = 0; //counter for amount of shots active
int currentEnemies = 0; //counter for amount of enemies active
int currentBulletType = 0; //keeps track of which bullet type is used
int score = 4000;
int level = 0;
int hiddenLevel = 0;
int heartX = 185;
int heartSpacing = 40;
int playerDamage = 10;
int enemyYMove = 0;

bool gameOver = false;

bool levelChanged = false;
bool scoreChanged = false;

struct BOX{
      int x;
      int y;
      int dir;
      int xd;
      int yd;
      bool active;
      int size;
      double health;
      double sHealth;
      int damage;
      int bdamage;
      int buc;
      int bucC;
      };

BOX me;
BOX enemies[MAX_ENEMIES];
BOX shots[MAXSHOTS];

void displayScore(){
     scoreDigit(score%10,150,5);
     scoreDigit(score/10%10,135,5);
     scoreDigit(score/100%10,120,5);
     scoreDigit(score/1000%10,105,5);
     scoreDigit(score/10000%10,90,5);
     
     }
     
void scoreDigit(int val, int x, int y){
     switch(val){
                 case 1: draw1(x,y);
                      break;
                 case 2: draw2(x,y);
                      break;
                 case 3: draw3(x,y);
                      break;
                 case 4: draw4(x,y);
                      break;
                 case 5: draw5(x,y);
                      break;
                 case 6: draw6(x,y);
                      break;
                 case 7: draw7(x,y);
                      break;
                 case 8: draw8(x,y);
                      break;
                 case 9: draw9(x,y);
                      break;
                 case 0: draw0(x,y);
                      break;
                 
                 }
     }

void drawHeart(int x, int y){
     int d = 2;
     //black
     rectfill(screen,x+2*d+1,  y+1,     x+6*d,  y+d,makecol(0,0,0));//top 5 left
     rectfill(screen,x+9*d+1,  y+1,     x+13*d, y+d,makecol(0,0,0));//top 5 right
     rectfill(screen,x+6*d+1,  y+d+1,   x+7*d,  y+2*d,makecol(0,0,0));//top triangle left
     rectfill(screen,x+7*d+1,  y+2*d+1, x+8*d,  y+3*d,makecol(0,0,0));//top triangle middle
     rectfill(screen,x+8*d+1,  y+d+1,   x+9*d,  y+2*d,makecol(0,0,0));//top triangle right
     rectfill(screen,x+d+1,    y+d+1,   x+2*d,  y+2*d,makecol(0,0,0));//left top dot
     rectfill(screen,x+1,      y+2*d+1, x+d,    y+8*d,makecol(0,0,0));//left side
     rectfill(screen,x+14*d+1, y+2*d+1, x+15*d, y+8*d,makecol(0,0,0));//right side
     rectfill(screen,x+13*d+1, y+d+1,   x+14*d ,y+2*d,makecol(0,0,0));//top right dot
    
     rectfill(screen,x+d+1,    y+8*d+1,  x+2*d,  y+9*d,makecol(0,0,0)); //left slope
     rectfill(screen,x+2*d+1,  y+9*d+1,  x+3*d,   y+10*d,makecol(0,0,0));
     rectfill(screen,x+3*d+1,  y+10*d+1, x+4*d,   y+11*d,makecol(0,0,0));
     rectfill(screen,x+4*d+1,  y+11*d+1, x+5*d,   y+12*d,makecol(0,0,0));     
     rectfill(screen,x+5*d+1,  y+12*d+1, x+6*d,   y+13*d,makecol(0,0,0));     
     rectfill(screen,x+6*d+1,  y+13*d+1, x+7*d,   y+14*d,makecol(0,0,0));
     rectfill(screen,x+7*d+1,  y+14*d+1, x+8*d,   y+15*d,makecol(0,0,0));//middle bottom dot
     rectfill(screen,x+8*d+1,  y+13*d+1, x+9*d,   y+14*d,makecol(0,0,0));//right slope
     rectfill(screen,x+9*d+1,  y+12*d+1, x+10*d,  y+13*d,makecol(0,0,0));
     rectfill(screen,x+10*d+1, y+11*d+1, x+11*d,  y+12*d,makecol(0,0,0));
     rectfill(screen,x+11*d+1, y+10*d+1, x+12*d,  y+11*d,makecol(0,0,0));
     rectfill(screen,x+12*d+1, y+9*d+1,  x+13*d,  y+10*d,makecol(0,0,0));
     rectfill(screen,x+13*d+1, y+8*d+1,  x+14*d,  y+9*d,makecol(0,0,0));
         
 //red
     rectfill(screen,x+2*d+1, y+d+1,   x+6*d,    y+2*d,makecol(200,0,0));//upper left tab
     rectfill(screen,x+9*d+1, y+d+1,   x+13*d,   y+2*d,makecol(200,0,0));//upper right tab
     rectfill(screen,x+d+1,   y+2*d+1, x+7*d,    y+3*d,makecol(200,0,0));//upper left tab
     rectfill(screen,x+8*d+1, y+2*d+1, x+14*d,   y+3*d,makecol(200,0,0));//upper right tab
     
     rectfill(screen,x+d+1,   y+3*d+1, x+14*d,   y+8*d,makecol(200,0,0));//mid body
     
     rectfill(screen,x+2*d+1, y+8*d+1,   x+13*d,    y+9*d,makecol(200,0,0));//slope
     rectfill(screen,x+3*d+1, y+9*d+1,   x+12*d,    y+10*d,makecol(200,0,0));
     rectfill(screen,x+4*d+1, y+10*d+1,  x+11*d,    y+11*d,makecol(200,0,0));
     rectfill(screen,x+5*d+1, y+11*d+1,  x+10*d,    y+12*d,makecol(200,0,0));
     rectfill(screen,x+6*d+1, y+12*d+1,  x+9*d,     y+13*d,makecol(200,0,0));
     rectfill(screen,x+7*d+1, y+13*d+1,  x+8*d,     y+14*d,makecol(200,0,0));                    
      
     }

void drawScore(int x, int y){
     //s
     rectfill(screen, x,   y,     x+10, y+30, makecol(0,0,0));
     rectfill(screen, x,   y+17,  x+6,  y+26, makecol(255,255,255));
     rectfill(screen, x+4, y+4,   x+10, y+13, makecol(255,255,255));
     
     x += 15;
     //c
     rectfill(screen, x,   y,     x+10, y+30, makecol(0,0,0));
     rectfill(screen, x+4, y+4, x+10,y+26, makecol(255,255,255));
     
     x+=15;     
     //o
     rectfill(screen, x,   y,     x+10, y+30, makecol(0,0,0));
     rectfill(screen, x+4, y+4,   x+6,  y+26, makecol(255,255,255));
     
     x+=15;
     //r
     rectfill(screen, x,   y,      x+10, y+30, makecol(0,0,0));
     rectfill(screen, x+4, y+4,   x+6,  y+12, makecol(255,255,255));
     rectfill(screen, x+4, y+18,x+6,y+30,makecol(255,255,255));
     rectfill(screen, x+8,y+13,x+10,y+17,makecol(255,255,255));         
     
     
     x+=15;
     //e
     rectfill(screen, x,   y,      x+10, y+30, makecol(0,0,0));
     rectfill(screen, x+4,   y+4,    x+10,  y+13, makecol(255,255,255));
     rectfill(screen, x+4,   y+17,   x+10,  y+26, makecol(255,255,255));
   
     
     
     }

void drawl(int x, int y){
     rectfill(screen,x,y,x+10,y+30,makecol(0,0,0));
     rectfill(screen,x+4,y,x+10,y+24,makecol(255,255,255));
     }
     
void drawv(int x, int y){
     rectfill(screen,x,y,x+10,y+30,makecol(0,0,0));
     rectfill(screen,x+3,y,x+7,y+22,makecol(255,255,255));//mid rec
     rectfill(screen,x+4,y+22,x+6,y+23,makecol(255,255,255));//mid dot
     rectfill(screen,x+5,y+23,x+5,y+24,makecol(255,255,255));
     rectfill(screen,x,y+26,x+1,y+30,makecol(255,255,255));//left l
     rectfill(screen,x+2,y+28,x+3,y+30,makecol(255,255,255));
     rectfill(screen,x+7,y+28,x+9,y+30,makecol(255,255,255));//right l
     rectfill(screen,x+9,y+26,x+10,y+30,makecol(255,255,255));     
     }
     
void draw1(int x, int y){
     rectfill(screen, x,   y,    x+10, y+30, makecol(255,255,255));
     rectfill(screen, x+6, y, x+10, y+30, makecol(0,0,0));
     }
     
void draw2(int x, int y){
     rectfill(screen, x,   y,    x+10, y+30, makecol(0,0,0));
     rectfill(screen, x,   y+4,  x+6,  y+13, makecol(255,255,255));
     rectfill(screen, x+4, y+17, x+10, y+26, makecol(255,255,255));
     }
     
void draw3(int x, int y){
     rectfill(screen, x,   y,      x+10, y+30, makecol(0,0,0));
     rectfill(screen, x,   y+4,    x+6,  y+13, makecol(255,255,255));
     rectfill(screen, x,   y+17,   x+6,  y+26, makecol(255,255,255));     
     }
     
void draw4(int x, int y){
     rectfill(screen, x,   y,    x+10, y+30, makecol(0,0,0));
     rectfill(screen, x+4, y,    x+6,  y+13, makecol(255,255,255));
     rectfill(screen, x,   y+17, x+6,  y+30, makecol(255,255,255));     
     }
     
void draw5(int x, int y){
     rectfill(screen, x,   y,     x+10, y+30, makecol(0,0,0));
     rectfill(screen, x,   y+17,  x+6,  y+26, makecol(255,255,255));
     rectfill(screen, x+4, y+4,   x+10, y+13, makecol(255,255,255));     
     }
     
void draw6(int x, int y){
     rectfill(screen, x,   y,    x+10, y+30, makecol(0,0,0));  
     rectfill(screen, x+4, y+4,  x+10, y+13, makecol(255,255,255));
     rectfill(screen, x+4, y+17, x+6,  y+26, makecol(255,255,255));   
     }
     
void draw7(int x, int y){
     rectfill(screen, x,   y,     x+10, y+30, makecol(0,0,0));
     rectfill(screen, x,   y+4,   x+6,  y+30, makecol(255,255,255));     
     }
     
void draw8(int x, int y){
     rectfill(screen, x,   y,     x+10, y+30, makecol(0,0,0));
     rectfill(screen, x+4, y+4,   x+6,  y+13, makecol(255,255,255));
     rectfill(screen, x+4, y+17,  x+6,  y+26, makecol(255,255,255));     
     }
     
void draw9(int x, int y){
     rectfill(screen, x,   y,     x+10, y+30, makecol(0,0,0));
     rectfill(screen, x+4, y+4,   x+6,  y+13, makecol(255,255,255));
     rectfill(screen, x,   y+17,  x+6,  y+30, makecol(255,255,255));     
     }
     
void draw0(int x, int y){
     rectfill(screen, x,   y,     x+10, y+30, makecol(0,0,0));
     rectfill(screen, x+4, y+4,   x+6,  y+26, makecol(255,255,255));     
     }

void drawLevelText(int x, int y){
     drawl(x,y);
     drawv(x+13,y);
     drawl(x+26,y);
     }     

void spawnEnemy(){
     if(rand()%ENEMY_SPAWN_BASE+1 < ENEMY_SPAWN_RATE && currentEnemies < MAX_ENEMIES){
         for(int i = 0; i < MAX_ENEMIES; i++){
                 if(enemies[i].active == false){
                     enemies[i].active = true;
                     enemies[i].x = rand()%SCREEN_W;
                     enemies[i].y = 85;
                     enemies[i].xd = rand()%11 - 5;
                     enemies[i].yd = 1;//(rand()%3+1)*2 + ((level - 1) * ENEMY_SPEED_PER_LEVEL);
                     enemies[i].size = 50 + (rand()%3 * 10);
                     enemies[i].health = (enemies[i].size/10 * me.damage) + ((level - 1) * ENEMY_HP_PER_LEVEL);
                     enemies[i].sHealth = enemies[i].health;
                     enemies[i].buc = (rand()%4+50)*5;//buc means block update counter, each enemy has a set speed after this
                     enemies[i].bucC = 0;
                     currentEnemies++;
                     drawEnemy(i);
                     break;                 
                 }//if        
         }//for
     }//if
}//funct

void eraseEnemy(int i){
     rectfill(screen, enemies[i].x - enemies[i].size/2, enemies[i].y - enemies[i].size/2, enemies[i].x + enemies[i].size/2, enemies[i].y + enemies[i].size/2, makecol(255,255,255));
}

void drawEnemy(int i){
     int r = static_cast<int>(((enemies[i].sHealth-enemies[i].health)/enemies[i].sHealth)*255);//as health gets lower this number gets higher from 0 to 1
     int g = static_cast<int>((enemies[i].health/enemies[i].sHealth)*255);//as health get lower this number gets lower from 1 to 0
     rectfill(screen, enemies[i].x - enemies[i].size/2, enemies[i].y - enemies[i].size/2, enemies[i].x + enemies[i].size/2, enemies[i].y + enemies[i].size/2, makecol(r,g,0));     
}

void updateEnemy(){//a bunch of messy code, sorry, its self explanatory though :)
 
     
    //if(emc > ENEMY_MOVE){
        for(int i = 0; i < MAX_ENEMIES; i++){ 

            //kill enemy if it's at bottom of screen    
            if(enemies[i].y >= SCREEN_H && enemies[i].active == true){
                killEnemy(i);
                me.health = me.health - 1;
                hurt();
            }//if
            //kill enemy if under or at 0 hp
            if(enemies[i].health <= 0 && enemies[i].active == true){
                score += 10;
                scoreChanged = true;
                killEnemy(i);
            }//if
            
            if(enemies[i].active == true){

                enemies[i].buc = enemies[i].buc - static_cast<int>((enemies[i].sHealth-enemies[i].health)/enemies[i].sHealth);
                //enemies[i].bucC +=  static_cast<int>((enemies[i].sHealth-enemies[i].health)/enemies[i].sHealth) * 999;
                
                if(enemies[i].bucC >= enemies[i].buc){
                    eraseEnemy(i);
                    enemies[i].y += enemies[i].yd;
                    enemies[i].x += enemies[i].xd;
                    enemies[i].bucC = 0;
                
                    if(enemies[i].x < enemies[i].size/2){//wall bounce
                        enemies[i].xd *= -1;
                        enemies[i].x = enemies[i].size/2;
                    }//if
                    
                    if(enemies[i].x > SCREEN_W - enemies[i].size/2){//detect wall bounce
                        enemies[i].xd *= -1;
                        enemies[i].x = SCREEN_W - enemies[i].size/2;
                    }//if
                    drawEnemy(i);
                }//if
                
                 
            }//if
            
            enemies[i].bucC++;           
        }//for

    //}//if
}//funct

void hurt(){
    if(me.health == 2)
        rectfill(screen,heartX, 5, heartX + heartSpacing -1, 39, makecol(255,255,255));
    else if(me.health == 1)
        rectfill(screen,heartX, 5, heartX + 2 * heartSpacing - 1, 39, makecol(255,255,255));       
    else if (me.health == 0){
        rectfill(screen,heartX, 5, heartX + 3 * heartSpacing -1, 39, makecol(255,255,255)); 
        gameOver = true;
         } 
     }

void moveplayer(){
     if(me.dir != -1){
        eraseplayer();
             switch(me.dir){
             case 1: 
                  if(me.x < CHARSIZE)
                          me.x = SCREEN_W + me.xd;//edge check
                  me.x -= me.xd;
                  break;
             case 2:
                  if(me.x > SCREEN_W - CHARSIZE)//edge check
                          me.x =  me.xd;                  
                  me.x += me.xd;
                  break;  
                            }//switch
        
        //checkplayerbounds();
                            
        me.dir = -1;
     }//if              
     
}//moveplayer

int getDistance(int x1, int y1, int x2, int y2){
    int distance = static_cast<int>(sqrt(  pow((x2-x1),2) + pow((y2-y1),2))/*sqrt*/)/*cast*/;
    return distance;
    
}

int checkEnemy(int i){

    for(int j = 0; j < MAX_ENEMIES; j++)
        if(enemies[j].active == true)
            if(getDistance(shots[i].x, shots[i].y, enemies[j].x, enemies[j].y) <= enemies[j].size/2+10)   
                    return j;
                               
    return -1;     
}

void updateBullets(){

    for(int i = 0; i < SUPL; i++){
 
        if(shots[sc].active == true){

            int enemyCheck = checkEnemy(sc);
            
            if(enemyCheck > -1){
              killBullet(sc);
              enemies[enemyCheck].health -= me.damage;
              score += 1;
              scoreChanged = true;
              break;                 
            } 
           
            if(shots[sc].y < 50 && shots[sc].active == true){
                killBullet(sc);
            }//if
            
            if(shots[sc].active == true){
                eraseBullet(sc);
                shots[sc].y -= shots[sc].yd;
                drawBullet(sc);
                }
        }///if
        sc++;
        sc = sc%MAXSHOTS;
    }//for  
}

void killBullet(int i){
   shots[i].active = false;
   eraseBullet(i);
   currentShots--;  
}

void killBullet2(int i){
   shots[i].active = false;
   currentShots--;     
     }
void killEnemy(int i){
   enemies[i].active = false;
   eraseEnemy(i);
   currentEnemies--;
}

int findEnemy(int i){
    for(int j = 0; j < MAX_ENEMIES; j++){
            
    }
}

void eraseBullet(int i){
    rectfill(screen, shots[i].x - 5, shots[i].y - 5, shots[i].x + 5, shots[i].y + 5, makecol(255,255,255));
}


void drawBullet(int i){
    rectfill(screen, shots[i].x - 5, shots[i].y - 5, shots[i].x + 5, shots[i].y + 5, makecol(0,0,0)); 
}
void shoot(){//triggers when space is pressed
    if(currentShots < MAXSHOTS){//if there are still shots avail
        for(int i = 0; i < MAXSHOTS; i++){//for every bullet possible
            if(shots[i].active == false){//finds first avail slot
                shots[i].x = me.x + CHARSIZE;//puts the bullet at the character
                shots[i].y = me.y - (2 * CHARSIZE + 6);//still puts it at the character
                shots[i].yd = 5;//sets speed
                shots[i].xd = 0;
                shots[i].active = true;//flags it as not avail
                drawBullet(i);//draws it
                currentShots++;//totals how many shots
                break; //breaks out of the entire if loop
            }//if
        }//for          
    }//if    
}//funct

void checkplayerbounds(){//a function used to limit the player from going off the edges, isn't used
     if(me.x < 0 + CHARSIZE)
        me.x = 0 + CHARSIZE;
     if(me.x > SCREEN_W - CHARSIZE)
        me.x = SCREEN_W - CHARSIZE;
     }//funct

void drawplayer(){
     triangle(screen, me.x, me.y, me.x + CHARSIZE, me.y - 2 * CHARSIZE, me.x + 2 * CHARSIZE, me.y, makecol(0,0,0));
     //rectfill(screen, me.x-CHARSIZE, me.y-CHARSIZE-CHARBUFFER, me.x+CHARSIZE, me.y+CHARSIZE-CHARBUFFER, makecol(255,255,255));
     }//funct

void eraseplayer(){
     triangle(screen, me.x, me.y, me.x + CHARSIZE, me.y - 2 * CHARSIZE, me.x + 2 * CHARSIZE, me.y, makecol(255,255,255));
     //rectfill(screen, me.x-CHARSIZE, me.y-CHARSIZE-CHARBUFFER, me.x+CHARSIZE, me.y+CHARSIZE-CHARBUFFER, makecol(255,255,255));
     }//funct

void printLevel(int x, int y){//parameters are the location it will print and it switches the current level and draws numbers based on the level
     switch(level){
         case 1: draw0(x,y); draw1(x+15,y);
              break;
         case 2: draw0(x,y); draw2(x+15,y);
              break;
         case 3: draw0(x,y); draw3(x+15,y);
              break;
         case 4: draw0(x,y); draw4(x+15,y);
              break;
         case 5: draw0(x,y); draw5(x+15,y);
              break;
         case 6: draw0(x,y); draw6(x+15,y);
              break;
         case 7: draw0(x,y); draw7(x+15,y);
              break;
         case 8: draw0(x,y); draw8(x+15,y);    
              break;
         case 9: draw0(x,y); draw9(x+15,y);    
              break;
         case 10: draw1(x,y); draw0(x+15,y);    
              break;
         case 11: draw1(x,y); draw1(x+15,y);    
              break;
         case 12: draw1(x,y); draw2(x+15,y);    
              break;
         case 13: draw1(x,y); draw3(x+15,y);    
              break;
         case 14: draw1(x,y); draw4(x+15,y);    
              break;
         case 15: draw1(x,y); draw5(x+15,y);    
              break;
         case 16: draw1(x,y); draw6(x+15,y);    
              break;
         case 17: draw1(x,y); draw7(x+15,y);    
              break;
         case 18: draw1(x,y); draw8(x+15,y);    
              break;
         case 19: draw1(x,y); draw2(x+15,y);    
              break;
         case 20: draw2(x,y); draw0(x+15,y);    
              break;                            
                                                                                                                                                                                                                            
 
                   }
     }

void checkLevel(){//sets the level to the digit rounded down of the score/500 which is 0 at first so I add 1
     level = static_cast<int>(score / POINTS_PER_LEVEL) + 1;
     if(level > hiddenLevel){//if the current level is higher than a hidden variable I use to detect when the level changes it sets the hidden level to the current level and updates the display
     hiddenLevel = level;
     printLevel(LEVEL_POSITION,5);
     }
     return;
     }

void checkinput(){
     if(key[KEY_A] || key[KEY_LEFT]){
           me.dir = 1;           
     }
     if(key[KEY_D] || key[KEY_RIGHT]){           
           me.dir = 2;           
     }
     if(key[KEY_UP]){
           //me.dir = 0;          
     }
     if(key[KEY_DOWN]){
           //me.dir = 0;           
     }

     if(key[KEY_SPACE]){                  
          if(rofc > ROF ){
          rofc = 0;                  
          shoot();
          }   
     }
  
         
     
}//funct
     
int main() {
	init();
	
	
	rectfill(screen, 0,0,SCREEN_W, SCREEN_H, makecol(255,255,255));
	
	srand (time(NULL));

	me.x = SCREEN_W / 2;
	me.y = SCREEN_H - 10;
	me.yd = 1;
	me.xd = 2;
	me.dir = -1;
	me.health = 3;
	me.damage = playerDamage;
	me.bdamage = me.damage;
	
	drawplayer();
	displayScore();
	drawScore(5,5);
	drawLevelText(LEVEL_POSITION_TEXT,5);
	drawHeart(heartX,5);
	drawHeart(heartX + heartSpacing,5);
	drawHeart(heartX + 2 * heartSpacing,5);
	
	rectfill(screen, 0, 40, SCREEN_W, 42, makecol(0,0,0));


	while (!key[KEY_ESC] && gameOver == false) {

        checkinput();
        checkLevel();
        if(upc > UPDATE_PLAYER_COUNTER){
		moveplayer();
		upc = 0;
        }
        
        drawplayer();
        
		spawnEnemy();
		updateEnemy();
        
		if(ubc > UPDATE_BULLET_COUNTER){
    		updateBullets();
    		ubc = 0;
        }
        
        if(scoreChanged == true){
        displayScore();
        scoreChanged = false;
        }

		rofc++;
		emc++;
        ubc++;
        upc++;
        enemyYMove++;
        enemyYMove %= 9999;
        rest(REST);
	}

	deinit();
	return 0;
}
END_OF_MAIN()

void init() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 400, 800, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}

// set_window_title(NULL, "Cube Shooter");
	install_timer();
	install_keyboard();
	install_mouse();
	/* add other initializations here */
	
set_window_title("Cube Shooter");
}

void deinit() {
	clear_keybuf();
	/* add other deinitializations here */
}
