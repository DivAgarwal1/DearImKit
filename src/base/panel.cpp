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

struct ImageData {
    GLuint tex_id;
    DearImKit::Size size;
};

ImageData LoadTextureFromFile(const char *filename) {
    int width, height, channels;
    unsigned char *data = stbi_load(filename, &width, &height, &channels, 4);
    if (!data)
        return ImageData{0};

    GLuint tex_id;
    glGenTextures(1, &tex_id);
    glBindTexture(GL_TEXTURE_2D, tex_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
    return ImageData{tex_id, DearImKit::Size{width, height}};
}

void DearImKit::Image(std::string filename, DearImKit::Size size) {
    ImageData image_data = LoadTextureFromFile(filename.c_str());

    ImTextureID my_tex_id = (ImTextureID)(intptr_t)image_data.tex_id;

    ImVec2 im_size;
    if (size.width >= 0 && size.height >= 0) {
        im_size = ImVec2{size.width, size.height};
    } else if (size.width > 0) {
        im_size = ImVec2{size.width, (float)image_data.size.height * size.width / image_data.size.width};
    } else if (size.height > 0) {
        im_size = ImVec2{(float)image_data.size.width * size.height / image_data.size.height, size.height};
    } else {
        im_size = ImVec2{image_data.size.width, image_data.size.height};
    }

    ImGui::Image(my_tex_id, im_size);
}

void DearImKit::ImageBackground(std::string filename) {
    ImVec2 win_pos = ImGui::GetWindowPos();
    ImVec2 win_size = ImGui::GetWindowSize();

    ImGui::GetWindowDrawList()->AddImage(
        (ImTextureID)(intptr_t)LoadTextureFromFile(filename.c_str()).tex_id,
        win_pos,
        ImVec2{win_pos.x + win_size.x, win_pos.y + win_size.y}
    );
}