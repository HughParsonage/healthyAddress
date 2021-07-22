
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

.abbrev_street_names <- function() {
  fread(text = "Abbreviation,Name
  ALY,ALLEY
  ANX,ANNEX
  ARC,ARCADE
  AVE,AVENUE
  BYU,BAYOO
  BCH,BEACH
  BND,BEND
  BLF,BLUFF
  BLFS,BLUFFS
  BTM,BOTTOM
  BLVD,BOULEVARD
  BR,BRANCH
  BRG,BRIDGE
  BRK,BROOK
  BRKS,BROOKS
  BG,BURG
  BGS,BURGS
  BYP,BYPASS
  CP,CAMP
  CYN,CANYON
  CPE,CAPE
  CSWY,CAUSEWAY
  CTR,CENTER
  CTRS,CENTERS
  CIR,CIRCLE
  CIRS,CIRCLES
  CLF,CLIFF
  CLFS,CLIFFS
  CLB,CLUB
  CMN,COMMON
  COR,CORNER
  CORS,CORNERS
  CRSE,COURSE
  CT,COURT
  CTS,COURTS
  CV,COVE
  CVS,COVES
  CRK,CREEK
  CRES,CRESCENT
  CRST,CREST
  XING,CROSSING
  XRD,CROSSROAD
  CURV,CURVE
  DL,DALE
  DM,DAM
  DV,DIVIDE
  DR,DRIVE
  DRS,DRIVES
  EST,ESTATE
  ESTS,ESTATES
  EXPY,EXPRESSWAY
  EXT,EXTENSION
  EXTS,EXTENSIONS
  FALL,FALL
  FLS,FALLS
  FRY,FERRY
  FLD,FIELD
  FLDS,FIELDS
  FLT,FLAT
  FLTS,FLATS
  FRD,FORD
  FRDS,FORDS
  FRST,FOREST
  FRG,FORGE
  FRGS,FORGES
  FRK,FORK
  FRKS,FORKS
  FT,FORT
  FWY,FREEWAY
  GDN,GARDEN
  GDNS,GARDENS
  GTWY,GATEWAY
  GLN,GLEN
  GLNS,GLENS
  GRN,GREEN
  GRNS,GREENS
  GRV,GROVE
  GRVS,GROVES
  HBR,HARBOR
  HBRS,HARBORS
  HVN,HAVEN
  HTS,HEIGHTS
  HWY,HIGHWAY
  HL,HILL
  HLS,HILLS
  HOLW,HOLLOW
  INLT,INLET
  I,INTERSTATE
  IS,ISLAND
  ISS,ISLANDS
  ISLE,ISLE
  JCT,JUNCTION
  JCTS,JUNCTIONS
  KY,KEY
  KYS,KEYS
  KNL,KNOLL
  KNLS,KNOLLS
  LK,LAKE
  LKS,LAKES
  LAND,LAND
  LNDG,LANDING
  LN,LANE
  LGT,LIGHT
  LGTS,LIGHTS
  LF,LOAF
  LCK,LOCK
  LCKS,LOCKS
  LDG,LODGE
  LOOP,LOOP
  MALL,MALL
  MNR,MANOR
  MNRS,MANORS
  MDW,MEADOW
  MDWS,MEADOWS
  MEWS,MEWS
  ML,MILL
  MLS,MILLS
  MSN,MISSION
  MHD,MOORHEAD
  MTWY,MOTORWAY
  MT,MOUNT
  MTN,MOUNTAIN
  MTNS,MOUNTAINS
  NCK,NECK
  ORCH,ORCHARD
  OVAL,OVAL
  OPAS,OVERPASS
  PARK,PARK
  PARK,PARKS
  PKWY,PARKWAY
  PKWY,PARKWAYS
  PASS,PASS
  PSGE,PASSAGE
  PATH,PATH
  PIKE,PIKE
  PNE,PINE
  PNES,PINES
  PL,PLACE
  PLN,PLAIN
  PLNS,PLAINS
  PLZ,PLAZA
  PT,POINT
  PTS,POINTS
  PRT,PORT
  PRTS,PORTS
  PR,PRAIRIE
  RADL,RADIAL
  RAMP,RAMP
  RNCH,RANCH
  RPD,RAPID
  RPDS,RAPIDS
  RST,REST
  RDG,RIDGE
  RDGS,RIDGES
  RIV,RIVER
  RD,ROAD
  RDS,ROADS
  RTE,ROUTE
  ROW,ROW
  RUE,RUE
  RUN,RUN
  SHL,SHOAL
  SHLS,SHOALS
  SHR,SHORE
  SHRS,SHORES
  SKWY,SKYWAY
  SPG,SPRING
  SPGS,SPRINGS
  SPUR,SPUR
  SPUR,SPURS
  SQ,SQUARE
  SQS,SQUARES
  STA,STATION
  STRM,STREAM
  ST,STREET
  STS,STREETS
  SMT,SUMMIT
  TER,TERRACE
  TRWY,THROUGHWAY
  TRCE,TRACE
  TRAK,TRACK
  TRL,TRAIL
  TUNL,TUNNEL
  TPKE,TURNPIKE
  UPAS,UNDERPASS
  UN,UNION
  UNS,UNIONS
  VLY,VALLEY
  VLYS,VALLEYS
  VIA,VIADUCT
  VW,VIEW
  VWS,VIEWS
  VLG,VILLAGE
  VLGS,VILLAGES
  VL,VILLE
  VIS,VISTA
  WALK,WALK
  WALK,WALKS
  WALL,WALL
  WAY,WAY
  WAYS,WAYS
  WL,WELL
  WLS,WELLS
  APT,APARTMENT
  BSMT *,BASEMENT
  BLDG,BUILDING
  DEPT,DEPARTMENT
  FL,FLOOR
  FRNT *,FRONT
  HNGR,HANGAR
  LBBY *,LOBBY
  LOT,LOT
  LOWR *,LOWER
  OFC *,OFFICE
  PH *,PENTHOUSE
  PIER,PIER
  REAR *,REAR
  RM,ROOM
  SIDE *,SIDE
  SLIP,SLIP
  SPC,SPACE
  STOP,STOP
  STE,SUITE
  TRLR,TRAILER
  UNIT,UNIT
  UPPR *,UPPER", sep = ",")
}



street_cd <- function(ADDRESS) {
  WHICH_TYPE <- rep_len(NA_integer_, length(address))
  ADDRESS <- fcoalesce(ADDRESS, "")
  ADDRESS <- sub("\\bRD\\b", "ROAD", ADDRESS)

  # 'ST' (i.e. ST GEORGE) may not always be street
  ADDRESS <- sub("\\bST$", "STREET", ADDRESS)
  permitted_street_type_ord <- .permitted_street_type_ord()
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

extract_standard_address <- function(address, LocalityByPostcode = NULL) {
  # LocStePoa <- FindLocality(address)


}

.set_cols_first <- function(DT, cols) {
  return(setcolorder(DT, c(intersect(cols, names(DT)), setdiff(names(DT), cols))))
}

CExtractStdAddress2 <- function(address, street_names) {
  .Call("CExtractStdAddress", address, .permitted_street_type_ord(), PACKAGE = packageName())
}
CwhichStreetName3_ <- function(x) {
  stopifnot(is.character(x))
  .Call("CwhichStreetName3", x, PACKAGE = packageName())
}



FindSentence <- function(x, word1, word2) {
  .Call("CFindSentence", x, word1, word2, PACKAGE = packageName())
}


# Returns the
LocalityGivenPostcode <- function(address, poa) {

  # We want to load the namespace
  if (!requireNamespace("PSMA", quietly = TRUE)) {
    stop("Package PSMA is required. See library(PSMA.foyer) for installation details.")
  }

  stopifnot(is.character(address), is.integer(poa), length(address) == length(poa))
  stopifnot(isNamespaceLoaded("PSMA"))
  if (is.null(cache_env)) {
    cache_env <- getOption("PSMA_env", new.env())
  }

  # LOCALITY_vs_LOCALITY_PID <- PSMA::get_fst("LOCALITY_vs_LOCALITY_PID",
  #                                           cache_env = cache_env)
  # LOCALITY_VS_POSTCODE <- PSMA::get_fst("LOCALITY_VS_POSTCODE")
  # STREET_BY_POSTCODE <- PSMA::get_fst("STREET_BY_POSTCODE")

  FullNamedAddressData <-
    if (exists("FullNamedAddressData", envir = cache_env, inherits = FALSE)) {
      get("FullNamedAddressData", envir = cache_env, inherits = FALSE)
    } else {
      X <- PSMA::get_fst("STREET_LOCALITY_ID__STREET_NAME_STREET_TYPE_CODE")
      Y <- PSMA::get_fst("STREET_ID_vs_ADDRESS_ID")
      Z <- X[Y,
             .(ADDRESS_DETAIL_INTRNL_ID, POSTCODE, STREET_TYPE_CODE, STREET_NAME, NUMBER_FIRST),
             on = .(STREET_LOCALITY_INTRNL_ID)]
      setkeyv(Z, c("POSTCODE", "STREET_TYPE_CODE", "STREET_NAME", "NUMBER_FIRST"))
      assign("FullNamedAddressData",
             Z,
             envir = cache_env)
    }
  setkeyv(FullNamedAddressData, c("POSTCODE", "STREET_TYPE_CODE", "STREET_NAME", "NUMBER_FIRST"))

  i <- min_i <- max_i <- NULL
  STREET_BY_POSTCODE[, i := 0:(.N - 1L)]
  minmax_i <- STREET_BY_POSTCODE[, .(min_i = min(i), max_i = max(i)), keyby = "POSTCODE"]

  # Create a table such that poa_by_r[p] = postcode
  poa_by_r <- data.table(POSTCODE = 0:(STREET_BY_POSTCODE[, max(POSTCODE)]))
  setkeyv(poa_by_r, "POSTCODE")
  minmax_i[poa_by_r, on = "POSTCODE"]

  FullNamedAddressData



}

EnsureUC <- function(x) {
  .Call("CEnsureUC", x, PACKAGE = packageName())
}

do_EncodeStreet <- function(x) {
  x <- EnsureUC(x)
  m <- chmatch(x, .permitted_street_type_ord(), nomatch = 0L)
  Abbrev <- PSMA::street_type_decoder$street_abbrev
  Abbrevi <- chmatch(PSMA::street_type_decoder$street_type, .permitted_street_type_ord(), nomatch = 0L)
  .Call("CEncodeStCd", x, m, Abbrev, Abbrevi, PACKAGE = packageName())
}



Extract2_ <- function(xx, id, Postcodes, StreetTypes, StreetNames, Numbers) {
  .Call("Extract2", xx, id, Postcodes, StreetTypes, StreetNames, Numbers,
        chmatch(StreetTypes, .permitted_street_type_ord(), nomatch = 0L),
        PACKAGE = packageName())
}

test_touppers <- function(x) {
  .Call("Ctest_touppers", x, PACKAGE = packageName())
}

