
#include "healthyAddress.h"
#include "streetcodes.h"


typedef struct {
  int flat_number;
  int number_first;
  int number_last;
  unsigned char suffix;
  int hashStreetName;
  int street_type;
  int postcode;
} Address;

typedef struct {
  int cd;
  const char * x;
  int lenx;
} StreetType;


typedef struct {
  int postcode;
  int n_saints;
  const char * suf;
  int nsuf;
  const char * suf2;
  int nsuf2;

} Saint;

#define NZ 274
#define ST_ST_ST 12
// ST_ST_ST position in the StreetType array for ST as 'Street'

const StreetType ZT_AV = {ST_CODE_AVENUE, "AV", 2};
const StreetType ZT_BR = {ST_CODE_BRANCH, "BR", 2};
const StreetType ZT_CH = {ST_CODE_CHASE, "CH", 2};
const StreetType ZT_CL = {ST_CODE_CLOSE, "CL", 2};
const StreetType ZT_CR = {ST_CODE_CRESCENT, "CR", 2};
const StreetType ZT_CT = {ST_CODE_COURT, "CT", 2};
const StreetType ZT_DR = {ST_CODE_DRIVE, "DR", 2};
const StreetType ZT_GR = {ST_CODE_GROVE, "GR", 2};
const StreetType ZT_LN = {ST_CODE_LANE, "LN", 2};
const StreetType ZT_PL = {ST_CODE_PLACE, "PL", 2};
const StreetType ZT_RD = {ST_CODE_ROAD, "RD", 2};
const StreetType ZT_SQ = {ST_CODE_SQUARE, "SQ", 2};
const StreetType ZT_ST = {ST_CODE_STREET, "ST", 2};
const StreetType ZT_AVE = {ST_CODE_AVENUE, "AVE", 3};
const StreetType ZT_BAY = {ST_CODE_BAY, "BAY", 3};
const StreetType ZT_BVD = {ST_CODE_BOULEVARD, "BVD", 3};
const StreetType ZT_CCT = {ST_CODE_CIRCUIT, "CCT", 3};
const StreetType ZT_CIR = {ST_CODE_CIRCLE, "CIR", 3};
const StreetType ZT_CNR = {ST_CODE_CORNER, "CNR", 3};
const StreetType ZT_DIP = {ST_CODE_DIP, "DIP", 3};
const StreetType ZT_DOM = {ST_CODE_DOMAIN, "DOM", 3};
const StreetType ZT_DPS = {ST_CODE_ROAD, "DPS", 3};
const StreetType ZT_DVE = {ST_CODE_DRIVE, "DVE", 3};
const StreetType ZT_END = {ST_CODE_END, "END", 3};
const StreetType ZT_ESP = {ST_CODE_ESPLANADE, "ESP", 3};
const StreetType ZT_EST = {ST_CODE_ESTATE, "EST", 3};
const StreetType ZT_GAP = {ST_CODE_GAP, "GAP", 3};
const StreetType ZT_GDN = {ST_CODE_GARDEN, "GDN", 3};
const StreetType ZT_GLD = {ST_CODE_GLADE, "GLD", 3};
const StreetType ZT_GRA = {ST_CODE_GRANGE, "GRA", 3};
const StreetType ZT_GRN = {ST_CODE_GREEN, "GRN", 3};
const StreetType ZT_GTE = {ST_CODE_GATE, "GTE", 3};
const StreetType ZT_HUB = {ST_CODE_HUB, "HUB", 3};
const StreetType ZT_HWY = {ST_CODE_HIGHWAY, "HWY", 3};
const StreetType ZT_KEY = {ST_CODE_KEY, "KEY", 3};
const StreetType ZT_PDE = {ST_CODE_PARADE, "PDE", 3};
const StreetType ZT_PNT = {ST_CODE_POINT, "PNT", 3};
const StreetType ZT_ROW = {ST_CODE_ROW, "ROW", 3};
const StreetType ZT_RTE = {ST_CODE_ROUTE, "RTE", 3};
const StreetType ZT_RTT = {ST_CODE_RETREAT, "RTT", 3};
const StreetType ZT_RUN = {ST_CODE_RUN, "RUN", 3};
const StreetType ZT_RVR = {ST_CODE_RIVER, "RVR", 3};
const StreetType ZT_TCE = {ST_CODE_TERRACE, "TCE", 3};
const StreetType ZT_TOP = {ST_CODE_TOP, "TOP", 3};
const StreetType ZT_TOR = {ST_CODE_TOR, "TOR", 3};
const StreetType ZT_TRK = {ST_CODE_TRACK, "TRK", 3};
const StreetType ZT_TRL = {ST_CODE_TRAIL, "TRL", 3};
const StreetType ZT_WAY = {ST_CODE_WAY, "WAY", 3};
const StreetType ZT_ACCS = {ST_CODE_ACCESS, "ACCS", 4};
const StreetType ZT_ACRE = {ST_CODE_ACRE, "ACRE", 4};
const StreetType ZT_BANK = {ST_CODE_BANK, "BANK", 4};
const StreetType ZT_BEND = {ST_CODE_BEND, "BEND", 4};
const StreetType ZT_BLVD = {ST_CODE_BOULEVARD, "BLVD", 4};
const StreetType ZT_BOWL = {ST_CODE_BOWL, "BOWL", 4};
const StreetType ZT_BRAE = {ST_CODE_BRAE, "BRAE", 4};
const StreetType ZT_BROW = {ST_CODE_BROW, "BROW", 4};
const StreetType ZT_BVDE = {ST_CODE_BOULEVARD, "BVDE", 4};
const StreetType ZT_COVE = {ST_CODE_COVE, "COVE", 4};
const StreetType ZT_CRES = {ST_CODE_CRESCENT, "CRES", 4};
const StreetType ZT_CRST = {ST_CODE_CREST, "CRST", 4};
const StreetType ZT_DALE = {ST_CODE_DALE, "DALE", 4};
const StreetType ZT_DASH = {ST_CODE_DASH, "DASH", 4};
const StreetType ZT_DELL = {ST_CODE_DELL, "DELL", 4};
const StreetType ZT_DENE = {ST_CODE_DENE, "DENE", 4};
const StreetType ZT_DOCK = {ST_CODE_DOCK, "DOCK", 4};
const StreetType ZT_DOWN = {ST_CODE_DOWN, "DOWN", 4};
const StreetType ZT_DRWY = {ST_CODE_DRIVEWAY, "DRWY", 4};
const StreetType ZT_EAST = {ST_CODE_EAST, "EAST", 4};
const StreetType ZT_EDGE = {ST_CODE_EDGE, "EDGE", 4};
const StreetType ZT_FLAT = {ST_CODE_FLAT, "FLAT", 4};
const StreetType ZT_FORD = {ST_CODE_FORD, "FORD", 4};
const StreetType ZT_FORK = {ST_CODE_FORK, "FORK", 4};
const StreetType ZT_GATE = {ST_CODE_GATE, "GATE", 4};
const StreetType ZT_GDNS = {ST_CODE_GARDENS, "GDNS", 4};
const StreetType ZT_GLEN = {ST_CODE_GLEN, "GLEN", 4};
const StreetType ZT_HIKE = {ST_CODE_HIKE, "HIKE", 4};
const StreetType ZT_HILL = {ST_CODE_HILL, "HILL", 4};
const StreetType ZT_KEYS = {ST_CODE_KEYS, "KEYS", 4};
const StreetType ZT_LANE = {ST_CODE_LANE, "LANE", 4};
const StreetType ZT_LINE = {ST_CODE_LINE, "LINE", 4};
const StreetType ZT_LINK = {ST_CODE_LINK, "LINK", 4};
const StreetType ZT_LOOP = {ST_CODE_LOOP, "LOOP", 4};
const StreetType ZT_MALL = {ST_CODE_MALL, "MALL", 4};
const StreetType ZT_MART = {ST_CODE_MART, "MART", 4};
const StreetType ZT_MAZE = {ST_CODE_MAZE, "MAZE", 4};
const StreetType ZT_MEAD = {ST_CODE_MEAD, "MEAD", 4};
const StreetType ZT_MEWS = {ST_CODE_MEWS, "MEWS", 4};
const StreetType ZT_MILE = {ST_CODE_MILE, "MILE", 4};
const StreetType ZT_NOOK = {ST_CODE_NOOK, "NOOK", 4};
const StreetType ZT_PARK = {ST_CODE_PARK, "PARK", 4};
const StreetType ZT_PASS = {ST_CODE_PASS, "PASS", 4};
const StreetType ZT_PATH = {ST_CODE_PATH, "PATH", 4};
const StreetType ZT_PHWY = {ST_CODE_PATHWAY, "PHWY", 4};
const StreetType ZT_PKWY = {ST_CODE_PARKWAY, "PKWY", 4};
const StreetType ZT_PORT = {ST_CODE_PORT, "PORT", 4};
const StreetType ZT_PROM = {ST_CODE_PROMENADE, "PROM", 4};
const StreetType ZT_QUAY = {ST_CODE_QUAY, "QUAY", 4};
const StreetType ZT_RAMP = {ST_CODE_RAMP, "RAMP", 4};
const StreetType ZT_RDGE = {ST_CODE_RIDGE, "RDGE", 4};
const StreetType ZT_RDWY = {ST_CODE_ROADWAY, "RDWY", 4};
const StreetType ZT_REST = {ST_CODE_REST, "REST", 4};
const StreetType ZT_RIDE = {ST_CODE_RIDE, "RIDE", 4};
const StreetType ZT_RISE = {ST_CODE_RISE, "RISE", 4};
const StreetType ZT_ROAD = {ST_CODE_ROAD, "ROAD", 4};
const StreetType ZT_SPUR = {ST_CODE_SPUR, "SPUR", 4};
const StreetType ZT_TARN = {ST_CODE_TARN, "TARN", 4};
const StreetType ZT_TURN = {ST_CODE_TURN, "TURN", 4};
const StreetType ZT_VALE = {ST_CODE_VALE, "VALE", 4};
const StreetType ZT_VIEW = {ST_CODE_VIEW, "VIEW", 4};
const StreetType ZT_WALK = {ST_CODE_WALK, "WALK", 4};
const StreetType ZT_WEST = {ST_CODE_WEST, "WEST", 4};
const StreetType ZT_WYND = {ST_CODE_WYND, "WYND", 4};
const StreetType ZT_YARD = {ST_CODE_YARD, "YARD", 4};
const StreetType ZT_ALLEY = {ST_CODE_ALLEY, "ALLEY", 5};
const StreetType ZT_AMBLE = {ST_CODE_AMBLE, "AMBLE", 5};
const StreetType ZT_BANAN = {ST_CODE_BANAN, "BANAN", 5};
const StreetType ZT_BEACH = {ST_CODE_BEACH, "BEACH", 5};
const StreetType ZT_BLVDE = {ST_CODE_BOULEVARD, "BLVDE", 5};
const StreetType ZT_BRACE = {ST_CODE_BRACE, "BRACE", 5};
const StreetType ZT_BREAK = {ST_CODE_BREAK, "BREAK", 5};
const StreetType ZT_BYWAY = {ST_CODE_BYWAY, "BYWAY", 5};
const StreetType ZT_CHASE = {ST_CODE_CHASE, "CHASE", 5};
const StreetType ZT_CLOSE = {ST_CODE_CLOSE, "CLOSE", 5};
const StreetType ZT_COPSE = {ST_CODE_COPSE, "COPSE", 5};
const StreetType ZT_CORSO = {ST_CODE_CORSO, "CORSO", 5};
const StreetType ZT_COURT = {ST_CODE_COURT, "COURT", 5};
const StreetType ZT_CREST = {ST_CODE_CREST, "CREST", 5};
const StreetType ZT_CRIEF = {ST_CODE_CRIEF, "CRIEF", 5};
const StreetType ZT_CROSS = {ST_CODE_CROSS, "CROSS", 5};
const StreetType ZT_DOWNS = {ST_CODE_DOWNS, "DOWNS", 5};
const StreetType ZT_DRIVE = {ST_CODE_DRIVE, "DRIVE", 5};
const StreetType ZT_ELBOW = {ST_CODE_ELBOW, "ELBOW", 5};
const StreetType ZT_FLATS = {ST_CODE_FLATS, "FLATS", 5};
const StreetType ZT_GLADE = {ST_CODE_GLADE, "GLADE", 5};
const StreetType ZT_GREEN = {ST_CODE_GREEN, "GREEN", 5};
const StreetType ZT_GROVE = {ST_CODE_GROVE, "GROVE", 5};
const StreetType ZT_GULLY = {ST_CODE_GULLY, "GULLY", 5};
const StreetType ZT_HAVEN = {ST_CODE_HAVEN, "HAVEN", 5};
const StreetType ZT_HEATH = {ST_CODE_HEATH, "HEATH", 5};
const StreetType ZT_HILLS = {ST_CODE_HILLS, "HILLS", 5};
const StreetType ZT_LYNNE = {ST_CODE_LYNNE, "LYNNE", 5};
const StreetType ZT_MANOR = {ST_CODE_MANOR, "MANOR", 5};
const StreetType ZT_NORTH = {ST_CODE_NORTH, "NORTH", 5};
const StreetType ZT_PALMS = {ST_CODE_PALMS, "PALMS", 5};
const StreetType ZT_PLACE = {ST_CODE_PLACE, "PLACE", 5};
const StreetType ZT_PLAZA = {ST_CODE_PLAZA, "PLAZA", 5};
const StreetType ZT_POINT = {ST_CODE_POINT, "POINT", 5};
const StreetType ZT_QUAYS = {ST_CODE_QUAYS, "QUAYS", 5};
const StreetType ZT_RANGE = {ST_CODE_RANGE, "RANGE", 5};
const StreetType ZT_REACH = {ST_CODE_REACH, "REACH", 5};
const StreetType ZT_RIDGE = {ST_CODE_RIDGE, "RIDGE", 5};
const StreetType ZT_RIVER = {ST_CODE_RIVER, "RIVER", 5};
const StreetType ZT_ROADS = {ST_CODE_ROADS, "ROADS", 5};
const StreetType ZT_ROUND = {ST_CODE_ROUND, "ROUND", 5};
const StreetType ZT_ROUTE = {ST_CODE_ROUTE, "ROUTE", 5};
const StreetType ZT_SLOPE = {ST_CODE_SLOPE, "SLOPE", 5};
const StreetType ZT_SOUTH = {ST_CODE_SOUTH, "SOUTH", 5};
const StreetType ZT_STEPS = {ST_CODE_STEPS, "STEPS", 5};
const StreetType ZT_STRIP = {ST_CODE_STRIP, "STRIP", 5};
const StreetType ZT_TRACK = {ST_CODE_TRACK, "TRACK", 5};
const StreetType ZT_TRAIL = {ST_CODE_TRAIL, "TRAIL", 5};
const StreetType ZT_TWIST = {ST_CODE_TWIST, "TWIST", 5};
const StreetType ZT_VIEWS = {ST_CODE_VIEWS, "VIEWS", 5};
const StreetType ZT_VILLA = {ST_CODE_VILLA, "VILLA", 5};
const StreetType ZT_VISTA = {ST_CODE_VISTA, "VISTA", 5};
const StreetType ZT_WHARF = {ST_CODE_WHARF, "WHARF", 5};
const StreetType ZT_WOODS = {ST_CODE_WOODS, "WOODS", 5};
const StreetType ZT_ACCESS = {ST_CODE_ACCESS, "ACCESS", 6};
const StreetType ZT_ARCADE = {ST_CODE_ARCADE, "ARCADE", 6};
const StreetType ZT_AVENUE = {ST_CODE_AVENUE, "AVENUE", 6};
const StreetType ZT_BRANCH = {ST_CODE_BRANCH, "BRANCH", 6};
const StreetType ZT_BRIDGE = {ST_CODE_BRIDGE, "BRIDGE", 6};
const StreetType ZT_BUSWAY = {ST_CODE_BUSWAY, "BUSWAY", 6};
const StreetType ZT_BYPASS = {ST_CODE_BYPASS, "BYPASS", 6};
const StreetType ZT_CENTRE = {ST_CODE_CENTRE, "CENTRE", 6};
const StreetType ZT_CIRCLE = {ST_CODE_CIRCLE, "CIRCLE", 6};
const StreetType ZT_CIRCUS = {ST_CODE_CIRCUS, "CIRCUS", 6};
const StreetType ZT_COMMON = {ST_CODE_COMMON, "COMMON", 6};
const StreetType ZT_CORNER = {ST_CODE_CORNER, "CORNER", 6};
const StreetType ZT_COURSE = {ST_CODE_COURSE, "COURSE", 6};
const StreetType ZT_DIVIDE = {ST_CODE_DIVIDE, "DIVIDE", 6};
const StreetType ZT_DOMAIN = {ST_CODE_DOMAIN, "DOMAIN", 6};
const StreetType ZT_ESTATE = {ST_CODE_ESTATE, "ESTATE", 6};
const StreetType ZT_FOLLOW = {ST_CODE_FOLLOW, "FOLLOW", 6};
const StreetType ZT_GARDEN = {ST_CODE_GARDEN, "GARDEN", 6};
const StreetType ZT_GRANGE = {ST_CODE_GRANGE, "GRANGE", 6};
const StreetType ZT_HOLLOW = {ST_CODE_HOLLOW, "HOLLOW", 6};
const StreetType ZT_ISLAND = {ST_CODE_ISLAND, "ISLAND", 6};
const StreetType ZT_LADDER = {ST_CODE_LADDER, "LADDER", 6};
const StreetType ZT_OUTLET = {ST_CODE_OUTLET, "OUTLET", 6};
const StreetType ZT_PARADE = {ST_CODE_PARADE, "PARADE", 6};
const StreetType ZT_POCKET = {ST_CODE_POCKET, "POCKET", 6};
const StreetType ZT_RAMBLE = {ST_CODE_RAMBLE, "RAMBLE", 6};
const StreetType ZT_RETURN = {ST_CODE_RETURN, "RETURN", 6};
const StreetType ZT_RISING = {ST_CODE_RISING, "RISING", 6};
const StreetType ZT_ROTARY = {ST_CODE_ROTARY, "ROTARY", 6};
const StreetType ZT_SQUARE = {ST_CODE_SQUARE, "SQUARE", 6};
const StreetType ZT_STRAIT = {ST_CODE_STRAIT, "STRAIT", 6};
const StreetType ZT_STREET = {ST_CODE_STREET, "STREET", 6};
const StreetType ZT_SUBWAY = {ST_CODE_SUBWAY, "SUBWAY", 6};
const StreetType ZT_TUNNEL = {ST_CODE_TUNNEL, "TUNNEL", 6};
const StreetType ZT_VALLEY = {ST_CODE_VALLEY, "VALLEY", 6};
const StreetType ZT_WATERS = {ST_CODE_WATERS, "WATERS", 6};
const StreetType ZT_CIRCUIT = {ST_CODE_CIRCUIT, "CIRCUIT", 7};
const StreetType ZT_CLUSTER = {ST_CODE_CLUSTER, "CLUSTER", 7};
const StreetType ZT_COMMONS = {ST_CODE_COMMONS, "COMMONS", 7};
const StreetType ZT_CONCORD = {ST_CODE_CONCORD, "CONCORD", 7};
const StreetType ZT_CUTTING = {ST_CODE_CUTTING, "CUTTING", 7};
const StreetType ZT_FAIRWAY = {ST_CODE_FAIRWAY, "FAIRWAY", 7};
const StreetType ZT_FREEWAY = {ST_CODE_FREEWAY, "FREEWAY", 7};
const StreetType ZT_GARDENS = {ST_CODE_GARDENS, "GARDENS", 7};
const StreetType ZT_GATEWAY = {ST_CODE_GATEWAY, "GATEWAY", 7};
const StreetType ZT_HARBOUR = {ST_CODE_HARBOUR, "HARBOUR", 7};
const StreetType ZT_HEIGHTS = {ST_CODE_HEIGHTS, "HEIGHTS", 7};
const StreetType ZT_HIGHWAY = {ST_CODE_HIGHWAY, "HIGHWAY", 7};
const StreetType ZT_LANDING = {ST_CODE_LANDING, "LANDING", 7};
const StreetType ZT_LANEWAY = {ST_CODE_LANEWAY, "LANEWAY", 7};
const StreetType ZT_LOOKOUT = {ST_CODE_LOOKOUT, "LOOKOUT", 7};
const StreetType ZT_MEANDER = {ST_CODE_MEANDER, "MEANDER", 7};
const StreetType ZT_OUTLOOK = {ST_CODE_OUTLOOK, "OUTLOOK", 7};
const StreetType ZT_PARKWAY = {ST_CODE_PARKWAY, "PARKWAY", 7};
const StreetType ZT_PASSAGE = {ST_CODE_PASSAGE, "PASSAGE", 7};
const StreetType ZT_PATHWAY = {ST_CODE_PATHWAY, "PATHWAY", 7};
const StreetType ZT_PURSUIT = {ST_CODE_PURSUIT, "PURSUIT", 7};
const StreetType ZT_RESERVE = {ST_CODE_RESERVE, "RESERVE", 7};
const StreetType ZT_RETREAT = {ST_CODE_RETREAT, "RETREAT", 7};
const StreetType ZT_ROADWAY = {ST_CODE_ROADWAY, "ROADWAY", 7};
const StreetType ZT_TERRACE = {ST_CODE_TERRACE, "TERRACE", 7};
const StreetType ZT_TRAMWAY = {ST_CODE_TRAMWAY, "TRAMWAY", 7};
const StreetType ZT_VILLAGE = {ST_CODE_VILLAGE, "VILLAGE", 7};
const StreetType ZT_WALKWAY = {ST_CODE_WALKWAY, "WALKWAY", 7};
const StreetType ZT_APPROACH = {ST_CODE_APPROACH, "APPROACH", 8};
const StreetType ZT_ARTERIAL = {ST_CODE_ARTERIAL, "ARTERIAL", 8};
const StreetType ZT_BROADWAY = {ST_CODE_BROADWAY, "BROADWAY", 8};
const StreetType ZT_CAUSEWAY = {ST_CODE_CAUSEWAY, "CAUSEWAY", 8};
const StreetType ZT_CRESCENT = {ST_CODE_CRESCENT, "CRESCENT", 8};
const StreetType ZT_CROSSING = {ST_CODE_CROSSING, "CROSSING", 8};
const StreetType ZT_DRIVEWAY = {ST_CODE_DRIVEWAY, "DRIVEWAY", 8};
const StreetType ZT_EASEMENT = {ST_CODE_EASEMENT, "EASEMENT", 8};
const StreetType ZT_ENTRANCE = {ST_CODE_ENTRANCE, "ENTRANCE", 8};
const StreetType ZT_FIRELINE = {ST_CODE_FIRELINE, "FIRELINE", 8};
const StreetType ZT_FRONTAGE = {ST_CODE_FRONTAGE, "FRONTAGE", 8};
const StreetType ZT_JUNCTION = {ST_CODE_JUNCTION, "JUNCTION", 8};
const StreetType ZT_MOTORWAY = {ST_CODE_MOTORWAY, "MOTORWAY", 8};
const StreetType ZT_PRECINCT = {ST_CODE_PRECINCT, "PRECINCT", 8};
const StreetType ZT_QUADRANT = {ST_CODE_QUADRANT, "QUADRANT", 8};
const StreetType ZT_STRAIGHT = {ST_CODE_STRAIGHT, "STRAIGHT", 8};
const StreetType ZT_TRAVERSE = {ST_CODE_TRAVERSE, "TRAVERSE", 8};
const StreetType ZT_TRUNKWAY = {ST_CODE_TRUNKWAY, "TRUNKWAY", 8};
const StreetType ZT_WATERWAY = {ST_CODE_WATERWAY, "WATERWAY", 8};
const StreetType ZT_BOARDWALK = {ST_CODE_BOARDWALK, "BOARDWALK", 9};
const StreetType ZT_BOULEVARD = {ST_CODE_BOULEVARD, "BOULEVARD", 9};
const StreetType ZT_CENTREWAY = {ST_CODE_CENTREWAY, "CENTREWAY", 9};
const StreetType ZT_CONCOURSE = {ST_CODE_CONCOURSE, "CONCOURSE", 9};
const StreetType ZT_COURTYARD = {ST_CODE_COURTYARD, "COURTYARD", 9};
const StreetType ZT_CRUISEWAY = {ST_CODE_CRUISEWAY, "CRUISEWAY", 9};
const StreetType ZT_DEVIATION = {ST_CODE_DEVIATION, "DEVIATION", 9};
const StreetType ZT_ESPLANADE = {ST_CODE_ESPLANADE, "ESPLANADE", 9};
const StreetType ZT_EXTENSION = {ST_CODE_EXTENSION, "EXTENSION", 9};
const StreetType ZT_FIREBREAK = {ST_CODE_FIREBREAK, "FIREBREAK", 9};
const StreetType ZT_FIRETRACK = {ST_CODE_FIRETRACK, "FIRETRACK", 9};
const StreetType ZT_FIRETRAIL = {ST_CODE_FIRETRAIL, "FIRETRAIL", 9};
const StreetType ZT_FORESHORE = {ST_CODE_FORESHORE, "FORESHORE", 9};
const StreetType ZT_FORMATION = {ST_CODE_FORMATION, "FORMATION", 9};
const StreetType ZT_PROMENADE = {ST_CODE_PROMENADE, "PROMENADE", 9};
const StreetType ZT_UNDERPASS = {ST_CODE_UNDERPASS, "UNDERPASS", 9};
const StreetType ZT_BOULEVARDE = {ST_CODE_BOULEVARDE, "BOULEVARDE", 10};
const StreetType ZT_CONNECTION = {ST_CODE_CONNECTION, "CONNECTION", 10};
const StreetType ZT_CULDESAC = {ST_CODE_CULDESAC, "CUL-DE-SAC", 10};
const StreetType ZT_EXPRESSWAY = {ST_CODE_EXPRESSWAY, "EXPRESSWAY", 10};
const StreetType ZT_SERVICEWAY = {ST_CODE_SERVICEWAY, "SERVICEWAY", 10};
const StreetType ZT_THROUGHWAY = {ST_CODE_THROUGHWAY, "THROUGHWAY", 10};
const StreetType ZT_DISTRIBUTOR = {ST_CODE_DISTRIBUTOR, "DISTRIBUTOR", 11};
const StreetType ZT_INTERCHANGE = {ST_CODE_INTERCHANGE, "INTERCHANGE", 11};
const StreetType * ZTZ[NZ] = {
  &ZT_AV, &ZT_BR, &ZT_CH, &ZT_CL, &ZT_CR, &ZT_CT, &ZT_DR, &ZT_GR, &ZT_LN, &ZT_PL, &ZT_RD,
  &ZT_SQ, &ZT_ST, &ZT_AVE, &ZT_BAY, &ZT_BVD, &ZT_CCT, &ZT_CIR, &ZT_CNR, &ZT_DIP, &ZT_DOM, &ZT_DPS,
  &ZT_DVE, &ZT_END, &ZT_ESP, &ZT_EST, &ZT_GAP, &ZT_GDN, &ZT_GLD, &ZT_GRA, &ZT_GRN, &ZT_GTE,
  &ZT_HUB, &ZT_HWY, &ZT_KEY, &ZT_PDE, &ZT_PNT, &ZT_ROW, &ZT_RTE, &ZT_RTT, &ZT_RUN, &ZT_RVR,
  &ZT_TCE, &ZT_TOP, &ZT_TOR, &ZT_TRK, &ZT_TRL, &ZT_WAY, &ZT_ACCS, &ZT_ACRE, &ZT_BANK,
  &ZT_BEND, &ZT_BLVD, &ZT_BOWL, &ZT_BRAE, &ZT_BROW, &ZT_BVDE, &ZT_COVE, &ZT_CRES, &ZT_CRST, &ZT_DALE,
  &ZT_DASH, &ZT_DELL, &ZT_DENE, &ZT_DOCK, &ZT_DOWN, &ZT_DRWY, &ZT_EAST, &ZT_EDGE, &ZT_FLAT, &ZT_FORD,
  &ZT_FORK, &ZT_GATE, &ZT_GDNS, &ZT_GLEN, &ZT_HIKE, &ZT_HILL, &ZT_KEYS, &ZT_LANE, &ZT_LINE, &ZT_LINK,
  &ZT_LOOP, &ZT_MALL, &ZT_MART, &ZT_MAZE, &ZT_MEAD, &ZT_MEWS, &ZT_MILE, &ZT_NOOK, &ZT_PARK, &ZT_PASS,
  &ZT_PATH, &ZT_PHWY, &ZT_PKWY, &ZT_PORT, &ZT_PROM, &ZT_QUAY, &ZT_RAMP, &ZT_RDGE, &ZT_RDWY, &ZT_REST, &ZT_RIDE,
  &ZT_RISE, &ZT_ROAD, &ZT_SPUR, &ZT_TARN, &ZT_TURN, &ZT_VALE, &ZT_VIEW, &ZT_WALK, &ZT_WEST, &ZT_WYND,
  &ZT_YARD, &ZT_ALLEY, &ZT_AMBLE, &ZT_BANAN, &ZT_BEACH, &ZT_BLVDE, &ZT_BRACE, &ZT_BREAK, &ZT_BYWAY, &ZT_CHASE,
  &ZT_CLOSE, &ZT_COPSE, &ZT_CORSO, &ZT_COURT, &ZT_CREST, &ZT_CRIEF, &ZT_CROSS, &ZT_DOWNS, &ZT_DRIVE, &ZT_ELBOW,
  &ZT_FLATS, &ZT_GLADE, &ZT_GREEN, &ZT_GROVE, &ZT_GULLY, &ZT_HAVEN, &ZT_HEATH, &ZT_HILLS, &ZT_LYNNE, &ZT_MANOR,
  &ZT_NORTH, &ZT_PALMS, &ZT_PLACE, &ZT_PLAZA, &ZT_POINT, &ZT_QUAYS, &ZT_RANGE, &ZT_REACH, &ZT_RIDGE, &ZT_RIVER,
  &ZT_ROADS, &ZT_ROUND, &ZT_ROUTE, &ZT_SLOPE, &ZT_SOUTH, &ZT_STEPS, &ZT_STRIP, &ZT_TRACK, &ZT_TRAIL, &ZT_TWIST,
  &ZT_VIEWS, &ZT_VILLA, &ZT_VISTA, &ZT_WHARF, &ZT_WOODS, &ZT_ACCESS, &ZT_ARCADE, &ZT_AVENUE, &ZT_BRANCH, &ZT_BRIDGE,
  &ZT_BUSWAY, &ZT_BYPASS, &ZT_CENTRE, &ZT_CIRCLE, &ZT_CIRCUS, &ZT_COMMON, &ZT_CORNER, &ZT_COURSE, &ZT_DIVIDE, &ZT_DOMAIN,
  &ZT_ESTATE, &ZT_FOLLOW, &ZT_GARDEN, &ZT_GRANGE, &ZT_HOLLOW, &ZT_ISLAND, &ZT_LADDER, &ZT_OUTLET, &ZT_PARADE, &ZT_POCKET,
  &ZT_RAMBLE, &ZT_RETURN, &ZT_RISING, &ZT_ROTARY, &ZT_SQUARE, &ZT_STRAIT, &ZT_STREET, &ZT_SUBWAY, &ZT_TUNNEL, &ZT_VALLEY,
  &ZT_WATERS, &ZT_CIRCUIT, &ZT_CLUSTER, &ZT_COMMONS, &ZT_CONCORD, &ZT_CUTTING, &ZT_FAIRWAY, &ZT_FREEWAY, &ZT_GARDENS, &ZT_GATEWAY,
  &ZT_HARBOUR, &ZT_HEIGHTS, &ZT_HIGHWAY, &ZT_LANDING, &ZT_LANEWAY, &ZT_LOOKOUT, &ZT_MEANDER, &ZT_OUTLOOK, &ZT_PARKWAY, &ZT_PASSAGE,
  &ZT_PATHWAY, &ZT_PURSUIT, &ZT_RESERVE, &ZT_RETREAT, &ZT_ROADWAY, &ZT_TERRACE, &ZT_TRAMWAY, &ZT_VILLAGE, &ZT_WALKWAY, &ZT_APPROACH,
  &ZT_ARTERIAL, &ZT_BROADWAY, &ZT_CAUSEWAY, &ZT_CRESCENT, &ZT_CROSSING, &ZT_DRIVEWAY, &ZT_EASEMENT, &ZT_ENTRANCE, &ZT_FIRELINE, &ZT_FRONTAGE,
  &ZT_JUNCTION, &ZT_MOTORWAY, &ZT_PRECINCT, &ZT_QUADRANT, &ZT_STRAIGHT, &ZT_TRAVERSE, &ZT_TRUNKWAY, &ZT_WATERWAY, &ZT_BOARDWALK, &ZT_BOULEVARD,
  &ZT_CENTREWAY, &ZT_CONCOURSE, &ZT_COURTYARD, &ZT_CRUISEWAY, &ZT_DEVIATION, &ZT_ESPLANADE, &ZT_EXTENSION, &ZT_FIREBREAK, &ZT_FIRETRACK, &ZT_FIRETRAIL,
  &ZT_FORESHORE, &ZT_FORMATION, &ZT_PROMENADE, &ZT_UNDERPASS, &ZT_BOULEVARDE, &ZT_CONNECTION, &ZT_CULDESAC, &ZT_EXPRESSWAY, &ZT_SERVICEWAY, &ZT_THROUGHWAY,
  &ZT_DISTRIBUTOR, &ZT_INTERCHANGE};

