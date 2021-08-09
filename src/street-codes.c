#include "healthyAddress.h"

SEXP CStreetCd2Str(SEXP x) {
	R_xlen_t N = xlength(x);
	const int * xp = INTEGER(x);
	SEXP ans = PROTECT(allocVector(STRSXP, N));
	for (R_xlen_t i = 0; i < N; ++i) {
		int xpi = xp[i];
	  if (xpi <= 0 || xpi > 224) {
	    SET_STRING_ELT(ans, i, NA_STRING);
	    continue;
	  }
		switch(xpi) {
			case 1:
			SET_STRING_ELT(ans, i, mkChar("ROAD"));
			break;
			case 2:
			SET_STRING_ELT(ans, i, mkChar("STREET"));
			break;
			case 3:
			SET_STRING_ELT(ans, i, mkChar("COURT"));
			break;
			case 4:
			SET_STRING_ELT(ans, i, mkChar("AVENUE"));
			break;
			case 5:
			SET_STRING_ELT(ans, i, mkChar("PLACE"));
			break;
			case 6:
			SET_STRING_ELT(ans, i, mkChar("LANE"));
			break;
			case 7:
			SET_STRING_ELT(ans, i, mkChar("DRIVE"));
			break;
			case 8:
			SET_STRING_ELT(ans, i, mkChar("CLOSE"));
			break;
			case 9:
			SET_STRING_ELT(ans, i, mkChar("TRACK"));
			break;
			case 10:
			SET_STRING_ELT(ans, i, mkChar("CRESCENT"));
			break;
			case 11:
			SET_STRING_ELT(ans, i, mkChar("WAY"));
			break;
			case 12:
			SET_STRING_ELT(ans, i, mkChar("TRAIL"));
			break;
			case 13:
			SET_STRING_ELT(ans, i, mkChar("HIGHWAY"));
			break;
			case 14:
			SET_STRING_ELT(ans, i, mkChar("TERRACE"));
			break;
			case 15:
			SET_STRING_ELT(ans, i, mkChar("PARADE"));
			break;
			case 16:
			SET_STRING_ELT(ans, i, mkChar("GROVE"));
			break;
			case 17:
			SET_STRING_ELT(ans, i, mkChar("ACCESS"));
			break;
			case 18:
			SET_STRING_ELT(ans, i, mkChar("CIRCUIT"));
			break;
			case 19:
			SET_STRING_ELT(ans, i, mkChar("RAMP"));
			break;
			case 20:
			SET_STRING_ELT(ans, i, mkChar("BOULEVARD"));
			break;
			case 21:
			SET_STRING_ELT(ans, i, mkChar("WALK"));
			break;
			case 22:
			SET_STRING_ELT(ans, i, mkChar("RISE"));
			break;
			case 23:
			SET_STRING_ELT(ans, i, mkChar("FIRETRAIL"));
			break;
			case 24:
			SET_STRING_ELT(ans, i, mkChar("BREAK"));
			break;
			case 25:
			SET_STRING_ELT(ans, i, mkChar("LOOP"));
			break;
			case 26:
			SET_STRING_ELT(ans, i, mkChar("MEWS"));
			break;
			case 27:
			SET_STRING_ELT(ans, i, mkChar("LINK"));
			break;
			case 28:
			SET_STRING_ELT(ans, i, mkChar("GARDENS"));
			break;
			case 29:
			SET_STRING_ELT(ans, i, mkChar("CIRCLE"));
			break;
			case 30:
			SET_STRING_ELT(ans, i, mkChar("PARKWAY"));
			break;
			case 31:
			SET_STRING_ELT(ans, i, mkChar("FREEWAY"));
			break;
			case 32:
			SET_STRING_ELT(ans, i, mkChar("VIEW"));
			break;
			case 33:
			SET_STRING_ELT(ans, i, mkChar("RETREAT"));
			break;
			case 34:
			SET_STRING_ELT(ans, i, mkChar("COVE"));
			break;
			case 35:
			SET_STRING_ELT(ans, i, mkChar("ESPLANADE"));
			break;
			case 36:
			SET_STRING_ELT(ans, i, mkChar("SQUARE"));
			break;
			case 37:
			SET_STRING_ELT(ans, i, mkChar("PASS"));
			break;
			case 38:
			SET_STRING_ELT(ans, i, mkChar("MOTORWAY"));
			break;
			case 39:
			SET_STRING_ELT(ans, i, mkChar("PATHWAY"));
			break;
			case 40:
			SET_STRING_ELT(ans, i, mkChar("VISTA"));
			break;
			case 41:
			SET_STRING_ELT(ans, i, mkChar("TURN"));
			break;
			case 42:
			SET_STRING_ELT(ans, i, mkChar("BEND"));
			break;
			case 43:
			SET_STRING_ELT(ans, i, mkChar("CHASE"));
			break;
			case 44:
			SET_STRING_ELT(ans, i, mkChar("GREEN"));
			break;
			case 45:
			SET_STRING_ELT(ans, i, mkChar("ENTRANCE"));
			break;
			case 46:
			SET_STRING_ELT(ans, i, mkChar("HEIGHTS"));
			break;
			case 47:
			SET_STRING_ELT(ans, i, mkChar("GLEN"));
			break;
			case 48:
			SET_STRING_ELT(ans, i, mkChar("PROMENADE"));
			break;
			case 49:
			SET_STRING_ELT(ans, i, mkChar("ROW"));
			break;
			case 50:
			SET_STRING_ELT(ans, i, mkChar("RIDGE"));
			break;
			case 51:
			SET_STRING_ELT(ans, i, mkChar("FIREBREAK"));
			break;
			case 52:
			SET_STRING_ELT(ans, i, mkChar("GLADE"));
			break;
			case 53:
			SET_STRING_ELT(ans, i, mkChar("APPROACH"));
			break;
			case 54:
			SET_STRING_ELT(ans, i, mkChar("PATH"));
			break;
			case 55:
			SET_STRING_ELT(ans, i, mkChar("RUN"));
			break;
			case 56:
			SET_STRING_ELT(ans, i, mkChar("BYPASS"));
			break;
			case 57:
			SET_STRING_ELT(ans, i, mkChar("ALLEY"));
			break;
			case 58:
			SET_STRING_ELT(ans, i, mkChar("ARCADE"));
			break;
			case 59:
			SET_STRING_ELT(ans, i, mkChar("ELBOW"));
			break;
			case 60:
			SET_STRING_ELT(ans, i, mkChar("BRACE"));
			break;
			case 61:
			SET_STRING_ELT(ans, i, mkChar("CORNER"));
			break;
			case 62:
			SET_STRING_ELT(ans, i, mkChar("ROUTE"));
			break;
			case 63:
			SET_STRING_ELT(ans, i, mkChar("RAMBLE"));
			break;
			case 64:
			SET_STRING_ELT(ans, i, mkChar("FIRELINE"));
			break;
			case 65:
			SET_STRING_ELT(ans, i, mkChar("CROSSING"));
			break;
			case 66:
			SET_STRING_ELT(ans, i, mkChar("GATE"));
			break;
			case 67:
			SET_STRING_ELT(ans, i, mkChar("GRANGE"));
			break;
			case 68:
			SET_STRING_ELT(ans, i, mkChar("FAIRWAY"));
			break;
			case 69:
			SET_STRING_ELT(ans, i, mkChar("LOOKOUT"));
			break;
			case 70:
			SET_STRING_ELT(ans, i, mkChar("POINT"));
			break;
			case 71:
			SET_STRING_ELT(ans, i, mkChar("HILL"));
			break;
			case 72:
			SET_STRING_ELT(ans, i, mkChar("CREST"));
			break;
			case 73:
			SET_STRING_ELT(ans, i, mkChar("LANEWAY"));
			break;
			case 74:
			SET_STRING_ELT(ans, i, mkChar("EXPRESSWAY"));
			break;
			case 75:
			SET_STRING_ELT(ans, i, mkChar("LINE"));
			break;
			case 76:
			SET_STRING_ELT(ans, i, mkChar("MALL"));
			break;
			case 77:
			SET_STRING_ELT(ans, i, mkChar("MEANDER"));
			break;
			case 78:
			SET_STRING_ELT(ans, i, mkChar("OUTLOOK"));
			break;
			case 79:
			SET_STRING_ELT(ans, i, mkChar("BAY"));
			break;
			case 80:
			SET_STRING_ELT(ans, i, mkChar("CROSS"));
			break;
			case 81:
			SET_STRING_ELT(ans, i, mkChar("WALKWAY"));
			break;
			case 82:
			SET_STRING_ELT(ans, i, mkChar("FIRETRACK"));
			break;
			case 83:
			SET_STRING_ELT(ans, i, mkChar("BRIDGE"));
			break;
			case 84:
			SET_STRING_ELT(ans, i, mkChar("PARK"));
			break;
			case 85:
			SET_STRING_ELT(ans, i, mkChar("PLAZA"));
			break;
			case 86:
			SET_STRING_ELT(ans, i, mkChar("NOOK"));
			break;
			case 87:
			SET_STRING_ELT(ans, i, mkChar("WYND"));
			break;
			case 88:
			SET_STRING_ELT(ans, i, mkChar("VALE"));
			break;
			case 89:
			SET_STRING_ELT(ans, i, mkChar("DOWNS"));
			break;
			case 90:
			SET_STRING_ELT(ans, i, mkChar("SPUR"));
			break;
			case 91:
			SET_STRING_ELT(ans, i, mkChar("BUSWAY"));
			break;
			case 92:
			SET_STRING_ELT(ans, i, mkChar("CIRCUS"));
			break;
			case 93:
			SET_STRING_ELT(ans, i, mkChar("POCKET"));
			break;
			case 94:
			SET_STRING_ELT(ans, i, mkChar("BOARDWALK"));
			break;
			case 95:
			SET_STRING_ELT(ans, i, mkChar("CONCOURSE"));
			break;
			case 96:
			SET_STRING_ELT(ans, i, mkChar("RIVER"));
			break;
			case 97:
			SET_STRING_ELT(ans, i, mkChar("QUAYS"));
			break;
			case 98:
			SET_STRING_ELT(ans, i, mkChar("RESERVE"));
			break;
			case 99:
			SET_STRING_ELT(ans, i, mkChar("DALE"));
			break;
			case 100:
			SET_STRING_ELT(ans, i, mkChar("ISLAND"));
			break;
			case 101:
			SET_STRING_ELT(ans, i, mkChar("REST"));
			break;
			case 102:
			SET_STRING_ELT(ans, i, mkChar("CONNECTION"));
			break;
			case 103:
			SET_STRING_ELT(ans, i, mkChar("END"));
			break;
			case 104:
			SET_STRING_ELT(ans, i, mkChar("QUAY"));
			break;
			case 105:
			SET_STRING_ELT(ans, i, mkChar("VIEWS"));
			break;
			case 106:
			SET_STRING_ELT(ans, i, mkChar("KEY"));
			break;
			case 107:
			SET_STRING_ELT(ans, i, mkChar("TRAVERSE"));
			break;
			case 108:
			SET_STRING_ELT(ans, i, mkChar("BOULEVARDE"));
			break;
			case 109:
			SET_STRING_ELT(ans, i, mkChar("FORMATION"));
			break;
			case 110:
			SET_STRING_ELT(ans, i, mkChar("OUTLET"));
			break;
			case 111:
			SET_STRING_ELT(ans, i, mkChar("DRIVEWAY"));
			break;
			case 112:
			SET_STRING_ELT(ans, i, mkChar("LANDING"));
			break;
			case 113:
			SET_STRING_ELT(ans, i, mkChar("EDGE"));
			break;
			case 114:
			SET_STRING_ELT(ans, i, mkChar("QUADRANT"));
			break;
			case 115:
			SET_STRING_ELT(ans, i, mkChar("VALLEY"));
			break;
			case 116:
			SET_STRING_ELT(ans, i, mkChar("WATERS"));
			break;
			case 117:
			SET_STRING_ELT(ans, i, mkChar("CAUSEWAY"));
			break;
			case 118:
			SET_STRING_ELT(ans, i, mkChar("BEACH"));
			break;
			case 119:
			SET_STRING_ELT(ans, i, mkChar("SERVICEWAY"));
			break;
			case 120:
			SET_STRING_ELT(ans, i, mkChar("CENTRE"));
			break;
			case 121:
			SET_STRING_ELT(ans, i, mkChar("EASEMENT"));
			break;
			case 122:
			SET_STRING_ELT(ans, i, mkChar("PASSAGE"));
			break;
			case 123:
			SET_STRING_ELT(ans, i, mkChar("STRIP"));
			break;
			case 124:
			SET_STRING_ELT(ans, i, mkChar("TARN"));
			break;
			case 125:
			SET_STRING_ELT(ans, i, mkChar("BRAE"));
			break;
			case 126:
			SET_STRING_ELT(ans, i, mkChar("DEVIATION"));
			break;
			case 127:
			SET_STRING_ELT(ans, i, mkChar("JUNCTION"));
			break;
			case 128:
			SET_STRING_ELT(ans, i, mkChar("STEPS"));
			break;
			case 129:
			SET_STRING_ELT(ans, i, mkChar("WHARF"));
			break;
			case 130:
			SET_STRING_ELT(ans, i, mkChar("BOWL"));
			break;
			case 131:
			SET_STRING_ELT(ans, i, mkChar("COURSE"));
			break;
			case 132:
			SET_STRING_ELT(ans, i, mkChar("GAP"));
			break;
			case 133:
			SET_STRING_ELT(ans, i, mkChar("GULLY"));
			break;
			case 134:
			SET_STRING_ELT(ans, i, mkChar("TUNNEL"));
			break;
			case 135:
			SET_STRING_ELT(ans, i, mkChar("CUTTING"));
			break;
			case 136:
			SET_STRING_ELT(ans, i, mkChar("ESTATE"));
			break;
			case 137:
			SET_STRING_ELT(ans, i, mkChar("EXTENSION"));
			break;
			case 138:
			SET_STRING_ELT(ans, i, mkChar("FORESHORE"));
			break;
			case 139:
			SET_STRING_ELT(ans, i, mkChar("GATEWAY"));
			break;
			case 140:
			SET_STRING_ELT(ans, i, mkChar("HAVEN"));
			break;
			case 141:
			SET_STRING_ELT(ans, i, mkChar("ROTARY"));
			break;
			case 142:
			SET_STRING_ELT(ans, i, mkChar("COMMON"));
			break;
			case 143:
			SET_STRING_ELT(ans, i, mkChar("COPSE"));
			break;
			case 144:
			SET_STRING_ELT(ans, i, mkChar("DISTRIBUTOR"));
			break;
			case 145:
			SET_STRING_ELT(ans, i, mkChar("FOLLOW"));
			break;
			case 146:
			SET_STRING_ELT(ans, i, mkChar("FRONTAGE"));
			break;
			case 147:
			SET_STRING_ELT(ans, i, mkChar("TOR"));
			break;
			case 148:
			SET_STRING_ELT(ans, i, mkChar("ARTERIAL"));
			break;
			case 149:
			SET_STRING_ELT(ans, i, mkChar("BANK"));
			break;
			case 150:
			SET_STRING_ELT(ans, i, mkChar("NORTH"));
			break;
			case 151:
			SET_STRING_ELT(ans, i, mkChar("ROADS"));
			break;
			case 152:
			SET_STRING_ELT(ans, i, mkChar("UNDERPASS"));
			break;
			case 153:
			SET_STRING_ELT(ans, i, mkChar("BROW"));
			break;
			case 154:
			SET_STRING_ELT(ans, i, mkChar("HEATH"));
			break;
			case 155:
			SET_STRING_ELT(ans, i, mkChar("LADDER"));
			break;
			case 156:
			SET_STRING_ELT(ans, i, mkChar("PRECINCT"));
			break;
			case 157:
			SET_STRING_ELT(ans, i, mkChar("RANGE"));
			break;
			case 158:
			SET_STRING_ELT(ans, i, mkChar("SOUTH"));
			break;
			case 159:
			SET_STRING_ELT(ans, i, mkChar("TRUNKWAY"));
			break;
			case 160:
			SET_STRING_ELT(ans, i, mkChar("AMBLE"));
			break;
			case 161:
			SET_STRING_ELT(ans, i, mkChar("BANAN"));
			break;
			case 162:
			SET_STRING_ELT(ans, i, mkChar("BRANCH"));
			break;
			case 163:
			SET_STRING_ELT(ans, i, mkChar("CORSO"));
			break;
			case 164:
			SET_STRING_ELT(ans, i, mkChar("DIVIDE"));
			break;
			case 165:
			SET_STRING_ELT(ans, i, mkChar("DOCK"));
			break;
			case 166:
			SET_STRING_ELT(ans, i, mkChar("FORD"));
			break;
			case 167:
			SET_STRING_ELT(ans, i, mkChar("FORK"));
			break;
			case 168:
			SET_STRING_ELT(ans, i, mkChar("GARDEN"));
			break;
			case 169:
			SET_STRING_ELT(ans, i, mkChar("HIKE"));
			break;
			case 170:
			SET_STRING_ELT(ans, i, mkChar("HOLLOW"));
			break;
			case 171:
			SET_STRING_ELT(ans, i, mkChar("INTERCHANGE"));
			break;
			case 172:
			SET_STRING_ELT(ans, i, mkChar("PALMS"));
			break;
			case 173:
			SET_STRING_ELT(ans, i, mkChar("RIDE"));
			break;
			case 174:
			SET_STRING_ELT(ans, i, mkChar("ROUND"));
			break;
			case 175:
			SET_STRING_ELT(ans, i, mkChar("SLOPE"));
			break;
			case 176:
			SET_STRING_ELT(ans, i, mkChar("STRAIT"));
			break;
			case 177:
			SET_STRING_ELT(ans, i, mkChar("SUBWAY"));
			break;
			case 178:
			SET_STRING_ELT(ans, i, mkChar("TOP"));
			break;
			case 179:
			SET_STRING_ELT(ans, i, mkChar("TRAMWAY"));
			break;
			case 180:
			SET_STRING_ELT(ans, i, mkChar("BROADWAY"));
			break;
			case 181:
			SET_STRING_ELT(ans, i, mkChar("CLUSTER"));
			break;
			case 182:
			SET_STRING_ELT(ans, i, mkChar("DELL"));
			break;
			case 183:
			SET_STRING_ELT(ans, i, mkChar("DOMAIN"));
			break;
			case 184:
			SET_STRING_ELT(ans, i, mkChar("FLAT"));
			break;
			case 185:
			SET_STRING_ELT(ans, i, mkChar("HUB"));
			break;
			case 186:
			SET_STRING_ELT(ans, i, mkChar("LYNNE"));
			break;
			case 187:
			SET_STRING_ELT(ans, i, mkChar("MEAD"));
			break;
			case 188:
			SET_STRING_ELT(ans, i, mkChar("MILE"));
			break;
			case 189:
			SET_STRING_ELT(ans, i, mkChar("PORT"));
			break;
			case 190:
			SET_STRING_ELT(ans, i, mkChar("REACH"));
			break;
			case 191:
			SET_STRING_ELT(ans, i, mkChar("RETURN"));
			break;
			case 192:
			SET_STRING_ELT(ans, i, mkChar("STRAIGHT"));
			break;
			case 193:
			SET_STRING_ELT(ans, i, mkChar("VILLAGE"));
			break;
			case 194:
			SET_STRING_ELT(ans, i, mkChar("WEST"));
			break;
			case 195:
			SET_STRING_ELT(ans, i, mkChar("WOODS"));
			break;
			case 196:
			SET_STRING_ELT(ans, i, mkChar("ACRE"));
			break;
			case 197:
			SET_STRING_ELT(ans, i, mkChar("BYWAY"));
			break;
			case 198:
			SET_STRING_ELT(ans, i, mkChar("CENTREWAY"));
			break;
			case 199:
			SET_STRING_ELT(ans, i, mkChar("COMMONS"));
			break;
			case 200:
			SET_STRING_ELT(ans, i, mkChar("CONCORD"));
			break;
			case 201:
			SET_STRING_ELT(ans, i, mkChar("COURTYARD"));
			break;
			case 202:
			SET_STRING_ELT(ans, i, mkChar("CRIEF"));
			break;
			case 203:
			SET_STRING_ELT(ans, i, mkChar("CRUISEWAY"));
			break;
			case 204:
			SET_STRING_ELT(ans, i, mkChar("CUL-DE-SAC"));
			break;
			case 205:
			SET_STRING_ELT(ans, i, mkChar("DASH"));
			break;
			case 206:
			SET_STRING_ELT(ans, i, mkChar("DENE"));
			break;
			case 207:
			SET_STRING_ELT(ans, i, mkChar("DIP"));
			break;
			case 208:
			SET_STRING_ELT(ans, i, mkChar("DOWN"));
			break;
			case 209:
			SET_STRING_ELT(ans, i, mkChar("EAST"));
			break;
			case 210:
			SET_STRING_ELT(ans, i, mkChar("FLATS"));
			break;
			case 211:
			SET_STRING_ELT(ans, i, mkChar("HARBOUR"));
			break;
			case 212:
			SET_STRING_ELT(ans, i, mkChar("HILLS"));
			break;
			case 213:
			SET_STRING_ELT(ans, i, mkChar("KEYS"));
			break;
			case 214:
			SET_STRING_ELT(ans, i, mkChar("MANOR"));
			break;
			case 215:
			SET_STRING_ELT(ans, i, mkChar("MART"));
			break;
			case 216:
			SET_STRING_ELT(ans, i, mkChar("MAZE"));
			break;
			case 217:
			SET_STRING_ELT(ans, i, mkChar("PURSUIT"));
			break;
			case 218:
			SET_STRING_ELT(ans, i, mkChar("RISING"));
			break;
			case 219:
			SET_STRING_ELT(ans, i, mkChar("ROADWAY"));
			break;
			case 220:
			SET_STRING_ELT(ans, i, mkChar("THROUGHWAY"));
			break;
			case 221:
			SET_STRING_ELT(ans, i, mkChar("TWIST"));
			break;
			case 222:
			SET_STRING_ELT(ans, i, mkChar("VILLA"));
			break;
			case 223:
			SET_STRING_ELT(ans, i, mkChar("WATERWAY"));
			break;
			case 224:
			SET_STRING_ELT(ans, i, mkChar("YARD"));
			break;
		}
	}
	UNPROTECT(1);
	return ans;
}

