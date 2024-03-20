#include "stdafx.h"
#include "DibFourier.h"
#include "Dib.h"
#include <math.h>

CDibFourier::CDibFourier(void)
  :m_nWidth(0), m_nHeight(0), m_pRe(NULL), m_pIm(NULL)
{
}


CDibFourier::~CDibFourier(void)
{
  Free();
}

void CDibFourier::Free()
{
  if (m_pRe)
  {
    for (register int i = 0; i < m_nHeight; i++)
    {
      delete[]m_pRe[i];
    }
    delete[]m_pRe;
  }

  if (m_pIm)
  {
    for (register int i = 0; i < m_nHeight; i++)
    {
      delete[]m_pIm[i];
    }
    delete[]m_pIm;
  }
}

void CDibFourier::SetImage(CDib &dib)
{
  Free();

  m_nWidth = dib.GetWidth();
  m_nHeight = dib.GetHeight();

  m_pRe = new double*[m_nHeight];
  m_pIm = new double*[m_nHeight];

  for (register int i = 0; i < m_nHeight; i++)
  {
    m_pRe[i] = new double[m_nWidth];
    m_pIm[i] = new double[m_nWidth];

    memset(m_pRe[i], 0, sizeof(double) * m_nWidth);
    memset(m_pIm[i], 0, sizeof(double) * m_nWidth);
  }

  BYTE** ptr = dib.GetPtr();
  for (register int row = 0; row < m_nHeight; row++)
  {
    for (register int col = 0; col < m_nWidth; col++)
    {
      m_pRe[row][col] = (double)ptr[row][col];
    }
  }
}

void CDibFourier::GetImage(CDib &dib)
{
  if (m_pRe == NULL)
  {
    return;
  }

  dib.CreateGrayImage(m_nWidth, m_nHeight);

  BYTE** ptr = dib.GetPtr();
  for (register int row = 0; row < m_nHeight; row++)
  {
    for (register int col = 0; col < m_nWidth; col++)
    {
      ptr[row][col] = (BYTE)limit(m_pRe[row][col] + 0.5);
    }
  }
}

void CDibFourier::GetSpectrumImage(CDib &dib)
{
  dib.CreateGrayImage(m_nWidth, m_nHeight);
  BYTE** ptr = dib.GetPtr();
  double** pSpectrum = new double *[m_nHeight];
  for (register int i = 0; i < m_nHeight; i++)
  {
    pSpectrum[i] = new double[m_nWidth];
    memset(pSpectrum[i], 0, sizeof(double) * m_nWidth);
  }
  double mag, max_value = 0;
  for (register int row = 0; row < m_nHeight; row++)
  {
    for (register int col = 0; col < m_nWidth; col++)
    {
      mag = sqrt(m_pRe[row][col] * m_pRe[row][col] + m_pIm[row][col] * m_pIm[row][col]);
      pSpectrum[row][col] = log(mag + 1);

      if (pSpectrum[row][col] > max_value)
      {
        max_value = pSpectrum[row][col];
      }
    }
  }

  int x, y;
  for (register int row = 0; row < m_nHeight; row++)
  {
    for (register int col = 0; col < m_nWidth; col++)
    {
      x = col + m_nWidth / 2;
      y = row + m_nHeight / 2;

      if (x >= m_nWidth) x -= m_nWidth;
      if (y >= m_nHeight) y -= m_nHeight;

      ptr[row][col] = (BYTE)limit(pSpectrum[y][x] * 255 / max_value);
    }
  }

  for (register int i = 0; i < m_nHeight; i++)
  {
    delete[]pSpectrum[i];
  }
  delete[]pSpectrum;
}