// zpos_by_len[i] gives the the first position in ZT
// of i length
#define NZ0POS 16
#define NZ0POR 15
const static int z0pos_by_len[NZ0POS] = {0, 0, 0, 13, 48, 113, 167, 203, 231, 250, 266, 272, 0};

// Originally
//   unique(.Permitted_street_type_ord_nchar_AZ())[, cat(strwrap(toString(order(ordering) - 1)), sep = "\n")]
// Now has to be manually done (some street types omitted)
const static int oZTC[NZ] =
  {10, 21, 103, 12, 198, 5, 125, 0, 13, 169, 9, 144, 8, 78, 6, 22, 130, 3, 122, 45, 159, 4,
   58, 235, 47, 46, 160, 33, 214, 42, 227, 35, 190, 7, 135, 48, 167, 16, 203, 97, 15, 52,
   56, 117, 251, 109, 102, 261, 119, 81, 86, 80, 73, 210, 17, 175, 93, 220, 209, 108, 39,
   225, 57, 24, 257, 11, 196, 90, 243, 92, 222, 164, 106, 51, 2, 121, 30, 134, 239, 213, 74,
   95, 264, 37, 98, 150, 259, 28, 133, 231, 91, 40, 173, 113, 168, 131, 118, 18, 178, 38,
   154, 192, 240, 236, 31, 72, 29, 185, 208, 217, 36, 146, 76, 59, 126, 216, 269, 79, 82,
   218, 219, 14, 128, 230, 260, 171, 89, 145, 88, 111, 107, 129, 104, 172, 176, 191, 250,
   253, 41, 151, 147, 224, 60, 187, 100, 267, 23, 96, 162, 34, 247, 266, 263, 189, 66, 237,
   215, 68, 245, 201, 202, 234, 116, 270, 174, 238, 221, 158, 105, 54, 256, 242, 157, 165,
   53, 179, 26, 136, 200, 207, 25, 182, 258, 262, 211, 137, 195, 177, 123, 272, 183, 241,
   44, 232, 50, 142, 152, 265, 55, 138, 188, 244, 148, 156, 248, 114, 115, 1, 170, 124, 180,
   64, 70, 71, 27, 184, 75, 186, 273, 143, 101, 153, 155, 197, 199, 43, 228, 233, 204, 62,
   20, 181, 69, 32, 140, 85, 87, 94, 149, 193, 246, 229, 110, 166, 49, 120, 252, 205, 206,
   254, 127, 255, 268, 61, 63, 19, 65, 67, 132, 212, 139, 77, 141, 83, 84, 223, 194, 99,
   226, 271, 161, 163, 249, 112};

SEXP C_get_oZTC(SEXP x) {
  SEXP ans = PROTECT(allocVector(INTSXP, NZ));
  for (int i = 0; i < NZ; ++i) {
    INTEGER(ans)[i] = oZTC[i];
  }
  UNPROTECT(1);
  return ans;
}

SEXP C_get_StreetType(SEXP x) {
  const int * xp = INTEGER(x);
  R_xlen_t N = xlength(x);
  SEXP ans = PROTECT(allocVector(STRSXP, N));
  for (R_xlen_t i = 0; i < N; ++i) {
    unsigned int xpi = xp[i];
    if (xpi < NZ) {
      SET_STRING_ELT(ans, i, mkCharCE(ZTZ[xpi]->x, CE_UTF8));
    }
  }
  UNPROTECT(1);
  return ans;
}

SEXP C_get_StreetCode(SEXP x) {
  const int * xp = INTEGER(x);
  R_xlen_t N = xlength(x);
  SEXP ans = PROTECT(allocVector(INTSXP, N));
  for (R_xlen_t i = 0; i < N; ++i) {
    unsigned int xpi = xp[i];
    if (xpi < NZ) {
      INTEGER(ans)[i] = ZTZ[xpi]->cd;
    }
  }
  UNPROTECT(1);
  return ans;
}


const static Saint St2044 = { 2044, 1, "PETERS", 6 };
const static Saint St2064 = { 2064, 1, "LEONARDS", 8 };
const static Saint St2065 = { 2065, 1, "LEONARDS", 8 };
const static Saint St2066 = { 2066, 1, "LEONARDS", 8 };
const static Saint St2072 = { 2072, 1, "IVES", 4 };
const static Saint St2073 = { 2073, 1, "IVES", 4 };
const static Saint St2075 = { 2075, 1, "IVES", 4 };
const static Saint St2176 = { 2176, 1, "JOHNS", 5 };
const static Saint St2177 = { 2177, 1, "JOHNS", 5 };
const static Saint St2204 = { 2204, 1, "PETERS", 6 };
const static Saint St2350 = { 2350, 1, "PATRICKS", 8 };
const static Saint St2354 = { 2354, 1, "LEONARDS", 8 };
const static Saint St2500 = { 2500, 1, "MOUNT THOMAS", 12 };
const static Saint St2540 = { 2540, 1, "GEORGES", 7 };
const static Saint St2560 = { 2560, 1, "HELENS", 6 };
const static Saint St2565 = { 2565, 1, "ANDREWS", 7 };
const static Saint St2760 = { 2760, 2, "MARYS", 5, "NORTH MARYS", 11 };
const static Saint St2770 = { 2770, 1, "MARYS", 5 };
const static Saint St3004 = { 3004, 1, "KILDA", 5 };
const static Saint St3006 = { 3006, 1, "KILDA", 5 };
const static Saint St3020 = { 3020, 1, "ALBANS", 6 };
const static Saint St3021 = { 3021, 1, "ALBANS", 6 };
const static Saint St3037 = { 3037, 1, "ALBANS", 6 };
const static Saint St3088 = { 3088, 1, "HELENA", 6 };
const static Saint St3184 = { 3184, 1, "KILDA", 5 };
const static Saint St3223 = { 3223, 1, "LEONARDS", 8 };
const static Saint St3384 = { 3384, 1, "ARNAUD", 6 };
const static Saint St3726 = { 3726, 1, "JAMES", 5 };
const static Saint St3727 = { 3727, 1, "JAMES", 5 };
const static Saint St3760 = { 3760, 1, "ANDREWS", 7 };
const static Saint St3941 = { 3941, 1, "ANDREWS", 7 };
const static Saint St3992 = { 3992, 1, "CLAIR", 5 };
const static Saint St3995 = { 3995, 1, "CLAIR", 5 };
const static Saint St4066 = { 4066, 1, "LUCIA", 5 };
const static Saint St4364 = { 4364, 1, "HELENS", 6 };
const static Saint St4405 = { 4405, 1, "RUTH", 4 };
const static Saint St4486 = { 4486, 1, "GEORGE", 6 };
const static Saint St4488 = { 4488, 1, "GEORGE", 6 };
const static Saint St4650 = { 4650, 1, "MARY", 4 };
const static Saint St4671 = { 4671, 1, "KILDA", 5 };
const static Saint St4706 = { 4706, 1, "LAWRENCE", 8 };
const static Saint St4798 = { 4798, 1, "HELENS", 6 };
const static Saint St4800 = { 4800, 1, "BEES", 4 };
const static Saint St4814 = { 4814, 1, "MOUNT JOHN", 10 };
const static Saint St4818 = { 4818, 1, "MT JOHN", 7 };
const static Saint St5011 = { 5011, 1, "CLAIR", 5 };
const static Saint St5014 = { 5014, 1, "CLAIR", 5 };
const static Saint St5042 = { 5042, 1, "MARYS", 5 };
const static Saint St5064 = { 5064, 1, "GEORGES", 7 };
const static Saint St5068 = { 5068, 1, "MORRIS", 6 };
const static Saint St5069 = { 5069, 1, "PETERS", 6 };
const static Saint St5081 = { 5081, 1, "PETERS", 6 };
const static Saint St5097 = { 5097, 1, "AGNES", 5 };
const static Saint St5110 = { 5110, 1, "KILDA", 5 };
const static Saint St5254 = { 5254, 1, "IVES", 4 };
const static Saint St5356 = { 5356, 1, "KITTS", 5 };
const static Saint St6010 = { 6010, 1, "JOHNS", 5 };
const static Saint St6021 = { 6021, 2, "ANTHONYS", 8, "LAWRENCE", 8 };
const static Saint St6052 = { 6052, 1, "PETERS", 6 };
const static Saint St6055 = { 6055, 1, "LEONARDS", 8 };
const static Saint St6101 = { 6101, 1, "JAMES", 5 };
const static Saint St6102 = { 6102, 1, "JAMES", 5 };
const static Saint St6122 = { 6122, 1, "THOMAS", 6 };
const static Saint St6152 = { 6152, 1, "LUCIA", 5 };
const static Saint St6172 = { 6172, 2, "MICHEL", 6, "CLAIR", 5 };
const static Saint St6285 = { 6285, 1, "MARGARETS", 9 };
const static Saint St6765 = { 6765, 1, "GEORGE", 6 };
const static Saint St7214 = { 7214, 1, "MARYS", 5 };
const static Saint St7216 = { 7216, 1, "HELENS", 6 };
const static Saint St7250 = { 7250, 1, "LEONARDS", 8 };

#define NSAINT 70
const Saint * Sts[NSAINT] = {&St2044, &St2064, &St2065, &St2066, &St2072, &St2073, &St2075, &St2176, &St2177, &St2204, &St2350,
                             &St2354, &St2500, &St2540, &St2560, &St2565, &St2760, &St2770, &St3004, &St3006, &St3020, &St3021, &St3037, &St3088, &St3184, &St3223,
                             &St3384, &St3726, &St3727, &St3760, &St3941, &St3992, &St3995, &St4066, &St4364, &St4405, &St4486, &St4488,
                             &St4650, &St4671, &St4706, &St4798, &St4800, &St4814, &St4818, &St5011, &St5014, &St5042, &St5064,
                             &St5068, &St5069, &St5081, &St5097, &St5110, &St5254, &St5356, &St6010, &St6021, &St6052, &St6055,
                             &St6101, &St6102, &St6122, &St6152, &St6172, &St6285, &St6765, &St7214, &St7216, &St7250};

