# Projeto de Sistemas em Tempo Real

### Professor: Felipe Viel
### Acadêmicos: Fábio Ivo, Sérgio Venturi e Thiago Melato

## Descrição do Projeto

Este projeto visa desenvolver um sistema de monitoramento e controle de subsistemas de um veículo, atendendo a requisitos temporais específicos. O software foi desenvolvido em C e utiliza multithreading para melhorar o desempenho e garantir a qualidade do monitoramento e controle dos subsistemas.

## Requisitos

- C
- Bibliotecas: <pthread.h>
               <stdio.h>
               <stdlib.h>
               <unistd.h>
               "termios_util.h"
- Linux ou MacOS

## Estrutura do Projeto

    .
    ├── build
    ├── include
    │   └── README
    ├── lib
    │   └── README
    ├── platformio.ini
    ├── src
    │   └── main.cpp
    └── test
        └── README
        
# Instruções de Execução

Para compilar e executar o código, siga as etapas abaixo:

1. Abra um terminal.

2. Navegue até o diretório raiz do projeto onde se encontram os arquivos fonte, utilizando o comando `cd`:
   ```sh
   cd /caminho/para/o/diretorio/do/projeto

3. Compile o código-fonte usando o GCC com o seguinte comando:
  ```
  gcc -o central Systems/lvt_system.c Systems/brake_system.c Systems/motor_system.c Systems/life_support_equipment_system.c Utils/termios_util.c central_on_board_computer.c -lpthread
```

4. Isso criará um arquivo executável chamado central.
Agora você pode executar o programa com o comando:
```
  ./central
```
5. Certifique-se de que todas as dependências necessárias, como bibliotecas ou arquivos de inclusão, estejam corretamente configuradas no seu sistema antes de compilar o código. Além disso, certifique-se de ter as permissões adequadas para compilar e executar o programa.







