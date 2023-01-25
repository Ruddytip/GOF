#pragma once
#include <vector>
#include "DynamicObject.h"

class Command{
public:
    virtual ~Command() {}
    virtual void Execute() = 0;
    // virtual void unExecute() = 0;
};
