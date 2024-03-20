#include "stdafx.h"
#include "Dib.h"
#include "DibFilter.h"

void DibFilterMean(CDib &dib)
{
  int w = dib.GetWidth();
  int h = dib.GetHeight();

  CDib cpy = dib;

  BYTE** ptr1 = dib.GetPtr();
  BYTE** ptr2 = cpy.GetPtr();

  int temp;
  for (register int row = 1; row < h-1; row++)
  {
    for (register int col = 1; col < w-1; col++)
    {
      temp = 
        ptr2[row - 1][col - 1] + 
        ptr2[row - 1][col] + 
        ptr2[row - 1][col + 1] + 
        ptr2[row][col - 1] + 
        ptr2[row][col] + 
        ptr2[row][col + 1] + 
        ptr2[row + 1][col - 1] + 
        ptr2[row + 1][col] + 
        ptr2[row + 1][col + 1];

      ptr1[row][col] = (BYTE)limit(temp / 9. + 0.5);
    }
  }
}

void DibFilterWeightedMean(CDib &dib)
{
  int w = dib.GetWidth();
  int h = dib.GetHeight();

  CDib cpy = dib;

  BYTE** ptr1 = dib.GetPtr();
  BYTE** ptr2 = cpy.GetPtr();

  int temp;
  for (register int row = 1; row < h - 1; row++)
  {
    for (register int col = 1; col < w - 1; col++)
    {
      temp = 
        ptr2[row - 1][col - 1] + 
        2 * ptr2[row - 1][col] + 
        ptr2[row - 1][col + 1] + 
        2 * ptr2[row][col - 1] + 
        4 * ptr2[row][col] + 
        2 * ptr2[row][col + 1] + 
        ptr2[row + 1][col - 1] + 
        2 * ptr2[row + 1][col] + 
        ptr2[row + 1][col + 1];

      ptr1[row][col] = (BYTE)limit(temp / 16. + 0.5);
    }
  }
}

void DibFilterGaussian(CDib &dib, double sigma)
{
  register int x;
  int w = dib.GetWidth();
  int h = dib.GetHeight();
  BYTE** ptr = dib.GetPtr();

  //create one dimension
  int dim = (int)max(3.0, 2 * 4 * sigma + 1.0); 
  if (dim % 2 == 0) dim++; 
  int dim2 = (int)dim / 2;
  double* pMask = new double[dim];
  for (register int i = 0; i < dim; i++)
  {
    x = i - dim2;
    pMask[i] = exp(-(x*x) / (2 * sigma*sigma)) / (sqrt(2 * PI)*sigma);
  }

  //save in temporarily Buffer
  double** buffer = new double*[h];
  for (register int i = 0; i < h; i++)
  {
    buffer[i] = new double[w];
    memset(buffer[i], 0, sizeof(double)*w);
  }

  //Vertival Convolution
  double sum1, sum2;
  for (register int col = 0; col < w; col++)
  {
    for (register int row = 0; row < h; row++)
    {
      sum1 = sum2 = 0.0;
      for (register int i = 0; i < dim; i++)
      {
        x = i - dim2 + row;

        if (x >= 0 && x < h)
        {
          sum1 += pMask[i];
          sum2 += (pMask[i] * ptr[x][col]);
        }
      }
      buffer[row][col] = (sum2 / sum1);
    }
  }

  //Horizontal Convolution
  for (register int row = 0; row < h; row++)
  {
    for (register int col = 0; col < w; col++)
    {
      sum1 = sum2 = 0.0;

      for (register int i = 0; i < dim; i++)
      {
        x = i - dim2 + col;
        if (x >= 0 && x < w)
        {
          sum1 += pMask[i];
          sum2 += (pMask[i] * buffer[row][x]);
        }
      }
      ptr[row][col] = (BYTE)limit(sum2 / sum1);
    }
  }

  //delete
  delete[] pMask;
  for (register int i = 0; i < h; i++)
  {
    delete[] buffer[i];
  }
  delete[] buffer;
}

void DibFilterUnsharpMask(CDib &dib)
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
      ptr1[row][col] = (BYTE)limit(
        5 * ptr2[row][col] -
        ptr2[row - 1][col] -
        ptr2[row][col - 1] -
        ptr2[row + 1][col] -
        ptr2[row][col + 1]
        );
    }
  }
}