void CDibFourier::GetPhaseImage(CDib &dib)
{
  dib.CreateGrayImage(m_nWidth, m_nHeight);
  BYTE** ptr = dib.GetPtr();
  double** pPhase = new double *[m_nHeight];
  for (register int i = 0; i < m_nHeight; i++)
  {
    pPhase[i] = new double[m_nWidth];
    memset(pPhase[i], 0, sizeof(double) * m_nWidth);
  }

  for (register int row = 0; row < m_nHeight; row++)
  {
    for (register int col = 0; col < m_nWidth; col++)
    {
      pPhase[row][col] = atan2(m_pIm[row][col], m_pRe[row][col]);
    }
  }

  int x, y;
  for (register int row = 0; row < m_nHeight; row++)
  {
    for (register int col = 0; col < m_nWidth; col++)
    {
      x = col + m_nWidth / 2;
      y = row + m_nHeight / 2;

      if (x >= m_nWidth) x -= m_nWidth;
      if (y >= m_nHeight) y -= m_nHeight;

      ptr[row][col] = (BYTE)limit(pPhase[y][x] * 128 / PI + 128);
    }
  }

  for (register int i = 0; i < m_nHeight; i++)
  {
    delete[]pPhase[i];
  }
  delete[]pPhase;
}

void CDibFourier::DFT(int dir)
{
  if (m_pRe == NULL || m_pIm == NULL)
  {
    return;
  }

  double** re = new double*[m_nHeight];
  double** im = new double*[m_nHeight];

  for (register int i = 0; i < m_nHeight; i++)
  {
    re[i] = new double[m_nWidth];
    im[i] = new double[m_nWidth];

    memcpy(re[i], m_pRe[i], sizeof(double) * m_nWidth);
    memcpy(im[i], m_pIm[i], sizeof(double) * m_nWidth);
  }

  double sum_re, sum_im, temp;
  for (register int row = 0; row < m_nHeight; row++)
  {
    for (register int col = 0; col < m_nWidth; col++)
    {
      sum_re = sum_im = 0;
      for (register int y = 0; y < m_nHeight; y++)
      {
        for (register int x = 0; x < m_nWidth; x++)
        {
          temp = 2 * dir * PI * ((double)col * x / m_nWidth + (double)row * y / m_nHeight);
          sum_re += (re[y][x] * cos(temp) - im[y][x] * sin(temp));
          sum_im += (re[y][x] * sin(temp) + im[y][x] * sin(temp));
        }//x
      }//y
      m_pRe[row][col] = sum_re;
      m_pIm[row][col] = sum_im;
      if (dir == -1)
      {
        m_pRe[row][col] /= (m_nWidth * m_nHeight);
        m_pIm[row][col] /= (m_nWidth * m_nHeight);
      }
    }//col
  }//row

  for (register int i = 0; i < m_nHeight; i++)
  {
    delete[]re[i];
    delete[]im[i];
  }
  delete[]re;
  delete[]im;
}

void CDibFourier::DFTRC(int dir)
{
  if (m_pRe == NULL || m_pIm == NULL)
  {
    return;
  }

  double* re = new double[m_nWidth];
  double* im = new double[m_nWidth];

  memset(re, 0, sizeof(double) * m_nWidth);
  memset(im, 0, sizeof(double) * m_nWidth);

  for (register int row = 0; row < m_nHeight; row++)
  {
    for (register int col = 0; col < m_nWidth; col++)
    {
      re[col] = m_pRe[row][col];
      im[col] = m_pIm[row][col];
    }

    DFT1d(re, im, m_nWidth, dir);

    for (register int col = 0; col < m_nWidth; col++)
    {
      m_pRe[row][col] = re[col];
      m_pIm[row][col] = im[col];
    }
  }
  delete[]re;
  delete[]im;

  re = new double[m_nHeight];
  im = new double[m_nHeight];

  memset(re, 0, sizeof(double) * m_nHeight);
  memset(im, 0, sizeof(double) * m_nHeight);

  for (register int col = 0; col < m_nWidth; col++)
  {
    for (register int row = 0; row < m_nHeight; row++)
    {
      re[row] = m_pRe[row][col];
      im[row] = m_pIm[row][col];
    }

    DFT1d(re, im, m_nHeight, dir);

    for (register int row = 0; row < m_nHeight; row++)
    {
      m_pRe[row][col] = re[row];
      m_pIm[row][col] = im[row];
    }
  }
  delete[]re;
  delete[]im;
}

