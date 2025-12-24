#pragma once
#include <Geode/ui/Popup.hpp>
#include "SharedPopupData.hpp"

class NearbyDownloadPopup : public SharedPopupData, geode::Popup<> {
public:
    static NearbyDownloadPopup* create();
    bool setup();

    void discoveryStarted();
    void discoveryFailed(const std::string& error);

    void requestSuccessful(const std::string& endpoint);
    void requestFailed(const std::string& endpoint);

    void initiateConnection(const std::string& endpoint, const std::string& digits);

    void connectionSuccessful(const std::string& endpoint);
    void connectionRejected(const std::string& endpoint);
    void connectionBroken(const std::string& endpoint);

    void dataReceived(const std::string& endpoint, std::span<const uint8_t> data);

    void connectionClosed(const std::string& endpoint);
};
