#include "matches.h"

Matches::Matches(int m) : m(m) {}

bool Matches::aquireM()
{
    return smphM.try_acquire();
}

void Matches::relaseM()
{
    smphM.release();
}

