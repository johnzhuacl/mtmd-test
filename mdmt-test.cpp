// mdmt-test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <tchar.h>
#include <time.h>
#include <windows.h>
#include "AclDateConvert.h"
#include <mbctype.h>

void setLocaleToSystemDefault()
{
  int currentCodePage = GetACP();
  char codePage[10];
  codePage[0] = '.';
  _itoa(currentCodePage, &codePage[1], 10);
  setlocale(LC_CTYPE, codePage);
  _setmbcp(_MB_CP_LOCALE);
}

inline long long PerformanceCounter() noexcept
{
  LARGE_INTEGER li;
  ::QueryPerformanceCounter(&li);
  return li.QuadPart;
}
/***
  The calculcation is just to ensure optimization won't skip the string function call.
***/
double doTest() {
  TCHAR testData[100] = _T("12345678");
  long long total = 0;
  double dtotal = 0.0;
  for (__int64 i = 0; i < 10000000; i++)
  {

    TCHAR* index =  _tcsstr(testData, _T("4"));
    int in = (TCHAR*)index - testData;
    total += in;
    TCHAR* v = _tcscat(testData, _T(".90"));
    double dv = _tstof(testData);
    dtotal += dv;
    _tcscpy(testData, _T("12345678"));
  }
  return dtotal - total;
}
int main()
{
  double total = 0.0;
  long long  startTime = PerformanceCounter();
  total = doTest();
  long long endTime = PerformanceCounter();
  __int64 diff = endTime - startTime;
  printf("elapsed = %f, %f\n", diff/1000000.0, total);
  setLocaleToSystemDefault();

  total = doTest();
  long long endTime2 = PerformanceCounter();
  diff = endTime2 - endTime;
  printf("elapsed when locale set = %f, %f\n", diff / 1000000.0, total);
  return 0;
}
