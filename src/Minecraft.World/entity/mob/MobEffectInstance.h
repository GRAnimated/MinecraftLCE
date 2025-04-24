#include <cstdint>
class MobEffect;

class MobEffectInstance {
public:
    MobEffectInstance(MobEffect*, int duration, int amplifier);

    MobEffect* mEffect;
    int mDuration;
    int mAmplifier;
    uint16_t word10;
    char byte12;
    bool mParticles;
    int dword14;
};