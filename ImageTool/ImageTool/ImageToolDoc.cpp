
// ImageToolDoc.cpp : CImageToolDoc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "ImageTool.h"
#endif

#include "ImageToolDoc.h"
#include "FileNewDlg.h"
#include <propkey.h>

#include "DibEnhancement.h"
#include "DibFilter.h"
#include "BrightnessDlg.h"
#include "ContrastDlg.h"
#include "GammaCorrectionDlg.h"
#include "HistogramDlg.h"
#include "ArithmeticDlg.h"
#include "GaussianDlg.h"
#include "AddNoiseDlg.h"
#include "DiffusionDlg.h"
#include "DibGeometry.h"
#include "TranslateDlg.h"
#include "ResizeDlg.h"
#include "DibRotate.h"
#include "RotateDlg.h"
#include "DibFourier.h"
#include "FreqFilterDlg.h"
#include "HarrisDlg.h"
#include "DibColor.h"
#include "ColorCombineDlg.h"
#include "DibSegment.h"
#include "BinarizationDlg.h"
#include "FourierDescDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageToolDoc

IMPLEMENT_DYNCREATE(CImageToolDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageToolDoc, CDocument)
  ON_COMMAND(ID_WINDOW_DUPLICATE, &CImageToolDoc::OnWindowDuplicate)
  ON_COMMAND(ID_EDIT_COPY, &CImageToolDoc::OnEditCopy)
  ON_COMMAND(ID_IMAGE_INVERSE, &CImageToolDoc::OnImageInverse)
  ON_COMMAND(ID_IMAGE_BRIGHTNESS, &CImageToolDoc::OnImageBrightness)
  ON_COMMAND(ID_IMAGE_CONTRAST, &CImageToolDoc::OnImageContrast)
  ON_COMMAND(ID_GAMMA_CORRECTION, &CImageToolDoc::OnGammaCorrection)
  ON_COMMAND(ID_VIEW_HISTOGRAM, &CImageToolDoc::OnViewHistogram)
  ON_COMMAND(ID_HISTO_EQUALIZE, &CImageToolDoc::OnHistoEqualize)
  ON_COMMAND(ID_IMAGE_ARITHMETIC, &CImageToolDoc::OnImageArithmetic)
  ON_COMMAND(ID_BITPLANE_SLICING, &CImageToolDoc::OnBitplaneSlicing)
  ON_COMMAND(ID_FILTER_MEAN, &CImageToolDoc::OnFilterMean)
  ON_COMMAND(ID_FILTER_WEIGHTED_MEAN, &CImageToolDoc::OnFilterWeightedMean)
  ON_COMMAND(ID_FILTER_GAUSSIAN, &CImageToolDoc::OnFilterGaussian)
  ON_COMMAND(ID_FILTER_LAPLACIAN, &CImageToolDoc::OnFilterLaplacian)
  ON_COMMAND(ID_FILTER_UNSHARP_MASK, &CImageToolDoc::OnFilterUnsharpMask)
  ON_COMMAND(ID_ADD_NOISE, &CImageToolDoc::OnAddNoise)
  ON_COMMAND(ID_FILTER_MEDIAN, &CImageToolDoc::OnFilterMedian)
  ON_COMMAND(ID_FILTER_DIFFUSION, &CImageToolDoc::OnFilterDiffusion)
  ON_COMMAND(ID_IMAGE_TRANSLATION, &CImageToolDoc::OnImageTranslation)
  ON_COMMAND(ID_IMAGE_RESIZE, &CImageToolDoc::OnImageResize)
  ON_COMMAND(ID_IMAGE_ROTATE, &CImageToolDoc::OnImageRotate)
  ON_COMMAND(ID_IMAGE_MIRROR, &CImageToolDoc::OnImageMirror)
  ON_COMMAND(ID_IMAGE_FLIP, &CImageToolDoc::OnImageFlip)
  ON_COMMAND(ID_FOURIER_DFT, &CImageToolDoc::OnFourierDft)
  ON_COMMAND(ID_FOURIER_DFTRC, &CImageToolDoc::OnFourierDftrc)
  ON_COMMAND(ID_FOURIER_FFT, &CImageToolDoc::OnFourierFft)
  ON_COMMAND(ID_IDEAL_LOWPASS, &CImageToolDoc::OnIdealLowpass)
  ON_COMMAND(ID_IDEAL_HIGHPASS, &CImageToolDoc::OnIdealHighpass)
  ON_COMMAND(ID_GAUSSIAN_LOWPASS, &CImageToolDoc::OnGaussianLowpass)
  ON_COMMAND(ID_GAUSSIAN_HIGHPASS, &CImageToolDoc::OnGaussianHighpass)
  ON_COMMAND(ID_EDGE_ROBERTS, &CImageToolDoc::OnEdgeRoberts)
  ON_COMMAND(ID_EDGE_PREWITT, &CImageToolDoc::OnEdgePrewitt)
  ON_COMMAND(ID_EDGE_SOBEL, &CImageToolDoc::OnEdgeSobel)
  ON_COMMAND(ID_HOUGH_LINE, &CImageToolDoc::OnHoughLine)
  ON_COMMAND(ID_HARRIS_CORNER, &CImageToolDoc::OnHarrisCorner)
  ON_COMMAND(ID_COLOR_GRAYSCALE, &CImageToolDoc::OnColorGrayscale)
  ON_UPDATE_COMMAND_UI(ID_COLOR_GRAYSCALE, &CImageToolDoc::OnUpdateColorGrayscale)
  ON_COMMAND(ID_COLOR_SPLIT_RGB, &CImageToolDoc::OnColorSplitRgb)
  ON_UPDATE_COMMAND_UI(ID_COLOR_SPLIT_RGB, &CImageToolDoc::OnUpdateColorSplitRgb)
  ON_COMMAND(ID_COLOR_SPLIT_HSI, &CImageToolDoc::OnColorSplitHsi)
  ON_UPDATE_COMMAND_UI(ID_COLOR_SPLIT_HSI, &CImageToolDoc::OnUpdateColorSplitHsi)
  ON_COMMAND(ID_COLOR_SPLIT_YUV, &CImageToolDoc::OnColorSplitYuv)
  ON_UPDATE_COMMAND_UI(ID_COLOR_SPLIT_YUV, &CImageToolDoc::OnUpdateColorSplitYuv)
  ON_COMMAND(ID_COLOR_COMBINE_RGB, &CImageToolDoc::OnColorCombineRgb)
  ON_COMMAND(ID_COLOR_COMBINE_HSI, &CImageToolDoc::OnColorCombineHsi)
  ON_COMMAND(ID_COLOR_COMBINE_YUV, &CImageToolDoc::OnColorCombineYuv)
  ON_COMMAND(ID_COLOR_EDGE, &CImageToolDoc::OnColorEdge)
  ON_UPDATE_COMMAND_UI(ID_COLOR_EDGE, &CImageToolDoc::OnUpdateColorEdge)
  ON_COMMAND(ID_COLOR_EQUALIZE, &CImageToolDoc::OnColorEqualize)
  ON_UPDATE_COMMAND_UI(ID_COLOR_EQUALIZE, &CImageToolDoc::OnUpdateColorEqualize)
  ON_COMMAND(ID_SEGMENT_BINARIZATION, &CImageToolDoc::OnSegmentBinarization)
  ON_COMMAND(ID_SEGMENT_ITERATIVE, &CImageToolDoc::OnSegmentIterative)
  ON_COMMAND(ID_SEGMENT_LABELING, &CImageToolDoc::OnSegmentLabeling)
  ON_COMMAND(ID_CONTOUR_TRACING, &CImageToolDoc::OnContourTracing)
  ON_COMMAND(ID_MORPHOLOGY_EROSION, &CImageToolDoc::OnMorphologyErosion)
  ON_COMMAND(ID_MORPHOLOGY_DILATION, &CImageToolDoc::OnMorphologyDilation)
  ON_COMMAND(ID_MORPHOLOGY_OPENING, &CImageToolDoc::OnMorphologyOpening)
  ON_COMMAND(ID_MORPHOLOGY_CLOSING, &CImageToolDoc::OnMorphologyClosing)
  ON_COMMAND(ID_GRAYMORPH_EROSION, &CImageToolDoc::OnGraymorphErosion)
  ON_COMMAND(ID_GRAYMORPH_DILATION, &CImageToolDoc::OnGraymorphDilation)
  ON_COMMAND(ID_GRAYMORPH_OPENING, &CImageToolDoc::OnGraymorphOpening)
  ON_COMMAND(ID_GRAYMORPH_CLOSING, &CImageToolDoc::OnGraymorphClosing)
  ON_COMMAND(ID_FOURIER_DESCRIPTOR, &CImageToolDoc::OnFourierDescriptor)
  ON_COMMAND(ID_INVARIANT_MOMENTS, &CImageToolDoc::OnInvariantMoments)
  ON_COMMAND(ID_FILE_NEW, &CImageToolDoc::OnFileNew)
