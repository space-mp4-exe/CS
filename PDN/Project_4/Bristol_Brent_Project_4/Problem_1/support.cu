/******************************************************************************
 *cr
 *cr            (C) Copyright 2010 The Board of Trustees of the
 *cr                        University of Illinois
 *cr                         All Rights Reserved
 *cr
 ******************************************************************************/

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "support.h"

void verify(float *A, float *B, float *C, int n) {

  const float relativeTolerance = 1e-6;

  for(int i = 0; i < n; i++) {
    float sum = A[i] + B[i];
    float relativeError = (sum - C[i])/sum;
    if (relativeError > relativeTolerance
      || relativeError < -relativeTolerance) {
      printf("TEST FAILED\n\n");
      exit(0);
    }
  }
  printf("TEST PASSED\n\n");

}

void startTime(Timer* timer) {
  #ifdef _WIN32
    QueryPerformanceCounter(&(timer->startTime));
  #else
      gettimeofday(&(timer->startTime), NULL);
  #endif
}

void stopTime(Timer* timer) {
  #ifdef _WIN32
      QueryPerformanceCounter(&(timer->endTime));
  #else
      gettimeofday(&(timer->endTime), NULL);
  #endif
}

float elapsedTime(Timer timer) {
  #ifdef _WIN32
      LARGE_INTEGER frequency;
      QueryPerformanceFrequency(&frequency);
      return (float)(timer.endTime.QuadPart - timer.startTime.QuadPart) 
                    / (float)frequency.QuadPart;
  #else
      return ((float)((timer.endTime.tv_sec  - timer.startTime.tv_sec)
                    + (timer.endTime.tv_usec - timer.startTime.tv_usec) / 1.0e6));
  #endif
}

