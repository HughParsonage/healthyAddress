#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* FIXME: 
   Check these declarations against the C/Fortran source code.
*/

/* .Call calls */
extern SEXP C_anyComma(SEXP, SEXP);
extern SEXP C_check_address_input(SEXP, SEXP, SEXP);
extern SEXP C_compress_latlon(SEXP, SEXP, SEXP);
extern SEXP C_compress_latlon_general(SEXP, SEXP, SEXP, SEXP, SEXP);
extern SEXP C_contains_BIG4(SEXP);
extern SEXP C_decompress_latlon(SEXP, SEXP);
extern SEXP C_decompress_latlon_general(SEXP, SEXP, SEXP, SEXP);
extern SEXP C_do_standard_address3(SEXP, SEXP, SEXP, SEXP);
extern SEXP C_do_the_xxx(SEXP, SEXP, SEXP);
extern SEXP C_fillPostcodeStreets(SEXP, SEXP, SEXP, SEXP);
extern SEXP C_freeALL_POSTCODE_STREETS(SEXP);
extern SEXP C_get_oZTC(SEXP);
extern SEXP C_get_StreetCode(SEXP);
extern SEXP C_get_StreetType(SEXP);
extern SEXP C_getTHEXXX(SEXP);
extern SEXP C_has_saint_name(SEXP, SEXP);
extern SEXP C_HashStreetName(SEXP);
extern SEXP C_isPostcode(SEXP);
extern SEXP C_max_nchar(SEXP);
extern SEXP C_MAX_POSTCODE(SEXP);
extern SEXP C_multistate_postcodes(SEXP);
extern SEXP C_N_POSTCODES(SEXP);
extern SEXP C_noLC(SEXP, SEXP);
extern SEXP C_NumberFirstLast(SEXP);
extern SEXP C_NumberSuffix2Raw(SEXP);
extern SEXP C_standard_address_postcode_trie(SEXP);
extern SEXP C_standard_address2(SEXP, SEXP);
extern SEXP C_StaticAssert(SEXP);
extern SEXP C_test_ALPHABET_ENC(SEXP);
extern SEXP C_test_n_words(SEXP);
extern SEXP C_trie_streetType(SEXP);
extern SEXP C_uint128_not_supported(SEXP);
extern SEXP C_uniquePostcodes(SEXP, SEXP, SEXP);
extern SEXP C_which_first_strstr(SEXP, SEXP);
extern SEXP C_xFlatFirstLast(SEXP);
extern SEXP Cconcat_upper(SEXP, SEXP, SEXP, SEXP, SEXP);
extern SEXP Cdigit256(SEXP, SEXP);
extern SEXP CExtractPostcode(SEXP);
extern SEXP CFindSentence(SEXP, SEXP, SEXP);
extern SEXP Cfollowed_by_STE_POSTCODE(SEXP, SEXP);
extern SEXP Cget_suffix(SEXP);
extern SEXP Cmatch_StreetType_Line1(SEXP, SEXP, SEXP);
extern SEXP Cmatch_word(SEXP, SEXP);
extern SEXP Ctest_WordData(SEXP, SEXP);
extern SEXP CToUpperBasic(SEXP);
extern SEXP Cxnumber(SEXP);
extern SEXP Cxnumber128(SEXP);
extern SEXP MAX_uN_STCDs(SEXP);

