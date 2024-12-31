#pragma once

class Level;

class MinecraftServer {
public:
    static MinecraftServer* sInstance;
    static MinecraftServer* getInstance();

    Level* getLevel(int);
};
