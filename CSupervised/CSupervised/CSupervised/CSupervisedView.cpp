
// CSupervisedView.cpp : CCSupervisedView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "CSupervised.h"
#endif

#include "CSupervisedDoc.h"
#include "CSupervisedView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCSupervisedView

IMPLEMENT_DYNCREATE(CCSupervisedView, CView)

BEGIN_MESSAGE_MAP(CCSupervisedView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_Water, &CCSupervisedView::OnWater)
	ON_COMMAND(ID_Plant, &CCSupervisedView::OnPlant)
	ON_COMMAND(ID_City, &CCSupervisedView::OnCity)
	ON_COMMAND(ID_Road, &CCSupervisedView::OnRoad)
	ON_COMMAND(ID_Ground, &CCSupervisedView::OnGround)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_Calculate, &CCSupervisedView::OnCalculate)
	ON_COMMAND(ID_Supervised, &CCSupervisedView::OnSupervised)
END_MESSAGE_MAP()

// CCSupervisedView ����/����

CCSupervisedView::CCSupervisedView()
	: m_type(0)
{
	// TODO: �ڴ˴���ӹ������
	for (int i = 0; i < 5; i++)
	{
		type[i].b3 = type[i].b4 = type[i].b5 = 0;
	}
}

CCSupervisedView::~CCSupervisedView()
{
}

BOOL CCSupervisedView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CCSupervisedView ����

void CCSupervisedView::OnDraw(CDC* pDC)
{
	CCSupervisedDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
    Mat newImage;
	if (pDoc->img.channels() == 1)
	{
		cvtColor(pDoc->img, newImage, CV_GRAY2BGRA);
	}
	else if (pDoc->img.channels() == 3)
	{
		cvtColor(pDoc->img, newImage, CV_BGR2BGRA);
	}
	else
	{
		newImage = pDoc->img;
	}
	Gdiplus::Bitmap bitmap(newImage.cols, newImage.rows, newImage.step1(), PixelFormat32bppARGB, newImage.data);

	//Gdiplus::Bitmap bitmap(pDoc->img.cols, pDoc->img.rows, pDoc->img.step, //ÿһ�е��ֽ���
	//	PixelFormat24bppRGB, pDoc->img.data);
	Gdiplus::Graphics graphics(pDC->GetSafeHdc());
	graphics.DrawImage(&bitmap, 0, 0);
}


// CCSupervisedView ��ӡ

BOOL CCSupervisedView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CCSupervisedView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CCSupervisedView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CCSupervisedView ���

#ifdef _DEBUG
void CCSupervisedView::AssertValid() const
{
	CView::AssertValid();
}

void CCSupervisedView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCSupervisedDoc* CCSupervisedView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCSupervisedDoc)));
	return (CCSupervisedDoc*)m_pDocument;
}
#endif //_DEBUG


// CCSupervisedView ��Ϣ�������


void CCSupervisedView::OnWater()
{
	// TODO: �ڴ���������������
	m_type = 1;
}


void CCSupervisedView::OnPlant()
{
	// TODO: �ڴ���������������
	m_type = 2;
}


void CCSupervisedView::OnCity()
{
	// TODO: �ڴ���������������
	m_type = 3;
}


void CCSupervisedView::OnRoad()
{
	// TODO: �ڴ���������������
	m_type = 4;
}


void CCSupervisedView::OnGround()
{
	// TODO: �ڴ���������������
	m_type = 5;
}


void CCSupervisedView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	pts.push_back(point);

	CView::OnLButtonDown(nFlags, point);
}


void CCSupervisedView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CPoint tmp(pts[0].x, pts[0].y);
	CDC *pDC = GetDC();
	CPen NewPen, *pOldPen;
	NewPen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	pOldPen = pDC->SelectObject(&NewPen);
	pDC->MoveTo(tmp);
	FILE *fp = fopen("classes.txt", "a+");
	fprintf(fp, "%d\n", pts.size());
	for (int i = 0; i < pts.size(); i++)
	{
		fprintf(fp, "%d %d\n", pts[i].x, pts[i].y);
		pDC->LineTo(pts[(i + 1) % pts.size()]);
	}
	pts.clear();
	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();
	fclose(fp);
	CView::OnRButtonDown(nFlags, point);
}


