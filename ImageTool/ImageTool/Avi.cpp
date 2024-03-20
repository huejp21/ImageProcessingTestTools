#include "stdafx.h"
#include "Avi.h"
#include "Dib.h"
#include "RGBBYTE.h"

#include <vfw.h>

CAvi::CAvi()
{
  AVIFileInit();

  m_pAviFile = NULL;
  m_pVideoStream = NULL;
  m_pVideoFrame = NULL;

  m_nWidth = 0;
  m_nRWidth = 0;
  m_nHeight = 0;
  m_nBitCount = 0;
  m_nTotalFrame = 0;
  m_nFrameRate = 0;
}
CAvi::~CAvi()
{
  Close();
  AVIFileExit();
}

BOOL CAvi::Open(LPCTSTR lpszPathName)
{
  int i;
  HRESULT hr;
  AVIFILEINFO aviFileInfo;
  AVISTREAMINFO aviStreamInfo;
  PAVISTREAM pAviTempStream = NULL;

  if (m_pAviFile)
  {
    Close();
    m_pAviFile = NULL;
  }

  hr = AVIFileOpen(&m_pAviFile, lpszPathName, OF_READ, NULL);
  if (hr)
  {
    return FALSE;
  }

  hr = AVIFileInfo(m_pAviFile, &aviFileInfo, sizeof(AVIFILEINFO));
  if (hr)
  {
    Close();
    return FALSE;
  }

  for (i = 0; i < (LONG)aviFileInfo.dwStreams; i++)
  {
    hr = AVIFileGetStream(m_pAviFile, &pAviTempStream, 0L, i);
    if (hr)
    {
      continue;
    }
    hr = AVIStreamInfo(pAviTempStream, &aviStreamInfo, sizeof(AVISTREAMINFO));
    if (hr)
    {
      continue;
    }
    if (aviStreamInfo.fccType == streamtypeVIDEO)
    {
      m_pVideoStream = pAviTempStream;

      AVIStreamAddRef(m_pVideoStream);
      m_nTotalFrame = aviStreamInfo.dwLength;
      m_nFrameRate = aviStreamInfo.dwRate / aviStreamInfo.dwScale;

      RECT rt = aviStreamInfo.rcFrame;
      m_nWidth = rt.right - rt.left;
      m_nHeight = rt.bottom - rt.top;
      m_nRWidth = (m_nWidth * m_nBitCount / 8 + 3) & ~3;
      m_pVideoFrame = AVIStreamGetFrameOpen(m_pVideoStream, NULL);
      if (!m_pVideoFrame)
      {
        Close();
        return FALSE;
      }
    }
    else
    {
      AVIStreamRelease(pAviTempStream);
    }
  }
  return TRUE;
}

void CAvi::Close()
{
  if (m_pVideoFrame != NULL)
  {
    AVIStreamGetFrameClose(m_pVideoFrame);
    m_pVideoFrame = NULL;
  }
  if (m_pVideoStream != NULL)
  {
    AVIStreamRelease(m_pVideoStream);
    m_pVideoStream = NULL;
  }
  if (m_pAviFile != NULL)
  {
    AVIFileRelease(m_pAviFile);
    m_pAviFile = NULL;
  }
}

void CAvi::DrawFrame(HDC hDC, int nFrame)
{
  BYTE *pDib = (BYTE*)AVIStreamGetFrame(m_pVideoFrame, nFrame);
  if (!pDib)
  {
    return;
  }
  LPBITMAPINFO lpbi;
  LPSTR lpDIBBits;

  lpbi = (LPBITMAPINFO)pDib;

  if (lpbi->bmiHeader.biBitCount == 8)
  {
    lpDIBBits = (LPSTR)pDib + sizeof(BITMAPINFOHEADER) + 1024;
  }
  else
  {
    lpDIBBits = (LPSTR)pDib + sizeof(BITMAPINFOHEADER);
  }

  ::SetDIBitsToDevice(
    hDC,
    0,
    0,
    m_nWidth,
    m_nHeight,
    0,
    0,
    0,
    (WORD)m_nHeight,
    lpDIBBits,
    lpbi,
    DIB_RGB_COLORS
    );
}

void CAvi::DrawFrame(HDC hDC, int nFrame, int dx, int dy)
{
  DrawFrame(hDC, nFrame, dx, dy, GetWidth(), GetHeight(), SRCCOPY);
}

void CAvi::DrawFrame(HDC hDC, int nFrame, int dx, int dy, int dw, int dh, DWORD dwRop)
{
  BYTE *pDib = (BYTE*)AVIStreamGetFrame(m_pVideoFrame, nFrame);
  if (!pDib)
  {
    return;
  }
  LPBITMAPINFO lpbi;
  LPSTR lpDIBBits;

  lpbi = (LPBITMAPINFO)pDib;

  if (lpbi->bmiHeader.biBitCount == 8)
  {
    lpDIBBits = (LPSTR)pDib + sizeof(BITMAPINFOHEADER) + 1024;
  }
  else
  {
    lpDIBBits = (LPSTR)pDib + sizeof(BITMAPINFOHEADER);
  }

  ::SetStretchBltMode(hDC, COLORONCOLOR);
  ::StretchDIBits(
    hDC,
    dx,
    dy,
    dw,
    dh,
    0,
    0,
    m_nWidth,
    m_nHeight,
    lpDIBBits,
    lpbi,
    DIB_RGB_COLORS,
    dwRop
    );
}

BOOL CAvi::GetFrame(int nFrame, CDib &dib)
{
  LPVOID lpDib;
  LPSTR lpDIBBits;
  LPBITMAPINFO lpbi;
  lpDib = AVIStreamGetFrame(m_pVideoFrame, nFrame);
  lpbi = (LPBITMAPINFO)lpDib;

  if (lpbi->bmiHeader.biBitCount == 8)
  {
    lpDIBBits = (LPSTR)lpDib + sizeof(BITMAPINFOHEADER) + 1024;
  }
  else
  {
    lpDIBBits = (LPSTR)lpDib + sizeof(BITMAPINFOHEADER);
  }

  if (lpbi->bmiHeader.biBitCount == 8)
  {
    lpDIBBits = (LPSTR)lpDib + sizeof(BITMAPINFOHEADER) + 1024;
    dib.CreateGrayImage(m_nWidth, m_nHeight);
    memcpy(dib.GetBitmapInfoAddr(), lpDib, lpbi->bmiHeader.biSize + 1024 + lpbi->bmiHeader.biSizeImage);
  }
  else if (lpbi->bmiHeader.biBitCount == 24)
  {
    lpDIBBits = (LPSTR)lpDib + sizeof(BITMAPINFOHEADER);
    dib.CreateRGBImage(m_nWidth, m_nHeight);
    memcpy(dib.GetBitmapInfoAddr(), lpDib, lpbi->bmiHeader.biSize + lpbi->bmiHeader.biSizeImage);
  }
  else
  {
    return FALSE;
  }
  return TRUE;
}
//}