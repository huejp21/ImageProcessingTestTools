#include "stdafx.h"
#include "Dib.h"
#include "RGBBYTE.h"


CDib::CDib()
{
  m_nWidth = 0;
  m_nHeight = 0;
  m_nBitCount = 0;
  m_nDibSize = 0;
  m_pDib = NULL;
  m_pPtr = NULL;
  m_pRgbPtr = NULL;
}

CDib::CDib(const CDib& dib)
{
  m_nWidth = 0;
  m_nHeight = 0;
  m_nBitCount = 0;
  m_nDibSize = 0;
  m_pDib = NULL;
  m_pPtr = NULL;
  m_pRgbPtr = NULL;

  if (dib.m_pDib != NULL)
  {
    m_pDib = new BYTE[dib.m_nDibSize];
    memcpy(m_pDib, dib.m_pDib, dib.m_nDibSize);
    InitDib();
  }
}


CDib::~CDib()
{
  Destroy();
}

BOOL CDib::CreateGrayImage(int nWidth, int nHeight, BYTE value)
{
  if (m_pDib)
  {
    Destroy();
  }
  int nBitCount = 8;

  DWORD dwSizeImage = nHeight * (DWORD)((nWidth * nBitCount / 8 + 3)&~3);

  m_pDib = new BYTE[sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * (1 << nBitCount) + dwSizeImage];
  if (m_pDib == NULL) return FALSE;

  LPBITMAPINFOHEADER lpbmi = (LPBITMAPINFOHEADER)m_pDib;

  lpbmi->biSize = sizeof(BITMAPINFOHEADER);
  lpbmi->biWidth = nWidth;
  lpbmi->biHeight = nHeight;
  lpbmi->biPlanes = 1;
  lpbmi->biBitCount = nBitCount;
  lpbmi->biCompression = BI_RGB;
  lpbmi->biSizeImage = dwSizeImage;
  lpbmi->biXPelsPerMeter = 0;
  lpbmi->biYPelsPerMeter = 0;
  lpbmi->biClrUsed = 0;
  lpbmi->biClrImportant = 0;

  RGBQUAD *pPal = (RGBQUAD*)((BYTE*)m_pDib + sizeof(BITMAPINFOHEADER));
  for (int i = 0; i < 256; i++)
  {
    pPal->rgbBlue = (BYTE)i;
    pPal->rgbGreen = (BYTE)i;
    pPal->rgbRed = (BYTE)i;
    pPal->rgbReserved = 0;
    pPal++;
  }

  InitDib();

  BYTE *pData = (BYTE*)GetDibBitsAddr();
  memset(pData, value, dwSizeImage);
  return TRUE;
}

BOOL CDib::CreateRGBImage(int nWidth, int nHeight, COLORREF value)
{
  if (m_pDib)
  {
    Destroy();
  }

  int nBitCount = 24;
  DWORD dwSizeImage = nHeight * (DWORD)((nWidth * nBitCount / 8 + 3)&~3);

  m_pDib = new BYTE[sizeof(BITMAPINFOHEADER) + dwSizeImage];
  if (m_pDib == NULL)
  {
    return FALSE;
  }

  LPBITMAPINFOHEADER lpbmi = (LPBITMAPINFOHEADER)m_pDib;

  lpbmi->biSize = sizeof(BITMAPINFOHEADER);
  lpbmi->biWidth = nWidth;
  lpbmi->biHeight = nHeight;
  lpbmi->biPlanes = 1;
  lpbmi->biBitCount = nBitCount;
  lpbmi->biCompression = BI_RGB;
  lpbmi->biSizeImage = dwSizeImage;
  lpbmi->biXPelsPerMeter = 0;
  lpbmi->biYPelsPerMeter = 0;
  lpbmi->biClrUsed = 0;
  lpbmi->biClrImportant = 0;

  InitDib();

  for (int nRow = 0; nRow < m_nHeight; nRow++)
  {
    for (int nCol = 0; nCol < m_nWidth; nCol++)
    {
      m_pRgbPtr[nRow][nCol] = value;
    }
  }
}