END_MESSAGE_MAP()


// CImageToolDoc ����/�Ҹ�

CImageToolDoc::CImageToolDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CImageToolDoc::~CImageToolDoc()
{
}

BOOL CImageToolDoc::OnNewDocument()
{
	//if (!CDocument::OnNewDocument())
	//	return FALSE;

	//// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	//// SDI ������ �� ������ �ٽ� ����մϴ�.

	//return TRUE;



  ////////�����ϴ����̾��� å�����Ұ�
  if (!CDocument::OnNewDocument())
  	return FALSE;


  BOOL bSuccess = TRUE;

  if (theApp.m_pNewDib == NULL)
  {


    CFileNewDlg dlg;
    if (dlg.DoModal() == IDOK)
    {
      switch (dlg.m_nType)
      {
      case 0:
        bSuccess = m_Dib.CreateGrayImage(dlg.m_nWidth, dlg.m_nHeight);
        break;
      case 1:
        bSuccess = m_Dib.CreateRGBImage(dlg.m_nWidth, dlg.m_nHeight);
        break;
      default:
        break;
      }
    }
    else
    {
      bSuccess = FALSE;
    }
  }
  else
  {
    m_Dib.Copy(theApp.m_pNewDib);
    theApp.m_pNewDib = NULL;
  }

  return bSuccess;
}




