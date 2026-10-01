# C Language — Cheatsheet com Exercícios (pythontutor.com)

> **Como usar:** acesse <https://pythontutor.com/c.html>, cole o código do exercício e clique em
> **"Visualize Execution"**. Use os botões **Next** e **Prev** para avançar passo a passo e
> observar o estado das variáveis, da pilha (*stack*) e do heap.

---

## 0. Introdução — lendo C pela primeira vez

Você já programou em JavaScript (Code.org) e em Assembler. C usa os mesmos conceitos
fundamentais — variáveis, condicionais, loops, funções — mas com uma sintaxe diferente
e muito mais controle (e responsabilidade) sobre a memória. Esta seção mapeia o que
você já sabe para o que vai ver no código C.

### 0.1 Visão geral da sintaxe

Quatro diferenças saltam aos olhos ao ler C pela primeira vez:

| O que você vê | O que significa | Equivalente em Python |
|---|---|---|
| `int x = 10;` | declaração com **tipo explícito** + ponto-e-vírgula obrigatório | `x = 10` |
| `{ ... }` | delimitam um **bloco** (em Python era a indentação) | `:` + indentação |
| `/* comentário */` | comentário de bloco | `# comentário` |
| `// comentário` | comentário de linha (C99+) | `# comentário` |
| `#include <stdio.h>` | importa uma biblioteca | `import` |
| `printf("...")` | imprime no terminal | `print(...)` |
| `scanf("%d", &x)` | lê do teclado | `x = int(input())` |

### 0.2 Todo programa C tem esta forma

```c
#include <stdio.h>          /* 1. importar bibliotecas necessárias */

int main(void) {            /* 2. ponto de entrada obrigatório */

    /* 3. declarações de variáveis (tipo obrigatório) */
    int x = 10;
    float f = 3.14;

    /* 4. instruções — cada uma termina com ; */
    printf("x = %d\n", x);

    return 0;               /* 5. sinaliza que o programa terminou com sucesso */
}
```

Diferente de Python, C não executa linha a linha como script: o arquivo inteiro é
**compilado** para um executável antes de rodar. Se há erro de sintaxe, nada executa.

### 0.3 Tipos são obrigatórios — e importam

Em Python, `x = 10` cria uma variável sem declarar tipo. Em C, **toda variável precisa
ter seu tipo declarado antes de ser usada**, e o tipo determina quanto espaço na memória
ela ocupa e quais operações são válidas:

```c
int    x = 10;       /* inteiro: 4 bytes, sem casas decimais */
float  f = 3.14;     /* ponto flutuante: 4 bytes, ~7 casas significativas */
double d = 3.14159;  /* ponto flutuante duplo: 8 bytes, ~15 casas significativas */
char   c = 'A';      /* um único caractere: 1 byte */
```

A consequência mais importante: **divisão entre inteiros é inteira em C**.

```c
int resultado = 7 / 2;   /* resultado = 3, não 3.5 */
```

Em Python `7 / 2` dá `3.5`. Em C dá `3` — o resto é descartado silenciosamente.
Para obter `3.5` em C: `7.0 / 2` ou `(double)7 / 2`.

### 0.4 Ponto-e-vírgula e chaves

Cada **instrução** termina com `;`. Esquecer o ponto-e-vírgula é o erro de compilação
mais comum ao começar:

```c
int x = 10       /* ERRO: falta ; */
printf("x = %d\n", x)  /* ERRO: falta ; */
```

**Blocos** de código são delimitados por `{ }` em vez de indentação. A indentação
continua sendo boa prática, mas o compilador não a exige:

```c
if (x > 0) {
    printf("positivo\n");   /* dentro do bloco */
    x = x - 1;             /* ainda dentro do bloco */
}                           /* fim do bloco */
printf("fora\n");           /* fora do bloco */
```

### 0.5 Entrada e saída básicas

```c
/* Imprimir — printf com formatadores */
printf("Olá, mundo!\n");            /* \n = nova linha */
printf("x = %d\n", x);             /* %d = inteiro */
printf("f = %.2f\n", f);           /* %.2f = float com 2 casas decimais */
printf("c = %c\n", c);             /* %c = caractere */
printf("s = %s\n", "texto");       /* %s = string */

/* Ler do teclado — scanf */
int n;
scanf("%d", &n);    /* & é obrigatório: passa o ENDEREÇO de n */
                    /* sem &, o programa pode travar ou dar segfault */

float f;
scanf("%f", &f);    /* %f para float no scanf */

double d;
scanf("%lf", &d);   /* %lf para double no scanf (diferente do printf!) */
```

> ⚠️ O `&` no `scanf` é a diferença mais traiçoeira para quem vem do Python.
> Ele significa "passe o endereço de memória da variável para que scanf possa
> escrever o valor lá dentro". Sem ele, o comportamento é indefinido.

### 0.6 Comparando Python e C lado a lado

```python
# Python
x = int(input("Digite um número: "))
if x > 0:
    print("positivo")
elif x == 0:
    print("zero")
else:
    print("negativo")

for i in range(5):
    print(i)

def soma(a, b):
    return a + b

resultado = soma(3, 4)
print(resultado)
```

```c
/* C equivalente */
#include <stdio.h>

int soma(int a, int b) {      /* tipo dos parâmetros obrigatório */
    return a + b;
}

int main(void) {
    int x;
    printf("Digite um número: ");
    scanf("%d", &x);           /* & obrigatório */

    if (x > 0) {
        printf("positivo\n");
    } else if (x == 0) {       /* else if, não elif */
        printf("zero\n");
    } else {
        printf("negativo\n");
    }

    for (int i = 0; i < 5; i++) {   /* init; condição; incremento */
        printf("%d\n", i);
    }

    int resultado = soma(3, 4);     /* tipo do resultado obrigatório */
    printf("%d\n", resultado);

    return 0;
}
```

### 0.7 O que C expõe que Python esconde

C não é "Python mais difícil" — é uma linguagem que **expõe camadas que Python
esconde deliberadamente**. Aprender C muda a forma de entender qualquer linguagem:

