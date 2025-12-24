#include "NearbyDownloadPopup.hpp"

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
    return true;
}

void NearbyDownloadPopup::discoveryStarted() {

}

void NearbyDownloadPopup::discoveryFailed(const std::string& error) {

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
