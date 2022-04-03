// LegoDoc.cpp : implementation of the CLegoDoc class
//

#include "stdafx.h"
#include "Lego.h"

#include "LegoDoc.h"
#include "Town.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLegoDoc

IMPLEMENT_DYNCREATE(CLegoDoc, CDocument)

BEGIN_MESSAGE_MAP(CLegoDoc, CDocument)
	//{{AFX_MSG_MAP(CLegoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLegoDoc construction/destruction

CLegoDoc::CLegoDoc()
{
	// TODO: add one-time construction code here
    m_pTown = 0;
}

CLegoDoc::~CLegoDoc()
{
    SetTown(0);
}

BOOL CLegoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
    ASSERT(!m_pTown);

    m_pTown = new Town;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CLegoDoc serialization

void CLegoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
        // ??? view/game still holding on to a now invalid pointer...
        SetTown(new Town);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CLegoDoc diagnostics

#ifdef _DEBUG
void CLegoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLegoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLegoDoc commands

void CLegoDoc::SetTown(Town* pTown)
{
    delete m_pTown;
    m_pTown = pTown;
}

void CLegoDoc::DeleteContents() 
{
	// TODO: Add your specialized code here and/or call the base class
    SetTown(0);

	CDocument::DeleteContents();
}