void DibFilterLaplacian(CDib &dib)
{
  int w = dib.GetWidth();
  int h = dib.GetHeight();

  CDib cpy = dib;
  BYTE** ptr1 = dib.GetPtr();
  BYTE** ptr2 = cpy.GetPtr();
  int temp;

  for (register int row = 1; row < h - 1; row++)
  {
    for (register int col = 1; col < w - 1; col++)
    {
      temp =
        4 * ptr2[row][col] -
        ptr2[row - 1][col] -
        ptr2[row][col + 1] -
        ptr2[row + 1][col] -
        ptr2[row][col - 1];

      ptr1[row][col] = (BYTE)limit(temp);
    }
  }
}

void DibNoiseGaussian(CDib &dib, int amount)
{
  int w = dib.GetWidth();
  int h = dib.GetHeight();

  BYTE** ptr = dib.GetPtr();

  srand((unsigned)time(NULL));
  double random;
  for (register int row = 0; row < h; row++)
  {
    for (register int col = 0; col < w; col++)
    {
      random = GaussianRand(0, amount);
      ptr[row][col] = (BYTE)limit(ptr[row][col] + random);
    }
  }
}

double GaussianRand(double mean, double standard)
{
  double x1, x2, radius, factor, y1;
  static double y2;
  static int use_last = 0;

  if (use_last)
  {
    y1 = y2;
    use_last = 0;
  }
  else
  {
    do
    {
      x1 = 2.0 * rand() / RAND_MAX - 1.0;
      x2 = 2.0 * rand() / RAND_MAX - 1.0;
      radius = x1 * x1 + x2 * x2;
    } while (radius < 0.00000001 || radius >= 1.0);

    factor = sqrt((-2.0 * log(radius)) / radius);
    y1 = x1 * factor;
    y2 = x2 * factor;

    use_last = 1;
  }
  return (mean + y1 * standard);
}

void DibNoiseSaltNPepper(CDib &dib, int amount)
{
  int w = dib.GetWidth();
  int h = dib.GetHeight();

  BYTE** ptr = dib.GetPtr();

  srand((unsigned)time(NULL));

  int random;

  for (register int row = 0; row < h; row++)
  {
    for (register int col = 0; col < w; col++)
    {
      random = (int)(rand() * 100 / RAND_MAX);
      if (random < amount / 2)
      {
        ptr[row][col] = 0;
      }
      else if (random < amount)
      {
        ptr[row][col] = 255;
      }
    }
  }
}

void DibFilterMedian(CDib &dib)
{
  int w = dib.GetWidth();
  int h = dib.GetHeight();

  CDib cpy = dib;
  BYTE** ptr1 = dib.GetPtr();
  BYTE** ptr2 = cpy.GetPtr();

  int m[9];
  for (register int row = 1; row < h - 1; row++)
  {
    for (register int col = 1; col < w - 1; col++)
    {
      m[0] = ptr2[row - 1][col - 1];
      m[1] = ptr2[row - 1][col];
      m[2] = ptr2[row - 1][col + 1];
      m[3] = ptr2[row][col - 1];
      m[4] = ptr2[row][col];
      m[5] = ptr2[row][col + 1];
      m[6] = ptr2[row + 1][col - 1];
      m[7] = ptr2[row + 1][col];
      m[8] = ptr2[row + 1][col + 1];

      DibInsertSort(m, 9);
      ptr1[row][col] = (BYTE)m[4];
    }
  }
}

void DibInsertSort(int *d, int n)
{
  int temp;
  register int j;
  for (register int i = 0; i < n; i++)
  {
    temp = d[i];
    j = i - 1;
    while (j > -1 && d[j] > temp)
    {
      d[j + 1] = d[j];
      j--;
    }
    d[j + 1] = temp;
  }
}