// CImageToolDoc serialization

void CImageToolDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CImageToolDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
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

// �˻� ó���⸦ �����մϴ�.
void CImageToolDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageToolDoc::SetSearchContent(const CString& value)
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

// CImageToolDoc ����

#ifdef _DEBUG
void CImageToolDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageToolDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageToolDoc ���


BOOL CImageToolDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
  if (!CDocument::OnOpenDocument(lpszPathName))
    return FALSE;

  // TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
  //return TRUE;


  return m_Dib.Load(lpszPathName);
}


BOOL CImageToolDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
  // TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
  //return CDocument::OnSaveDocument(lpszPathName);

  return m_Dib.Save(lpszPathName);
}


void CImageToolDoc::OnWindowDuplicate()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  AfxNewImage(m_Dib);
}


void CImageToolDoc::OnEditCopy()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  if (m_Dib.IsValid())
  {
    m_Dib.CopyToClipboard();
  }
}


void CImageToolDoc::OnImageInverse()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CDib dib = m_Dib;
  DibInverse(dib);
  AfxNewImage(dib);
}


void CImageToolDoc::OnImageBrightness()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CBrightnessDlg dlg;
  if (dlg.DoModal() == IDOK)
  {
    CDib dib = m_Dib;
    DibBrightness(dib, dlg.m_nBrightness);
    AfxNewImage(dib);
  }
}


void CImageToolDoc::OnImageContrast()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CContrastDlg dlg;
  if (dlg.DoModal() == IDOK)
  {
    CDib dib = m_Dib;
    DibBrightness(dib, dlg.m_nContrast);
    AfxNewImage(dib);
  }
}


void CImageToolDoc::OnGammaCorrection()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CGammaCorrectionDlg dlg;
  if (dlg.DoModal() == IDOK)
  {
    CDib dib = m_Dib;
    DibGammaCorrection(dib, dlg.m_fGamma);
    AfxNewImage(dib);
  }
}


void CImageToolDoc::OnViewHistogram()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CHistogramDlg dlg;
  dlg.SetImage(m_Dib);
  dlg.DoModal();
}


void CImageToolDoc::OnHistoEqualize()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CDib dib = m_Dib;
  DibHistEqual(dib);
  AfxNewImage(dib);
}


void CImageToolDoc::OnImageArithmetic()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CArithmeticDlg dlg;
  if (dlg.DoModal() == IDOK)
  {
    CImageToolDoc *pDoc1 = (CImageToolDoc*)dlg.m_pDoc1;
    CImageToolDoc *pDoc2 = (CImageToolDoc*)dlg.m_pDoc2;

    CDib dib;
    BOOL result = FALSE;

    switch (dlg.m_nOption)
    {
    case 0:
      result = DibAdd(pDoc1->m_Dib, pDoc2->m_Dib, dib);
      break;
    case 1:
      result = DibSub(pDoc1->m_Dib, pDoc2->m_Dib, dib);
      break;
    case 2:
      result = DibAve(pDoc1->m_Dib, pDoc2->m_Dib, dib);
      break;
    case 3:
      result = DibDif(pDoc1->m_Dib, pDoc2->m_Dib, dib);
      break;
    case 4:
      result = DibAND(pDoc1->m_Dib, pDoc2->m_Dib, dib);
      break;
    case 5:
      result = DibOR(pDoc1->m_Dib, pDoc2->m_Dib, dib);
      break;
    default:
      break;
    }

    if (result)
    {
      AfxNewImage(dib);
    }
    else
    {
      AfxMessageBox(TEXT("Image size is different!"));
    }
  }
}


