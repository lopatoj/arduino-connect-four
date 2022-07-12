//project.h

#ifndef INCLUDED_PROJECT
#define INCLUDED_PROJECT
#define POTENTIOMETER_PIN A0

void select(int player);
void logic(int p);
void disp();
void selectLogic();
void selectColor();
bool ifWinner(int p);
void winningAnimation();
boolean tied();

#endif // INCLUDED_PROJECT
