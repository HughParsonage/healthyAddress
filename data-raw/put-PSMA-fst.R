suppressMessages({
library(data.table)
library(hutilscpp)
library(hutils)
library(magrittr)
library(fst)
devtools::load_all(quiet = TRUE)
})

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

files_psv <- dir("~/Data/PSMA-Geocoded-Address-202105/G-NAF/G-NAF MAY 2021/Standard",
                 full.names = TRUE,
                 pattern = "\\.psv$")
files_ <- trim_common_affixes(files_psv)
for (i in seq_along(files_psv)) {
  if (exists(files_[i]) || grepl("201", files_[i])) {
    next
  }
  cat(hh_ss(), "\t", formatC(files_[i], width = max(nchar(files_))), "\n")
  assign(files_[i], value = fread(file = files_psv[i], sep = "|", showProgress = FALSE))
}


do_full_Address <- function(ste) {
  cat(hh_ss(), "\t", formatC(ste, width = 4), "\n")
  STE_ADDRESS_DETAIL <- get(paste0(ste, "_ADDRESS_DETAIL"))
  STE_STREET_LOCALITY <- get(paste0(ste, "_STREET_LOCALITY"))

  STE_FULL_ADDRESS <-
    merge(selector(STE_ADDRESS_DETAIL,
                   cols = c("ADDRESS_SITE_PID",
                            # "BUILDING_NAME",
                            # "LOT_NUMBER",
                            "FLAT_NUMBER",
                            "NUMBER_FIRST",
                            "NUMBER_FIRST_SUFFIX",
                            "NUMBER_LAST",
                            "STREET_LOCALITY_PID",
                            "POSTCODE")),

          selector(STE_STREET_LOCALITY,
                   cols = c("STREET_LOCALITY_PID",
                            "STREET_NAME",
                            "STREET_TYPE_CODE")),
          by = "STREET_LOCALITY_PID") %>%
    #
    .[, "STREET_TYPE_CODE" := chmatch(STREET_TYPE_CODE,
                                      healthyAddress:::.permitted_street_type_ord())] %>%
    .[, "STREET_LOCALITY_PID" := NULL] %>%
    .[, hSTREET_NAME := HashStreetName(STREET_NAME)] %>%
    set_cols_last("NUMBER_FIRST_SUFFIX") %>%
    setkey(POSTCODE, STREET_TYPE_CODE, STREET_NAME, NUMBER_FIRST, FLAT_NUMBER) %>%
    .[, "NUMBER_FIRST_SUFFIX" := NumberSuffix2Raw(NUMBER_FIRST_SUFFIX)] %>%
    .[]
  if (dir.exists("inst/extdata")) {
    fst::write_fst(STE_FULL_ADDRESS,
                   paste0("inst/extdata/", ste, "_FULL_ADDRESS.fst"),
                   compress = 85)
  }
  STE_FULL_ADDRESS
}

.ste_chars <- c("NSW", "VIC", "QLD", "SA", "WA", "TAS", "NT", "ACT", "OT")

ListofSTE_FullAddresses <-
  lapply(.ste_chars,
         do_full_Address) %>%
  setNames(.ste_chars)



