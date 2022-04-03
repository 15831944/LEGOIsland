// MxDirectDrawWnd.h : header file
//

class MxDirectDraw;

/////////////////////////////////////////////////////////////////////////////
// MxDirectDrawWnd window

class MxDirectDrawWnd : public CWnd
{
// Construction
public:
	MxDirectDrawWnd();

// Attributes
public:
    MxDirectDraw* DirectDraw() { return m_pDirectDraw; }

// Operations
public:
    virtual BOOL    Create(const char* windowName,
                           const CWnd* pParentWnd,
                           BOOL fullScreen,
                           int width, int height, int bpp,
                           const PALETTEENTRY* pPaletteEntries,
                           int pPaletteEntryCount);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MxDirectDrawWnd)
	public:
	virtual BOOL DestroyWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~MxDirectDrawWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(MxDirectDrawWnd)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    virtual MxDirectDraw*   CreateDirectDraw();

    const PALETTEENTRY*   PaletteEntries() const { return m_pPaletteEntries; }
    int                   PaletteEntryCount() const { return m_paletteEntryCount; }

    static void FatalErrorHandler(const char*, HRESULT, void*);
    static void ErrorHandler(const char*, HRESULT, void*);

private:
    MxDirectDraw*   m_pDirectDraw;
    BOOL            m_handleActivate;
    PALETTEENTRY*   m_pPaletteEntries;
    int             m_paletteEntryCount;
};

BOOL GetResourceBitmapPaletteEntries(const char* pResourceName,
                                     int paletteEntryCount,
                                     PALETTEENTRY* pPaletteEntry,
                                     int& rPaletteEntryCount);

/////////////////////////////////////////////////////////////////////////////
