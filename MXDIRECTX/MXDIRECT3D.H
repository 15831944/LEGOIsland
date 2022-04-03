#ifndef _MxDirect3D_h
#define _MxDirect3D_h

#include "MxDirectDraw.h"
#include <d3d.h>

//////////////////////////////////////////////////////////////////////////////
//
// MxDirect3D

class MxDirect3D : public MxDirectDraw
{

    struct Direct3DDeviceInfo
    {
        char            Desc[50];
        char            Name[30];
        D3DDEVICEDESC   HWDesc;
        D3DDEVICEDESC   HELDesc;
        GUID            Guid;

        void Initialize(const GUID* pGuid,
                        const char* pDeviceDescription,
                        const char* pDeviceName,
                        const LPD3DDEVICEDESC pHWDesc,
                        const LPD3DDEVICEDESC pHELDesc)
        {
            memcpy(&Guid, pGuid, sizeof(GUID));
            strcpy(Desc, pDeviceDescription);
            strcpy(Name, pDeviceName);
            memcpy(&HWDesc, pHWDesc, sizeof(HWDesc));
            memcpy(&HELDesc, pHELDesc, sizeof(HELDesc));
        }
    };

    enum { maxDeviceInfoCount = 5 };

public:
    MxDirect3D();
    ~MxDirect3D();

    BOOL    Create(HWND,
                   BOOL fullScreen,
                   int width, int height, int bpp,
                   const PALETTEENTRY* pPaletteEntries,
                   int pPaletteEntryCount);
    void    Destroy();
    void    DestroyButNotDirectDraw();

    const char* ErrorToString(HRESULT);

    IDirect3D*          Direct3D()          { return m_pDirect3D;}
    IDirect3DDevice*    Direct3DDevice()    { return m_pDirect3DDevice;}

protected:
    BOOL        D3DCreate();
    BOOL        D3DInit();
    BOOL        D3DSetMode();

    int         ZBufferDepth(Direct3DDeviceInfo*);

    BOOL        FilterDisplayModes(LPDDSURFACEDESC);

    HRESULT     EnumDevicesCallback(GUID*, char*, char*,
                                    LPD3DDEVICEDESC, LPD3DDEVICEDESC);

    static HRESULT CALLBACK EnumDevicesCallback(GUID*, char*, char*,
                                                LPD3DDEVICEDESC, LPD3DDEVICEDESC,
                                                void*);

private:
    Direct3DDeviceInfo  m_deviceInfo[maxDeviceInfoCount];
    Direct3DDeviceInfo* m_pCurrentDeviceInfo;
    int                 m_deviceInfoCount;

    IDirect3D*          m_pDirect3D;
    IDirect3DDevice*    m_pDirect3DDevice;

    BOOL                m_bTexturesDisabled;
};

#endif /* _MxDirect3D_h */