| Python esconde | C expõe | Por que importa |
|---|---|---|
| tipo das variáveis | `int`, `float`, `char` explícitos | você sabe exatamente quantos bytes cada dado ocupa |
| alocação de memória | `malloc` / `free` explícitos | você controla quando a memória é criada e destruída |
| referências e cópias | ponteiros `*` e endereços `&` | você entende por que `lista2 = lista1` em Python não faz cópia |
| overflow de inteiro | silencioso — ocorre e é comportamento definido | você vê `0u - 1 = 4294967295` (wrap-around) |
| tamanho de strings | `\0` invisível ao final de todo array de char | você entende buffer overflow |

---

## 1. Estrutura de um programa

```c
#include <stdio.h>      /* inclui declarações da biblioteca padrão de E/S */
#include <stdlib.h>     /* malloc, free, exit, atoi, rand … */
#include <string.h>     /* strlen, strcpy, strcmp, memset … */
#include <math.h>       /* sqrt, pow, fabs … (compilar com -lm) */

int main(void) {
    /* código */
    return 0;           /* 0 = sucesso; qualquer outro valor = erro */
}

/* Também válido: */
int main(int argc, char *argv[]) {  /* argc = nº de argumentos; argv = vetor de strings */
    return 0;
}
```

**Unidade de compilação:** cada arquivo `.c` é compilado separadamente. Declarações
compartilhadas entre arquivos vão em arquivos `.h` (headers).

**Sequência de build:**
```
código-fonte (.c)  →  pré-processador  →  compilador  →  assembler  →  linker  →  executável
```

**Compilar com gcc:**
```bash
gcc -Wall -Wextra -std=c11 -o programa programa.c
gcc -Wall -Wextra -std=c11 -fsanitize=address -g -o programa programa.c  # com detecção de erros de memória
```

### 🔬 Exercício 1 — Pilha de chamadas

Cole e execute. Observe os frames de `main`, `soma_mult` e `mult` aparecerem e
desaparecerem na **pilha de chamadas**.

```c
#include <stdio.h>

int mult(int a, int b) {
    return a * b;
}

int soma_mult(int a, int b, int c) {
    return a + mult(b, c);
}

int main(void) {
    int resultado = soma_mult(1, 5, 3);
    printf("%d\n", resultado);   /* 16 */
    return 0;
}
```

---

## 2. Tipos primitivos e tamanhos

| Tipo       | Tamanho típico | Faixa (signed)                    | Exemplo literal |
|------------|----------------|-----------------------------------|-----------------|
| `char`     | 1 byte         | −128 a 127                        | `'A'`, `'\n'`   |
| `short`    | 2 bytes        | −32 768 a 32 767                  | `(short)100`    |
| `int`      | 4 bytes        | −2 147 483 648 a 2 147 483 647    | `42`, `-7`      |
| `long`     | 4–8 bytes      | depende da plataforma             | `100000L`       |
| `long long`| 8 bytes        | −9.2×10¹⁸ a 9.2×10¹⁸             | `9LL`           |
| `float`    | 4 bytes        | ~7 dígitos significativos         | `3.14f`         |
| `double`   | 8 bytes        | ~15 dígitos significativos        | `3.14159`       |
| `long double`| 8–16 bytes  | depende da plataforma             | `3.14L`         |
| `_Bool`    | 1 byte         | 0 ou 1                            | `0`, `1`        |

**Modificadores:**

| Modificador  | Efeito |
|---|---|
| `unsigned`   | elimina valores negativos; dobra o máximo positivo |
| `signed`     | padrão para `int`; explícito para `char` (depende do compilador) |
| `short`      | pelo menos 2 bytes |
| `long`       | pelo menos 4 bytes |
| `long long`  | pelo menos 8 bytes (C99+) |

**Tipos de tamanho exato** (`<stdint.h>`, preferíveis em código portável):

```c
#include <stdint.h>
int8_t   a;   /* exatamente 8 bits */
int16_t  b;   /* exatamente 16 bits */
int32_t  c;   /* exatamente 32 bits */
int64_t  d;   /* exatamente 64 bits */
uint32_t e;   /* sem sinal, 32 bits */
```

**Conversão implícita (promoção aritmética):**
- Operandos menores que `int` são promovidos a `int` antes da operação.
- Em operações mistas (`int` + `double`), o `int` é convertido para `double`.
- Atribuição de `double` para `int` **trunca** (não arredonda).

```c
int   x = 7 / 2;      /* 3   — divisão inteira */
float y = 7.0 / 2;    /* 3.5 — 7.0 promove 2 para double */
int   z = (int)3.9;   /* 3   — truncamento explícito (cast) */
```

### 🔬 Exercício 2 — Tamanhos e promoção

```c
#include <stdio.h>

int main(void) {
    printf("char:      %zu byte(s)\n", sizeof(char));
    printf("short:     %zu byte(s)\n", sizeof(short));
    printf("int:       %zu byte(s)\n", sizeof(int));
    printf("long:      %zu byte(s)\n", sizeof(long));
    printf("long long: %zu byte(s)\n", sizeof(long long));
    printf("float:     %zu byte(s)\n", sizeof(float));
    printf("double:    %zu byte(s)\n", sizeof(double));

    /* Promoção e truncamento */
    printf("\n7 / 2   = %d\n",   7 / 2);       /* 3  */
    printf("7.0 / 2 = %.1f\n",  7.0 / 2);      /* 3.5 */
    printf("(int)3.9= %d\n",    (int)3.9);      /* 3  */

    unsigned int u = 0;
    u--;  /* wrap-around: vira UINT_MAX */
    printf("0u - 1  = %u\n", u);
    return 0;
}
```

---

## 3. Declaração e inicialização

```c
int x;               /* declaração — valor INDEFINIDO (lixo de memória) */
int y = 10;          /* inicialização */
int a, b, c;         /* múltiplas declarações na mesma linha */
int v[5] = {0};      /* inicializa todos os elementos com 0 */
const int N = 5;     /* constante — não pode ser modificada após inicialização */
```

**Categorias de armazenamento:**

```c
auto int x;          /* padrão para variáveis locais — criada/destruída com o bloco */
static int s;        /* persiste durante toda a execução do programa */
extern int g;        /* declaração de variável definida em outro arquivo .c */
register int r;      /* sugestão ao compilador para usar registrador (raro hoje) */
```

**Inicialização de arrays e structs:**

