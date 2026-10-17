#include "NX/Render/RendererCore.h"
#include "fui/fui.h"
#include "fui/fuiFile.h"
#include "fui/fuiRenderNodeStage.h"

// Reconstructed from 0x7100489f18. Render nodes own their children; managed
// texture removal follows renderer release, then the serialized tables die.
fuiFile::~fuiFile() {
    delete m_renderNodeStage;
    for (int i = 0; i < m_header.m_bitmapCount; ++i) {
        fuiBitmap* bitmap = m_data.m_fuiBitmap + i;
        if (bitmap->m_texture) {
            if (bitmap->m_texture > 0)
                Renderer::sInstance->TextureFree(bitmap->m_texture);
            fui::sInstance->removeManagedTexture(this, bitmap);
        }
    }
    delete[] static_cast<unsigned char*>(m_field138);
}
