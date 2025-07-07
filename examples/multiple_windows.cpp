// See hello_world.cpp first

#include <functional>

#include "DearImKit/dearimkit.h"

class HelloWorldAgain : public DearImKit::Panel {
public:
    HelloWorldAgain(int index, int num_times = 1) : DearImKit::Panel("Hello World Again"), m_index(index), m_num_times(num_times) {};

    bool draw() override {
        bool stay_open = true;

        // Check out https://github.com/ocornut/imgui for guide to ImGui logic
        if (!ImGui::Begin((DearImKit::Panel::getName() + "##" + std::to_string(m_index)).c_str(), &stay_open)) {
            ImGui::End();
            return stay_open;
        }

        for (int i = 0; i < m_num_times; i++) {
            ImGui::Text("Hello World again from DearImKit");
        }

        ImGui::End();
        return stay_open;
    }

private:
    int m_num_times;
    int m_index;
};

class HelloWorld : public DearImKit::Panel {
public:
    HelloWorld(int num_times = 1) : DearImKit::Panel("Hello World"), m_num_times(num_times) {};

    bool draw() override {
        bool stay_open = true;

        // Check out https://github.com/ocornut/imgui for guide to ImGui logic
        if (!DearImKit::Begin(*this, &stay_open)) {
            ImGui::End();
            return stay_open;
        }

        for (int i = 0; i < m_num_times; i++) {
            ImGui::Text("Hello World from DearImKit");
        }

        if (ImGui::Button("Say Hello World again")) {
            // HelloWorld2 will now be rendered
            DearImKit::AddPanel<HelloWorldAgain>(m_num_windows_opened, 3);
            m_num_windows_opened++;
        }

        ImGui::End();
        return stay_open;
    }

private:
    int m_num_times;

    int m_num_windows_opened = 0;
};

int main() {
    std::function<void(void)> at_start = []() {
        DearImKit::AddPanel<HelloWorld>(2);
    };

    DearImKit::SetupApp(at_start);
}