```c
int v[5]      = {1, 2, 3};     /* v[3] e v[4] valem 0 automaticamente */
int m[2][3]   = {{1,2,3},{4,5,6}};
char s[10]    = "hello";        /* preenche com 'h','e','l','l','o','\0',0,0,0,0 */

struct Ponto p = {.x = 3, .y = 4};  /* inicializador designado (C99) */
```

**`volatile`:** informa ao compilador que o valor pode mudar a qualquer momento
(hardware, threads, signal handlers) — impede otimizações que eliminam leituras:

```c
volatile int sensor;   /* lido a cada acesso, nunca cacheado em registrador */
```

### 🔬 Exercício 3 — Variável não inicializada vs. inicializada

```c
#include <stdio.h>

int global = 0;   /* variáveis globais são inicializadas com 0 automaticamente */

int main(void) {
    int a = 42;
    int b;          /* valor lixo — NUNCA use antes de atribuir */
    b = a + 8;

    printf("a = %d\n", a);
    printf("b = %d\n", b);
    printf("global = %d\n", global);

    const int N = 100;
    /* N = 200; */   /* erro de compilação: assignment of read-only variable */
    printf("N = %d\n", N);
    return 0;
}
```

---

## 4. Operadores

### Tabela completa com precedência (maior para menor)

| Nível | Operadores | Associatividade |
|---|---|---|
| 15 | `()` `[]` `->` `.` | esquerda → direita |
| 14 | `!` `~` `++` `--` `+` `-` `*` `&` `(tipo)` `sizeof` | **direita → esquerda** (unários) |
| 13 | `*` `/` `%` | esquerda → direita |
| 12 | `+` `-` | esquerda → direita |
| 11 | `<<` `>>` | esquerda → direita |
| 10 | `<` `<=` `>` `>=` | esquerda → direita |
| 9  | `==` `!=` | esquerda → direita |
| 8  | `&` (bit a bit) | esquerda → direita |
| 7  | `^` | esquerda → direita |
| 6  | `\|` | esquerda → direita |
| 5  | `&&` | esquerda → direita |
| 4  | `\|\|` | esquerda → direita |
| 3  | `? :` | **direita → esquerda** |
| 2  | `=` `+=` `-=` `*=` `/=` `%=` `&=` `\|=` `^=` `<<=` `>>=` | **direita → esquerda** |
| 1  | `,` | esquerda → direita |

### Operadores bit a bit — detalhamento

```c
unsigned char a = 0b10110011;   /* 179 decimal */
unsigned char b = 0b11001010;   /* 202 decimal */

a & b    /* AND:  0b10000010 = 130 — bit 1 só se ambos forem 1 */
a | b    /* OR:   0b11111011 = 251 — bit 1 se ao menos um for 1 */
a ^ b    /* XOR:  0b01111001 =  121 — bit 1 se forem diferentes */
~a       /* NOT:  0b01001100 — inverte todos os bits */
a << 2   /* shift esquerdo: multiplica por 4 (se não houver overflow) */
a >> 1   /* shift direito:  divide por 2 (para unsigned; para signed, comportamento definido pela impl.) */
```

**Máscaras de bits — usos comuns:**

```c
/* testar se o bit N está ligado */
if (flags & (1 << N)) { ... }

/* ligar o bit N */
flags |= (1 << N);

/* desligar o bit N */
flags &= ~(1 << N);

/* alternar o bit N */
flags ^= (1 << N);
```

### Operador vírgula

Avalia ambas as expressões da esquerda para a direita; o valor da expressão é o da direita:

```c
int x = (a = 3, b = 4, a + b);   /* x = 7 */
for (int i = 0, j = 10; i < j; i++, j--) { ... }  /* uso comum: múltiplos contadores */
```

### 🔬 Exercício 4 — Divisão inteira, módulo, incremento e bits

```c
#include <stdio.h>

int main(void) {
    int a = 17, b = 5;
    printf("%d / %d = %d\n",  a, b, a / b);   /* 3 — truncamento */
    printf("%d %% %d = %d\n", a, b, a % b);   /* 2 — resto */

    int x = 3;
    int pre = ++x;   /* x=4, pre=4 */
    int pos = x++;   /* pos=4, x=5 */
    printf("pre=%d  pos=%d  x=%d\n", pre, pos, x);

    int max = (a > b) ? a : b;
    printf("max = %d\n", max);

    /* Bit a bit */
    unsigned char flags = 0;
    flags |= (1 << 2);   /* liga bit 2: 0b00000100 = 4 */
    flags |= (1 << 5);   /* liga bit 5: 0b00100100 = 36 */
    printf("flags = %u  (0x%02X)\n", flags, flags);

    flags &= ~(1 << 2);  /* desliga bit 2: 0b00100000 = 32 */
    printf("flags sem bit2 = %u\n", flags);
    return 0;
}
```

---

## 5. Controle de fluxo

### Sintaxe completa

```c
/* if / else if / else */
if (expressão) instrução;
if (expressão) { bloco; } else if (expressão) { bloco; } else { bloco; }

/* switch — expressão deve ser tipo inteiro */
switch (expressão_inteira) {
    case constante1:
        /* instruções */
        break;          /* sem break: cai no próximo case (fall-through) */
    case constante2:
    case constante3:    /* agrupa casos */
        break;
    default:            /* opcional; executa se nenhum case bater */
        break;
}

/* while — testa antes */
while (condição) instrução;

/* do-while — testa depois (executa ao menos uma vez) */
do { instrução; } while (condição);

/* for */
for (init; condição; atualização) instrução;
for (;;) { /* loop infinito */ break; }

/* goto — usar com moderação; útil para sair de loops aninhados */
for (...) {
    for (...) {
        if (erro) goto fim;
    }
}
fim:
    /* tratamento */
```

**Valores de verdade em C:**
- `0`, `0.0`, `NULL`, `'\0'` → **falso**
- Qualquer outro valor → **verdadeiro**
- Não existe tipo `bool` nativo antes de C99; use `<stdbool.h>` para `bool`, `true`, `false`

```c
#include <stdbool.h>
bool encontrado = false;
if (encontrado) { ... }
```

### 🔬 Exercício 5a — if / else if / else

```c
#include <stdio.h>

int main(void) {
    int nota = 72;
    if      (nota >= 90) printf("A\n");
    else if (nota >= 80) printf("B\n");
    else if (nota >= 70) printf("C\n");
    else                 printf("Reprovado\n");
    return 0;
}
```