if (FALSE) {
  LATEST <- normalizePath("~/Data/PSMA-Geocoded-Address-202105/",
                          winslash = "/")

  ADDRESS_DETAIL_PID__by__LATLON <-
    dir(pattern = "_ADDRESS_DEFAULT_GEOCODE_psv",
        recursive = TRUE,
        full.names = TRUE,
        path = LATEST) %>%
    lapply(fread,
           na.strings = "",
           select = c("ADDRESS_DETAIL_PID",
                      "LATITUDE",
                      "LONGITUDE"),
           key = "ADDRESS_DETAIL_PID") %>%
    rbindlist %>%
    setkeyv("ADDRESS_DETAIL_PID")

  STREET_PID_vs_ADDRESS_PID <-
    dir(pattern = "_ADDRESS_DETAIL_psv.psv$",
        path = LATEST,
        recursive = TRUE,
        full.names = TRUE) %>%
    lapply(fread,
           na.strings = "",
           select = c("ADDRESS_DETAIL_PID",
                      # "DATE_CREATED",
                      # "DATE_LAST_MODIFIED",
                      # "DATE_RETIRED",
                      "BUILDING_NAME",
                      # "LOT_NUMBER_PREFIX",
                      "LOT_NUMBER",
                      # "LOT_NUMBER_SUFFIX",
                      # "FLAT_TYPE_CODE",
                      # "FLAT_NUMBER_PREFIX",
                      "FLAT_NUMBER",
                      # "FLAT_NUMBER_SUFFIX",
                      # "LEVEL_TYPE_CODE",
                      # "LEVEL_NUMBER_PREFIX",
                      # "LEVEL_NUMBER",
                      # "LEVEL_NUMBER_SUFFIX",
                      # "NUMBER_FIRST_PREFIX",
                      "NUMBER_FIRST",
                      # "NUMBER_FIRST_SUFFIX",
                      # "NUMBER_LAST_PREFIX",
                      # "NUMBER_LAST",
                      # "NUMBER_LAST_SUFFIX",
                      "STREET_LOCALITY_PID",
                      # "LOCATION_DESCRIPTION",
                      # "LOCALITY_PID",
                      # "ALIAS_PRINCIPAL",
                      "POSTCODE"
                      # "PRIVATE_STREET",
                      # "LEGAL_PARCEL_ID",
                      # "CONFIDENCE",
                      # "ADDRESS_SITE_PID",
                      # "LEVEL_GEOCODED_CODE",
                      # "PROPERTY_PID",
                      # "GNAF_PROPERTY_PID",
                      # "PRIMARY_SECONDARY"
           )) %>%
    rbindlist(use.names = TRUE, fill = TRUE) %>%
    setkey(ADDRESS_DETAIL_PID)

  STREET_LOCALITY_PID__STREET_NAME_STREET_TYPE_CODE <-
    dir(pattern = "_STREET_LOCALITY_psv.psv$",
        path = LATEST,
        recursive = TRUE,
        full.names = TRUE) %>%
    lapply(fread,
           na.strings = "",
           select = c("STREET_LOCALITY_PID",
                      "STREET_NAME",
                      "STREET_TYPE_CODE")) %>%
    rbindlist(use.names = TRUE, fill = TRUE)
}

absent_postcodes <-
  c(815L, 2006L, 2052L, 2109L, 2123L, 2129L, 2139L, 2314L, 2351L,
    2522L, 2755L, 3005L, 3010L, 3050L, 3086L, 3694L, 3800L, 4029L,
    4072L, 4222L, 4229L, 4230L, 4271L, 4345L, 4475L, 4801L, 5005L,
    6712L,
    6711L, 6731L, 6733L, 6762L, 7001L)

# guesses
absent_postcode_states <-
  fcase(absent_postcodes == 815,
        "NT",
        absent_postcodes < 3000,
        "NSW",
        absent_postcodes < 4000,
        "VIC",
        absent_postcodes < 5000,
        "QLD",
        absent_postcodes < 6000,
        "SA",
        absent_postcodes < 7000,
        "WA",
        absent_postcodes < 8000,
        "TAS",
        default = "OT")

rbindlist(lapply(ListofSTE_FullAddresses, function(DT) DT[, .(POSTCODE = unique(POSTCODE))]),
          idcol = "ste_int") %>%
  rbind(data.table(POSTCODE = absent_postcodes,
                   ste_int = absent_postcode_states),
        use.names = TRUE, fill = TRUE) %>%
  .[, nStates := .N, by = .(POSTCODE)] %>%
  .[, ste_int := match(ste_int, .ste_chars)] %>%
  set_cols_first("POSTCODE") %>%
  setkey(POSTCODE, ste_int) %>%
  write_fst("inst/extdata/Postcode2ste.fst") %>%
  .[]

