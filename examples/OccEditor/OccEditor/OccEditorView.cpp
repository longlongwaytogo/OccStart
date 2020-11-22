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

// OccEditorView.cpp : COccEditorView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "OccEditor.h"
#endif

#include "OccEditorDoc.h"
#include "OccEditorView.h"

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif


// COccEditorView

IMPLEMENT_DYNCREATE(COccEditorView, CView)

BEGIN_MESSAGE_MAP(COccEditorView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COccEditorView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_SPHERE, &COccEditorView::OnSphere)
	ON_WM_SIZE()
END_MESSAGE_MAP()

// COccEditorView ����/����

COccEditorView::COccEditorView()
{
	// TODO: �ڴ˴���ӹ������

}

COccEditorView::~COccEditorView()
{
}

BOOL COccEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// COccEditorView ����

void COccEditorView::OnDraw(CDC* /*pDC*/)
{
	COccEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if(m_hView)
	{
		//m_hView->MustBeResized();
		m_hView->Update(); 
		m_hView->Redraw();
	}

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}

#include <BRepPrimAPI_MakeSphere.hxx> 
#include <TopoDS_Shape.hxx>

void COccEditorView::DrawSphere(float radius)
{
	BRepPrimAPI_MakeSphere mkSphere(radius);
	TopoDS_Shape Sphere = mkSphere.Shape();
	Handle(AIS_Shape) myAISSphere = new AIS_Shape(Sphere);
	GetDocument()->GetAISContext()->Display(myAISSphere, Standard_False);
	
	FitAll();
}


void COccEditorView::FitAll() 
{ 
	if (!m_hView.IsNull()) 
		m_hView->FitAll();
	m_hView->ZFitAll();
}

// COccEditorView ��ӡ


void COccEditorView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL COccEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void COccEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void COccEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void COccEditorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void COccEditorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// COccEditorView ���

#ifdef _DEBUG
void COccEditorView::AssertValid() const
{
	CView::AssertValid();
}

void COccEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COccEditorDoc* COccEditorView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COccEditorDoc)));
	return (COccEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// COccEditorView ��Ϣ�������


void COccEditorView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	m_bHlrModeIsOn  = Standard_False;
	m_hView = GetDocument()->GetViewer()->CreateView();
	m_hView->SetComputedMode(m_bHlrModeIsOn);
	Handle(Graphic3d_GraphicDriver) graphicDriver = ((COccEditorApp*)AfxGetApp())->GetGraphicDriver();
 
	Handle(WNT_Window) hWntWindow = new WNT_Window(GetSafeHwnd());
	m_hView->SetWindow(hWntWindow);
	if (!hWntWindow->IsMapped()) {
		hWntWindow->Map();
	}
	hWntWindow->SetBackground(Quantity_NOC_SLATEBLUE2);

	//Standard_Integer w = 100;

	//Standard_Integer h = 100;
	//hWntWindow->Size(w, h);
//	::PostMessage(GetSafeHwnd(), WM_SIZE, SIZE_RESTORED, w + h * 65536);

	FitAll();
	// ����OpenCaseCade������
	m_hView->ZBufferTriedronSetup(Quantity_NOC_RED, Quantity_NOC_GREEN, Quantity_NOC_BLUE1, 0.8, 0.05, 12);
	m_hView->TriedronDisplay(Aspect_TOTP_LEFT_LOWER, Quantity_NOC_WHITE, 0.2, V3d_ZBUFFER);
	 
	

	// TODO: �ڴ����ר�ô����/����û���
}


void COccEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CView::OnMouseMove(nFlags, point);

    if(nFlags && MK_LBUTTON){ 
    //myView->Rotate(point.x,point.y); 
    m_hView->Rotation(point.x,point.y); 
	//m_hView->Update();
    } 

}


void COccEditorView::OnSphere()
{
	// TODO: �ڴ���������������
	DrawSphere(6);
}


void COccEditorView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	if(m_hView)
		m_hView->MustBeResized();
	// TODO: �ڴ˴������Ϣ����������
}