void CImageToolDoc::OnBitplaneSlicing()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  int w = m_Dib.GetWidth();
  int h = m_Dib.GetHeight();

  CDib dib;
  dib.CreateGrayImage(w, h);
  for (register int i = 0; i < 8; i++)
  {
    DibBitPlane(m_Dib, i, dib);
    AfxNewImage(dib);
  }
}


void CImageToolDoc::OnFilterMean()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CDib dib = m_Dib;
  DibFilterMean(dib);
  AfxNewImage(dib);
}


void CImageToolDoc::OnFilterWeightedMean()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CDib dib = m_Dib;
  DibFilterWeightedMean(dib);
  AfxNewImage(dib);
}


void CImageToolDoc::OnFilterGaussian()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CGaussianDlg dlg;
  if (dlg.DoModal() == IDOK)
  {
    CDib dib = m_Dib;
    DibFilterGaussian(dib, dlg.m_fSigma);
    AfxNewImage(dib);
  }
}


void CImageToolDoc::OnFilterLaplacian()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CDib dib = m_Dib;
  DibFilterLaplacian(dib);
  AfxNewImage(dib);
}


void CImageToolDoc::OnFilterUnsharpMask()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CDib dib = m_Dib;
  DibFilterUnsharpMask(dib);
  AfxNewImage(dib);
}


void CImageToolDoc::OnAddNoise()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CAddNoiseDlg dlg;
  if (dlg.DoModal() == IDOK)
  {
    CDib dib = m_Dib;
    switch (dlg.m_nNoiseType)
    {
    case 0:
      DibNoiseGaussian(dib, dlg.m_nAmount);
      break;
    case 1:
      DibNoiseSaltNPepper(dib, dlg.m_nAmount);
      break;
    default:
      break;
    }
    AfxNewImage(dib);
  }
}


void CImageToolDoc::OnFilterMedian()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CDib dib = m_Dib;
  DibFilterMedian(dib);
  AfxNewImage(dib);
}


void CImageToolDoc::OnFilterDiffusion()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CDiffusionDlg dlg;
  if (dlg.DoModal() == IDOK)
  {
    CDib dib = m_Dib;
    DibFilterDiffusion(dib, dlg.m_fLambda, dlg.m_fK, dlg.m_nIteration);
    AfxNewImage(dib);
  }
}


void CImageToolDoc::OnImageTranslation()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CTranslateDlg dlg;
  if (dlg.DoModal() == IDOK)
  {
    CDib dib = m_Dib;
    DibTranslate(dib, dlg.m_nNewSX, dlg.m_nNewSY);
    AfxNewImage(dib);
  }
}


void CImageToolDoc::OnImageResize()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CResizeDlg dlg;
  dlg.m_nOldWidth = m_Dib.GetWidth();
  dlg.m_nOldHeight = m_Dib.GetHeight();
  if (dlg.DoModal() == IDOK)
  {
    CDib dib = m_Dib;
    switch (dlg.m_nInterpolation)
    {
    case 0:
      DibResizeNearest(dib, dlg.m_nNewWidth, dlg.m_nNewHeight);
      break;
    case 1:
      DibResizeBilinear(dib, dlg.m_nNewWidth, dlg.m_nNewHeight);
      break;
    case 2:
      DibResizeCubic(dib, dlg.m_nNewWidth, dlg.m_nNewHeight);
      break;
    default:
      break;
    }
    AfxNewImage(dib);
  }
}



void CImageToolDoc::OnImageRotate()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CRotateDlg dlg;
  if (dlg.DoModal() == IDOK)
  {
    CDib dib = m_Dib;
    switch (dlg.m_nRotate)
    {
    case 0:
      DibRotate90(dib);
      break;
    case 1:
      DibRotate180(dib);
      break;
    case 2:
      DibRotate270(dib);
      break;
    case 3:
      DibRotate(dib, dlg.m_fAngle);
      break;
    default:
      break;
    }
    AfxNewImage(dib);
  }
}