### 🔬 Exercício 5b — for com break e continue

```c
#include <stdio.h>

int main(void) {
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) continue;
        if (i == 7)     break;
        printf("%d\n", i);
    }
    return 0;
}
```

### 🔬 Exercício 5c — do-while

```c
#include <stdio.h>

int main(void) {
    int n = 1;
    do {
        printf("n = %d\n", n);
        n *= 2;
    } while (n < 32);
    return 0;
}
```

### 🔬 Exercício 5d — switch com fall-through

```c
#include <stdio.h>

int main(void) {
    int dia = 3;
    switch (dia) {
        case 1: case 2: case 3: case 4: case 5:
            printf("Dia util\n");  break;
        case 6: case 7:
            printf("Fim de semana\n"); break;
        default:
            printf("Invalido\n");
    }
    return 0;
}
```

---

## 6. Funções

### Sintaxe completa

```c
/* Protótipo (declaração) — deve aparecer antes do uso */
tipo_retorno nome(tipo param1, tipo param2);
void sem_retorno(void);          /* void: sem parâmetros / sem retorno */
int variadic(int n, ...);        /* variadic: nº variável de argumentos */

/* Definição */
int soma(int a, int b) {
    return a + b;
}

/* Função inline — sugestão ao compilador para evitar chamada de função */
static inline int quadrado(int x) { return x * x; }

/* Ponteiro para função */
int (*op)(int, int);             /* op é um ponteiro para função que recebe dois int e retorna int */
op = soma;
int r = op(3, 4);                /* r = 7 */
```

**Passagem de parâmetros em C:**
- C usa **passagem por valor**: a função recebe uma *cópia* do argumento.
- Para modificar a variável original, passe o *endereço* (ponteiro).
- Arrays são passados como ponteiro para o primeiro elemento — `sizeof` não funciona dentro da função.

```c
void dobra_valor(int x)  { x *= 2; }          /* não modifica o original */
void dobra_ref(int *x)   { *x *= 2; }         /* modifica via ponteiro */

void print_array(int *v, int n) {              /* n precisa ser passado explicitamente */
    for (int i = 0; i < n; i++) printf("%d ", v[i]);
}
```

**Recursão e pilha:**
Cada chamada recursiva cria um novo **frame de ativação** na stack com suas próprias
variáveis locais e parâmetros. Recursão profunda pode causar *stack overflow*.

### 🔬 Exercício 6 — Pilha de chamadas e ponteiro como parâmetro

```c
#include <stdio.h>

int fatorial(int n) {
    if (n <= 1) return 1;
    return n * fatorial(n - 1);
}

void dobra(int *x) { *x *= 2; }

int main(void) {
    printf("5! = %d\n", fatorial(5));

    int v = 7;
    dobra(&v);
    printf("dobro de 7 = %d\n", v);

    /* ponteiro para função */
    int (*fn)(int) = fatorial;
    printf("fn(4) = %d\n", fn(4));   /* 24 */
    return 0;
}
```

---

## 7. Arrays

### Sintaxe e semântica

```c
int v[5];                          /* 5 ints; índices 0 a 4; NÃO inicializado */
int v[5] = {0};                    /* todos zeros */
int v[]  = {10, 20, 30};           /* tamanho inferido: 3 */
int m[2][3] = {{1,2,3},{4,5,6}};   /* matriz 2×3, armazenada em row-major order */

/* Arrays e ponteiros — equivalências fundamentais */
v[i]    ==  *(v + i)               /* indexação = aritmética de ponteiro */
&v[i]   ==  v + i
v       ==  &v[0]                  /* nome do array = ponteiro para 1º elemento */

/* Tamanho de um array local */
int n = sizeof(v) / sizeof(v[0]);  /* funciona apenas no escopo de declaração */
```

**Limitações:**
- Índice fora dos limites → **comportamento indefinido** (C não verifica).
- Arrays não podem ser atribuídos diretamente (`v2 = v1` não copia; use `memcpy`).
- Arrays não podem ser retornados de funções por valor; retorne ponteiro (heap) ou use struct.

**VLA — Variable Length Array (C99):**

```c
void foo(int n) {
    int v[n];    /* tamanho definido em tempo de execução — stack! */
    /* ... */
}               /* VLAs são removidos do escopo ao sair da função */
```

### 🔬 Exercício 7 — Array e matriz

```c
#include <stdio.h>
#include <string.h>

int main(void) {
    int v[5] = {10, 20, 30, 40, 50};
    int soma = 0;
    for (int i = 0; i < 5; i++) soma += v[i];
    printf("soma = %d\n", soma);

    /* cópia de array com memcpy */
    int w[5];
    memcpy(w, v, sizeof(v));
    w[0] = 99;
    printf("v[0]=%d  w[0]=%d\n", v[0], w[0]);   /* 10 e 99 — independentes */

    /* matriz */
    int m[2][3] = {{1, 2, 3}, {4, 5, 6}};
    printf("m[1][2] = %d\n", m[1][2]);   /* 6 */

    /* row-major: elementos consecutivos na memória */
    int *p = &m[0][0];
    for (int i = 0; i < 6; i++) printf("%d ", p[i]);   /* 1 2 3 4 5 6 */
    printf("\n");
    return 0;
}
```

---

## 8. Strings

### Representação e funções

C não tem tipo string — strings são **arrays de `char` terminados por `'\0'`**:

```c
char s1[] = "hello";         /* array: {'h','e','l','l','o','\0'} — 6 bytes */
char *s2  = "hello";         /* ponteiro para literal em memória estática (imutável) */
char s3[20];                 /* buffer de 20 bytes; deve ser preenchido manualmente */
```

**Funções de `<string.h>`:**

| Função | Descrição | Retorno |
|---|---|---|
| `strlen(s)` | comprimento sem `'\0'` | `size_t` |
| `strcpy(dst, src)` | copia src em dst (sem verificar tamanho) | `dst` |
| `strncpy(dst, src, n)` | copia até n bytes; não garante `'\0'` | `dst` |
| `strcat(dst, src)` | concatena src no final de dst | `dst` |
| `strncat(dst, src, n)` | concatena até n bytes | `dst` |
| `strcmp(a, b)` | 0 se iguais; <0 se a<b; >0 se a>b | `int` |
| `strncmp(a, b, n)` | compara até n bytes | `int` |
| `strchr(s, c)` | ponteiro para 1ª ocorrência de c em s | `char*` ou NULL |
| `strstr(s, sub)` | ponteiro para 1ª ocorrência de sub em s | `char*` ou NULL |
| `memset(p, v, n)` | preenche n bytes a partir de p com valor v | `p` |
| `memcpy(dst, src, n)` | copia n bytes de src para dst | `dst` |
| `memmove(dst, src, n)` | como memcpy mas seguro se regiões se sobrepõem | `dst` |

