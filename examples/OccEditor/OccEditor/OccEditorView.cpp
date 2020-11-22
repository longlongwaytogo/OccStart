// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// OccEditorView.cpp : COccEditorView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COccEditorView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_SPHERE, &COccEditorView::OnSphere)
	ON_WM_SIZE()
END_MESSAGE_MAP()

// COccEditorView 构造/析构

COccEditorView::COccEditorView()
{
	// TODO: 在此处添加构造代码

}

COccEditorView::~COccEditorView()
{
}

BOOL COccEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// COccEditorView 绘制

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

	// TODO: 在此处为本机数据添加绘制代码
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

// COccEditorView 打印


void COccEditorView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL COccEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void COccEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void COccEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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


// COccEditorView 诊断

#ifdef _DEBUG
void COccEditorView::AssertValid() const
{
	CView::AssertValid();
}

void COccEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COccEditorDoc* COccEditorView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COccEditorDoc)));
	return (COccEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// COccEditorView 消息处理程序


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
	// 构建OpenCaseCade坐标轴
	m_hView->ZBufferTriedronSetup(Quantity_NOC_RED, Quantity_NOC_GREEN, Quantity_NOC_BLUE1, 0.8, 0.05, 12);
	m_hView->TriedronDisplay(Aspect_TOTP_LEFT_LOWER, Quantity_NOC_WHITE, 0.2, V3d_ZBUFFER);
	 
	

	// TODO: 在此添加专用代码和/或调用基类
}


void COccEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CView::OnMouseMove(nFlags, point);

    if(nFlags && MK_LBUTTON){ 
    //myView->Rotate(point.x,point.y); 
    m_hView->Rotation(point.x,point.y); 
	//m_hView->Update();
    } 

}


void COccEditorView::OnSphere()
{
	// TODO: 在此添加命令处理程序代码
	DrawSphere(6);
}


void COccEditorView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	if(m_hView)
		m_hView->MustBeResized();
	// TODO: 在此处添加消息处理程序代码
}
