#include "NearbyUploadPopup.hpp"

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

    return true;
}

void NearbyUploadPopup::advertisementStarted() {

}

void NearbyUploadPopup::advertisementFailed(const std::string& error) {

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
