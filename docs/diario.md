# Diário da Atividade

## Ambiente

- **Versão do OpenCode:** opencode – v1.18.31
- **Modelo usado:** Big Pickle (OpenCode Zen)

## Parte 1: antes de programar

- **O que cada classe guarda:**
  - `Astronauta`: CPF, nome, idade, estado de vida e disponibilidade.
  - `Voo`: código, estado do voo, vetor de CPFs da tripulação, além de `quantidadeDuracao` e `unidadeDuracao`.
  - `Agência`: vetor de astronautas e vetor de voos.

- **O que acontece em `LANCAR_VOO`, em palavras:**
  Busca o voo pelo código, verifica se ele está planejado e se tem astronautas cadastrados. Em seguida, percorre a lista de CPFs da tripulação conferindo se todos estão vivos e disponíveis. Se todos passarem nas validações, altera a disponibilidade de cada astronauta.

- **Uma dúvida que eu tinha antes de começar:**
  Como gerenciar a alteração de disponibilidade dos astronautas ao lançar ou finalizar um voo.

---

## Parte 1: uso de IA para entender algo

- **O que perguntei (ou "não usei"):**
  Perguntei sobre os avisos do compilador ao comparar variáveis `int` com `vector.size()`.

- **O que aprendi:**
  Que `vector.size()` retorna o tipo `size_t` e que a comparação direta com `int` gera aviso do compilador.

---

## Primeiro contato: revisão sem editar

- **As três melhorias que a IA sugeriu, em uma linha cada:**
  - Substituir strings de estado por `enum class`.
  - Retornar strings por `const&` e marcar getters com `const`.
  - Centralizar as validações repetidas da agência.

- **A que escolhi e por quê:** 
  Escolhi a melhoria 2, por ser mais fácil e segura de implementar. Altera apenas a assinatura dos métodos sem mexer na lógica ou na saída do programa, garantindo que não vão ter erros nos testes.

- **O que mudou no código, e se os seis testes continuaram passando:** 
  Mudou os parâmetros do tipo string nos construtores e métodos, que passaram a receber por referência constante (`const string&`). Sim, os testes continuam passando.

- **O que entendi que não sabia antes:** 
  Que ao passar ou retornar uma string por valor simples, o C++ cria uma cópia inteira do texto na memória, o que gera um consome um recurso desnecessário.

---

## Missão 1: LISTAR_ASTRONAUTAS e HISTORICO

- **Primeira mensagem (o pedido do plano):**

> "Este programa em C++11 controla astronautas e voos de uma agência espacial. Ele lê comandos da entrada padrão. As classes Astronauta, Voo e Agencia estão no código. Os testes da Parte 1 passam. Quero dois comandos novos: LISTAR_ASTRONAUTAS e HISTORICO cpf.
> 
> LISTAR_ASTRONAUTAS mostra todos os astronautas em três grupos, na ordem de cadastro dentro de cada grupo:
> disponiveis: vivos que não estão em nenhum voo em curso.
> em voo: vivos que estão em um voo em curso, com o código desse voo.
> mortos: os mortos. Grupo vazio mostra (nenhum).
> [exemplo de saida]
> 
> HISTORICO cpf mostra os voos dos quais o astronauta participou (lançados com ele a bordo), com o estado atual de cada um, na ordem de cadastro dos voos. Voo só planejado não aparece. Sem voos: (nenhum voo). CPF desconhecido: ERRO: astronauta 999 nao cadastrado.
> [exemplo de saída]
> 
> Não mude nenhum comando que já existe nem a saída deles. Não use nada fora da biblioteca padrão. Vou conferir com bash testes/testar.sh missao1 e depois com bash testes/testar.sh parte1.
> Antes de editar, me diga quais arquivos e quais métodos você vai criar ou alterar, e por quê."