static const char LETTERS[26] =
  {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
   'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

// isUPPER is faster than isupper
// 20 s to 7 s for 30 M strings
static bool isUPPER(char x) {
  unsigned char AAA = 'A';
  unsigned char uac = x;
  unsigned int y = (unsigned int)uac - AAA;
  return y < 26u;
}

static char toupper1(char x) {
  unsigned int xi = x - 'a';
  return (xi < 26) ? LETTERS[xi] : x;
}

// Hashes of common street types
#define TOP_ST_TYPES 32
const unsigned int hash_street_types[32] =
  {5862547 /* RD */,
   193444898 /* DPS */,
   2089353917 /* ROAD */,
   5862626,
   -938027068, 5862130, 213732634, 5861938, 193443895, -1758728215, 5862617, 231400990, 5862215, 2088983683, 5861971, 193445234, 208333225, 5862122, 213747795, 193461480, 226149834, 5862132, 2088892162, 1252464830, 193462922, 193462922, 193461487, 226150023, 193457987, 632738020};
const unsigned int hash_street_typecd[32] =
  {1, 1, 1, 2, 2, 3, 3, 4, 4, 4, 5, 5, 6, 6, 7, 7, 7, 8, 8, 9, 9, 10, 10, 10, 11, 11, 12, 12, 13, 13};






/*
 static const unsigned int SIXTEEN_PRIMER[16] =
 {53, 47, 43, 41, 37, 31, 29, 23, 19, 17, 13, 11, 7, 5, 3, 2};
 */

unsigned int djb2_hash(const char * str, int n, int i) {
  unsigned int hash = 5381;
  //
  // while (c = *str++)
  //   hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  // using xor instead of + performs slightly better on STREET_NAME
  while (++i < n) {
    unsigned char xi = str[i];
    hash = ((hash << 5) + hash) ^ xi;
  }
  return hash;
}

#define DJB2_HIGH_STREET 1467366250
#define DJB2_ST_GEORGES 685862476
#define DJB2_ST_VINCENT -899305073
#define DJB2_ESPLANADE 1588178048
#define DJB2_ESPLANADE_EAST 1418946723
#define DJB2_ESPLANADE_WEST 1419448821
#define DJB2_THE_STRAND -1123822046
#define DJB2_THE_RIGHI 1526029921
#define DJB2_THE_PARKS 1519372231
#define DJB2_THE_PARKWAY 1033948411


unsigned int djb2_hash_w1w2_only_letters(const char * str, WordData * wd, int w1, int w2) {
  unsigned int hash = 5381;
  for (int w = w1; w <= w2; ++w) {
    for (int j = wd->lhs[w]; j < wd->rhs[w]; ++j) {
      unsigned char xi = str[j];
      if (isupper(xi)) {
        hash = ((hash << 5) + hash) ^ xi;
      }
    }
    if (w < w2) {
      // include space between (so not after final, nor if only one word)
      hash = ((hash << 5) + hash) ^ ' ';
    }
  }
  return hash;
}



/*
 static const unsigned char letters[26] =
 {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
 */



//' @noRd
//' @description
//' Returns the positions of words, between [j0, n) among x,
//' among x.  Only the *last* WORD_DATUMS are considered.
//'
//' After the function is called:
//'
//' N_WORDS[0] returns the number of words in the substring
//' N_WORDS[1] = j + 1 for last j before exiting (i.e. n if N_WORDS[0] <= WORD_DATUMS or the position of the 16th word)
//' lhs[w] is the position of the first char of the w'th word
//' rhs[w] is the position of the first char _after_ the first word
//' nnos is the number of
//'
//' Assumptions:
//'   x consists of uppercase char and breakers only.
//'
//'
WordData word_data(const char * x, int n, int j0) {
  int no1st = 0;
  int lhs[WORD_DATUMS] = {0};
  int rhs[WORD_DATUMS] = {0};

  // ensure we're at the start of a word
  while (j0 < n && x[j0] == ' ') {
    ++j0;
  }
  int w = 0;

  for (int j = j0; j < n; ++j) {
    if (w >= WORD_DATUMS) {
      break;
    }

    unsigned char b = x[j];
    if (b == ' ' || b == ',') {
      unsigned char a = x[j - 1];
      if (a == ' ' || a == ',') {
        // not yet start of new word
        lhs[w] = j + 1;
        continue;
      }
      rhs[w] = j;
      ++w;
      lhs[w] = j + 1;
    }
  }
  rhs[w] = n;
  ++w;
  if (!isdigit(x[0])) {
    for (int j = n - 1; j >= 1; --j) {
      if (isdigit(x[j])) {
        no1st = j;
      }
    }
  }

  WordData wd;
  wd.n_words = w;
  for (int jj = 0; jj < WORD_DATUMS; ++jj) {
    wd.lhs[jj] = lhs[jj];
    wd.rhs[jj] = rhs[jj];
  }
  wd.x = x;
  wd.n = n;
  wd.no1st = no1st;
  return wd;
}

SEXP Ctest_WordData(SEXP xx, SEXP rr) {
  if (!isString(xx)) {
    return R_NilValue;
  }
  const int r = asInteger(rr); // r = 0 n_words, r = 1 lhs, r = 2 rhs
  int n = length(STRING_ELT(xx, 0));
  const char * x = CHAR(STRING_ELT(xx, 0));
  WordData wd = word_data(x, n, 0);

  switch(r) {
  case 0:
    return ScalarInteger(wd.n_words);
  case 1: {
      SEXP ans = PROTECT(allocVector(INTSXP, WORD_DATUMS));
      for (int i = 0; i < WORD_DATUMS; ++i) {
        INTEGER(ans)[i] = wd.lhs[i];
      }
      UNPROTECT(1);
      return ans;
    }
  case 2: {
    SEXP ans = PROTECT(allocVector(INTSXP, WORD_DATUMS));
    for (int i = 0; i < WORD_DATUMS; ++i) {
      INTEGER(ans)[i] = wd.rhs[i];
    }
    UNPROTECT(1);
    return ans;
  }

  }
  return R_NilValue;
}

// the words LEVEL and FLOOR are followed by numbers which do not
// form part of the standard address
int has_LEVEL(WordData wd) {
  int n_words = wd.n_words;
  const char * x = wd.x;
  const char LEVEL[5] = "LEVEL";
  const char FLOOR[5] = "FLOOR";
  for (int w = 0; w < n_words - 1; ++w) {
    int j = wd.lhs[w];
    if (x[j] != 'L' && x[j] != 'F') {
      continue;
    }
    if (isdigit(x[j + 1])) {
      return j + 1;
    }
    bool has_level = true;
    // L 251
    if (x[j + 1] == ' ' && isdigit(x[j + 2])) {
      return j + 2;
    }
    // LEVEL
    for (int k = 1; k < 5; ++k) {
      const char xjk = x[j + k];
      if (xjk != LEVEL[k] && xjk != FLOOR[k]) {
        has_level = false;
        break;
      }
    }
    if (has_level) {
      return next_numeral(j + 5, x, wd.n);
    }
  }
  return 0;
}



unsigned int xLEVEL(WordData wd) {
  int j = has_LEVEL(wd);
  if (j == 0) {
    return 0;
  }
  const char * x = wd.x;
  unsigned int o = x[j] - '0';
  while (isdigit(x[++j])) {
    o *= 10;
    o += x[j] - '0';
  }
  return o;

}



SEXP C_HashStreetName(SEXP x) {
  if (!isString(x)) {
    error("`x` was type '%s' but must be a character vector.", type2char(TYPEOF(x)));
  }
  R_xlen_t N = xlength(x);
  const SEXP * xp = STRING_PTR(x);
  // http://www.cse.yorku.ca/~oz/hash.html
  SEXP ans = PROTECT(allocVector(INTSXP, N));
  int * restrict ansp = INTEGER(ans);
  for (R_xlen_t i = 0; i < N; ++i) {
    if (xp[i] == NA_STRING) {
      ansp[i] = NA_INTEGER;
      continue;
    }

    int n = length(xp[i]);
    const char * xi = CHAR(xp[i]);
    ansp[i] = djb2_hash(xi, n, -1);
  }
  UNPROTECT(1);
  return ans;
}

bool char_is_LETTER(char x) {
  // assumes AZ contiguous and in order
  unsigned int xi = x - 'A';
  return xi <= 25u;
}

bool jchar_is_LETTER(const char * x, int j) {
  unsigned char xj = x[j];
  return char_is_LETTER(xj);
}

bool jchar_is_LETTER_or_hyphen(const char * x, int j) {
  unsigned char xj = x[j];
  return char_is_LETTER(xj) || xj == '-';
}

// Is y a substring within x, starting at position i?
// x The string within which y is suspected to exist
// i the character position of x from which y is expected
// n The (entire) length of x
// y The search term/the substring
// m The length of this substring
bool substring_within(const char * x, int i, int n, const char * y, int m) {
  // if the remaining length of x is insufficient to contain y, then no
  if (n - i < m) {
    return false;
  }
  for (int j = 0; j < m; ++j) {
    if (x[i + j] != y[j]) {
      return false;
    }
  }
  return true;
}

// For detecting things like 'THE ESPLANADE'
// Is the first 'word' the substring 'THE'
bool string_first_word_THE(const char * x, int n, int j) {
  while (++j < n - 5) {
    if (x[j] != ' ') {
      continue;
    }
    if (x[j + 1] == 'T' &&
        x[j + 2] == 'H' &&
        x[j + 3] == 'E' &&
        x[j + 4] == ' ') {
      return true;
    }
    // is a word
    if (jchar_is_LETTER(x, j) && !jchar_is_number(x, j - 1) &&
        jchar_is_LETTER(x, j + 1) && jchar_is_LETTER(x, j + 2)) {
      break;
    }
  }
  return false;
}



// 0 if no THE in word
int THE_xxx(WordData wd) {
  const char * x = wd.x;
  int n = wd.n;
  int n_words = wd.n_words;
  for (int w = 0; w < n_words - 1; ++w) {
    int lhs = wd.lhs[w];
    int rhs = wd.rhs[w];
    if (rhs - lhs != 3) {
      continue;
    }
    int j = lhs;
    if (x[j++] != 'T' || x[j++] != 'H' || x[j++] != 'E') {
      continue;
    }
    lhs = wd.lhs[w + 1];
    rhs = wd.rhs[w + 1];
    // int width_next = rhs - lhs;
    if (substring_within(x, lhs, n, "ESPLANADE", 9)) {
      return ST_CODE_ESPLANADE;
    }
    if (substring_within(x, lhs, n, "AVENUE", 6)) {
      return ST_CODE_AVENUE;
    }
    if (substring_within(x, lhs, n, "CRESCENT", 8)) {
      return ST_CODE_CRESCENT;
    }
    // DE before D to avoid having to distinguish
    if (substring_within(x, lhs, n, "BOULEVARDE", 10)) {
      return ST_CODE_BOULEVARDE;
    }
    if (substring_within(x, lhs, n, "BOULEVARD", 9)) {
      return ST_CODE_BOULEVARD;
    }
    if (substring_within(x, lhs, n, "PARADE", 6)) {
      return ST_CODE_PARADE;
    }
    if (substring_within(x, lhs, n, "PROMENADE", 9)) {
      return ST_CODE_PROMENADE;
    }
    if (substring_within(x, lhs, n, "TERRACE", 7)) {
      return ST_CODE_TERRACE;
    }
    if (substring_within(x, lhs, n, "GROVE", 5)) {
      return ST_CODE_GROVE;
    }
    if (substring_within(x, lhs, n, "STRAND", 6)) {
      return DJB2_THE_STRAND;
    }
    if (substring_within(x, lhs, n, "RIGHI", 5)) {
      return DJB2_THE_RIGHI;
    }
    if (substring_within(x, lhs, n, "PKWY", 4)) {
      return DJB2_THE_PARKWAY;
    }
    if (substring_within(x, lhs, n, "PARK", 4)) {
      if (substring_within(x, lhs, n, "PARKS", 5)) {
        return DJB2_THE_PARKS;
      }
      if (substring_within(x, lhs, n, "PARKW", 5)) {
        return DJB2_THE_PARKWAY;
      }
    }

  }
  return 0;
}




int ndigits_positive(int x) {
  if (x == 0) return 0;
  if (x < 10) return 1;
  if (x < 100) return 2;
  if (x < 1000) return 3;
  if (x < 10000) return 4;
  if (x < 100000) return 5;
  if (x < 1000000) return 6;
  if (x < 10000000) return 7;
  if (x < 100000000) return 8;
  if (x < 1000000000) return 9;
  return 10;
}

int which_char_is_space(const char * x, int n) {
  for (int i = 0; i < n; ++i) {
    if (x[i] == ' ') {
      return i + 1;
    }
  }
  return 0;
}


int digit_of_from(const char * x, int * j, unsigned char barrier, int len) {
  // x a string of length len from which the digit is sought from
  // position j, terminating whenever barrier occurs
  int o = 0;
  int k = j[0];
  while (k < len && x[k] != barrier) {
    unsigned int xk = x[k] - '0';
    if (xk > 9U) {
      break;
    }
    o *= 10;
    o += xk;
    ++k;
  }
  j[0] = k;
  return o;
}



// VIC->2
int ste_as_int(const char * x, int ii) {
  int i = ii;
  // we don't know
  while (!char_is_LETTER(x[i])) {
    ++i;
  }
  unsigned char xi = x[i];
  switch(xi) {
  case 'N':
    switch(x[i + 1]) {
    case 'T':
      return 7;
    case 'S':
      return (x[i + 2] == 'W') ? 1 : 0;
    }
    break;
  case 'V':
    return (x[i + 1] == 'I' && x[i + 2] == 'C') ? 2 : 0;
    break;
  case 'Q':
    return (x[i + 1] == 'L' && x[i + 2] == 'D') ? 3 : 0;
    break;
  case 'S':
    return (x[i + 1] == 'A') ? 4 : 0;
    break;
  case 'W':
    return (x[i + 1] == 'A') ? 5 : 0;
    break;
  case 'T':
    return (x[i + 1] == 'A' && x[i + 2] == 'S') ? 6 : 0;
    break;
  case 'A':
    return (x[i + 1] == 'C' && x[i + 2] == 'T') ? 8 : 0;
    break;
  case 'O':
    return (x[i + 1] == 'T') ? 9 : 0;
  }
  return 0;
}

int construct_postcode(const char * x, const int n4) {
  int o = 0;
  const int ten4s[4] = {1000, 100, 10, 1};
  for (int d = 0; d < 4; ++d) {
    char xj = x[n4 + d];
    o += ten4s[d] * (xj - '0');
  }
  return o;
}

int xpostcode_unsafe(const char * x, int n) {
  // unsafe = don't check that length is sufficient
  const int n4 = n - 4;
  return construct_postcode(x, n4);
}

bool find_four_digits(const char * x, int n, int jj[1]) {
  int i = jj[0];
  for (; i > 0; --i) {
    if (!isdigit(x[i]) || !isdigit(x[i + 3])) {
      continue;
    }
    if (!isdigit(x[i - 1]) &&
        // isdigit(x[i]) &&
        isdigit(x[i + 1]) &&
        isdigit(x[i + 2]) &&
        // isdigit(x[i + 3]) &&
        !isdigit(x[i + 4])) {
      jj[0] = i;
      return true;
    }
  }
  // i == 0
  if (isdigit(x[0]) && isdigit(x[1]) && isdigit(x[2]) && isdigit(x[3]) && !isdigit(x[4])) {
    jj[0] = 0;
    return true;
  }

  return false;
}

int xpostcode_unsafe2(const char * x, int n) {
  if (isdigit(x[n - 4]) && isdigit(x[n - 3]) && isdigit(x[n - 2]) && isdigit(x[n - 1])) {
    return xpostcode_unsafe(x, n);
  }
  int jj[1] = {n - 5};
  if (find_four_digits(x, n, jj)) {
    return construct_postcode(x, (const int)jj[0]);
  }
  return 0;
}


// Convert number_suffix to raw for compression
unsigned char number_suffix2raw(char x0, char x1) {
  if (x0 == ' ') {
    return 0; // i.e. no suffix
  }
  if (x1 == '\0' || x1 == ' ' || isdigit(x0)) {
    return x0;
  }
  switch(x0) {
  case 'A':
    switch(x1) {
    case 'A':
      return 'a';
    case 'B':
      return 'b';
    default:
      return 254;
    }
  case 'B':
    switch(x1) {
    case 'B':
      return 'c';
    case 'C':
      return 'd';
    default:
      return 253;
    }
  case 'C':
    return 'e';
  case 'G':
    switch(x1) {
    case 'R':
      return 'g';
    case 'X':
      return 'h';
    case 'Z':
      return 'i';
    default:
      return 252;
    }
  case 'M':
    return 'm';
  case 'N':
    return 'n';
  case 'T':
    switch(x1) {
    case 'T':
      return 't';
    case '3':
      return 'u';
    default:
      return 251;
    }
    break;
  }
  return 0;
}




SEXP C_uniquePostcodes(SEXP xx) {
  if (!isInteger(xx)) {
    error("`x` was type '%s' but must be integer.", type2char(TYPEOF(xx)));
  }
  R_xlen_t N = xlength(xx);
  const int * xp = INTEGER(xx);

  unsigned char postcode_tbl[SUP_POSTCODES] = {0};
  for (R_xlen_t i = 0; i < N; ++i) {
    unsigned int xpi = xp[i]; // NA becomes big, one branch only
    if (xpi >= SUP_POSTCODES) {
      continue;
    }
    postcode_tbl[xpi] = 1;
  }
  int n_out = 0; // number of unique postcodes
  // i = 1, we don't want to include zero
  for (int i = 1; i < SUP_POSTCODES; ++i) {
    n_out += postcode_tbl[i];
  }
  SEXP ans = PROTECT(allocVector(INTSXP, n_out));
  int * restrict ansp = INTEGER(ans);
  for (int i = 1, j = 0; i < SUP_POSTCODES; ++i) {
    if (postcode_tbl[i]) {
      ansp[j] = i;
      ++j;
    }
  }
  UNPROTECT(1);
  return ans;
}




SEXP CToUpperBasic(SEXP x) {
  R_xlen_t N = xlength(x);
  if (TYPEOF(x) != STRSXP) {
    error("TYPEOF(x) != STRSXP");
  }
  SEXP ans = PROTECT(allocVector(STRSXP, N));
  for (R_xlen_t i = 0; i < N; ++i) {
    SEXP xi = STRING_ELT(x, i);
    if (xi == NA_STRING) {
      SET_STRING_ELT(ans, i, xi);
      continue;
    }
    int nchari = length(xi);
    const char * xpi = CHAR(xi);
    char anspi[nchari + 1];
    for (int j = 0; j < nchari; ++j) {
      unsigned char xpij = xpi[j];
      anspi[j] = toupper1(xpij);
    }
    anspi[nchari] = '\0';
    SET_STRING_ELT(ans, i, mkCharCE(anspi, CE_UTF8));
  }
  UNPROTECT(1);
  return ans;
}







SEXP CExtractPostcode(SEXP x) {
  R_xlen_t N = xlength(x);
  const SEXP * xpp = STRING_PTR(x);
  SEXP ans = PROTECT(allocVector(INTSXP, N));
  int * restrict ansp = INTEGER(ans);
// pragma omp parallel for
  for (R_xlen_t i = 0; i < N; ++i) {
    int n = length(xpp[i]);
    if (n < 4) {
      ansp[i] = NA_INTEGER;
      continue;
    }
    const char * xp = CHAR(xpp[i]);
    ansp[i] = xpostcode_unsafe2(xp, n);
  }
  UNPROTECT(1);
  return ans;
}

SEXP MAX_uN_STCDs(SEXP x) {
  return ScalarInteger(MAX_NUMBER_STREET_TYPES_ANY_POSTCODE);
}
SEXP C_N_STREET_TYPES(SEXP x) {
  return ScalarInteger(N_STREET_TYPES);
}

void do_flat_number(const char * x, int n, int ans[2], int jj) {
  ans[0] = 0; // position after last digit of flat number
  ans[1] = 0; // the flat number itself
  if (n < 4) {
    return;
  }

  // position j so that it points to the first digit of the flat number
  int j = jj;
  switch(x[j]) {
  case 'A':
    j += substring_within(x, j, n, "APT", 3) ? 3 : (substring_within(x, j, n, "APARTMENT", 9) ? 9 : 0);
    break;
  case 'U':
    j += (x[1] == 'N' && x[2] == 'I' && x[3] == 'T' && x[4] != 'S') ? 4 : 1;
    // e.g. UNIT G

    break;
  case 'F':
    if (x[1] == 'L' && x[2] == 'A' && x[3] == 'T' && x[4] != 'S') {
      j += 4;
    } else {
      ans[0] = 1;
      return;
    }

    break;
  case 'G':
    j += 1;
    break;
  default: {
      // have to seek ahead
      int has_slash = 0;
      if (n < 6) {
        return; // don't bother
      }
      for (int i = 0; i < 6; ++i) {
        if (x[i] == '/') {
          has_slash = i;
          break;
        }
      }
      if (has_slash) {
        j = has_slash;
        int o = 0;
        int ten = 1;
        for (int j = has_slash; j >= 0; --j) {
          if (isdigit(x[j])) {
            o += ten * (x[j] - '0');
            ten *= 10; // no need to check overflow because only looking at first 5 chars
          }
        }
        ans[0] = has_slash;
        ans[1] = o;
        return;
      }
      while (j < n && !isdigit(x[j])) {
        ++j;
      }
      ans[0] = j;
      ans[1] = 0;
      return;
    }
  }
  while (j < n && !isdigit(x[j])) {
    ++j;
  }
  int o = 0;
  while (j < n && isdigit(x[j])) {
    int digit = x[j] - '0';
    o *= 10;
    o += digit;
    ++j;
  }
  ans[0] = j;
  ans[1] = o;
}


SEXP C_NumberFirstLast(SEXP xx) {
  if (!isString(xx)) {
    error("`address` was type '%s' but must be a character vector.", type2char(TYPEOF(xx)));
  }
  R_xlen_t N = xlength(xx);
  const SEXP * xp = STRING_PTR(xx);
  int np = 0;
  SEXP n_unit = PROTECT(allocVector(INTSXP, N)); ++np;
  SEXP nfirst = PROTECT(allocVector(INTSXP, N)); ++np;
  SEXP nfinal = PROTECT(allocVector(INTSXP, N)); ++np;
  SEXP posfin = PROTECT(allocVector(INTSXP, N)); ++np;
  SEXP suffix = PROTECT(allocVector(RAWSXP, N)); ++np;

  int * restrict nun = INTEGER(n_unit);
  int * restrict nfp = INTEGER(nfirst);
  int * restrict nfl = INTEGER(nfinal);
  int * restrict pfp = INTEGER(posfin);
  unsigned char * restrict sfp = RAW(suffix);

  for (R_xlen_t i = 0; i < N; ++i) {
    nun[i] = NA_INTEGER;
    nfp[i] = NA_INTEGER;
    nfl[i] = NA_INTEGER;
    pfp[i] = 0;
    if (xp[i] == NA_STRING) {
      continue;
    }
    int n = length(xp[i]);
    if (n <= 4) {
      continue; // confusion with postcode, can't be anything meaningful (even 1 A ST)
    }
    const char * x = CHAR(xp[i]);
    int j_start = 0;
    const char x0 = x[0];
    if (!isdigit(x[0])) {
      const char x1 = x[1];
      const char x2 = x[2];
      if (x0 == 'C' && x1 == '/' && (x2 == '-' || x2 == 'O')) {
        // careof
        j_start = 3;
      }
    }
    int flat_number2i[2] = {0};
    do_flat_number(x, n, flat_number2i, j_start);
    nun[i] = flat_number2i[1];

    int o1 = 0;
    int o2 = 0;

    // two numbers are separated by a dash
    bool two_numbers = false;
    // move after flat number:
    j_start = flat_number2i[1] > 0 ? (flat_number2i[0] + 1) : j_start;
    int j = j_start;
    for (; j < n - 4; ++j) {
      if (jchar_is_number(x, j)) {
        int digit = x[j] - '0';
        if (two_numbers) {
          o2 *= 10;
          o2 += digit;
        } else {
          o1 *= 10;
          o1 += digit;
        }
        continue;
      }
      if (x[j] == '-') {
        two_numbers = true;
        continue;
      }
      break; // don't continue on first encounter with non-number/dash
    }

    unsigned char this_suffix = number_suffix2raw(x[j], x[j + 1]);
    j += (this_suffix == 0 ? 0 : (islower(this_suffix) ? 2 : 1));
    sfp[i] = this_suffix;

    nfp[i] = o1;
    nfl[i] = o2;
    pfp[i] = j;

  }
  SEXP ans = PROTECT(allocVector(VECSXP, np)); ++np;
  SET_VECTOR_ELT(ans, 0, n_unit);
  SET_VECTOR_ELT(ans, 1, nfirst);
  SET_VECTOR_ELT(ans, 2, nfinal);
  SET_VECTOR_ELT(ans, 3, posfin);
  SET_VECTOR_ELT(ans, 4, suffix);

  UNPROTECT(np);
  return ans;
}

bool jchar_is_number(const char * x, int j) {
  return isdigit(x[j]);
}

unsigned int pos_preceding_word(const char * x, int i) {
  for (int j = i - 3; j > 0; --j) {
    // want the position of the preceding word (following a number)
    // because we're really after the street name
    if (x[j] == ' ' && isdigit(x[j - 1]) && jchar_is_LETTER(x, j + 1)) {
      return j + 1;
    }
  }
  return 0;
}


int has_comma(const char * x, int n) {
  for (int j = 0; j < n; ++j) {
    if (x[j] == ',') {
      return j + 1;
    }
  }
  return 0;
}

void comma_locations(int commas[8], const char * x, int n) {
  unsigned int j = 0;
  for (int i = 0; i < n; ++i) {
    commas[j & 7] = i;
    j += (*(x + i) == ',');
  }
  // ensure remaining are filled with negatives
  for (; j < 8; ++j) {
    commas[j] = -1;
  }
}

void detect_char(unsigned char ans[256], const char * x, int n) {
  for (int j = 0; j < n; ++j) {
    unsigned int xj = (unsigned char)x[j];
    ans[xj] = 1;
  }
}

SEXP C_anyComma(SEXP x, SEXP oo) {
  if (!isString(x)) {
    warning("Not a string, so returning 0.");
    return ScalarInteger(0);
  }
  const int o = asInteger(oo);
  R_xlen_t N = xlength(x);
  const SEXP * xp = STRING_PTR(x);
  if (o == 1) {
    for (R_xlen_t i = 0; i < N; ++i) {
      // if (has_comma(CHAR(xp[i]), length(xp[i]))) {
      //   return i >= INT_MAX ? ScalarReal(i + 1) : ScalarInteger(i + 1);
      // }
      int xx[8] = {0};
      comma_locations(xx, CHAR(xp[i]), length(xp[i]));
      if (xx[0] >= 0) {
        return i >= INT_MAX ? ScalarReal(i + 1) : ScalarInteger(i + 1);
      }
    }
  } else if (o == 0) {
    unsigned char all_chars[256] = {0};
    for (R_xlen_t i = 0; i < N; ++i) {
      detect_char(all_chars, CHAR(xp[i]), length(xp[i]));
      if (all_chars[44]) {
        return ScalarInteger(i + 1);
      }
    }

  }
  return ScalarInteger(0);
}









SEXP CFindSentence(SEXP xx, SEXP W1, SEXP W2) {
  int np = 0;
  R_xlen_t N = xlength(xx);
  if (TYPEOF(xx) != STRSXP || TYPEOF(W1) != STRSXP || TYPEOF(W2) != STRSXP) {
    error("Arguments must be character.");
  }
  if (xlength(W1) != xlength(W2)) {
    error("length(W1) != length(W2)");
  }
  int WN = length(W1);
  if (((uint64_t)N) * ((uint64_t)WN) > 1e9) {
    error("Quadratic algorithm would take too long.");
  }


  SEXP W1_widths = PROTECT(allocVector(INTSXP, WN)); np++;
  SEXP W2_widths = PROTECT(allocVector(INTSXP, WN)); np++;
  int * restrict w1_width = INTEGER(W1_widths);
  int * restrict w2_width = INTEGER(W2_widths);
  for (int j = 0; j < WN; ++j) {
    w1_width[j] = length(STRING_ELT(W1, j));
    w2_width[j] = length(STRING_ELT(W2, j));
  }

  SEXP ans = PROTECT(allocVector(INTSXP, N)); np++;
  int * restrict ansp = INTEGER(ans);
  // only check 8 words


  for (R_xlen_t i = 0; i < N; ++i) {
    int word_widths[8] = {0};
    int word_pos[9] = {0};
    ansp[i] = NA_INTEGER;
    int n = length(STRING_ELT(xx, i));
    const char * x = CHAR(STRING_ELT(xx, i));
    int word_width_i = 0;
    int d = 0;
    for (int c = 0; c < n; ++c) {
      bool is_space = x[c] == ' ';
      if (is_space) {
        d = c + 1;
      }
      // the word grows with each space,
      // unless the spaces are consecutive
      word_widths[word_width_i] += (!is_space);
      word_pos[word_width_i + 1] = d;
      word_width_i += is_space && c > 0 && x[c - 1] != ' ';
      word_width_i &= 7; // ensure only use last 8 trailing widths.
    }

    // Now go through the widths
    for (int j = 0; j < WN; ++j) {
      int w1j = w1_width[j];
      int w2j = w2_width[j];
      bool matches = false;
      for (int wwi = 1; wwi < 8; ++wwi) {
        if (matches) {
          break;
        }
        if (word_widths[wwi - 1] == w1j &&
            word_widths[wwi] == w2j) {
          const char * w1 = CHAR(STRING_ELT(W1, j));
          const char * w2 = CHAR(STRING_ELT(W2, j));
          const int c1_start = word_pos[wwi - 1];
          const int c2_start = word_pos[wwi];
          if ((w2j - 1 + c2_start) >= n) {
            // unexpected: word 2 would trails of target
            continue;
          }
          // provisionally
          matches = true;
          for (int c = 0; c < w1j; ++c) {
            if (w1[c] != x[c + c1_start]) {
              matches = false;
              break;
            }
          }
          for (int c = 0; c < w2j; ++c) {
            if (w2[c] != x[c + c2_start]) {
              matches = false;
              break;
            }
          }
        }
      }
      if (matches) {
        ansp[i] = j + 1;
        break;
      }
    }


  }
  UNPROTECT(np);
  return ans;
}

bool noLC(SEXP x) {
  R_xlen_t N = xlength(x);
  bool char_array[256] = {0};
  const SEXP * xp = STRING_PTR(x);
#pragma omp parallel for reduction(|| : char_array[:256])
  for (R_xlen_t i = 0; i < N; ++i) {
    if (xp[i] == NA_STRING) {
      continue;
    }
    int n = length(xp[i]);
    const char * xi = CHAR(xp[i]);
    for (int j = 0; j < n; ++j) {
      unsigned char xj = xi[j];
      unsigned int xju = xj;
      char_array[xju] = true;
    }
  }

  for (unsigned int c = 0; c < 255; ++c) {
    unsigned char uc = (unsigned char)c;
    if (islower(uc) && char_array[c]) {
      return false;
    }
  }
  return true;
}

SEXP C_noLC(SEXP x) {
  if (TYPEOF(x) != STRSXP) {
    error("Internal error(EnsureUC): TYPEOF(x) != STRSXP.");
  }
  return ScalarLogical(noLC(x));
}



SEXP Cmatch_word(SEXP xx, SEXP yy) {
  int np = 0;
  if (TYPEOF(xx) != STRSXP || TYPEOF(yy) != STRSXP) {
    error("Wrong types"); // # nocov
  }
  R_xlen_t N = xlength(xx);
  R_xlen_t M = xlength(yy);
  SEXP nchar_yy = PROTECT(allocVector(INTSXP, M)); np++;
  int * restrict nchar_yyp = INTEGER(nchar_yy);
  for (R_xlen_t j = 0; j < M; ++j) {
    nchar_yyp[j] = length(STRING_ELT(yy, j));
  }
  SEXP ans = PROTECT(allocVector(INTSXP, N)); np++;
  int * restrict ansp = INTEGER(ans);

  // order to look for words
  const int W_ORD[16] = { 3,  4,  5,  2,  6, 0, 1, 7,
                          11, 12, 13, 10, 14, 8, 9, 15};

  for (R_xlen_t i = 0; i < N; ++i) {
    ansp[i] = NA_INTEGER;
    int n = length(STRING_ELT(xx, i));
    const char * x = CHAR(STRING_ELT(xx, i));
    int word_sizes[16] = {0};
    int word_positions[16] = {0};
    int j = 0;
    unsigned int wsk = 0, wpk = 0; // index of word_sizes
    word_sizes[0] = 1;
    while (++j < n && x[j] != ' ') {
      word_sizes[0] += 1;
    }
    j = n - 1;
    wsk = 1, wpk = 1;
    while (--j >= 1) {
      bool isnt_space = x[j] != ' ';
      bool follows_space = x[j - 1] == ' ';
      bool eow = !isnt_space && !follows_space;
      bool sow = isnt_space && follows_space;
      word_sizes[wsk] += isnt_space;
      word_positions[wpk] = j;
      wsk += eow;
      wsk &= 15u;
      wpk += sow;
      wpk &= 15u;
    }
    j = 0;
    bool matched = false;
    for (int w_ = 0; w_ < 16; ++w_) {
      int w = W_ORD[w_];

      if (matched) {
        break;
      }
      int len_word_i = word_sizes[w];

      for (R_xlen_t k = 0; k < M; ++k) {
        if (matched) {
          break;
        }
        int len_k = nchar_yyp[k];
        if (len_k != len_word_i) {
          continue;
        }
        matched = true; // provisional
        const char * y = CHAR(STRING_ELT(yy, k));
        const int wpw = word_positions[w];
        for (int c = 0; c < len_k; ++c) {
          unsigned char xc = x[c + wpw];
          unsigned char yc = y[c];
          if (xc != yc) {
            matched = false;
            break;
          }
        }
        if (matched) {
          ansp[i] = k + 1;
        }
      }
    }

  }
  UNPROTECT(np);
  return ans;
}

SEXP Cmatch_StreetType_Line1(SEXP xx, SEXP mm, SEXP jPos) {
  // This differs from Cmatch without Line1 in that we can assume the last
  // word in the string is the street type

  // m = return type
  // yy = Permitted street type
  // xx = address
  int np = 0;
  if (TYPEOF(xx) != STRSXP) {
    error("Wrong types"); // # nocov
  }

  R_xlen_t N = xlength(xx);
  const int m = asInteger(mm) ;
  const unsigned int m1 = m > 0 ? 256 : 0;
  const unsigned int m2 = m == 2 ? 65536 : 0;
  const bool hasNumberPosition = isInteger(jPos) && xlength(jPos) == N;
  const int * last_number_p = hasNumberPosition ? INTEGER(jPos) : INTEGER(mm);
  const SEXP * xp = STRING_PTR(xx);

  SEXP ans = PROTECT(allocVector(INTSXP, N)); np++;
  int * restrict ansp = INTEGER(ans);
  for (R_xlen_t i = 0; i < N; ++i) {
    ansp[i] = NA_INTEGER;
    if (xp[i] == NA_STRING) {
      continue;
    }
    int n = length(xp[i]);
    const char * x = CHAR(xp[i]);
    if (substring_within(x, n - 3, n, " RD", 3)) {
      ansp[i] = ST_CODE_ROAD + m1 * (n - 3) + m2 * pos_preceding_word(x, n - 3); continue;
    }
    if (substring_within(x, n - 4, n, " DPS", 4)) {
      ansp[i] = ST_CODE_ROAD + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 5, n, " ROAD", 5)) {
      ansp[i] = ST_CODE_ROAD + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 3, n, " ST", 3)) {
      ansp[i] = ST_CODE_STREET + m1 * (n - 3) + m2 * pos_preceding_word(x, n - 3); continue;
    }
    if (substring_within(x, n - 7, n, " STREET", 7)) {
      ansp[i] = ST_CODE_STREET;
      ansp[i] += m1 * (n - 7);
      if (hasNumberPosition) {
        ansp[i] += m2 * last_number_p[i];
        continue;
      }
      ansp[i] += m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 3, n, " CT", 3)) {
      ansp[i] = ST_CODE_COURT + m1 * (n - 3) + m2 * pos_preceding_word(x, n - 3); continue;
    }
    if (substring_within(x, n - 6, n, " COURT", 6)) {
      ansp[i] = ST_CODE_COURT + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 3, n, " AV", 3)) {
      ansp[i] = ST_CODE_AVENUE + m1 * (n - 3) + m2 * pos_preceding_word(x, n - 3); continue;
    }
    if (substring_within(x, n - 4, n, " AVE", 4)) {
      ansp[i] = ST_CODE_AVENUE + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 7, n, " AVENUE", 7)) {
      ansp[i] = ST_CODE_AVENUE + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 3, n, " PL", 3)) {
      ansp[i] = ST_CODE_PLACE + m1 * (n - 3) + m2 * pos_preceding_word(x, n - 3); continue;
    }
    if (substring_within(x, n - 6, n, " PLACE", 6)) {
      ansp[i] = ST_CODE_PLACE + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 3, n, " LN", 3)) {
      ansp[i] = ST_CODE_LANE + m1 * (n - 3) + m2 * pos_preceding_word(x, n - 3); continue;
    }
    if (substring_within(x, n - 5, n, " LANE", 5)) {
      ansp[i] = ST_CODE_LANE + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 3, n, " DR", 3)) {
      ansp[i] = ST_CODE_DRIVE + m1 * (n - 3) + m2 * pos_preceding_word(x, n - 3); continue;
    }
    if (substring_within(x, n - 4, n, " DVE", 4)) {
      ansp[i] = ST_CODE_DRIVE + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 6, n, " DRIVE", 6)) {
      ansp[i] = ST_CODE_DRIVE + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 3, n, " CL", 3)) {
      ansp[i] = ST_CODE_CLOSE + m1 * (n - 3) + m2 * pos_preceding_word(x, n - 3); continue;
    }
    if (substring_within(x, n - 6, n, " CLOSE", 6)) {
      ansp[i] = ST_CODE_CLOSE + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 4, n, " TRK", 4)) {
      ansp[i] = ST_CODE_TRACK + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 6, n, " TRACK", 6)) {
      ansp[i] = ST_CODE_TRACK + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 3, n, " CR", 3)) {
      ansp[i] = ST_CODE_CRESCENT + m1 * (n - 3) + m2 * pos_preceding_word(x, n - 3); continue;
    }
    if (substring_within(x, n - 5, n, " CRES", 5)) {
      ansp[i] = ST_CODE_CRESCENT + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 9, n, " CRESCENT", 9)) {
      ansp[i] = ST_CODE_CRESCENT + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 4, n, " WAY", 4)) {
      ansp[i] = ST_CODE_WAY + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 4, n, " WAY", 4)) {
      ansp[i] = ST_CODE_WAY + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 4, n, " TRL", 4)) {
      ansp[i] = ST_CODE_TRAIL + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 6, n, " TRAIL", 6)) {
      ansp[i] = ST_CODE_TRAIL + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 4, n, " HWY", 4)) {
      ansp[i] = ST_CODE_HIGHWAY + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 8, n, " HIGHWAY", 8)) {
      ansp[i] = ST_CODE_HIGHWAY + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 4, n, " TCE", 4)) {
      ansp[i] = ST_CODE_TERRACE + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 8, n, " TERRACE", 8)) {
      ansp[i] = ST_CODE_TERRACE + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 4, n, " PDE", 4)) {
      ansp[i] = ST_CODE_PARADE + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 7, n, " PARADE", 7)) {
      ansp[i] = ST_CODE_PARADE + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 3, n, " GR", 3)) {
      ansp[i] = ST_CODE_GROVE + m1 * (n - 3) + m2 * pos_preceding_word(x, n - 3); continue;
    }
    if (substring_within(x, n - 6, n, " GROVE", 6)) {
      ansp[i] = ST_CODE_GROVE + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 5, n, " ACCS", 5)) {
      ansp[i] = ST_CODE_ACCESS + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 7, n, " ACCESS", 7)) {
      ansp[i] = ST_CODE_ACCESS + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 4, n, " CCT", 4)) {
      ansp[i] = ST_CODE_CIRCUIT + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 8, n, " CIRCUIT", 8)) {
      ansp[i] = ST_CODE_CIRCUIT + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 5, n, " RAMP", 5)) {
      ansp[i] = ST_CODE_RAMP + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 4, n, " BVD", 4)) {
      ansp[i] = ST_CODE_BOULEVARD + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 5, n, " BLVD", 5)) {
      ansp[i] = ST_CODE_BOULEVARD + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 5, n, " BVDE", 5)) {
      ansp[i] = ST_CODE_BOULEVARD + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 6, n, " BLVDE", 6)) {
      ansp[i] = ST_CODE_BOULEVARD + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 10, n, " BOULEVARD", 10)) {
      ansp[i] = ST_CODE_BOULEVARD + m1 * (n - 10) + m2 * pos_preceding_word(x, n - 10); continue;
    }
    if (substring_within(x, n - 5, n, " WALK", 5)) {
      ansp[i] = ST_CODE_WALK + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 5, n, " RISE", 5)) {
      ansp[i] = ST_CODE_RISE + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 10, n, " FIRETRAIL", 10)) {
      ansp[i] = ST_CODE_FIRETRAIL + m1 * (n - 10) + m2 * pos_preceding_word(x, n - 10); continue;
    }
    if (substring_within(x, n - 6, n, " BREAK", 6)) {
      ansp[i] = ST_CODE_BREAK + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 5, n, " LOOP", 5)) {
      ansp[i] = ST_CODE_LOOP + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 5, n, " MEWS", 5)) {
      ansp[i] = ST_CODE_MEWS + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 5, n, " LINK", 5)) {
      ansp[i] = ST_CODE_LINK + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 5, n, " GDNS", 5)) {
      ansp[i] = ST_CODE_GARDENS + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 8, n, " GARDENS", 8)) {
      ansp[i] = ST_CODE_GARDENS + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 4, n, " CIR", 4)) {
      ansp[i] = ST_CODE_CIRCLE + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 7, n, " CIRCLE", 7)) {
      ansp[i] = ST_CODE_CIRCLE + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 5, n, " PKWY", 5)) {
      ansp[i] = ST_CODE_PARKWAY + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 8, n, " PARKWAY", 8)) {
      ansp[i] = ST_CODE_PARKWAY + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 8, n, " FREEWAY", 8)) {
      ansp[i] = ST_CODE_FREEWAY + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 5, n, " VIEW", 5)) {
      ansp[i] = ST_CODE_VIEW + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 4, n, " RTT", 4)) {
      ansp[i] = ST_CODE_RETREAT + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 8, n, " RETREAT", 8)) {
      ansp[i] = ST_CODE_RETREAT + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 5, n, " COVE", 5)) {
      ansp[i] = ST_CODE_COVE + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 4, n, " ESP", 4)) {
      ansp[i] = ST_CODE_ESPLANADE + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 10, n, " ESPLANADE", 10)) {
      ansp[i] = ST_CODE_ESPLANADE + m1 * (n - 10) + m2 * pos_preceding_word(x, n - 10); continue;
    }
    if (substring_within(x, n - 3, n, " SQ", 3)) {
      ansp[i] = ST_CODE_SQUARE + m1 * (n - 3) + m2 * pos_preceding_word(x, n - 3); continue;
    }
    if (substring_within(x, n - 7, n, " SQUARE", 7)) {
      ansp[i] = ST_CODE_SQUARE + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 5, n, " PASS", 5)) {
      ansp[i] = ST_CODE_PASS + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 9, n, " MOTORWAY", 9)) {
      ansp[i] = ST_CODE_MOTORWAY + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 5, n, " PHWY", 5)) {
      ansp[i] = ST_CODE_PATHWAY + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 8, n, " PATHWAY", 8)) {
      ansp[i] = ST_CODE_PATHWAY + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 6, n, " VISTA", 6)) {
      ansp[i] = ST_CODE_VISTA + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 5, n, " TURN", 5)) {
      ansp[i] = ST_CODE_TURN + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 5, n, " BEND", 5)) {
      ansp[i] = ST_CODE_BEND + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 3, n, " CH", 3)) {
      ansp[i] = ST_CODE_CHASE + m1 * (n - 3) + m2 * pos_preceding_word(x, n - 3); continue;
    }
    if (substring_within(x, n - 6, n, " CHASE", 6)) {
      ansp[i] = ST_CODE_CHASE + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 4, n, " GRN", 4)) {
      ansp[i] = ST_CODE_GREEN + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 6, n, " GREEN", 6)) {
      ansp[i] = ST_CODE_GREEN + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 9, n, " ENTRANCE", 9)) {
      ansp[i] = ST_CODE_ENTRANCE + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 8, n, " HEIGHTS", 8)) {
      ansp[i] = ST_CODE_HEIGHTS + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 5, n, " GLEN", 5)) {
      ansp[i] = ST_CODE_GLEN + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 10, n, " PROMENADE", 10)) {
      ansp[i] = ST_CODE_PROMENADE + m1 * (n - 10) + m2 * pos_preceding_word(x, n - 10); continue;
    }
    if (substring_within(x, n - 4, n, " ROW", 4)) {
      ansp[i] = ST_CODE_ROW + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 5, n, " RDGE", 5)) {
      ansp[i] = ST_CODE_RIDGE + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 6, n, " RIDGE", 6)) {
      ansp[i] = ST_CODE_RIDGE + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 10, n, " FIREBREAK", 10)) {
      ansp[i] = ST_CODE_FIREBREAK + m1 * (n - 10) + m2 * pos_preceding_word(x, n - 10); continue;
    }
    if (substring_within(x, n - 4, n, " GLD", 4)) {
      ansp[i] = ST_CODE_GLADE + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 6, n, " GLADE", 6)) {
      ansp[i] = ST_CODE_GLADE + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 9, n, " APPROACH", 9)) {
      ansp[i] = ST_CODE_APPROACH + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 5, n, " PATH", 5)) {
      ansp[i] = ST_CODE_PATH + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 4, n, " RUN", 4)) {
      ansp[i] = ST_CODE_RUN + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 7, n, " BYPASS", 7)) {
      ansp[i] = ST_CODE_BYPASS + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 6, n, " ALLEY", 6)) {
      ansp[i] = ST_CODE_ALLEY + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 7, n, " ARCADE", 7)) {
      ansp[i] = ST_CODE_ARCADE + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 6, n, " ELBOW", 6)) {
      ansp[i] = ST_CODE_ELBOW + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 6, n, " BRACE", 6)) {
      ansp[i] = ST_CODE_BRACE + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 4, n, " CNR", 4)) {
      ansp[i] = ST_CODE_CORNER + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 7, n, " CORNER", 7)) {
      ansp[i] = ST_CODE_CORNER + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 4, n, " RTE", 4)) {
      ansp[i] = ST_CODE_ROUTE + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 6, n, " ROUTE", 6)) {
      ansp[i] = ST_CODE_ROUTE + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 7, n, " RAMBLE", 7)) {
      ansp[i] = ST_CODE_RAMBLE + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 9, n, " FIRELINE", 9)) {
      ansp[i] = ST_CODE_FIRELINE + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 9, n, " CROSSING", 9)) {
      ansp[i] = ST_CODE_CROSSING + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 4, n, " GTE", 4)) {
      ansp[i] = ST_CODE_GATE + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 5, n, " GATE", 5)) {
      ansp[i] = ST_CODE_GATE + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 4, n, " GRA", 4)) {
      ansp[i] = ST_CODE_GRANGE + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 7, n, " GRANGE", 7)) {
      ansp[i] = ST_CODE_GRANGE + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 8, n, " FAIRWAY", 8)) {
      ansp[i] = ST_CODE_FAIRWAY + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 8, n, " LOOKOUT", 8)) {
      ansp[i] = ST_CODE_LOOKOUT + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 4, n, " PNT", 4)) {
      ansp[i] = ST_CODE_POINT + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 6, n, " POINT", 6)) {
      ansp[i] = ST_CODE_POINT + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 5, n, " HILL", 5)) {
      ansp[i] = ST_CODE_HILL + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 5, n, " CRST", 5)) {
      ansp[i] = ST_CODE_CREST + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 6, n, " CREST", 6)) {
      ansp[i] = ST_CODE_CREST + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 8, n, " LANEWAY", 8)) {
      ansp[i] = ST_CODE_LANEWAY + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 11, n, " EXPRESSWAY", 11)) {
      ansp[i] = ST_CODE_EXPRESSWAY + m1 * (n - 11) + m2 * pos_preceding_word(x, n - 11); continue;
    }
    if (substring_within(x, n - 5, n, " LINE", 5)) {
      ansp[i] = ST_CODE_LINE + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 5, n, " MALL", 5)) {
      ansp[i] = ST_CODE_MALL + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 8, n, " MEANDER", 8)) {
      ansp[i] = ST_CODE_MEANDER + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 8, n, " OUTLOOK", 8)) {
      ansp[i] = ST_CODE_OUTLOOK + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 4, n, " BAY", 4)) {
      ansp[i] = ST_CODE_BAY + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 6, n, " CROSS", 6)) {
      ansp[i] = ST_CODE_CROSS + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 8, n, " WALKWAY", 8)) {
      ansp[i] = ST_CODE_WALKWAY + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 10, n, " FIRETRACK", 10)) {
      ansp[i] = ST_CODE_FIRETRACK + m1 * (n - 10) + m2 * pos_preceding_word(x, n - 10); continue;
    }
    if (substring_within(x, n - 7, n, " BRIDGE", 7)) {
      ansp[i] = ST_CODE_BRIDGE + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 5, n, " PARK", 5)) {
      ansp[i] = ST_CODE_PARK + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 6, n, " PLAZA", 6)) {
      ansp[i] = ST_CODE_PLAZA + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 5, n, " NOOK", 5)) {
      ansp[i] = ST_CODE_NOOK + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 5, n, " WYND", 5)) {
      ansp[i] = ST_CODE_WYND + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 5, n, " VALE", 5)) {
      ansp[i] = ST_CODE_VALE + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 6, n, " DOWNS", 6)) {
      ansp[i] = ST_CODE_DOWNS + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 5, n, " SPUR", 5)) {
      ansp[i] = ST_CODE_SPUR + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 7, n, " BUSWAY", 7)) {
      ansp[i] = ST_CODE_BUSWAY + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 7, n, " CIRCUS", 7)) {
      ansp[i] = ST_CODE_CIRCUS + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 7, n, " POCKET", 7)) {
      ansp[i] = ST_CODE_POCKET + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 10, n, " BOARDWALK", 10)) {
      ansp[i] = ST_CODE_BOARDWALK + m1 * (n - 10) + m2 * pos_preceding_word(x, n - 10); continue;
    }
    if (substring_within(x, n - 10, n, " CONCOURSE", 10)) {
      ansp[i] = ST_CODE_CONCOURSE + m1 * (n - 10) + m2 * pos_preceding_word(x, n - 10); continue;
    }
    if (substring_within(x, n - 4, n, " RVR", 4)) {
      ansp[i] = ST_CODE_RIVER + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 6, n, " RIVER", 6)) {
      ansp[i] = ST_CODE_RIVER + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 6, n, " QUAYS", 6)) {
      ansp[i] = ST_CODE_QUAYS + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 8, n, " RESERVE", 8)) {
      ansp[i] = ST_CODE_RESERVE + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 5, n, " DALE", 5)) {
      ansp[i] = ST_CODE_DALE + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 7, n, " ISLAND", 7)) {
      ansp[i] = ST_CODE_ISLAND + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 5, n, " REST", 5)) {
      ansp[i] = ST_CODE_REST + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 11, n, " CONNECTION", 11)) {
      ansp[i] = ST_CODE_CONNECTION + m1 * (n - 11) + m2 * pos_preceding_word(x, n - 11); continue;
    }
    if (substring_within(x, n - 4, n, " END", 4)) {
      ansp[i] = ST_CODE_END + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 5, n, " QUAY", 5)) {
      ansp[i] = ST_CODE_QUAY + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 6, n, " VIEWS", 6)) {
      ansp[i] = ST_CODE_VIEWS + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 4, n, " KEY", 4)) {
      ansp[i] = ST_CODE_KEY + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 9, n, " TRAVERSE", 9)) {
      ansp[i] = ST_CODE_TRAVERSE + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 11, n, " BOULEVARDE", 11)) {
      ansp[i] = ST_CODE_BOULEVARDE + m1 * (n - 11) + m2 * pos_preceding_word(x, n - 11); continue;
    }
    if (substring_within(x, n - 10, n, " FORMATION", 10)) {
      ansp[i] = ST_CODE_FORMATION + m1 * (n - 10) + m2 * pos_preceding_word(x, n - 10); continue;
    }
    if (substring_within(x, n - 7, n, " OUTLET", 7)) {
      ansp[i] = ST_CODE_OUTLET + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 5, n, " DRWY", 5)) {
      ansp[i] = ST_CODE_DRIVEWAY + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 9, n, " DRIVEWAY", 9)) {
      ansp[i] = ST_CODE_DRIVEWAY + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 8, n, " LANDING", 8)) {
      ansp[i] = ST_CODE_LANDING + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 5, n, " EDGE", 5)) {
      ansp[i] = ST_CODE_EDGE + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 9, n, " QUADRANT", 9)) {
      ansp[i] = ST_CODE_QUADRANT + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 7, n, " VALLEY", 7)) {
      ansp[i] = ST_CODE_VALLEY + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 7, n, " WATERS", 7)) {
      ansp[i] = ST_CODE_WATERS + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 9, n, " CAUSEWAY", 9)) {
      ansp[i] = ST_CODE_CAUSEWAY + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 6, n, " BEACH", 6)) {
      ansp[i] = ST_CODE_BEACH + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 11, n, " SERVICEWAY", 11)) {
      ansp[i] = ST_CODE_SERVICEWAY + m1 * (n - 11) + m2 * pos_preceding_word(x, n - 11); continue;
    }
    if (substring_within(x, n - 7, n, " CENTRE", 7)) {
      ansp[i] = ST_CODE_CENTRE + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 9, n, " EASEMENT", 9)) {
      ansp[i] = ST_CODE_EASEMENT + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 8, n, " PASSAGE", 8)) {
      ansp[i] = ST_CODE_PASSAGE + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 6, n, " STRIP", 6)) {
      ansp[i] = ST_CODE_STRIP + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 5, n, " TARN", 5)) {
      ansp[i] = ST_CODE_TARN + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 5, n, " BRAE", 5)) {
      ansp[i] = ST_CODE_BRAE + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 10, n, " DEVIATION", 10)) {
      ansp[i] = ST_CODE_DEVIATION + m1 * (n - 10) + m2 * pos_preceding_word(x, n - 10); continue;
    }
    if (substring_within(x, n - 9, n, " JUNCTION", 9)) {
      ansp[i] = ST_CODE_JUNCTION + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 6, n, " STEPS", 6)) {
      ansp[i] = ST_CODE_STEPS + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 6, n, " WHARF", 6)) {
      ansp[i] = ST_CODE_WHARF + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 5, n, " BOWL", 5)) {
      ansp[i] = ST_CODE_BOWL + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 7, n, " COURSE", 7)) {
      ansp[i] = ST_CODE_COURSE + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 4, n, " GAP", 4)) {
      ansp[i] = ST_CODE_GAP + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 6, n, " GULLY", 6)) {
      ansp[i] = ST_CODE_GULLY + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 7, n, " TUNNEL", 7)) {
      ansp[i] = ST_CODE_TUNNEL + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 8, n, " CUTTING", 8)) {
      ansp[i] = ST_CODE_CUTTING + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 4, n, " EST", 4)) {
      ansp[i] = ST_CODE_ESTATE + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 7, n, " ESTATE", 7)) {
      ansp[i] = ST_CODE_ESTATE + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 10, n, " EXTENSION", 10)) {
      ansp[i] = ST_CODE_EXTENSION + m1 * (n - 10) + m2 * pos_preceding_word(x, n - 10); continue;
    }
    if (substring_within(x, n - 10, n, " FORESHORE", 10)) {
      ansp[i] = ST_CODE_FORESHORE + m1 * (n - 10) + m2 * pos_preceding_word(x, n - 10); continue;
    }
    if (substring_within(x, n - 8, n, " GATEWAY", 8)) {
      ansp[i] = ST_CODE_GATEWAY + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 6, n, " HAVEN", 6)) {
      ansp[i] = ST_CODE_HAVEN + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 7, n, " ROTARY", 7)) {
      ansp[i] = ST_CODE_ROTARY + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 7, n, " COMMON", 7)) {
      ansp[i] = ST_CODE_COMMON + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 6, n, " COPSE", 6)) {
      ansp[i] = ST_CODE_COPSE + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 12, n, " DISTRIBUTOR", 12)) {
      ansp[i] = ST_CODE_DISTRIBUTOR + m1 * (n - 12) + m2 * pos_preceding_word(x, n - 12); continue;
    }
    if (substring_within(x, n - 7, n, " FOLLOW", 7)) {
      ansp[i] = ST_CODE_FOLLOW + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 9, n, " FRONTAGE", 9)) {
      ansp[i] = ST_CODE_FRONTAGE + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 4, n, " TOR", 4)) {
      ansp[i] = ST_CODE_TOR + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 9, n, " ARTERIAL", 9)) {
      ansp[i] = ST_CODE_ARTERIAL + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 5, n, " BANK", 5)) {
      ansp[i] = ST_CODE_BANK + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 6, n, " NORTH", 6)) {
      ansp[i] = ST_CODE_NORTH + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 6, n, " ROADS", 6)) {
      ansp[i] = ST_CODE_ROADS + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 10, n, " UNDERPASS", 10)) {
      ansp[i] = ST_CODE_UNDERPASS + m1 * (n - 10) + m2 * pos_preceding_word(x, n - 10); continue;
    }
    if (substring_within(x, n - 5, n, " BROW", 5)) {
      ansp[i] = ST_CODE_BROW + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 6, n, " HEATH", 6)) {
      ansp[i] = ST_CODE_HEATH + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 7, n, " LADDER", 7)) {
      ansp[i] = ST_CODE_LADDER + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 9, n, " PRECINCT", 9)) {
      ansp[i] = ST_CODE_PRECINCT + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 6, n, " RANGE", 6)) {
      ansp[i] = ST_CODE_RANGE + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 6, n, " SOUTH", 6)) {
      ansp[i] = ST_CODE_SOUTH + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 9, n, " TRUNKWAY", 9)) {
      ansp[i] = ST_CODE_TRUNKWAY + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 6, n, " AMBLE", 6)) {
      ansp[i] = ST_CODE_AMBLE + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 6, n, " BANAN", 6)) {
      ansp[i] = ST_CODE_BANAN + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 7, n, " BRANCH", 7)) {
      ansp[i] = ST_CODE_BRANCH + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 6, n, " CORSO", 6)) {
      ansp[i] = ST_CODE_CORSO + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 7, n, " DIVIDE", 7)) {
      ansp[i] = ST_CODE_DIVIDE + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 5, n, " DOCK", 5)) {
      ansp[i] = ST_CODE_DOCK + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 5, n, " FORD", 5)) {
      ansp[i] = ST_CODE_FORD + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 5, n, " FORK", 5)) {
      ansp[i] = ST_CODE_FORK + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 4, n, " GDN", 4)) {
      ansp[i] = ST_CODE_GARDEN + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 7, n, " GARDEN", 7)) {
      ansp[i] = ST_CODE_GARDEN + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 5, n, " HIKE", 5)) {
      ansp[i] = ST_CODE_HIKE + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 7, n, " HOLLOW", 7)) {
      ansp[i] = ST_CODE_HOLLOW + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 12, n, " INTERCHANGE", 12)) {
      ansp[i] = ST_CODE_INTERCHANGE + m1 * (n - 12) + m2 * pos_preceding_word(x, n - 12); continue;
    }
    if (substring_within(x, n - 6, n, " PALMS", 6)) {
      ansp[i] = ST_CODE_PALMS + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 5, n, " RIDE", 5)) {
      ansp[i] = ST_CODE_RIDE + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 6, n, " ROUND", 6)) {
      ansp[i] = ST_CODE_ROUND + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 6, n, " SLOPE", 6)) {
      ansp[i] = ST_CODE_SLOPE + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 7, n, " STRAIT", 7)) {
      ansp[i] = ST_CODE_STRAIT + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 7, n, " SUBWAY", 7)) {
      ansp[i] = ST_CODE_SUBWAY + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 4, n, " TOP", 4)) {
      ansp[i] = ST_CODE_TOP + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 8, n, " TRAMWAY", 8)) {
      ansp[i] = ST_CODE_TRAMWAY + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 9, n, " BROADWAY", 9)) {
      ansp[i] = ST_CODE_BROADWAY + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 8, n, " CLUSTER", 8)) {
      ansp[i] = ST_CODE_CLUSTER + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 5, n, " DELL", 5)) {
      ansp[i] = ST_CODE_DELL + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 7, n, " DOMAIN", 7)) {
      ansp[i] = ST_CODE_DOMAIN + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 5, n, " FLAT", 5)) {
      ansp[i] = ST_CODE_FLAT + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 4, n, " HUB", 4)) {
      ansp[i] = ST_CODE_HUB + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 6, n, " LYNNE", 6)) {
      ansp[i] = ST_CODE_LYNNE + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 5, n, " MEAD", 5)) {
      ansp[i] = ST_CODE_MEAD + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 5, n, " MILE", 5)) {
      ansp[i] = ST_CODE_MILE + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 5, n, " PORT", 5)) {
      ansp[i] = ST_CODE_PORT + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 6, n, " REACH", 6)) {
      ansp[i] = ST_CODE_REACH + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 7, n, " RETURN", 7)) {
      ansp[i] = ST_CODE_RETURN + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 9, n, " STRAIGHT", 9)) {
      ansp[i] = ST_CODE_STRAIGHT + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 8, n, " VILLAGE", 8)) {
      ansp[i] = ST_CODE_VILLAGE + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 5, n, " WEST", 5)) {
      ansp[i] = ST_CODE_WEST + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 6, n, " WOODS", 6)) {
      ansp[i] = ST_CODE_WOODS + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 5, n, " ACRE", 5)) {
      ansp[i] = ST_CODE_ACRE + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 6, n, " BYWAY", 6)) {
      ansp[i] = ST_CODE_BYWAY + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 10, n, " CENTREWAY", 10)) {
      ansp[i] = ST_CODE_CENTREWAY + m1 * (n - 10) + m2 * pos_preceding_word(x, n - 10); continue;
    }
    if (substring_within(x, n - 8, n, " COMMONS", 8)) {
      ansp[i] = ST_CODE_COMMONS + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 8, n, " CONCORD", 8)) {
      ansp[i] = ST_CODE_CONCORD + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 10, n, " COURTYARD", 10)) {
      ansp[i] = ST_CODE_COURTYARD + m1 * (n - 10) + m2 * pos_preceding_word(x, n - 10); continue;
    }
    if (substring_within(x, n - 6, n, " CRIEF", 6)) {
      ansp[i] = ST_CODE_CRIEF + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 10, n, " CRUISEWAY", 10)) {
      ansp[i] = ST_CODE_CRUISEWAY + m1 * (n - 10) + m2 * pos_preceding_word(x, n - 10); continue;
    }
    if (substring_within(x, n - 11, n, " CUL-DE-SAC", 11)) {
      ansp[i] = ST_CODE_CULDESAC + m1 * (n - 11) + m2 * pos_preceding_word(x, n - 11); continue;
    }
    if (substring_within(x, n - 5, n, " DASH", 5)) {
      ansp[i] = ST_CODE_DASH + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 5, n, " DENE", 5)) {
      ansp[i] = ST_CODE_DENE + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 4, n, " DIP", 4)) {
      ansp[i] = ST_CODE_DIP + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 5, n, " DOWN", 5)) {
      ansp[i] = ST_CODE_DOWN + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 5, n, " EAST", 5)) {
      ansp[i] = ST_CODE_EAST + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 6, n, " FLATS", 6)) {
      ansp[i] = ST_CODE_FLATS + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 8, n, " HARBOUR", 8)) {
      ansp[i] = ST_CODE_HARBOUR + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 6, n, " HILLS", 6)) {
      ansp[i] = ST_CODE_HILLS + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 5, n, " KEYS", 5)) {
      ansp[i] = ST_CODE_KEYS + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 6, n, " MANOR", 6)) {
      ansp[i] = ST_CODE_MANOR + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 5, n, " MART", 5)) {
      ansp[i] = ST_CODE_MART + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 5, n, " MAZE", 5)) {
      ansp[i] = ST_CODE_MAZE + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 8, n, " PURSUIT", 8)) {
      ansp[i] = ST_CODE_PURSUIT + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 7, n, " RISING", 7)) {
      ansp[i] = ST_CODE_RISING + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 5, n, " RDWY", 5)) {
      ansp[i] = ST_CODE_ROADWAY + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 8, n, " ROADWAY", 8)) {
      ansp[i] = ST_CODE_ROADWAY + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 11, n, " THROUGHWAY", 11)) {
      ansp[i] = ST_CODE_THROUGHWAY + m1 * (n - 11) + m2 * pos_preceding_word(x, n - 11); continue;
    }
    if (substring_within(x, n - 6, n, " TWIST", 6)) {
      ansp[i] = ST_CODE_TWIST + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 6, n, " VILLA", 6)) {
      ansp[i] = ST_CODE_VILLA + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 9, n, " WATERWAY", 9)) {
      ansp[i] = ST_CODE_WATERWAY + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 5, n, " YARD", 5)) {
      ansp[i] = ST_CODE_YARD + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }

  }
  UNPROTECT(np);
  return ans;
}


