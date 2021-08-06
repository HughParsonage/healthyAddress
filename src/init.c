#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* FIXME: 
   Check these declarations against the C/Fortran source code.
*/

/* .Call calls */
extern SEXP C_N_STREET_TYPES(SEXP);
extern SEXP C_uniquePostcodes(SEXP);
extern SEXP CDecodeWord_16_2(SEXP);
extern SEXP Cdigit256(SEXP, SEXP);
extern SEXP CEncodeStCd(SEXP, SEXP, SEXP, SEXP);
extern SEXP CEncodeWord_16_2(SEXP);
extern SEXP CEnsureUC(SEXP);
extern SEXP CExtractAddressID(SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP);
extern SEXP CextractNumber(SEXP, SEXP, SEXP);
extern SEXP CExtractPostcode(SEXP);
extern SEXP CExtractStdAddress(SEXP, SEXP);
extern SEXP CFindSentence(SEXP, SEXP, SEXP);
extern SEXP Cmatch_StreetName(SEXP, SEXP, SEXP, SEXP, SEXP, SEXP);
extern SEXP Cmatch_StreetType(SEXP, SEXP, SEXP);
extern SEXP Cmatch_word(SEXP, SEXP);
extern SEXP CNamePresent(SEXP, SEXP, SEXP, SEXP, SEXP);
extern SEXP Cpoa_has_stcd(SEXP);
extern SEXP CPoaHasSt(SEXP, SEXP);
extern SEXP CStreet2StreetCode(SEXP);
extern SEXP CStreetCd2Str(SEXP);
extern SEXP Ctest_digit_of_from(SEXP, SEXP, SEXP);
extern SEXP Ctest_touppers(SEXP);
extern SEXP CToUpperBasic(SEXP);
extern SEXP CwhichStreetName3(SEXP);
extern SEXP Extract2(SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP);
extern SEXP MAX_uN_STCDs(SEXP);

static const R_CallMethodDef CallEntries[] = {
    {"C_N_STREET_TYPES",    (DL_FUNC) &C_N_STREET_TYPES,     1},
    {"C_uniquePostcodes",   (DL_FUNC) &C_uniquePostcodes,    1},
    {"CDecodeWord_16_2",    (DL_FUNC) &CDecodeWord_16_2,     1},
    {"Cdigit256",           (DL_FUNC) &Cdigit256,            2},
    {"CEncodeStCd",         (DL_FUNC) &CEncodeStCd,          4},
    {"CEncodeWord_16_2",    (DL_FUNC) &CEncodeWord_16_2,     1},
    {"CEnsureUC",           (DL_FUNC) &CEnsureUC,            1},
    {"CExtractAddressID",   (DL_FUNC) &CExtractAddressID,   10},
    {"CextractNumber",      (DL_FUNC) &CextractNumber,       3},
    {"CExtractPostcode",    (DL_FUNC) &CExtractPostcode,     1},
    {"CExtractStdAddress",  (DL_FUNC) &CExtractStdAddress,   2},
    {"CFindSentence",       (DL_FUNC) &CFindSentence,        3},
    {"Cmatch_StreetName",   (DL_FUNC) &Cmatch_StreetName,    6},
    {"Cmatch_StreetType",   (DL_FUNC) &Cmatch_StreetType,    3},
    {"Cmatch_word",         (DL_FUNC) &Cmatch_word,          2},
    {"CNamePresent",        (DL_FUNC) &CNamePresent,         5},
    {"Cpoa_has_stcd",       (DL_FUNC) &Cpoa_has_stcd,        1},
    {"CPoaHasSt",           (DL_FUNC) &CPoaHasSt,            2},
    {"CStreet2StreetCode",  (DL_FUNC) &CStreet2StreetCode,   1},
    {"CStreetCd2Str",       (DL_FUNC) &CStreetCd2Str,        1},
    {"Ctest_digit_of_from", (DL_FUNC) &Ctest_digit_of_from,  3},
    {"Ctest_touppers",      (DL_FUNC) &Ctest_touppers,       1},
    {"CToUpperBasic",       (DL_FUNC) &CToUpperBasic,        1},
    {"CwhichStreetName3",   (DL_FUNC) &CwhichStreetName3,    1},
    {"Extract2",            (DL_FUNC) &Extract2,             7},
    {"MAX_uN_STCDs",        (DL_FUNC) &MAX_uN_STCDs,         1},
    {NULL, NULL, 0}
};

void R_init_healthyAddress(DllInfo *dll)
{
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
