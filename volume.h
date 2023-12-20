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
    // volume ���Ϊ 0-100��������Ҫ���� 100
    CoUninitialize();
    return currentVolume * 100;
}

// ��������������
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
    // ��������
    hr = endpointVolume->SetMasterVolumeLevelScalar(volume / 100.0, NULL);
    if (FAILED(hr)) {
        cout << "SetMasterVolumeLevelScalar failed" << endl;
        return -1;
    }
    CoUninitialize();
    return 0;
}


// ��ȡ��˷�����
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
    // volume ���Ϊ 0-100��������Ҫ���� 100
    CoUninitialize();
    return currentVolume * 100;
}


// ������˷�����
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
    // ��������
    hr = endpointVolume->SetMasterVolumeLevelScalar(volume / 100.0, NULL);
    if (FAILED(hr)) {
        cout << "SetMasterVolumeLevelScalar failed" << endl;
        return -1;
    }
    CoUninitialize();
    return 0;
}

// ��ȡ�Ƿ���
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

// �����Ƿ���
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
    // �����Ƿ���
    endpointVolume->SetMute(mute, NULL);
    CoUninitialize();
    return 0;
}

// ����ϵͳ�����仯���������仯ʱ���������
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
    // ���ûص�����

    VolumeChangeNotifier* notifier = new VolumeChangeNotifier();
    hr = endpointVolume->RegisterControlChangeNotify(notifier);
    if (FAILED(hr))
    {
        cout << "RegisterControlChangeNotify failed" << endl;
        return;
    }
    // �ȴ��ص�����
    Sleep(INFINITE);
    CoUninitialize();
}