void CDibFourier::FFT(int dir)
{
  if (m_pRe == NULL || m_pIm == NULL)
  {
    return;
  }
  if (!IsPowerOf2(m_nWidth) || !IsPowerOf2(m_nHeight))
  {
    return;
  }

  double* re = new double[m_nWidth];
  double* im = new double[m_nWidth];

  memset(re, 0, sizeof(double) * m_nWidth);
  memset(im, 0, sizeof(double) * m_nWidth);

  for (register int row = 0; row < m_nHeight; row++)
  {
    for (register int col = 0; col < m_nWidth; col++)
    {
      re[col] = m_pRe[row][col];
      im[col] = m_pIm[row][col];
    }

    FFT1d(re, im, m_nWidth, dir);

    for (register int col = 0; col < m_nWidth; col++)
    {
      m_pRe[row][col] = re[col];
      m_pIm[row][col] = im[col];
    }
  }
  delete [] re;
  delete [] im;

  re = new double[m_nHeight];
  im = new double[m_nHeight];

  memset(re, 0, sizeof(double) * m_nHeight);
  memset(im, 0, sizeof(double) * m_nHeight);

  for (register int col = 0; col < m_nWidth; col++)
  {
    for (register int row = 0; row < m_nHeight; row++)
    {
      re[row] = m_pRe[row][col];
      im[row] = m_pIm[row][col];
    }

    FFT1d(re, im, m_nHeight, dir);

    for (register int row = 0; row < m_nHeight; row++)
    {
      m_pRe[row][col] = re[row];
      m_pIm[row][col] = im[row];
    }
  }
  delete[]re;
  delete[]im;

}

void CDibFourier::IdealLowpass(int cutoff)
{
  int w2 = m_nWidth / 2;
  int h2 = m_nHeight / 2;

  int x, y;
  for (register int row = 0; row < m_nHeight; row++)
  {
    for (register int col = 0; col < m_nWidth; col++)
    {
      x = col + w2;
      y = row + h2;
      if (x >= m_nWidth) x -= m_nWidth;
      if (y >= m_nHeight) y -= m_nHeight;

      if (sqrt((double)(x - w2) * (x - w2) + (y - h2) * (y - h2)) > cutoff)
      {
        m_pRe[row][col] = m_pIm[row][col] = 0;
      }
        
    }
  }
}

void CDibFourier::IdealHighpass(int cutoff)
{
  int w2 = m_nWidth / 2;
  int h2 = m_nHeight / 2;

  int x, y;
  for (register int row = 0; row < m_nHeight; row++)
  {
    for (register int col = 0; col < m_nWidth; col++)
    {
      x = col + w2;
      y = row + h2;
      if (x >= m_nWidth) x -= m_nWidth;
      if (y >= m_nHeight) y -= m_nHeight;

      if (sqrt((double)(x - w2) * (x - w2) + (y - h2) * (y - h2)) < cutoff)
      {
        m_pRe[row][col] = m_pIm[row][col] = 0;
      }

    }
  }
}

void CDibFourier::GaussianLowpass(int cutoff)
{
  int w2 = m_nWidth / 2;
  int h2 = m_nHeight / 2;

  int x, y;
  double dist2, hval;
  for (register int row = 0; row < m_nHeight; row++)
  {
    for (register int col = 0; col < m_nWidth; col++)
    {
      x = col + w2;
      y = row + h2;
      if (x >= m_nWidth) x -= m_nWidth;
      if (y >= m_nHeight) y -= m_nHeight;

      dist2 = (double)(x - w2) * (x - w2) + (y - h2) * (y - h2);
      hval = exp(-dist2 / (2 * cutoff * cutoff));

      m_pRe[row][col] *= hval;
      m_pIm[row][col] *= hval;
    }
  }
}

