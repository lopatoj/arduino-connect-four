//project.cpp - Put your project code here!

#include "lights.h"
#include "project.h"
#define POTENTIOMETER_PIN A0

int board[5][5] = {0};
int highest[5] = {0, 0, 0, 0, 0};
int winningPosition[4][2];
int winner;
int pos;
//which light
int coordinate(int x, int y) {
  if (y == 0) {
    return 20 + x;
  } else if (y == 1) {
    return 19 - x;
  } else if (y == 2) {
    return 10 + x;
  } else if (y == 3) {
    return 9 - x;
  } else if (y == 4) {
    return 0 + x;
  }
  return 25;
}

void disp() {
  for (int x = 0; x < 5; x++) {
    for (int y = 0; y < 5; y++) {
      if (board[x][y] == 0) {
        leds[coordinate(x, y)] = CRGB::Black;
      } else if (board[x][y] == 1) {
        leds[coordinate(x, y)] = CRGB::Red;
      } else if (board[x][y] == 2) {
        leds[coordinate(x, y)] = CRGB::Yellow;
      }
    }
  }
  FastLED.delay(1000);
}

void selectColor(int p, int t) {
  CRGB color = (p == 1 ? CRGB::Red : CRGB::Yellow);
  color = ((t / 500) % 2 == 0 ? color : CRGB::Blue);
  for (int x = 0; x < 5; x++) {
    if (x == pos) {
      leds[coordinate(x, highest[x])] = color;
    } else {
      if(board[x][highest[x]] == 0) {
        leds[coordinate(x, highest[x])] = CRGB::Black;
      } else if(board[x][highest[x]] == 1) {
        leds[coordinate(x, highest[x])] = CRGB::Red;
      } else if(board[x][highest[x]] == 2) {
        leds[coordinate(x, highest[x])] = CRGB::Yellow;
      }
    }
  }

  FastLED.show();
}
//choose the pos based on twisting  of the knob
void selectLogic() {
  int value = analogRead(POTENTIOMETER_PIN);
  if (value >= 0 && value < 205) {
    pos = 0;
  }
  else if (value >= 205 && value < 410) {
    pos = 1;
  }
  else if (value >= 410 && value < 615) {
    pos = 2;
  }
  else if (value >= 615 && value < 820) {
    pos = 3;
  }
  else if (value >= 820) {
    pos = 4;
  }
  
}

void select(int player) {
  bool selected = false;
  int timer = 0;
  int previousValue = pos;
  int delayTime = 10;

  while (!selected) {
    if (previousValue != pos) {
      previousValue = pos;
      timer = 0;
    }

    if(highest[pos] >= 5) {
      timer = 0;
    }

    selectLogic();
    selectColor(player, timer);

    delay(delayTime);
    timer += delayTime;
    if (timer >= 3000 && highest[pos] < 5) {
      selected = true;
    }
  }
}

void logic(int player) {
  board[pos][highest[pos]] = player;  
  highest[pos]++;
}

boolean hori(int player){
  for(int x=0; x<2;x++){
    for(int y=0;y<4;y++){
     if(board[x][y]==player&&board[x+1][y]==player&&board[x+2][y]==player&&board[x+3][y]==player){
      winningPosition[0][0] = x;
      winningPosition[0][1] = y;
      winningPosition[1][0] = x+1;
      winningPosition[1][1] = y;
      winningPosition[2][0] = x+2;
      winningPosition[2][1] = y;
      winningPosition[3][0] = x+3;
      winningPosition[3][1] = y;
      return true;
     }
  }
 }
  return false;
}
  
boolean vert(int player){
  for(int x=0; x<4;x++){
    for(int y=0;y<2;y++){
      if(board[x][y]==player&&board[x][y+1]==player&&board[x][y+2]==player&&board[x][y+3]==player){
        winningPosition[0][0] = x;
        winningPosition[0][1] = y;
        winningPosition[1][0] = x;
        winningPosition[1][1] = y+1;
        winningPosition[2][0] = x;
        winningPosition[2][1] = y+2;
        winningPosition[3][0] = x;
        winningPosition[3][1] = y+3;
        return true;
      }
    }
  }
  return false;
}

boolean diag(int player){
  for(int x = 0; x < 2; x++) {
    for(int y = 0; y < 2; y++) {
      if(board[x][y]==player&&board[x+1][y+1]==player&&board[x+2][y+2]==player&&board[x+3][y+3]==player){
        winningPosition[0][0] = x;
        winningPosition[0][1] = y;
        winningPosition[1][0] = x+1;
        winningPosition[1][1] = y+1;
        winningPosition[2][0] = x+2;
        winningPosition[2][1] = y+2;
        winningPosition[3][0] = x+3;
        winningPosition[3][1] = y+3;
        return true;
      }
      if(board[x][y+3]==player&&board[x+1][y+2]==player&&board[x+2][y+1]==player&&board[x+3][y]==player){
        winningPosition[0][0] = x;
        winningPosition[0][1] = y+3;
        winningPosition[1][0] = x+1;
        winningPosition[1][1] = y+2;
        winningPosition[2][0] = x+2;
        winningPosition[2][1] = y+1;
        winningPosition[3][0] = x+3;
        winningPosition[3][1] = y;
        return true;
      }
    }
  }
  return false;
}

bool ifWinner(int p){
  if(hori(p)) {
    winner = p;
    return true;
  }
  if(vert(p)) {
    winner = p;
    return true;
  }
  if(diag(p)) {
    winner = p;
    return true;
  }
  return false;
}

boolean checkWinningCell(int x, int y) {
  for(int i = 0; i < 4; i++) {
    if(winningPosition[i][0] == x && winningPosition[i][1] == y) {
      return true;
    }
  }

  return false;
}

boolean tied() {
  for(int x = 0; x < 5; x++) {
    for(int y = 0; y < 5; y++) {
      if(board[x][y] == 0) {
        return false;
      }
    }
  }

  winningPosition[0][0] = 100;
  winningPosition[0][1] = 100;
  winningPosition[1][0] = 100;
  winningPosition[1][1] = 100;
  winningPosition[2][0] = 100;
  winningPosition[2][1] = 100;
  winningPosition[3][0] = 100;
  winningPosition[3][1] = 100;
  return true;
}

void winningAnimation() {
  for(int x=0; x< 5;x++){
    for(int y=0; y<5 ; y++){
      board[x][y]=0;
    }
  }
  for(int i = 0; i < 5; i++) {
    highest[i] = 0;
  }
  Serial.println("Animation");
  for(int i = 0; i < 20; i++) {
    for(int x = 0; x < 5; x++) {
      for(int y = 0; y < 5; y++) {
        if(!checkWinningCell(x, y)) {
          leds[coordinate(x,y)].red = (int)leds[coordinate(x,y)].red * .7;
          leds[coordinate(x,y)].green = (int)leds[coordinate(x,y)].green * .6;
          leds[coordinate(x,y)].blue = (int)leds[coordinate(x,y)].blue * .5;
        }
        FastLED.show();
      }
    }
  }
  FastLED.delay(4000);
  disp();
}
