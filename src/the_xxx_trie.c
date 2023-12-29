#include "healthyAddress.h"

#define N_THE_XXXS 25

// This is true, but not necessarily the longest
// word one might find in an address string
#define MAX_STREET_NAME_LEN 41


const char * THE_XXXs[N_THE_XXXS] =
  {"ESPLANADE", "AVENUE", "CRESCENT", "BOULEVARDE", "BOULEVARD", "STRAND", "ENTRANCE ROAD",
   "PARADE", "HORSLEY DRIVE", "PARKWAY", "PROMENADE", "TERRACE", "CORSO", "GRAND PARADE",
   "GROVE", "NORTHERN ROAD", "LAKES WAY", "BUCKETTS WAY", "RIDGE", "GRANGE", "RIDGEWAY",
   "RIVER ROAD", "WOOL ROAD", "PENINSULA", "SCENIC ROAD"};


#define ALPHABET_SIZE 27  // Assuming only uppercase letters

typedef struct TrieNode {
  struct TrieNode *children[ALPHABET_SIZE];
  bool isEndOfWord;
  int code;  // New field to store the code
} TrieNode;


TrieNode *getNode(void) {
  TrieNode *pNode = (TrieNode *)malloc(sizeof(TrieNode));

  if (pNode) {
    pNode->isEndOfWord = false;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
      pNode->children[i] = NULL;
    }
  }

  return pNode;
}

void freeTrie(TrieNode *root) {
  if (!root) return;

  for (int i = 0; i < ALPHABET_SIZE; i++) {
    freeTrie(root->children[i]);
  }

  free(root);
}

void insert(TrieNode *root, const char *key, int code) {
  TrieNode *pCrawl = root;

  for (int i = 0; key[i] != '\0'; i++) {
    unsigned int index = key[i] - 'A';
    if (index >= ALPHABET_SIZE) {
      index = ALPHABET_SIZE - 1;
    }
    if (!pCrawl->children[index]) {
      pCrawl->children[index] = getNode();
    }
    pCrawl = pCrawl->children[index];
  }

  pCrawl->isEndOfWord = true;
  pCrawl->code = code;  // Set the code for the end node
}

int search(TrieNode *root, const char *key) {
  TrieNode *pCrawl = root;

  for (int i = 0; key[i] != '\0'; i++) {
    int index = key[i] - 'A';
    if (!pCrawl->children[index]) {
      return -1;  // Word not found
    }
    pCrawl = pCrawl->children[index];
  }

  if (pCrawl != NULL && pCrawl->isEndOfWord) {
    return pCrawl->code;  // Return the code associated with the word
  }

  return -1;  // Word not found
}

void insert_all(TrieNode *root) {
  for (int i = 0; i < N_THE_XXXS; ++i) {
    insert(root, THE_XXXs[i], i);
  }
}

int THE_xxx2(TrieNode *root, WordData wd) {
  const char *x = wd.x;
  int n_words = wd.n_words;

  for (int w = 0; w < n_words - 1; ++w) {
    int lhs = wd.lhs[w];
    int rhs = wd.rhs[w];

    if (rhs - lhs != 3) continue;

    int j = lhs;
    if (x[j++] != 'T' || x[j++] != 'H' || x[j++] != 'E') continue;

    lhs = wd.lhs[w + 1];
    rhs = wd.rhs[w + 1];
    int w_ = rhs - lhs;
    if (w_ > MAX_STREET_NAME_LEN || !isupper(x[lhs])) {
      continue;
    }

    // Extract the substring starting after 'THE ' and use it for trie search
    char streetName[MAX_STREET_NAME_LEN]; // Define MAX_STREET_NAME_LEN appropriately
    strncpy(streetName, x + lhs, rhs - lhs);
    streetName[rhs - lhs] = '\0'; // Null-terminate the extracted string

    // Use trie to check if this is a known street name
    int maybe_code = search(root, streetName);
    if (maybe_code != -1) {
      // Found a match, return appropriate code or perform needed action
      return maybe_code; // Replace with actual return code
    }
  }

  return 0; // No match found
}

SEXP C_do_the_xxx(SEXP x) {
  errIfNotStr(x, "x");
  R_xlen_t N = xlength(x);
  const SEXP * xp = STRING_PTR(x);
  TrieNode * root = getNode();
  if (root == NULL) {
    error("root == NULL");
  }
  insert_all(root);
  SEXP ans = PROTECT(allocVector(INTSXP, N));
  int * restrict ansp = INTEGER(ans);
  for (R_xlen_t i = 0; i < N; ++i) {
    if (xp[i] == NA_STRING) {
      ansp[i] = NA_INTEGER;
      continue;
    }
    const char * xi = CHAR(xp[i]);
    int ni = length(xp[i]);
    if (ni <= 4) {
      ansp[i] = 0;
      continue;
    }
    WordData wd = word_data(xi, ni, 0); // 9M/s
    ansp[i] = THE_xxx2(root, wd); // 60M/s
  }
  freeTrie(root);
  UNPROTECT(1);
  return ans;
}