void CDibFourier::GaussianHighpass(int cutoff)
{
  int w2 = m_nWidth / 2;
  int h2 = m_nHeight / 2;

  int x, y;
  double dist2, hval;
  for (register int row = 0; row < m_nHeight; row++)
  {
    for (register int col = 0; col < m_nWidth; col++)
    {
      x = col + w2;
      y = row + h2;
      if (x >= m_nWidth) x -= m_nWidth;
      if (y >= m_nHeight) y -= m_nHeight;

      dist2 = (double)(x - w2) * (x - w2) + (y - h2) * (y - h2);
      hval = 1.0 - exp(-dist2 / (2 * cutoff * cutoff));

      m_pRe[row][col] *= hval;
      m_pIm[row][col] *= hval;
    }
  }
}



void DFT1d(double *re, double *im, int N, int dir)
{
  double *tr = new double[sizeof(double) * N];
  double *ti = new double[sizeof(double) * N];

  memcpy(tr, re, sizeof(double) * N);
  memcpy(ti, im, sizeof(double) * N);

  double sum_re, sum_im, temp;

  for (register int i = 0; i < N; i++)
  {
    sum_re = sum_im = 0;

    for (register int x = 0; x < N; x++)
    {
      temp = 2 * dir * PI * ((double)i * x / N);
      sum_re += (tr[x] * cos(temp) + ti[x] * sin(temp));
      sum_im += (ti[x] * cos(temp) - tr[x] * sin(temp));
    }

    re[i] = sum_re;
    im[i] = sum_im;
  }

  if (dir == -1)
  {
    for (register int i = 0; i < N; i++)
    {
      re[i] /= (double)N;
      im[i] /= (double)N;
    }
  }

  delete[]tr;
  delete[]ti;
}

void FFT1d(double *re, double *im, int N, int dir)
{
  register int i, j, k;

  int n2 = N >> 1;
  int nb = 0;

  while (N != (1 << nb))
    nb++;

  for (i = 0, j = 0; i < N - 1; i++)
  {
    if (i < j)
    {
      swap(re[i], re[j]);
      swap(im[i], im[j]);
    }

    k = n2;

    while (k <= j)
    {
      j -= k;
      k >>= 1;
    }

    j += k;
  }

  int i1, l, l1, l2;
  double c1, c2, t1, t2, u1, u2, z;

  c1 = -1.0;
  c2 = 0.0;
  l2 = 1;

  for (l = 0; l<nb; l++)
  {
    l1 = l2;
    l2 <<= 1;
    u1 = 1.0;
    u2 = 0.0;

    for (j = 0; j < l1; j++)
    {
      for (i = j; i < N; i += l2)
      {
        i1 = i + l1;
        t1 = u1 * re[i1] - u2 * im[i1];
        t2 = u1 * im[i1] + u2 * re[i1];
        re[i1] = re[i] - t1;
        im[i1] = im[i] - t2;
        re[i] += t1;
        im[i] += t2;
      }

      z = u1 * c1 - u2 * c2;
      u2 = u1 * c2 + u2 * c1;
      u1 = z;
    }

    c2 = sqrt((1.0 - c1) / 2.0);

    if (dir == 1)
    {
      c2 = -c2;
    }

    c1 = sqrt((1.0 + c1) / 2.0);
  }

  if (dir == -1)
  {
    for (i = 0; i < N; i++)
    {
      re[i] /= (double)N;
      im[i] /= (double)N;
    }
  }
}

BOOL IsPowerOf2(int n)
{
  int ref = 1;
  while (ref < n)
  {
    ref <<= 1;
  }

  if (ref == n)
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}