int which_street_code(const char * x, int n) {

  if (string_equal(x, n, "ROAD", 4)) {
    return ST_CODE_ROAD;
  }
  if (string_equal(x, n, "STREET", 6)) {
    return ST_CODE_STREET;
  }
  if (string_equal(x, n, "COURT", 5)) {
    return ST_CODE_COURT;
  }
  if (string_equal(x, n, "AVENUE", 6)) {
    return ST_CODE_AVENUE;
  }
  if (string_equal(x, n, "PLACE", 5)) {
    return ST_CODE_PLACE;
  }
  if (string_equal(x, n, "LANE", 4)) {
    return ST_CODE_LANE;
  }
  if (string_equal(x, n, "DRIVE", 5)) {
    return ST_CODE_DRIVE;
  }
  if (string_equal(x, n, "CLOSE", 5)) {
    return ST_CODE_CLOSE;
  }
  if (string_equal(x, n, "TRACK", 5)) {
    return ST_CODE_TRACK;
  }
  if (string_equal(x, n, "CRESCENT", 8)) {
    return ST_CODE_CRESCENT;
  }
  if (string_equal(x, n, "WAY", 3)) {
    return ST_CODE_WAY;
  }
  if (string_equal(x, n, "TRAIL", 5)) {
    return ST_CODE_TRAIL;
  }
  if (string_equal(x, n, "HIGHWAY", 7)) {
    return ST_CODE_HIGHWAY;
  }
  if (string_equal(x, n, "TERRACE", 7)) {
    return ST_CODE_TERRACE;
  }
  if (string_equal(x, n, "PARADE", 6)) {
    return ST_CODE_PARADE;
  }
  if (string_equal(x, n, "GROVE", 5)) {
    return ST_CODE_GROVE;
  }
  if (string_equal(x, n, "ACCESS", 6)) {
    return ST_CODE_ACCESS;
  }
  if (string_equal(x, n, "CIRCUIT", 7)) {
    return ST_CODE_CIRCUIT;
  }
  if (string_equal(x, n, "RAMP", 4)) {
    return ST_CODE_RAMP;
  }
  if (string_equal(x, n, "BOULEVARD", 9)) {
    return ST_CODE_BOULEVARD;
  }
  if (string_equal(x, n, "WALK", 4)) {
    return ST_CODE_WALK;
  }
  if (string_equal(x, n, "RISE", 4)) {
    return ST_CODE_RISE;
  }
  if (string_equal(x, n, "FIRETRAIL", 9)) {
    return ST_CODE_FIRETRAIL;
  }
  if (string_equal(x, n, "BREAK", 5)) {
    return ST_CODE_BREAK;
  }
  if (string_equal(x, n, "LOOP", 4)) {
    return ST_CODE_LOOP;
  }
  if (string_equal(x, n, "MEWS", 4)) {
    return ST_CODE_MEWS;
  }
  if (string_equal(x, n, "LINK", 4)) {
    return ST_CODE_LINK;
  }
  if (string_equal(x, n, "GARDENS", 7)) {
    return ST_CODE_GARDENS;
  }
  if (string_equal(x, n, "CIRCLE", 6)) {
    return ST_CODE_CIRCLE;
  }
  if (string_equal(x, n, "PARKWAY", 7)) {
    return ST_CODE_PARKWAY;
  }
  if (string_equal(x, n, "FREEWAY", 7)) {
    return ST_CODE_FREEWAY;
  }
  if (string_equal(x, n, "VIEW", 4)) {
    return ST_CODE_VIEW;
  }
  if (string_equal(x, n, "RETREAT", 7)) {
    return ST_CODE_RETREAT;
  }
  if (string_equal(x, n, "COVE", 4)) {
    return ST_CODE_COVE;
  }
  if (string_equal(x, n, "ESPLANADE", 9)) {
    return ST_CODE_ESPLANADE;
  }
  if (string_equal(x, n, "SQUARE", 6)) {
    return ST_CODE_SQUARE;
  }
  if (string_equal(x, n, "PASS", 4)) {
    return ST_CODE_PASS;
  }
  if (string_equal(x, n, "MOTORWAY", 8)) {
    return ST_CODE_MOTORWAY;
  }
  if (string_equal(x, n, "PATHWAY", 7)) {
    return ST_CODE_PATHWAY;
  }
  if (string_equal(x, n, "VISTA", 5)) {
    return ST_CODE_VISTA;
  }
  if (string_equal(x, n, "TURN", 4)) {
    return ST_CODE_TURN;
  }
  if (string_equal(x, n, "BEND", 4)) {
    return ST_CODE_BEND;
  }
  if (string_equal(x, n, "CHASE", 5)) {
    return ST_CODE_CHASE;
  }
  if (string_equal(x, n, "GREEN", 5)) {
    return ST_CODE_GREEN;
  }
  if (string_equal(x, n, "ENTRANCE", 8)) {
    return ST_CODE_ENTRANCE;
  }
  if (string_equal(x, n, "HEIGHTS", 7)) {
    return ST_CODE_HEIGHTS;
  }
  if (string_equal(x, n, "GLEN", 4)) {
    return ST_CODE_GLEN;
  }
  if (string_equal(x, n, "PROMENADE", 9)) {
    return ST_CODE_PROMENADE;
  }
  if (string_equal(x, n, "ROW", 3)) {
    return ST_CODE_ROW;
  }
  if (string_equal(x, n, "RIDGE", 5)) {
    return ST_CODE_RIDGE;
  }
  if (string_equal(x, n, "FIREBREAK", 9)) {
    return ST_CODE_FIREBREAK;
  }
  if (string_equal(x, n, "GLADE", 5)) {
    return ST_CODE_GLADE;
  }
  if (string_equal(x, n, "APPROACH", 8)) {
    return ST_CODE_APPROACH;
  }
  if (string_equal(x, n, "PATH", 4)) {
    return ST_CODE_PATH;
  }
  if (string_equal(x, n, "RUN", 3)) {
    return ST_CODE_RUN;
  }
  if (string_equal(x, n, "BYPASS", 6)) {
    return ST_CODE_BYPASS;
  }
  if (string_equal(x, n, "ALLEY", 5)) {
    return ST_CODE_ALLEY;
  }
  if (string_equal(x, n, "ARCADE", 6)) {
    return ST_CODE_ARCADE;
  }
  if (string_equal(x, n, "ELBOW", 5)) {
    return ST_CODE_ELBOW;
  }
  if (string_equal(x, n, "BRACE", 5)) {
    return ST_CODE_BRACE;
  }
  if (string_equal(x, n, "CORNER", 6)) {
    return ST_CODE_CORNER;
  }
  if (string_equal(x, n, "ROUTE", 5)) {
    return ST_CODE_ROUTE;
  }
  if (string_equal(x, n, "RAMBLE", 6)) {
    return ST_CODE_RAMBLE;
  }
  if (string_equal(x, n, "FIRELINE", 8)) {
    return ST_CODE_FIRELINE;
  }
  if (string_equal(x, n, "CROSSING", 8)) {
    return ST_CODE_CROSSING;
  }
  if (string_equal(x, n, "GATE", 4)) {
    return ST_CODE_GATE;
  }
  if (string_equal(x, n, "GRANGE", 6)) {
    return ST_CODE_GRANGE;
  }
  if (string_equal(x, n, "FAIRWAY", 7)) {
    return ST_CODE_FAIRWAY;
  }
  if (string_equal(x, n, "LOOKOUT", 7)) {
    return ST_CODE_LOOKOUT;
  }
  if (string_equal(x, n, "POINT", 5)) {
    return ST_CODE_POINT;
  }
  if (string_equal(x, n, "HILL", 4)) {
    return ST_CODE_HILL;
  }
  if (string_equal(x, n, "CREST", 5)) {
    return ST_CODE_CREST;
  }
  if (string_equal(x, n, "LANEWAY", 7)) {
    return ST_CODE_LANEWAY;
  }
  if (string_equal(x, n, "EXPRESSWAY", 10)) {
    return ST_CODE_EXPRESSWAY;
  }
  if (string_equal(x, n, "LINE", 4)) {
    return ST_CODE_LINE;
  }
  if (string_equal(x, n, "MALL", 4)) {
    return ST_CODE_MALL;
  }
  if (string_equal(x, n, "MEANDER", 7)) {
    return ST_CODE_MEANDER;
  }
  if (string_equal(x, n, "OUTLOOK", 7)) {
    return ST_CODE_OUTLOOK;
  }
  if (string_equal(x, n, "BAY", 3)) {
    return ST_CODE_BAY;
  }
  if (string_equal(x, n, "CROSS", 5)) {
    return ST_CODE_CROSS;
  }
  if (string_equal(x, n, "WALKWAY", 7)) {
    return ST_CODE_WALKWAY;
  }
  if (string_equal(x, n, "FIRETRACK", 9)) {
    return ST_CODE_FIRETRACK;
  }
  if (string_equal(x, n, "BRIDGE", 6)) {
    return ST_CODE_BRIDGE;
  }
  if (string_equal(x, n, "PARK", 4)) {
    return ST_CODE_PARK;
  }
  if (string_equal(x, n, "PLAZA", 5)) {
    return ST_CODE_PLAZA;
  }
  if (string_equal(x, n, "NOOK", 4)) {
    return ST_CODE_NOOK;
  }
  if (string_equal(x, n, "WYND", 4)) {
    return ST_CODE_WYND;
  }
  if (string_equal(x, n, "VALE", 4)) {
    return ST_CODE_VALE;
  }
  if (string_equal(x, n, "DOWNS", 5)) {
    return ST_CODE_DOWNS;
  }
  if (string_equal(x, n, "SPUR", 4)) {
    return ST_CODE_SPUR;
  }
  if (string_equal(x, n, "BUSWAY", 6)) {
    return ST_CODE_BUSWAY;
  }
  if (string_equal(x, n, "CIRCUS", 6)) {
    return ST_CODE_CIRCUS;
  }
  if (string_equal(x, n, "POCKET", 6)) {
    return ST_CODE_POCKET;
  }
  if (string_equal(x, n, "BOARDWALK", 9)) {
    return ST_CODE_BOARDWALK;
  }
  if (string_equal(x, n, "CONCOURSE", 9)) {
    return ST_CODE_CONCOURSE;
  }
  if (string_equal(x, n, "RIVER", 5)) {
    return ST_CODE_RIVER;
  }
  if (string_equal(x, n, "QUAYS", 5)) {
    return ST_CODE_QUAYS;
  }
  if (string_equal(x, n, "RESERVE", 7)) {
    return ST_CODE_RESERVE;
  }
  if (string_equal(x, n, "DALE", 4)) {
    return ST_CODE_DALE;
  }
  if (string_equal(x, n, "ISLAND", 6)) {
    return ST_CODE_ISLAND;
  }
  if (string_equal(x, n, "REST", 4)) {
    return ST_CODE_REST;
  }
  if (string_equal(x, n, "CONNECTION", 10)) {
    return ST_CODE_CONNECTION;
  }
  if (string_equal(x, n, "END", 3)) {
    return ST_CODE_END;
  }
  if (string_equal(x, n, "QUAY", 4)) {
    return ST_CODE_QUAY;
  }
  if (string_equal(x, n, "VIEWS", 5)) {
    return ST_CODE_VIEWS;
  }
  if (string_equal(x, n, "KEY", 3)) {
    return ST_CODE_KEY;
  }
  if (string_equal(x, n, "TRAVERSE", 8)) {
    return ST_CODE_TRAVERSE;
  }
  if (string_equal(x, n, "BOULEVARDE", 10)) {
    return ST_CODE_BOULEVARDE;
  }
  if (string_equal(x, n, "FORMATION", 9)) {
    return ST_CODE_FORMATION;
  }
  if (string_equal(x, n, "OUTLET", 6)) {
    return ST_CODE_OUTLET;
  }
  if (string_equal(x, n, "DRIVEWAY", 8)) {
    return ST_CODE_DRIVEWAY;
  }
  if (string_equal(x, n, "LANDING", 7)) {
    return ST_CODE_LANDING;
  }
  if (string_equal(x, n, "EDGE", 4)) {
    return ST_CODE_EDGE;
  }
  if (string_equal(x, n, "QUADRANT", 8)) {
    return ST_CODE_QUADRANT;
  }
  if (string_equal(x, n, "VALLEY", 6)) {
    return ST_CODE_VALLEY;
  }
  if (string_equal(x, n, "WATERS", 6)) {
    return ST_CODE_WATERS;
  }
  if (string_equal(x, n, "CAUSEWAY", 8)) {
    return ST_CODE_CAUSEWAY;
  }
  if (string_equal(x, n, "BEACH", 5)) {
    return ST_CODE_BEACH;
  }
  if (string_equal(x, n, "SERVICEWAY", 10)) {
    return ST_CODE_SERVICEWAY;
  }
  if (string_equal(x, n, "CENTRE", 6)) {
    return ST_CODE_CENTRE;
  }
  if (string_equal(x, n, "EASEMENT", 8)) {
    return ST_CODE_EASEMENT;
  }
  if (string_equal(x, n, "PASSAGE", 7)) {
    return ST_CODE_PASSAGE;
  }
  if (string_equal(x, n, "STRIP", 5)) {
    return ST_CODE_STRIP;
  }
  if (string_equal(x, n, "TARN", 4)) {
    return ST_CODE_TARN;
  }
  if (string_equal(x, n, "BRAE", 4)) {
    return ST_CODE_BRAE;
  }
  if (string_equal(x, n, "DEVIATION", 9)) {
    return ST_CODE_DEVIATION;
  }
  if (string_equal(x, n, "JUNCTION", 8)) {
    return ST_CODE_JUNCTION;
  }
  if (string_equal(x, n, "STEPS", 5)) {
    return ST_CODE_STEPS;
  }
  if (string_equal(x, n, "WHARF", 5)) {
    return ST_CODE_WHARF;
  }
  if (string_equal(x, n, "BOWL", 4)) {
    return ST_CODE_BOWL;
  }
  if (string_equal(x, n, "COURSE", 6)) {
    return ST_CODE_COURSE;
  }
  if (string_equal(x, n, "GAP", 3)) {
    return ST_CODE_GAP;
  }
  if (string_equal(x, n, "GULLY", 5)) {
    return ST_CODE_GULLY;
  }
  if (string_equal(x, n, "TUNNEL", 6)) {
    return ST_CODE_TUNNEL;
  }
  if (string_equal(x, n, "CUTTING", 7)) {
    return ST_CODE_CUTTING;
  }

  if (string_equal(x, n, "EXTENSION", 9)) {
    return ST_CODE_EXTENSION;
  }
  if (string_equal(x, n, "FORESHORE", 9)) {
    return ST_CODE_FORESHORE;
  }
  if (string_equal(x, n, "GATEWAY", 7)) {
    return ST_CODE_GATEWAY;
  }
  if (string_equal(x, n, "HAVEN", 5)) {
    return ST_CODE_HAVEN;
  }
  if (string_equal(x, n, "ROTARY", 6)) {
    return ST_CODE_ROTARY;
  }
  if (string_equal(x, n, "COMMON", 6)) {
    return ST_CODE_COMMON;
  }
  if (string_equal(x, n, "COPSE", 5)) {
    return ST_CODE_COPSE;
  }
  if (string_equal(x, n, "DISTRIBUTOR", 11)) {
    return ST_CODE_DISTRIBUTOR;
  }
  if (string_equal(x, n, "FOLLOW", 6)) {
    return ST_CODE_FOLLOW;
  }
  if (string_equal(x, n, "FRONTAGE", 8)) {
    return ST_CODE_FRONTAGE;
  }
  if (string_equal(x, n, "TOR", 3)) {
    return ST_CODE_TOR;
  }
  if (string_equal(x, n, "ARTERIAL", 8)) {
    return ST_CODE_ARTERIAL;
  }
  if (string_equal(x, n, "BANK", 4)) {
    return ST_CODE_BANK;
  }
  if (string_equal(x, n, "NORTH", 5)) {
    return ST_CODE_NORTH;
  }
  if (string_equal(x, n, "ROADS", 5)) {
    return ST_CODE_ROADS;
  }
  if (string_equal(x, n, "UNDERPASS", 9)) {
    return ST_CODE_UNDERPASS;
  }
  if (string_equal(x, n, "BROW", 4)) {
    return ST_CODE_BROW;
  }
  if (string_equal(x, n, "HEATH", 5)) {
    return ST_CODE_HEATH;
  }
  if (string_equal(x, n, "LADDER", 6)) {
    return ST_CODE_LADDER;
  }
  if (string_equal(x, n, "PRECINCT", 8)) {
    return ST_CODE_PRECINCT;
  }
  if (string_equal(x, n, "RANGE", 5)) {
    return ST_CODE_RANGE;
  }
  if (string_equal(x, n, "SOUTH", 5)) {
    return ST_CODE_SOUTH;
  }
  if (string_equal(x, n, "TRUNKWAY", 8)) {
    return ST_CODE_TRUNKWAY;
  }
  if (string_equal(x, n, "AMBLE", 5)) {
    return ST_CODE_AMBLE;
  }
  if (string_equal(x, n, "BANAN", 5)) {
    return ST_CODE_BANAN;
  }
  if (string_equal(x, n, "BRANCH", 6)) {
    return ST_CODE_BRANCH;
  }
  if (string_equal(x, n, "CORSO", 5)) {
    return ST_CODE_CORSO;
  }
  if (string_equal(x, n, "DIVIDE", 6)) {
    return ST_CODE_DIVIDE;
  }
  if (string_equal(x, n, "DOCK", 4)) {
    return ST_CODE_DOCK;
  }
  if (string_equal(x, n, "FORD", 4)) {
    return ST_CODE_FORD;
  }
  if (string_equal(x, n, "FORK", 4)) {
    return ST_CODE_FORK;
  }
  if (string_equal(x, n, "GARDEN", 6)) {
    return ST_CODE_GARDEN;
  }
  if (string_equal(x, n, "HIKE", 4)) {
    return ST_CODE_HIKE;
  }
  if (string_equal(x, n, "HOLLOW", 6)) {
    return ST_CODE_HOLLOW;
  }
  if (string_equal(x, n, "INTERCHANGE", 11)) {
    return ST_CODE_INTERCHANGE;
  }
  if (string_equal(x, n, "PALMS", 5)) {
    return ST_CODE_PALMS;
  }
  if (string_equal(x, n, "RIDE", 4)) {
    return ST_CODE_RIDE;
  }
  if (string_equal(x, n, "ROUND", 5)) {
    return ST_CODE_ROUND;
  }
  if (string_equal(x, n, "SLOPE", 5)) {
    return ST_CODE_SLOPE;
  }
  if (string_equal(x, n, "STRAIT", 6)) {
    return ST_CODE_STRAIT;
  }
  if (string_equal(x, n, "SUBWAY", 6)) {
    return ST_CODE_SUBWAY;
  }
  if (string_equal(x, n, "TOP", 3)) {
    return ST_CODE_TOP;
  }
  if (string_equal(x, n, "TRAMWAY", 7)) {
    return ST_CODE_TRAMWAY;
  }
  if (string_equal(x, n, "BROADWAY", 8)) {
    return ST_CODE_BROADWAY;
  }
  if (string_equal(x, n, "CLUSTER", 7)) {
    return ST_CODE_CLUSTER;
  }
  if (string_equal(x, n, "DELL", 4)) {
    return ST_CODE_DELL;
  }
  if (string_equal(x, n, "DOMAIN", 6)) {
    return ST_CODE_DOMAIN;
  }
  if (string_equal(x, n, "FLAT", 4)) {
    return ST_CODE_FLAT;
  }
  if (string_equal(x, n, "HUB", 3)) {
    return ST_CODE_HUB;
  }
  if (string_equal(x, n, "LYNNE", 5)) {
    return ST_CODE_LYNNE;
  }
  if (string_equal(x, n, "MEAD", 4)) {
    return ST_CODE_MEAD;
  }
  if (string_equal(x, n, "MILE", 4)) {
    return ST_CODE_MILE;
  }
  if (string_equal(x, n, "PORT", 4)) {
    return ST_CODE_PORT;
  }
  if (string_equal(x, n, "REACH", 5)) {
    return ST_CODE_REACH;
  }
  if (string_equal(x, n, "RETURN", 6)) {
    return ST_CODE_RETURN;
  }
  if (string_equal(x, n, "STRAIGHT", 8)) {
    return ST_CODE_STRAIGHT;
  }
  if (string_equal(x, n, "VILLAGE", 7)) {
    return ST_CODE_VILLAGE;
  }
  if (string_equal(x, n, "WEST", 4)) {
    return ST_CODE_WEST;
  }
  if (string_equal(x, n, "WOODS", 5)) {
    return ST_CODE_WOODS;
  }
  if (string_equal(x, n, "ACRE", 4)) {
    return ST_CODE_ACRE;
  }
  if (string_equal(x, n, "BYWAY", 5)) {
    return ST_CODE_BYWAY;
  }
  if (string_equal(x, n, "CENTREWAY", 9)) {
    return ST_CODE_CENTREWAY;
  }
  if (string_equal(x, n, "COMMONS", 7)) {
    return ST_CODE_COMMONS;
  }
  if (string_equal(x, n, "CONCORD", 7)) {
    return ST_CODE_CONCORD;
  }
  if (string_equal(x, n, "COURTYARD", 9)) {
    return ST_CODE_COURTYARD;
  }
  if (string_equal(x, n, "CRIEF", 5)) {
    return ST_CODE_CRIEF;
  }
  if (string_equal(x, n, "CRUISEWAY", 9)) {
    return ST_CODE_CRUISEWAY;
  }
  if (string_equal(x, n, "CUL-DE-SAC", 10)) {
    return ST_CODE_CULDESAC;
  }
  if (string_equal(x, n, "DASH", 4)) {
    return ST_CODE_DASH;
  }
  if (string_equal(x, n, "DENE", 4)) {
    return ST_CODE_DENE;
  }
  if (string_equal(x, n, "DIP", 3)) {
    return ST_CODE_DIP;
  }
  if (string_equal(x, n, "DOWN", 4)) {
    return ST_CODE_DOWN;
  }
  if (string_equal(x, n, "EAST", 4)) {
    return ST_CODE_EAST;
  }
  if (string_equal(x, n, "FLATS", 5)) {
    return ST_CODE_FLATS;
  }
  if (string_equal(x, n, "HARBOUR", 7)) {
    return ST_CODE_HARBOUR;
  }
  if (string_equal(x, n, "HILLS", 5)) {
    return ST_CODE_HILLS;
  }
  if (string_equal(x, n, "KEYS", 4)) {
    return ST_CODE_KEYS;
  }
  if (string_equal(x, n, "MANOR", 5)) {
    return ST_CODE_MANOR;
  }
  if (string_equal(x, n, "MART", 4)) {
    return ST_CODE_MART;
  }
  if (string_equal(x, n, "MAZE", 4)) {
    return ST_CODE_MAZE;
  }
  if (string_equal(x, n, "PURSUIT", 7)) {
    return ST_CODE_PURSUIT;
  }
  if (string_equal(x, n, "RISING", 6)) {
    return ST_CODE_RISING;
  }
  if (string_equal(x, n, "ROADWAY", 7)) {
    return ST_CODE_ROADWAY;
  }
  if (string_equal(x, n, "THROUGHWAY", 10)) {
    return ST_CODE_THROUGHWAY;
  }
  if (string_equal(x, n, "TWIST", 5)) {
    return ST_CODE_TWIST;
  }
  if (string_equal(x, n, "VILLA", 5)) {
    return ST_CODE_VILLA;
  }
  if (string_equal(x, n, "WATERWAY", 8)) {
    return ST_CODE_WATERWAY;
  }
  if (string_equal(x, n, "YARD", 4)) {
    return ST_CODE_YARD;
  }
  return 0;
}

