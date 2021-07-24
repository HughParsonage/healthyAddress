#ifndef healthyAddress_H
#define healthyAddress_H

#include <R.h>
#define USE_RINTERNALS
#include <Rinternals.h>
// #include <signal.h> // the debugging machinery + breakpoint aidee
// raise(SIGINT);
#include <stdint.h> // for uint64_t rather than unsigned long long
#include <stdbool.h>
#include <math.h>
#include "streetcodes.h"

#define N_POSTCODES 2640
#define SUP_POSTCODES 8192
#define MAX_NUMBER_STREET_TYPES_ANY_POSTCODE 64
#define N_STREET_TYPES 201
#define MAX_POSTCODE 7470
#define N_UNIQUE_STREET_CODES 201

int isnt_sorted_asc(SEXP x);
int find_common_street(const char * x, int n, int i);
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
bool poa_has_street_type(int poa, int type);


#endif
