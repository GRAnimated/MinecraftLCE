#include "net/minecraft/world/level/newbiome/layer/Layer.h"

#include "net/minecraft/world/level/biome/Biome.h"

Layer::Layer(long long seed) {
    this->mChildLayer = nullptr;

    long long n = seed;
    for (int i = 0; i < 3; i++) {
        n *= n * 6364136223846793005LL + 1442695040888963407LL;
        n += seed;
    }

    this->mMixedSeed = 0;
    this->mSeed = n;
}

void Layer::init(long long l) {
    mMixedSeed = l;
    if (mChildLayer != nullptr) {
        mChildLayer->init(l);
    }

    mMixedSeed *= mMixedSeed * 6364136223846793005L + 1442695040888963407L;
    mMixedSeed += mSeed;
    mMixedSeed *= mMixedSeed * 6364136223846793005L + 1442695040888963407L;
    mMixedSeed += mSeed;
    mMixedSeed *= mMixedSeed * 6364136223846793005L + 1442695040888963407L;
    mMixedSeed += mSeed;
}

void Layer::initRandom(long long l, long long m) {
    mRandom = mMixedSeed;
    mRandom *= mRandom * 6364136223846793005L + 1442695040888963407L;
    mRandom += l;
    mRandom *= mRandom * 6364136223846793005L + 1442695040888963407L;
    mRandom += m;
    mRandom *= mRandom * 6364136223846793005L + 1442695040888963407L;
    mRandom += l;
    mRandom *= mRandom * 6364136223846793005L + 1442695040888963407L;
    mRandom += m;
}

int Layer::nextRandom(int i) {
    int j = (int)((mRandom >> 24) % i);
    if (j < 0) {
        j += i;
    }

    mRandom *= mRandom * 6364136223846793005L + 1442695040888963407L;
    mRandom += mMixedSeed;
    return j;
}

bool Layer::isSame(int biomeIdA, int biomeIdB) {
    if (biomeIdA == biomeIdB) {
        return true;
    } else {
        Biome* biome = Biome::getBiome(biomeIdA);
        Biome* biome2 = Biome::getBiome(biomeIdB);
        if (biome != nullptr && biome2 != nullptr) {
            if (biome != Biome::MESA_PLATEAU_F && biome != Biome::MESA_PLATEAU) {
                return biome == biome2 || biome->getBaseClass() == biome2->getBaseClass();
            } else {
                return biome2 == Biome::MESA_PLATEAU_F || biome2 == Biome::MESA_PLATEAU;
            }
        } else {
            return false;
        }
    }
}

bool Layer::isOcean(int biomeId) {
    if (Biome::OCEAN->mBiomeID == biomeId) {
        return true;
    } else if (Biome::DEEP_OCEAN->mBiomeID == biomeId) {
        return true;
    }

    return Biome::FROZEN_OCEAN->mBiomeID == biomeId;
}

int Layer::random(int i, int j, int k, int l) {
    int random = nextRandom(4);

    int ret = (random != 2 ? i : k);
    if (random == 3)
        ret = l;
    if (random == 1)
        ret = j;
    return ret;
}

int Layer::random(int i, int j) {
    if (nextRandom(2)) {
        return j;
    }

    return i;
}

int Layer::modeOrRandom(int i, int j, int k, int l) {
    if (j == k && k == l) {
        return j;
    } else if (i == j && i == k) {
        return i;
    } else if (i == j && i == l) {
        return i;
    } else if (i == k && i == l) {
        return i;
    } else if (i == j && k != l) {
        return i;
    } else if (i == k && j != l) {
        return i;
    } else if (i == l && j != k) {
        return i;
    } else if (j == k && i != l) {
        return j;
    } else if (j == l && i != k) {
        return j;
    } else {
        return k == l && i != j ? k : random(i, j, k, l);
    }
}
