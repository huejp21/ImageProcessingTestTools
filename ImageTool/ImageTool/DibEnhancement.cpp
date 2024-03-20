#include "stdafx.h"
#include "Dib.h"
#include "DibEnhancement.h"
#include "RGBBYTE.h"
#include <math.h>

void DibInverse(CDib &dib)
{
  //Only working Grayscale Image. if use on true color image maybe will be error.
  int w = dib.GetWidth();
  int h = dib.GetHeight();

  if (dib.GetBitCount() == 8)
  {
    BYTE** ptr = dib.GetPtr();

    for (register int row = 0; row < h; row++)
    {
      for (register int col = 0; col < w; col++)
      {
        ptr[row][col] = 255 - ptr[row][col];
      }
    }
  }
  else
  {
    RGBBYTE** ptr = dib.GetRGBPtr();

    for (register int row = 0; row < h; row++)
    {
      for (register int col = 0; col < w; col++)
      {
        ptr[row][col].r = 255 - ptr[row][col].r;
        ptr[row][col].g = 255 - ptr[row][col].g;
        ptr[row][col].b = 255 - ptr[row][col].b;
      }
    }
  }
}

void DibBrightness(CDib &dib, int n)
{
  //Only working Grayscale Image. if use on true color image maybe will be error.
  int w = dib.GetWidth();
  int h = dib.GetHeight();

  BYTE** ptr = dib.GetPtr();

  for (register int row = 0; row < h; row++)
  {
    for (register int col = 0; col < w; col++)
    {
      ptr[row][col] = limit(ptr[row][col] + n);
    }
  }
}

void DibContrast(CDib &dib, int n)
{
  //Only working Grayscale Image. if use on true color image maybe will be error.
  int w = dib.GetWidth();
  int h = dib.GetHeight();

  BYTE** ptr = dib.GetPtr();
  BYTE value;
  for (register int row = 0; row < h; row++)
  {
    for (register int col = 0; col < w; col++)
    {
      value = ptr[row][col];
      ptr[row][col] = limit(value + ((value - 128) * n / 100));
    }
  }
}

void DibGammaCorrection(CDib &dib, float gamma)
{
  float invgamma = 1.f / gamma;

  int w = dib.GetWidth();
  int h = dib.GetHeight();
  BYTE** ptr = dib.GetPtr();

  for (register int row = 0; row < h; row++)
  {
    for (register int col = 0; col < w; col++)
    {
      ptr[row][col] = (BYTE)limit(pow((ptr[row][col] / 255.f), invgamma) * 255 + 0.5f);
    }
  }
}

void DibHistogram(CDib &dib, float histogram[256])
{
  int w = dib.GetWidth();
  int h = dib.GetHeight();
  BYTE** ptr = dib.GetPtr();
  int temp[256];
  memset(temp, 0, sizeof(int) * 256);

  for (register int row = 0; row < h; row++)
  {
    for (register int col = 0; col < w; col++)
    {
      temp[ptr[row][col]]++;
    }
  }
  float area = (float)w * h;
  for (register int i = 0; i < 256; i++)
  {
    histogram[i] = temp[i] / area;
  }
}

void DibHistEqual(CDib &dib)
{
  int w = dib.GetWidth();
  int h = dib.GetHeight();

  float hist[256];
  DibHistogram(dib, hist);
  double cdf[256] = { 0.0, };
  cdf[0] = hist[0];

  for (register int i = 1; i < 256; i++)
  {
    cdf[i] = cdf[i - 1] + hist[i];
  }

  BYTE** ptr = dib.GetPtr();
  for (register int row = 0; row < h; row++)
  {
    for (register int col = 0; col < w; col++)
    {
      ptr[row][col] = (BYTE)limit(cdf[ptr[row][col]] * 255);
    }
  }
}

BOOL DibAdd(CDib &dib1, CDib &dib2, CDib &dib3)
{
  int w = dib1.GetWidth();
  int h = dib1.GetHeight();

  if (w != dib2.GetWidth() || h !=dib2.GetHeight())
  {
    return FALSE;
  }

  dib3.CreateGrayImage(w, h);

  BYTE** ptr1 = dib1.GetPtr();
  BYTE** ptr2 = dib2.GetPtr();
  BYTE** ptr3 = dib3.GetPtr();

  for (register int row = 0; row < h; row++)
  {
    for (register int col = 0; col < w; col++)
    {
      ptr3[row][col] = limit(ptr1[row][col] + ptr2[row][col]);
    }
  }

  return TRUE;
}

