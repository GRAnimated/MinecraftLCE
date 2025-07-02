#pragma once

class DataOutputStream;

class GameRuleManager {
public:
    // param names guessed
    void saveGameRules(unsigned char** dst, unsigned int* dstSize);

    void writeRuleFile(DataOutputStream* stream);
};