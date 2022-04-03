#include "MxDirectX.h"

#define RELEASE(x) if (x != NULL) {x->Release(); x = NULL;}

MxDirect3D::MxDirect3D()
{
    m_pDirect3D             = 0;
    m_pDirect3DDevice       = 0;
    m_bTexturesDisabled     = FALSE;
    m_pCurrentDeviceInfo    = 0;
    m_deviceInfoCount       = 0;
}

MxDirect3D::~MxDirect3D()
{
    Destroy();
}

BOOL
MxDirect3D::Create(HWND hWnd, BOOL fullScreen,
                   int width, int height, int bpp,
                   const PALETTEENTRY* pPaletteEntries, 
                   int paletteEntryCount)
{
    if (!MxDirectDraw::Create(hWnd,
                              fullScreen, width, height, bpp,
                              pPaletteEntries, paletteEntryCount))
    {
        return FALSE;
    }

    return (D3DCreate() && D3DInit() && D3DSetMode());
}

void
MxDirect3D::Destroy()
{
    RELEASE(m_pDirect3DDevice);
    RELEASE(m_pDirect3D);
    MxDirectDraw::Destroy();

    // ??? or in Create()
    m_pCurrentDeviceInfo    = 0;
    m_deviceInfoCount       = 0;
}

void
MxDirect3D::DestroyButNotDirectDraw()
{
    RELEASE(m_pDirect3DDevice);
    RELEASE(m_pDirect3D);
    MxDirectDraw::DestroyButNotDirectDraw();

    // ??? or in Create()
    m_pCurrentDeviceInfo    = 0;
    m_deviceInfoCount       = 0;
}

BOOL
MxDirect3D::D3DCreate()
{
    HRESULT result;

    result = DirectDraw()->QueryInterface(IID_IDirect3D, (void**) &m_pDirect3D);
    if (result != DD_OK)
    {
        Error("Creation of IDirect3D failed", result);
        return FALSE;
    }
    return TRUE; 
}

BOOL
MxDirect3D::D3DInit()
{
    HRESULT result;

    result = m_pDirect3D->EnumDevices(EnumDevicesCallback, this);
    if (result != DD_OK)
    {
        Error("EnumDevices failed", result);
    }

    return (result == DD_OK);
}

// Initialize the D3D objects which change when the mode changes.
BOOL
MxDirect3D::D3DSetMode()
{
    HRESULT     result;

    // Create the viewport and device objects.
    if (m_pCurrentDeviceInfo->HWDesc.dcmColorModel)
    {
        // Hardware driver
        if (m_bOnlySoftRender)
        {
            Error("Failed to place vital surfaces in video memory for hardware driver", 
                  DDERR_GENERIC);
            return FALSE;
        }
        if (m_pCurrentDeviceInfo->HWDesc.dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_PERSPECTIVE)
        {
            m_bTexturesDisabled =  FALSE;
        }
        else
        {
            m_bTexturesDisabled = TRUE;
        } 

        if (!CreateZBuffer(DDSCAPS_VIDEOMEMORY, ZBufferDepth(m_pCurrentDeviceInfo)))
        {
            return FALSE;
        }
    }
    else
    {
        // Software driver
        if (m_pCurrentDeviceInfo->HELDesc.dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_PERSPECTIVE)
        {
            m_bTexturesDisabled = FALSE;
        }
        else
        {
            m_bTexturesDisabled = TRUE;
        } 

        if (!CreateZBuffer(DDSCAPS_SYSTEMMEMORY, ZBufferDepth(m_pCurrentDeviceInfo)))
        {
            return FALSE;
        }
    }

    result = BackBuffer()->QueryInterface(m_pCurrentDeviceInfo->Guid,
                                          (void**) &m_pDirect3DDevice);
    if (result != DD_OK)
    {
        Error("Create D3D device failed", result);
        return FALSE;
    }

    {
        Mode    mode = CurrentMode();

        // enumerate display modes again - m_pCurrentDeviceInfo is now set
        if (!EnumerateDisplayModes())
        {
            return FALSE;
        }

        // NOTE: the current mode may have been removed
        if (IsFullScreen())
        {
            if (!IsSupportedMode(mode.width, mode.height, mode.bitsPerPixel))
            {
                Error("This device cannot support the current display mode", 
                      DDERR_GENERIC);
                return FALSE;
            }
        }
    }

    return TRUE;
}

