class Mob;

class JumpControl {
public:
    JumpControl(Mob*);

    virtual ~JumpControl();
    virtual void tick();

    Mob* mMob;
    bool mJumping = false;
};