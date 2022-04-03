// RVWeightsDlg.cpp : implementation file
//

#include "StdMain.h"
#include <afxwin.h>
#include "resource.h"
#include "LegoOmni.h"
#include "RVWeightsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// ??? defined in realtime.cpp
extern double SIZE_WEIGHT;       
extern double ACCURACY_WEIGHT;   
extern double SEMANTIC_WEIGHT;   
extern double FOCUS_WEIGHT;      
extern double MOTION_WEIGHT;     
extern double HYSTERESIS_WEIGHT;

double* g_pWeights[] = 
{
    &SIZE_WEIGHT,
    &ACCURACY_WEIGHT,
    &SEMANTIC_WEIGHT,
    &FOCUS_WEIGHT,
    &MOTION_WEIGHT,
    &HYSTERESIS_WEIGHT,
};

const char* g_pWeightsName[] =
{
    "Size",
    "Accuracy",
    "Semantic",
    "Focus",
    "Motion",
    "Hysteresis"
};

/////////////////////////////////////////////////////////////////////////////
// CRVWeightsDlg dialog


CRVWeightsDlg::CRVWeightsDlg(CWnd* pParent /*=NULL*/)
	: m_pWeights(g_pWeights), CDialog(CRVWeightsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRVWeightsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CRVWeightsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRVWeightsDlg)
	DDX_Control(pDX, IDC_SENSITIVITY_TEXT, m_sensitivityText);
	DDX_Control(pDX, IDC_SENSITIVITY, m_sensitivity);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRVWeightsDlg, CDialog)
	//{{AFX_MSG_MAP(CRVWeightsDlg)
	ON_WM_VSCROLL()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// ???
int power10(int n)
{
    // returns 10 to the power of n
    int i;
    int value;

    for (i = 0, value = 1; i < n; i++)
    {
        assert(value < ((INT_MAX / 10) + 1));
        value *= 10;
    }
    return value;
}

void CRVWeightsDlg::SetValueFromSliderPos(int index, int sliderPos)
{
    int sensitivity = m_sensitivity.GetPos();
    int maxValue = power10(sensitivity);

    *m_pWeights[index] = (maxValue - sliderPos) / (double) maxValue;
}

int CRVWeightsDlg::GetSliderPosForValue(int index)
{
    int sensitivity = m_sensitivity.GetPos();
    int maxValue = power10(sensitivity);

    return maxValue - (int) (maxValue * (*m_pWeights[index]));
}

void CRVWeightsDlg::GetTextForValue(int index, CString& text)
{
    double  value = *m_pWeights[index];

    text.Format("%.4f", value);
}

void CRVWeightsDlg::GetTextForSensitivity(CString& text)
{
    int sensitivity = m_sensitivity.GetPos();
    int maxValue = power10(sensitivity);

    text.Format("1/%d", maxValue);
}


void CRVWeightsDlg::ConfigureSliders()
{
    int     sensitivity = m_sensitivity.GetPos();
    int     minValue = 0;
    int     maxValue = power10(sensitivity);
    int     tickFreq = (maxValue / 10);
    int     ctrlID;

    for (ctrlID = IDC_WEIGHT_SIZE; ctrlID <= IDC_WEIGHT_HYSTERESIS; ctrlID++)
    {
        CSliderCtrl*    pSlider = (CSliderCtrl*) GetDlgItem(ctrlID);
        int             index = ctrlID - IDC_WEIGHT_SIZE;

	    pSlider->SetRange(minValue, maxValue);
	    pSlider->SetTicFreq(tickFreq);
	    pSlider->SetPos(GetSliderPosForValue(index));
        pSlider->SetPageSize(1);
        UpdateValueText(index);
    }
}

/////////////////////////////////////////////////////////////////////////////
// CRVWeightsDlg message handlers

const int maxSensitivity = 4;

BOOL CRVWeightsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    int currentSensitivity = 1;

    m_sensitivity.SetRange(1, maxSensitivity);
    m_sensitivity.SetBase(10);
    m_sensitivity.SetPos(currentSensitivity);

    UpdateSensitivityText();
    ConfigureSliders();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRVWeightsDlg::UpdateValueText(int index) 
{
    CStatic*    pStatic = (CStatic*) GetDlgItem(IDC_STATIC_WEIGHT_SIZE + index);
    CString     text;

    GetTextForValue(index, text);
	pStatic->SetWindowText(text);
}

void CRVWeightsDlg::UpdateSensitivityText() 
{
    CString     sensitivityText;

    GetTextForSensitivity(sensitivityText);
	m_sensitivityText.SetWindowText(sensitivityText);
}

void CRVWeightsDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
    if (pScrollBar->IsKindOf(RUNTIME_CLASS(CSpinButtonCtrl)))
    {
        UpdateSensitivityText();
        ConfigureSliders();
    }
    else
    {
        CSliderCtrl*    pSlider = (CSliderCtrl*) (CWnd*) pScrollBar;
        int             index = pSlider->GetDlgCtrlID() - IDC_WEIGHT_SIZE;

        SetValueFromSliderPos(index, pSlider->GetPos());
        UpdateValueText(index);
    }

    CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CRVWeightsDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
    SaveWeightsToRegistry();
    ShowWindow(SW_HIDE);
}

void CRVWeightsDlg::SaveWeightsToRegistry()
{
    int weight;
    int ctrlID;

    for (ctrlID = IDC_WEIGHT_SIZE; ctrlID <= IDC_WEIGHT_HYSTERESIS; ctrlID++)
    {
        weight = (int) (*m_pWeights[ctrlID - IDC_WEIGHT_SIZE] * power10(maxSensitivity));
        AfxGetApp()->WriteProfileInt("Realtime View Weights",
                                     g_pWeightsName[ctrlID - IDC_WEIGHT_SIZE],
                                     weight);
    }
}

void CRVWeightsDlg::LoadWeightsFromRegistry()
{
    int ctrlID;

    for (ctrlID = IDC_WEIGHT_SIZE; ctrlID <= IDC_WEIGHT_HYSTERESIS; ctrlID++)
    {
        int weight;

        weight = (int) AfxGetApp()->GetProfileInt("Realtime View Weights",
                                                  g_pWeightsName[ctrlID - IDC_WEIGHT_SIZE],
                                                  INT_MAX);

        if (weight != INT_MAX)
        {
            *m_pWeights[ctrlID - IDC_WEIGHT_SIZE] = weight / (double) power10(maxSensitivity);  
        }
    }
}

void CRVWeightsDlg::OnButton1() 
{
    int ctrlID;

    LoadWeightsFromRegistry();

    for (ctrlID = IDC_WEIGHT_SIZE; ctrlID <= IDC_WEIGHT_HYSTERESIS; ctrlID++)
    {
        CSliderCtrl*    pSlider = (CSliderCtrl*) GetDlgItem(ctrlID);
        int             index = ctrlID - IDC_WEIGHT_SIZE;

	    pSlider->SetPos(GetSliderPosForValue(index));
        UpdateValueText(index);
    }
}
