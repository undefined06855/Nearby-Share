#include "NearbyDownloadPopup.hpp"
#include "NearbyShareManager.hpp"

NearbyDownloadPopup* NearbyDownloadPopup::create() {
    auto ret = new NearbyDownloadPopup;
    if (ret->initAnchored(450.f, 225.f)) {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

bool NearbyDownloadPopup::setup() {
    setTitle("Downloading Level");

    NearbyShareManager::get().setDiscoveryName("test downloader");
    NearbyShareManager::get().startDiscovery();

    return true;
}

void NearbyDownloadPopup::discoveryStarted() {
    geode::log::info("discovery started...");
}

void NearbyDownloadPopup::discoveryFailed(const std::string& error) {
    geode::log::info("discovery failed! {}", error);
}

void NearbyDownloadPopup::updateEndpointList() {
    geode::log::debug("endpoint list update:");
    geode::log::pushNest();
    for (auto& endpoint : m_endpoints) geode::log::debug(" - {}", endpoint);
    geode::log::popNest();
}

void NearbyDownloadPopup::requestSuccessful(const std::string& endpoint) {

}

void NearbyDownloadPopup::requestFailed(const std::string& endpoint) {

}


void NearbyDownloadPopup::initiateConnection(const std::string& endpoint, const std::string& digits) {

}

void NearbyDownloadPopup::connectionSuccessful(const std::string& endpoint) {

}

void NearbyDownloadPopup::connectionRejected(const std::string& endpoint) {

}

void NearbyDownloadPopup::connectionBroken(const std::string& endpoint) {

}

void NearbyDownloadPopup::dataReceived(const std::string& endpoint, std::span<const uint8_t> data) {

}

void NearbyDownloadPopup::connectionClosed(const std::string& endpoint) {

}
