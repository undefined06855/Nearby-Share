#pragma once
#include <Geode/ui/Popup.hpp>
#include "SharedPopupData.hpp"

class NearbyUploadPopup : public SharedPopupData, geode::Popup<GJGameLevel*> {
public:
    static NearbyUploadPopup* create(GJGameLevel* level);
    bool setup(GJGameLevel* level);

    void advertisementStarted();
    void advertisementFailed(const std::string& error);

    void initiateConnection(const std::string& endpoint, const std::string& digits);

    void connectionSuccessful(const std::string& endpoint);
    void connectionRejected(const std::string& endpoint);
    void connectionBroken(const std::string& endpoint);

    void dataSent(const std::string& endpoint, long long transferred, long long total, int status);

    void connectionClosed(const std::string& endpoint);
};
