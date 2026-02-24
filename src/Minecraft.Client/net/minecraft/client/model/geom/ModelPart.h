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

    float m_xTexSize;
    float m_yTexSize;
    float m_xPos;
    float m_yPos;
    float m_zPos;
    int m_dword1C;
    int m_dword20;
    int m_dword24;
    float m_xRot;
    float m_yRot;
    float m_zRot;
    bool m_mirror;
    bool m_visible;
    bool m_neverRender;
    std::vector<Cube*> m_cubes;
    std::vector<ModelPart*> m_childrens;
    float m_translateX;
    float m_translateY;
    float m_translateZ;
    int m_dword74;
    int m_dword78;
    int m_dword7C;
    int m_dword80;
    int m_dword84;
    int m_dword88;
    int m_dword8C;
    std::wstring m_id;
    int m_xTexOffs;
    int m_yTexOffs;
    char m_compiled;
    int m_list;
    ModelPart* m_parent;
    float m_yOffset;
    char m_byteC4;
};