BOOL
MxDirect3D::FilterDisplayModes(LPDDSURFACEDESC pddsd)
{
    if (m_pCurrentDeviceInfo)
    {
        DWORD deviceDepth;

        if (m_pCurrentDeviceInfo->HWDesc.dwFlags & D3DDD_DEVICERENDERBITDEPTH)
        {
            deviceDepth = m_pCurrentDeviceInfo->HWDesc.dwDeviceRenderBitDepth;
        } 
        else 
        {
            deviceDepth = m_pCurrentDeviceInfo->HELDesc.dwDeviceRenderBitDepth;
        }

        return (((pddsd->ddpfPixelFormat.dwRGBBitCount == 8UL) &&
                 (deviceDepth & DDBD_8)) ||
                ((pddsd->ddpfPixelFormat.dwRGBBitCount == 16UL) &&
                 (deviceDepth & DDBD_16)));
    }

    return TRUE;
}

int MxDirect3D::ZBufferDepth(Direct3DDeviceInfo* pDeviceInfo)
{
    int   depth;
    DWORD   deviceDepth;

    if (pDeviceInfo->HWDesc.dwFlags & D3DDD_DEVICEZBUFFERBITDEPTH)
    {
        deviceDepth = pDeviceInfo->HWDesc.dwDeviceZBufferBitDepth;
    }
    else
    {
        deviceDepth = pDeviceInfo->HELDesc.dwDeviceZBufferBitDepth;
    }

    if (deviceDepth & DDBD_32)
        depth = 32;
    else if (deviceDepth & DDBD_24)
        depth = 24;
    else if (deviceDepth & DDBD_16)
        depth = 16;
    else if (deviceDepth & DDBD_8)
        depth = 8;
    else
        depth = -1;

    return depth;
}

HRESULT 
MxDirect3D::EnumDevicesCallback(GUID* pGuid,
                                char* pDeviceDescription,
                                char* pDeviceName,
                                LPD3DDEVICEDESC pHWDesc,
                                LPD3DDEVICEDESC pHELDesc)
{
    m_deviceInfo[m_deviceInfoCount].Initialize(pGuid,
                                               pDeviceDescription,
                                               pDeviceName,
                                               pHWDesc,
                                               pHELDesc);

    // Chooses hardware over software, RGB lights over mono lights
    // If software only, choose Ramp over RGB.

    if (!m_pCurrentDeviceInfo)
    {
        m_pCurrentDeviceInfo = &m_deviceInfo[m_deviceInfoCount];
    }
    else
    {
        if (pHWDesc->dcmColorModel && !m_bOnlySoftRender)
        {
            if (!m_pCurrentDeviceInfo->HWDesc.dcmColorModel)
            {
                m_pCurrentDeviceInfo = &m_deviceInfo[m_deviceInfoCount];
            }
            else if (pHWDesc->dcmColorModel & D3DCOLOR_RGB &&
                     m_pCurrentDeviceInfo->HWDesc.dcmColorModel & D3DCOLOR_MONO)
            {
                m_pCurrentDeviceInfo = &m_deviceInfo[m_deviceInfoCount];
            }
        }
        else if (!m_pCurrentDeviceInfo->HWDesc.dcmColorModel)
        {
            if (!m_pCurrentDeviceInfo->HELDesc.dcmColorModel)
            {
                m_pCurrentDeviceInfo = &m_deviceInfo[m_deviceInfoCount];
            }
            else if (pHELDesc->dcmColorModel & D3DCOLOR_MONO &&
                     m_pCurrentDeviceInfo->HELDesc.dcmColorModel & D3DCOLOR_RGB)
            {
                m_pCurrentDeviceInfo = &m_deviceInfo[m_deviceInfoCount];
            }
        }
    }
    m_deviceInfoCount++;

    if (m_deviceInfoCount == maxDeviceInfoCount)
    {
        return (D3DENUMRET_CANCEL);
    }

    return (D3DENUMRET_OK);
}

