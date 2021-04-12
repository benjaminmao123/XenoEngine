#include "pch.h"
#include "Sprite.h"

Xeno::Sprite::Sprite(Entity* owner) :
    Component(owner)
{ }

const Xeno::Quad& Xeno::Sprite::GetQuad() const
{
    return mQuad;
}