SEXP Cmatch_StreetType(SEXP xx, SEXP yy, SEXP mm) {
  // m = return type
  // yy = Permitted street type
  // xx = address
  int np = 0;
  if (TYPEOF(xx) != STRSXP || TYPEOF(yy) != STRSXP) {
    error("Wrong types"); // # nocov
  }
  R_xlen_t N = xlength(xx);
  const int m = asInteger(mm) ;
  const unsigned int m1 = m > 0 ? 256 : 0;
  const unsigned int m2 = m == 2 ? 65536 : 0;


  R_xlen_t M = xlength(yy);
  if (M < 16) {
    error("M < 16 unexpected (should be at least 200)");
  }
  SEXP nchar_yy = PROTECT(allocVector(INTSXP, M)); np++;
  int * restrict nchar_yyp = INTEGER(nchar_yy);
  for (R_xlen_t j = 0; j < M; ++j) {
    nchar_yyp[j] = length(STRING_ELT(yy, j));
  }
  SEXP ans = PROTECT(allocVector(INTSXP, N)); np++;
  int * restrict ansp = INTEGER(ans);


  // order to look for words
  const int W_ORD[16] = { 3,  4,  5,  2,  6,  0, 1, 7,
                          11, 12, 13, 10, 14, 8, 9, 15};

  // last chars of top 13
  // const char suffix12[6] = {'D', 'E', 'K', 'L', 'T', 'Y'};

  // Difference with match_word is that we check the first 10 entries
  // First iteration

// #pragma omp parallel for
  for (R_xlen_t i = 0; i < N; ++i) {
    ansp[i] = NA_INTEGER;
  }


// #pragma omp parallel for
  for (R_xlen_t i = 0; i < N; ++i) {
    int n = length(STRING_ELT(xx, i));
    // almost impossible (but required because we multiply the character position
    // by 256 to encode the position of the match
    //
    if (__builtin_expect(n >= 32768, 0)) {
      continue;
    }
    const char * x = CHAR(STRING_ELT(xx, i));

    // First check for 'THE ESPLANADE' etc
    if (string_first_word_THE(x, n, 0)) {
      ansp[i] = ST_CODE_ESPLANADE;
      continue;
    }





    int j = n - 4; // postcode
    while (j >= 4 && x[j] == ' ') {
      --j; // maybe 800
    }
    // Contemplate at least the street name and numbers
    while (--j > 10) {
      // not end of word
      if (x[j + 1] != ' ' && x[j + 1] != ',') {
        continue;
      }
      char xj = x[j];
      if (xj == 'D' &&
          x[j - 1] == 'A' &&
          x[j - 2] == 'O' &&
          x[j - 3] == 'R' &&
          x[j - 4] == ' ') {
        ansp[i] = ST_CODE_ROAD + m1 * (j - 4) + m2 * pos_preceding_word(x, j - 4);
        break;
      }
      if (xj == 'T') {
        if (x[j - 4] == 'C' &&
            x[j - 3] == 'O' &&
            x[j - 2] == 'U' &&
            x[j - 1] == 'R' &&
            x[j - 5] == ' ') {
          ansp[i] = ST_CODE_COURT + m1 * (j - 5) + m2 * pos_preceding_word(x, j - 5);
          break;
        }
        if (x[j - 6] == ' ' &&
            x[j - 5] == 'S' &&
            x[j - 4] == 'T' &&
            x[j - 3] == 'R' &&
            x[j - 2] == 'E' &&
            x[j - 1] == 'E') {
          ansp[i] = ST_CODE_STREET + m1 * (j - 6) + m2 * pos_preceding_word(x, j - 6);
          break;
        }
        if (x[j - 8] == ' ' &&
            x[j - 7] == 'C' &&
            x[j - 6] == 'R' &&
            x[j - 5] == 'E' &&
            x[j - 4] == 'S' &&
            x[j - 3] == 'C' &&
            x[j - 2] == 'E' &&
            x[j - 1] == 'N') {
          ansp[i] = ST_CODE_CRESCENT + m1 * (j - 8) + m2 * pos_preceding_word(x, j - 8);
          break;
        }
        --j;
        continue;
      }
      if (xj == 'E') {
        if (x[j - 1] == 'N' &&
            x[j - 2] == 'A' &&
            x[j - 3] == 'L' &&
            x[j - 4] == ' ') {
          ansp[i] = ST_CODE_LANE + m1 * (j - 4) + m2 * pos_preceding_word(x, j - 4);
          break;
        }
        if (x[j - 5] == ' ') {
          if (x[j - 4] == 'P' &&
              x[j - 3] == 'L' &&
              x[j - 2] == 'A' &&
              x[j - 1] == 'C') {
            ansp[i] = ST_CODE_PLACE + 256 * (j - 5) + m2 * pos_preceding_word(x, j - 5);
            break;
          }
          if (x[j - 4] == 'D' &&
              x[j - 3] == 'R' &&
              x[j - 2] == 'I' &&
              x[j - 1] == 'V') {
            ansp[i] = ST_CODE_DRIVE + 256 * (j - 5) + m2 * pos_preceding_word(x, j - 5);
            break;
          }
          if (x[j - 4] == 'C' &&
              x[j - 3] == 'L' &&
              x[j - 2] == 'O' &&
              x[j - 1] == 'S') {
            ansp[i] = ST_CODE_CLOSE + 256 * (j - 5) + m2 * pos_preceding_word(x, j - 5);
            break;
          }
        }
        if (x[j - 6] == ' ' &&
            x[j - 5] == 'A' &&
            x[j - 4] == 'V' &&
            x[j - 3] == 'E' &&
            x[j - 2] == 'N' &&
            x[j - 1] == 'U') {
          ansp[i] = ST_CODE_AVENUE + 256 * (j - 6) + m2 * pos_preceding_word(x, j - 6);
          break;
        }
        --j;
        continue; // must not be in top 13
      }

      if (x[j - 5] == ' ' &&
          x[j - 4] == 'T' &&
          x[j - 3] == 'R' &&
          x[j - 2] == 'A') {
        if (x[j - 1] == 'C' &&
            xj == 'K') {
          ansp[i] = ST_CODE_TRACK + 256 * (j - 5) + m2 * pos_preceding_word(x, j - 5);
          break;
        }
        if (x[j - 1] == 'I' &&
            xj == 'L') {
          ansp[i] = ST_CODE_TRAIL + 256 * (j - 5) +  m2 * pos_preceding_word(x, j - 5);
          break;
        }
        j -= 5;
        continue;
      }
    }


  }

  // Special case 'ST' may be Street but could also be e.g. 'ST KILDA' 'ST LEONARDS' 'ST ALBANS'
//#pragma omp parallel for
  for (R_xlen_t i = 0; i < N; ++i) {
    if (ansp[i] != NA_INTEGER) {
      continue;
    }
    int n = length(STRING_ELT(xx, i));
    const char * x = CHAR(STRING_ELT(xx, i));
    int j = 4;
    bool maybe_street = false;
    for (; j < n - 6; ++j) {
      if (x[j] != ' ' && x[j] != ',') {
        continue;
      }
      if (x[j + 1] == 'S' &&
          x[j + 2] == 'T') {
        if (x[j + 3] == ' ' || x[j + 3] == ',') {
          j = j + 4;
          maybe_street = true;
          break;
        }
        if (x[j + 3] == '.' && (x[j + 4] == ' ' || x[j + 4] == ',')) {
          j = j + 4;
          maybe_street = true;
          break;
        }
        j += 2;
      }
    }
    if (!maybe_street) {
      continue;
    }
    if (substring_within(x, j, n, "IVES", 4)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "LEONARDS", 8)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "KILDA", 5)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "THOMAS", 6)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "MARYS", 5)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "HELENA", 6)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "ALBANS", 6)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "PETERS", 6)) {
      maybe_street = false;
      continue;
    }

    if (substring_within(x, j, n, "CLAIR", 5)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "LEONARDS CREEK", 14)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "IVES", 4)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "GEORGES BASIN", 13)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "JOHNS PARK", 10)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "PATRICKS", 8)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "HELENS PARK", 11)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "ANDREWS", 7)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "MARYS", 5)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "VIDGEONS' STATION", 17)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "HELENS", 6)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "GEORGE", 6)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "JOHN", 4)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "KILDA", 5)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "MARY", 4)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "AUBYN", 5)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "RUTH", 4)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "LAWRENCE", 8)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "AGNES", 5)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "HELENS BEACH", 12)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "BEES ISLAND", 11)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "JOHN", 4)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "LUCIA", 5)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "MORRIS", 6)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "ST.GEORGES", 10)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "KITTS", 5)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "ST.MORRIS", 9)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "ST.CLAIR", 8)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "ST.PETERS", 9)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "ST.AGNES", 8)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "ST.MARYS", 8)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "KITTS", 5)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "ST.KILDA", 8)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "JOHNS", 5)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "PATRICKS RIVER", 14)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "ARNAUD", 6)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "JAMES", 5)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "PETERS PLACE ESTATE", 19)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "ANTHONYS PLACE ESTATE", 21)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "MARGARETS ESTATE", 16)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "LUCIA ESTATE", 12)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "JOHNS WOOD ESTATE", 17)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "MICHEL PRIVATE GARDEN ESTATE", 28)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "THOMAS PRIVATE ESTATE", 21)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "CLAIR ESTATE", 12)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "LEONARDS ESTATE", 15)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "LAWRENCE ESTATE", 15)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "GEORGE RANGES", 13)) {
      maybe_street = false;
      continue;
    }



    // Note j - 2 not j - 6 because it's ST not STREET
    ansp[i] = ST_CODE_STREET + m1 * (j - 4) + m2 * pos_preceding_word(x, j - 4);





  }


  // A street name is more likely to follow a comma than a space
  // if commas are present.  Check commas:
