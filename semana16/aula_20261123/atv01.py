# Gabriel Peres de Oliveira - Atv 01

# Atv 01 – Console. No >>>, calcule 17 / 5, 17 // 5, 17 % 5 e 2 ** 10.
# Anote o resultado e explique a diferença entre / e // em comparação
# com a divisão inteira do C.

x = 17 / 5
print("17 / 5 =", x)

y = 17 // 5
print("17 // 5 =", y)

z = 17 % 5
print("17 % 5 =", z) 

w = 2 ** 10
print("2 ** 10 =", w)


# Em Python, o operador / representa a divisão real e sempre retorna um float.
# Já o operador // representa da divisão inteira, descartando a parte fracionada.
# Em C, não existe um operador como // e o operador / representa uma divisão,
# que depende das suas entradas: se forem dois números inteiros, o resultado é
# um inteiro; se um dos números for float o resultado será um float.
