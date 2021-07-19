#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* FIXME: 
   Check these declarations against the C/Fortran source code.
*/

/* .Call calls */
extern SEXP CExtractStdAddress(SEXP, SEXP);
extern SEXP CFindLocality(SEXP);
extern SEXP Cidentify_address_format(SEXP);
extern SEXP Ctest_digit_of_from(SEXP, SEXP, SEXP);
extern SEXP CToUpperBasic(SEXP);
extern SEXP CwhichStreetName3(SEXP);

static const R_CallMethodDef CallEntries[] = {
    {"CExtractStdAddress",       (DL_FUNC) &CExtractStdAddress,       2},
    {"CFindLocality",            (DL_FUNC) &CFindLocality,            1},
    {"Cidentify_address_format", (DL_FUNC) &Cidentify_address_format, 1},
    {"Ctest_digit_of_from",      (DL_FUNC) &Ctest_digit_of_from,      3},
    {"CToUpperBasic",            (DL_FUNC) &CToUpperBasic,            1},
    {"CwhichStreetName3",        (DL_FUNC) &CwhichStreetName3,        1},
    {NULL, NULL, 0}
};

void R_init_healthyAddress(DllInfo *dll)
{
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
