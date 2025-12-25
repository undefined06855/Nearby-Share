#pragma once
#include <Geode/utils/coro.hpp>
#include <Geode/ui/Popup.hpp>

using BoolTask = geode::Task<bool, std::monostate>;

class TaskPopup {
    BoolTask m_task;
    BoolTask::PostResult m_postResult;

    FLAlertLayer* m_popup;
public:
    TaskPopup(const char* title, const std::string& content, const char* btn1, const char* btn2);
    BoolTask showAndWait();
};