// #pragma omp parallel for
  for (R_xlen_t i = 0; i < N; ++i) {
    if (ansp[i] != NA_INTEGER) {
      continue;
    }
    int n = length(STRING_ELT(xx, i));
    const char * x = CHAR(STRING_ELT(xx, i));
    int last_comma = has_comma(x, n);
    if (!last_comma) {
      continue;
    }
    int word_sizes[16] = {0};
    int word_positions[16] = {0};
    unsigned int wsk = 0; // index of word_sizes
    // Find the sizes, positions of words preceding commas
    int this_word_size = 0;
    for (int jj = 0; jj <= last_comma; ++jj) {
      switch(x[jj]) {
      case ',':
    {
      // when ',' we record the size thus far and hence the position of the start
      word_positions[wsk] = jj - this_word_size;
      word_sizes[wsk] = this_word_size;
      this_word_size = 0;
      ++wsk;
    }
        break;
      case ' ':
        this_word_size = 0; // when ' ' we reset (i.e. don't count words preceding commas)
        break;
      default:
        ++this_word_size;
      }
    }

    bool matched = false;
    for (int w_ = 0; w_ < 16; ++w_) {
      int w = w_; // don't jump around

      if (matched) {
        break;
      }
      int len_word_i = word_sizes[w];
      if (len_word_i == 0) {
        continue;
      }

      for (R_xlen_t k = 0; k < M; ++k) {
        if (matched) {
          break;
        }
        int len_k = nchar_yyp[k];

        if (len_k != len_word_i) {
          continue;
        }

        matched = true; // provisional
        const char * y = CHAR(STRING_ELT(yy, k));
        const int wpw = word_positions[w];
        for (int c = 0; c < len_k; ++c) {
          unsigned char xc = x[c + wpw];
          unsigned char yc = y[c];
          if (xc != yc) {
            matched = false;
            break;
          }
        }
        if (matched) {
          ansp[i] = (k + 1) + m1 * (wpw - 1) + m2 * pos_preceding_word(x, wpw - 1);
        }
      }
    }

  }



