
typedef struct {
  int *digits;
  int size;
  int capacity;
} BigInt;

void MakeBigInt(BigInt *n, char *num);

BigInt add(BigInt *a, BigInt *b);

BigInt multiply(BigInt *a, BigInt *b);

void PrintBigInt(BigInt *n);

void DropBigInt(BigInt *first, ...);
