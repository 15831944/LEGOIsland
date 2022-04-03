// ROIDoc.cpp : implementation of the CROIDoc class
//

#include "stdafx.h"
#include "ROIInspector.h"

#include "ROIDoc.h"
#include "LegoROI.h"
#include "LegoStorage.h"
#include "LegoAnim.h"
#include "Version.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CROIDoc

IMPLEMENT_DYNCREATE(CROIDoc, CDocument)

BEGIN_MESSAGE_MAP(CROIDoc, CDocument)
	//{{AFX_MSG_MAP(CROIDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CROIDoc construction/destruction

CROIDoc::CROIDoc()
{
	// TODO: add one-time construction code here
    m_pROIs                 = 0;
    m_trees                 = 0;
    m_roiCount              = 0;
    m_pRenderer             = 0;
    m_pViewLODListManager   = 0;
}

CROIDoc::~CROIDoc()
{
    ASSERT(!m_pROIs);    // DeleteContents() should have been called
}

LegoAnim*
CROIDoc::GetAnimation(int i) const
{
    ASSERT(i < m_roiCount);
    
    return &m_trees[i];
}

BOOL CROIDoc::SetManagers(Tgl::Renderer* pRenderer,
                          ViewLODListManager* pViewLODListManager)
{
    ASSERT(!m_pRenderer);
    ASSERT(!m_pViewLODListManager);

    m_pRenderer             = pRenderer;
    m_pViewLODListManager   = pViewLODListManager;

    return TRUE;
}

BOOL CROIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
    
    ASSERT(!m_pROIs);    // DeleteContents() should have been called

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CROIDoc serialization

void CROIDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
        if (m_pROIs)
        {
            LegoFile    file;
            LegoResult  result;

            BeginWaitCursor();
            result = file.Open(ar.GetFile()->GetFilePath(), LegoFile::c_write);
            if (result == SUCCESS)
            {
                LegoU32 version = MODEL_VERSION;
                result = file.Write(&version, sizeof(version));
                if (result == SUCCESS) {
                    result = file.Write(&m_roiCount, sizeof(m_roiCount));
                }

                for (int i = 0; i < m_roiCount; i++)
                {
                    if (result == SUCCESS)
                    {
        	            result = m_trees[i].Write(&file);
                    }
	                if (result == SUCCESS)
                    {
        	            result = m_pROIs[i]->Write(&file);
                    }
                }
        	    file.Close();
            }
            EndWaitCursor();

            if (result != SUCCESS)
            {
                AfxMessageBox("Failed to save");
            }
        }
	}
	else
	{
        LegoFile    file;
        LegoResult  result;

        ASSERT(!m_pROIs);    // DeleteContents() should have been called
        ASSERT(m_pRenderer);
        ASSERT(m_pViewLODListManager);

        BeginWaitCursor();
        result = file.Open(ar.GetFile()->GetFilePath(), LegoFile::c_read);
        if (result == SUCCESS)
        {
            LegoU32 version;
            result = file.Read(&version, sizeof(version));
            if (result == SUCCESS) {
                if (version == MODEL_VERSION) {
                    result = file.Read(&m_roiCount, sizeof(m_roiCount));
                    if (result == SUCCESS)
                    {
                        int i;

                        m_pROIs = new LegoROI* [m_roiCount];
                        m_trees = new LegoAnim[m_roiCount];

                        memset(m_pROIs, 0, m_roiCount * sizeof(LegoROI*));

                        for (i = 0; i < m_roiCount; i++)
                        {
	                        if (result == SUCCESS)
                            {
            	                result = m_trees[i].Read(&file);
                            }
	                        if (result == SUCCESS)
                            {
                                m_pROIs[i] = new LegoROI(m_pRenderer);
        	                    result = m_pROIs[i]->Read(m_pRenderer,
                                                          m_pViewLODListManager,
                                                          &file,
                                                          TRUE);
                            }
                            if (result == SUCCESS)
                            {
        	                    result = m_pROIs[i]->SetFrame(&m_trees[i], 0);
                            }
                        }
                    }
                }
                else
                {
                    CString msg;

                    msg.Format("Version mismatch: File created by converter version %ld expected\n%s was created by converter version %ld",
                                (long) MODEL_VERSION, (const char*) ar.GetFile()->GetFilePath(), (long) version);

                    AfxMessageBox(msg);
                    result = FAILURE;
                }
            }
        	file.Close();
        }
        EndWaitCursor();

        if (result != SUCCESS)
        {
            DeleteContents();
            AfxMessageBox("Failed to load");
        }
	}
}

/////////////////////////////////////////////////////////////////////////////
// CROIDoc diagnostics

#ifdef _DEBUG
void CROIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CROIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CROIDoc commands

void CROIDoc::DeleteContents() 
{
    for (int i = 0; i < m_roiCount; i++)
    {
        delete m_pROIs[i];
        m_pROIs[i] = 0;
    }
    delete [] m_pROIs;
    delete [] m_trees;
    m_pROIs     = 0;
    m_trees     = 0;
    m_roiCount  = 0;

    CDocument::DeleteContents();
}

int CROIDoc::GetTotalLODCount(const ROI* pROI) const
{
    int lodCount = 0;

    if (pROI)
    {
	    const CompoundObject*   pCompoundObject = pROI->GetComp();
    
        lodCount = pROI->GetLODCount();
        
        if (pCompoundObject)
        {
            CompoundObject::const_iterator  iterator = pCompoundObject->begin();

            while (!(iterator == pCompoundObject->end()))
            {
                lodCount += GetTotalLODCount(*iterator);
                ++iterator;
            }
        }
    }

    return lodCount;
}


void CROIDoc::OnCloseDocument() 
{
    // CDocument::OnCloseDocument() first deletes frame window, which deletes
    // the view, which deletes the LODList manager... and LODList manager
    // likes to have no outstanding references to LODLists when it is being
    // deleted, so delete the loaded ROIs here

    // This issue wouldn't have come up if the document (or someone else but
    // the view) owned the renderer and lodlist manager.  If Lego3DManager
    // allowed them to be passed in... this could then be arranged.

    DeleteContents();

	CDocument::OnCloseDocument();
}

