#include "tamper.h"

Tamper::Tamper(int l) : l(l) {}

bool Tamper::aquireT()
{
    return smphT.try_acquire();
}

void Tamper::relaseT()
{
    smphT.release();
}