SEXP CStreet2StreetCode(SEXP xx) {
	R_xlen_t N = xlength(xx);
  SEXP ans = PROTECT(allocVector(INTSXP, N));
  int * restrict ansp = INTEGER(ans);
	for (R_xlen_t i = 0; i < N; ++i) {
		// whichStreetName(const char * x, unsigned int len, int ans[])
		int n = length(STRING_ELT(xx, i));
		const char * x = CHAR(STRING_ELT(xx, i));
		ansp[i] = which_street_code(x, n);
	}
	UNPROTECT(1);
	return ans;
}

int find_common_street(const char * x, int n, int i) {
  switch(x[i]) {
  case 'A':
    if (i < n - 6 &&
        x[i + 1] == 'V' &&
        x[i + 2] == 'E') {
      if (x[i + 3] == ' ') {
        return ST_CODE_AVENUE;
      }
      if (x[i + 3] == 'N' &&
          x[i + 4] == 'U' &&
          x[i + 5] == 'E' &&
          x[i + 6] == ' ') {
        return ST_CODE_AVENUE;
      }
    }
    return -1;
    break;
  case 'C':
    switch(x[i + 1]) {
    case 'O':
      if (x[i + 2] == 'U' &&
          x[i + 3] == 'R' &&
          x[i + 4] == 'T') {
        return ST_CODE_COURT;
      }
    }
  }
  return -1;
}

