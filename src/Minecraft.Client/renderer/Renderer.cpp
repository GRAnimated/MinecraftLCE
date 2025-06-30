#include "Minecraft.Client/renderer/Renderer.h"
#include "png.h"
void Renderer::vtbl_7101130608_func_19() {}
void Renderer::CaptureScreen(ImageFileBuffer* image_file_buffer, _XSOCIAL_PREVIEWIMAGE* xsocial_previewimage) {}
void Renderer::BeginConditionalSurvey(int i) {}
void Renderer::EndConditionalSurvey() {}
void Renderer::BeginConditionalRendering(int i) {}
void Renderer::EndConditionalRendering() {}
void Renderer::TextureDynamicUpdateStart() {}
void Renderer::TextureDynamicUpdateEnd() {}
void Renderer::vtbl_7101130608_func_67() {}
void Renderer::StateSetLineWidth(float x) {}
void Renderer::StateSetEnableViewportClipPlanes(bool cond) {}
void Renderer::BeginEvent(const wchar_t* string) {}
void Renderer::EndEvent() {}

bool Renderer::IsWidescreen() {
    return true;
}

bool Renderer::IsHiDef() {
    return true;
}

int Renderer::GetMaxTextures() {
    return 1024;
}

void Renderer::Tick() {
    this->CBuffTick();
}

// NON_MATCHING | Score: 205 (lower is better)
// Not sure how to make it compile the 2 other instructions
// also unsure what the return value is.
float32x4_t Renderer::MatrixMult(float* matrix) {
    return this->MultWithStack((float (*)[4])matrix);
}

void Renderer::UpdateGamma(unsigned short gamma) {
    this->mGamma = gamma;
}