**Conversões string ↔ número (`<stdlib.h>`):**

```c
int   n = atoi("42");           /* string → int */
double d = atof("3.14");        /* string → double */
long  l = strtol("FF", NULL, 16); /* string → long com base (16=hex) */
char buf[20];
sprintf(buf, "%d", 42);         /* int → string */
snprintf(buf, sizeof(buf), "%.2f", 3.14);  /* seguro: limita tamanho */
```

### 🔬 Exercício 8 — Manipulação de strings

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    char s[] = "Brasilia";
    printf("Comprimento: %zu\n", strlen(s));

    for (int i = 0; s[i] != '\0'; i++)
        printf("s[%d]='%c' ASCII=%d\n", i, s[i], (int)s[i]);

    /* comparação */
    printf("strcmp: %d\n", strcmp(s, "Brasilia"));    /* 0 */
    printf("strcmp: %d\n", strcmp(s, "Curitiba"));    /* negativo */

    /* busca */
    char *pos = strchr(s, 'i');
    if (pos) printf("Primeiro 'i' na posição %td\n", pos - s);  /* 5 */

    /* conversão */
    int n = atoi("1234");
    printf("atoi(\"1234\") = %d\n", n);
    return 0;
}
```

---

## 9. Ponteiros

### Sintaxe e semântica completa

```c
int  x  = 10;
int *p  = &x;        /* p guarda o endereço de x; tipo: int* */
*p = 20;             /* derreferência: acessa/modifica o objeto apontado */

/* Ponteiro nulo — "não aponta para nada" */
int *q = NULL;        /* ou: int *q = 0; */
if (q == NULL) { }    /* sempre verificar antes de derreferênciar */

/* const e ponteiros — quatro combinações */
const int *p1 = &x;         /* ponteiro para int constante: *p1 não pode mudar */
int *const p2 = &x;         /* ponteiro constante para int: p2 não pode apontar para outro lugar */
const int *const p3 = &x;   /* ambos constantes */
int *p4 = &x;               /* nenhum constante */

/* Ponteiro void — tipo genérico */
void *vp = &x;               /* aceita qualquer tipo */
int  *ip = (int*)vp;         /* cast necessário para derreferênciar */
```

**Aritmética de ponteiros:**
- `p + n` avança `n * sizeof(*p)` bytes — aponta para o n-ésimo elemento seguinte.
- Só é definida dentro de um array (ou um elemento além do último).
- A diferença entre dois ponteiros para o mesmo array tem tipo `ptrdiff_t`.

```c
int v[5] = {10, 20, 30, 40, 50};
int *p = v;             /* aponta para v[0] */
int *q = v + 3;         /* aponta para v[3] */
ptrdiff_t diff = q - p; /* 3 */
```

**Ponteiro para função:**

```c
int (*cmp)(const void*, const void*);    /* protótipo da função de comparação do qsort */
int comparar(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}
cmp = comparar;
```

### 🔬 Exercício 9a — Ponteiro básico e derreferência

```c
#include <stdio.h>

int main(void) {
    int x = 10;
    int *p = &x;

    printf("x    = %d\n",  x);
    printf("&x   = %p\n",  (void*)&x);
    printf("p    = %p\n",  (void*)p);
    printf("*p   = %d\n",  *p);

    *p = 99;
    printf("x apos *p=99: %d\n", x);
    return 0;
}
```

### 🔬 Exercício 9b — Aritmética de ponteiros

```c
#include <stdio.h>
#include <stddef.h>

int main(void) {
    int v[4] = {10, 20, 30, 40};
    int *p = v;

    printf("*p     = %d\n", *p);
    printf("*(p+1) = %d\n", *(p+1));
    printf("*(p+2) = %d\n", *(p+2));

    int *q = v + 3;
    ptrdiff_t diff = q - p;
    printf("q - p  = %td\n", diff);   /* 3 */

    p++;
    printf("apos p++: *p = %d\n", *p);   /* 20 */
    return 0;
}
```

### 🔬 Exercício 9c — Ponteiro para ponteiro

```c
#include <stdio.h>

int main(void) {
    int   x  = 42;
    int  *p  = &x;
    int **pp = &p;

    printf("x   = %d\n",   x);
    printf("*p  = %d\n",  *p);
    printf("**pp= %d\n", **pp);

    **pp = 100;
    printf("x apos **pp=100: %d\n", x);
    return 0;
}
```

---

## 10. Alocação dinâmica

### Funções de `<stdlib.h>`

```c
void *malloc(size_t bytes);          /* aloca bytes no heap; conteúdo indeterminado */
void *calloc(size_t n, size_t sz);   /* aloca n elementos de sz bytes; inicializa com 0 */
void *realloc(void *p, size_t bytes);/* redimensiona bloco; pode mover; antigo fica inválido */
void  free(void *p);                 /* libera bloco; p deve vir de malloc/calloc/realloc */
```

**Regras essenciais:**
- Sempre verificar se o retorno é `NULL` (falha de alocação).
- Cada `malloc`/`calloc` deve ter exatamente um `free`.
- Não acesse memória após `free` (*use-after-free*).
- Não chame `free` duas vezes no mesmo ponteiro (*double-free*).
- Após `free`, atribua `NULL` ao ponteiro para evitar uso acidental.

```c
/* Padrão idiomático */
int *v = malloc(n * sizeof(*v));    /* sizeof(*v) em vez de sizeof(int) — mais seguro */
if (!v) { perror("malloc"); exit(1); }
/* usar v ... */
free(v);
v = NULL;
```

**Stack vs. Heap:**

| | Stack | Heap |
|---|---|---|
| Gerenciamento | automático (compilador) | manual (`malloc`/`free`) |
| Tamanho | limitado (~1–8 MB) | limitado pela RAM disponível |
| Velocidade | muito rápido | mais lento (busca de bloco livre) |
| Duração | até sair do bloco | até `free` ou fim do processo |
| Erros comuns | stack overflow | memory leak, double-free, use-after-free |

### 🔬 Exercício 10 — Heap vs. Stack e realloc

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n = 4;
    int *v = calloc(n, sizeof(int));   /* heap, inicializado com 0 */
    if (!v) { perror("calloc"); return 1; }

    for (int i = 0; i < n; i++) v[i] = (i + 1) * 10;
    for (int i = 0; i < n; i++) printf("v[%d]=%d\n", i, v[i]);

    /* expandir para 6 elementos */
    n = 6;
    int *tmp = realloc(v, n * sizeof(int));
    if (!tmp) { free(v); perror("realloc"); return 1; }
    v = tmp;
    v[4] = 50; v[5] = 60;
    for (int i = 0; i < n; i++) printf("v[%d]=%d\n", i, v[i]);

    free(v);
    v = NULL;
    return 0;
}
```

