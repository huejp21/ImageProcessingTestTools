#include "stdafx.h"
#include "Dib.h"
#include "DibRotate.h"
#include <math.h>

void DibRotate(CDib &dib, double angle)
{
  int w = dib.GetWidth();
  int h = dib.GetHeight();

  CDib cpy = dib;

  double rad = (angle*PI) / 180;
  double cos_value = cos(rad);
  double sin_value = sin(rad);

  int nx, ny, minx, miny, maxx, maxy, nw, nh;

  minx = maxx = 0;
  miny = maxy = 0;

  nx = (int)floor(w * cos_value + 0.5);
  ny = (int)floor(w * sin_value + 0.5);
  minx = (minx < nx) ? minx : nx;
  maxx = (maxx > nx) ? maxx : nx;
  miny = (miny < ny) ? miny : ny;
  maxy = (maxy > ny) ? maxy : ny;

  nx = (int)floor(-h * sin_value + 0.5);
  ny = (int)floor(h * cos_value + 0.5);
  minx = (minx < nx) ? minx : nx;
  maxx = (maxx > nx) ? maxx : nx;
  miny = (miny < ny) ? miny : ny;
  maxy = (maxy > ny) ? maxy : ny;

  nx = (int)floor(w * cos_value - h * sin_value + 0.5);
  ny = (int)floor(w * sin_value + h * cos_value + 0.5);
  minx = (minx < nx) ? minx : nx;
  maxx = (maxx > nx) ? maxx : nx;
  miny = (miny < ny) ? miny : ny;
  maxy = (maxy > ny) ? maxy : ny;

  nw = maxx - minx;
  nh = maxy - miny;

  dib.CreateGrayImage(nw, nh, 0);

  BYTE** ptr1 = dib.GetPtr();
  BYTE** ptr2 = cpy.GetPtr();

  int x1, x2, y1, y2;
  double rx, ry, p, q, temp;

  for (register int row = miny; row < maxy; row++)
  {
    for (register int col = minx; col < maxx; col++)
    {
      rx = col * cos_value + row * sin_value;
      ry = -col * sin_value + row * cos_value;

      if (rx < 0 || rx > w-1 || ry < 0 || ry > h-1) continue;

      x1 = (int)rx;
      y1 = (int)ry;

      x2 = x1 + 1;
      if (x2 == w) x2 = w - 1;
      y2 = y1 + 1;
      if (y2 == h) y2 = h - 1;

      p = rx - x1;
      q = ry - y1;

      temp =
        (1.0 - p) * (1.0 - q) * ptr2[y1][x1] +
        p * (1.0 - q) * ptr2[y1][x2] +
        (1.0 - p) * q * ptr2[y2][x1] +
        p * q * ptr2[y2][x2];

      ptr1[row - miny][col - minx] = (BYTE)limit(temp);
    }
  }
}

void DibRotate90(CDib &dib)
{
  int w = dib.GetWidth();
  int h = dib.GetHeight();

  CDib cpy = dib;

  dib.CreateGrayImage(h, w);

  BYTE** ptr1 = dib.GetPtr();
  BYTE** ptr2 = cpy.GetPtr();

  for (register int row = 0; row < w; row++)
  {
    for (register int col = 0; col < h; col++)
    {
      ptr1[row][col] = ptr2[h - 1 - col][row];
    }
  }
}

void DibRotate180(CDib &dib)
{
  int w = dib.GetWidth();
  int h = dib.GetHeight();

  CDib cpy = dib;

  dib.CreateGrayImage(h, w);

  BYTE** ptr1 = dib.GetPtr();
  BYTE** ptr2 = cpy.GetPtr();

  for (register int row = 0; row < h; row++)
  {
    for (register int col = 0; col < w; col++)
    {
      ptr1[row][col] = ptr2[h - 1 - row][w - 1 - col];
    }
  }
}

void DibRotate270(CDib &dib)
{
  int w = dib.GetWidth();
  int h = dib.GetHeight();

  CDib cpy = dib;

  dib.CreateGrayImage(h, w);

  BYTE** ptr1 = dib.GetPtr();
  BYTE** ptr2 = cpy.GetPtr();

  for (register int row = 0; row < w; row++)
  {
    for (register int col = 0; col < h; col++)
    {
      ptr1[row][col] = ptr2[col][w - 1 - row];
    }
  }
}

void DibMirror(CDib &dib)
{
  int w = dib.GetWidth();
  int h = dib.GetHeight();

  CDib cpy = dib;

  dib.CreateGrayImage(w, h);

  BYTE** ptr1 = dib.GetPtr();
  BYTE** ptr2 = cpy.GetPtr();

  for (register int row = 0; row < h; row++)
  {
    for (register int col = 0; col < w; col++)
    {
      ptr1[row][col] = ptr2[row][w - 1 - col];
    }
  }
}

void DibFlip(CDib &dib)
{
  int w = dib.GetWidth();
  int h = dib.GetHeight();

  CDib cpy = dib;

  dib.CreateGrayImage(w, h);

  BYTE** ptr1 = dib.GetPtr();
  BYTE** ptr2 = cpy.GetPtr();

  for (register int row = 0; row < h; row++)
  {
    for (register int col = 0; col < w; col++)
    {
      ptr1[row][col] = ptr2[h - 1 - row][col];
    }
  }
}