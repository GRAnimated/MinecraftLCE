#include "Minecraft.World/level/border/WorldBorder.h"
#include "Minecraft.Core/System.h"

WorldBorder::WorldBorder(Level* level) {}

double WorldBorder::getMinX() {
    double max = getCenterX() + getSize() * -0.5;

    if (max < (double)-mWorldSize)
        max = -mWorldSize;
    return max;
}

double WorldBorder::getMaxX() {
    double max = getCenterX() + getSize() * 0.5;

    if (max > (double)mWorldSize)
        max = mWorldSize;
    return max;
}

double WorldBorder::getMinZ() {
    double max = getCenterZ() + getSize() * -0.5;

    if (max < (double)-mWorldSize)
        max = -mWorldSize;
    return max;
}

double WorldBorder::getMaxZ() {
    double max = getCenterZ() + getSize() * 0.5;

    if (max > (double)mWorldSize)
        max = mWorldSize;
    return max;
}

BorderStatus* WorldBorder::getStatus() {
    if (mNextSize < mCurrentSize)
        return gBorderStatusShrinking;

    if (mNextSize > mCurrentSize)
        return gBorderStatusGrowing;

    return gBorderStatusStationary;
}

double WorldBorder::getSize() {
    if (getStatus() != gBorderStatusStationary) {
        double time = (float)(System::processTimeInMilliSecs() - mTime2) / (float)(mTime1 - mTime2);

        if (!(time >= 1.0f))
            return mCurrentSize + (time * (mNextSize - mCurrentSize));

        setSize(mNextSize);
    }
    return mCurrentSize;
}

double WorldBorder::getCenterX() {
    return mCenterX;
}

double WorldBorder::getCenterZ() {
    return mCenterZ;
}

std::vector<BorderChangeListener*>* WorldBorder::getListeners() {
    return &mListeners;
}

double WorldBorder::getDamageSafeZone() {
    return mDamageSafeZone;
}

double WorldBorder::getDamagePerBlock() {
    return mDamageAmount;
}
