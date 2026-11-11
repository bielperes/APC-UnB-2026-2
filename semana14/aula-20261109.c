#include <stdlib.h>
typedef struct Ponto { int x; int y; } Ponto;
void recursao(int i, Ponto *** ponteiroDePontosAlocados) {
  Ponto *pp2 = (Ponto *) malloc(sizeof(Ponto));
  ponteiroDePontosAlocados[i] = pp2;
  if (i>0) recursao(i-1, ponteiroDePontosAlocados);
}  
void main() {
  Ponto * pontosAlocados[3];  
/* Acesso */
  recursao (2, &pontosAlocados);
  for (int i = 0; i < 3; i++) {
    free(pontosAlocados[i]);
  }
}