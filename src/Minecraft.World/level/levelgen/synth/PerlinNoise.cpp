#include "PerlinNoise.h"
#include "Minecraft.Util/Mth.h"

/*
arrayWithLength<double> PerlinNoise::getRegion(arrayWithLength<double> array, int a3, int octaveMultiplier, int a5, int frequency, int amplitude, int a8, double persistence, double frequencyFactor,
                                               double amplitudeFactor) {
    {
        int a12 = 1;

        if (array) {
            if (a3) {
                for (int i = 0; i < a3; ++i) {
                    array.get(i) = 0;
                }
            }
        } else {
            arrayWithLength<double> tempArray(a8 * frequency * a12, true);
            array = tempArray;
        }

        if (mMaxOctaves < 1)
            return array;

        double scale = 1.0;

        for (int i = 0; i < mMaxOctaves; ++i) {
            double octaveFrequency = Mth::lfloor(octaveMultiplier * scale * frequencyFactor);
            double octaveAmplitude = Mth::lfloor(frequency * scale * amplitudeFactor);
            long long octaveFreqMask = octaveFrequency + 16777215;
            if (octaveFrequency >= 0)
                octaveFreqMask = octaveFrequency;
            long long octaveAmplMask = octaveAmplitude + 16777215;
            if (octaveAmplitude >= 0)
                octaveAmplMask = octaveAmplitude;
            double octaveSize = scale * frequencyFactor;
            mNoiseLevels[i]->add(array, a3, a5, a8, octaveMultiplier * scale * frequencyFactor - octaveFrequency + (octaveFrequency - (octaveFreqMask & 0xFFFFFFFFFF000000LL)),
                                 amplitude * scale * amplitudeFactor, octaveFrequency - octaveAmplMask + (octaveAmplMask - (octaveAmplMask & 0xFFFFFFFFFF000000LL)), scale * frequencyFactor,
                                 scale * amplitudeFactor, octaveSize, scale);
            scale *= 0.5;
        }

        return array;
    }
}
*/