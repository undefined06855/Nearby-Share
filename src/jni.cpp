#include "jni.hpp"
#include "NearbyShareManager.hpp"
#include <Geode/cocos/platform/android/jni/JniHelper.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wwritable-strings"
#pragma clang diagnostic ignored "-Wunknown-pragmas" // clangd bug?

void jni::registerJNINatives() {
    static const JNINativeMethod methods[] = {
        {
            "discoveryStartCallback",
            "()V",
            reinterpret_cast<void*>(&jni::discoveryStartCallback)
        },
        {
            "discoveryFailureCallback",
            "(Ljava/lang/String;)V",
            reinterpret_cast<void*>(&jni::discoveryFailureCallback)
        },
        {
            "advertisingStartCallback",
            "()V",
            reinterpret_cast<void*>(&jni::advertisingStartCallback)
        },
        {
            "advertisingFailureCallback",
            "(Ljava/lang/String;)V",
            reinterpret_cast<void*>(&jni::advertisingFailureCallback)
        },
        {
            "endpointFoundCallback",
            "(Ljava/lang/String;)V",
            reinterpret_cast<void*>(&jni::endpointFoundCallback)
        },
        {
            "endpointLostCallback",
            "(Ljava/lang/String;)V",
            reinterpret_cast<void*>(&jni::endpointLostCallback)
        },
        {
            "connectionRequestSuccessCallback",
            "(Ljava/lang/String;)V",
            reinterpret_cast<void*>(&jni::connectionRequestSuccessCallback)
        },
        {
            "connectionRequestFailureCallback",
            "(Ljava/lang/String;)V",
            reinterpret_cast<void*>(&jni::connectionRequestFailureCallback)
        },
        {
            "connectionInitiatedCallback",
            "(Ljava/lang/String;Ljava/lang/String;)V",
            reinterpret_cast<void*>(&jni::connectionInitiatedCallback)
        },
        {
            "connectionSuccessCallback",
            "(Ljava/lang/String;)V",
            reinterpret_cast<void*>(&jni::connectionSuccessCallback)
        },
        {
            "connectionRejectedCallback",
            "(Ljava/lang/String;)V",
            reinterpret_cast<void*>(&jni::connectionRejectedCallback)
        },
        {
            "connectionBrokenCallback",
            "(Ljava/lang/String;)V",
            reinterpret_cast<void*>(&jni::connectionBrokenCallback)
        },
        {
            "dataSendUpdateCallback",
            "(Ljava/lang/String;JJI)V",
            reinterpret_cast<void*>(&jni::dataSendUpdateCallback)
        },
        {
            "dataReceivedCallback",
            "(Ljava/lang/String;[B)V",
            reinterpret_cast<void*>(&jni::dataReceivedCallback)
        },
        {
            "connectionClosedCallback",
            "(Ljava/lang/String;)V",
            reinterpret_cast<void*>(&jni::connectionClosedCallback)
        }
    };

    JNIEnv* env;
    auto ret = cocos2d::JniHelper::getJavaVM()->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6);

    if (ret != JNI_OK) {
        geode::log::warn("Failed to get java env!");
        return;
    }

    auto nearbyShareUtils = cocos2d::JniHelper::getClassID("com/geode/launcher/utils/NearbyShareUtils");
    ret = env->RegisterNatives(nearbyShareUtils, methods, sizeof(methods) / sizeof(JNINativeMethod));
    if (ret) {
        geode::log::warn("Failed to set native functions!");
        NearbyShareManager::get().m_launcherOutdated = true;
        return;
    }

    jni::enableDiscovery(true);
}

#pragma clang diagnostic pop

#define PARSE_JSTRING(name) const std::string& name##String(env->GetStringUTFChars(name, nullptr))
#define FREE_JSTRING(name) env->ReleaseStringUTFChars(name, name##String.data())

#define PARSE_JBYTEARRAY(name) jbyte* name##Ptr = env->GetByteArrayElements(name, nullptr); std::span<const uint8_t> name##Span((uint8_t*)name##Ptr, env->GetArrayLength(name))
#define FREE_JBYTEARRAY(name) env->ReleaseByteArrayElements(name, name##Ptr, JNI_ABORT)

