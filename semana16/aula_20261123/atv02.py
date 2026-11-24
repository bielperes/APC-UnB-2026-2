# Gabriel Peres de Oliveira - Atv 02

# Atv 02 – Tipos dinâmicos. Faça x = 10, depois x = 2.5, depois x = "dez",
# chamando type(x) após cada uma. Por que isso daria erro em C? 

x = 10
print(type(x))

x = 2.5
print(type(x))

x = "dez"
print(type(x))

# Em C, a declaração de um variável é do tipo estática. Você é obrigado a
# declarar o tipo da variável antes de usar e o programa mantém aquele tipo
# até o final da execução do programa. Já em Python, essa declaração é dinâmica
# e pode variar no decorrer do programa (conforme os exemplos dessa atividade).
