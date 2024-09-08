#pragma once
#include "Item.h"

class Item;
class RangedWeapon :
    public Item
{
private:


public:
    RangedWeapon(unsigned value);
    virtual ~RangedWeapon();

    virtual RangedWeapon* clone() = 0;
};

