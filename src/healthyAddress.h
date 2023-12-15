#ifndef healthyAddress_H
#define healthyAddress_H

#if _OPENMP
#include <omp.h>
#endif

#include <R.h>
#define USE_RINTERNALS
#include <Rinternals.h>
#include <stdint.h> // for uint64_t rather than unsigned long long
#include <stdbool.h>
#include <math.h>
#include "streetcodes.h"
#include <ctype.h>


// Empirical data / known features of Australian postcodes
#define N_POSTCODES 2640
#define SUP_POSTCODES 8192
#define SUP_POSTCODE_ 8191
#define MAX_NUMBER_STREET_TYPES_ANY_POSTCODE 64
#define N_STREET_TYPES 201
#define MAX_POSTCODE 7470
#define N_UNIQUE_STREET_CODES 201
#define MAX_STREET_CODE 224

// Parameters or assumptions (often about stacks)
// // Number of words per string to be considered
#define WORD_DATUMS 16

int isnt_sorted_asc(SEXP x);
int find_common_street(const char * x, int n, int i);

bool jchar_is_number(const char * x, int j);
int next_numeral(int j, const char * x, int n);
int j_post_LEVEL(const char * x, int n);


bool has_STREET(const char * x, int n);
bool has_ROAD(const char * x, int n);
bool has_AVENUE(const char * x, int n);
bool has_DRIVE(const char * x, int n);
bool has_COURT(const char * x, int n);
bool has_CRESCENT(const char * x, int n);
bool has_WAY(const char * x, int n);
bool has_CLOSE(const char * x, int n);
bool has_PLACE(const char * x, int n);
bool has_LANE(const char * x, int n);
bool has_GROVE(const char * x, int n);

bool poa_has_ROAD(int poa);

bool poa_has_street_type(int poa, int type);
int postcode2intrnl(unsigned int poa);
int intrnl2postcode(unsigned int ipoa);

// verifyEquiStr.c
void errIfNotLen(SEXP x, const char * xx, R_xlen_t N);
void verifyEquiStr2(SEXP x, const char * xx,
                    SEXP y, const char * yy);
void verifyEquiOrLen1Str2(SEXP x, const char * xx,
                          SEXP y, const char * yy);
void verifyEquiStr4(SEXP x, const char * xx,
                    SEXP y, const char * yy,
                    SEXP z, const char * zz,
                    SEXP w, const char * ww);
void errifNotTF(SEXP x, const char * v);


#endif
