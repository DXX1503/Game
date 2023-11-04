#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include "enemy_base.h"
#include "enemy_normal.h"
#include "enemy_bm.h"
#include "enemy_boss.h"

class EnemyFactory
{
public:
    enum enemy_type{normal,bm,boss};
    EnemyFactory();
    Enemy_base * getEnemy(enemy_type p);

};

#endif // ENEMYFACTORY_H