void jni::discoveryStartCallback(JNIEnv* env, jobject) {
    geode::log::debug("jni::discoveryStartCallback");

    NearbyShareManager::get().discoveryStarted();
}

void jni::discoveryFailureCallback(JNIEnv* env, jobject, jstring error) {
    geode::log::debug("jni::discoveryFailureCallback");
    PARSE_JSTRING(error);
    NearbyShareManager::get().discoveryFailed(errorString);
    FREE_JSTRING(error);
}

void jni::advertisingStartCallback(JNIEnv* env, jobject) {
    geode::log::debug("jni::advertisingStartCallback");
    NearbyShareManager::get().advertisingStarted();
}

void jni::advertisingFailureCallback(JNIEnv* env, jobject, jstring error) {
    geode::log::debug("jni::advertisingFailureCallback");
    PARSE_JSTRING(error);
    NearbyShareManager::get().advertisingFailed(errorString);
    FREE_JSTRING(error);
}

void jni::endpointFoundCallback(JNIEnv* env, jobject, jstring endpoint) {
    geode::log::debug("jni::endpointFoundCallback");
    PARSE_JSTRING(endpoint);
    NearbyShareManager::get().endpointFound(endpointString);
    FREE_JSTRING(endpoint);
}

void jni::endpointLostCallback(JNIEnv* env, jobject, jstring endpoint) {
    geode::log::debug("jni::endpointLostCallback");
    PARSE_JSTRING(endpoint);
    NearbyShareManager::get().endpointLost(endpointString);
    FREE_JSTRING(endpoint);
}

void jni::connectionRequestSuccessCallback(JNIEnv* env, jobject, jstring endpoint) {
    geode::log::debug("jni::connectionRequestSuccessCallback");
    PARSE_JSTRING(endpoint);
    NearbyShareManager::get().requestSuccessful(endpointString);
    FREE_JSTRING(endpoint);
}

void jni::connectionRequestFailureCallback(JNIEnv* env, jobject, jstring endpoint) {
    geode::log::debug("jni::connectionRequestFailureCallback");
    PARSE_JSTRING(endpoint);
    NearbyShareManager::get().requestFailed(endpointString);
    FREE_JSTRING(endpoint);
}

void jni::connectionInitiatedCallback(JNIEnv* env, jobject, jstring endpoint, jstring digits) {
    geode::log::debug("jni::connectionInitiatedCallback");
    PARSE_JSTRING(endpoint); PARSE_JSTRING(digits);
    NearbyShareManager::get().connectionInitiated(endpointString, digitsString);
    FREE_JSTRING(endpoint); FREE_JSTRING(digits);
}

void jni::connectionSuccessCallback(JNIEnv* env, jobject, jstring endpoint) {
    geode::log::debug("jni::connectionSuccessCallback");
    PARSE_JSTRING(endpoint);
    NearbyShareManager::get().connectionSuccessful(endpointString);
    FREE_JSTRING(endpoint);
}

void jni::connectionRejectedCallback(JNIEnv* env, jobject, jstring endpoint) {
    geode::log::debug("jni::connectionRejectedCallback");
    PARSE_JSTRING(endpoint);
    NearbyShareManager::get().connectionRejected(endpointString);
    FREE_JSTRING(endpoint);
}

void jni::connectionBrokenCallback(JNIEnv* env, jobject, jstring endpoint) {
    geode::log::debug("jni::connectionBrokenCallback");
    PARSE_JSTRING(endpoint);
    NearbyShareManager::get().connectionBroken(endpointString);
    FREE_JSTRING(endpoint);
}

void jni::dataSendUpdateCallback(JNIEnv* env, jobject, jstring endpoint, jlong bytesTransferred, jlong totalBytes, jint status) {
    geode::log::debug("jni::dataSendUpdateCallback");
    PARSE_JSTRING(endpoint);
    NearbyShareManager::get().dataSent(endpointString, bytesTransferred, totalBytes, status);
    FREE_JSTRING(endpoint);
}

void jni::dataReceivedCallback(JNIEnv* env, jobject, jstring endpoint, jbyteArray data) {
    geode::log::debug("jni::dataReceivedCallback");
    PARSE_JSTRING(endpoint);
    PARSE_JBYTEARRAY(data);
    NearbyShareManager::get().dataReceived(endpointString, dataSpan);
    FREE_JSTRING(endpoint);
    FREE_JBYTEARRAY(data);
}