HRESULT CALLBACK 
MxDirect3D::EnumDevicesCallback(GUID* pGuid,
                                char* pDeviceDescription,
                                char* pDeviceName,
                                LPD3DDEVICEDESC pHWDesc,
                                LPD3DDEVICEDESC pHELDesc,
                                void* pContext)
{
    MxDirect3D* pDirect3D = (MxDirect3D*) pContext;

    return pDirect3D->EnumDevicesCallback(pGuid,
                                          pDeviceDescription,
                                          pDeviceName,
                                          pHWDesc,
                                          pHELDesc);
}

// Returns a string describing the given error code.
const char*
MxDirect3D::ErrorToString(HRESULT error)
{
    switch(error) {
        case DD_OK:
            return "No error.\0";
        case D3DERR_BADMAJORVERSION:
            return "D3DERR_BADMAJORVERSION\0";
        case D3DERR_BADMINORVERSION:
            return "D3DERR_BADMINORVERSION\0";
        case D3DERR_EXECUTE_LOCKED:
            return "D3DERR_EXECUTE_LOCKED\0";
        case D3DERR_EXECUTE_NOT_LOCKED:
            return "D3DERR_EXECUTE_NOT_LOCKED\0";
        case D3DERR_EXECUTE_CREATE_FAILED:
            return "D3DERR_EXECUTE_CREATE_FAILED\0";
        case D3DERR_EXECUTE_DESTROY_FAILED:
            return "D3DERR_EXECUTE_DESTROY_FAILED\0";
        case D3DERR_EXECUTE_LOCK_FAILED:
            return "D3DERR_EXECUTE_LOCK_FAILED\0";
        case D3DERR_EXECUTE_UNLOCK_FAILED:
            return "D3DERR_EXECUTE_UNLOCK_FAILED\0";
        case D3DERR_EXECUTE_FAILED:
            return "D3DERR_EXECUTE_FAILED\0";
        case D3DERR_EXECUTE_CLIPPED_FAILED:
            return "D3DERR_EXECUTE_CLIPPED_FAILED\0";
        case D3DERR_TEXTURE_NO_SUPPORT:
            return "D3DERR_TEXTURE_NO_SUPPORT\0";
        case D3DERR_TEXTURE_NOT_LOCKED:
            return "D3DERR_TEXTURE_NOT_LOCKED\0";
        case D3DERR_TEXTURE_LOCKED:
            return "D3DERR_TEXTURELOCKED\0";
        case D3DERR_TEXTURE_CREATE_FAILED:
            return "D3DERR_TEXTURE_CREATE_FAILED\0";
        case D3DERR_TEXTURE_DESTROY_FAILED:
            return "D3DERR_TEXTURE_DESTROY_FAILED\0";
        case D3DERR_TEXTURE_LOCK_FAILED:
            return "D3DERR_TEXTURE_LOCK_FAILED\0";
        case D3DERR_TEXTURE_UNLOCK_FAILED:
            return "D3DERR_TEXTURE_UNLOCK_FAILED\0";
        case D3DERR_TEXTURE_LOAD_FAILED:
            return "D3DERR_TEXTURE_LOAD_FAILED\0";
        case D3DERR_MATRIX_CREATE_FAILED:
            return "D3DERR_MATRIX_CREATE_FAILED\0";
        case D3DERR_MATRIX_DESTROY_FAILED:
            return "D3DERR_MATRIX_DESTROY_FAILED\0";
        case D3DERR_MATRIX_SETDATA_FAILED:
            return "D3DERR_MATRIX_SETDATA_FAILED\0";
        case D3DERR_SETVIEWPORTDATA_FAILED:
            return "D3DERR_SETVIEWPORTDATA_FAILED\0";
        case D3DERR_MATERIAL_CREATE_FAILED:
            return "D3DERR_MATERIAL_CREATE_FAILED\0";
        case D3DERR_MATERIAL_DESTROY_FAILED:
            return "D3DERR_MATERIAL_DESTROY_FAILED\0";
        case D3DERR_MATERIAL_SETDATA_FAILED:
            return "D3DERR_MATERIAL_SETDATA_FAILED\0";
        case D3DERR_LIGHT_SET_FAILED:
            return "D3DERR_LIGHT_SET_FAILED\0";
        default:
            return MxDirectDraw::ErrorToString(error);
    }
}
