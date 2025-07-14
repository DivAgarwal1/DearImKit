#include "DearImKit/base/panel.h"

#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "GLFW/glfw3.h"

DearImKit::Panel::Panel(const std::string &name) : m_name(name) {};

std::string DearImKit::Panel::getName() const {
    return m_name;
}

bool DearImKit::Begin(const DearImKit::Panel &panel, bool *p_open, ImGuiWindowFlags flags) {
    return ImGui::Begin(panel.getName().c_str(), p_open, flags);
}

GLuint LoadTextureFromFile(const char *filename) {
    int width, height, channels;
    unsigned char *data = stbi_load(filename, &width, &height, &channels, 4);
    if (!data)
        return 0;

    GLuint tex_id;
    glGenTextures(1, &tex_id);
    glBindTexture(GL_TEXTURE_2D, tex_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
    return tex_id;
}

void DearImKit::Image(std::string filename, int width, int height) {
    ImTextureID my_tex_id = (ImTextureID)(intptr_t)LoadTextureFromFile(filename.c_str());
    ImVec2 size(width, height);

    ImGui::Image(my_tex_id, size);
}

void DearImKit::ImageBackground(std::string filename) {
    ImVec2 win_pos = ImGui::GetWindowPos();
    ImVec2 win_size = ImGui::GetWindowSize();

    ImGui::GetWindowDrawList()->AddImage(
        (ImTextureID)(intptr_t)LoadTextureFromFile(filename.c_str()),
        win_pos,
        ImVec2(win_pos.x + win_size.x, win_pos.y + win_size.y)
    );
}