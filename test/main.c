/*
 * Copyright (C) 2013 Leonid Myravjev (asm@asm.pp.ru)
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#include <stdio.h>
#include <unistd.h>

#include <math.h>

#include <charger.h>
#include "getch.h"

typedef struct {
  int cap;
  int volt;
  int res;
  int temp;
  
  int capmax;
  int extvolt;
  int extres;

} battary;

static void batt_cap2volt(battary* b);


int batt_tick(battary* b, int seconds)
{
  batt_cap2volt(b);
  return 0;
}

int batt_printinfo(battary* b)
{
  printf("v1: %i, v2: %i, extres: %i, cur: %i, vint: %i cap: %i, capfull: %i\n", b->extvolt, b->extvolt, b->extres, 0, b->volt, b->cap, b->capmax);

  return 0;
}

int batt_setvolt(battary* bat, int volt, int res)
{
  printf("New voltage: %i, resitor: %i\n", volt, res);

  return 0;
}

static void batt_cap2volt(battary* b)
{
  float cap=b->cap*15/2700.0;
  double res = (1.0/400.0)*pow((cap-7.8),3)+1.25;

  b->volt=res*100;
}

int batt_init(battary* b)
{
  b->extres=0xffff;
  b->capmax=2700;
  b->cap=1000;
  batt_cap2volt(b);
  return 0;
}


static int usage() 
{
  printf("Usage:\n");
  printf(" ? -- this help message\n");
  return 0;
}

int main(void)
{
  printf("Init charger...\n");

  battary cbat={0};
  battary* bat=&cbat;

  //int second;

  batt_init(bat);

  int iter=0;
  while(1)
  {
    int key = trych();

    if(key!=0){
      switch(key) {
        case '?': usage(); break;
        case 'c': bat->cap+=100; break;
        case 'C': bat->cap-=100; break;
      }
    }
    if ((iter++%100)==0) {
      printf("Time: %i second: ", iter/100);
      batt_printinfo(bat);

      batt_tick(bat, 10);
    }
    usleep(10000);
  }

  return 0;
}