bool has_ROAD(const char * x, int n) {
  // assume postcode
  for (int i = 1; i < n - 6; ++i) {
    if (x[i - 1] != ' ') {
      continue;
    }
    if (x[i] == 'R') {
      if (x[i + 1] == 'D' && x[i + 2] == ' ') {
        return true;
      }
      if (x[i + 1] == 'O' && x[i + 2] == 'A' && x[i + 3] == 'D' && x[i + 4] == ' ') {
        return true;
      }
    }
  }
  return false;
}

bool has_STREET(const char * x, int n) {
  // assume postcode
  for (int i = 1; i < n - 7; ++i) {
    if (x[i - 1] != ' ') {
      continue;
    }
    if (x[i] == 'S' && x[i + 1] == 'T') {
      // Don't do 'ST' because of places like st albans
      if (x[i + 2] == 'R' &&
          x[i + 3] == 'E' &&
          x[i + 4] == 'E' &&
          x[i + 5] == 'T' &&
          x[i + 6] == ' ') {
        return true;
      }
    }
  }
  return false;
}

bool has_COURT(const char * x, int n) {
  // assume postcode
  for (int i = 1; i < n - 6; ++i) {
    if (x[i - 1] != ' ') {
      continue;
    }
    if (x[i] == 'C') {
      if (x[i + 1] == 'T' && x[i + 2] == ' ') {
        return true;
      }
      // Don't do 'ST' because of places like st albans
      if (x[i + 1] == 'O' && x[i + 2] == 'U' && x[i + 3] == 'R' && x[i + 4] == 'T' && x[i + 5] == ' ') {
        return true;
      }
    }
  }
  return false;
}

