#pragma once

class Voteable;

class Voteables {
public:
    // types,
    // 0 - Map Voting
    // 3 - Build Off build Voting
    Voteable* getVoteable(unsigned int type);
};
