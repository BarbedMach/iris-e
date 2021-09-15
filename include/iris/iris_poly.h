#ifndef IRIS_INCLUDE_IRIS_POLY_H
#define IRIS_INCLUDE_IRIS_POLY_H

#include <iris/iris_errno.h>
#include <iris/iris_poly_types.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#if 1
#define IRIS_POLY_KERNEL_ARGS       size_t _off0, size_t _off1, size_t _off2, \
                                    size_t _ndr0, size_t _ndr1, size_t _ndr2, \
                                    size_t _gws0, size_t _gws1, size_t _gws2, \
                                    size_t _lws0, size_t _lws1, size_t _lws2
#else
#define IRIS_POLY_KERNEL_ARGS       size_t _wgo0, size_t _wgo1, size_t _wgo2, \
                                    size_t _wgs0, size_t _wgs1, size_t _wgs2, \
                                    size_t _gws0, size_t _gws1, size_t _gws2, \
                                    size_t _lws0, size_t _lws1, size_t _lws2
#endif
#define IRIS_POLY_ARRAY_1D(F, M, TYPESZ, S0)                                  \
        F##_args.M.dim    = 1;                                                \
        F##_args.M.typesz = TYPESZ;                                           \
        F##_args.M.s0     = S0
#define IRIS_POLY_ARRAY_2D(F, M, TYPESZ, S1, S0)                              \
        F##_args.M.dim    = 2;                                                \
        F##_args.M.typesz = TYPESZ;                                           \
        F##_args.M.s1     = S1;                                               \
        F##_args.M.s0     = S0
#define IRIS_POLY_DOMAIN(D, I0, I1)                                           \
        size_t D[2] = { I0, I1 }
#define IRIS_POLY_READ_1D(F, M, I)                                            \
        iris_poly_read(&F##_args.M, I)
#define IRIS_POLY_MUWR_1D(F, M, I)                                            \
        iris_poly_muwr(&F##_args.M, I)
#define IRIS_POLY_MAWR_1D(F, M, I)                                            \
        iris_poly_mawr(&F##_args.M, I)
#define IRIS_POLY_READ_2D(F, M, I0, I1)                                       \
        iris_poly_read_2d(&F##_args.M, I0, I1)
        //iris_poly_read(&F##_args.M, I0 * F##_args.M.s0 + I1);             
#define IRIS_POLY_MUWR_2D(F, M, I0, I1)                                       \
        iris_poly_muwr_2d(&F##_args.M, I0, I1)
        //iris_poly_muwr(&F##_args.M, I0 * F##_args.M.s0 + I1)
#define IRIS_POLY_MAWR_2D(F, M, I0, I1)                                       \
        iris_poly_mawr_2d(&F##_args.M, I0, I1)
        //iris_poly_mawr(&F##_args.M, I0 * F##_args.M.s0 + I1)

typedef int32_t i32;

#ifdef __cplusplus
extern "C" {
#endif

static pthread_mutex_t iris_poly_mutex;
static int iris_poly_kernel_idx;

void iris_poly_init() {
  pthread_mutex_init(&iris_poly_mutex, NULL);
}

void iris_poly_finalize() {
  pthread_mutex_destroy(&iris_poly_mutex);
}

static void iris_poly_lock() {
  pthread_mutex_lock(&iris_poly_mutex);
}

static void iris_poly_unlock() {
  pthread_mutex_unlock(&iris_poly_mutex);
}

static void iris_poly_mem_init(iris_poly_mem* p) {
  p->r0 = SIZE_MAX;
  p->r1 = 0;
  p->w0 = SIZE_MAX;
  p->w1 = 0;
}

static void iris_poly_read(iris_poly_mem* p, size_t idx) {
  if (idx < p->r0) p->r0 = idx;
  if (idx > p->r1) p->r1 = idx;
}

static void iris_poly_muwr(iris_poly_mem* p, size_t idx) {
  if (idx < p->w0) p->w0 = idx;
  if (idx > p->w1) p->w1 = idx;
}

static void iris_poly_mawr(iris_poly_mem* p, size_t idx) {
  return iris_poly_muwr(p, idx);
}

static void iris_poly_read_2d(iris_poly_mem* p, size_t idx1, size_t idx2) {
  return iris_poly_read(p, idx1 * p->s0 + idx2);
}

static void iris_poly_muwr_2d(iris_poly_mem* p, size_t idx1, size_t idx2) {
  return iris_poly_muwr(p, idx1 * p->s0 + idx2);
}

static void iris_poly_mawr_2d(iris_poly_mem* p, size_t idx1, size_t idx2) {
  return iris_poly_muwr_2d(p, idx1, idx2);
}

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif /* IRIS_INCLUDE_IRIS_POLY_H */

