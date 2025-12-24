#pragma once
#include "NearbyDownloadPopup.hpp"
#include "NearbyUploadPopup.hpp"

class NearbyShareManager {
    NearbyShareManager();
public:
    static NearbyShareManager& get();

    bool m_launcherOutdated;
    NearbyDownloadPopup* m_downloadPopup;
    NearbyUploadPopup* m_uploadPopup;

    void registerJNINatives();

    void requestPermissionsIfNeeded();

    void startDiscovery();
    void discoveryStarted();
    void discoveryFailed(const std::string& error);

    void startAdvertising();
    void advertisingStarted();
    void advertisingFailed(const std::string& error);

    void endpointFound(const std::string& endpoint);
    void endpointLost(const std::string& endpoint);

    void requestConnection(const std::string& endpoint);
    void requestSuccessful(const std::string& endpoint);
    void requestFailed(const std::string& endpoint);

    void connectionInitiated(const std::string& endpoint, const std::string& digits);

    void acceptConnection(const std::string& endpoint);
    void rejectConnection(const std::string& endpoint);

    void connectionSuccessful(const std::string& endpoint);
    void connectionRejected(const std::string& endpoint);
    void connectionBroken(const std::string& endpoint);

    void sendData(const std::string& endpoint, std::span<const uint8_t> data);
    void dataSent(const std::string& endpoint, long long transferred, long long total, int status);
    void dataReceived(const std::string& endpoint, std::span<const uint8_t> data);

    void closeConnection(const std::string& endpoint);
    void connectionClosed(const std::string& endpoint);
};
