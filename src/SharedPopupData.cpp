#include "SharedPopupData.hpp"

void SharedPopupData::endpointFound(const std::string& endpoint) {
    m_endpoints.push_back(endpoint);
    updateEndpointList();
}

void SharedPopupData::endpointLost(const std::string& endpoint) {
    m_endpoints.erase(std::remove(m_endpoints.begin(), m_endpoints.end(), endpoint), m_endpoints.end());
    updateEndpointList();
}
