#pragma once

class SharedPopupData {
public:
    std::vector<std::string> m_endpoints;

    void endpointFound(const std::string& endpoint);
    void endpointLost(const std::string& endpoint);
};
