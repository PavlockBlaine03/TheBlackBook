#pragma once
#include "RangedWeapon.h"

class Item;
class RangedWeapon;
class Bow :
    public RangedWeapon
{
private:


public:
    Bow(unsigned value);
    virtual ~Bow();

    virtual Bow* clone();
};