void CImageToolDoc::OnImageMirror()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CDib dib = m_Dib;
  DibMirror(dib);
  AfxNewImage(dib);
}


void CImageToolDoc::OnImageFlip()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CDib dib = m_Dib;
  DibFlip(dib);
  AfxNewImage(dib);
}


void CImageToolDoc::OnFourierDft()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  int w = m_Dib.GetWidth();
  int h = m_Dib.GetHeight();

  if (w * h > 128 * 128)
  {
    CString str = TEXT("������ ũ�Ⱑ Ŀ�� �ð��� ���� ���� �� �ֽ��ϴ�.\nAre you continu?");
    if (AfxMessageBox(str, MB_OKCANCEL) != IDOK)
    {
      return;
    }
  }

  CDibFourier fourier;
  fourier.SetImage(m_Dib);
  fourier.DFT(1);

  CDib dib;
  fourier.GetSpectrumImage(dib);
  AfxNewImage(dib);

  fourier.GetPhaseImage(dib);
  AfxNewImage(dib);

  fourier.DFT(-1);
  fourier.GetImage(dib);
  AfxNewImage(dib);
}


void CImageToolDoc::OnFourierDftrc()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CDibFourier fourier;
  fourier.SetImage(m_Dib);
  fourier.DFTRC(1);

  CDib dib;
  fourier.GetSpectrumImage(dib);
  AfxNewImage(dib);

  fourier.GetPhaseImage(dib);
  AfxNewImage(dib);

  fourier.DFTRC(-1);
  fourier.GetImage(dib);
  AfxNewImage(dib);
}


void CImageToolDoc::OnFourierFft()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  int w = m_Dib.GetWidth();
  int h = m_Dib.GetHeight();

  if (!IsPowerOf2(w) || !IsPowerOf2(h))
  {
    AfxMessageBox(TEXT("���� �Ǵ� ������ ũ�Ⱑ 2�� �¼��� �ƴմϴ�."));
    return;
  }

  CDibFourier fourier;
  fourier.SetImage(m_Dib);
  fourier.FFT(1);

  CDib dib;
  fourier.GetSpectrumImage(dib);
  AfxNewImage(dib);

  fourier.GetPhaseImage(dib);
  AfxNewImage(dib);

  fourier.FFT(-1);
  fourier.GetImage(dib);
  AfxNewImage(dib);
}


void CImageToolDoc::OnIdealLowpass()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  int w = m_Dib.GetWidth();
  int h = m_Dib.GetHeight();

  if (!IsPowerOf2(w) || !IsPowerOf2(h))
  {
    AfxMessageBox(TEXT("���� �Ǵ� ������ ũ�Ⱑ 2�� �¼��� �ƴմϴ�."));
    return;
  }

  CFreqFilterDlg dlg;
  dlg.m_strFilterType = TEXT("���� ��� ����");
  dlg.m_strFilterShape = TEXT("�̻���(Ideal)");
  dlg.m_strRange.Format(TEXT("(0 ~ %d)"), min(w / 2, h / 2));

  if (dlg.DoModal() == IDOK)
  {
    CDibFourier fourier;
    fourier.SetImage(m_Dib);
    fourier.FFT(1);
    fourier.IdealLowpass(dlg.m_nCutoff);
    fourier.FFT(-1);

    CDib dib;
    fourier.GetImage(dib);
    AfxNewImage(dib);
  }
}


void CImageToolDoc::OnIdealHighpass()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  int w = m_Dib.GetWidth();
  int h = m_Dib.GetHeight();

  if (!IsPowerOf2(w) || !IsPowerOf2(h))
  {
    AfxMessageBox(TEXT("���� �Ǵ� ������ ũ�Ⱑ 2�� �¼��� �ƴմϴ�."));
    return;
  }

  CFreqFilterDlg dlg;
  dlg.m_strFilterType = TEXT("�� ��� ����");
  dlg.m_strFilterShape = TEXT("�̻���(Ideal)");
  dlg.m_strRange.Format(TEXT("(0 ~ %d)"), min(w / 2, h / 2));

  if (dlg.DoModal() == IDOK)
  {
    CDibFourier fourier;
    fourier.SetImage(m_Dib);
    fourier.FFT(1);
    fourier.IdealHighpass(dlg.m_nCutoff);
    fourier.FFT(-1);

    CDib dib;
    fourier.GetImage(dib);
    AfxNewImage(dib);
  }
}