BOOL CDib::InitDib()
{
  LPBITMAPINFOHEADER lpbmi = (LPBITMAPINFOHEADER)m_pDib;

  m_nWidth = lpbmi->biWidth;
  m_nHeight = lpbmi->biHeight;
  m_nBitCount = lpbmi->biBitCount;

  DWORD dwSizeImage = m_nHeight * (DWORD)((m_nWidth * m_nBitCount / 8 + 3)&~3);
  m_nDibSize = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * getPaletteNums() + dwSizeImage;

  if (!AllocPtr())
  {
    return FALSE;
  }
  return TRUE;
}

void CDib::Destroy()
{
  if (m_pDib)
  {
    delete[] m_pDib;
    m_pDib = NULL;
  }

  FreePtr();

  m_nWidth = 0;
  m_nHeight = 0;
  m_nBitCount = 0;
  m_nDibSize = 0;
}

CDib& CDib::operator=(const CDib& dib)
{
  if (this == &dib)
  {
    return *this;
  }

  if (dib.m_pDib == NULL)
  {
    Destroy();
    return *this;
  }

  if (m_pDib)
  {
    Destroy();
  }

  m_pDib = new BYTE[dib.m_nDibSize];
  memcpy(m_pDib, dib.m_pDib, dib.m_nDibSize);

  InitDib();
  
  return *this;
}

BOOL CDib::Copy(CDib *pDib)
{
  if (!pDib->IsValid())
  {
    Destroy();
    return TRUE;
  }

  if (m_pDib)
  {
    Destroy();
  }

  DWORD dwDibSize = pDib->GetDibSize();
  m_pDib = new BYTE[dwDibSize];
  if (m_pDib == NULL)
  {
    return FALSE;
  }

  BYTE *pbi = (BYTE*)pDib->GetBitmapInfoAddr();
  memcpy(m_pDib, pbi, dwDibSize);
  InitDib();
  return TRUE;
}

BOOL CDib::Load(LPCTSTR lpszFileName)
{
  CString fileType;
  fileType = lpszFileName;
  fileType.MakeUpper();
  
  if (fileType.Right(4) == ".BMP")
  {
    return LoadBMP(lpszFileName);
  }
  else
  {
    return FALSE;
  }
}

BOOL CDib::Save(LPCTSTR lpszFileName)
{
  CString fileType;
  fileType = lpszFileName;
  fileType.MakeUpper();

  if (fileType.Right(4) == ".BMP")
  {
    return SaveBMP(lpszFileName);
  }
  else
  {
    return FALSE;
  }
}

void CDib::Draw(HDC hDC)
{
  Draw(hDC, 0, 0);
}

void CDib::Draw(HDC hDC, int dx, int dy)
{
  if (m_pDib == NULL)
  {
    return;
  }

  LPBITMAPINFO lpbi = (LPBITMAPINFO)m_pDib;
  void *lpBits = (void*)GetDibBitsAddr();
  ::SetDIBitsToDevice(hDC, dx, dy, m_nWidth, m_nHeight, 0, 0, 0, m_nHeight, lpBits, lpbi, DIB_RGB_COLORS);
  ///////////////////////////////////////////////
}

void CDib::Draw(HDC hDC, int dx, int dy, int dw, int dh, DWORD dwRop)
{
  if (m_pDib ==NULL)
  {
    return;
  }

  LPBITMAPINFO lpbi = (LPBITMAPINFO)m_pDib;
  LPSTR lpDIBITS = (LPSTR)GetDibBitsAddr();

  ::StretchDIBits(hDC, dx, dy, dw, dh, 0, 0, m_nWidth, m_nHeight, lpDIBITS, lpbi, DIB_RGB_COLORS, SRCCOPY);
}

void CDib::Draw(HDC hDC, int dx, int dy, int dw, int dh, int sx, int sy, int sw, int sh, DWORD dwRop)
{
  if (m_pDib == NULL)
  {
    return;
  }

  LPBITMAPINFO lpbi = (LPBITMAPINFO)m_pDib;
  LPSTR lpDIBITS = (LPSTR)GetDibBitsAddr();

  ::StretchDIBits(hDC, dx, dy, dw, dh, sx, sy, sw, sh, lpDIBITS, lpbi, DIB_RGB_COLORS, SRCCOPY);
}

LPVOID CDib::GetDibBitsAddr()
{
  LPBITMAPINFOHEADER lpbmi = (LPBITMAPINFOHEADER)m_pDib;
  LPVOID lpDibBits = (LPVOID)((BYTE*)m_pDib + lpbmi->biSize + sizeof(RGBQUAD) * getPaletteNums());

  return lpDibBits;
}

