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
FF[, i := .I]

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

Street_by_POSTCODE <-
  unique(FF, by = key(FF)[1:3]) %>%
  .[, STREET_TYPE_CODE_INT := encode_street_name(STREET_TYPE_CODE)] %>%
  .[]


find_psma_cols <- function(cols, state = "VIC") {
  all_psv <- dir(path = "~/Data/PSMA-Geocoded-Address-202105/G-NAF/",
                 pattern = "\\.psv$",
                 full.names = TRUE,
                 recursive = TRUE)
  state_psv <- all_psv[grep(state, basename(all_psv))]
  all_names <-
    lapply(state_psv, function(file.psv) {
      names(fread(file = file.psv, sep = "|", nrows = 0))
    })
  files_with_cols <- state_psv[vapply(all_names, function(noms) all(cols %in% noms), NA)]
  if (!length(files_with_cols)) {
    cat("No matching files\n")
    return(invisible(NULL))
  }
  cat("Basenames\n\t", paste0(basename(files_with_cols), collapse = "\n\t"), sep = "")
  return(invisible(files_with_cols))
}

fread_psma <- function(type_pattern = ".",
                       state = "VIC",
                       multiple_ok = FALSE,
                       nrows = 1L) {
  all_psv <- dir(path = "~/Data/PSMA-Geocoded-Address-202105/G-NAF/", pattern = "\\.psv$", full.names = TRUE, recursive = TRUE)

  files2read <- all_psv[grepl(state, basename(all_psv)) & grepl(type_pattern, basename(all_psv), perl = TRUE)]
  if (length(files2read) == 0) {
    warning("len = ", length(files2read))
    return(data.table())
  }
  if (!isTRUE(multiple_ok) && length(files2read) != 1) {
    stop(length(files2read), " files:\n  ",
         paste0(basename(files2read), collapse = "\n  "))
  }
  if (length(files2read) > 1L) {
    L <- lapply(files2read, fread, sep = "|", nrows = nrows, showProgress = FALSE)
    names(L) <- hutils::trim_common_affixes(basename(files2read))
    return(L)
  }
  fread(file = files2read, sep = "|", nrows = nrows, showProgress = FALSE)
}

# Get Suburbs with 'ST' in them
ST_SUBURBS <-
  rbindlist(fread_psma("(?<!(STREET_))LOCALITY_ALIAS_psv", nrows = Inf, multiple_ok = TRUE, state = "."),
            idcol = "Ste") %>%
  unique(by = "NAME") %>%
  .[grep("\\bST\\b", NAME), unique(NAME)]
usethis::use_data(ST_SUBURBS, internal = TRUE)

# cat(.Permitted_street_type_ord_nchar_AZ()[, .(ans = paste0("const StreetType ZT_", STREET_CODE, " = {ST_CODE_", STREET_STANDARD, ", ", dQuote(STREET_CODE, q = F), ", ", nchar(STREET_CODE), "};"))][[1]], sep = "\n", file = provide.file("src/ZT.c"))

PAZ <- copy(.Permitted_street_type_ord_nchar_AZ())
cat("const StreetType ZTZ[", nrow(PAZ), "] = {\n", file = provide.file("src/ZT.c"), append = TRUE, sep = "")
for (i in 1:nrow(PAZ)) {
  cat("ZT_", PAZ$STREET_CODE[i], ", ", file = "src/ZT.c", append = TRUE, sep = "")
  if ((i %% 10L) == 0L) {
    cat("\n", file = "src/ZT.c", append = TRUE)
  }
}
cat("}\n", file = "src/ZT.c", append = TRUE)

PSMA_PATH <- "G:/PSMA-202311/G-NAF/G-NAF NOVEMBER 2023/Standard/"
.ste_chars <- c("NSW", "VIC", "QLD", "SA", "WA", "TAS", "NT", "ACT", "OT")
AY <-
  lapply(.ste_chars, function(ste) {
    ad <- dir(PSMA_PATH, pattern = paste0(ste, ".*ADDRESS_DETAIL.*psv$"), full.names = TRUE)
    st <- dir(PSMA_PATH, pattern = paste0(ste, ".*_STREET_LOCALITY_psv.*psv$"), full.names = TRUE)

    adf <- fread(file = ad, sep = "|", select = c("STREET_LOCALITY_PID", "POSTCODE"))
    stf <- fread(file = st, sep = "|", select = c("STREET_LOCALITY_PID", "STREET_NAME", "STREET_TYPE_CODE"))
    stf[, STREET_TYPE_CODE := chmatch(STREET_TYPE_CODE, healthyAddress:::.permitted_street_type_ord())]
    merge(unique(adf), unique(stf), by = "STREET_LOCALITY_PID")[, STREET_LOCALITY_PID := NULL]
  }) |>
  rbindlist(use.names = TRUE, fill = TRUE) |>
  setkey(POSTCODE, STREET_TYPE_CODE, STREET_NAME) %>%
  unique(by = key(.)) %>%
  setcolorder()

AZ <-
  read_ste_fst() %>%
  .[, .(POSTCODE, STREET_TYPE_CODE, STREET_NAME)] %>%
  unique %>%
  setkey(POSTCODE, STREET_TYPE_CODE, STREET_NAME) %>%
  .[]

AZZ <-
  rbind(AY, AZ) %>%
  setkey(POSTCODE, STREET_TYPE_CODE, STREET_NAME) %>%
  unique(by = key(.)) %>%
  setcolorder()

# We want to retain old addresses too
ORIG <- qs::qread("./inst/extdata/POSTCODE-STREET_TYPE_CODE-STREET_NAME.qs")

AZZZ <-
  rbind(AZZ, ORIG) %>%
  setkey(POSTCODE, STREET_TYPE_CODE, STREET_NAME) %>%
  unique(by = key(.)) %>%
  setcolorder()

qs::qsave(AZZZ, "./inst/extdata/POSTCODE-STREET_TYPE_CODE-STREET_NAME.qs")