void CImageToolDoc::OnGaussianLowpass()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  int w = m_Dib.GetWidth();
  int h = m_Dib.GetHeight();

  if (!IsPowerOf2(w) || !IsPowerOf2(h))
  {
    AfxMessageBox(TEXT("���� �Ǵ� ������ ũ�Ⱑ 2�� �¼��� �ƴմϴ�."));
    return;
  }

  CFreqFilterDlg dlg;
  dlg.m_strFilterType = TEXT("���� ��� ����");
  dlg.m_strFilterShape = TEXT("����þ�(Gaussian)");
  dlg.m_strRange.Format(TEXT("(0 ~ %d)"), min(w / 2, h / 2));

  if (dlg.DoModal() == IDOK)
  {
    CDibFourier fourier;
    fourier.SetImage(m_Dib);
    fourier.FFT(1);
    fourier.GaussianLowpass(dlg.m_nCutoff);
    fourier.FFT(-1);

    CDib dib;
    fourier.GetImage(dib);
    AfxNewImage(dib);
  }
}


void CImageToolDoc::OnGaussianHighpass()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  int w = m_Dib.GetWidth();
  int h = m_Dib.GetHeight();

  if (!IsPowerOf2(w) || !IsPowerOf2(h))
  {
    AfxMessageBox(TEXT("���� �Ǵ� ������ ũ�Ⱑ 2�� �¼��� �ƴմϴ�."));
    return;
  }

  CFreqFilterDlg dlg;
  dlg.m_strFilterType = TEXT("�� ��� ����");
  dlg.m_strFilterShape = TEXT("����þ�(Gaussian)");
  dlg.m_strRange.Format(TEXT("(0 ~ %d)"), min(w / 2, h / 2));

  if (dlg.DoModal() == IDOK)
  {
    CDibFourier fourier;
    fourier.SetImage(m_Dib);
    fourier.FFT(1);
    fourier.GaussianHighpass(dlg.m_nCutoff);
    fourier.FFT(-1);

    CDib dib;
    fourier.GetImage(dib);
    AfxNewImage(dib);
  }
}


void CImageToolDoc::OnEdgeRoberts()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CDib dib = m_Dib;
  DibEdgeRoberts(dib);
  AfxNewImage(dib);
}


void CImageToolDoc::OnEdgePrewitt()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CDib dib = m_Dib;
  DibEdgePrewitt(dib);
  AfxNewImage(dib);
}


void CImageToolDoc::OnEdgeSobel()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CDib dib = m_Dib;
  DibEdgeSobel(dib);
  AfxNewImage(dib);
}


void CImageToolDoc::OnHoughLine()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CDib dib = m_Dib;
  LineParam line = DibHoughLine(dib);
  DibDrawLine(dib, line, 255);

  AfxNewImage(dib);

  CString str;
  str.Format(TEXT("���� ��ȯ ���:\n\nrho = %lf, ang = %lf"), line.rho, line.ang);
  AfxMessageBox(str);
}


void CImageToolDoc::OnHarrisCorner()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CHarrisDlg dlg;
  if (dlg.DoModal() == IDOK)
  {
    CornerPoints cp;
    cp = DibHarrisCorner(m_Dib, dlg.m_nThreshold);

    CDib dib = m_Dib;
    BYTE** ptr = dib.GetPtr();

    int x, y;
    for (register int i = 0; i < cp.num; i++)
    {
      x = cp.x[i];
      y = cp.y[i];

      ptr[y - 1][x - 1] = ptr[y - 1][x] = ptr[y - 1][x + 1] = 0;
      ptr[y][x - 1] = ptr[y][x] = ptr[y][x + 1] = 0;
      ptr[y + 1][x - 1] = ptr[y + 1][x] = ptr[y + 1][x + 1] = 0;
    }
    AfxNewImage(dib);
  }
}

void CImageToolDoc::OnColorGrayscale()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CDib dib = m_Dib;
  DibGrayscale(dib);
  AfxNewImage(dib);
}

void CImageToolDoc::OnUpdateColorGrayscale(CCmdUI *pCmdUI)
{
  // TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
  pCmdUI->Enable(m_Dib.GetBitCount() == 24);
}

void CImageToolDoc::OnColorSplitRgb()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CDib dibR, dibG, dibB;
  DibColorSplitRGB(m_Dib, dibR, dibG, dibB);

  AfxNewImage(dibR);
  AfxNewImage(dibG);
  AfxNewImage(dibB);
}


