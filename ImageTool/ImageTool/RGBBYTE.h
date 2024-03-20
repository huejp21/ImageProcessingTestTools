#pragma once
class RGBBYTE
{
public:
  BYTE b;
  BYTE g;
  BYTE r;
public:
  RGBBYTE(const BYTE &pixel = 0);
  RGBBYTE(const BYTE &_r, const BYTE &_g, const BYTE &_b);
  RGBBYTE(const RGBBYTE &pixel);
  ~RGBBYTE();

public:
  RGBBYTE &operator=(const RGBBYTE &pixel);
  RGBBYTE &operator=(const COLORREF &pixel);
  RGBBYTE &operator=(const BYTE &pixel);

  int operator==(const RGBBYTE &pixel);
  int operator!=(const RGBBYTE &pixel);
};