void DibFilterDiffusion(CDib &dib, float lambda, float k, int iter)
{
  int w = dib.GetWidth();
  int h = dib.GetHeight();

  BYTE** ptr = dib.GetPtr();

  float k2 = k * k;

  float gradn, grads, grade, gradw;
  float gcn, gcs, gce, gcw;
  float temp;

  float** cpy = new float*[h];
  for (register int row = 0; row < h; row++)
  {
    cpy[row] = new float[w];
    memset(cpy[row], 0, sizeof(float) * w);
  }

  float** buffer = new float*[h];
  for (register int row = 0; row < h; row++)
  {
    buffer[row] = new float[w];
    memset(buffer[row], 0, sizeof(float) * w);
  }

  for (register int row = 0; row < h; row++)
  {
    for (register int col = 0; col < w; col++)
    {
      cpy[row][col] = buffer[row][col] = (float)ptr[row][col];
    }
  }

  for (register int i = 0; i < iter; i++)
  {
    for (register int row = 1; row < h - 1; row++)
    {
      for (register int col = 0; col < w - 1; col++)
      {
        temp = cpy[row][col];

        gradn = cpy[row - 1][col] - temp;
        grads = cpy[row + 1][col] - temp;
        grade = cpy[row][col - 1] - temp;
        gradw = cpy[row][col + 1] - temp;

        gcn = gradn / (1.0f + gradn * gradn / k2);
        gcs = grads / (1.0f + grads * grads / k2);
        gce = grade / (1.0f + grade * grade / k2);
        gcw = gradw / (1.0f + gradw * gradw / k2);

        buffer[row][col] = cpy[row][col] + lambda * (gcn + gcs + gce + gcw);
      }
    }
    for (register int row = 0; row < h; row++)
    {
      memcpy(cpy[row], buffer[row], sizeof(float) * w);
    }
  }

  for (register int row = 0; row < h; row++)
  {
    delete[]buffer[row];
    delete[]cpy[row];
  }
  delete[]buffer;
  delete[]cpy;
}

void DibEdgeRoberts(CDib &dib)
{
  int w = dib.GetWidth();
  int h = dib.GetHeight();

  CDib cpy = dib;
  dib.CreateGrayImage(w, h, 0);

  BYTE** ptr1 = dib.GetPtr();
  BYTE** ptr2 = cpy.GetPtr();

  int h1, h2;
  double hval;
  for (register int row = 1; row < h - 1; row++)
  {
    for (register int col = 1; col < w - 1; col++)
    {
      h1 = ptr2[row][col] - ptr2[row - 1][col - 1];
      h2 = ptr2[row][col] - ptr2[row - 1][col + 1];

      hval = sqrt((double)h1 * h1 + h2 * h2);

      ptr1[row][col] = (BYTE)limit(hval);
    }
  }
}

void DibEdgePrewitt(CDib &dib)
{
  int w = dib.GetWidth();
  int h = dib.GetHeight();

  CDib cpy = dib;
  dib.CreateGrayImage(w, h, 0);

  BYTE** ptr1 = dib.GetPtr();
  BYTE** ptr2 = cpy.GetPtr();

  int h1, h2;
  double hval;
  for (register int row = 1; row < h - 1; row++)
  {
    for (register int col = 1; col < w - 1; col++)
    {
      h1 =
        - ptr2[row - 1][col - 1]
        - ptr2[row - 1][col]
        - ptr2[row - 1][col + 1]
        + ptr2[row + 1][col - 1]
        + ptr2[row + 1][col]
        + ptr2[row + 1][col + 1];

      h2 = 
        - ptr2[row - 1][col - 1]
        - ptr2[row][col - 1]
        - ptr2[row + 1][col - 1]
        + ptr2[row - 1][col + 1]
        + ptr2[row][col + 1]
        + ptr2[row + 1][col + 1];

      hval = sqrt((double)h1 * h1 + h2 * h2);

      ptr1[row][col] = (BYTE)limit(hval);
    }
  }
}

void DibEdgeSobel(CDib &dib)
{
  int w = dib.GetWidth();
  int h = dib.GetHeight();

  CDib cpy = dib;
  dib.CreateGrayImage(w, h, 0);

  BYTE** ptr1 = dib.GetPtr();
  BYTE** ptr2 = cpy.GetPtr();

  int h1, h2;
  double hval;
  for (register int row = 1; row < h - 1; row++)
  {
    for (register int col = 1; col < w - 1; col++)
    {
      h1 =
        - ptr2[row - 1][col - 1]
        - 2 * ptr2[row - 1][col]
        - ptr2[row - 1][col + 1]
        + ptr2[row + 1][col - 1]
        + 2 * ptr2[row + 1][col]
        + ptr2[row + 1][col + 1];

      h2 =
        - ptr2[row - 1][col - 1]
        - 2 * ptr2[row][col - 1]
        - ptr2[row + 1][col - 1]
        + ptr2[row - 1][col + 1]
        + 2 * ptr2[row][col + 1]
        + ptr2[row + 1][col + 1];

      hval = sqrt((double)h1 * h1 + h2 * h2);

      ptr1[row][col] = (BYTE)limit(hval);
    }
  }
}

