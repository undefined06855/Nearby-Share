#include "NearbyUploadPopup.hpp"
#include "NearbyShareManager.hpp"

NearbyUploadPopup* NearbyUploadPopup::create(GJGameLevel* level) {
    auto ret = new NearbyUploadPopup;
    if (ret->initAnchored(450.f, 225.f, level)) {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

bool NearbyUploadPopup::setup(GJGameLevel* level) {
    setTitle(fmt::format("Uploading {}", level->m_levelName).c_str());

    NearbyShareManager::get().setDiscoveryName("test uploader");
    NearbyShareManager::get().startAdvertising();

    return true;
}

void NearbyUploadPopup::advertisementStarted() {
    geode::log::debug("advertisement started...");
}

void NearbyUploadPopup::advertisementFailed(const std::string& error) {
    geode::log::debug("advertisement failed! {}", error);
}

void NearbyUploadPopup::updateEndpointList() {
    geode::log::debug("endpoint list update:");
    geode::log::pushNest();
    for (auto& endpoint : m_endpoints) geode::log::debug(" - {}", endpoint);
    geode::log::popNest();
}

void NearbyUploadPopup::initiateConnection(const std::string& endpoint, const std::string& digits) {

}

void NearbyUploadPopup::connectionSuccessful(const std::string& endpoint) {

}

void NearbyUploadPopup::connectionRejected(const std::string& endpoint) {

}

void NearbyUploadPopup::connectionBroken(const std::string& endpoint) {

}

void NearbyUploadPopup::dataSent(const std::string& endpoint, long long transferred, long long total, int status) {

}

void NearbyUploadPopup::connectionClosed(const std::string& endpoint) {

}
