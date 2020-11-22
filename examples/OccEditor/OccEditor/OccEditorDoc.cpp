// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// OccEditorDoc.cpp : COccEditorDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "OccEditor.h"
#endif

#include "OccEditorDoc.h"

#include <propkey.h>

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif

// COccEditorDoc

IMPLEMENT_DYNCREATE(COccEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(COccEditorDoc, CDocument)
END_MESSAGE_MAP()


// COccEditorDoc ����/����

COccEditorDoc::COccEditorDoc()
{
	// TODO: �ڴ����һ���Թ������

}

COccEditorDoc::~COccEditorDoc()
{
}

BOOL COccEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	InitOCC();
	

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}

#include "AIS_Trihedron.hxx"
#include "Geom_Axis2Placement.hxx"

BOOL COccEditorDoc::InitOCC()
{
	Handle(Graphic3d_GraphicDriver) aGraphicDriver = ((COccEditorApp*)AfxGetApp())->GetGraphicDriver();
	m_hViewer = new V3d_Viewer(aGraphicDriver); 
 
	m_hViewer->SetDefaultLights();
	m_hViewer->SetLightOn();
	//myViewer->SetDefaultBackgroundColor(Quantity_NOC_BLUE1);//�ı䱳����ɫ
 
	m_hAISContext =new AIS_InteractiveContext(m_hViewer);  //����һ�������ĵ�
	//m_hAISContext->DefaultDrawer()->UIsoAspect()->SetNumber(11);
	//m_hAISContext->DefaultDrawer()->VIsoAspect()->SetNumber(11);
 
	//��������ʵ�����ʾģʽ
	m_hAISContext->SetDisplayMode(AIS_Shaded,Standard_True);
	m_hAISContext->SetAutomaticHilight(Standard_False);

	//Handle(AIS_Trihedron) myTrihedron;
	//Handle(Geom_Axis2Placement) myTrihedronAxis=new Geom_Axis2Placement(gp::XOY());
	//myTrihedron=new AIS_Trihedron(myTrihedronAxis);
	//m_hAISContext->Display(myTrihedron,Standard_False);
	
	return TRUE;
}

// COccEditorDoc ���л�

void COccEditorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
	
}


#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void COccEditorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void COccEditorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void COccEditorDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// COccEditorDoc ���

#ifdef _DEBUG
void COccEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COccEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// COccEditorDoc ����
