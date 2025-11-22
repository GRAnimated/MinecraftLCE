#include "net/minecraft/client/particle/Particle.h"
#include "net/minecraft/client/particle/TextureUVCoordinateSet.h"
#include "net/minecraft/client/renderer/texture/TextureAtlasSprite.h"
#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/resources/ResourceLocation.h"
#include "net/minecraft/util/Mth.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/phys/AABB.h"
#include <cstdio>
#include <vector>

AABB* gParticleDefaultAABB = AABB::newPermanent(0, 0, 0, 0, 0, 0);

// NON_MATCHING
Particle::Particle(Level* level, double posX, double posY, double posZ, double speedX, double speedY,
                   double speedZ)
    : field_0x8(0), field_0x10(0), mRandom(), mUVSet() {
    _init(level, posX, posY, posZ);

    mVelX = speedX + ((Random::random() * 2.0) - 1.0) * 0.4;
    mVelY = speedY + ((Random::random() * 2.0) - 1.0) * 0.4;
    mVelZ = speedZ + ((Random::random() * 2.0) - 1.0) * 0.4;

    float norm = (float)(Random::random() + Random::random() + 1.0f) * 0.15f;
    float len = Mth::sqrt(mVelX * mVelX + mVelY * mVelY + mVelZ * mVelZ);

    mVelX = mVelX / len * norm * 0.4;
    mVelY = mVelY / len * norm * 0.4 + 0.1;
    mVelZ = mVelZ / len * norm * 0.4;
}

Particle::Particle(Level* level, double posX, double posY, double posZ) : field_0x8(0), field_0x10(0) {
    _init(level, posX, posY, posZ);
}

// NON_MATCHING Score: 520
void Particle::_init(Level* level, double posX, double posY, double posZ) {
    mLevel = level;
    mBoundingBox = AABB::newPermanent(gParticleDefaultAABB);
    mCanCollide = true;
    field_0x90 = 0;
    mWidth = 0.6f;
    mHeight = 1.8f;
    field_0x130 = 0;
    mAlpha = 1.0f;
    field_0x110 = 1.0f;
    mIsOnGround = false;
    mIsRemoved = false;
    mSpriteAtlas = nullptr;
    mGravityScale = 0.0f;
    field_0x108 = 1.0f;
    field_0x10c = 1.0f;
    mTexJitterX = mRandom.nextFloat() * 3.0f;
    mTexJitterY = mRandom.nextFloat() * 3.0f;
    mScale = (mRandom.nextFloat() * 0.5f + 0.5f) * 2.0f;
    mMaxAge = (int)(4.0F / (mRandom.nextFloat() * 0.9F + 0.1F));
    mAge = 0;

    mUVSet = TextureUVCoordinateSet(0.0, 0.0, 1.0, 1.0, 16, 16, ResourceLocation(), 1.0);
    setSize(0.2, 0.2);
    setPos(posX, posY, posZ);

    mPrevPosX = posX;
    mPrevPosY = posY;
    mPrevPosZ = posZ;
    mVelX = 0;
    mVelY = 0;
    mVelZ = 0;
}

void Particle::setBoundingBox(const AABB* newAABB) {
    mBoundingBox->set(newAABB);
}

AABB* Particle::getBoundingBox() {
    return mBoundingBox;
}

bool Particle::isAlive() {
    return !mIsRemoved;
}

void Particle::remove() {
    mIsRemoved = true;
}

float Particle::getAlpha() {
    return mAlpha;
}

Level* Particle::getLevel() {
    return mLevel;
}

Particle* Particle::setPower(float powerScale) {
    mVelX *= (double)powerScale;
    mVelY = (mVelY - 0.1) * (double)powerScale + 0.1;
    mVelZ *= (double)powerScale;
    return this;
}

Particle* Particle::scale(float scale) {
    setSize(0.2f * scale, 0.2f * scale);
    mScale *= scale;
    return this;
}

void Particle::tick() {
    mPrevPosX = mPosX;
    mPrevPosY = mPosY;
    mPrevPosZ = mPosZ;

    if (mAge++ >= mMaxAge) {
        remove();
    }

    mVelY -= 0.04 * mGravityScale;
    move(mVelX, mVelY, mVelZ);
    mVelX *= 0.98;
    mVelY *= 0.98;
    mVelZ *= 0.98;

    if (mIsOnGround) {
        mVelX *= 0.7;
        mVelZ *= 0.7;
    }
}

