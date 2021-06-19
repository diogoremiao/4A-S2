# Comparar RIP, OSPF e BGP4

Os protocolos de routing RIP e OSPF dizem respeito a routing interno, enquanto que protocolo BGP4 diz respeito a routing externo.

O protocolo de routing RIP é baseado no algoritmo de routing distance-vector, tendo uma complexidade reduzida e tempos de convergência elevados.
O algoritmo distance-vector consiste em ter os vários nós de uma rede a enviarem aos nós vizinhos a sua tabela de routing completa. O nó, como tem acesso às tabelas dos vizinhos, identifica o melhor caminho para cada destino, construindo assim a sua propria tabela de routing.
O RIP é mais antigo dos protocolos de routing que utiliza distance vector.
A sua métrica na primeira versão baseava-se apenas no hop count, sendo que na segunda também considerava a taxa de transmissão.
Este protocolo não é compatível com VLSM e é um standard IETF. A versão dois é.
Por norma é um protocolo de routing usado em redes de pequena dimensão.

O protocolo OSPF, ao contrário do RIP, é baseado no algoritmo Link-State. É um standard do IETF, podendo ser utilizado por qualquer fabricante, garantindo heterogeneidade,

No algoritmo link-state os nós anunciam pela rede apenas os seus pacotes LSP para informarem os outros nós da rede sobre o seu estado e dos seus vizinhos.
Seguidamente, os LSP recebidos dos nís vizinhos vão ser utilizados para construir um modelo global da rede e uma tabela de routing.
Os melhores caminhos são calculados usando o algoritmo SPF.

Este protocolo, devido à sua complexidade e aos baixos tempos de convergências, deverá ser usado em redes de média e grande dimensão.
O OSPF tem também presente o conceito de área, que minima a tabela de routing e aumenta a eficiência do sistema. Todas a áreas têm que estar ligadas diretamente à área 0 ou backbone.

O protocolos de routing externo são adequados a redes de grande dimensão. Por exemplo, no caso que uma empresa tem amis do que uma ligação ao ISP para haver redundância e/ou distribuição do tráfego ou até o caso de uma empresa que tem vários routers para vários ISPs.

Quando é criada uma AS, uma rede uniformizada na sua comunicação interna e com intercomunicação total, usamos o BGP4 para comunicar com outros AS. Tem uma convergÊncia rápida (1s) e existem vários critérios para escolher a melhor rota.

O algoritmo utilizado no BGP4 é o path-vector.
neste algoritmo, cada entrada na tabela de routing contém a rede de destino, o próximo router e o caminho para chegar ao destino.
A coleção de dados é feita da seguinte forma: os router de fronteira de cada AS que participam no routing por path vector, anunciam a sua acessibilidade a outras redes, através de mensagens path vector. Cada router que receba a mensagem tem que verificar que o caminho anunciado está de acordo com a sua política.
Se estiver, o ASBR modifica a sua tabela de rotas e modifica também a mensagem, antes de a enviar para o próximo hop. Na mensagem modificada envia o seu próprio AS number e substitui a entrada do próximo router com a sua identificação.

# Solução para gestão segura de uma rede, caso haja dispositivos que não suportam SNMPv3.

Caso se verifique isto, a gestão da rede poderá ser feita através de vistas de controlo de acesso, onde só será permitido operações de leitura e não irão ser permitidas operações de escrita, limitando assim, o diálogo.
As gestão da rede pode também ser feita numa estrutura dedicada para o efeito -  gestão out-band, normalmente através de VPN.