---

## 11. Structs e Unions

### Sintaxe completa

```c
/* Definição */
struct Ponto { int x; int y; };

/* Com typedef — elimina a necessidade de escrever 'struct' a cada uso */
typedef struct {
    float re;
    float im;
} Complexo;

/* Struct aninhada */
typedef struct {
    char nome[50];
    struct { int dia; int mes; int ano; } nasc;
} Pessoa;

/* Acesso */
Ponto p  = {3, 4};
p.x = 10;                    /* acesso direto */

Ponto *pp = &p;
pp->x = 10;                  /* equivale a (*pp).x = 10 */

/* Struct como valor — C copia o conteúdo inteiro na atribuição e passagem para função */
Complexo a = {1.0f, 2.0f};
Complexo b = a;              /* cópia independente */
```

**Padding e alinhamento:**
O compilador pode inserir bytes de preenchimento (*padding*) entre membros para
satisfazer requisitos de alinhamento do processador:

```c
struct Ex {
    char  c;   /* 1 byte + 3 bytes padding */
    int   i;   /* 4 bytes */
    char  d;   /* 1 byte + 3 bytes padding */
};             /* sizeof(struct Ex) pode ser 12, não 6 */

/* Para empacotar sem padding (útil em protocolos de rede): */
struct __attribute__((packed)) Ex2 { char c; int i; char d; };
```

**Bit fields** — membros com número de bits controlado:

```c
typedef struct {
    unsigned int ativo  : 1;   /* 1 bit */
    unsigned int nivel  : 3;   /* 3 bits (0–7) */
    unsigned int codigo : 12;  /* 12 bits */
} Flags;
```

### 🔬 Exercício 11a — Struct com ponteiro

```c
#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[30];
    int  x, y;
} Ponto;

float dist2(const Ponto *a, const Ponto *b) {
    int dx = a->x - b->x, dy = a->y - b->y;
    return (float)(dx*dx + dy*dy);
}

int main(void) {
    Ponto origem = {"origem", 0, 0};
    Ponto p      = {"p",      3, 4};

    printf("%s: (%d,%d)\n", p.nome, p.x, p.y);

    Ponto *ptr = &p;
    ptr->x = 10;
    printf("apos ptr->x=10: p.x=%d\n", p.x);

    printf("dist2(origem,p)=%.0f\n", dist2(&origem, &p));

    /* struct como valor — cópia independente */
    Ponto q = p;
    q.x = 99;
    printf("p.x=%d  q.x=%d\n", p.x, q.x);   /* 10 e 99 */
    return 0;
}
```

### 🔬 Exercício 11b — Union: membros compartilham memória

```c
#include <stdio.h>

union Dado { int i; float f; char c; };

int main(void) {
    union Dado d;
    d.i = 65;
    printf("d.i='%d'  d.c='%c'\n", d.i, d.c);   /* 65 e 'A' — mesmos bytes */
    d.f = 3.14f;
    printf("d.f=%.2f\n", d.f);   /* d.i agora tem valor indefinido */
    return 0;
}
```

---

## 12. Enums

### Sintaxe e semântica

```c
/* Enum simples — valores implícitos: 0, 1, 2, … */
enum Cor { VERMELHO, VERDE, AZUL };

/* Valores explícitos — os seguintes incrementam a partir do último explícito */
typedef enum { DOM=0, SEG=1, TER=2, QUA=3, QUI=4, SEX=5, SAB=6 } DiaSemana;

/* Enum como máscara de bits (potências de 2) */
typedef enum {
    LEITURA   = 1 << 0,   /* 1 */
    ESCRITA   = 1 << 1,   /* 2 */
    EXECUCAO  = 1 << 2,   /* 4 */
} Permissao;

/* Uso */
Permissao p = LEITURA | ESCRITA;   /* 3 */
if (p & ESCRITA) printf("pode escrever\n");
```

Enums são tipos inteiros — o compilador pode escolher `int` ou menor. Casts
explícitos são necessários para converter `int` de volta para enum.

### 🔬 Exercício 12 — Enum com switch e flags

```c
#include <stdio.h>

typedef enum { DOM=0, SEG, TER, QUA, QUI, SEX, SAB } DiaSemana;

const char *nome_dia(DiaSemana d) {
    switch (d) {
        case DOM: return "Domingo";
        case SEG: return "Segunda";
        case TER: return "Terca";
        case QUA: return "Quarta";
        case QUI: return "Quinta";
        case SEX: return "Sexta";
        case SAB: return "Sabado";
        default:  return "???";
    }
}

typedef enum { LEITURA=1, ESCRITA=2, EXECUCAO=4 } Permissao;

int main(void) {
    for (DiaSemana d = DOM; d <= SAB; d++)
        printf("%d = %s\n", d, nome_dia(d));

    Permissao p = LEITURA | EXECUCAO;   /* 5 */
    printf("\nPermissões: leitura=%s escrita=%s execução=%s\n",
           (p & LEITURA)  ? "sim" : "não",
           (p & ESCRITA)  ? "sim" : "não",
           (p & EXECUCAO) ? "sim" : "não");
    return 0;
}
```

---

## 13. Entrada / Saída básica

### Formatadores de `printf` e `scanf`

