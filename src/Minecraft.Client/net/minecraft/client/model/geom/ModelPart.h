#pragma once

#include <string>
#include <vector>

class Model;
class Cube;

class ModelPart {
public:
    void construct(Model*, const std::wstring&);
    void texOffs(int xTexOffs, int yTexOffs);
    void addBox(float, float, float, int, int, int, float);
    void addBox(float, float, float, int, int, int);
    void addBoxMapTex(float, float, float, int, int, int, int, int, float);
    void addChild(ModelPart*);

    virtual ~ModelPart();
    virtual void render(float, bool shouldCallList, bool);
    virtual void renderRollable(float, bool);
    virtual void compile(float);

    float mXTexSize;
    float mYTexSize;
    float mXPos;
    float mYPos;
    float mZPos;
    int dword1C;
    int dword20;
    int dword24;
    float mXRot;
    float mYRot;
    float mZRot;
    bool mMirror;
    bool mVisible;
    bool mNeverRender;
    std::vector<Cube*> mCubes;
    std::vector<ModelPart*> mChildrens;
    float mTranslateX;
    float mTranslateY;
    float mTranslateZ;
    int dword74;
    int dword78;
    int dword7C;
    int dword80;
    int dword84;
    int dword88;
    int dword8C;
    std::wstring mId;
    int mXTexOffs;
    int mYTexOffs;
    char mCompiled;
    int mList;
    ModelPart* mParent;
    float mYOffset;
    char byteC4;
};
