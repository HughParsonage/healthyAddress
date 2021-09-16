#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* FIXME: 
   Check these declarations against the C/Fortran source code.
*/

/* .Call calls */
extern SEXP C_do_standard_address(SEXP);
extern SEXP C_HashStreetName(SEXP);
extern SEXP C_noLC(SEXP);
extern SEXP C_NumberFirstLast(SEXP);
extern SEXP C_NumberSuffix2Raw(SEXP);
extern SEXP C_StaticAssert(SEXP);
extern SEXP C_uniquePostcodes(SEXP);
extern SEXP Cdigit256(SEXP, SEXP);
extern SEXP CExtractPostcode(SEXP);
extern SEXP CFindSentence(SEXP, SEXP, SEXP);
extern SEXP Cmatch_StreetName(SEXP, SEXP, SEXP, SEXP);
extern SEXP Cmatch_StreetType(SEXP, SEXP, SEXP);
extern SEXP Cmatch_StreetType_Line1(SEXP, SEXP, SEXP);
extern SEXP Cmatch_word(SEXP, SEXP);
extern SEXP CPoaHasSt(SEXP, SEXP);
extern SEXP Cs2u(SEXP, SEXP);
extern SEXP Ctest_WordData(SEXP, SEXP);
extern SEXP CToUpperBasic(SEXP);
extern SEXP MAX_uN_STCDs(SEXP);
extern SEXP ZMatchStreetName(SEXP);

static const R_CallMethodDef CallEntries[] = {
    {"C_do_standard_address",   (DL_FUNC) &C_do_standard_address,   1},
    {"C_HashStreetName",        (DL_FUNC) &C_HashStreetName,        1},
    {"C_noLC",                  (DL_FUNC) &C_noLC,                  1},
    {"C_NumberFirstLast",       (DL_FUNC) &C_NumberFirstLast,       1},
    {"C_NumberSuffix2Raw",      (DL_FUNC) &C_NumberSuffix2Raw,      1},
    {"C_StaticAssert",          (DL_FUNC) &C_StaticAssert,          1},
    {"C_uniquePostcodes",       (DL_FUNC) &C_uniquePostcodes,       1},
    {"Cdigit256",               (DL_FUNC) &Cdigit256,               2},
    {"CExtractPostcode",        (DL_FUNC) &CExtractPostcode,        1},
    {"CFindSentence",           (DL_FUNC) &CFindSentence,           3},
    {"Cmatch_StreetName",       (DL_FUNC) &Cmatch_StreetName,       4},
    {"Cmatch_StreetType",       (DL_FUNC) &Cmatch_StreetType,       3},
    {"Cmatch_StreetType_Line1", (DL_FUNC) &Cmatch_StreetType_Line1, 3},
    {"Cmatch_word",             (DL_FUNC) &Cmatch_word,             2},
    {"CPoaHasSt",               (DL_FUNC) &CPoaHasSt,               2},
    {"Cs2u",                    (DL_FUNC) &Cs2u,                    2},
    {"Ctest_WordData",          (DL_FUNC) &Ctest_WordData,          2},
    {"CToUpperBasic",           (DL_FUNC) &CToUpperBasic,           1},
    {"MAX_uN_STCDs",            (DL_FUNC) &MAX_uN_STCDs,            1},
    {"ZMatchStreetName",        (DL_FUNC) &ZMatchStreetName,        1},
    {NULL, NULL, 0}
};

void R_init_healthyAddress(DllInfo *dll)
{
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
