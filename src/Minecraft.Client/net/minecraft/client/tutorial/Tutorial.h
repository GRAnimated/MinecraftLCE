#pragma once

enum eTutorial_GameMode {};
enum eTutorial_State {};

class UIScene;

class Tutorial {
public:
    static void staticCtor();

    void showTutorialPopup(bool);

    virtual ~Tutorial();
    virtual void tick();
    virtual bool isStateCompleted(eTutorial_State);
    virtual void setStateCompleted(eTutorial_State);
    virtual void changeTutorialState(eTutorial_State, UIScene*);
};
