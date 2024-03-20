#pragma once


void DibTranslate(CDib &dib, int sx, int sy);
void DibResizeNearest(CDib &dib, int nw, int nh);
void DibResizeBilinear(CDib &dib, int nw, int nh);
void DibResizeCubic(CDib &dib, int nw, int nh);
double cubic_interpolation(double v1, double v2, double v3, double v4, double d);