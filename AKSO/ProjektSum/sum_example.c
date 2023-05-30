#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// To jest deklaracja testowanej funkcji.
void sum(int64_t *x, size_t n);

// To są dane do testów.
static const int64_t x0[] = {3};
static const int64_t x1[] = {7, 9};
static const int64_t x2[] = {-3, 8};
static const int64_t x3[] = {3, -8};
static const int64_t x4[] = {-5, -6};
static const int64_t x5[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
static const int64_t x6[] = {
  INT64_MAX, INT64_MAX, INT64_MAX, INT64_MAX,
  INT64_MAX, INT64_MAX, INT64_MAX, INT64_MAX,
  INT64_MAX, INT64_MAX, INT64_MAX
};
static const int64_t x7[] = {
  INT64_MIN, INT64_MIN, INT64_MIN, INT64_MIN,
  INT64_MIN, INT64_MIN, INT64_MIN, INT64_MIN,
  INT64_MIN, INT64_MIN, INT64_MIN, INT64_MIN,
  INT64_MIN
};

// To są oczekiwane wyniki.
static const int64_t y0[] = {0x0000000000000003};
static const int64_t y1[] = {0x0000000900000007, 0x0000000000000000};
static const int64_t y2[] = {0x00000007fffffffd, 0x0000000000000000};
static const int64_t y3[] = {0xfffffff800000003, 0xffffffffffffffff};
static const int64_t y4[] = {0xfffffff9fffffffb, 0xffffffffffffffff};
static const int64_t y5[] = {
  0x0000004000020011, 0x0000040000000010, 0x0000000002000000, 0x0000000000020000,
  0x0000000000020000, 0x0000000002000000, 0x0000040000000000, 0x0000000000000000,
  0x0000000000000010, 0x0000004000000000, 0x0000000000000000, 0x0000000000020000,
  0x0000000000000000, 0x0000000000000010, 0x0000000000000000
};
static const int64_t y6[] = {
  0x7fefffffff7fffdf, 0x0007ffffe0400010, 0x000000000ffe0000, 0xffffffffffff0000,
  0xffffffffe000ffff, 0xfff000000fffffff, 0x0007ffffffffffff, 0xffffffffff800000,
  0x00000000003fffff, 0xffffffffffffffe0, 0x000000000000000f
};
static const int64_t y7[] = {
  0x8000000000000000, 0xfffff7fffffbfff7, 0xfbffffffffffdfff, 0xfffeffffffffffff,
  0xfffeffffffffffff, 0xfbffffffffffffff, 0xffffffffffffffff, 0xffffffffffffdfff,
  0xfffff7ffffffffff, 0xffffffffffffffff, 0xfffffffffffbffff, 0xffffffffffffffff,
  0xfffffffffffffff7
};

typedef struct {
  size_t  const t;  // numer testu
  size_t  const n;  // rozmiar tablicy
  int64_t const *x; // tablica
  int64_t const *y; // oczekiwany wynik
} test_data_t;

#define SIZE(x) (sizeof x / sizeof x[0])
#define DATA(t) {t, SIZE(x##t), x##t, y##t}

static const test_data_t test_data[] = {
  DATA(0),
  DATA(1),
  DATA(2),
  DATA(3),
  DATA(4),
  DATA(5),
  DATA(6),
  DATA(7),
};

int main() {
  for (size_t test = 0; test < SIZE(test_data); ++test) {
    size_t n = test_data[test].n;
    int64_t *work_space = malloc(n * sizeof (int64_t));
    assert(work_space);
    memcpy(work_space, test_data[test].x, n * sizeof (int64_t));

    sum(work_space, n);

    for (size_t i = 0; i < n; ++i) {
      printf("W teście jest git\n");
      if (work_space[i] != test_data[test].y[i]) {
        printf("W teście %zu pod indeksem %zu\n"
               "jest        %016" PRIx64 ",\n"
               "powinno być %016" PRIx64 ".\n",
               test_data[test].t, i, work_space[i], test_data[test].y[i]);
      }
    }
    free(work_space);
  }
}