void jni::connectionClosedCallback(JNIEnv* env, jobject, jstring endpoint) {
    geode::log::debug("jni::connectionClosedCallback");
    PARSE_JSTRING(endpoint);
    NearbyShareManager::get().connectionClosed(endpointString);
    FREE_JSTRING(endpoint);
}

#undef PARSE_JSTRING
#undef FREE_JSTRING

#undef PARSE_JBYTEARRAY
#undef FREE_JBYTEARRAY

bool jni::hasPermissions() {
    auto info = cocos2d::JniMethodInfo();
    if (!cocos2d::JniHelper::getStaticMethodInfo(info, "com/geode/launcher/utils/NearbyShareUtils", "hasPermissions", "()Z")) {
        geode::log::warn("Failed to get JNI method info for hasPermissions!");
        return false;
    }

    auto ret = info.env->CallStaticBooleanMethod(info.classID, info.methodID);
    info.env->DeleteLocalRef(info.classID);

    return ret;
}

void jni::requestPermissions() {
    auto info = cocos2d::JniMethodInfo();
    if (!cocos2d::JniHelper::getStaticMethodInfo(info, "com/geode/launcher/utils/NearbyShareUtils", "requestPermissions", "()V")) {
        geode::log::warn("Failed to get JNI method info for requestPermissions!");
        return;
    }

    info.env->CallStaticVoidMethod(info.classID, info.methodID);
    info.env->DeleteLocalRef(info.classID);
}

void jni::enableDiscovery(bool enabled) {
    auto info = cocos2d::JniMethodInfo();
    if (!cocos2d::JniHelper::getStaticMethodInfo(info, "com/geode/launcher/utils/NearbyShareUtils", "enableDiscovery", "(Z)V")) {
        geode::log::warn("Failed to get JNI method info for enableDiscovery!");
        return;
    }

    info.env->CallStaticVoidMethod(info.classID, info.methodID, enabled);
    info.env->DeleteLocalRef(info.classID);
}

void jni::setDiscoveryName(const std::string& name) {
    auto info = cocos2d::JniMethodInfo();
    if (!cocos2d::JniHelper::getStaticMethodInfo(info, "com/geode/launcher/utils/NearbyShareUtils", "setDiscoveryName", "(Ljava/lang/String;)V")) {
        geode::log::warn("Failed to get JNI method info for setDiscoveryName!");
        return;
    }

    jstring javaString = info.env->NewStringUTF(name.data());
    info.env->CallStaticVoidMethod(info.classID, info.methodID, javaString);
    info.env->DeleteLocalRef(javaString);
    info.env->DeleteLocalRef(info.classID);
}

void jni::beginDiscovery(Strategy strategy) {
    auto info = cocos2d::JniMethodInfo();
    if (!cocos2d::JniHelper::getStaticMethodInfo(info, "com/geode/launcher/utils/NearbyShareUtils", "beginDiscovery", "(I)V")) {
        geode::log::warn("Failed to get JNI method info for beginDiscovery!");
        return;
    }

    info.env->CallStaticVoidMethod(info.classID, info.methodID, fmt::underlying(strategy));
    info.env->DeleteLocalRef(info.classID);
}

void jni::beginAdvertising(Strategy strategy) {
    auto info = cocos2d::JniMethodInfo();
    if (!cocos2d::JniHelper::getStaticMethodInfo(info, "com/geode/launcher/utils/NearbyShareUtils", "beginAdvertising", "(I)V")) {
        geode::log::warn("Failed to get JNI method info for beginAdvertising!");
        return;
    }

    info.env->CallStaticVoidMethod(info.classID, info.methodID, fmt::underlying(strategy));
    info.env->DeleteLocalRef(info.classID);
}

