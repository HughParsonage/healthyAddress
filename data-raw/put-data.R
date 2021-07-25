library(PSMA)
library(data.table)
library(magrittr)
library(hutils)
library(hutilscpp)
stopifnot(dir.exists("data-raw"), file.exists("DESCRIPTION"),
          desc::desc_get("Package") == "healthyAddress")
devtools::load_all()

insert_define_into_header <- function(text1, text2, header.file = "./src/healthyAddress.h") {
  stopifnot(file.exists(header.file), !startsWith(text1, "#"))
  old <- readLines(header.file)
  if (any(startsWith(old, paste("#define", text1)))) {
    message(paste("#define", text1), " already exists in header:\n\t",
            "Present:\t", old[startsWith(old, paste("#define", text1))], "\n\t",
            "Request:\t", paste("#define", text1, text2))
    return(invisible(NULL))
  }
  w <- which_last(startsWith(old, "#define"))
  stopifnot(w > 0)
  new <- c(old[1:w], paste("#define", text1, text2),
           old[-(1:w)])
  writeLines(new, header.file)
}

insert_function_into_header <- function(text1,
                                        header.file = "./src/healthyAddress.h") {
  stopifnot(file.exists(header.file), !startsWith(text1, "#"))
  old <- readLines(header.file)
  if (any(startsWith(old, text1))) {
    message(text1, " already exists in header:\n\t",
            "Present:\t", old[startsWith(old, text1)], "\n\t",
            "Request:\t", text1)
    return(invisible(NULL))
  }
  w <- last(grep("^(int|bool|SEXP) ", old))
  new <- c(old[1:w], text1,
           old[-(1:w)])
  writeLines(new, header.file)
}


# Populate
FF <- get_FullNamedAddressData()

all_postcodes <- FF[, unique(POSTCODE)]
max_postcode <- FF[, max(POSTCODE)]
toString10 <- function(x) {
  out <- character(length(x))
  width <- max(ceiling(log10(x)))
  for (i in seq_along(x)) {
    if (i != length(x)) {
      out[i] <- paste0(formatC(x[i], width = width), ",", if (i %% 10L) " " else "\n")
    }
  }
  out[length(x)] <- formatC(x[i], width = width)
  paste0(out, collapse = "")
}
if (file.exists("src/intrnl-postcode.c"))
  stopifnot(file.remove("src/intrnl-postcode.c"))
cat('#include "healthyAddress.h"', "\n", sep = "", file = "src/intrnl-postcode.c")
insert_define_into_header("N_POSTCODES", length(all_postcodes), header.file = "src/healthyAddress.h")
insert_define_into_header("MAX_POSTCODE", max_postcode, header.file = "src/healthyAddress.h")
insert_define_into_header("N_STREET_TYPES", FF[, uniqueN(STREET_TYPE_CODE)],
                          header.file = "src/healthyAddress.h")
MAX_STREET_CODE <- length(.permitted_street_type_ord())
insert_define_into_header("MAX_STREET_CODE", MAX_STREET_CODE)

cat("int IntrnlPoa_to_POSTCODE[] = {",
    toString10(all_postcodes),
    "};\n",
    sep = "",
    file = "src/intrnl-postcode.c",
    append = TRUE)

POSTCODE_to_IntrnlPoa <- integer(max(all_postcodes))
for (i in seq_along(all_postcodes)) {
  POSTCODE_to_IntrnlPoa[all_postcodes[i]] <- i - 1L
}

cat("int POSTCODE_to_IntrnlPoa[] = {",
    toString10(POSTCODE_to_IntrnlPoa),
    "};\n",
    sep = "",
    file = "src/intrnl-postcode.c",
    append = TRUE)
cat("\n",
    file = "src/intrnl-postcode.c",
    append = TRUE)
cat("int postcode2intrnl(int poa) {\n",
    "return POSTCODE_to_IntrnlPoa[poa];\n",
    "}\n",
    file = "src/intrnl-postcode.c",
    append = TRUE)
cat("int intrnl2postcode(int ipoa) {\n",
    "return IntrnlPoa_to_POSTCODE[ipoa];\n",
    "}\n",
    file = "src/intrnl-postcode.c",
    append = TRUE)


cat("int intrnl2postcode(int ipoa);\n",
    "int intrnl2postcode(int ipoa);\n",
    sep = "",
    file = "src/intrnl-postcode.h",
    append = TRUE)


uniqueN_StreetTypes_by_POSTCODE <-
  FF[, .(nSTREET_TYPES = uniqueN(STREET_TYPE_CODE)), keyby = .(POSTCODE)]

unique__StreetTypes_by_POSTCODE <-
  FF[, .(STREET_TYPES = unique(STREET_TYPE_CODE)), keyby = .(POSTCODE)]

insert_define_into_header("N_UNIQUE_STREET_CODES", FF[, uniqueN(STREET_TYPE_CODE)],
                          "src/healthyAddress.h")

CJ_POSTCODE_StreetType_Exists <-
  copy(unique__StreetTypes_by_POSTCODE) %>%
  .[, POSTCODE := match(POSTCODE, all_postcodes) - 1L] %>%
  .[complete.cases(STREET_TYPES)] %>%

  dcast(POSTCODE ~ STREET_TYPES,
        fun.aggregate = length,
        value.var = "STREET_TYPES") %>%
  melt(id.vars = "POSTCODE",
       variable.name = "STREET_TYPE",
       value.name = "Exists",
       variable.factor = FALSE) %>%
  .[, STREET_TYPE := chmatch(STREET_TYPE, .permitted_street_type_ord())] %>%
  setnames("POSTCODE", "IntrnlPostcode") %>%
  setkey(IntrnlPostcode, STREET_TYPE) %>%
  .[]
CJX_POSTCODE_StreetType_Exists <-
  CJ_POSTCODE_StreetType_Exists[CJ(IntrnlPostcode = unique(CJ_POSTCODE_StreetType_Exists$IntrnlPostcode),
                                   STREET_TYPE = seq_len(MAX_STREET_CODE))]
CJX_POSTCODE_StreetType_Exists[, Exists := coalesce(Exists, 0L)]

ca <- function(...) cat(..., sep = "", file = "src/street-type-exists.c", append = TRUE)
cat("#include", '"healthyAddress.h"\n', file = "src/street-type-exists.c")
ca("static const unsigned char PoaStr[N_POSTCODES][MAX_STREET_CODE] = {\n")
for (p in seq_along(all_postcodes)) {
  if (nrow(CJX_POSTCODE_StreetType_Exists[.(p - 1L)]) != MAX_STREET_CODE) {
    stop(nrow(CJX_POSTCODE_StreetType_Exists[.(p - 1L)]), " ", MAX_STREET_CODE)
  }
  ca("{", paste0(CJX_POSTCODE_StreetType_Exists[.(p - 1L)]$Exists, collapse = ","), "},\n")
}
ca("};\n")
ca("bool poa_has_street_type(int poa, int type) {\n")
ca("  int intrnl_poa = postcode2intrnl(poa);\n")
ca("return PoaStr[poa][type];\n")
ca("}\n")

insert_function_into_header("bool poa_has_street_type(int poa, int type);\n")