LineParam DibHoughLine(CDib& dib)
{
  int w = dib.GetWidth();
  int h = dib.GetHeight();

  BYTE** ptr = dib.GetPtr();

  int num_rho = (int)(sqrt((double)w*w + h*h) * 2);
  int num_ang = 360;

  double* tsin = new double[num_ang];
  double* tcos = new double[num_ang];

  for (register int i = 0; i < num_ang; i++)
  {
    tsin[i] = (double)sin(i*PI / num_ang);
    tcos[i] = (double)cos(i*PI / num_ang);
  }

  int** arr = new int*[num_rho];
  for (register int i = 0; i < num_rho; i++)
  {
    arr[i] = new int[num_ang];
    memset(arr[i], 0, sizeof(int)*num_ang);
  }

  int m, n;
  for (register int row = 0; row < h; row++)
  {
    for (register int col = 0; col < w; col++)
    {
      if (ptr[row][col] > 128)
      {
        for (n = 0; n<num_ang; n++)
        {
          m = (int)floor(col * tsin[n] + row * tcos[n] + 0.5);
          m += (num_rho / 2);

          arr[m][n]++;
        }
      }
    }
  }

  LineParam line;
  line.rho = line.ang = 0;

  int arr_max = 0;
  for (m = 0; m<num_rho; m++)
  {
    for (n = 0; n<num_ang; n++)
    {
      if (arr[m][n] > arr_max)
      {
        arr_max = arr[m][n];
        line.rho = m - (num_rho / 2);
        line.ang = n*180.0 / num_ang;
      }
    }
  }

  delete[] tsin;
  delete[] tcos;

  for (register int i = 0; i < num_rho; i++)
    delete[] arr[i];
  delete[] arr;

  return line;
}

void DibDrawLine(CDib& dib, LineParam line, BYTE c)
{
  register int x, y;

  int w = dib.GetWidth();
  int h = dib.GetHeight();

  BYTE** ptr = dib.GetPtr();

  if (line.ang == 90)
  {
    x = (int)(line.rho + 0.5);

    for (y = 0; y < h; y++)
    {
      ptr[y][x] = c;
    }

    return;
  }

  int x1 = 0;
  int y1 = (int)floor(line.rho / cos(line.ang*PI / 180) + 0.5);
  int x2 = dib.GetWidth() - 1;
  int y2 = (int)floor((line.rho - x2*sin(line.ang*PI / 180)) / cos(line.ang*PI / 180) + 0.5);

  DibDrawLine(dib, x1, y1, x2, y2, c);
}

void DibDrawLine(CDib& dib, int x1, int y1, int x2, int y2, BYTE c)
{
  register int x, y;
  double m;

  int w = dib.GetWidth();
  int h = dib.GetHeight();

  BYTE** ptr = dib.GetPtr();

  if (x1 == x2)
  {
    if (y1 > y2)
    {
      swap(y1, y2);
    }

    for (y = y1; y <= y2; y++)
    {
      ptr[y][x1] = c;
    }

    return;
  }
  m = (double)(y2 - y1) / (x2 - x1);

  if ((m > -1) && (m < 1))
  {
    if (x1 > x2)
    {
      swap(x1, x2);
      swap(y1, y2);
    }

    for (x = x1; x <= x2; x++)
    {
      y = (int)floor(m*(x - x1) + y1 + 0.5);
      if (y >= 0 && y < h)
      {
        ptr[y][x] = c;
      }
    }
  }
  else
  {
    if (y1 > y2)
    {
      swap(x1, x2);
      swap(y1, y2);
    }

    for (y = y1; y <= y2; y++)
    {
      x = (int)floor((y - y1) / m + x1 + 0.5);
      if (y >= 0 && y < h)
      {
        ptr[y][x] = c;
      }
    }
  }
}

