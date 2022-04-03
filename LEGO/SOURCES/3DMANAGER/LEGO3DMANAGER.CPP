// Lego3DManager.cpp : implementation file
//
#include "stdafx.h"
#include "Lego3DManager.h"

#include "tgl.h"
#include "Lego3DView.h"
#include "ViewLODList.h"

//////////////////////////////////////////////////////////////////////////////

BOOL InitializeCreateStruct(TglSurface::CreateStruct& rTglSurfaceCreateStruct,
                            const Lego3DManager::CreateStruct& rCreateStruct)
{
    // initializes a TglSurface::CreateStruct from a Lego3DManager::CreateStruct
    rTglSurfaceCreateStruct.m_pDriverGUID   = rCreateStruct.m_pDriverGUID;
    rTglSurfaceCreateStruct.m_hWnd          = rCreateStruct.m_hWnd;
    rTglSurfaceCreateStruct.m_pDirectDraw   = rCreateStruct.m_pDirectDraw;
    rTglSurfaceCreateStruct.m_pFrontBuffer  = rCreateStruct.m_pFrontBuffer;
    rTglSurfaceCreateStruct.m_pBackBuffer   = rCreateStruct.m_pBackBuffer;
    rTglSurfaceCreateStruct.m_pPalette      = rCreateStruct.m_pPalette;
    rTglSurfaceCreateStruct.m_isFullScreen  = rCreateStruct.m_isFullScreen;

    return TRUE;
}

//////////////////////////////////////////////////////////////////////////////

Lego3DManager::Lego3DManager()
{
    // Tgl things
    m_pRenderer     = 0;

    m_pLego3DView   = 0;
    m_pViewLODListManager   = 0;
}

Lego3DManager::~Lego3DManager()
{
    Destroy();
}

BOOL
Lego3DManager::Create(CreateStruct& rCreateStruct)
{
    TglSurface::CreateStruct    tglSurfaceCreateStruct;
    BOOL                        result;

    assert(!m_pViewLODListManager);
    assert(!m_pRenderer);
    assert(!m_pLego3DView);

    m_pViewLODListManager = new ViewLODListManager;
    assert(m_pViewLODListManager);

    m_pRenderer = Tgl::CreateRenderer();
    assert(m_pRenderer);

    m_pLego3DView = new Lego3DView;

    result = InitializeCreateStruct(tglSurfaceCreateStruct, rCreateStruct);
    assert(result);

    result = m_pLego3DView->Create(tglSurfaceCreateStruct, m_pRenderer);
    assert(result);

    return result;
}

void
Lego3DManager::Destroy()
{
    delete m_pLego3DView;
    m_pLego3DView = 0;

    delete m_pRenderer;
    m_pRenderer = 0;

    delete m_pViewLODListManager;
    m_pViewLODListManager = 0;
}

double
Lego3DManager::Render()
{
    assert(m_pLego3DView);

    return m_pLego3DView->Render();
}
