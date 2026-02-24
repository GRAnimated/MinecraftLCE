#pragma once

class Mob;

class JumpControl {
public:
    JumpControl(Mob*);

    virtual ~JumpControl();
    virtual void tick();

    Mob* m_mob;
    bool m_jumping = false;
};
