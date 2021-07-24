#include "healthyAddress.h"

SEXP CStreetCd2Str(SEXP x) {
	R_xlen_t N = xlength(x);
	const int * xp = INTEGER(x);
	SEXP ans = PROTECT(allocVector(STRSXP, N));
	for (R_xlen_t i = 0; i < N; ++i) {
		int xpi = xp[i];
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



