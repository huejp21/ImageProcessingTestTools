#pragma once

#define MAX_CORNER 5000

typedef struct _CornerPoints
{
  int num = 0;
  int x[MAX_CORNER];
  int y[MAX_CORNER];
} CornerPoints;

typedef struct _LineParam
{
  double rho = 0;
  double ang = 0;
} LineParam;

void DibFilterMean(CDib &dib);
void DibFilterWeightedMean(CDib &dib);
void DibFilterGaussian(CDib &dib, double sigma);
void DibFilterUnsharpMask(CDib &dib);
void DibFilterLaplacian(CDib &dib);
void DibNoiseGaussian(CDib &dib, int amount);
double GaussianRand(double mean, double standard);
void DibNoiseSaltNPepper(CDib &dib, int amount);
void DibFilterMedian(CDib &dib);
void DibInsertSort(int *d, int n);
void DibFilterDiffusion(CDib &dib, float lambda, float k, int iter);
void DibEdgeRoberts(CDib &dib);
void DibEdgePrewitt(CDib &dib);
void DibEdgeSobel(CDib &dib);
LineParam DibHoughLine(CDib &dib);
void DibDrawLine(CDib &dib, LineParam line, BYTE c);
void DibDrawLine(CDib &dib, int x1, int y1, int x2, int y2, BYTE c);
CornerPoints DibHarrisCorner(CDib &dib, double th);