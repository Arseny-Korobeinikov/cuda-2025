#ifndef __GEMM_CUBLAS_H
#define __GEMM_CUBLAS_H

#pragma once
#include <cublas_v2.h>
#include <cuda_runtime.h>

#include <vector>

std::vector<float> GemmCUBLAS(const std::vector<float>& a, const std::vector<float>& b, int n);

#endif  // __GEMM_CUBLAS_H