// #pragma omp parallel for
  for (R_xlen_t i = 0; i < N; ++i) {
    if (ansp[i] != NA_INTEGER) {
      continue;
    }
    int n = length(STRING_ELT(xx, i));
    const char * x = CHAR(STRING_ELT(xx, i));
    int word_sizes[16] = {0};
    int word_positions[16] = {0};
    int j = 0;
    unsigned int wsk = 0, wpk = 0; // index of word_sizes
    word_sizes[0] = 1;
    while (++j < n && x[j] != ' ') {
      word_sizes[0] += 1;
    }
    j = n - 1;
    wsk = 1, wpk = 1;
    while (--j >= 1) {
      bool isnt_space = x[j] != ' ';
      bool follows_space = x[j - 1] == ' ';
      bool eow = !isnt_space && !follows_space;
      bool sow = isnt_space && follows_space;
      word_sizes[wsk] += isnt_space;
      word_positions[wpk] = j;
      wsk += eow;
      wsk &= 15u;
      wpk += sow;
      wpk &= 15u;
    }
    j = 0;
    bool matched = false;
    for (int w_ = 0; w_ < 16; ++w_) {
      int w = W_ORD[w_];

      if (matched) {
        break;
      }
      int len_word_i = word_sizes[w];

      for (R_xlen_t k = 0; k < M; ++k) {
        if (matched) {
          break;
        }
        int len_k = nchar_yyp[k];
        if (len_k != len_word_i) {
          continue;
        }

        matched = true; // provisional
        const char * y = CHAR(STRING_ELT(yy, k));
        const int wpw = word_positions[w];
        for (int c = 0; c < len_k; ++c) {
          unsigned char xc = x[c + wpw];
          unsigned char yc = y[c];
          if (xc != yc) {
            matched = false;
            break;
          }
        }
        if (matched) {
          ansp[i] = (k + 1) + m1 * (wpw - 1) + m2 * pos_preceding_word(x, wpw - 1);
        }
      }
    }

  }
  UNPROTECT(np);
  return ans;
}

SEXP digit2560(SEXP xx) {
  R_xlen_t N = xlength(xx);
  const int * x = INTEGER(xx);
  SEXP ans = PROTECT(allocVector(INTSXP, N));
  int * restrict ansp = INTEGER(ans);
// #pragma omp parallel for
  for (R_xlen_t i = 0; i < N; ++i) {
    int xi = x[i];
    ansp[i] = xi == NA_INTEGER ? xi : xi & 255;
  }
  UNPROTECT(1);
  return ans;
}

SEXP digit2561(SEXP xx) {
  R_xlen_t N = xlength(xx);
  const int * x = INTEGER(xx);
  SEXP ans = PROTECT(allocVector(INTSXP, N));
  int * restrict ansp = INTEGER(ans);
//// #pragma omp parallel for
  for (R_xlen_t i = 0; i < N; ++i) {
    unsigned int xi = x[i];
    xi /= 256u;
    xi &= 255u;
    ansp[i] = xi;
  }
  UNPROTECT(1);
  return ans;
}

SEXP digit2562(SEXP xx) {
  R_xlen_t N = xlength(xx);
  const int * x = INTEGER(xx);
  SEXP ans = PROTECT(allocVector(INTSXP, N));
  int * restrict ansp = INTEGER(ans);
// #pragma omp parallel for
  for (R_xlen_t i = 0; i < N; ++i) {
    unsigned int xi = x[i];
    xi /= 256u;
    xi /= 256u;
    xi &= 255u;
    ansp[i] = xi;
  }
  UNPROTECT(1);
  return ans;
}

SEXP digit2563(SEXP xx) {
  R_xlen_t N = xlength(xx);
  const int * x = INTEGER(xx);
  SEXP ans = PROTECT(allocVector(INTSXP, N));
  int * restrict ansp = INTEGER(ans);
// #pragma omp parallel for
  for (R_xlen_t i = 0; i < N; ++i) {
    unsigned int xi = x[i];
    // xi /= 256u;
    // xi /= 256u;
    // xi /= 256u;
    // xi &= 255u;
    ansp[i] = xi >> 24;
  }
  UNPROTECT(1);
  return ans;
}

SEXP Cdigit256(SEXP xx, SEXP dd) {
  if (!isInteger(xx) || !isInteger(dd)) {
    error("xx,dd");
  }
  const int d = asInteger(dd);
  switch(d) {
  case 0:
    return digit2560(xx);
  case 1:
    return digit2561(xx);
  case 2:
    return digit2562(xx);
  case 3:
    return digit2563(xx);
  }
  return xx;
}

SEXP Cmatch_StreetName(SEXP xx,
                       SEXP StreetMatch1,
                       SEXP jPos,
                       SEXP ReturnHash) {
  R_xlen_t N = xlength(xx);
  if (!isString(xx)) {
    error("`x` was type '%s' but must be a character vector.", type2char(TYPEOF(xx)));
  }
  if (!isInteger(StreetMatch1)) {
    error("`StreetMatch1` was type '%s' but must be an integer vector.", type2char(TYPEOF(StreetMatch1)));
  }
  if (!isInteger(jPos)) {
    error("`jPos` was type '%s' but must be an integer vector.", type2char(TYPEOF(jPos)));
  }
  const bool return_hash = asLogical(ReturnHash);

  const SEXP * xp = STRING_PTR(xx);
  const int * streetMatch1p = INTEGER(StreetMatch1);
  const int * last_number_p = INTEGER(jPos);
  const bool use_last_number = xlength(jPos) == N;
  if (xlength(StreetMatch1) != N) {
    error("Lengths differ(%d,%d).", use_last_number, xlength(StreetMatch1) & INT_MAX);
  }

  if (return_hash && use_last_number) {
    SEXP ans = PROTECT(allocVector(INTSXP, N));
    int * restrict ansp = INTEGER(ans);
    for (R_xlen_t i = 0; i < N; ++i) {

      int n = length(xp[i]);
      unsigned int si = streetMatch1p[i];
      if (n <= 4 || si > INT_MAX) {
        ansp[i] = NA_INTEGER;
        continue;
      }
      int lhs = last_number_p[i];
      int rhs = (si >> 8u) & 255;
      const char * x = CHAR(xp[i]);
      ansp[i] = djb2_hash(x, rhs, lhs);
    }
    UNPROTECT(1);
    return ans;
  }

  SEXP ans = PROTECT(allocVector(STRSXP, N));

  if (use_last_number) {
    for (R_xlen_t i = 0; i < N; ++i) {
      SEXP CX = xp[i];
      int n = length(xp[i]);
      unsigned int si = streetMatch1p[i];
      if (n <= 4 || si > INT_MAX) {
        SET_STRING_ELT(ans, i, NA_STRING);
        continue;
      }
      int si2 = last_number_p[i] + 1;
      int si1 = (si >> 8u) & 255;

      if (si1 <= si2) {
        SET_STRING_ELT(ans, i, NA_STRING);
        continue;
      }

      const char * x = CHAR(CX);
      char oy[si1 - si2 + 1];
      for (int j = si2; j < si1; ++j) {
        oy[j - si2] = x[j];
      }
      oy[si1 - si2] = '\0';
      const char * o = (const char *)oy;
      SET_STRING_ELT(ans, i, mkCharCE(o, CE_UTF8));

    }
  } else {
    for (R_xlen_t i = 0; i < N; ++i) {
      SEXP CX = STRING_ELT(xx, i);
      if (CX == NA_STRING) {
        SET_STRING_ELT(ans, i, CX);
        continue;
      }

      unsigned int si = streetMatch1p[i];
      if (si > INT_MAX) {
        SET_STRING_ELT(ans, i, NA_STRING);
        continue;
      }

      // int si0 = si & 255;
      int si1 = (si / 256) & 255;
      int si2 = si / 65536;
      int oy_len = si1 - si2 + 1;
      if (oy_len <= 0) {
        SET_STRING_ELT(ans, i, NA_STRING);
        continue;
      }


      const char * x = CHAR(CX);
      char oy[oy_len];
      for (int j = si2; j < si1; ++j) {
        oy[j - si2] = x[j];
      }
      oy[si1 - si2] = '\0';
      const char * o = (const char *)oy;
      SET_STRING_ELT(ans, i, mkCharCE(o, CE_UTF8));
    }
  }
  UNPROTECT(1);
  return ans;
}

SEXP C_NumberSuffix2Raw(SEXP xx) {
  if (!isString(xx)) {
    error("`x` was type '%s' but must be a character vector.", type2char(TYPEOF(xx))); // # nocov
  }
  R_xlen_t N = xlength(xx);
  const SEXP * xp = STRING_PTR(xx);
  SEXP ans = PROTECT(allocVector(RAWSXP, N));
  unsigned char * ansp = RAW(ans);
  for (R_xlen_t i = 0; i < N; ++i) {
    int n = length(xp[i]);
    ansp[i] = 0;
    if (n) {
      const char * x = CHAR(xp[i]);
      char x0 = x[0];
      char x1 = n > 1 ? x[1] : '\0';
      ansp[i] = number_suffix2raw(x0, x1);
    }
  }
  UNPROTECT(1);
  return ans;
}

// Returns street code from word in x
int wd2st(const char * x, int n, WordData * wd, int w) {
  int n_words = wd->n_words;
  int lhs_w = wd->lhs[w];
  int rhs_w = wd->rhs[w];
  if (w > n_words || rhs_w == 0 || !isupper(x[lhs_w])) {
    return 0;
  }
  unsigned int width_w = rhs_w - lhs_w;
  int z0pos = z0pos_by_len[width_w & NZ0POR];
  unsigned int width_w1 = width_w + 1;
  int z1pos = z0pos_by_len[width_w1 & NZ0POR];
  for (int z = z0pos; z < z1pos; ++z) {
    const StreetType * Z = ZTZ[z];
    const char * xz = Z->x;
    int nz = Z->lenx;
    if (nz == width_w && substring_within(x, lhs_w, n, xz, nz)) {
      return Z->cd;
    }
  }
  return 0;
}