| Especificador | Tipo | Exemplo |
|---|---|---|
| `%d`, `%i` | `int` | `42`, `-7` |
| `%u` | `unsigned int` | `255` |
| `%ld` | `long` | `100000L` |
| `%lld` | `long long` | `9LL` |
| `%f` | `float`/`double` (printf) | `3.14` |
| `%lf` | `double` (scanf) | `3.14` |
| `%e`, `%E` | notação científica | `3.14e+00` |
| `%g` | mais curto entre `%f` e `%e` | `3.14` |
| `%c` | `char` | `'A'` |
| `%s` | `char*` (string) | `"hello"` |
| `%p` | ponteiro | `0x7fff...` |
| `%x`, `%X` | hexadecimal | `ff`, `FF` |
| `%o` | octal | `377` |
| `%zu` | `size_t` | `8` |
| `%td` | `ptrdiff_t` | `3` |
| `%%` | literal `%` | `%` |

**Flags de formatação:**

```c
printf("%10d",   42);   /* "        42" — alinhado à direita, largura 10 */
printf("%-10d",  42);   /* "42        " — alinhado à esquerda */
printf("%010d",  42);   /* "0000000042" — preenchido com zeros */
printf("%+d",    42);   /* "+42"        — sinal explícito */
printf("%.5f",  3.14);  /* "3.14000"    — 5 casas decimais */
printf("%8.2f", 3.14);  /* "    3.14"   — largura 8, 2 decimais */
```

**E/S de arquivo:**

```c
FILE *f = fopen("dados.txt", "r");   /* "r"=leitura, "w"=escrita, "a"=append, "rb"=binário */
if (!f) { perror("fopen"); exit(1); }

char linha[256];
while (fgets(linha, sizeof(linha), f)) { /* lê linha por linha */
    /* processar linha */
}

fprintf(f, "%d\n", valor);   /* escreve formatado no arquivo */
fclose(f);
```

### 🔬 Exercício 13 — Formatação e E/S de arquivo

```c
#include <stdio.h>

int main(void) {
    int    i = 255;
    double f = 3.14159;
    char   s[] = "Brasilia";

    printf("Decimal:     %d\n",    i);
    printf("Hex:         %x\n",    i);      /* ff */
    printf("Octal:       %o\n",    i);      /* 377 */
    printf("Float:       %.4f\n",  f);
    printf("Cientifico:  %e\n",    f);
    printf("Alinhado:    %10.2f\n",f);      /* "      3.14" */
    printf("String:      %-10s|\n",s);      /* "Brasilia  |" */
    printf("Ponteiro:    %p\n",    (void*)s);

    /* Escrever e ler arquivo */
    FILE *fw = fopen("/tmp/teste.txt", "w");
    if (fw) {
        fprintf(fw, "%d %.2f %s\n", i, f, s);
        fclose(fw);
    }

    FILE *fr = fopen("/tmp/teste.txt", "r");
    if (fr) {
        int n; double d; char t[50];
        fscanf(fr, "%d %lf %49s", &n, &d, t);
        printf("lido: %d %.2f %s\n", n, d, t);
        fclose(fr);
    }
    return 0;
}
```

---

## 14. Pré-processador

### Diretivas

```c
/* Inclusão de headers */
#include <stdio.h>          /* busca nos diretórios de sistema */
#include "meu_header.h"     /* busca primeiro no diretório atual */

/* Constantes e macros */
#define PI            3.14159265358979
#define QUADRADO(x)   ((x)*(x))           /* sempre com parênteses! */
#define MAX(a,b)      ((a)>(b)?(a):(b))   /* cuidado: avalia a e b duas vezes */
#define STRINGIFY(x)  #x                  /* converte token em string */
#define CONCAT(a,b)   a##b                /* concatenação de tokens */
#undef PI                                 /* remove definição */

/* Compilação condicional */
#ifdef DEBUG
    #define LOG(msg) printf("[DEBUG] %s:%d %s\n", __FILE__, __LINE__, msg)
#else
    #define LOG(msg)   /* macro vazia — sem overhead em release */
#endif

#if defined(_WIN32)
    /* código Windows */
#elif defined(__linux__)
    /* código Linux */
#endif

/* Macros predefinidas */
__FILE__     /* nome do arquivo fonte (string) */
__LINE__     /* linha atual (int) */
__DATE__     /* data de compilação (string) */
__TIME__     /* hora de compilação (string) */
__func__     /* nome da função atual (C99) */
```

**Guard de inclusão** — evita inclusão múltipla do mesmo header:

```c
/* meu_header.h */
#ifndef MEU_HEADER_H
#define MEU_HEADER_H

/* declarações ... */

#endif /* MEU_HEADER_H */
```

### 🔬 Exercício 14 — Macros e compilação condicional

```c
#include <stdio.h>

#define PI            3.14159
#define QUADRADO(x)   ((x)*(x))
#define MAX(a,b)      ((a)>(b)?(a):(b))

#define DEBUG 1
#ifdef DEBUG
    #define LOG(msg)  printf("[%s:%d] %s\n", __FILE__, __LINE__, msg)
#else
    #define LOG(msg)
#endif

int main(void) {
    double r = 5.0;
    printf("Área r=5: %.2f\n", PI * QUADRADO(r));

    int a = 7, b = 3;
    printf("MAX(%d,%d) = %d\n", a, b, MAX(a,b));

    LOG("iniciando cálculo");   /* só aparece se DEBUG estiver definido */

    printf("Compilado em %s às %s\n", __DATE__, __TIME__);
    return 0;
}
```

---

## 15. Escopo e duração

### Tabela completa

| Classe de armazenamento | Onde declarada | Duração | Escopo | Inicialização padrão |
|---|---|---|---|---|
| `auto` (padrão) | dentro de função/bloco | bloco | bloco | **indeterminada** |
| `static` local | dentro de função/bloco | programa inteiro | bloco | zero |
| `static` global | fora de funções | programa inteiro | arquivo `.c` | zero |
| `extern` | fora de funções | programa inteiro | múltiplos arquivos | zero |
| `register` | dentro de função | bloco | bloco | indeterminada |

**Regras de visibilidade:**
- Um identificador em escopo interno **oculta** (*shadows*) um de mesmo nome em escopo externo.
- Variáveis globais `static` são visíveis **apenas no arquivo** onde são declaradas.
- `extern` **declara** sem **definir**: a definição deve existir em exatamente um arquivo `.c`.