static const R_CallMethodDef CallEntries[] = {
    {"C_anyComma",                       (DL_FUNC) &C_anyComma,                       2},
    {"C_check_address_input",            (DL_FUNC) &C_check_address_input,            3},
    {"C_compress_latlon",                (DL_FUNC) &C_compress_latlon,                3},
    {"C_compress_latlon_general",        (DL_FUNC) &C_compress_latlon_general,        5},
    {"C_contains_BIG4",                  (DL_FUNC) &C_contains_BIG4,                  1},
    {"C_decompress_latlon",              (DL_FUNC) &C_decompress_latlon,              2},
    {"C_decompress_latlon_general",      (DL_FUNC) &C_decompress_latlon_general,      4},
    {"C_do_standard_address3",           (DL_FUNC) &C_do_standard_address3,           4},
    {"C_do_the_xxx",                     (DL_FUNC) &C_do_the_xxx,                     3},
    {"C_fillPostcodeStreets",            (DL_FUNC) &C_fillPostcodeStreets,            4},
    {"C_freeALL_POSTCODE_STREETS",       (DL_FUNC) &C_freeALL_POSTCODE_STREETS,       1},
    {"C_get_oZTC",                       (DL_FUNC) &C_get_oZTC,                       1},
    {"C_get_StreetCode",                 (DL_FUNC) &C_get_StreetCode,                 1},
    {"C_get_StreetType",                 (DL_FUNC) &C_get_StreetType,                 1},
    {"C_getTHEXXX",                      (DL_FUNC) &C_getTHEXXX,                      1},
    {"C_has_saint_name",                 (DL_FUNC) &C_has_saint_name,                 2},
    {"C_HashStreetName",                 (DL_FUNC) &C_HashStreetName,                 1},
    {"C_isPostcode",                     (DL_FUNC) &C_isPostcode,                     1},
    {"C_max_nchar",                      (DL_FUNC) &C_max_nchar,                      1},
    {"C_MAX_POSTCODE",                   (DL_FUNC) &C_MAX_POSTCODE,                   1},
    {"C_multistate_postcodes",           (DL_FUNC) &C_multistate_postcodes,           1},
    {"C_N_POSTCODES",                    (DL_FUNC) &C_N_POSTCODES,                    1},
    {"C_noLC",                           (DL_FUNC) &C_noLC,                           2},
    {"C_NumberFirstLast",                (DL_FUNC) &C_NumberFirstLast,                1},
    {"C_NumberSuffix2Raw",               (DL_FUNC) &C_NumberSuffix2Raw,               1},
    {"C_standard_address_postcode_trie", (DL_FUNC) &C_standard_address_postcode_trie, 1},
    {"C_standard_address2",              (DL_FUNC) &C_standard_address2,              2},
    {"C_StaticAssert",                   (DL_FUNC) &C_StaticAssert,                   1},
    {"C_test_ALPHABET_ENC",              (DL_FUNC) &C_test_ALPHABET_ENC,              1},
    {"C_test_n_words",                   (DL_FUNC) &C_test_n_words,                   1},
    {"C_trie_streetType",                (DL_FUNC) &C_trie_streetType,                1},
    {"C_uint128_not_supported",          (DL_FUNC) &C_uint128_not_supported,          1},
    {"C_uniquePostcodes",                (DL_FUNC) &C_uniquePostcodes,                3},
    {"C_which_first_strstr",             (DL_FUNC) &C_which_first_strstr,             2},
    {"C_xFlatFirstLast",                 (DL_FUNC) &C_xFlatFirstLast,                 1},
    {"Cconcat_upper",                    (DL_FUNC) &Cconcat_upper,                    5},
    {"Cdigit256",                        (DL_FUNC) &Cdigit256,                        2},
    {"CExtractPostcode",                 (DL_FUNC) &CExtractPostcode,                 1},
    {"CFindSentence",                    (DL_FUNC) &CFindSentence,                    3},
    {"Cfollowed_by_STE_POSTCODE",        (DL_FUNC) &Cfollowed_by_STE_POSTCODE,        2},
    {"Cget_suffix",                      (DL_FUNC) &Cget_suffix,                      1},
    {"Cmatch_StreetType_Line1",          (DL_FUNC) &Cmatch_StreetType_Line1,          3},
    {"Cmatch_word",                      (DL_FUNC) &Cmatch_word,                      2},
    {"Ctest_WordData",                   (DL_FUNC) &Ctest_WordData,                   2},
    {"CToUpperBasic",                    (DL_FUNC) &CToUpperBasic,                    1},
    {"Cxnumber",                         (DL_FUNC) &Cxnumber,                         1},
    {"Cxnumber128",                      (DL_FUNC) &Cxnumber128,                      1},
    {"MAX_uN_STCDs",                     (DL_FUNC) &MAX_uN_STCDs,                     1},
    {NULL, NULL, 0}
};

void R_init_healthyAddress(DllInfo *dll)
{
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
