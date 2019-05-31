
// CSupervisedView.h : CCSupervisedView ��Ľӿ�
//
#include <vector>
using namespace std;
#pragma once
typedef struct types {
	double b3, b4, b5;
}types;

class CCSupervisedView : public CView
{
protected: // �������л�����
	CCSupervisedView();
	DECLARE_DYNCREATE(CCSupervisedView)

// ����
public:
	CCSupervisedDoc* GetDocument() const;

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
	virtual ~CCSupervisedView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	int m_type;
	types type[5];
	vector<CPoint> pts;
	afx_msg void OnWater();
	afx_msg void OnPlant();
	afx_msg void OnCity();
	afx_msg void OnRoad();
	afx_msg void OnGround();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnCalculate();
	afx_msg void OnSupervised();
	int CountDist(int x, int y);
};

#ifndef _DEBUG  // CSupervisedView.cpp �еĵ��԰汾
inline CCSupervisedDoc* CCSupervisedView::GetDocument() const
   { return reinterpret_cast<CCSupervisedDoc*>(m_pDocument); }
#endif

