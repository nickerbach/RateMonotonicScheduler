#include "Signaler.h"

Signaler::Signaler()
{
  threadComplete = true;
  counter = 0;
  overrunCount = 0;
}

Signaler::~Signaler() {}