int CDib::getPaletteNums()
{
  //팔레트 강제로 줫더만 16비트 24 비트는 대응이 안될걸? 나중에 비트만 맏으면 자동으로 계산하게 만들것
  switch (m_nBitCount)
  {
  case 1:
    return 2;
  case 4:
    return 16;
  case 8:
    return 256;
  default:
    return 0;
    break;
  }
}

BOOL CDib::AllocPtr()
{
  if (m_nBitCount == 8)
  {
    if (m_pPtr) FreePtr();
    m_pPtr = new BYTE*[m_nHeight];
    if (!m_pPtr) return FALSE;

    int nRWidth = ((m_nWidth * m_nBitCount / 8 + 3)&~3);
    BYTE *pData = (BYTE*)GetDibBitsAddr();
    for (int i = 0; i < m_nHeight; i++)
    {
      m_pPtr[i] = (BYTE*)(pData + (m_nHeight - i - 1) * nRWidth);
    }
  }
  else if (m_nBitCount == 24)
  {
    if (m_pRgbPtr) FreePtr();
    m_pRgbPtr = new RGBBYTE*[m_nHeight];
    if (!m_pRgbPtr) return FALSE;

    int nRWidth = ((m_nWidth * m_nBitCount / 8 + 3)&~3);
    BYTE *pData = (BYTE*)GetDibBitsAddr();
    for (int i = 0; i < m_nHeight; i++)
    {
      m_pRgbPtr[i] = (RGBBYTE*)(pData + (m_nHeight - i - 1) * nRWidth);
    }
  }
  else return FALSE;

  return TRUE;
}

void CDib::FreePtr()
{
  if (m_pPtr != NULL)
  {
    delete[] m_pPtr;
    m_pPtr = NULL;
  }
  if (m_pRgbPtr != NULL)
  {
    delete[] m_pRgbPtr;
    m_pRgbPtr = NULL;
  }
}

BOOL CDib::CopyToClipboard()
{
  int dwSizeDib;
  HANDLE hDib;

  if (!::OpenClipboard(NULL))
  {
    return FALSE;
  }

  dwSizeDib = GetDibSize();
  hDib = ::GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, dwSizeDib);
  if (hDib == NULL)
  {
    ::CloseClipboard();
    return FALSE;
  }

  void *lpDib = ::GlobalLock((HGLOBAL)hDib);
  memcpy(lpDib, GetBitmapInfoAddr(), dwSizeDib);
  ::GlobalUnlock(hDib);

  ::EmptyClipboard();
  ::SetClipboardData(CF_DIB, hDib);
  ::CloseClipboard();

  return TRUE;
}

BOOL CDib::PasteFromClipboard()
{
  HANDLE hDib;
  DWORD dwSize;
  void *lpDib;

  if (!::IsClipboardFormatAvailable(CF_DIB))
  {
    return FALSE;
  }
  if (!::OpenClipboard(NULL))
  {
    return FALSE;
  }
  hDib = ::GetClipboardData(CF_DIB);
  if (hDib == NULL)
  {
    ::CloseClipboard();
    return FALSE;
  }

  dwSize = (DWORD)::GlobalSize((HGLOBAL)hDib);
  lpDib = ::GlobalLock((HGLOBAL)hDib);

  LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)lpDib;
  LONG nWidth = lpbi->biWidth;
  LONG nHeight = lpbi->biHeight;
  WORD nBitCount = lpbi->biBitCount;
  DWORD dwSizeDib;

  DWORD dwSizeImage = nHeight * (DWORD)((nWidth * nBitCount / 8 + 3)&~3);
  if (nBitCount == 8)
  {
    dwSizeDib = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * (1 << nBitCount) + dwSizeImage;
  }
  else
  {
    dwSizeDib = sizeof(BITMAPINFOHEADER) + dwSizeImage;
  }

  if (m_pDib)
  {
    Destroy();
  }
  m_pDib = new BYTE[dwSizeDib];
  memcpy(m_pDib, lpDib, dwSizeDib);
  ::GlobalUnlock(hDib);
  ::CloseClipboard();

  InitDib();

  return TRUE;
}

