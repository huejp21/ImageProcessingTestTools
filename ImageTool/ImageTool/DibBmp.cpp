#include "stdafx.h"
#include "Dib.h"

#define DIB_HEADER_MARKER ((WORD)('M' << 8) | 'B')

BOOL CDib::LoadBMP(LPCTSTR lpszFileName)
{
  CFile file;
  UINT nFileSize, nDibSize;

  BITMAPFILEHEADER bmfh;
  LPBITMAPINFOHEADER lpbmi;

  if (!file.Open(lpszFileName, CFile::modeRead | CFile::shareDenyWrite))
  {
    return FALSE;
  }

  nFileSize = (UINT)file.GetLength();

  if (file.Read((LPSTR)&bmfh, sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))
  {
    file.Close();
    return FALSE;
  }

  if (bmfh.bfType != DIB_HEADER_MARKER)
  {
    file.Close();
    return FALSE;
  }

  nDibSize = nFileSize - sizeof(bmfh);

  if (m_pDib)
  {
    Destroy();
  }

  m_pDib = new BYTE[nDibSize];
  if (m_pDib == NULL)
  {
    file.Close();
    return FALSE;
  }

  if (file.Read(m_pDib, nDibSize) != nDibSize)
  {
    delete[] m_pDib;
    m_pDib = NULL;
    file.Close();
    return FALSE;
  }

  lpbmi = (LPBITMAPINFOHEADER)m_pDib;
  if (lpbmi->biSize != sizeof(BITMAPINFOHEADER))
  {
    delete[] m_pDib;
    m_pDib = NULL;
    file.Close();
    return FALSE;
  }

  if (!InitDib())
  {
    delete[] m_pDib;
    m_pDib = NULL;
    file.Close();
    return FALSE;
  }

  file.Close();
  return TRUE;
}

BOOL CDib::SaveBMP(LPCTSTR lpszFileName)
{
  CFile file;
  BITMAPFILEHEADER bmfh;

  if (m_pDib == NULL)
  {
    return FALSE;
  }

  if (!file.Open(lpszFileName, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite))
  {
    return FALSE;
  }

  bmfh.bfType = DIB_HEADER_MARKER;
  bmfh.bfSize = (DWORD)sizeof(BITMAPFILEHEADER) + m_nDibSize;
  bmfh.bfReserved1 = 0;
  bmfh.bfReserved2 = 0;
  bmfh.bfOffBits = (DWORD)(sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * getPaletteNums());

  file.Write((LPSTR)&bmfh, sizeof(bmfh));

  file.Write(m_pDib, m_nDibSize);
  file.Close();
  return TRUE;
}