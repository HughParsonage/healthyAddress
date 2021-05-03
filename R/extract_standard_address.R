
permitted_street_cds <- function() {
  c("ACCESS", "ACRE",
    "ALLEY", "AMBLE", "APPROACH",
    "ARCADE", "ARTERIAL", "AVENUE",
    "BANAN", "BANK", "BAY", "BEACH",
    "BEND", "BOARDWALK", "BOULEVARD",
    "BOULEVARDE", "BOWL", "BRACE",
    "BRAE", "BRANCH", "BREAK",
    "BRIDGE", "BROADWAY", "BROW",
    "BUSWAY", "BYPASS", "BYWAY",
    "CAUSEWAY", "CENTRE", "CENTREWAY",
    "CHASE", "CIRCLE", "CIRCUIT",
    "CIRCUS", "CLOSE", "CLUSTER",
    "COMMON", "COMMONS", "CONCORD",
    "CONCOURSE", "CONNECTION", "COPSE",
    "CORNER", "CORSO", "COURSE",
    "COURT", "COURTYARD", "COVE",
    "CRESCENT", "CREST", "CRIEF",
    "CROSS", "CROSSING", "CRUISEWAY",
    "CUL-DE-SAC", "CUTTING", "DALE",
    "DASH", "DELL", "DENE", "DEVIATION",
    "DIP", "DISTRIBUTOR", "DIVIDE",
    "DOCK", "DOMAIN", "DOWN", "DOWNS",
    "DRIVE", "DRIVEWAY", "EASEMENT",
    "EAST", "EDGE", "ELBOW", "END",
    "ENTRANCE", "ESPLANADE", "ESTATE",
    "EXPRESSWAY", "EXTENSION", "FAIRWAY",
    "FIREBREAK", "FIRELINE", "FIRETRACK",
    "FIRETRAIL", "FLAT", "FLATS",
    "FOLLOW", "FORD", "FORESHORE",
    "FORK", "FORMATION", "FREEWAY",
    "FRONTAGE", "GAP", "GARDEN",
    "GARDENS", "GATE", "GATEWAY",
    "GLADE", "GLEN", "GRANGE",
    "GREEN", "GROVE", "GULLY",
    "HARBOUR", "HAVEN", "HEATH",
    "HEIGHTS", "HIGHWAY", "HIKE",
    "HILL", "HILLS", "HOLLOW",
    "HUB", "INTERCHANGE", "ISLAND",
    "JUNCTION", "KEY", "KEYS",
    "LADDER", "LANDING", "LANE",
    "LANEWAY", "LINE", "LINK",
    "LOOKOUT", "LOOP", "LYNNE",
    "MALL", "MANOR", "MART", "MAZE",
    "MEAD", "MEANDER", "MEWS",
    "MILE", "MOTORWAY", "NOOK",
    "NORTH", "OUTLET", "OUTLOOK",
    "PALMS", "PARADE", "PARK",
    "PARKWAY", "PASS", "PASSAGE",
    "PATH", "PATHWAY", "PLACE",
    "PLAZA", "POCKET", "POINT",
    "PORT", "PRECINCT", "PROMENADE",
    "PURSUIT", "QUADRANT", "QUAY",
    "QUAYS", "RAMBLE", "RAMP",
    "RANGE", "REACH", "RESERVE",
    "REST", "RETREAT", "RETURN",
    "RIDE", "RIDGE", "RISE", "RISING",
    "RIVER", "ROAD", "ROADS", "ROADWAY",
    "ROTARY", "ROUND", "ROUTE",
    "ROW", "RUN", "SERVICEWAY",
    "SKYLINE", "SLOPE", "SOUTH",
    "SPUR", "SQUARE", "STEPS",
    "STRAIGHT", "STRAIT", "STREET",
    "STRIP", "SUBWAY", "TARN",
    "TERRACE", "THROUGHWAY", "TOP",
    "TOR", "TRACK", "TRAIL", "TRAMWAY",
    "TRAVERSE", "TRUNKWAY", "TUNNEL",
    "TURN", "TWIST", "UNDERPASS",
    "VALE", "VALLEY", "VIEW", "VIEWS",
    "VILLA", "VILLAGE", "VISTA",
    "WALK", "WALKWAY", "WATERS",
    "WATERWAY", "WAY", "WEST",
    "WHARF", "WOODS", "WYND", "YARD")
}
# ordered from most common to least
.permitted_street_type_ord <- function() {
  c("ROAD", "STREET", "COURT", "AVENUE", "PLACE", "LANE", "DRIVE",
    "CLOSE", "TRACK", "CRESCENT", "WAY", "TRAIL", "HIGHWAY", "TERRACE",
    "PARADE", "GROVE", "ACCESS", "CIRCUIT", "RAMP", "BOULEVARD",
    "WALK", "RISE", "FIRETRAIL", "BREAK", "LOOP", "MEWS", "LINK",
    "GARDENS", "CIRCLE", "PARKWAY", "FREEWAY", "VIEW", "RETREAT",
    "COVE", "ESPLANADE", "SQUARE", "PASS", "MOTORWAY", "PATHWAY",
    "VISTA", "TURN", "BEND", "CHASE", "GREEN", "ENTRANCE", "HEIGHTS",
    "GLEN", "PROMENADE", "ROW", "RIDGE", "FIREBREAK", "GLADE", "APPROACH",
    "PATH", "RUN", "BYPASS", "ALLEY", "ARCADE", "ELBOW", "BRACE",
    "CORNER", "ROUTE", "RAMBLE", "FIRELINE", "CROSSING", "GATE",
    "GRANGE", "FAIRWAY", "LOOKOUT", "POINT", "HILL", "CREST", "LANEWAY",
    "EXPRESSWAY", "LINE", "MALL", "MEANDER", "OUTLOOK", "BAY", "CROSS",
    "WALKWAY", "FIRETRACK", "BRIDGE", "PARK", "PLAZA", "NOOK", "WYND",
    "VALE", "DOWNS", "SPUR", "BUSWAY", "CIRCUS", "POCKET", "BOARDWALK",
    "CONCOURSE", "RIVER", "QUAYS", "RESERVE", "DALE", "ISLAND", "REST",
    "CONNECTION", "END", "QUAY", "VIEWS", "KEY", "TRAVERSE", "BOULEVARDE",
    "FORMATION", "OUTLET", "DRIVEWAY", "LANDING", "EDGE", "QUADRANT",
    "VALLEY", "WATERS", "CAUSEWAY", "BEACH", "SERVICEWAY", "CENTRE",
    "EASEMENT", "PASSAGE", "STRIP", "TARN", "BRAE", "DEVIATION",
    "JUNCTION", "STEPS", "WHARF", "BOWL", "COURSE", "GAP", "GULLY",
    "TUNNEL", "CUTTING", "ESTATE", "EXTENSION", "FORESHORE", "GATEWAY",
    "HAVEN", "ROTARY", "COMMON", "COPSE", "DISTRIBUTOR", "FOLLOW",
    "FRONTAGE", "TOR", "ARTERIAL", "BANK", "NORTH", "ROADS", "UNDERPASS",
    "BROW", "HEATH", "LADDER", "PRECINCT", "RANGE", "SOUTH", "TRUNKWAY",
    "AMBLE", "BANAN", "BRANCH", "CORSO", "DIVIDE", "DOCK", "FORD",
    "FORK", "GARDEN", "HIKE", "HOLLOW", "INTERCHANGE", "PALMS", "RIDE",
    "ROUND", "SLOPE", "STRAIT", "SUBWAY", "TOP", "TRAMWAY", "BROADWAY",
    "CLUSTER", "DELL", "DOMAIN", "FLAT", "HUB", "LYNNE", "MEAD",
    "MILE", "PORT", "REACH", "RETURN", "STRAIGHT", "VILLAGE", "WEST",
    "WOODS", "ACRE", "BYWAY", "CENTREWAY", "COMMONS", "CONCORD",
    "COURTYARD", "CRIEF", "CRUISEWAY", "CUL-DE-SAC", "DASH", "DENE",
    "DIP", "DOWN", "EAST", "FLATS", "HARBOUR", "HILLS", "KEYS", "MANOR",
    "MART", "MAZE", "PURSUIT", "RISING", "ROADWAY", "THROUGHWAY",
    "TWIST", "VILLA", "WATERWAY", "YARD")
}