void CImageToolDoc::OnUpdateColorSplitRgb(CCmdUI *pCmdUI)
{
  // TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
  pCmdUI->Enable(m_Dib.GetBitCount() == 24);
}


void CImageToolDoc::OnColorSplitHsi()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CDib dibH, dibS, dibI;
  DibColorSplitHSI(m_Dib, dibH, dibS, dibI);

  AfxNewImage(dibH);
  AfxNewImage(dibS);
  AfxNewImage(dibI);
}


void CImageToolDoc::OnUpdateColorSplitHsi(CCmdUI *pCmdUI)
{
  // TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
  pCmdUI->Enable(m_Dib.GetBitCount() == 24);
}


void CImageToolDoc::OnColorSplitYuv()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CDib dibY, dibU, dibV;
  DibColorSplitYUV(m_Dib, dibY, dibU, dibV);

  AfxNewImage(dibY);
  AfxNewImage(dibU);
  AfxNewImage(dibV);
}


void CImageToolDoc::OnUpdateColorSplitYuv(CCmdUI *pCmdUI)
{
  // TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
  pCmdUI->Enable(m_Dib.GetBitCount() == 24);
}


void CImageToolDoc::OnColorCombineRgb()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CColorCombineDlg dlg;
  dlg.m_strColorSpace.Format(TEXT("RGB ���� ��� ��ġ��"));
  if (dlg.DoModal() == IDOK)
  {
    CImageToolDoc* pDoc1 = (CImageToolDoc*)dlg.m_pDoc1;
    CImageToolDoc* pDoc2 = (CImageToolDoc*)dlg.m_pDoc2;
    CImageToolDoc* pDoc3 = (CImageToolDoc*)dlg.m_pDoc3;

    CDib dib;
    BOOL ret;

    ret = DibColorCombineRGB(pDoc1->m_Dib, pDoc2->m_Dib, pDoc3->m_Dib, dib);

    if (ret)
    {
      AfxNewImage(dib);
    }
    else
    {
      AfxMessageBox(TEXT("������ ũ�Ⱑ �ٸ��ϴ�."));
    }
  }
}


void CImageToolDoc::OnColorCombineHsi()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CColorCombineDlg dlg;
  dlg.m_strColorSpace.Format(TEXT("RGB ���� ��� ��ġ��"));
  if (dlg.DoModal() == IDOK)
  {
    CImageToolDoc* pDoc1 = (CImageToolDoc*)dlg.m_pDoc1;
    CImageToolDoc* pDoc2 = (CImageToolDoc*)dlg.m_pDoc2;
    CImageToolDoc* pDoc3 = (CImageToolDoc*)dlg.m_pDoc3;

    CDib dib;
    BOOL ret;

    ret = DibColorCombineHSI(pDoc1->m_Dib, pDoc2->m_Dib, pDoc3->m_Dib, dib);

    if (ret)
    {
      AfxNewImage(dib);
    }
    else
    {
      AfxMessageBox(TEXT("������ ũ�Ⱑ �ٸ��ϴ�."));
    }
  }
}


void CImageToolDoc::OnColorCombineYuv()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CColorCombineDlg dlg;
  dlg.m_strColorSpace.Format(TEXT("RGB ���� ��� ��ġ��"));
  if (dlg.DoModal() == IDOK)
  {
    CImageToolDoc* pDoc1 = (CImageToolDoc*)dlg.m_pDoc1;
    CImageToolDoc* pDoc2 = (CImageToolDoc*)dlg.m_pDoc2;
    CImageToolDoc* pDoc3 = (CImageToolDoc*)dlg.m_pDoc3;

    CDib dib;
    BOOL ret;

    ret = DibColorCombineYUV(pDoc1->m_Dib, pDoc2->m_Dib, pDoc3->m_Dib, dib);

    if (ret)
    {
      AfxNewImage(dib);
    }
    else
    {
      AfxMessageBox(TEXT("������ ũ�Ⱑ �ٸ��ϴ�."));
    }
  }
}


void CImageToolDoc::OnColorEdge()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CDib dib = m_Dib;
  DibColorEdge(dib);
  AfxNewImage(dib);
}


void CImageToolDoc::OnUpdateColorEdge(CCmdUI *pCmdUI)
{
  // TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
  pCmdUI->Enable(m_Dib.GetBitCount() == 24);
}


