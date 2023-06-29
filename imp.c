#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

//
// imp.c by jon
//
// this program will fight one imp

int randomNumber(){
  //  srand(time(NULL));
  return rand() % 20;
}


struct stats {
  int hp;
  int mana;
  int atk;
};

struct imp {
  struct stats impStat;
};

struct boss {
  struct stats bossStats;
};

struct player {
  char *name;
  struct stats playerStats;
};

void intro(struct player *p){
  char name[200];
  printf("welcome to imp.c\n");
  printf("this program will fight 1 imp without interaction\n");
  printf("please enter players name: ");
  scanf("%s", name);
  p->name = name;
}

void setStats(struct player *p, struct imp *i, struct boss *b){
  p->playerStats.hp = 700;
  p->playerStats.atk = 5;

  i->impStat.hp = 700;
  i->impStat.atk = 3;
  b->bossStats.hp = 2000;
}

void randomizeAttack(struct player *p, struct imp *i, struct boss *b){
  p->playerStats.atk = randomNumber();
  i->impStat.atk = randomNumber();
}
void enterDungeon(){
  printf("entering dungeon to fight imp\n");
}

void playerSwing(struct player *p, struct imp *i, struct boss *b){
  i->impStat.hp = i->impStat.hp - p->playerStats.atk;
  printf("%s swung their sword and did %d damage. imp has %d health left\n", p->name, p->playerStats.atk, i->impStat.hp);
}

void impFireball(struct player *p, struct imp *i, struct boss *b){
  p->playerStats.hp = p->playerStats.hp - i->impStat.atk;
  printf("imps fireball reduced your health by %d, you have %d health left\n", i->impStat.atk, p->playerStats.hp);
}

void fight(struct player *p, struct imp *i, struct boss *b){
  while (p->playerStats.hp && i->impStat.hp > 10){
    playerSwing(p, i, b);
    if (randomNumber() == 5) { playerSwing(p, i, b); printf("extra swing!\n");}
    if (randomNumber() == 7) { playerSwing(p, i, b); printf("extra swing!\n");}
    if (randomNumber() == 6) { impFireball(p, i, b); printf("imp attacks again!\n"); }
    sleep(2);
    randomizeAttack(p, i, b);
    impFireball(p, i, b);
    sleep(1);
    randomizeAttack(p, i, b);
  }

  if (p->playerStats.hp > i->impStat.hp) {
    printf("youve killed the imp! great job!");
}else{
  printf("the imp killed you, sorry warrior");
 }
}

int main(){
  struct player Player;
  struct imp Imp;
  struct boss Boss;
  setStats(&Player, &Imp, &Boss);
  intro(&Player);
  fight (&Player, &Imp, &Boss);
  return 0;
}