street_cd <- function(ADDRESS) {
  WHICH_TYPE <- rep_len(NA_integer_, length(address))
  ADDRESS <- fcoalesce(ADDRESS, "")
  ADDRESS <- sub("\\bRD\\b", "ROAD", ADDRESS)

  # 'ST' (i.e. ST GEORGE) may not always be street
  ADDRESS <- sub("\\bST$", "STREET", ADDRESS)
  for (i in seq_along(permitted_street_type_ord)) {
    street_cdi <- permitted_street_type_ord[i]
    # if the address ends with this street code, note that
    ewi <- endsWith(ADDRESS, street_cdi)
    # replace unless already replaced
    fewi <- fcoalesce(WHICH_TYPE[ewi], i)

    WHICH_TYPE[ewi] <- fewi
  }





  out <- data.table(ADDRESS,
                    TYPE = permitted_street_type_ord[WHICH_TYPE])
  out[, NAME := sub(paste0("^.*[0-9] ([A-Z ]+) ", .BY[[1]]), "\\1", ADDRESS), by = .(TYPE)]
  setcolorder(out, c("ADDRESS", "NAME", "TYPE"))
  out[]
}

#' @name toupper_basic
#' @title Uppercase
#' @param x A character vector
#' @export
toupper_basic <- function(x) {
  stopifnot(is.character(x))
  .Call("CToUpperBasic", x, PACKAGE = packageName())
}

extract_standard_address <- function(address) {

  ADDRESS <- gsub("[^A-Z0-9 /]", "", toupper(trimws(address)))

  unit_no <-
    fcase(grepl("^U(NIT)? [0-9]", ADDRESS),
          as.integer(sub("^U(?:NIT)? ([0-9]+)[^0-9].*$", "\\1", ADDRESS)),

          # e.g. G02/56 Felmington
          grepl("^G?[0-9]+\\s*/\\s*[0-9]+\\s*", ADDRESS),
          as.integer(sub("^G?([0-9]+)\\s*/.*$", "\\1", ADDRESS)),
          default = NA_integer_)


  # for things like 85-89 just use 85
  has_number <- grepl("[0-9]", address)
  street_no <- fifelse(has_number,
                       sub("^[^0-9]*([0-9]+).*$", "\\1", address, perl = TRUE),
                       "")

  ans <- street_cd(ADDRESS)
  ans[, "street_no" := street_no]
  ans[, "address" := address]
  ans[, "flat_number" := unit_no]
  .set_cols_first(ans, "address")
  ans[]
}

.set_cols_first <- function(DT, cols) {
  return(setcolorder(DT, c(intersect(cols, names(DT)), setdiff(names(DT), cols))))
}


