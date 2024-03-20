#pragma once
#pragma once

const double PI = acos(-0.1);

class RGBBYTE;

class CDib
{
protected:
  LONG m_nWidth;
  LONG m_nHeight;
  WORD m_nBitCount;
  DWORD m_nDibSize;

  BYTE *m_pDib;
  BYTE **m_pPtr;
  RGBBYTE ** m_pRgbPtr;
public:
  CDib(void);
  CDib(const CDib& dib);
  ~CDib(void);

  BOOL CreateGrayImage(int nWidth, int nHeight, BYTE value = 255);
  BOOL CreateRGBImage(int nWidth, int nHeight, COLORREF value = 0x00ffffff);
  void Destroy();

  CDib& operator = (const CDib& dib);
  BOOL Copy(CDib* pImage);

  void Draw(HDC hDC);
  void Draw(HDC hDC, int dx, int dy);
  void Draw(HDC hDC, int dx, int dy, int dw, int dh, DWORD dwRop = SRCCOPY);
  void Draw(HDC hDC, int dx, int dy, int dw, int dh, int sx, int sy, int sw, int sh, DWORD dwRop = SRCCOPY);

  BOOL Load(LPCTSTR lpszFileName);
  BOOL Save(LPCTSTR lpszFileName);

  BYTE **GetPtr();
  RGBBYTE **GetRGBPtr();

  BOOL CopyToClipboard();
  BOOL PasteFromClipboard();

  LONG GetHeight(){ return m_nHeight; }
  LONG GetWidth(){ return m_nWidth; }
  WORD GetBitCount(){ return m_nBitCount; }
  DWORD GetDibSize(){ return m_nDibSize; }
  BOOL IsValid(){ return (m_pDib != NULL); }
  LPBITMAPINFO GetBitmapInfoAddr(){ return (LPBITMAPINFO)m_pDib; }
  int getPaletteNums();
  LPVOID GetDibBitsAddr();

protected:
  BOOL InitDib();

  BOOL LoadBMP(LPCTSTR lpszFileName);
  BOOL SaveBMP(LPCTSTR lpszFileName);

  BOOL AllocPtr();
  void FreePtr();
};

inline BYTE** CDib::GetPtr()
{
  ASSERT(m_nBitCount == 8);
  ASSERT(m_pPtr != NULL);

  return m_pPtr;
}

inline RGBBYTE** CDib::GetRGBPtr()
{
  ASSERT(m_nBitCount == 24);
  ASSERT(m_pRgbPtr != NULL);

  return m_pRgbPtr;
}

template<typename T>
inline T limit(const T& value)
{
  return((value > 255) ? 255 : ((value < 0) ? 0 : value));
}

template<typename T>
inline T limit(const T& value, const T& lower, const T& upper)
{
  return((value > upper) ? upper : ((value < lower) ? lower : value));
}

template<typename T>
inline void swap(T& lha, T& rha)
{
  T tmp = lha;
  lha = rha;
  rha = tmp;
}
