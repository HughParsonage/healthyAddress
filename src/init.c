#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* FIXME: 
   Check these declarations against the C/Fortran source code.
*/

/* .Call calls */
extern SEXP C_HashStreetName(SEXP);
extern SEXP C_noLC(SEXP);
extern SEXP C_NumberFirstLast(SEXP);
extern SEXP C_NumberSuffix2Raw(SEXP);
extern SEXP C_uniquePostcodes(SEXP);
extern SEXP Cdigit256(SEXP, SEXP);
extern SEXP CExtractPostcode(SEXP);
extern SEXP CExtractStdAddress(SEXP, SEXP);
extern SEXP CFindSentence(SEXP, SEXP, SEXP);
extern SEXP Cmatch_StreetName(SEXP, SEXP, SEXP);
extern SEXP Cmatch_StreetType(SEXP, SEXP, SEXP);
extern SEXP Cmatch_StreetType_Line1(SEXP, SEXP);
extern SEXP Cmatch_word(SEXP, SEXP);
extern SEXP Cpoa_has_stcd(SEXP);
extern SEXP CPoaHasSt(SEXP, SEXP);
extern SEXP CStreetCd2Str(SEXP);
extern SEXP Ctest_digit_of_from(SEXP, SEXP, SEXP);
extern SEXP Ctest_touppers(SEXP);
extern SEXP CToUpperBasic(SEXP);
extern SEXP CwhichStreetName3(SEXP);
extern SEXP MAX_uN_STCDs(SEXP);

static const R_CallMethodDef CallEntries[] = {
    {"C_HashStreetName",        (DL_FUNC) &C_HashStreetName,        1},
    {"C_noLC",                  (DL_FUNC) &C_noLC,                  1},
    {"C_NumberFirstLast",       (DL_FUNC) &C_NumberFirstLast,       1},
    {"C_NumberSuffix2Raw",      (DL_FUNC) &C_NumberSuffix2Raw,      1},
    {"C_uniquePostcodes",       (DL_FUNC) &C_uniquePostcodes,       1},
    {"Cdigit256",               (DL_FUNC) &Cdigit256,               2},
    {"CExtractPostcode",        (DL_FUNC) &CExtractPostcode,        1},
    {"CExtractStdAddress",      (DL_FUNC) &CExtractStdAddress,      2},
    {"CFindSentence",           (DL_FUNC) &CFindSentence,           3},
    {"Cmatch_StreetName",       (DL_FUNC) &Cmatch_StreetName,       3},
    {"Cmatch_StreetType",       (DL_FUNC) &Cmatch_StreetType,       3},
    {"Cmatch_StreetType_Line1", (DL_FUNC) &Cmatch_StreetType_Line1, 2},
    {"Cmatch_word",             (DL_FUNC) &Cmatch_word,             2},
    {"Cpoa_has_stcd",           (DL_FUNC) &Cpoa_has_stcd,           1},
    {"CPoaHasSt",               (DL_FUNC) &CPoaHasSt,               2},
    {"CStreetCd2Str",           (DL_FUNC) &CStreetCd2Str,           1},
    {"Ctest_digit_of_from",     (DL_FUNC) &Ctest_digit_of_from,     3},
    {"Ctest_touppers",          (DL_FUNC) &Ctest_touppers,          1},
    {"CToUpperBasic",           (DL_FUNC) &CToUpperBasic,           1},
    {"CwhichStreetName3",       (DL_FUNC) &CwhichStreetName3,       1},
    {"MAX_uN_STCDs",            (DL_FUNC) &MAX_uN_STCDs,            1},
    {NULL, NULL, 0}
};

void R_init_healthyAddress(DllInfo *dll)
{
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
