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

// OccEditorView.h : COccEditorView 类的接口
//

#pragma once


class COccEditorView : public CView
{
protected: // 仅从序列化创建
	COccEditorView();
	DECLARE_DYNCREATE(COccEditorView)

// 特性
public:
	COccEditorDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~COccEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

	void Display();
private:
	Handle_V3d_View m_hView;
	Standard_Boolean m_bHlrModeIsOn;
	
public:	
	virtual void OnInitialUpdate();
	void FitAll();
	void DrawSphere(float radius = 1);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSphere();
};

#ifndef _DEBUG  // OccEditorView.cpp 中的调试版本
inline COccEditorDoc* COccEditorView::GetDocument() const
   { return reinterpret_cast<COccEditorDoc*>(m_pDocument); }
#endif

