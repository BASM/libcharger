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

#include <charger.h>

typedef struct {
  int cap;
  int volt;
  int extvolt;
  int resitor;
  int temp;

} battary;

int batt_tick(battary* b, int seconds)
{

  return 0;
}

int batt_printinfo(battary* b)
{
  printf("v1: %i, v2: %i, cur: %i, vint: %i cap: %i\n", b->extvolt, b->extvolt, 0, b->volt, b->cap);

  return 0;
}

int batt_setvolt(battary* bat, int volt, int res)
{
  printf("New voltage: %i, resitor: %i\n", volt, res);

  return 0;
}

int main(void)
{
  printf("Init charger...\n");

  battary cbat={0};
  battary* bat=&cbat;

  int second;

  while(1)
  {
    batt_tick(bat, 10);
    batt_printinfo(bat);

    sleep(1);
  }

  return 0;
}
