#include "stdafx.h"
#include "Dib.h"
#include "DibSegment.h"
#include "DibEnhancement.h"
#include "DibFourier.h"

void DibBinarization(CDib &dib, int th)
{
  int w = dib.GetWidth();
  int h = dib.GetHeight();

  BYTE** ptr = dib.GetPtr();

  for (register int row = 0; row < h; row++)
  {
    for (register int col = 0; col < w; col++)
    {
      ptr[row][col] = (ptr[row][col] > th) ? 255 : 0;
    }
  }
}

int DibBinarizationIterative(CDib &dib)
{
  int w = dib.GetWidth();
  int h = dib.GetHeight();

  float hist[256] = { 0, };

  DibHistogram(dib, hist);

  int T, Told;

  float sum = 0.f;
  for (register int i = 0; i < 256; i++)
  {
    sum += (i * hist[i]);
  }

  T = (int)sum;

  float a1, b1, u1, a2, b2, u2;

  do
  {
    Told = T;
    a1 = b1 = 0;
    for (register int i = 0; i <= Told; i++)
    {
      a1 += (i * hist[i]);
      b1 += hist[i];
    }
    u1 = a1 / b1;

    a2 = b2 = 0;
    for (register int i = Told + 1; i < 256; i++)
    {
      a2 += (i * hist[i]);
      b2 += hist[i];
    }
    u2 = a2 / b2;

    if (b1 == 0) b1 = 1.f;
    if (b2 == 0) b2 = 1.f;

    T = (int)((u1 + u2) / 2);
  } while (T != Told);

  return T;
}

int DibLabeling(CDib& dib)
{
  int w = dib.GetWidth();
  int h = dib.GetHeight();

  BYTE** ptr = dib.GetPtr();

  //------------------------------------------------------------------------- 
  // 임시로 레이블을 저장할 메모리 공간과 등가 테이블 생성 
  //------------------------------------------------------------------------- 

  int** map = new int*[h];
  for (register int i = 0; i < h; i++)
  {
    map[i] = new int[w];
    memset(map[i], 0, sizeof(int)*w);
  }

  int eq_tbl[MAX_LABEL][2] = { { 0, }, };

  //------------------------------------------------------------------------- 
  // 첫 번째 스캔 - 초기 레이블 지정 및 등가 테이블 생성 
  //------------------------------------------------------------------------- 

  int label = 0, maxl, minl, min_eq, max_eq;

  for (register int row = 1; row < h; row++)
    for (register int col = 1; col < w; col++)
    {
      if (ptr[row][col] != 0)
      {
        // 바로 위 픽셀과 왼쪽 픽셀 모두에 레이블이 존재하는 경우 
        if ((map[row - 1][col] != 0) && (map[row][col - 1] != 0))
        {
          if (map[row - 1][col] == map[row][col - 1])
          {
            // 두 레이블이 서로 같은 경우 
            map[row][col] = map[row - 1][col];
          }
          else
          {
            // 두 레이블이 서로 다른 경우, 작은 레이블을 부여 
            maxl = max(map[row - 1][col], map[row][col - 1]);
            minl = min(map[row - 1][col], map[row][col - 1]);

            map[row][col] = minl;

            // 등가 테이블 조정 
            min_eq = min(eq_tbl[maxl][1], eq_tbl[minl][1]);
            max_eq = max(eq_tbl[maxl][1], eq_tbl[minl][1]);

            eq_tbl[eq_tbl[max_eq][1]][1] = min_eq;
          }
        }
        else if (map[row - 1][col] != 0)
        {
          // 바로 위 픽셀에만 레이블이 존재할 경우 
          map[row][col] = map[row - 1][col];
        }
        else if (map[row][col - 1] != 0)
        {
          // 바로 왼쪽 픽셀에만 레이블이 존재할 경우 
          map[row][col] = map[row][col - 1];
        }
        else
        {
          // 이웃에 레이블이 존재하지 않으면 새로운 레이블을 부여 
          label++;
          map[row][col] = label;
          eq_tbl[label][0] = label;
          eq_tbl[label][1] = label;
        }
      }
    }

  //------------------------------------------------------------------------- 
  // 등가 테이블 정리 
  //------------------------------------------------------------------------- 

  int temp;
  for (register int i = 1; i <= label; i++)
  {
    temp = eq_tbl[i][1];
    if (temp != eq_tbl[i][0])
      eq_tbl[i][1] = eq_tbl[temp][1];
  }

  // 등가 테이블의 레이블을 1부터 차례대로 증가시키기 

  int* hash = new int[label + 1];
  memset(hash, 0, sizeof(int)*(label + 1));

  for (register int i = 1; i <= label; i++)
    hash[eq_tbl[i][1]] = eq_tbl[i][1];

  int cnt = 1;
  for (register int i = 1; i <= label; i++)
    if (hash[i] != 0)
      hash[i] = cnt++;

  for (register int i = 1; i <= label; i++)
    eq_tbl[i][1] = hash[eq_tbl[i][1]];

  delete[] hash;

  //------------------------------------------------------------------------- 
  // 두 번째 스캔 - 등가 테이블을 이용하여 모든 픽셀에 고유의 레이블 부여 
  //------------------------------------------------------------------------- 

  dib.CreateGrayImage(w, h, 0);
  ptr = dib.GetPtr();

  for (register int row = 1; row < h; row++)
    for (register int col = 1; col < w; col++)
    {
      if (map[row][col] != 0)
      {
        temp = map[row][col];
        ptr[row][col] = (BYTE)(eq_tbl[temp][1]);
      }
    }

  //------------------------------------------------------------------------- 
  // 임시 메모리 공간 해제 
  //------------------------------------------------------------------------- 

  for (register int i = 0; i < h; i++)
    delete[] map[i];
  delete[] map;

  return (cnt - 1);
}

