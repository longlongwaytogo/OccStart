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

// OccEditorView.h : COccEditorView ��Ľӿ�
//

#pragma once


class COccEditorView : public CView
{
protected: // �������л�����
	COccEditorView();
	DECLARE_DYNCREATE(COccEditorView)

// ����
public:
	COccEditorDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~COccEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // OccEditorView.cpp �еĵ��԰汾
inline COccEditorDoc* COccEditorView::GetDocument() const
   { return reinterpret_cast<COccEditorDoc*>(m_pDocument); }
#endif