CornerPoints DibHarrisCorner(CDib &dib, double th)
{
  int w = dib.GetWidth();
  int h = dib.GetHeight();

  BYTE** ptr = dib.GetPtr();

  double** dx2 = new double*[h];
  double** dy2 = new double*[h];
  double** dxy = new double*[h];

  for (register int i = 0; i < h; i++)
  {
    dx2[i] = new double[w];
    dy2[i] = new double[w];
    dxy[i] = new double[w];
    memset(dx2[i], 0, sizeof(int) * w);
    memset(dy2[i], 0, sizeof(int) * w);
    memset(dxy[i], 0, sizeof(int) * w);
  }

  double tx, ty;
  for (register int row = 1; row < h -1; row++)
  {
    for (register int col = 1; col < w - 1; col++)
    {
      tx = (
        ptr[row - 1][col + 1]
        + ptr[row][col + 1]
        + ptr[row + 1][col + 1]
        - ptr[row - 1][col - 1]
        - ptr[row][col - 1]
        - ptr[row + 1][col - 1]
        ) / 6.0;

      ty = (
        ptr[row + 1][col - 1]
        + ptr[row + 1][col]
        + ptr[row + 1][col + 1]
        - ptr[row - 1][col - 1]
        - ptr[row - 1][col]
        - ptr[row - 1][col + 1]
        ) / 6.0;

      dx2[row][col] = tx * tx;
      dy2[row][col] = ty * ty;
      dxy[row][col] = tx * ty;
    }
  }

  double** gdx2 = new double*[h];
  double** gdy2 = new double*[h];
  double** gdxy = new double*[h];

  for (register int i = 0; i < h; i++)
  {
    gdx2[i] = new double[w];
    gdy2[i] = new double[w];
    gdxy[i] = new double[w];
    memset(gdx2[i], 0, sizeof(int) * w);
    memset(gdy2[i], 0, sizeof(int) * w);
    memset(gdxy[i], 0, sizeof(int) * w);
  }

  double g[5][5] = 
  {
    { 1, 4, 6, 4, 1 },
    { 4, 16, 24, 16, 24 },
    { 6, 24, 36, 24, 6 },
    { 4, 16, 24, 16, 24 },
    { 1, 4, 6, 4, 1 }
  };

  for (register int y = 0; y < 5; y++)
  {
    for (register int x = 0; x < 5; x++)
    {
      g[y][x] /= 256;
    }
  }

  double tx2, ty2, txy;
  for (register int row = 2; row < h - 2; row++)
  {
    for (register int col = 2; col < w - 2; col++)
    {
      tx2 = ty2 = txy = 0;
      for (register int y = 0; y < 5; y++)
      {
        for (register int x = 0; x < 5; x++)
        {
          tx2 += (dx2[row + y - 2][col + x - 2] * g[y][x]);
          ty2 += (dy2[row + y - 2][col + x - 2] * g[y][x]);
          txy += (dxy[row + y - 2][col + x - 2] * g[y][x]);
        }
      }
      gdx2[row][col] = tx2;
      gdy2[row][col] = ty2;
      gdxy[row][col] = txy;
    }
  }

  double** crf = new double*[h];
  for (register int i = 0; i < h; i++)
  {
    crf[i] = new double[w];
    memset(crf[i], 0, sizeof(double) * w);
  }

  double k = 0.04;
  for (register int row = 2; row < h - 2; row++)
  {
    for (register int col = 2; col < w - 2; col++)
    {
      crf[row][col] = (gdx2[row][col] * gdy2[row][col] - gdxy[row][col] * gdxy[row][col])
        - k * (gdx2[row][col] + gdy2[row][col]) * (gdx2[row][col] + gdy2[row][col]);
    }
  }

  CornerPoints cp;
  cp.num = 0;
  for (register int row = 2; row < h - 2; row++)
  {
    for (register int col = 2; col < w - 2; col++)
    {
      if (crf[row][col] > th)
      {
        if (
          crf[row][col] > crf[row - 1][col] &&
          crf[row][col] > crf[row - 1][col + 1] &&
          crf[row][col] > crf[row][col + 1] &&
          crf[row][col] > crf[row + 1][col + 1] &&
          crf[row][col] > crf[row + 1][col] &&
          crf[row][col] > crf[row + 1][col - 1] &&
          crf[row][col] > crf[row][col - 1] &&
          crf[row][col] > crf[row - 1][col - 1]
          )
        {
          if (cp.num < MAX_CORNER)
          {
            cp.x[cp.num] = col;
            cp.y[cp.num] = row;
            cp.num++;
          }
        }
      }
    }
  }

  for (register int i = 0; i < h; i++)
  {
    delete[]dx2[i];
    delete[]dy2[i];
    delete[]dxy[i];
    delete[]gdx2[i];
    delete[]gdy2[i];
    delete[]gdxy[i];
    delete[]crf[i];
  }
  delete[]dx2;
  delete[]dy2;
  delete[]dxy;
  delete[]gdx2;
  delete[]gdy2;
  delete[]gdxy;
  delete[]crf;

  return cp;
}