- **O plano que a IA apresentou, resumido:**
  Criou os métodos `listarAstronautas()` e `historico(cpf)` na classe `Agencia`, percorrendo os vetores internos para agrupar astronautas (disponiveis, em voo, mortos) e filtrar o histórico de voos não planejado.

- **Mudei algo no plano antes de liberar?** 
  Não.

- **Resultado de `testar.sh missao1` e de `testar.sh parte1`:** 
  Os dois passaram de primeira.

- **Precisei refazer? O que mudou no pedido:** 
  Não precisei refazer.

---

## Missão 2: SALVAR e CARREGAR

- **Primeira mensagem:**

> "Este programa em C++11 controla astronautas e voos de uma agência espacial. Ele lê comandos da entrada padrão. As classes Astronauta, Voo e Agencia estão no código. Os testes da Parte 1 e da Missão 1 passam.
> 
> Quero dois comandos novos: SALVAR nome_do_arquivo e CARREGAR nome_do_arquivo.
> 
> SALVAR nome_do_arquivo grava todos os dados em um arquivo de texto e imprime: OK: dados salvos em nome_do_arquivo Se não conseguir abrir o arquivo para escrita: ERRO: nao foi possivel salvar em nome_do_arquivo
> 
> CARREGAR nome_do_arquivo substitui todos os dados atuais pelos do arquivo e imprime: OK: dados carregados de nome_do_arquivo Se o arquivo não existir: ERRO: nao foi possivel carregar de nome_do_arquivo (e os dados atuais continuam como estavam).
> 
> O formato do arquivo de texto fica a seu critério, desde que permita reconstruir totalmente o estado dos astronautas (vivo/disponível) e dos voos (estado e lista de CPFs).
> 
> Não mude nenhum comando que já existe nem a saída deles. Não use nada fora da biblioteca padrão. Vou conferir com bash testes/testar.sh missao2 e depois com bash testes/testar.sh parte1.."

- **O plano, resumido:**
  Implementar os métodos `salvar()` e `carregar()` usando `ofstream` e `ifstream` para gravar e ler em arquivo de texto formatado o número total de astronautas e voos e suas respectivas propriedades.

