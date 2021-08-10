library(data.table)
library(hutilscpp)
library(hutils)
library(magrittr)
library(fst)

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
  if (exists(files_[i])) {
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
                   cols = c("ADDRESS_DETAIL_PID",
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
    .[, (paste0(ste, "_GA_INTRNL_ADDRESS_ID")) := as.integer(substr(ADDRESS_DETAIL_PID, 6L, 14L))] %>%
    .[, ADDRESS_DETAIL_PID := NULL] %>%
    .[, "STREET_TYPE_CODE" := chmatch(STREET_TYPE_CODE,
                                      healthyAddress:::.permitted_street_type_ord())] %>%
    .[, "STREET_LOCALITY_PID" := NULL] %>%
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

ListofSTE_FullAddresses <-
  lapply(c("NSW", "VIC", "QLD", "SA", "WA", "TAS", "NT", "ACT", "OT"),
         do_full_Address)


VIC_FULL_ADDRESS <-
  merge(selector(VIC_ADDRESS_DETAIL,
                 cols = c("ADDRESS_DETAIL_PID",
                          "BUILDING_NAME",
                          "LOT_NUMBER",
                          "FLAT_NUMBER",
                          "LEVEL_NUMBER_PREFIX",
                          "LEVEL_NUMBER",
                          "LEVEL_NUMBER_SUFFIX",
                          "NUMBER_FIRST_PREFIX",
                          "NUMBER_FIRST",
                          "NUMBER_FIRST_SUFFIX",
                          "NUMBER_LAST_PREFIX",
                          "NUMBER_LAST",
                          "NUMBER_LAST_SUFFIX",
                          "STREET_LOCALITY_PID",
                          "POSTCODE")),

        selector(VIC_STREET_LOCALITY,
                 cols = c("STREET_LOCALITY_PID",
                          "STREET_NAME",
                          "STREET_TYPE_CODE")),
        by = "STREET_LOCALITY_PID")
fwalnume_address_detail_id <- dhhs::fwalnume(VIC_FULL_ADDRESS$ADDRESS_DETAIL_PID)
encoded <- dhhs::encode_ID(VIC_FULL_ADDRESS$ADDRESS_DETAIL_PID,
                          cipher = fwalnume_address_detail_id)
set(VIC_FULL_ADDRESS,
    j = "healthyAddress_202105_VIC_INTRNL_ADDRESS_DETAIL_PID",
    value = encoded)


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

rbindlist(lapply(ListofSTE_FullAddresses, function(DT) DT[, .(POSTCODE = unique(POSTCODE))]),
          idcol = "ste_int") %>%
  set_cols_first("POSTCODE") %>%
  setkey(POSTCODE, ste_int) %>%
  .[, nStates := .N, by = .(POSTCODE)] %>%
  write_fst("inst/extdata/Postcode2ste.fst") %>%
  .[]


