bool has_AVENUE(const char * x, int n) {
  // assume postcode
  for (int i = 1; i < n - 7; ++i) {
    if (x[i - 1] != ' ') {
      continue;
    }
    if (x[i] == 'A' && x[i + 1] == 'V' && x[i + 2] == 'E') {
      if (x[i + 3] == ' ') {
        return true;
      }
      // Don't do 'ST' because of places like st albans
      if (x[i + 3] == 'N' && x[i + 4] == 'U' && x[i + 5] == 'E' && x[i + 6] == ' ') {
        return true;
      }
    }
  }
  return false;
}

bool has_PLACE(const char * x, int n) {
  // assume postcode
  for (int i = 1; i < n - 6; ++i) {
    if (x[i - 1] != ' ') {
      continue;
    }
    if (x[i] == 'P' && x[i + 1] == 'L') {
      if (x[i + 2] == ' ') {
        return true;
      }
      if (x[i + 2] == 'A' && x[i + 3] == 'C' && x[i + 4] == 'E' && x[i + 5] == ' ') {
        return true;
      }
    }
  }
  return false;
}

bool has_LANE(const char * x, int n) {
  // assume postcode
  for (int i = 1; i < n - 6; ++i) {
    if (x[i - 1] != ' ') {
      continue;
    }
    if (x[i] == 'L') {
      if (x[i + 1] == 'N' && x[i + 2] == ' ') {
        return true;
      }
      if (x[i + 1] == 'A' && x[i + 2] == 'N' && x[i + 3] == 'E' && x[i + 4] == ' ') {
        return true;
      }
    }
  }
  return false;
}

