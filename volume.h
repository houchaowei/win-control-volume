#pragma once
#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <iostream>
#include "VolumeChangeNotifier.h"

using namespace std;

static int getVolume() {
    HRESULT hr;
    CoInitialize(NULL);
    IMMDeviceEnumerator* deviceEnumerator = NULL;
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER,
        __uuidof(IMMDeviceEnumerator), (LPVOID*)&deviceEnumerator);
    IMMDevice* defaultDevice = NULL;
    hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
    IAudioEndpointVolume* endpointVolume = NULL;
    hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL,
        (LPVOID*)&endpointVolume);
    float currentVolume = 0;
    endpointVolume->GetMasterVolumeLevelScalar(&currentVolume);
    // cout << "volume: " << currentVolume << endl;
    // volume 输出为 0-100，所以需要乘以 100
    CoUninitialize();
    return currentVolume * 100;
}

// 设置扬声器音量
static int setVolume(float volume) {
    HRESULT hr;
    CoInitialize(NULL);
    IMMDeviceEnumerator* deviceEnumerator = NULL;
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER,
        __uuidof(IMMDeviceEnumerator), (LPVOID*)&deviceEnumerator);
    IMMDevice* defaultDevice = NULL;
    hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
    IAudioEndpointVolume* endpointVolume = NULL;
    hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL,
        (LPVOID*)&endpointVolume);
    // 设置音量
    hr = endpointVolume->SetMasterVolumeLevelScalar(volume / 100.0, NULL);
    if (FAILED(hr)) {
        cout << "SetMasterVolumeLevelScalar failed" << endl;
        return -1;
    }
    CoUninitialize();
    return 0;
}


// 获取麦克风音量
static int getVolumeMicrophone() {
    HRESULT hr;
    CoInitialize(NULL);
    IMMDeviceEnumerator* deviceEnumerator = NULL;
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER,
        __uuidof(IMMDeviceEnumerator), (LPVOID*)&deviceEnumerator);
    IMMDevice* defaultDevice = NULL;
    hr = deviceEnumerator->GetDefaultAudioEndpoint(eCapture, eConsole, &defaultDevice);
    IAudioEndpointVolume* endpointVolume = NULL;
    hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL,
        (LPVOID*)&endpointVolume);
    float currentVolume = 0;
    endpointVolume->GetMasterVolumeLevelScalar(&currentVolume);
    // cout << "volume: " << currentVolume << endl;
    // volume 输出为 0-100，所以需要乘以 100
    CoUninitialize();
    return currentVolume * 100;
}


// 设置麦克风音量
static int setVolumeMicrophone(float volume) {
    HRESULT hr;
    CoInitialize(NULL);
    IMMDeviceEnumerator* deviceEnumerator = NULL;
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER,
        __uuidof(IMMDeviceEnumerator), (LPVOID*)&deviceEnumerator);
    IMMDevice* defaultDevice = NULL;
    hr = deviceEnumerator->GetDefaultAudioEndpoint(eCapture, eConsole, &defaultDevice);
    IAudioEndpointVolume* endpointVolume = NULL;
    hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL,
        (LPVOID*)&endpointVolume);
    // 设置音量
    hr = endpointVolume->SetMasterVolumeLevelScalar(volume / 100.0, NULL);
    if (FAILED(hr)) {
        cout << "SetMasterVolumeLevelScalar failed" << endl;
        return -1;
    }
    CoUninitialize();
    return 0;
}

// 获取是否静音
static bool getMute()
{
    HRESULT hr;
    CoInitialize(NULL);
    IMMDeviceEnumerator* deviceEnumerator = NULL;
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER,
        __uuidof(IMMDeviceEnumerator), (LPVOID*)&deviceEnumerator);
    IMMDevice* defaultDevice = NULL;
    hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
    IAudioEndpointVolume* endpointVolume = NULL;
    hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL,
        (LPVOID*)&endpointVolume);
    BOOL mute;
    endpointVolume->GetMute(&mute);
    CoUninitialize();
    return mute;
}

// 设置是否静音
static int setMute(bool mute)
{
    HRESULT hr;
    CoInitialize(NULL);
    IMMDeviceEnumerator* deviceEnumerator = NULL;
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER,
        __uuidof(IMMDeviceEnumerator), (LPVOID*)&deviceEnumerator);
    IMMDevice* defaultDevice = NULL;
    hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
    IAudioEndpointVolume* endpointVolume = NULL;
    hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL,
        (LPVOID*)&endpointVolume);
    // 设置是否静音
    endpointVolume->SetMute(mute, NULL);
    CoUninitialize();
    return 0;
}

// 监听系统音量变化，当音量变化时，输出音量
static void listenVolume()
{
    HRESULT hr;
    CoInitialize(NULL);
    IMMDeviceEnumerator* deviceEnumerator = NULL;
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER,
        __uuidof(IMMDeviceEnumerator), (LPVOID*)&deviceEnumerator);
    IMMDevice* defaultDevice = NULL;
    hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
    IAudioEndpointVolume* endpointVolume = NULL;
    hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL,
        (LPVOID*)&endpointVolume);
    // 设置回调函数

    VolumeChangeNotifier* notifier = new VolumeChangeNotifier();
    hr = endpointVolume->RegisterControlChangeNotify(notifier);
    if (FAILED(hr))
    {
        cout << "RegisterControlChangeNotify failed" << endl;
        return;
    }
    // 等待回调函数
    Sleep(INFINITE);
    CoUninitialize();
}