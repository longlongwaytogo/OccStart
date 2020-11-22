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

// OccEditorDoc.cpp : COccEditorDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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


// COccEditorDoc 构造/析构

COccEditorDoc::COccEditorDoc()
{
	// TODO: 在此添加一次性构造代码

}

COccEditorDoc::~COccEditorDoc()
{
}

BOOL COccEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	InitOCC();
	

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

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
	//myViewer->SetDefaultBackgroundColor(Quantity_NOC_BLUE1);//改变背景颜色
 
	m_hAISContext =new AIS_InteractiveContext(m_hViewer);  //创建一个交互文档
	//m_hAISContext->DefaultDrawer()->UIsoAspect()->SetNumber(11);
	//m_hAISContext->DefaultDrawer()->VIsoAspect()->SetNumber(11);
 
	//这里设置实体的显示模式
	m_hAISContext->SetDisplayMode(AIS_Shaded,Standard_True);
	m_hAISContext->SetAutomaticHilight(Standard_False);

	//Handle(AIS_Trihedron) myTrihedron;
	//Handle(Geom_Axis2Placement) myTrihedronAxis=new Geom_Axis2Placement(gp::XOY());
	//myTrihedron=new AIS_Trihedron(myTrihedronAxis);
	//m_hAISContext->Display(myTrihedron,Standard_False);
	
	return TRUE;
}

// COccEditorDoc 序列化

void COccEditorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
	
}


#ifdef SHARED_HANDLERS

// 缩略图的支持
void COccEditorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
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

// 搜索处理程序的支持
void COccEditorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
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

// COccEditorDoc 诊断

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


// COccEditorDoc 命令