bool iz_saint(int w, const char * x, int n, WordData * wd, unsigned char * m1, unsigned int Postcode) {
  unsigned char m1_postcode = m1[Postcode];
  if (!m1_postcode) {
    return false;
  }
  int n_words = wd->n_words;
  if (w + 1 >= n_words) {
    return false;
  }
  // next word
  int lhs_w1 = wd->lhs[w + 1];
  int rhs_w1 = wd->rhs[w + 1];
  int width_w1 = rhs_w1 - lhs_w1;

  unsigned int Stsi = m1_postcode & 127;
  const Saint * Stp = Sts[Stsi];
  int n_saints = Stp->n_saints;
  int nsuf = Stp->nsuf;
  // There are only two postcodes with more than two locality suffixes
  if (n_saints == 2) {
    int nsuf2 = Stp->nsuf2;
    if (nsuf == width_w1) {
      const char * suf = Stp->suf;
      if (substring_within(x, lhs_w1, n, suf, nsuf)) {
        return true;
      }
    }
    if (nsuf == width_w1) {
      const char * suf2 = Stp->suf2;
      if (substring_within(x, lhs_w1, n, suf2, nsuf2)) {
        return true;
      }
    }
  }
  if (n_saints == 1) {
    if (nsuf == width_w1) {
      const char * suf = Stp->suf;
      if (substring_within(x, lhs_w1, n, suf, nsuf)) {
        return true;
      }
    }
  }
  return false;
}

int has_CRT(const char * x, int n, WordData * wd) {
  int n_words = wd->n_words;
  for (int w = 0; w < n_words; ++w) {
    int lhs_w = wd->lhs[w];
    int rhs_w = wd->rhs[w];
    if (rhs_w - lhs_w == 3) {
      if (x[lhs_w++] == 'C' && x[lhs_w++] == 'R' && x[lhs_w] == 'T') {
        return w + 1;
      }
    }
  }
  return 0;
}

void do_street_type_no_number(int ans[3], const char * x, int n, WordData * wd, unsigned int Postcode, unsigned char * m1) {
  unsigned int hashes[WORD_DATUMS] = {0};
  int n_words = wd->n_words;
  for (int w = 0; w < n_words; ++w) {
    hashes[w] = djb2_hash(x, wd->rhs[w], wd->lhs[w] - 1);
  }
  int street_type = 0;
  for (int s = 0; s < 32; ++s) {
    // Check the hash of the second word -- most likely to be the street type
    if (hashes[1] == hash_street_types[s]) {
      ans[0] = hash_street_typecd[s];
      ans[1] = wd->lhs[1];
      ans[2] = hashes[0];
      return;
    }
  }

  bool found_first_32 = false;
  for (int w = 1; w < n_words; ++w) {
    if (found_first_32) {
      break;
    }
    for (int s = 0; s < 32; ++s) {
      if (hashes[w] == hash_street_types[s]) {
        street_type = hash_street_typecd[s];
        ans[0] = street_type;
        ans[1] = wd->lhs[w];
        ans[0] = hashes[w - 1];
        found_first_32 = true;
        break;
      }
    }
  }
  for (int z_ = 0; z_ < NZ; ++z_) {
    // go in order of 'ordering'
    int z = oZTC[z_];
    const StreetType * Z = ZTZ[z];
    int nz = Z->lenx;
    for (int w_ = 1; w_ < WORD_DATUMS; ++w_) {
      int w = w_; // for no numbering, just go in 'natural' order
      if (w > n_words) {
        break;
      }
      int lhs_w = wd->lhs[w];
      int rhs_w = wd->rhs[w];
      if (rhs_w == 0) {
        continue;
      }
      unsigned int width_w = rhs_w - lhs_w;
      if (width_w != nz) {
        continue;
      }
      const char * xz = Z->x;
      if (substring_within(x, lhs_w, n, xz, nz)) {
        if (z == ST_ST_ST && iz_saint(w, x, n, wd, m1, Postcode)) {
          continue;
        }
        ans[0] = Z->cd;
        ans[1] = lhs_w;
        ans[2] = djb2_hash(x, wd->lhs[w - 1], -1);
        return;
      }
    }
  }

}

void do_street_type(int ans[3], const char * x, int n, int j__ /*Position after number, zero significant => no number */,
                    WordData * wd, unsigned int Postcode, unsigned char * m1) {
  if (Postcode > SUP_POSTCODE_) {
    return;
  }
  if (j__ == 0) {
    do_street_type_no_number(ans, x, n, wd, Postcode, m1);
    return;
  }



  int no1st = wd->no1st;
  int n_words = wd->n_words;
  int first_word_post_number = 1;
  if (no1st) {
    for (int w = 2; w < WORD_DATUMS - 1; ++w) {
      int wj = wd->lhs[w];
      if (wj > no1st) {
        int wj1 = wd->lhs[w + 1];
        unsigned char xwj1 = x[wj1];
        if (isdigit(xwj1)) {
          continue;
        }
        first_word_post_number = w;
        break;
      }
    }
  }
  if (Postcode == 3023) {
    for (int w = first_word_post_number; w < n_words - 3; ++w) {
      int lhs_w0 = wd->lhs[w];
      char w10 = x[lhs_w0];
      if (w10 != 'S') {
        continue;
      }
      int lhs_w1 = wd->lhs[w + 1];
      int lhs_w2 = wd->lhs[w + 2];
      // ST VINCENT W
      // 012345678901

      if (lhs_w1 != lhs_w0 + 3 ||
          lhs_w2 != lhs_w0 + 11) {
        continue;
      }

      char w20 = x[lhs_w1];

      if (w20 != 'V') {
        continue;
      }
      char w30 = x[lhs_w2];
      if (w30 != 'W') {
        continue;
      }
      // int rhs_w1 = wd->rhs[w + 1];
      // int rhs_w2 = wd->rhs[w + 2];
      ans[0] = ST_CODE_WAY;
      ans[1] = lhs_w2;
      ans[2] = DJB2_ST_VINCENT;
      return;
    }
  }
  if (Postcode == 3024 || Postcode == 3084 || Postcode == 3141 || Postcode == 3936) {
    // possible THE RIGHI
    for (int w = first_word_post_number; w < n_words - 2; ++w) {
      int lhs_w0 = wd->lhs[w];
      char w10 = x[lhs_w0];
      if (w10 != 'T') {
        continue;
      }
      int lhs_w1 = wd->lhs[w + 1];
      if (lhs_w1 != lhs_w0 + 4) {
        continue;
      }
      char w20 = x[lhs_w1];
      if (w20 != 'R') {
        continue;
      }
      ans[0] = 0;
      ans[1] = 0;
      ans[2] = DJB2_THE_RIGHI;
    }
  }

  if (Postcode >= 3147 && Postcode <= 3152) {
    // possibly high street road
    for (int w = first_word_post_number; w < n_words - 3; ++w) {
      int lhs_w0 = wd->lhs[w];
      char w10 = x[lhs_w0];
      if (w10 != 'H') {
        continue;
      }
      int lhs_w1 = wd->lhs[w + 1];
      int lhs_w2 = wd->lhs[w + 2];
      char w20 = x[lhs_w1];
      char w30 = x[lhs_w2];
      if (w20 != 'S' || w30 != 'R') {
        continue;
      }
      // int rhs_w1 = wd->rhs[w + 1];
      // int rhs_w2 = wd->rhs[w + 2];
      ans[0] = 1;
      ans[1] = lhs_w2;
      ans[2] = DJB2_HIGH_STREET;
      return;
    }
  }
  if (Postcode == 3068 || Postcode == 3070) {
    // possibly ST GEORGES ROAD
    for (int w = first_word_post_number; w < n_words - 3; ++w) {
      int lhs_w0 = wd->lhs[w];
      char w10 = x[lhs_w0];
      if (w10 != 'S') {
        continue;
      }
      int lhs_w1 = wd->lhs[w + 1];
      int lhs_w2 = wd->lhs[w + 2];
      // ST GEORGES R
      // 012345678901

      if (lhs_w1 != lhs_w0 + 3 ||
          lhs_w2 != lhs_w0 + 11) {
        continue;
      }

      char w20 = x[lhs_w1];

      if (w20 != 'G') {
        continue;
      }
      char w30 = x[lhs_w2];
      if (w30 != 'R' && w30 != 'C') {
        continue;
      }
      // int rhs_w1 = wd->rhs[w + 1];
      // int rhs_w2 = wd->rhs[w + 2];
      ans[0] = w30 == 'R' ? ST_CODE_ROAD : ST_CODE_COURT;
      ans[1] = lhs_w2;
      ans[2] = DJB2_ST_GEORGES;
      return;
    }
  }
  if (Postcode == 3174) {
    // LOWER TERRACE
    for (int w = first_word_post_number; w < n_words - 2; ++w) {
      int lhs_w0 = wd->lhs[w];
      char w10 = x[lhs_w0];
      if (w10 != 'L') {
        continue;
      }
      int lhs_w1 = wd->lhs[w + 1];
      int lhs_w2 = wd->lhs[w + 2];

      if (lhs_w1 != lhs_w0 + 6 ||
          lhs_w2 != lhs_w0 + 14) {
        continue;
      }
      ans[0] = ST_CODE_CRESCENT;
      ans[1] = lhs_w2;
      ans[2] = 1301557904;
      return;
    }
  }
  if (Postcode == 3207) {
    // ESPLANADE EAST
    for (int w = first_word_post_number; w < n_words - 2; ++w) {
      int lhs_w0 = wd->lhs[w];
      int lhs_w2 = wd->lhs[w + 2];
      char w10 = x[lhs_w0];
      // Check first letter of ESPLANADE
      if (w10 != 'E') {
        continue;
      }
      const char ESPLANADE___ST[15] = "ESPLANADE EAST";
      bool is_esplanade = true;
      for (int j = 1; j < 14; ++j) {
        if (j == 10 || j == 11) {
          // WEST
          // EAST
          // ^^
          continue;
        }
        if (x[lhs_w0 + j] != ESPLANADE___ST[j]) {
          is_esplanade = false;
        }
      }
      if (is_esplanade) {

        ans[0] = 0;
        ans[1] = lhs_w2;
        ans[2] = x[lhs_w0 + 10] == 'E' ? DJB2_ESPLANADE_EAST : DJB2_ESPLANADE_WEST;
        return;
      }
    }
  }

  // const int W_ORD[WORD_DATUMS] = {  2, 3,  4,   5,  6, 0, 1, 7,
  //                                   11, 12, 13, 10, 14, 8, 9, 15};
  const int W_ORD[WORD_DATUMS] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};

  // one with first 20
  for (int w_ = 0; w_ < 4; ++w_) {
    int w = W_ORD[w_] + first_word_post_number;
    if (w > n_words) {
      continue;
    }

    int lhs_w = wd->lhs[w];
    int rhs_w = wd->rhs[w];
    if (rhs_w == 0) {
      continue;
    }
    unsigned int width_w = rhs_w - lhs_w;
    int z0pos = z0pos_by_len[width_w & NZ0POR];
    unsigned int width_w1 = width_w + 1;
    int z1pos = z0pos_by_len[width_w1 & NZ0POR];
    for (int z = z0pos; z < z1pos; ++z) {
      const StreetType * Z = ZTZ[z];
      if (Z->cd > 20) {
        // Don't check if code is outside top 16 common
        continue;
      }

      int nz = Z->lenx;
      if (nz != width_w) {
        continue;
      }

      const char * xz = Z->x;
      if (substring_within(x, lhs_w, n, xz, nz)) {
        if (z == ST_ST_ST && iz_saint(w, x, n, wd, m1, Postcode)) {
          continue;
        }
        ans[0] = Z->cd;
        ans[1] = lhs_w;
        return;
      }
    }
  }

  for (int w_ = 0; w_ < WORD_DATUMS; ++w_) {
    int w = W_ORD[w_];
    if (w > n_words) {
      continue;
    }
    if (w < first_word_post_number) {
      continue;
    }
    int lhs_w = wd->lhs[w];
    int rhs_w = wd->rhs[w];
    if (rhs_w == 0) {
      continue;
    }
    unsigned int width_w = rhs_w - lhs_w;
    int z0pos = z0pos_by_len[width_w & NZ0POR];
    unsigned int width_w1 = width_w + 1;
    int z1pos = z0pos_by_len[width_w1 & NZ0POR];
    for (int z = z0pos; z < z1pos; ++z) {
      const StreetType * Z = ZTZ[z];
      const char * xz = Z->x;
      int nz = Z->lenx;
      if (Z->cd == ST_CODE_VALE && isnt_vale_postcode(Postcode)) {
        continue;
      }
      // bool substring_within(const char * x, int i, int n, const char * y, int m)
      if (nz == width_w && substring_within(x, lhs_w, n, xz, nz)) {
        if (z == ST_ST_ST && iz_saint(w, x, n, wd, m1, Postcode)) {
          continue;
        }

        ans[0] = Z->cd;
        ans[1] = lhs_w;
        return;
      }
    }
  }
}

#define N_FLATS 9
const char * FLATS[N_FLATS] =
  {"U", "G",
   "APT",
   "CARS", "FLAT", "ROOM", "SHOP", "UNIT",
   "APARTMENT"};

// Approximate frequency
#define FLAT_CODE_UNIT 1
#define FLAT_CODE_FLAT 2
#define FLAT_CODE_CARS 3
#define FLAT_CODE_SHOP 4
#define FLAT_CODE_APT_ 5
#define FLAT_CODE_ROOM 9
// corresponding codes
const uint8_t FLATC[N_FLATS] =
  {FLAT_CODE_UNIT, FLAT_CODE_UNIT,
   FLAT_CODE_APT_,
   FLAT_CODE_CARS, FLAT_CODE_FLAT, FLAT_CODE_ROOM, FLAT_CODE_SHOP, FLAT_CODE_UNIT,
   FLAT_CODE_APT_};


int has_flat(const char * x, int n) {
  for (int j = 0; j < n; ++j) {
    unsigned char xj = x[j];
    if (isdigit(x[j])) {
      // if a digit but no 'flat' synonym encountered, we check for
      // a slash to signify unit
      ++j;
      while (isdigit(x[j])) {
        ++j;
      }
      while (isspace(x[j])) {
        ++j;
      }
      // Possibly 108A/144
      if (isUPPER(x[j]) && x[j + 1] == '/') {
        return 1;
      }
      if (x[j] == '/') {
        return 1;
      }
      return 0;
    }
    if (j == 0 || x[j - 1] == ' ') {
      if (x[j] == 'U') {
        if ((x[j + 1] == ' ' && isdigit(x[j + 2])) || isdigit(x[j + 1])) {
          return FLAT_CODE_UNIT;
        }
      }
      // Not sure why I previously put "UNIT" rather than "UNIT " here; however
      // UNITS sometimes appears in addresses that do not a FLAT_NUMBER field.
      if (substring_within(x, j, n, "UNIT", 4) && (x[j + 4] == ' ' || isdigit(x[j + 4]))) {
        return FLAT_CODE_UNIT;
      }
      if (substring_within(x, j, n, "APARTMENT ", 10)) {
        return FLAT_CODE_APT_;
      }
      if (substring_within(x, j, n, "FLAT ", 5)) {
        return FLAT_CODE_FLAT;
      }
      if (substring_within(x, j, n, "ROOM ", 5)) {
        return FLAT_CODE_ROOM;
      }
      if (substring_within(x, j, n, "SHOP ", 5)) {
        return FLAT_CODE_SHOP;
      }
      if (substring_within(x, j, n, "CAR", 3)) {
        if (substring_within(x, j, n, "CARSPACE ", 9) ||
            substring_within(x, j, n, "CARPARK ", 8)) {
          return FLAT_CODE_CARS;
        }
      }

      unsigned char xk = x[j + 1];
      if (isdigit(xk)) {
        // e.g. G05
        switch(xj) {
        case 'G':
          return FLAT_CODE_UNIT;
        case 'U':
          return FLAT_CODE_UNIT;
        }
      }
    }
  }
  return 0;
}


// LEVEL 123
// 012345678  returns 9
int where_LEVEL_exact_number_ends(const char * x, int n) {
  if (x[0] == 'L' && x[1] == 'E' && x[2] == 'V' && x[3] == 'E' && x[4] == 'L' && (isdigit(x[5]) || isspace(x[5]))) {
    int k = 5;
    while (isspace(x[k])) {
      ++k;
    }
    while (isdigit(x[k])) {
      ++k;
    }
    return k;
  }
  for (int j = 1; j < n - 5; ++j) {
    if (x[j - 1] != ' ') {
      continue;
    }
    if (x[j] == 'L' &&
        x[j + 1] == 'E' && x[j + 2] == 'V' &&
        x[j + 3] == 'E' && x[j + 4] == 'L' && (isdigit(x[j + 5]) || isspace(x[j + 5]))) {
      int k = j + 5;
      while (isspace(x[k])) {
        ++k;
      }
      while (isdigit(x[k])) {
        ++k;
      }
      return k;
    }
  }
  return 0;
}

int where_LEVEL_abbrev_number_ends(const char * x, int n) {
  if (x[0] == 'L') {
    int k = 1;
    while (isspace(x[k])) {
      ++k;
    }
    while (isdigit(x[k])) {
      ++k;
    }
    return k;
  }
  for (int j = 1; j < n - 5; ++j) {
    if (x[j - 1] != ' ') {
      continue;
    }
    if (x[j] == 'L' &&
        x[j + 1] == 'E' && x[j + 2] == 'V' &&
        x[j + 3] == 'E' && x[j + 4] == 'L') {
      int k = j + 5;
      while (isspace(x[k])) {
        ++k;
      }
      while (isdigit(x[k])) {
        ++k;
      }
      return k;
    }
  }
  return 0;
}



int flat_of(const char * x, int n, int J[1]) {
  int k = 0; // position of digit starting flat
  bool has_flat = false;
  // WordData wd = word_data(x, n, 0);

  // test for level:
  // int has_level = has_LEVEL(wd);
  // int j = j_post_LEVEL(x, n);

  int j = 0;
  for (; j < n; ++j) {
    if (isdigit(x[j])) {
      // if a digit but no 'flat' synonym encountered, we check for
      // a slash to signify unit
      k = j;
      ++j;
      while (isdigit(x[j])) {
        ++j;
      }
      // possibly a suffix
      if (isupper(x[j]) && x[j + 1] == '/') {
        has_flat = true;
        break;
      }
      while (isspace(x[j])) {
        ++j;
      }
      if (x[j] == '/') {
        has_flat = true;
        break;
      }
      return 0;
    }
    if (j == 0 || x[j - 1] == ' ') {
      if (x[j] == 'U') {
        if (substring_within(x, j, n, "UNIT", 4)) {
          k = j + 4;
          while (isspace(x[k])) {
            ++k;
          }
          if (isdigit(x[k])) {
            has_flat = true;
            break;
          }
          return 0; // Unusual, implies 'UNIT' followed by non digit
        }
        if ((x[j + 1] == ' ' && isdigit(x[j + 2]))) {
          k = j + 2;
          has_flat = true;
          break;
        } else if (isdigit(x[j + 1])) {
          k = j + 1;
          has_flat = true;
          break;
        } else {
          return 0;
        }
      }
      if (substring_within(x, j, n, "APARTMENT ", 10)) {
        has_flat = true;
        k = j + 10;
        break;
      }
      if (substring_within(x, j, n, "FLAT ", 5)) {
        has_flat = true;
        k = j + 5;
        break;
      }
      if (substring_within(x, j, n, "ROOM ", 5)) {
        has_flat = true;
        k = j + 5;
        break;
      }
      // e.g. G05
      if (x[j] == 'G') {
        if (isdigit(x[j + 1])) {
          has_flat = true;
          k = j + 1;
          break;
        }
        if (isspace(x[j + 1]) && isdigit(x[j + 2])) {
          has_flat = true;
          k = j + 2;
          break;
        }
      }
    }
  }
  int o = 0;
  if (has_flat) {
    while (isdigit(x[k])) {
      o *= 10;
      o += x[k] - '0';
      ++k;
    }
  }
  J[0] = k;
  return o;
}

int next_word(int j, WordData wd) {
  int n_words = wd.n_words;
  for (int w = 1; w < n_words - 1; ++w) {
    if (wd.lhs[w] > j) {
      return wd.lhs[w];
    }
  }
  return wd.lhs[n_words - 1];
}



void first_three_numbers(int ans[4], unsigned char suf[3], const char * x, int n) {
  int i = 0; // index of number
  int k = 0;
  int j = 0;
  unsigned char x0 = x[0];
  if (!isdigit(x0)) {
    // BIG4
    if (x[j] == 'B' && x[j + 1] == 'I' && x[j + 2] == 'G') {
      j += 4;
    }

  } else {
    ans[0] = x0 - '0';
    ++j;
    if (!isdigit(x[j])) {
      suf[i] = x[j];
      ++i;
      k = j;
    }
  }

  for (; j < n; ++j) {
    unsigned char xj = x[j];
    if (isdigit(xj)) {
      ans[i] *= 10;
      ans[i] += xj - '0';
      if (!isdigit(x[j + 1])) {
        suf[i] = x[j + 1];
        ++i;
        ++j;
        k = j;
        if (i == 3) {
          break;
        }
      }
    }

  }
  ans[3] = k;
}

void first_four_numbers(int ans[5], unsigned char suf[3], const char * x, int n) {
  int i = 0; // index of number
  int k = 0;
  int j = 0;
  unsigned char x0 = x[0];
  if (!isdigit(x0)) {
    // BIG4
    if (x[j] == 'B' && x[j + 1] == 'I' && x[j + 2] == 'G') {
      j += 4;
    }

  } else {
    ans[0] = x0 - '0';
    ++j;
    if (!isdigit(x[j])) {
      suf[i] = x[j];
      ++i;
      k = j;
    }
  }

  for (; j < n; ++j) {
    unsigned char xj = x[j];
    if (isdigit(xj)) {
      ans[i] *= 10;
      ans[i] += xj - '0';
      if (!isdigit(x[j + 1])) {
        // note i must be < 3, but if
        // we have never entered this section
        // where (i == 3) => break
        // it can be at most 1
        if (i < 3) {
          suf[i] = x[j + 1];
        }
        ++i;
        ++j;
        k = j;
        if (i == 4) {
          break;
        }
      }
    }

  }
  ans[4] = k;
}

unsigned char suf3suf(unsigned char x[3]) {
  if (x[2] > '/') {
    return x[2];
  }
  if (x[1] > '/') {
    return x[1];
  }
  if (x[0] > '/') {
    return x[0];
  }
  return 0;
}


