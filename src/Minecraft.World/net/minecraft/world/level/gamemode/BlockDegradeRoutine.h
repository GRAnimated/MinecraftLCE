#pragma once

class ServerLevel;
class DegradationSequenceRuleDefinition;

class BlockDegradeRoutine {
public:
    BlockDegradeRoutine(ServerLevel*, DegradationSequenceRuleDefinition*);

    char eloo[0x70];
};
