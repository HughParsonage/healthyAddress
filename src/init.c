#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* FIXME: 
   Check these declarations against the C/Fortran source code.
*/

/* .Call calls */
extern SEXP CEncodeStCd(SEXP, SEXP, SEXP, SEXP);
extern SEXP CEnsureUC(SEXP);
extern SEXP CExtractStdAddress(SEXP, SEXP);
extern SEXP CFindSentence(SEXP, SEXP, SEXP);
extern SEXP Ctest_digit_of_from(SEXP, SEXP, SEXP);
extern SEXP Ctest_touppers(SEXP);
extern SEXP CToUpperBasic(SEXP);
extern SEXP CwhichStreetName3(SEXP);
extern SEXP Extract2(SEXP, SEXP, SEXP, SEXP, SEXP, SEXP);

static const R_CallMethodDef CallEntries[] = {
    {"CEncodeStCd",         (DL_FUNC) &CEncodeStCd,         4},
    {"CEnsureUC",           (DL_FUNC) &CEnsureUC,           1},
    {"CExtractStdAddress",  (DL_FUNC) &CExtractStdAddress,  2},
    {"CFindSentence",       (DL_FUNC) &CFindSentence,       3},
    {"Ctest_digit_of_from", (DL_FUNC) &Ctest_digit_of_from, 3},
    {"Ctest_touppers",      (DL_FUNC) &Ctest_touppers,      1},
    {"CToUpperBasic",       (DL_FUNC) &CToUpperBasic,       1},
    {"CwhichStreetName3",   (DL_FUNC) &CwhichStreetName3,   1},
    {"Extract2",            (DL_FUNC) &Extract2,            6},
    {NULL, NULL, 0}
};

void R_init_healthyAddress(DllInfo *dll)
{
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