ContourPoints DibContourTracing(CDib& dib)
{
  int w = dib.GetWidth();
  int h = dib.GetHeight();

  BYTE** ptr = dib.GetPtr();

  int x, y, nx, ny;
  int dold, d, cnt;
  int dir[8][2] = { // 진행 방향을 나타내는 배열
    { 1, 0 },
    { 1, 1 },
    { 0, 1 },
    { -1, 1 },
    { -1, 0 },
    { -1, -1 },
    { 0, -1 },
    { 1, -1 },
  };

  // 외곽선 좌표를 저장할 구조체
  ContourPoints cp;
  cp.num = 0;

  for (register int row = 0; row < h; row++)
  {
    for (register int col = 0; col < w; col++)
    {
      if (ptr[row][col] != 0)
      {
        x = col;
        y = row;

        dold = d = cnt = 0;

        while (1)
        {
          nx = x + dir[d][0];
          ny = y + dir[d][1];

          if (nx < 0 || nx >= w || ny < 0 || ny >= h || ptr[ny][nx] == 0)
          {
            // 진행 방향에 있는 픽셀이 객체가 아닌 경우,
            // 시계방향으로 진행방향을 바꾸고 다시 시도한다.

            if (++d > 7) d = 0;
            cnt++;

            // 8방향 모두 배경인 경우
            if (cnt >= 8)
            {
              cp.x[cp.num] = x;
              cp.y[cp.num] = y;
              cp.num++;

              break; // 추적 끝냄.
            }
          }
          else
          {
            // 진행 방향에 있는 픽셀이 객체인 경우,
            // 현재 점을 외곽선 정보에 저장

            cp.x[cp.num] = x;
            cp.y[cp.num] = y;
            cp.num++;

            if (cp.num >= MAX_CONTOUR)
            {
              break; // 외곽선 픽셀이 너무 많으면 강제 종료.
            }

            // 진행방향으로 이동
            x = nx;
            y = ny;

            // 방향 정보 초기화.
            cnt = 0;
            dold = d;
            d = (dold + 6) % 8;
          }

          // 시작점으로 돌아왔고, 진행방향이 초기화된 경우
          // 외곽선 추적 끝냄.
          if (x == col && y == row && d == 0)
          {
            break;
          }
        }

        // for루프를 강제로 종료하기 위해 i, j값을 조정.
        col = w; row = h;
      }
    }
  }
  return cp;
}

