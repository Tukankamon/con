#include <stddef.h>
#include <stdio.h>

typedef enum {
  OK,
  GENERAL,
  INVALID_VALUE,
  NOT_DIGIT,
  INVALID_BASE,
  INVALID_FLAG,
} Error;

int handleError(Error e) {
  switch (e) {
    case GENERAL:
      printf("There was a GENERAl error\n");
      return 1;
    case INVALID_VALUE:
      printf("Invalid value input\n");
      return 1;
    case NOT_DIGIT:
      printf("Invalid digit in the input\n");
      return 1;
    case INVALID_BASE:
      printf("Invalid base for given input\n");
      return 1;
    default:
      printf("Everything is OK, no errors\n");
      return 0;
  }
}

// Capital L to not mix with strlen
// Can reach stack overflow in large strings
size_t strLen(const char *num) {
  if (*num == '\0') return 0;
  else {
    return strLen (num+1) +1;
  }
}

size_t strToInt(Error *err, char c) {
  switch (c) {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    case 'A':
    case 'a':
      return 10;
    case 'B':
    case 'b':
      return 11;
    case 'C':
    case 'c':
      return 12;
    case 'D':
    case 'd':
      return 13;
    case 'E':
    case 'e':
      return 14;
    case 'F':
    case 'f':
      return 15;
    default:
      *err = NOT_DIGIT;
      return 0;
  }
}

size_t power(size_t base, size_t expo) {
  size_t result = 1;
  for (size_t i = 0; i<expo; i++) {
    result *= base;
  }
  return result;
}

char* pruneIdentifier(const char*num) {
  char* p = num; // To make sure num doesnt change
  switch (*p) {
    case '0':
    case 'x':
    case 'X':
    case 'b':
    case 'B':
    case 'o':
    case 'O':
      return pruneIdentifier(p+1);
    default: return p;
  }
}

size_t handleBase(Error *err, const char *num, int base) {
  num = pruneIdentifier(num);
  size_t dim = strLen(num);
  size_t result = 0;
  for (size_t i = 0; i<dim; i++) {
    size_t c = strToInt(err, num[i]); // #TODO find better name for "c"
    if (c >= base) {
      *err = INVALID_BASE;
      return 0;
    }
    result += c * power(base, dim-i-1);
  }
  return result;
}

size_t baseChange(Error *err, char *num) {
  if (strLen(num)==0) {
    *err = INVALID_VALUE;
    return 0;
  }
  if (num[0] != '0' || strLen(num) == 1) {
    return handleBase(err, num, 10);
  };
  char identifier = num[1];
  switch (identifier) {
    case 'x':
    case 'X':
      return handleBase(err, num, 16);
    case 'b':
    case 'B':
      return handleBase(err, num, 2);
    // Standard is to not have an identifier so 010 is 8 in octal
    case 'o':
    case 'O':
      return handleBase(err, num, 8);
    default:
      *err = INVALID_VALUE;
      return 0;
  }
}

int flag(Error *err, int argc, char* argv[]){
  if (argc != 3) return 1;
  if (strLen(argv[2]) != 2 || argv[2][0] != '-') {
    *err = INVALID_FLAG;
    printf("E: Invalid flag");
    return 0;
  }
  int result;
  // #TODO add arbitrary bases
  switch (argv[2][1]) {
    case 'd': return 10;
    case 'x': return 16;
    case 'b': return 2;
    case 'o': return 8;
    default: return 0;
  }
}

int main (int argc, char *argv[]){
  Error err = OK;
  if (argc < 2 || argc > 3) {
    printf("Usage: %s 0x/0b + NUMBER [-b] [-x] [-d] [-o]\n", argv[0]);
    return 1;
  }
  size_t result = baseChange(&err, argv[1]);

  if (err != OK) {
    handleError(err);
    return 1;
  }

  switch (flag(&err, argc, argv)) {
    case 10:
      printf("Result in decimal: %lu\n", result);
      return 0;
    case 2:
      printf("Result in binary: %b\n", result);
      return 0;
    case 16:
      printf("Result in hexadecimal: 0x%x\n", result);
      return 0;
    case 8:
      printf("Result in octal: 0%o\n", result); // idk if it is %o
      return 0;
    case 1:
      return 0;
    default:
      handleError(err);
      return 1;
  }
  return 1;
}
