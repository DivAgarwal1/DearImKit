#include "../../include/DearImKit/panel_manager/panel_manager.h"

#include <functional>
#include <string>

#include "DearImKit/base/base.h"
#include "DearImKit/panel_manager/panel_manager.h"

class ExternPanel : public DearImKit::Panel {
public:
    ExternPanel(std::string name, std::function<bool(void*)> draw, void* state) : DearImKit::Panel(name), m_draw(draw), mp_state(state) {};

    bool draw() override {
        return m_draw(mp_state);
    }

private:
    std::function<bool(void*)> m_draw;
    void* mp_state;
};

void DearImKit_AddPanel(const char* name, bool (*draw)(void*), void* state) {
    DearImKit::AddPanel<ExternPanel>(name, draw, state);
}