void DibMorphologyErosion(CDib &dib)
{
  int w = dib.GetWidth();
  int h = dib.GetHeight();

  CDib cpy = dib;

  BYTE** ptr1 = dib.GetPtr();
  BYTE** ptr2 = cpy.GetPtr();

  for (register int row = 1; row < h -1; row++)
  {
    for (register int col = 1; col < w - 1; col++)
    {
      if (ptr2[row][col] != 0)
      {
        if (
          ptr2[row - 1][col - 1] == 0 ||
          ptr2[row - 1][col] == 0 ||
          ptr2[row - 1][col + 1] == 0 ||
          ptr2[row][col - 1] == 0 ||
          ptr2[row][col + 1] == 0 ||
          ptr2[row + 1][col - 1] == 0 ||
          ptr2[row + 1][col] == 0 ||
          ptr2[row + 1][col + 1] == 0
          )
        {
          ptr1[row][col] = 0;
        }
      }
    }
  }
}

void DibMorphologyDilation(CDib &dib)
{
  int w = dib.GetWidth();
  int h = dib.GetHeight();

  CDib cpy = dib;

  BYTE** ptr1 = dib.GetPtr();
  BYTE** ptr2 = cpy.GetPtr();

  for (register int row = 1; row < h - 1; row++)
  {
    for (register int col = 1; col < w - 1; col++)
    {
      if (ptr2[row][col] == 0)
      {
        if (
          ptr2[row - 1][col - 1] != 0 ||
          ptr2[row - 1][col] != 0 ||
          ptr2[row - 1][col + 1] != 0 ||
          ptr2[row][col - 1] != 0 ||
          ptr2[row][col + 1] != 0 ||
          ptr2[row + 1][col - 1] != 0 ||
          ptr2[row + 1][col] != 0 ||
          ptr2[row + 1][col + 1] != 0
          )
        {
          ptr1[row][col] = 255;
        }
      }
    }
  }
}

void DibMorphologyGrayErosion(CDib &dib)
{
  int w = dib.GetWidth();
  int h = dib.GetHeight();

  CDib cpy = dib;

  BYTE** ptr1 = dib.GetPtr();
  BYTE** ptr2 = cpy.GetPtr();

  int x, y, pmin;
  for (register int row = 0; row < h; row++)
  {
    for (register int col = 0; col < w; col++)
    {
      pmin = 255;
      for (register int n = -1; n <= 1; n++)
      {
        for (register int m = -1; m <= 1; m++)
        {
          x = col + m;
          y = row + n;

          if (x >= 0 && x < w && y >= 0 && y < h)
          {
            if (ptr2[y][x] < pmin)
            {
              pmin = ptr2[y][x];
            }
          }
        }
      }
      ptr1[row][col] = pmin;
    }
  }
}

void DibMorphologyGrayDilation(CDib &dib)
{
  int w = dib.GetWidth();
  int h = dib.GetHeight();

  CDib cpy = dib;

  BYTE** ptr1 = dib.GetPtr();
  BYTE** ptr2 = cpy.GetPtr();

  int x, y, pmax;
  for (register int row = 0; row < h; row++)
  {
    for (register int col = 0; col < w; col++)
    {
      pmax = 0;
      for (register int n = -1; n <= 1; n++)
      {
        for (register int m = -1; m <= 1; m++)
        {
          x = col + m;
          y = row + n;

          if (x >= 0 && x < w && y >= 0 && y < h)
          {
            if (ptr2[y][x] > pmax)
            {
              pmax = ptr2[y][x];
            }
          }
        }
      }
      ptr1[row][col] = pmax;
    }
  }
}

ContourPoints DibFourierDescriptor(CDib &dib, int nPercent)
{
  ContourPoints cp;
  cp = DibContourTracing(dib);

  int w = dib.GetWidth();
  int h = dib.GetHeight();

  int n = cp.num;

  double *x = new double[n];
  double *y = new double[n];

  for (register int i = 0; i < n; i++)
  {
    x[i] = (double)cp.x[i];
    y[i] = (double)cp.y[i];
  }

  DFT1d(x, y, n, 1);

  int p = n * nPercent / 100;
  for (register int i = p; i < n; i++)
  {
    x[i] = 0;
    y[i] = 0;
  }

  DFT1d(x, y, n, -1);

  for (register int i = 0; i < n; i++)
  {
    cp.x[i] = (int)(x[i] + 0.5);
    cp.y[i] = (int)(y[i] + 0.5);

    cp.x[i] = limit(cp.x[i], 0, w - 1);
    cp.y[i] = limit(cp.y[i], 0, h - 1);
  }

  delete[]x;
  delete[]y;

  return cp;
}

