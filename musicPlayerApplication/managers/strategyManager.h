#ifndef STRATEGY_MANAGER_H
#define STRATEGY_MANAGER_H

#include "../strategies/customPlayStrategy.h"
#include "../strategies/randomPlayStrategy.h"
#include "../strategies/sequentialPlayStrategy.h"

class StrategyManager {
private:
    SequentialPlayStrategy sequentialStrategy;
    RandomPlayStrategy randomStrategy;
    CustomPlayStrategy customStrategy;
public:
    PlayStrategy* getStrategy(StrategyType type) {
        switch (type) {
            case StrategyType::SEQUENTIAL:
                return &sequentialStrategy;
            case StrategyType::RANDOM:  
                return &randomStrategy;
            case StrategyType::CUSTOM:
                return &customStrategy;
            default:
                return nullptr;
        }
    }
};

#endif // STRATEGY_MANAGER_H