### 🔬 Exercício 15a — Escopo de bloco e shadowing

```c
#include <stdio.h>

int global = 100;   /* escopo global, duração: programa inteiro */

int main(void) {
    int x = 1;
    printf("x externo = %d\n", x);
    printf("global    = %d\n", global);

    {
        int x = 2;   /* shadows o x externo */
        int global = 999;  /* shadows a global */
        printf("x interno  = %d\n", x);
        printf("global local = %d\n", global);
    }   /* x=2 e global local desaparecem aqui */

    printf("x apos bloco = %d\n", x);       /* 1 */
    printf("global       = %d\n", global);  /* 100 */
    return 0;
}
```

### 🔬 Exercício 15b — Variável `static` local

```c
#include <stdio.h>

void contador(void) {
    static int n = 0;   /* inicializado UMA VEZ; persiste entre chamadas */
    n++;
    printf("chamada %d\n", n);
}

int main(void) {
    contador(); contador(); contador();   /* 1, 2, 3 */
    return 0;
}
```

---

## 16. Boas práticas resumidas

- **Inicialize** todas as variáveis antes de usar.
- **Verifique retornos** de `malloc`, `fopen`, `scanf` — nunca assuma sucesso.
- **Todo `malloc` tem um `free`** — use ferramentas como Valgrind ou `-fsanitize=address`.
- **Prefira `strncpy`/`snprintf`** a `strcpy`/`sprintf` — evita buffer overflow.
- Use **`const`** sempre que um parâmetro ponteiro não será modificado.
- **Compile com `-Wall -Wextra`** e resolva todos os avisos antes de entregar.
- **Guard de inclusão** em todo arquivo `.h` — evita erros de inclusão múltipla.
- Prefira **`sizeof(*p)`** a `sizeof(tipo)` em chamadas de `malloc` — mais seguro se o tipo mudar.
- Atribua **`NULL`** ao ponteiro após `free` — evita *use-after-free* acidental.

### 🔬 Exercício 16 — Estouro de buffer detectado com segurança

```c
#include <stdio.h>
#include <string.h>

int main(void) {
    char destino[8];

    /* SEGURO: limita a cópia ao tamanho do buffer */
    strncpy(destino, "Brasilia-DF", sizeof(destino) - 1);
    destino[sizeof(destino) - 1] = '\0';   /* garante terminador */

    printf("destino = '%s'\n", destino);   /* "Brasili" */
    printf("strlen  = %zu\n",  strlen(destino));   /* 7 */

    /* ALTERNATIVA SEGURA com snprintf */
    char buf[16];
    int  n = snprintf(buf, sizeof(buf), "valor=%d", 12345);
    if (n >= (int)sizeof(buf)) printf("truncado!\n");
    printf("buf = '%s'\n", buf);
    return 0;
}
```

---

## 17. Ponteiros para funções e callbacks *(seção adicional)*

Ponteiros para funções permitem passar comportamento como argumento — base de
padrões como *strategy*, *callback* e ordenação genérica.

```c
/* Tipo de ponteiro para função */
typedef int (*Comparador)(const void *, const void *);

/* qsort da stdlib usa exatamente esse padrão */
void qsort(void *base, size_t n, size_t sz, Comparador cmp);
```

### 🔬 Exercício 17 — qsort e ponteiro para função

```c
#include <stdio.h>
#include <stdlib.h>

int cmp_int_asc(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int cmp_int_desc(const void *a, const void *b) {
    return *(int*)b - *(int*)a;
}

void print_array(int *v, int n) {
    for (int i = 0; i < n; i++) printf("%d ", v[i]);
    printf("\n");
}

int main(void) {
    int v[] = {40, 10, 30, 50, 20};
    int n   = sizeof(v) / sizeof(v[0]);

    qsort(v, n, sizeof(int), cmp_int_asc);
    printf("Crescente:  "); print_array(v, n);

    qsort(v, n, sizeof(int), cmp_int_desc);
    printf("Decrescente:"); print_array(v, n);

    /* Array de ponteiros para função */
    int (*ops[])(const void*, const void*) = { cmp_int_asc, cmp_int_desc };
    qsort(v, n, sizeof(int), ops[0]);
    printf("Crescente:  "); print_array(v, n);
    return 0;
}
```

---

## 18. Listas ligadas — estrutura recursiva com ponteiros *(seção adicional)*

Demonstram ponteiros, structs, alocação dinâmica e recursão em conjunto.

### 🔬 Exercício 18 — Lista simplesmente ligada

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int        valor;
    struct No *proximo;   /* ponteiro para o próprio tipo — struct recursiva */
} No;

No *criar_no(int valor) {
    No *n = malloc(sizeof(No));
    if (!n) { perror("malloc"); exit(1); }
    n->valor    = valor;
    n->proximo  = NULL;
    return n;
}

void inserir_frente(No **cabeca, int valor) {
    No *novo    = criar_no(valor);
    novo->proximo = *cabeca;
    *cabeca     = novo;
}

void imprimir(const No *cabeca) {
    for (const No *p = cabeca; p; p = p->proximo)
        printf("%d -> ", p->valor);
    printf("NULL\n");
}

void liberar(No *cabeca) {
    while (cabeca) {
        No *prox = cabeca->proximo;
        free(cabeca);
        cabeca = prox;
    }
}

int main(void) {
    No *lista = NULL;
    inserir_frente(&lista, 30);
    inserir_frente(&lista, 20);
    inserir_frente(&lista, 10);
    imprimir(lista);   /* 10 -> 20 -> 30 -> NULL */
    liberar(lista);
    lista = NULL;
    return 0;
}
```

**O que observar no PythonTutor:** cada nó aparece no heap como uma caixa com dois
campos; `proximo` é uma seta que encadeia os nós; `cabeca` em `main` aponta para o
primeiro.

---

> **Dica de uso no PythonTutor:**
> - Ative **"Show all frames"** para ver funções recursivas empilhando.
> - Ative **"Render memory"** → "Show in compact mode" para arrays grandes.
> - Use o link **"Generate permanent link"** para salvar e compartilhar um exercício.
>
> **Compilar localmente com detecção de erros:**
> ```bash
> gcc -Wall -Wextra -std=c11 -fsanitize=address,undefined -g -o prog prog.c
> ```
