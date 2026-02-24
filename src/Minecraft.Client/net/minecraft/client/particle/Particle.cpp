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
    : m_field0x8(0), m_field0x10(0), m_random(), m_uvSet() {
    _init(level, posX, posY, posZ);

    m_velX = speedX + ((Random::random() * 2.0) - 1.0) * 0.4;
    m_velY = speedY + ((Random::random() * 2.0) - 1.0) * 0.4;
    m_velZ = speedZ + ((Random::random() * 2.0) - 1.0) * 0.4;

    float norm = (float)(Random::random() + Random::random() + 1.0f) * 0.15f;
    float len = Mth::sqrt(m_velX * m_velX + m_velY * m_velY + m_velZ * m_velZ);

    m_velX = m_velX / len * norm * 0.4;
    m_velY = m_velY / len * norm * 0.4 + 0.1;
    m_velZ = m_velZ / len * norm * 0.4;
}

Particle::Particle(Level* level, double posX, double posY, double posZ) : m_field0x8(0), m_field0x10(0) {
    _init(level, posX, posY, posZ);
}

// NON_MATCHING Score: 520
void Particle::_init(Level* level, double posX, double posY, double posZ) {
    m_level = level;
    m_boundingBox = AABB::newPermanent(gParticleDefaultAABB);
    m_canCollide = true;
    m_field0x90 = 0;
    m_width = 0.6f;
    m_height = 1.8f;
    m_field0x130 = 0;
    m_alpha = 1.0f;
    m_field0x110 = 1.0f;
    m_isOnGround = false;
    m_isRemoved = false;
    m_spriteAtlas = nullptr;
    m_gravityScale = 0.0f;
    m_field0x108 = 1.0f;
    m_field0x10c = 1.0f;
    m_texJitterX = m_random.nextFloat() * 3.0f;
    m_texJitterY = m_random.nextFloat() * 3.0f;
    m_scale = (m_random.nextFloat() * 0.5f + 0.5f) * 2.0f;
    m_maxAge = (int)(4.0F / (m_random.nextFloat() * 0.9F + 0.1F));
    m_age = 0;

    m_uvSet = TextureUVCoordinateSet(0.0, 0.0, 1.0, 1.0, 16, 16, ResourceLocation(), 1.0);
    setSize(0.2, 0.2);
    setPos(posX, posY, posZ);

    m_prevPosX = posX;
    m_prevPosY = posY;
    m_prevPosZ = posZ;
    m_velX = 0;
    m_velY = 0;
    m_velZ = 0;
}

void Particle::setBoundingBox(const AABB* newAABB) {
    m_boundingBox->set(newAABB);
}

AABB* Particle::getBoundingBox() {
    return m_boundingBox;
}

bool Particle::isAlive() {
    return !m_isRemoved;
}

void Particle::remove() {
    m_isRemoved = true;
}

float Particle::getAlpha() {
    return m_alpha;
}

Level* Particle::getLevel() {
    return m_level;
}

Particle* Particle::setPower(float powerScale) {
    m_velX *= (double)powerScale;
    m_velY = (m_velY - 0.1) * (double)powerScale + 0.1;
    m_velZ *= (double)powerScale;
    return this;
}

Particle* Particle::scale(float scale) {
    setSize(0.2f * scale, 0.2f * scale);
    m_scale *= scale;
    return this;
}

void Particle::tick() {
    m_prevPosX = m_posX;
    m_prevPosY = m_posY;
    m_prevPosZ = m_posZ;

    if (m_age++ >= m_maxAge) {
        remove();
    }

    m_velY -= 0.04 * m_gravityScale;
    move(m_velX, m_velY, m_velZ);
    m_velX *= 0.98;
    m_velY *= 0.98;
    m_velZ *= 0.98;

    if (m_isOnGround) {
        m_velX *= 0.7;
        m_velZ *= 0.7;
    }
}

// NON_MATCHING TODO: implement it :}
void Particle::render(BufferBuilder*, std::shared_ptr<Entity>&, float param4, float param5, float param6,
                      float param7, float param8, float param9) {
    float scaleScaled = m_scale / 10;
    if (m_spriteAtlas) {
        m_uvSet.m_u0 = m_spriteAtlas->getU0(false);
        m_uvSet.m_v0 = m_spriteAtlas->getV0(false);
        m_uvSet.m_u1 = m_spriteAtlas->getU1(false);
        m_uvSet.m_v1 = m_spriteAtlas->getV1(false);
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
        m_spriteAtlas = newSprite;
}

// NON_MATCHING | score 415, idk.
void Particle::setMiscTex(int miscTex) {
    if (getParticleTexture() == 0 || getParticleTexture() == 4) {
        TextureUVCoordinateSet tex = TextureUVCoordinateSet(TextureUVCoordinateSet::fromOldSystem(miscTex));
        m_uvSet = tex;
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
    m_posX = newX;
    m_posY = newY;
    m_posZ = newZ;
    double halfWidth = m_width / 2.0f;
    AABB* newAABB = AABB::newTemp(newX - halfWidth, newY, newZ - halfWidth, halfWidth + newX, m_height + newY,
                                  halfWidth + newZ);
    setBoundingBox(newAABB);
}

void Particle::move(double dx, double dy, double dz) {
    double newDx = dx;
    double newDz = dz;
    double newDy = dy;

    if (m_canCollide) {
        std::vector<AABB*>* BBsList
            = m_level->getCollisionAABBs(0L, getBoundingBox()->expand(dx, dy, dz), false, false, true);

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
    m_isOnGround = newDy != dy && dy < 0.0;
    if (newDx != dx)
        m_velX = 0.0;
    if (newDz != dz)
        m_velZ = 0.0;
}

int Particle::getLightColor() {
    BlockPos partPos = BlockPos(m_posX, m_posY, m_posZ);
    if (m_level->hasChunkAt(partPos))
        return m_level->getLightColor(partPos, 0, -1);
    return 0;
}

float Particle::getBrightness() {
    BlockPos partPos = BlockPos(m_posX, m_posY, m_posZ);
    if (m_level->hasChunkAt(partPos))
        return m_level->getBrightness(partPos);
    return 0;
}

void Particle::setSize(float newWidth, float newHeight) {
    if (m_width != newWidth || m_height != newHeight) {
        m_width = newWidth;
        m_height = newHeight;

        AABB* currentAABB = getBoundingBox();
        AABB* newBox = AABB::newTemp(
            currentAABB->m_inX, currentAABB->m_inY, currentAABB->m_inZ, currentAABB->m_inX + (double)m_width,
            currentAABB->m_inY + (double)m_height, currentAABB->m_inZ + (double)m_width);
        setBoundingBox(newBox);
    }
}

void Particle::setLocationFromBoundingbox() {
    AABB* thisBB = getBoundingBox();
    m_posX = (thisBB->m_inX + thisBB->m_axX) / 2;
    m_posY = thisBB->m_inY;
    m_posZ = (thisBB->m_inZ + thisBB->m_axZ) / 2;
}

void Particle::setCamerViewDirection(Vec3* direction) {
    Vec3* view = Particle::VIEW_DIRECTION;
    view->m_z = direction->m_z;
    view->m_y = direction->m_y;
    view->m_x = direction->m_x;
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
