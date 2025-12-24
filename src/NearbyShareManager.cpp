#include "NearbyShareManager.hpp"
#include "jni.hpp"

NearbyShareManager::NearbyShareManager()
    : m_launcherOutdated(false)
    , m_uploadPopup(nullptr)
    , m_downloadPopup(nullptr) {}

NearbyShareManager& NearbyShareManager::get() {
    static NearbyShareManager instance;
    return instance;
}

void NearbyShareManager::registerJNINatives() {
    jni::registerJNINatives();
}

void NearbyShareManager::requestPermissionsIfNeeded() {
    if (!jni::hasPermissions()) {
        geode::log::debug("jarvis, request permissions");
        jni::requestPermissions();
    }
}

void NearbyShareManager::startDiscovery() {
    jni::beginDiscovery(jni::Strategy::P2P_POINT_TO_POINT);
}

void NearbyShareManager::discoveryStarted() {
    if (m_downloadPopup) m_downloadPopup->discoveryStarted();
}

void NearbyShareManager::discoveryFailed(const std::string& error) {
    if (m_downloadPopup) m_downloadPopup->discoveryFailed(error);
}

void NearbyShareManager::startAdvertising() {
    jni::beginAdvertising(jni::Strategy::P2P_POINT_TO_POINT);
}

void NearbyShareManager::advertisingStarted() {
    if (m_uploadPopup) m_uploadPopup->advertisementStarted();
}

void NearbyShareManager::advertisingFailed(const std::string& error) {
    if (m_uploadPopup) m_uploadPopup->advertisementFailed(error);
}

void NearbyShareManager::endpointFound(const std::string& endpoint) {
    if (m_uploadPopup) m_uploadPopup->endpointFound(endpoint);
    if (m_downloadPopup) m_downloadPopup->endpointFound(endpoint);
}

void NearbyShareManager::endpointLost(const std::string& endpoint) {
    if (m_uploadPopup) m_uploadPopup->endpointLost(endpoint);
    if (m_downloadPopup) m_downloadPopup->endpointLost(endpoint);
}

void NearbyShareManager::requestConnection(const std::string& endpoint) {
    jni::requestConnection(endpoint);
}

void NearbyShareManager::requestSuccessful(const std::string& endpoint) {
    if (m_downloadPopup) m_downloadPopup->requestSuccessful(endpoint);
}

void NearbyShareManager::requestFailed(const std::string& endpoint) {
    if (m_downloadPopup) m_downloadPopup->requestFailed(endpoint);
}

void NearbyShareManager::connectionInitiated(const std::string& endpoint, const std::string& digits) {
    if (m_uploadPopup) m_uploadPopup->initiateConnection(endpoint, digits);
    if (m_downloadPopup) m_downloadPopup->initiateConnection(endpoint, digits);
}

void NearbyShareManager::acceptConnection(const std::string& endpoint) {
    jni::acceptConnection(endpoint);
}

void NearbyShareManager::rejectConnection(const std::string& endpoint) {
    jni::rejectConnection(endpoint);
}

void NearbyShareManager::connectionSuccessful(const std::string& endpoint) {
    if (m_uploadPopup) m_uploadPopup->connectionSuccessful(endpoint);
    if (m_downloadPopup) m_downloadPopup->connectionSuccessful(endpoint);
}

void NearbyShareManager::connectionRejected(const std::string& endpoint) {
    if (m_uploadPopup) m_uploadPopup->connectionRejected(endpoint);
    if (m_downloadPopup) m_downloadPopup->connectionRejected(endpoint);
}

void NearbyShareManager::connectionBroken(const std::string& endpoint) {
    if (m_uploadPopup) m_uploadPopup->connectionBroken(endpoint);
    if (m_downloadPopup) m_downloadPopup->connectionBroken(endpoint);
}

void NearbyShareManager::sendData(const std::string& endpoint, std::span<const uint8_t> data) {
    jni::sendData(endpoint, data);
}

void NearbyShareManager::dataSent(const std::string& endpoint, long long transferred, long long total, int status) {
    if (m_uploadPopup) m_uploadPopup->dataSent(endpoint, transferred, total, status);
}

void NearbyShareManager::dataReceived(const std::string& endpoint, std::span<const uint8_t> data) {
    if (m_downloadPopup) m_downloadPopup->dataReceived(endpoint, data);
}

void NearbyShareManager::closeConnection(const std::string& endpoint) {
    jni::disconnect(endpoint);
}

void NearbyShareManager::connectionClosed(const std::string& endpoint) {
    if (m_uploadPopup) m_uploadPopup->connectionClosed(endpoint);
    if (m_downloadPopup) m_downloadPopup->connectionClosed(endpoint);
}