void CImageToolDoc::OnColorEqualize()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CDib dib = m_Dib;
  DibColorHistEqual(dib);
  AfxNewImage(dib);
}


void CImageToolDoc::OnUpdateColorEqualize(CCmdUI *pCmdUI)
{
  // TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
  pCmdUI->Enable(m_Dib.GetBitCount() == 24);
}


void CImageToolDoc::OnSegmentBinarization()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CBinarizationDlg dlg;
  dlg.SetImage(m_Dib);
  if (dlg.DoModal() == IDOK)
  {
    CDib dib = m_Dib;
    DibBinarization(dib, dlg.m_nThreshold);
    AfxNewImage(dib);
  }
}


void CImageToolDoc::OnSegmentIterative()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CDib dib = m_Dib;
  int th = DibBinarizationIterative(dib);
  DibBinarization(dib, th);
  AfxNewImage(dib);

  CString str;
  str.Format(TEXT("Threshold = %d"), th);
  AfxMessageBox(str);
}


void CImageToolDoc::OnSegmentLabeling()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CDib dib = m_Dib;
  int nLabel = DibLabeling(dib);
  AfxNewImage(dib);

  CString str;
  str.Format(TEXT("Label count = %d"), nLabel);
  AfxMessageBox(str);
}


void CImageToolDoc::OnContourTracing()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  ContourPoints cp = DibContourTracing(m_Dib);

  int w = m_Dib.GetWidth();
  int h = m_Dib.GetHeight();

  CDib dib;
  dib.CreateGrayImage(w, h, 0);
  BYTE** ptr = dib.GetPtr();

  for (register int i = 0; i < cp.num; i++)
  {
    ptr[cp.y[i]][cp.x[i]] = 255;
  }

  AfxNewImage(dib);
}


void CImageToolDoc::OnMorphologyErosion()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CDib dib = m_Dib;
  DibMorphologyErosion(dib);
  AfxNewImage(dib);
}


void CImageToolDoc::OnMorphologyDilation()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CDib dib = m_Dib;
  DibMorphologyDilation(dib);
  AfxNewImage(dib);
}


void CImageToolDoc::OnMorphologyOpening()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CDib dib = m_Dib;
  DibMorphologyErosion(dib);
  DibMorphologyDilation(dib);
  AfxNewImage(dib);
}


void CImageToolDoc::OnMorphologyClosing()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CDib dib = m_Dib;
  DibMorphologyDilation(dib);
  DibMorphologyErosion(dib);
  AfxNewImage(dib);
}


void CImageToolDoc::OnGraymorphErosion()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CDib dib = m_Dib;
  DibMorphologyGrayErosion(dib);
  AfxNewImage(dib);
}


void CImageToolDoc::OnGraymorphDilation()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CDib dib = m_Dib;
  DibMorphologyGrayDilation(dib);
  AfxNewImage(dib);
}


void CImageToolDoc::OnGraymorphOpening()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CDib dib = m_Dib;
  DibMorphologyGrayErosion(dib);
  DibMorphologyGrayDilation(dib);
  AfxNewImage(dib);
}


void CImageToolDoc::OnGraymorphClosing()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CDib dib = m_Dib;
  DibMorphologyGrayDilation(dib);
  DibMorphologyGrayErosion(dib);
  AfxNewImage(dib);
}


void CImageToolDoc::OnFourierDescriptor()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  CFourierDescDlg dlg;
  if (dlg.DoModal() == IDOK)
  {
    ContourPoints cp = DibFourierDescriptor(m_Dib, dlg.m_nPercent);

    int w = m_Dib.GetWidth();
    int h = m_Dib.GetHeight();

    CDib dib = m_Dib;
    dib.CreateGrayImage(w, h, 0);
    BYTE** ptr = dib.GetPtr();

    for (register int i = 0; i < cp.num; i++)
    {
      ptr[cp.y[i]][cp.x[i]] = 255;
    }

    AfxNewImage(dib);
  }
}


void CImageToolDoc::OnInvariantMoments()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  double m[7] = { 0, };
  DibInvariantMoments(m_Dib, m);

  CString str = TEXT("Invariant Moments : (x0.000001)\n\n");
  for (register int i = 0; i < 7; i++)
  {
    str.AppendFormat(TEXT("m[%d] = %16.10lf\n"), i, m[i] * 1000000);
  }

  AfxMessageBox(str);
}


void CImageToolDoc::OnFileNew()
{
  // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
  theApp.m_pImageDocTemplate->OpenDocumentFile(NULL);
}