bool has_DRIVE(const char * x, int n) {
  // assume postcode
  for (int i = 1; i < n - 6; ++i) {
    if (x[i - 1] != ' ') {
      continue;
    }
    if (x[i] == 'D' && x[i + 1] == 'R') {
      if (x[i + 2] == ' ') {
        return true;
      }
      if (x[i + 2] == 'I' && x[i + 3] == 'V' && x[i + 4] == 'E' && x[i + 5] == ' ') {
        return true;
      }
    }
  }
  return false;
}

bool has_WAY(const char * x, int n) {
  for (int i = 1; i < n - 6; ++i) {
    if (x[i - 1] != ' ') {
      continue;
    }
    if (x[i] == 'W') {
      if (x[i + 1] == 'A' && x[i + 2] == 'Y' && x[i + 3] == ' ') {
        return true;
      }
      if (x[i + 1] == 'Y' && x[i + 2] == ' ') {
        return true;
      }
    }
  }
  return false;
}

bool has_CLOSE(const char * x, int n) {
  for (int i = 1; i < n - 6; ++i) {
    if (x[i - 1] != ' ') {
      continue;
    }
    if (x[i] == 'C' && x[i + 1] == 'L') {
      if (x[i + 2] == ' ') {
        return true;
      }
      if (x[i + 2] == 'S' &&
          x[i + 3] == 'E' &&
          x[i + 4] == ' ') {
        return true;
      }
    }
  }
  return false;
}

bool has_GROVE(const char * x, int n) {
  for (int i = 1; i < n - 6; ++i) {
    if (x[i - 1] != ' ') {
      continue;
    }
    if (x[i] == 'G' && x[i + 1] == 'R') {
      if (x[i + 2] == ' ') {
        return true;
      }
      if (x[i + 2] == 'O' &&
          x[i + 3] == 'V' &&
          x[i + 4] == 'E' &&
          x[i + 5] == ' ') {
        return true;
      }
    }
  }
  return false;
}

bool poa_has_ROAD(int poa) {
	return poa_has_street_type(poa, ST_CODE_ROAD);
}





SEXP Cpoa_has_stcd(SEXP Postcode) {
  const int postcode = asInteger(Postcode);
  int ans[256] = {0};
  int n = 0;
  for (int i = 0; i < N_STREET_TYPES; ++i) {
    if (poa_has_street_type(postcode, i)) {
      ans[n] = i + 1;
      ++n;
    }
  }
  SEXP Ans = PROTECT(allocVector(INTSXP, n));
  int * restrict ansp = INTEGER(Ans);
  for (int j = 0; j < n; ++j) {
    ansp[j] = ans[j];
  }
  UNPROTECT(1);
  return Ans;
}




