#include <winnt.h>
#include <minwindef.h>
#include <Unknwnbase.h>
#include <endpointvolume.h>
#include <iostream>
using namespace std;

class VolumeChangeNotifier : public IAudioEndpointVolumeCallback
{
    LONG _cRef;
public:
    VolumeChangeNotifier() : _cRef(1) {}
    ~VolumeChangeNotifier() {}
    ULONG STDMETHODCALLTYPE AddRef()
    {
        return InterlockedIncrement(&_cRef);
    }
    ULONG STDMETHODCALLTYPE Release()
    {
        ULONG ulRef = InterlockedDecrement(&_cRef);
        if (0 == ulRef)
        {
            delete this;
        }
        return ulRef;
    }
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, VOID** ppvInterface)
    {
        if (IID_IUnknown == riid)
        {
            AddRef();
            *ppvInterface = (IUnknown*)this;
        }
        else if (__uuidof(IAudioEndpointVolumeCallback) == riid)
        {
            AddRef();
            *ppvInterface = (IAudioEndpointVolumeCallback*)this;
        }
        else
        {
            *ppvInterface = NULL;
            return E_NOINTERFACE;
        }
        return S_OK;
    }
    // 实现 OnNotify 方法
    HRESULT STDMETHODCALLTYPE OnNotify(PAUDIO_VOLUME_NOTIFICATION_DATA pNotify)
    {
        if (pNotify == NULL)
        {
            return E_INVALIDARG;
        }
        // 输出音量
        cout << "Volume changed: " << pNotify->fMasterVolume << endl;
        return S_OK;
    }

    VolumeChangeNotifier(const LONG& _cRef)
        : _cRef(_cRef)
    {
    }

    bool operator==(const VolumeChangeNotifier& other) const
    {
        return false;
    }
};