- **O formato do arquivo (cole cinco linhas do `dados_teste.txt`):**
  ```text
  ASTRONAUTAS 2
  111 30 1 1 Ana Maria 
  222 35 1 1 Bruno Costa
  VOOS 1
  10 1 111 0 - planejado

- **Resultado de testar.sh missao2 e de testar.sh parte1:**
Os dois passaram de primeira.

- **Precisei refazer? O que mudou no pedido:**
Não precisei refazer.

### Missão 3: RELATORIO
- **Primeira mensagem:**

> "Este programa em C++11 controla astronautas e voos de uma agência espacial. Ele lê comandos da entrada padrão. As classes estão no código e os testes anteriores passam. Quero um comando novo: RELATORIO. Ele deve imprimir a linha RELATORIO seguida de nove linhas com o estado atual do sistema, exatamente neste formato:
>
>
> [exemplo de saída no formato]
> Regras:
> A experiência de um astronauta é o número de voos já lançados em que ele estava a bordo (voo planejado não conta; astronauta morto continua contando). Em caso de empate, vale o cadastrado primeiro. Se ninguém voou: astronauta mais experiente: (nenhum).
>
> Taxa de sucesso é a parte inteira de (sucessos * 100) / finalizados, onde finalizados = com sucesso + com explosão. Sem voos finalizados: taxa de sucesso: (nenhum voo finalizado).
>
> Atenção: Garanta que os dados carregados do arquivo (da Missão 2) reconstruam a experiência corretamente para que o relatório permaneça consistente após o CARREGAR.
>
> Não mude nenhum comando existente. Não use nada fora da biblioteca padrão C++11. Vou conferir com bash testes/testar.sh missao3 e bash testes/testar.sh parte1."

- **O plano, resumido:**
  Criar o método relatorio() na classe Agencia para calcular os contadores de voos em cada estado, o número de astronautas vivos/mortos, identificar o astronauta com maior participação em voos lançados e calcular a taxa de sucesso inteira.

- **Resultado de testar.sh missao3 e de testar.sh parte1:**
  Os dois passaram de primeira.

- **Precisei refazer? O que mudou no pedido:**
  Não precisei refazer.

## Missão 4: livre
- **O que escolhi e por quê:**
  Criei o comando DEFINIR_DURACAO para registrar e exibir a duração esperada de uma missão (em dias, meses ou anos), adicionando uma funcionalidade útil ao sistema sem alterar a lógica dos comandos que já existiam ou quebrar os testes feitos.

- **O comando novo, a saída que eu esperava e o nome do meu arquivo de comandos (escritos antes de pedir):**
  Comando: DEFINIR_DURACAO 10 6 meses

  Saída esperada: OK: duracao do voo 10 definida para 6 meses

  Estrutura do arquivo de teste: testes/missao4

- **Primeira mensagem:**
> "Este programa em C++11 controla astronautas e voos de uma agência espacial. As classes estão no código e todos os testes anteriores passam. Quero implementar a seguinte funcionalidade nova para a Missão 4 sem alterar nenhuma regra ou mensagem dos comandos existentes: o comando DEFINIR_DURACAO codigo quantidade unidade.
>
> Regras:
>
> O comando recebe o codigo do voo (inteiro), a quantidade (inteiro) e a unidade (string: "dias", "meses" ou "anos").
> 
> Se o voo não existir: ERRO: voo codigo nao cadastrado
>
> Se a quantidade for menor ou igual a 0: ERRO: duracao deve ser maior que zero
>
> Se a unidade for diferente de "dias", "meses" ou "anos": ERRO: unidade invalida (use dias, meses ou anos)
>
> Se o voo existir e os dados forem válidos, registra a duração e imprime: OK: duracao do voo codigo definida para X unidade (Exemplo:
>OK: duracao do voo 10 definida para 6 meses)
>
> Exibição: Atualize apenas o comando LISTAR_VOOS para que, se o voo tiver uma duração definida, ele exiba (duracao: X unidade) logo após o código do voo. Se o voo não tiver duração definida, a exibição do LISTAR_VOOS deve continuar exatamente igual ao que é hoje, para não impactar os cenários padrão.
>
> Atenção:
>
> Não altere o funcionamento nem as mensagens de erro de nenhum outro comando existente.
>Garanta que a duração seja salva e carregada corretamente pelos comandos SALVAR e CARREGAR.
>Mantenha o código estritamente dentro da biblioteca padrão C++11."

- **O que veio, comparado com o que eu esperava:**
  Ele fez a função que eu precisava, porém ele não criou os arquivos missão 4 para testes, então acabei tendo que pedir, ele criou o arquivo .in porém não o .out, pedi novamente e ele acabou fazendo o que foi pedido.

- **testar.sh parte1 continuou passando?**
  Sim, continua passando normalmente.

- **Aceitei, ajustei ou descartei? Por quê:**
Aceitei e fiz mais alguns ajustes para que os testes passassem e a função funcionasse.

## Fechamento
- **O que a IA fez que eu não conseguiria fazer sozinho nesse prazo:**
  Me ajudou bastante na parte de salvar e carregar os dados em arquivos e a criar o comando DEFINIR_DURACAO. Outra coisa muito útil foi que ela descobriu o que estava causando erros no meu código e onde estava as falhas nos testes.

- **Onde ela errou ou fez algo que eu não pedi:**
  Na Missão 4, ela não criou os arquivos de teste e quando criou tentou rodar o teste pela primeira vez, o arquivo .out acabou ficando de fora.

- **O que eu faria diferente da próxima vez:**
  Pediria para a IA criar a pasta de testes com o arquivo .in e .out, prestar mais atenção na falta de detalhe ao pedir algo.