# Monitoramento de Memória

O trabalho em questão consiste em monitorar a memória de um computador com sistema operacional linux e imprimir no terminal
os processos em ordem decrescente de acordo com o uso da memória no momento. Assim é feito o monitoramente de quanta memória cada
processo utiliza, além de observar o swapping e as faltas de páginas de cada processo. Também é feito o monitoramento considerando
a memória total.

# Compilação

g++ -std=c++11 -pthread memoria.cpp -o memoria

# Execução

./memoria /proc


