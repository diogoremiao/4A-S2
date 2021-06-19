# Respostas Teste Modelo

## Pergunta 1

Há duas formas de proceder para alinhar a trama. No alinhamento em série quando o sistema se encontra desalinhado, ele inicia a procura da palavra de alinhamento bit a bit. Depois procede apenas a procurar a palavra de trama em trama.

O alinhamento em paralelo tem o mesmo principio, no entanto inicia uma nova maquina de estados sempre que encontra a palavra de alinhamento. Quando uma dessas máquinas estiver alinhada, o sistema fica alinhado e a procura passa para trama a trama.

Alinhamento CRC

Alinhamento CRC (Cycle Redundancy Check) é um mecanismo que permite detetar erros de transmissão de trama e impede falsos alinhamentos.
Baseia-se em atribuir uma sequência de bits à palavra a transmitir. Os resultados da divisão polinomial na chegada e partida têm que ser iguais.
O alinhamento é baseado num threshold de erros (91.4%). Quando s\ao detetas mais que o threshold de erros definido, o sistema encontra-se desalinhado. Para voltar a alinhar é preciso detetar a palavra de alinhamento 2 vezes e o bit 2 de alternância, assim como 2 CRC corretos em 4.

## Pergunta 2

Um indicador é o CRC, que se tiver uma percentagem de erros muito grande indica uma avaria no sistema.
Outro é o delay, que pode indicar uma sobrecarga ou falta de capacidade do sistema.

Numa configuração de ligação ponto-ponto dedicada, apenas é preciso comutar no recetor.

**inserir imagem épica**

Numa configueação partilhada, é preciso comutar nos dois lados.

**inserir imagem épica**

## Pergunta 3

FDMA (Frequency Division Multiple Access) corresponde à transmissão simultânea em vários canais, através da separação da largura de banda em vários sub-canais. São utilizadas bandas de guarda para evitar interferências.

Desse modo, uma estação pode aceder a um transpositor simultaneamente com outros, dado que tem a sua própria banda. O satélite consegue separar os diferentes sinais com filtros passa-banda e reencaminhar para outra estação numa portadora dedicada (FDMA) para não interferir com outras transmissões.

## Pergunta 4

WDM opera sobre o mesmo princípio que FDM mas sobre fibra ótica. Atribúi um comprimento de onda para cada canel, permitindo um débito muito elevado sobre fibra.

DWDM é uma iteração da tecnologia que permite compactar mais canais, de modo a aumentar o débito.

Para inserir essa informação na fibra recorremos ao OTM (Optical Terminal Multiplexer), que faz a multiplexagem e desmultiplexador dos canais.
No entanto, para aumentar a usabilidade do sistema, desenvolveu-se os OADM que permitem remover informação de um conjunto de canais e inserir nova informação nesses canais, tal como na rede SDH.
OS ROADM permitem uma configuração fácil dos comprimentos de onda que são filtrados, de forma a aumentar a eficiência e potencia de configuração da rede.

## Pergunta 5

ADSL opera sobre a tecnologia DMT (Discrete Multi-Tone), que basicamente opera sobre FDM, atribuindo banda conforme as necessidades de cada canal, operando de forma adaptativa.
O isolamento dos sentidos de transmissão pode ser feitos de duas formas: FDM, sem sobreposição de frequências, e cancelamento de ECO.

Next representa a interferências próxima, na mesma extremidade. Fext representa a interferência remota, nas duas extremidades.

Com FDM, eliminamos o NEXT pois não há sobreposição de frequências na transmissão.

Com CE, acorre NExt a baixas frequências pois é onde há sobreposição de frequências. Permite no entanto mais capacidade.

## Pergunta 6

No pior cenário possível, todas as entradas podem apresentar uma célula para uma saída (N células). Logo tem que suportar (N escritas) e 1 leitura para encaminhas um pacote.

## Pergunta 7

L = BP - sum (Perdas_Componentes) - margem / alpha.

BP balanço de potencia = Pe-Pr

alpha atenuação específica nas fibras

## Pergunta 8

Virtualização corresponde a ter entidades como redes ou servidores a providenciar funcionalidades de dispositivos físicos que eles estão a emular.
Virtualização de servidores corresponde a um único servidor a correr as funções de vários, como VMs.
Razões para virtualizar redes são:

- Sharing: Descentralizar processamento

- Segurança e isolamento: VPN

- Agregação de serviços e recursos para simplicidade

- Dynamics: Instalação rápida e móvel

- Gestão de falhas.

Vantagens:

- Minimização dos custos com hardware.

- Mobilidade de serviços

- Consolidação de serviços

- Preservar energia: desligar recursos se não estiveram a ser utilizados

- Automação mais fácil

- Escalabilidade e flexibilidade.

## Questão 9

TOR (Top-of-the-Rack) consiste numa gestão interna em cada rack entre os servidores e switches mais pequenos instalados na mesma rack.

Reduz consideravelmente o número de cabos e otimiza o espaço usado pelos equipamentos, no entanto obriga à gestão de muitos equipamentos (switches) e pode pode levar a um grande desperdício de portas.

EOR (End-of-the-Row) consiste numa gestão inter-rack, com os servidores todos ligados a switches de grande capacidade na mesma row (fila).

Reduz consideravelmente o número de dispositivos, assim como o número de portas desperdiçadas. No entanto apresenta desafios de escalabilidade (novos switches) e requer muitos mais cabos e mais compridos.