void jni::requestConnection(const std::string& endpoint) {
    auto info = cocos2d::JniMethodInfo();
    if (!cocos2d::JniHelper::getStaticMethodInfo(info, "com/geode/launcher/utils/NearbyShareUtils", "requestConnection", "(Ljava/lang/String;)V")) {
        geode::log::warn("Failed to get JNI method info for requestConnection!");
        return;
    }

    jstring javaString = info.env->NewStringUTF(endpoint.data());
    info.env->CallStaticVoidMethod(info.classID, info.methodID, javaString);
    info.env->DeleteLocalRef(javaString);
    info.env->DeleteLocalRef(info.classID);
}

void jni::acceptConnection(const std::string& endpoint) {
    auto info = cocos2d::JniMethodInfo();
    if (!cocos2d::JniHelper::getStaticMethodInfo(info, "com/geode/launcher/utils/NearbyShareUtils", "acceptConnection", "(Ljava/lang/String;)V")) {
        geode::log::warn("Failed to get JNI method info for acceptConnection!");
        return;
    }

    jstring javaString = info.env->NewStringUTF(endpoint.data());
    info.env->CallStaticVoidMethod(info.classID, info.methodID, javaString);
    info.env->DeleteLocalRef(javaString);
    info.env->DeleteLocalRef(info.classID);
}

void jni::rejectConnection(const std::string& endpoint) {
    auto info = cocos2d::JniMethodInfo();
    if (!cocos2d::JniHelper::getStaticMethodInfo(info, "com/geode/launcher/utils/NearbyShareUtils", "rejectConnection", "(Ljava/lang/String;)V")) {
        geode::log::warn("Failed to get JNI method info for rejectConnection!");
        return;
    }

    jstring javaString = info.env->NewStringUTF(endpoint.data());
    info.env->CallStaticVoidMethod(info.classID, info.methodID, javaString);
    info.env->DeleteLocalRef(javaString);
    info.env->DeleteLocalRef(info.classID);
}

void jni::endDiscovery() {
    auto info = cocos2d::JniMethodInfo();
    if (!cocos2d::JniHelper::getStaticMethodInfo(info, "com/geode/launcher/utils/NearbyShareUtils", "endDiscovery", "()V")) {
        geode::log::warn("Failed to get JNI method info for endDiscovery!");
        return;
    }

    info.env->CallStaticVoidMethod(info.classID, info.methodID);
    info.env->DeleteLocalRef(info.classID);
}

void jni::endAdvertisement() {
    auto info = cocos2d::JniMethodInfo();
    if (!cocos2d::JniHelper::getStaticMethodInfo(info, "com/geode/launcher/utils/NearbyShareUtils", "endAdvertisement", "()V")) {
        geode::log::warn("Failed to get JNI method info for endAdvertisement!");
        return;
    }

    info.env->CallStaticVoidMethod(info.classID, info.methodID);
    info.env->DeleteLocalRef(info.classID);
}

void jni::sendData(const std::string& endpoint, std::span<const uint8_t> data) {
    auto info = cocos2d::JniMethodInfo();
    if (!cocos2d::JniHelper::getStaticMethodInfo(info, "com/geode/launcher/utils/NearbyShareUtils", "sendData", "(Ljava/lang/String;[B)V")) {
        geode::log::warn("Failed to get JNI method info for sendData!");
        return;
    }

    jstring javaString = info.env->NewStringUTF(endpoint.data());
    jbyteArray javaData = info.env->NewByteArray(data.size());
    info.env->SetByteArrayRegion(javaData, 0, data.size(), reinterpret_cast<const jbyte*>(data.data()));
    info.env->CallStaticVoidMethod(info.classID, info.methodID, javaString, javaData);
    info.env->DeleteLocalRef(javaString);
    info.env->DeleteLocalRef(javaData);
    info.env->DeleteLocalRef(info.classID);
}

void jni::disconnect(const std::string& endpoint) {
    auto info = cocos2d::JniMethodInfo();
    if (!cocos2d::JniHelper::getStaticMethodInfo(info, "com/geode/launcher/utils/NearbyShareUtils", "disconnect", "(Ljava/lang/String;)V")) {
        geode::log::warn("Failed to get JNI method info for disconnect!");
        return;
    }

    jstring javaString = info.env->NewStringUTF(endpoint.data());
    info.env->CallStaticVoidMethod(info.classID, info.methodID, javaString);
    info.env->DeleteLocalRef(javaString);
    info.env->DeleteLocalRef(info.classID);
}
