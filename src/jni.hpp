#pragma once
#include <jni.h>

namespace jni {

enum class Strategy {
    P2P_CLUSTER = 1,
    P2P_POINT_TO_POINT = 2,
    P2P_STAR = 3
};

void registerJNINatives();

// jni callbacks

void discoveryStartCallback(JNIEnv* env, jobject);
void discoveryFailureCallback(JNIEnv* env, jobject, jstring error);
void advertisingStartCallback(JNIEnv* env, jobject);
void advertisingFailureCallback(JNIEnv* env, jobject, jstring error);

void endpointFoundCallback(JNIEnv* env, jobject, jstring endpoint);
void endpointLostCallback(JNIEnv* env, jobject, jstring endpoint);

void connectionRequestSuccessCallback(JNIEnv* env, jobject, jstring endpoint);
void connectionRequestFailureCallback(JNIEnv* env, jobject, jstring endpoint);

void connectionInitiatedCallback(JNIEnv* env, jobject, jstring endpoint, jstring digits);

void connectionSuccessCallback(JNIEnv* env, jobject, jstring endpoint);
void connectionRejectedCallback(JNIEnv* env, jobject, jstring endpoint);
void connectionBrokenCallback(JNIEnv* env, jobject, jstring endpoint);

void dataSendUpdateCallback(JNIEnv* env, jobject, jstring endpoint, jlong bytesTransferred, jlong totalBytes, jint status);
void dataReceivedCallback(JNIEnv* env, jobject, jstring endpoint, jbyteArray data);

void connectionClosedCallback(JNIEnv* env, jobject, jstring endpoint);

// jni functions

bool hasPermissions();
void requestPermissions();

void enableNearbyConnectionsCallbacks(bool enabled);
void setDiscoveryName(const std::string& name);

void beginDiscovery(Strategy strategy);
void beginAdvertising(Strategy strategy);

void requestConnection(const std::string& endpoint);

void acceptConnection(const std::string& endpoint);
void rejectConnection(const std::string& endpoint);

void endDiscovery();
void endAdvertisement();

void sendData(const std::string& endpoint, std::span<const uint8_t> data);

void disconnect(const std::string& endpoint);

}