BOOL DibSub(CDib &dib1, CDib &dib2, CDib &dib3)
{
  int w = dib1.GetWidth();
  int h = dib1.GetHeight();

  if (w != dib2.GetWidth() || h != dib2.GetHeight())
  {
    return FALSE;
  }

  dib3.CreateGrayImage(w, h);

  BYTE** ptr1 = dib1.GetPtr();
  BYTE** ptr2 = dib2.GetPtr();
  BYTE** ptr3 = dib3.GetPtr();

  for (register int row = 0; row < h; row++)
  {
    for (register int col = 0; col < w; col++)
    {
      ptr3[row][col] = limit(ptr1[row][col] - ptr2[row][col]);
    }
  }

  return TRUE;
}

BOOL DibAve(CDib &dib1, CDib &dib2, CDib &dib3)
{
  int w = dib1.GetWidth();
  int h = dib1.GetHeight();

  if (w != dib2.GetWidth() || h != dib2.GetHeight())
  {
    return FALSE;
  }

  dib3.CreateGrayImage(w, h);

  BYTE** ptr1 = dib1.GetPtr();
  BYTE** ptr2 = dib2.GetPtr();
  BYTE** ptr3 = dib3.GetPtr();

  for (register int row = 0; row < h; row++)
  {
    for (register int col = 0; col < w; col++)
    {
      ptr3[row][col] = limit((ptr1[row][col] + ptr2[row][col]) / 2);
    }
  }

  return TRUE;
}

BOOL DibDif(CDib &dib1, CDib &dib2, CDib &dib3)
{
  int w = dib1.GetWidth();
  int h = dib1.GetHeight();

  if (w != dib2.GetWidth() || h != dib2.GetHeight())
  {
    return FALSE;
  }

  dib3.CreateGrayImage(w, h);

  BYTE** ptr1 = dib1.GetPtr();
  BYTE** ptr2 = dib2.GetPtr();
  BYTE** ptr3 = dib3.GetPtr();
  int temp;
  for (register int row = 0; row < h; row++)
  {
    for (register int col = 0; col < w; col++)
    {
      temp = ptr1[row][col] - ptr2[row][col];
      ptr3[row][col] = (BYTE)((temp >= 0) ? temp : -temp);
    }
  }

  return TRUE;
}

BOOL DibAND(CDib &dib1, CDib &dib2, CDib &dib3)
{
  int w = dib1.GetWidth();
  int h = dib1.GetHeight();

  if (w != dib2.GetWidth() || h != dib2.GetHeight())
  {
    return FALSE;
  }

  dib3.CreateGrayImage(w, h);

  BYTE** ptr1 = dib1.GetPtr();
  BYTE** ptr2 = dib2.GetPtr();
  BYTE** ptr3 = dib3.GetPtr();
  for (register int row = 0; row < h; row++)
  {
    for (register int col = 0; col < w; col++)
    {
      ptr3[row][col] = (BYTE)(ptr1[row][col] & ptr2[row][col]);
    }
  }

  return TRUE;
}

BOOL DibOR(CDib &dib1, CDib &dib2, CDib &dib3)
{
  int w = dib1.GetWidth();
  int h = dib1.GetHeight();

  if (w != dib2.GetWidth() || h != dib2.GetHeight())
  {
    return FALSE;
  }

  dib3.CreateGrayImage(w, h);

  BYTE** ptr1 = dib1.GetPtr();
  BYTE** ptr2 = dib2.GetPtr();
  BYTE** ptr3 = dib3.GetPtr();
  for (register int row = 0; row < h; row++)
  {
    for (register int col = 0; col < w; col++)
    {
      ptr3[row][col] = (BYTE)(ptr1[row][col] | ptr2[row][col]);
    }
  }

  return TRUE;
}

void DibBitPlane(CDib &dib1, int bit, CDib &dib2)
{
  int w = dib1.GetWidth();
  int h = dib1.GetHeight();

  dib2.CreateGrayImage(w, h);

  BYTE** ptr1 = dib1.GetPtr();
  BYTE** ptr2 = dib2.GetPtr();

  for (register int row = 0; row < h; row++)
  {
    for (register int col = 0; col < w; col++)
    {
      ptr2[row][col] = (ptr1[row][col] & (1 << bit)) ? 255 : 0;
    }
  }
}