Address do_standard_address(const char * x, int n, unsigned char * m1, int postcode, TrieNode * root) {
  int numberFirstLast[3] = {0};
  int Street[2] = {0};
  Address ad;
  WordData wd = word_data(x, n, 0);
  int level = xLEVEL(wd);
  unsigned char suf[3] = {0};
  int poa_digits = (postcode == 0 ? 0 : (postcode < 1000 ? 3 : 4));
  int n_less_poa = n - poa_digits;
  int j = 0;
  if (level) {
    int four_nos[5] = {0};
    first_four_numbers(four_nos, suf, x, n_less_poa);
    if (four_nos[3] == 0) {
      // i.e. only two numbers identified (excl postcode and level)
      // could be flat then number or number then number
      if (has_flat(x, n_less_poa - 1)) {
        numberFirstLast[0] = four_nos[0];
        numberFirstLast[1] = four_nos[2];
      } else {
        numberFirstLast[1] = four_nos[1];
        numberFirstLast[2] = four_nos[2];
      }
    } else {
      numberFirstLast[0] = four_nos[0];
      numberFirstLast[1] = four_nos[2];
      numberFirstLast[2] = four_nos[3];
    }
    j = next_word(four_nos[4], wd) ; // position after final digit
  } else {
    int three_nos[4] = {0};
    first_three_numbers(three_nos, suf, x, n_less_poa);
    if (three_nos[0] == 0) {
      // no numbers (exclude postcode)
      j = 0;
      wd.no1st = 0;
    } else {

      if (three_nos[2] == 0) {
        // i.e. only two numbers identified (excl postcode)
        // could be flat then number or number then number
        if (has_flat(x, n_less_poa - 1)) {
          numberFirstLast[0] = three_nos[0];
          numberFirstLast[1] = three_nos[1];
        } else {
          numberFirstLast[1] = three_nos[0];
          numberFirstLast[2] = three_nos[1];
        }
      } else {
        numberFirstLast[0] = three_nos[0];
        numberFirstLast[1] = three_nos[1];
        numberFirstLast[2] = three_nos[2];
      }
      j = next_word(three_nos[3], wd) ; // position after final digit
    }
  }
  if (postcode > 0 && postcode <= MAX_POSTCODE) {
    int the_street = THE_xxx3(root, wd, M_POSTCODE[postcode].THE_code);
    // int the_street = 0;
    if (the_street) {
      ad.postcode = postcode;
      ad.flat_number = numberFirstLast[0];
      ad.number_first = numberFirstLast[1];
      ad.number_last = numberFirstLast[2];
      // assume such a street may not be hashed
      ad.hashStreetName = the_street;
      ad.street_type = 0;
      ad.suffix = suf3suf(suf);
      return ad;
    }
  }
  int street_type[3] = {0};
  do_street_type(street_type, x, n, j, &wd, postcode, m1);
  Street[1] = street_type[0];
  ad.hashStreetName = street_type[2];

  // int j_StreetName = j;

  // Give the hashes of the next 1,2,3,4 words
  // idea is the street name may be more than one name
  if (!ad.hashStreetName) {
    unsigned int hash = 5381;
    // street_type[1] = pos of first word of street type
    // so < -1 to omit space
    int hash_lhs = j;
    int hash_rhs = street_type[1] - 1;
    while (hash_rhs > j && !isupper(x[hash_rhs])) {
      --hash_rhs;
    }
    for (int k = hash_lhs; k <= hash_rhs; ++k) {
      unsigned char xk = x[k];
      hash = ((hash << 5) + hash) ^ xk;
    }
    ad.hashStreetName = hash;
  }

  ad.postcode = postcode;
  ad.flat_number = numberFirstLast[0];
  ad.number_first = numberFirstLast[1];
  ad.number_last = numberFirstLast[2];
  ad.street_type = Street[1];
  if (ad.hashStreetName == 5381 && ad.street_type == ST_CODE_ESPLANADE) {
    // Strange quirk where 'ESPLANADE' is the street name
    ad.hashStreetName = DJB2_ESPLANADE;
    ad.street_type = 0;
  }
  ad.suffix = suf3suf(suf);

  return ad;
}

static void prepare_M1(unsigned char * M1) {
  // purpose of this function is to memoize the
  // function (postcode => saint data)
  memset(M1, 0, SUP_POSTCODES);
  for (int p = 0; p < NSAINT; ++p) {
    const Saint * Stp = Sts[p];
    int postcode_p = Stp->postcode;
    int n_saintsp = Stp->n_saints;
    M1[postcode_p] = 128 * (n_saintsp == 2) + p;
    M_POSTCODE[postcode_p].n_saints = n_saintsp;
  }


}


SEXP C_do_standard_address(SEXP xx) {
  R_xlen_t N = xlength(xx);
  const SEXP * xp = STRING_PTR(xx);
  // Memoiziation
  unsigned char * M1 = malloc(sizeof(char) * SUP_POSTCODES);
  if (M1 == NULL) {
    error("Internal error(C_do_standard_address): unable to allocate M1");
  }
  prepare_M1(M1);
  TrieNode * root = getNode();
  if (root == NULL) {
    free(M1);
    free(root);
    error("Unable to allocate TrieNode*root.");
  }
  insert_all(root);
  memoize_trie_postcodes(); // inserts the THE codes appropriately


  int np = 0;

  SEXP FlatNumber = PROTECT(allocVector(INTSXP, N)); np++;
  SEXP NumberFirst = PROTECT(allocVector(INTSXP, N)); np++;
  SEXP NumberLast  = PROTECT(allocVector(INTSXP, N)); np++;
  SEXP H0 = PROTECT(allocVector(INTSXP, N)); np++;
  SEXP StreetCode = PROTECT(allocVector(INTSXP, N)); np++;
  SEXP Postcode = PROTECT(allocVector(INTSXP, N)); np++;
  SEXP NumberSuffix = PROTECT(allocVector(RAWSXP, N)); ++np;

  int * restrict flat_numberp = INTEGER(FlatNumber);
  int * restrict number_firstp = INTEGER(NumberFirst);
  int * restrict number_lastp = INTEGER(NumberLast);
  int * restrict h0 = INTEGER(H0);
  int * restrict street_codep = INTEGER(StreetCode);
  int * restrict pp = INTEGER(Postcode);
  unsigned char * restrict number_suffixp = RAW(NumberSuffix);

  for (R_xlen_t i = 0; i < N; ++i) {
    int n = length(xp[i]);
    if (n <= 4) {
      pp[i] = NA_INTEGER;
      number_firstp[i] = NA_INTEGER;
      number_lastp[i] = NA_INTEGER;
      h0[i] = 0;
      street_codep[i] = NA_INTEGER;
      flat_numberp[i] = NA_INTEGER;
      number_suffixp[i] = 0;
      continue;
    }
    const char * x = CHAR(xp[i]);
    Address ad = do_standard_address(x, n, M1, xpostcode_unsafe(x, n), root);
    h0[i] = ad.hashStreetName;
    pp[i] = ad.postcode;
    street_codep[i] = ad.street_type;
    flat_numberp[i] = ad.flat_number;
    number_firstp[i] = ad.number_first;
    number_lastp[i] = ad.number_last;
    number_suffixp[i] = ad.suffix;
  }

  SEXP ans = PROTECT(allocVector(VECSXP, np)); ++np;
  int li = 0;
  SET_VECTOR_ELT(ans, li, FlatNumber);   ++li;
  SET_VECTOR_ELT(ans, li, NumberFirst);  ++li;
  SET_VECTOR_ELT(ans, li, NumberLast) ;  ++li;
  SET_VECTOR_ELT(ans, li, NumberSuffix); ++li;
  SET_VECTOR_ELT(ans, li, H0);           ++li;
  SET_VECTOR_ELT(ans, li, StreetCode);   ++li;
  SET_VECTOR_ELT(ans, li, Postcode);     ++li;
  UNPROTECT(np);
  free(M1);
  freeTrie(root);
  return ans;

}

SEXP ZMatchStreetName(SEXP x) {
  if (!isString(x)) {
    error("x not a STRSXP."); // # nocov
  }
  R_xlen_t N = xlength(x);
  const SEXP * xp = STRING_PTR(x);
  SEXP ans = PROTECT(allocVector(INTSXP, N));
  int * restrict ansp = INTEGER(ans);

  for (R_xlen_t i = 0; i < N; ++i) {
    unsigned int o = 0;
    int n = length(xp[i]);
    if (n <= 2) {
      ansp[i] = NA_INTEGER;
      continue;
    }
    const char * xi = CHAR(xp[i]);
    WordData wdi = word_data(xi, n, 0);
    bool matched = false;
    for (int z = 0; z < 271; ++z) {
      const char * zi = ZTZ[z]->x;
      int zlen = ZTZ[z]->lenx;
      int zcd = ZTZ[z]->cd;
      for (int w = 0; w < wdi.n_words; ++w) {
        int lhs_w = wdi.lhs[w];
        int rhs_w = wdi.rhs[w];
        int www_w = rhs_w - lhs_w;
        if (www_w != zlen) {
          continue;
        }
        matched = true;
        for (int j = lhs_w; j < rhs_w; ++j) {
          if (xi[j] != zi[j]) {
            matched = false;
            o = zcd;
            break;
          }
        }
        if (matched) {
          break;
        }
      }
    }
    ansp[i] = o;
  }
  UNPROTECT(1);
  return ans;
}


SEXP C_StaticAssert(SEXP x) {
  // Check ZTZ concordance with z0pos_by_len
  for (int i = 1; i < NZ0POS; ++i) {
    int zi = z0pos_by_len[i];
    if (zi && zi < 271) {
      int len0 = ZTZ[zi - 1]->lenx;
      int len1 = ZTZ[zi]->lenx;
      if (len0 == len1) {
        warning("(StaticAssert FAIL)len0 == len1 [%d == %d] at i = %d with %s", len0, len1, i, ZTZ[zi]->x);
      }
      if (len1 != i) {
        warning("(StaticAssert FAIL)len1 != i + 2 [%d != %d + 2]", len1, i);
      }
    }
  }
  for (int i = 1; i < 271; ++i) {
    int o_ztz_i1 = oZTC[i];
    int o_ztz_i0 = oZTC[i - 1];
    int cd_i0 = ZTZ[o_ztz_i0]->cd;
    int cd_i1 = ZTZ[o_ztz_i1]->cd;
    if (cd_i0 != cd_i1 && (cd_i0 != cd_i1 - 1)) {
      Rprintf("ZTZ[oztz_i - 1].x = %s\n", ZTZ[o_ztz_i0]->x);
      Rprintf("ZTZ[oztz_i].x = %s\n", ZTZ[o_ztz_i1]->x);

      warning("(StaticAssert FAIL)cd_i0 = %d, yet cd_i1 = %d, at %d ", cd_i0, cd_i1, i);
      break;
    }
  }

  return R_NilValue;
}



SEXP C_areST(SEXP x) {
  if (!isString(x)) {
    error("x must be a STRSXP."); // # nocov
  }
  const SEXP * xp = STRING_PTR(x);
  R_xlen_t N = xlength(x);
  SEXP ans = PROTECT(allocVector(LGLSXP, N));
  int * restrict ansp = LOGICAL(ans);
  for (R_xlen_t i = 0; i < N; ++i) {
    int n = length(xp[i]);
    ansp[i] = FALSE;
    if (n < 2) {
      continue;
    }
    const char * xi = CHAR(xp[i]);
    if (n == 2) {
      ansp[i] = xi[0] == 'S' && xi[1] == 'T';
      continue;
    }

    int j = 0;
    if (xi[j] == 'S' && xi[j + 1] == 'T' && !isalnum(xi[j + 2])) {
      ansp[i] = 1;
      continue;
    }

    bool o = false;
    while (++j < n - 2) {
      if (!isalnum(xi[j - 1]) && xi[j] == 'S') {
        if (xi[j + 1] != 'T') {
          ++j;
          continue;
        }
        o = true;
        break;
      }
    }
    ansp[i] = o;
  }
  UNPROTECT(1);
  return ans;
}



SEXP C_has_word(SEXP xx, SEXP ww) {
  R_xlen_t N = xlength(xx);
  const SEXP * xp = STRING_PTR(xx);
  SEXP ans = PROTECT(allocVector(RAWSXP, N));
  unsigned char * ansp = RAW(ans);
  const int w = asInteger(ww);
  for (R_xlen_t i = 0; i < N; ++i) {
    int n = length(xp[i]);
    const char * x = CHAR(xp[i]);
    WordData wd = word_data(x, n, 0);
    switch(w) {
    case 0:
      ansp[i] = wd.n_words;
      break;
    case 1:
      ansp[i] = has_LEVEL(wd);
    }
  }
  UNPROTECT(1);
  return ans;

}

static int get_street_type_line1(const char * x, int n) {
  int j = n - 1;
  while (j > 0 && x[j] != ' ') {
    --j;
  }
  ++j;
  int len = n - j;
  char x0 = x[j];
  if (len >= NZ0POS) {
    return 0;
  }
  int lhs = z0pos_by_len[len];
  int rhs = ((len + 1) >= NZ0POS) ? NZ : z0pos_by_len[len + 1];
  for (int z = lhs; z < rhs; ++z) {
    const char * zi = ZTZ[z]->x;
    if (x0 != zi[0]) {
      continue;
    }
    bool matched = true;
    for (int k = 1; k < len; ++k) {
      if (x[j + k] != zi[k]) {
        matched = false;
        break;
      }
    }
    if (!matched) {
      continue;
    }
    int zcd = ZTZ[z]->cd;
    return zcd;
  }
  return 0;
}

static void xnumber2(unsigned int ans[2], int J[1], const char * x, int n) {
  int j = J[0];
  for (int i = j, k = 0; i < n; ++i) {
    if (isdigit(x[i])) {
      if (i >= 2 && (i == 2 || x[i - 3] == ' ') && x[i - 2] == 'L' && x[i - 1] == ' ') {
        continue; // is LEVEL
      }
      if (i >= 6 && (i == 6 || x[i - 7] == ' ') &&
          x[i - 6] == 'L' &&
          x[i - 5] == 'E' &&
          x[i - 4] == 'V' &&
          x[i - 3] == 'E' &&
          x[i - 2] == 'L' &&
          x[i - 1] == ' ') {
        continue;
      }
      do {
        ans[k] *= 10;
        ans[k] += x[i] - '0';
        ++i;
      } while (isdigit(x[i]));
      J[0] = i; // move the pointer to the char after digit
      ++k;
      if (k == 2) {
        return;
      }
    }
  }
}

unsigned char get_suff(const char * x, int n) {
  unsigned char suf[3] = {0};
  for (int j = 1, k = 0; j < n - 1; ++j) {
    if (isdigit(x[j - 1]) && isupper(x[j])) {
      suf[k] = x[j];
      ++k;
      if (k >= 3) {
        break;
      }
    }
  }
  return suf3suf(suf);
}


Address get_address_line1(const char * x, int n, int J[1]) {
  Address A;
  A.street_type = get_street_type_line1(x, n);
  int flat = flat_of(x, n, J);
  if (flat) {
    A.flat_number = flat;
  }
  unsigned int nos[2] = {0};
  xnumber2(nos, J, x, n);
  A.number_first = nos[0];
  A.number_last = nos[1];
  while (isspace(J[0])) {
    ++J[0];
  }

  A.suffix = get_suff(x, n);
  if (A.suffix != 0) {
    J[0] += 1;
    J[0] += isspace(J[0]);
  }
  A.hashStreetName = djb2_hash(x, n, J[0]);
  return A;
}


//' When the address input is in multiple vectors.
SEXP C_do_standard_address3(SEXP Line1, SEXP Line2, SEXP Postcode, SEXP KeepStreetName) {
  // error("Not yet implemented.");
  R_xlen_t N = xlength(Postcode);
  verifyEquiStr2(Line1, "Line1", Line2, "Line2");
  if (!isInteger(Postcode)) {
    error("`Postcode` was type '%s' but must be type integer.", type2char(TYPEOF(Postcode)));
  }
  errIfNotLen(Line1, "Line1", N);
  errifNotTF(KeepStreetName, "KeepStreetName");
  const bool keepStreetName = asLogical(KeepStreetName);

  const int * postcode = INTEGER(Postcode);
  const SEXP * x1p = STRING_PTR(Line1);
  // const SEXP * x2p = STRING_PTR(Line2);

  int np = 0;
  // void do_standard_address(const char * x, int n, int numberFirstLast[3], int Street[2], int Postcode[2], int StreetHashes[4])
  SEXP FlatNumber = PROTECT(allocVector(INTSXP, N)); np++;
  SEXP NumberFirst = PROTECT(allocVector(INTSXP, N)); np++;
  SEXP NumberLast  = PROTECT(allocVector(INTSXP, N)); np++;
  SEXP H0 = PROTECT(allocVector(INTSXP, N)); np++;
  SEXP StreetCode = PROTECT(allocVector(INTSXP, N)); np++;
  SEXP NumberSuffix = PROTECT(allocVector(RAWSXP, N)); np++;
  SEXP StreetName = PROTECT(allocVector(STRSXP, keepStreetName ? N : 0)); np++;

  int * restrict flat_numberp = INTEGER(FlatNumber);
  int * restrict number_firstp = INTEGER(NumberFirst);
  int * restrict number_lastp = INTEGER(NumberLast);
  int * restrict h0 = INTEGER(H0);
  int * restrict street_codep = INTEGER(StreetCode);
  unsigned char * restrict number_suffixp = RAW(NumberSuffix);

  unsigned char * M1 = malloc(sizeof(char) * SUP_POSTCODES);
  if (M1 == NULL) {
    error("Internal error(C_do_standard_address3): unable to allocate M1");
  }
  prepare_M1(M1);

  for (R_xlen_t i = 0; i < N; ++i) {
    int postcodei = postcode[i];
    if (postcodei <= 0) {
      continue;
    }
    int n1 = length(x1p[i]);
    if (n1 <= 4) {
      number_firstp[i] = NA_INTEGER;
      number_lastp[i] = NA_INTEGER;
      h0[i] = 0;
      street_codep[i] = NA_INTEGER;
      flat_numberp[i] = NA_INTEGER;
      number_suffixp[i] = 0;
      continue;
    }

    const char * x1pi = CHAR(x1p[i]);


    int J[1] = {0};
    Address ad = get_address_line1(x1pi, n1, J);
    h0[i] = ad.hashStreetName;
    street_codep[i] = ad.street_type;
    flat_numberp[i] = ad.flat_number;
    number_firstp[i] = ad.number_first;
    number_lastp[i] = ad.number_last;
    number_suffixp[i] = ad.suffix;
    if (keepStreetName) {
      int n_char_street_name = n1 - J[0] + 1;
      char SN[n_char_street_name];
      for (int snj = 0; snj < n_char_street_name; ++snj) {
        SN[snj] = x1pi[snj + J[0]];
      }
      SN[n_char_street_name] = '\0';
      SET_STRING_ELT(StreetName, i, mkCharCE((const char *)SN, CE_UTF8));
    }

  }
  SEXP ans = PROTECT(allocVector(VECSXP, keepStreetName ? np : (np - 1))); ++np;
  int li = 0;
  SET_VECTOR_ELT(ans, li, FlatNumber);   ++li;
  SET_VECTOR_ELT(ans, li, NumberFirst);  ++li;
  SET_VECTOR_ELT(ans, li, NumberLast) ;  ++li;
  SET_VECTOR_ELT(ans, li, NumberSuffix); ++li;
  SET_VECTOR_ELT(ans, li, H0);           ++li;
  SET_VECTOR_ELT(ans, li, StreetCode);   ++li;
  if (keepStreetName) {
    SET_VECTOR_ELT(ans, li, StreetName);
  }
  UNPROTECT(np);
  free(M1);
  return ans;
}




SEXP Cget_suffix(SEXP x) {
  if (!isString(x)) {
    return R_NilValue;
  }
  R_xlen_t N = xlength(x);
  const SEXP * xp = STRING_PTR(x);
  SEXP ans = PROTECT(allocVector(RAWSXP, N));
  unsigned char * ansp = RAW(ans);

  for (R_xlen_t i = 0; i < N; ++i) {
    int n = length(xp[i]);
    if (n <= 4) {
      ansp[i] = 0;
      continue;
    }
    const char * x1pi = CHAR(xp[i]);
    ansp[i] = get_suff(x1pi, n);

  }
  UNPROTECT(1);
  return ans;
}

SEXP C_trie_streetType(SEXP x) {
  errIfNotStr(x, "x");
  R_xlen_t N = xlength(x);
  SEXP ans = PROTECT(allocVector(INTSXP, N));
  int * restrict ansp = INTEGER(ans);
  TrieNode * root = getNode();
  if (root == NULL) {
    UNPROTECT(1);
    return R_NilValue;
  }
  for (int i = 0; i < NZ; ++i) {
    insert(root, ZTZ[i]->x, ZTZ[i]->cd);
  }
  const SEXP * xp = STRING_PTR(x);
#pragma omp parallel for
  for (R_xlen_t i = 0; i < N; ++i) {
    ansp[i] = 0;
    const char * xi = CHAR(xp[i]);
    int ni = length(xp[i]);
    uint32_t o = 0;
    int trie_search = search(root, xi);
    if (trie_search != -1) {
      ansp[i] = trie_search;
      continue;
    }
    for (int j = 1; j < ni; ++j) {
      if (xi[j - 1] == ' ' && isUPPER(xi[j])) {
        char buffer[12]; // max nchar of street types
        int k = j + 1;
        while (k < ni && isUPPER(xi[k])) {
          ++k;
        }
        if (k - j < 12) {
          strncpy(buffer, xi + j, k - j);
          buffer[k - j] = '\0';
          trie_search = search(root, buffer);
          if (trie_search != -1) {
            o <<= 8;
            o += trie_search;
          }
        }
        // move to end of word just found
        j = k - 1;
      }
    }
    ansp[i] = o;
  }


  freeTrie(root);
  UNPROTECT(1);
  return ans;
}





