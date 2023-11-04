#include "enemyfactory.h"

EnemyFactory::EnemyFactory()
{
}

Enemy_base *EnemyFactory::getEnemy(enemy_type p)
{
    Enemy_base * pfac=nullptr;
    switch (p) {
    case normal:
        pfac=new Enemy_normal();
        break;
    case bm:
        pfac=new enemy_Bm();
        break;
    case boss:
        pfac=new enemy_Boss();
        break;
    default:
        break;
    }
    return pfac;
}
