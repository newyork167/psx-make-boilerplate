//
// Created by newyork167 on 4/17/2020.
//

#ifndef WITUZ_MAIN_H
#define WITUZ_MAIN_H

#include "constants.h"
#include "sounds/hpup.h"
#include "sounds/crate.h"

#define BOOL int
#define true 1
#define false 0

Image crash;
Image ps1;

int x = 0;
int y = 0;
int speed = 4;

BOOL checkForCollision = false;
BOOL audioInitialized = false;
BOOL inCurrentCollision = false;

GsBOXF damageSplashBox;
int damageColorR = 255;

#endif //WITUZ_MAIN_H