// NON_MATCHING TODO: implement it :}
void Particle::render(BufferBuilder*, std::shared_ptr<Entity>&, float param4, float param5, float param6,
                      float param7, float param8, float param9) {
    float scaleScaled = mScale / 10;
    if (mSpriteAtlas) {
        mUVSet.mU0 = mSpriteAtlas->getU0(false);
        mUVSet.mV0 = mSpriteAtlas->getV0(false);
        mUVSet.mU1 = mSpriteAtlas->getU1(false);
        mUVSet.mV1 = mSpriteAtlas->getV1(false);
    }

    double dVar14 = (double)param4;

    int uVar9 = getLightColor();
    float fVar19 = scaleScaled * param5;
    float fVar18 = scaleScaled * param8;
    float fVar15 = scaleScaled * param7;
    float fVar16 = scaleScaled * param9;
}

int Particle::getParticleTexture() {
    return 0;
}

void Particle::setSprite(TextureAtlasSprite* newSprite) {
    int partTex = getParticleTexture();
    if (partTex == 1 || partTex == 2)
        mSpriteAtlas = newSprite;
}

// NON_MATCHING | score 415, idk.
void Particle::setMiscTex(int miscTex) {
    if (getParticleTexture() == 0 || getParticleTexture() == 4) {
        TextureUVCoordinateSet tex = TextureUVCoordinateSet(TextureUVCoordinateSet::fromOldSystem(miscTex));
        mUVSet = tex;
    }
}

std::wstring Particle::toString() const {
    return L"A particle";
}

bool Particle::isSemiTransparent() {
    return false;
}

bool Particle::isTransparent() {
    return false;
}

void Particle::setPos(double newX, double newY, double newZ) {
    mPosX = newX;
    mPosY = newY;
    mPosZ = newZ;
    double halfWidth = mWidth / 2.0f;
    AABB* newAABB = AABB::newTemp(newX - halfWidth, newY, newZ - halfWidth, halfWidth + newX, mHeight + newY,
                                  halfWidth + newZ);
    setBoundingBox(newAABB);
}

void Particle::move(double dx, double dy, double dz) {
    double newDx = dx;
    double newDz = dz;
    double newDy = dy;

    if (mCanCollide) {
        std::vector<AABB*>* BBsList
            = mLevel->getCollisionAABBs(0L, getBoundingBox()->expand(dx, dy, dz), false, false, true);

        for (auto it = BBsList->begin(); it != BBsList->end(); ++it) {
            newDy = (*it)->clipYCollide(getBoundingBox(), newDy);
        }
        setBoundingBox(getBoundingBox()->move(0.0, newDy, 0.0));

        for (auto it = BBsList->begin(); it != BBsList->end(); ++it) {
            newDx = (*it)->clipXCollide(getBoundingBox(), newDx);
        }
        setBoundingBox(getBoundingBox()->move(newDx, 0.0, 0.0));

        for (auto it = BBsList->begin(); it != BBsList->end(); ++it) {
            newDz = (*it)->clipZCollide(getBoundingBox(), newDz);
        }
        setBoundingBox(getBoundingBox()->move(0.0, 0.0, newDz));

    } else {
        setBoundingBox(getBoundingBox()->move(dx, dy, dz));
    }

    setLocationFromBoundingbox();
    mIsOnGround = newDy != dy && dy < 0.0;
    if (newDx != dx)
        mVelX = 0.0;
    if (newDz != dz)
        mVelZ = 0.0;
}

int Particle::getLightColor() {
    BlockPos partPos = BlockPos(mPosX, mPosY, mPosZ);
    if (mLevel->hasChunkAt(partPos))
        return mLevel->getLightColor(partPos, 0, -1);
    return 0;
}

float Particle::getBrightness() {
    BlockPos partPos = BlockPos(mPosX, mPosY, mPosZ);
    if (mLevel->hasChunkAt(partPos))
        return mLevel->getBrightness(partPos);
    return 0;
}

void Particle::setSize(float newWidth, float newHeight) {
    if (mWidth != newWidth || mHeight != newHeight) {
        mWidth = newWidth;
        mHeight = newHeight;

        AABB* currentAABB = getBoundingBox();
        AABB* newBox = AABB::newTemp(currentAABB->minX, currentAABB->minY, currentAABB->minZ,
                                     currentAABB->minX + (double)mWidth, currentAABB->minY + (double)mHeight,
                                     currentAABB->minZ + (double)mWidth);
        setBoundingBox(newBox);
    }
}

void Particle::setLocationFromBoundingbox() {
    AABB* thisBB = getBoundingBox();
    mPosX = (thisBB->minX + thisBB->maxX) / 2;
    mPosY = thisBB->minY;
    mPosZ = (thisBB->minZ + thisBB->maxZ) / 2;
}

void Particle::setCamerViewDirection(Vec3* direction) {
    Vec3* view = Particle::VIEW_DIRECTION;
    view->z = direction->z;
    view->y = direction->y;
    view->x = direction->x;
}

void Particle::setXOffset(double value) {
    Particle::X_OFFSET = value;
}

void Particle::setYOffset(double value) {
    Particle::Y_OFFSET = value;
}

void Particle::setZOffset(double value) {
    Particle::Z_OFFSET = value;
}
