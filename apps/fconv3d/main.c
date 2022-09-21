// Copyright 2020 ETH Zurich and University of Bologna.
//
// SPDX-License-Identifier: Apache-2.0
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Author: Matteo Perotti

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "fconv3d.h"
#include "runtime.h"

#ifndef SPIKE
#include "printf.h"
#endif

// Define Matrix dimensions:
// o = i ° f, with i=[(M+F-1)x(N+f-1)xCH], f=[FxFxCH], o=[MxN]
// The filter is a square matrix, and F is odd

// Matrices defined in data.S
extern double i[] __attribute__((
    aligned(4 * NR_LANES))); // [ (M+floor(F/2)) * (N+floor(F/2)) * CH ]
extern double f[] __attribute__((aligned(4 * NR_LANES)));        // [ F*F*CH ]
extern double o[] __attribute__((aligned(4 * NR_LANES)));        // [ M*N ]
extern double golden_o[] __attribute__((aligned(4 * NR_LANES))); // [ M*N ]
// M, N, F defined in data.S
extern int64_t M;
extern int64_t N;
extern int64_t ICH;
extern int64_t OCH;
extern int64_t F;

// Return 0 if the two FP numbers differ by more than a threshold
int similarity_check(double a, double b, double threshold) {
  double diff = a - b;
  if (FABS(diff) > threshold) {
    printf("fabs(diff): %lf, threshold: %lf\n", diff, threshold);
    return 0;
  } else
    return 1;
}

// Verify the matrices
int verify_matrix(double *matrix, double *golden_matrix, int64_t R, int64_t C,
                  int64_t OCH, double threshold) {
  for (int oc = 0; oc < OCH; ++oc)
    for (int r = 0; r < R; ++r)
      for (int c = 0; c < C; ++c)
        if (!similarity_check(matrix[c + C * r + (C * R) * oc],
                              golden_matrix[c + C * r + (C * R) * oc],
                              threshold)) {
          printf("Error: o[%d][%d][%d] = %lf, instead of %lf\n", oc, r, c,
                 matrix[c + C * r + (C * R) * oc],
                 golden_matrix[c + C * r + (C * R) * oc]);
          return 1;
        }
  return 0;
}

void print_matrix(double const *matrix, uint64_t num_rows,
                  uint64_t num_columns) {
  printf("0x%8X\n", (uint64_t)matrix);
  for (uint64_t i = 0; i < num_rows; ++i) {
    for (uint64_t j = 0; j < num_columns; ++j) {
      printf("%10f ", matrix[i * num_columns + j]);
    }
    printf("\n");
  }
}

int main() {
  printf("\n");
  printf("=============\n");
  printf("=  FCONV3D  =\n");
  printf("=============\n");
  printf("\n");
  printf("\n");

  printf("Input Mtx size: %dx%d\n", M + F - 1, N + F - 1);
  printf("Output Mtx size: %dx%d\n", M, N);
  printf("Filter size: %dx%d\n", F, F);
  printf("Channels: %d\n", ICH);

  // Call the main kernel, and measure cycles
  start_timer();
  if (F == 7)
    fconv3d_CHx7x7(o, i, f, M, N, ICH, F);
  else if (F == 3)
    fconv3d_CHx3x3(o, i, f, M, N, ICH, OCH, F);
  else
    printf("Error: the filter size is different from 7 or 3.\n");
  stop_timer();

  // Performance metrics
  int64_t runtime = get_timer();
  float performance = 2.0 * OCH * ICH * F * F * M * N / runtime;
  float utilization = 100 * performance / (2.0 * NR_LANES);

  printf("The execution took %d cycles.\n", runtime);
  printf("The performance is %f DPFLOP/cycle (%f%% utilization).\n",
         performance, utilization);

  // Verify correctness
  printf("Verifying result...\n");
  int error = verify_matrix(o, golden_o, M, N, OCH, THRESHOLD);
  if (error != 0) {
    printf("Fail.\n");
  } else {
    printf("Passed.\n");
  }

  return error;
}
