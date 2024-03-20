#pragma once
#include <vfw.h>
#include "Dib.h"

class CAvi
{
public:
  CAvi();
  ~CAvi();

public:
  BOOL    Open(LPCTSTR lpszPathName);
  void    Close();

  void    DrawFrame(HDC hDC, int nFrame);
  void    DrawFrame(HDC hDC, int nFrame, int dx, int dy);
  void    DrawFrame(HDC hDC, int nFrame, int dx, int dy, int dw, int dh, DWORD dwRop = SRCCOPY);

  BOOL    GetFrame(int nFrame, CDib &dib);

  int     GetFrameRate() { return m_nFrameRate; }
  int     GetTotalFrame() { return m_nTotalFrame; }
  int     GetHeight() { return m_nHeight; }
  int     GetWidth() { return m_nWidth; }
  int     GetBitCount() { return m_nBitCount; }
  BOOL    IsValid() { return (m_pAviFile != NULL); };

protected:

  PAVIFILE    m_pAviFile = NULL;
  PAVISTREAM  m_pVideoStream = NULL;
  PGETFRAME   m_pVideoFrame;

  int         m_nWidth = 0;
  int         m_nRWidth = 0;
  int         m_nHeight = 0;

  int         m_nBitCount = 0;

  int         m_nTotalFrame = 0;
  int         m_nFrameRate = 0;
};