void CCSupervisedView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CView::OnLButtonDblClk(nFlags, point);
}


void CCSupervisedView::OnCalculate()
{
	// TODO: �ڴ���������������
	Mat img = imread("band_345.bmp");
	Mat dst, roi = Mat::zeros(img.size(), CV_8U);
	vector<vector<cv::Point>> contour;
	vector<cv::Point> pt;
	int count, times = 0;
	cv::Point tmp;
	FILE *fp1 = fopen("classes.txt", "r");
	if (!fp1)
		return;
	while (!feof(fp1))
	{
		fscanf(fp1, "%d", &count);
		for (int i = 0; i < count; i++)
		{
			fscanf(fp1, "%d %d", &tmp.x, &tmp.y);
			pt.push_back(tmp);
		}
		contour.push_back(pt);
		drawContours(roi, contour, 0, Scalar::all(255), -1);
		contour.clear();
		pt.clear();
		times++;
		if (times == 2)
		{
			img.copyTo(dst, roi);
			roi = Mat::zeros(img.size(), CV_8U);
			double r = 0, g = 0, b = 0;
			int num = 0;
			for (int i = 0; i < dst.rows; i++)
			{
				for (int j = 0; j < dst.cols; j++)
				{
					if (dst.at<Vec3b>(i, j) != Vec3b(0, 0, 0))
					{
						num++;
						r = (double)(r*(num - 1) + dst.at<Vec3b>(i, j)[2]) / (double)(num);
						g = (double)(g*(num - 1) + dst.at<Vec3b>(i, j)[1]) / (double)(num);
						b = (double)(b*(num - 1) + dst.at<Vec3b>(i, j)[0]) / (double)(num);
					}
				}
			}
			FILE *fp = fopen("means.txt", "a+");
			fprintf(fp, "%.2lf %.2lf %.2lf\n", r, g, b);
			fclose(fp);
			times = 0;
			dst = Mat::zeros(img.size(), CV_8UC3);
		}
	}
}


void CCSupervisedView::OnSupervised()
{
	// TODO: �ڴ���������������
	Mat img = imread("band_345.bmp");
	Mat classified;
	classified.create(img.size(), CV_8UC3);
	FILE *fp = fopen("means.txt", "r");
	int i = 0;
	while (!feof(fp))
	{
		fscanf(fp, "%lf %lf %lf", &type[i].b3, &type[i].b4, &type[i].b5);
		i++;
	}
	fclose(fp);

	int idx;
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			idx = CountDist(i, j);
			switch (idx)
			{
			case 0:
				classified.at<Vec3b>(i, j) = Vec3b(255, 0, 0);
				break;
			case 1:
				classified.at<Vec3b>(i, j) = Vec3b(0, 255, 0);
				break;
			case 2:
				classified.at<Vec3b>(i, j) = Vec3b(0, 255, 255);
				break;
			case 3:
				classified.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
				break;
			case 4:
				classified.at<Vec3b>(i, j) = Vec3b(45, 82, 160);
				break;
			}
		}
	}
	imwrite("Classified.bmp", classified);
}


int CCSupervisedView::CountDist(int x, int y)
{
	double b3, b4, b5;
	double dist[5], min = 100000;
	double d3, d4, d5;
	Mat img = imread("band_345.bmp");
	int idx = -1;
	b3 = img.at<Vec3b>(x, y)[2];
	b4 = img.at<Vec3b>(x, y)[1];
	b5 = img.at<Vec3b>(x, y)[0];
	for (int i = 0; i < 5; i++)
	{
		d3 = b3 - type[i].b3; 
		d4 = b4 - type[i].b4;
		d5 = b5 - type[i].b5;
		dist[i] = pow(d3, 2) + pow(d4, 2) + pow(d5, 2);
		if (dist[i] < min)
		{
			min = dist[i];
			idx = i;
		}
	}
	return idx;
}
