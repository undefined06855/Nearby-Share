#include "TaskPopup.hpp"

TaskPopup::TaskPopup(const char* title, const std::string& content, const char* btn1, const char* btn2) {
    auto [task, post, prog, cancelled] = BoolTask::spawn("TaskPopup");

    m_task = std::move(task);
    m_postResult = std::move(post);

    m_popup = geode::createQuickPopup(
        title, content, btn1, btn2,
        [this](auto pop, bool result) {
            m_postResult(result);
        },
        false
    );
}

BoolTask TaskPopup::showAndWait() {
    m_popup->show();
    return m_task;
}
