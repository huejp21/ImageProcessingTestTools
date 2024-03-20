#include "stdafx.h"
#include "Dib.h"
#include "DibGeometry.h"

void DibTranslate(CDib &dib, int sx, int sy)
{
  CDib cpy = dib;
  int w = dib.GetWidth();
  int h = dib.GetHeight();

  dib.CreateGrayImage(w, h, 0);

  BYTE** ptr1 = dib.GetPtr();
  BYTE** ptr2 = cpy.GetPtr();

  int x, y;

  for (register int row = 0; row < h; row++)
  {
    for (register int col = 0; col < w; col++)
    {
      x = col - sx;
      y = row - sy;
      if (x >= 0 && x < w && y>= 0 && y < h)
      {
        ptr1[row][col] = ptr2[y][x];
      }
    }
  }
}

void DibResizeNearest(CDib &dib, int nw, int nh)
{
  CDib cpy = dib;
  int w = cpy.GetWidth();
  int h = cpy.GetHeight();

  dib.CreateGrayImage(nw, nh);

  BYTE** ptr1 = dib.GetPtr();
  BYTE** ptr2 = cpy.GetPtr();

  int x, y;

  for (register int row = 0; row < nh; row++)
  {
    for (register int col = 0; col < nw; col++)
    {
      x = (int)w * col / nw;
      y = (int)h *row / nh;

      ptr1[row][col] = ptr2[y][x];
    }
  }
}

void DibResizeBilinear(CDib &dib, int nw, int nh)
{
  CDib cpy = dib;
  int w = cpy.GetWidth();
  int h = cpy.GetHeight();

  dib.CreateGrayImage(nw, nh);

  BYTE** ptr1 = dib.GetPtr();
  BYTE** ptr2 = cpy.GetPtr();

  int x1, y1, x2, y2;
  double rx, ry, p, q, temp;

  for (register int row = 0; row < nh; row++)
  {
    for (register int col = 0; col < nw; col++)
    {
      rx = (double)w * col / nw;
      ry = (double)h * row / nh;

      x1 = (int)rx;
      y1 = (int)ry;

      x2 = x1 + 1;
      if (x2 == w) x2 = w - 1;
      y2 = y1 + 1;
      if (y2 == w) y2 = h - 1;

      p = rx - x1;
      q = ry - y1;

      temp =
        (1.0 - p) * (1.0 - q) * ptr2[y1][x1] +
        p *(1.0 - q) * ptr2[y1][x2] +
        (1.0 - p) * q * ptr2[y2][x1] +
        p * q * ptr2[y2][x2];

      ptr1[row][col] = (BYTE)limit(temp);
    }
  }
}

void DibResizeCubic(CDib &dib, int nw, int nh)
{
  CDib cpy = dib;
  int w = cpy.GetWidth();
  int h = cpy.GetHeight();

  dib.CreateGrayImage(nw, nh);

  BYTE** ptr1 = dib.GetPtr();
  BYTE** ptr2 = cpy.GetPtr();

  int x1, x2, x3, x4, y1, y2, y3, y4;
  double v1, v2, v3, v4, v;
  double rx, ry, p, q;

  for (register int row = 0; row < nh; row++)
  {
    for (register int col = 0; col < nw; col++)
    {
      rx = (double)w * col / nw;
      ry = (double)h * row / nh;

      x2 = (int)rx;
      x1 = x2 - 1;
      if (x1 < 0) x1 = 0;
      x3 = x2 + 1;
      if (x3 >= w) x3 = w - 1;
      x4 = x2 + 2;
      if (x4 >= w) x4 = w - 1;
      p = rx - x2;

      y2 = (int)ry;
      y1 = y2 - 1;
      if (y1 < 0) y1 = 0;
      y3 = y2 + 1;
      if (y3 >= h) y3 = h - 1;
      y4 = y2 + 2;
      if (y4 >= h) y4 = h - 1;
      q = ry - y2;

      v1 = cubic_interpolation(ptr2[y1][x1], ptr2[y1][x2], ptr2[y1][x3], ptr2[y1][x4], p);
      v2 = cubic_interpolation(ptr2[y2][x1], ptr2[y2][x2], ptr2[y2][x3], ptr2[y2][x4], p);
      v3 = cubic_interpolation(ptr2[y3][x1], ptr2[y3][x2], ptr2[y3][x3], ptr2[y3][x4], p);
      v4 = cubic_interpolation(ptr2[y4][x1], ptr2[y4][x2], ptr2[y4][x3], ptr2[y4][x4], p);
      v = cubic_interpolation(v1, v2, v3, v4, q);
      ptr1[row][col] = (BYTE)limit(v);
    }
  }
}

double cubic_interpolation(double v1, double v2, double v3, double v4, double d)
{
  double v, p1, p2, p3, p4;
  p1 = v2;
  p2 = -v1 + v3;
  p3 = 2 * (v1 - v2) + v3 - v4;
  p4 = -v1 + v2 - v3 + v4;

  v = p1 + d * (p2 + d * (p3 + d * p4));
  return v;
}