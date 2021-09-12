
#include "healthyAddress.h"
#include "streetcodes.h"

typedef struct {
  int cd;
  const char * x;
  int lenx;
} StreetType;


const StreetType ZT_AV = {ST_CODE_AVENUE, "AV", 2};
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
const StreetType * ZTZ[271] = {
  &ZT_AV, &ZT_CH, &ZT_CL, &ZT_CR, &ZT_CT, &ZT_DR, &ZT_GR, &ZT_LN, &ZT_PL, &ZT_RD,
  &ZT_SQ, &ZT_ST, &ZT_AVE, &ZT_BAY, &ZT_BVD, &ZT_CCT, &ZT_CIR, &ZT_CNR, &ZT_DIP, &ZT_DPS,
  &ZT_DVE, &ZT_END, &ZT_ESP, &ZT_EST, &ZT_GAP, &ZT_GDN, &ZT_GLD, &ZT_GRA, &ZT_GRN, &ZT_GTE,
  &ZT_HUB, &ZT_HWY, &ZT_KEY, &ZT_PDE, &ZT_PNT, &ZT_ROW, &ZT_RTE, &ZT_RTT, &ZT_RUN, &ZT_RVR,
  &ZT_TCE, &ZT_TOP, &ZT_TOR, &ZT_TRK, &ZT_TRL, &ZT_WAY, &ZT_ACCS, &ZT_ACRE, &ZT_BANK,
  &ZT_BEND, &ZT_BLVD, &ZT_BOWL, &ZT_BRAE, &ZT_BROW, &ZT_BVDE, &ZT_COVE, &ZT_CRES, &ZT_CRST, &ZT_DALE,
  &ZT_DASH, &ZT_DELL, &ZT_DENE, &ZT_DOCK, &ZT_DOWN, &ZT_DRWY, &ZT_EAST, &ZT_EDGE, &ZT_FLAT, &ZT_FORD,
  &ZT_FORK, &ZT_GATE, &ZT_GDNS, &ZT_GLEN, &ZT_HIKE, &ZT_HILL, &ZT_KEYS, &ZT_LANE, &ZT_LINE, &ZT_LINK,
  &ZT_LOOP, &ZT_MALL, &ZT_MART, &ZT_MAZE, &ZT_MEAD, &ZT_MEWS, &ZT_MILE, &ZT_NOOK, &ZT_PARK, &ZT_PASS,
  &ZT_PATH, &ZT_PHWY, &ZT_PKWY, &ZT_PORT, &ZT_QUAY, &ZT_RAMP, &ZT_RDGE, &ZT_RDWY, &ZT_REST, &ZT_RIDE,
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



/*
 static const unsigned char letters[26] =
 {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
 */

typedef struct {
  int n_words;
  int lhs[WORD_DATUMS];
  int rhs[WORD_DATUMS];
} WordData;


static const char LETTERS[26] =
  {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
   'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

static char toupper1(char x) {
  unsigned int xi = x - 'a';
  return (xi < 26) ? LETTERS[xi] : x;
}

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
//'
//' Assumptions:
//'   x consists of uppercase char and breakers only.
//'
//'
//' @param ans
void word_data(WordData * wd, const char * x, int n, int j0) {
  int N_WORDS[2] = {0};
  for (int w_j = 0; w_j < WORD_DATUMS; ++w_j) {
    wd->lhs[w_j] = 0;
    wd->rhs[w_j] = 0;
  }
  Rprintf("..");
  wd->n_words = WORD_DATUMS;
  Rprintf("|");

  // ensure we're at the start of a word
  while (j0 < n && x[j0] == ' ') {
    ++j0;
  }
  int w = 0;

  for (int j = j0; j < n; ++j) {
    unsigned char xj = x[j];
    bool is_breaker = xj == ' ' || xj == ',';
    N_WORDS[1] = j + 1;
    if (is_breaker) {
      N_WORDS[w] += 1;
      wd->rhs[w] = j;
      ++w;
      if (w >= WORD_DATUMS) {
        return;
      }
      ++j;
      wd->lhs[w] = j;
      while (++j < n && (x[j] == ' ' || x[j] == ',')) {
        wd->lhs[w] = j;
      }
    }
  }
  Rprintf("W");
  wd->n_words = N_WORDS[0];
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

bool char_is_number(char x) {
  unsigned int xi = x - '0';
  return xi <= 9U;
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


int next_nonnumber(const char * x, int from) {
  while (char_is_number(x[from])) {
    ++from;
  }
  return from;
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

bool has_postcode(const char * x, int n) {
  if (n < 4) {
    return 0;
  }
  int k = n - 4;
  return
    char_is_number(x[k]) &&
      char_is_number(x[k + 1]) &&
      char_is_number(x[k + 2]) &&
      char_is_number(x[k + 3]);
}

bool has_postcode_from(const char * x, int k) {
  return
  char_is_number(x[k]) &&
    char_is_number(x[k + 1]) &&
    char_is_number(x[k + 2]) &&
    char_is_number(x[k + 3]);
}


int xpostcode_unsafe(const char * x, int n) {
  // unsafe = don't check that length is sufficient
  int o = 0;
  const int ten4s[4] = {1000, 100, 10, 1};
  const int n4 = n - 4;
  for (int d = 0; d < 4; ++d) {
    char xj = x[n4 + d];
    if (isdigit(xj)) {
      o += ten4s[d] * (xj - '0');
    }
  }
  return o;
}



int n_spaces(const char * x, int n) {
  int o = 0;
  for (int i = 0; i < n; ++i) {
    o += x[i] == ' ';
  }
  return o;
}

bool has_ste_postcode(const char * x, int n) {
  // <STE> <nnnn>
  // location of space before
  if (n < 4 + 1 + 3) {
    return false;
  }
  // n - 8
  if (x[n - 8] == ' ') {
    // two char
    return ste_as_int(x, n - 7) && has_postcode(x, n);
  }
  return ste_as_int(x, n - 8) && has_postcode(x, n);
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




SEXP CPoaHasSt(SEXP Poa, SEXP Type) {
  R_xlen_t N = xlength(Poa);
  if (TYPEOF(Poa) != INTSXP || xlength(Type) != N) {
    return R_NilValue;
  }
  if (TYPEOF(Type) != INTSXP) {
    if (TYPEOF(Type) != STRSXP) {
      return R_NilValue;
    }
    return R_NilValue;
  }


  if (N != xlength(Type)) {
    return R_NilValue;
  }
  const int * poap = INTEGER(Poa);
  const int * typep = INTEGER(Type);
  SEXP ans = PROTECT(allocVector(INTSXP, N));
  int * restrict ansp = INTEGER(ans);
  for (R_xlen_t i = 0; i < N; ++i) {
    ansp[i] = poa_has_street_type(poap[i], typep[i]);
  }
  UNPROTECT(1);
  return ans;
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
// #pragma omp parallel for
  for (R_xlen_t i = 0; i < N; ++i) {
    int n = length(xpp[i]);
    if (n < 4) {
      ansp[i] = NA_INTEGER;
      continue;
    }
    const char * xp = CHAR(xpp[i]);
    ansp[i] = xpostcode_unsafe(xp, n);
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
  switch(x[0]) {
  case 'U':
    j = (x[1] == 'N' && x[2] == 'I' && x[3] == 'T') ? 4 : 1;
    break;
  case 'G':
    j = 1;
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
      }
      return;
    }
  }
  while (j < n && x[j] == ' ') {
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
  int i = n - 1;
  while (i >= 0 && x[i] != ',') {
    --i;
  }
  return i;
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
    xi /= 256u;
    xi /= 256u;
    xi /= 256u;
    xi &= 255u;
    ansp[i] = xi;
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
        if (i == 0) {
          Rprintf("(%d,%d)\n", si1, si2);
          continue;
        }
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

      const char * x = CHAR(CX);
      char oy[si1 - si2 + 1];
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

int street_type(const char * x, int n, int j, WordData * wd, int Postcode) {
  if (Postcode <= 0) {
    return NA_INTEGER;
  }
  int n_words = wd->n_words;
  const int W_ORD[WORD_DATUMS] = { 3,  4,  5,  2,  6, 0, 1, 7,
                                   11, 12, 13, 10, 14, 8, 9, 15};
  for (int w_ = 0; w_ < 16; ++w_) {
    int w = W_ORD[w_];
    if (w > n_words) {
      continue;
    }
    int lhs_w = wd->lhs[w];
    int rhs_w = wd->rhs[w];
    int width_w = rhs_w - lhs_w;
    if (width_w == 2) {
      char x_w0 = x[lhs_w];
      char x_w1 = x[lhs_w + 1];
      for (int z = 0; z < 12; ++z) {
        const StreetType * Z = ZTZ[z];
        const char * xz = Z->x;
        int nz = Z->lenx;
        if (nz == 2) {
          if (x_w0 == xz[0] && x_w1 == xz[1]) {
            return Z->cd;
          }
        }
      }
    }
  }
  return 0;
}

void do_standard_address(const char * x, int n, int numberFirstLast[3], int Street[2], int Postcode[2], int StreetHashes[4]) {
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

  while (j < n && x[j] == ' ') {
    ++j;
  }
  WordData wd = { .n_words = 0, .lhs[0] = 0, .rhs[0] = 0};
  // int j_StreetName = j;

  // Give the hashes of the next 1,2,3,4 words
  // idea is the street name may be more than one name
  unsigned int Hashes[4] = {5381, 5381, 5381, 5381};
  int n_hashes_complete = 0;
  unsigned int hash = 5381;
  for (int k = j; k < n; ++k) {
    if (n_hashes_complete >= 4) {
      break;
    }
    Hashes[n_hashes_complete] = hash;
    unsigned char xk = x[k];
    if (!isupper(xk)) {
      if (xk == ',') {
        break;
      }
      n_hashes_complete++;
    }
    hash = ((hash << 5) + hash) ^ xk;
  }
  for (int h = 0; h < 4; ++h) {
    StreetHashes[h] = Hashes[h];
  }

  // now identify the street type
  // must be after the street name (by assumption)
  int postcode = xpostcode_unsafe(x, n);
  Street[1] = street_type(x, n, j, &wd, postcode);

  numberFirstLast[0] = flat_number2i[1];
  numberFirstLast[1] = o1;
  numberFirstLast[2] = o2;
  Postcode[0] = postcode;
}

SEXP C_do_standard_address(SEXP xx) {
  R_xlen_t N = xlength(xx);
  const SEXP * xp = STRING_PTR(xx);
  int np = 0;
  // void do_standard_address(const char * x, int n, int numberFirstLast[3], int Street[2], int Postcode[2], int StreetHashes[4])
  SEXP FlatNumber = PROTECT(allocVector(INTSXP, N)); np++;
  SEXP NumberFirst = PROTECT(allocVector(INTSXP, N)); np++;
  SEXP NumberLast  = PROTECT(allocVector(INTSXP, N)); np++;
  SEXP H0 = PROTECT(allocVector(INTSXP, N)); np++;
  SEXP H1 = PROTECT(allocVector(INTSXP, N)); np++;
  SEXP H2 = PROTECT(allocVector(INTSXP, N)); np++;
  SEXP H3 = PROTECT(allocVector(INTSXP, N)); np++;
  SEXP StreetCode = PROTECT(allocVector(INTSXP, N)); np++;
  SEXP Postcode = PROTECT(allocVector(INTSXP, N)); np++;

  int * restrict flat_numberp = INTEGER(FlatNumber);
  int * restrict number_firstp = INTEGER(NumberFirst);
  int * restrict number_lastp = INTEGER(NumberLast);
  int * restrict h0 = INTEGER(H0);
  int * restrict h1 = INTEGER(H1);
  int * restrict h2 = INTEGER(H2);
  int * restrict h3 = INTEGER(H3);
  int * restrict street_codep = INTEGER(StreetCode);
  int * restrict pp = INTEGER(Postcode);

  for (R_xlen_t i = 0; i < N; ++i) {
    int n = length(xp[i]);
    int numberFirstLast[3] = {0};
    int street[2] = {0};
    int postcode[2] = {0};
    int streetHashes[4] = {0};
    if (n <= 4) {
      pp[i] = NA_INTEGER;
      number_firstp[i] = NA_INTEGER;
      number_lastp[i] = NA_INTEGER;
      h0[i] = streetHashes[0];
      h1[i] = streetHashes[1];
      h2[i] = streetHashes[2];
      h3[i] = streetHashes[3];
      street_codep[i] = NA_INTEGER;
      flat_numberp[i] = NA_INTEGER;
      continue;
    }
    const char * x = CHAR(xp[i]);

    do_standard_address(x, n, numberFirstLast, street, postcode, streetHashes);
    h0[i] = streetHashes[0];
    h1[i] = streetHashes[1];
    h2[i] = streetHashes[2];
    h3[i] = streetHashes[3];
    pp[i] = postcode[0];
    street_codep[i] = street[1];
    flat_numberp[i] = numberFirstLast[0];
    number_firstp[i] = numberFirstLast[1];
    number_lastp[i] = numberFirstLast[2];
    //if (!(i & 255)) Rprintf("\n");
  }
  SEXP ans = PROTECT(allocVector(VECSXP, np)); ++np;
  SET_VECTOR_ELT(ans, 0, NumberFirst);
  SET_VECTOR_ELT(ans, 1, NumberLast) ;
  SET_VECTOR_ELT(ans, 2, H0);
  SET_VECTOR_ELT(ans, 3, H1);
  SET_VECTOR_ELT(ans, 4, H2);
  SET_VECTOR_ELT(ans, 5, H3);
  SET_VECTOR_ELT(ans, 6, Postcode);
  SET_VECTOR_ELT(ans, 7, FlatNumber);
  SET_VECTOR_ELT(ans, 8, StreetCode);
  UNPROTECT(np);
  return ans;

}