void DibInvariantMoments(CDib& dib, double m[7])
{
  double g00, g10, g01, g20, g02, g11, g30, g03, g21, g12;
  double c00, c20, c02, c11, c30, c03, c21, c12;
  double n20, n02, n11, n30, n03, n21, n12;

  // 기하학적 모멘트 구하기  

  g00 = DibGeometricMoment(dib, 0, 0);
  g10 = DibGeometricMoment(dib, 1, 0);
  g01 = DibGeometricMoment(dib, 0, 1);
  g20 = DibGeometricMoment(dib, 2, 0);
  g02 = DibGeometricMoment(dib, 0, 2);
  g11 = DibGeometricMoment(dib, 1, 1);
  g30 = DibGeometricMoment(dib, 3, 0);
  g03 = DibGeometricMoment(dib, 0, 3);
  g21 = DibGeometricMoment(dib, 2, 1);
  g12 = DibGeometricMoment(dib, 1, 2);

  // 중심 모멘트 구하기  

  double cx = g10 / g00;
  double cy = g01 / g00;

  c00 = g00;
  c20 = g20 - cx*g10;
  c02 = g02 - cy*g01;
  c11 = g11 - cx*g01;
  c30 = g30 - 3 * cx*g20 + 2 * cx*cx*g10;
  c03 = g03 - 3 * cy*g02 + 2 * cy*cy*g01;
  c21 = g21 - 2 * cx*g11 - cy*g20 + 2 * cx*cx*g01;
  c12 = g12 - 2 * cy*g11 - cx*g02 + 2 * cy*cy*g10;

  // 정규화된 중심 모멘트  

  n20 = c20 / pow(c00, 2.);
  n02 = c02 / pow(c00, 2.);
  n11 = c11 / pow(c00, 2.);
  n30 = c30 / pow(c00, 2.5);
  n03 = c03 / pow(c00, 2.5);
  n21 = c21 / pow(c00, 2.5);
  n12 = c12 / pow(c00, 2.5);

  // 불변 모멘트 구하기  

  m[0] = n20 + n02;
  m[1] = (n20 - n02)*(n20 - n02) + 4 * n11*n11;
  m[2] = (n30 - 3 * n12)*(n30 - 3 * n12) + (3 * n21 - n03)*(3 * n21 - n03);
  m[3] = (n30 + n12)*(n30 + n12) + (n21 + n03)*(n21 + n03);
  m[4] = (n30 - 3 * n12)*(n30 + n12)*((n30 + n12)*(n30 + n12) - 3 * (n21 + n03)*(n21 + n03)) + (3 * n21 - n03)*(n21 + n03)*(3 * (n30 + n12)*(n30 + n12) - (n21 + n03)*(n21 + n03));
  m[5] = (n20 - n02)*((n30 + n12)*(n30 + n12) - (n21 + n03)*(n21 + n03)) + 4 * n11*(n30 + n12)*(n21 + n03);
  m[6] = (3 * n21 - n03)*(n30 + n12)*((n30 + n12)*(n30 + n12) - 3 * (n21 + n03)*(n21 + n03)) + (3 * n12 - n30)*(n21 + n03)*(3 * (n30 + n12)*(n30 + n12) - (n21 + n03)*(n21 + n03));
}


double DibGeometricMoment(CDib& dib, int p, int q)
{


  int w = dib.GetWidth();
  int h = dib.GetHeight();

  BYTE** ptr = dib.GetPtr();

  double moment = 0, temp;

  for (register int row = 0; row < h; row++)
    for (register int col = 0; col < w; col++)
    {
      temp = 1;

      for (register int i = 0; i < p; i++)
      {
        temp *= col;
      }
      for (register int i = 0; i < q; i++)
      {
        temp *= row;
      }
      moment += (temp*ptr[row][col]);
    }

  return moment;
}
