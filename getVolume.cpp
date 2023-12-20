#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <iostream>

using namespace std;

int main1() {
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
    cout << "{\"volume\":" << currentVolume * 100 << "}" << endl;
    CoUninitialize();
    return 0;
}
