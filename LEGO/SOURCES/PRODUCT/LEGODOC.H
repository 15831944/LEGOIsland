// LegoDoc.h : interface of the CLegoDoc class
//
/////////////////////////////////////////////////////////////////////////////

class Town;

class CLegoDoc : public CDocument
{
protected: // create from serialization only
	CLegoDoc();
	DECLARE_DYNCREATE(CLegoDoc)

// Attributes
public:
    void    SetTown(Town*);
	Town*   GetTown() { return m_pTown; }; 

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLegoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLegoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLegoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	Town*	m_pTown;	

};

/////////////////////////////////////////////////////////////////////////////
