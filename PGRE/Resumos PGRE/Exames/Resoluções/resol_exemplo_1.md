# 1 - Requisitos do utilizador

Os requisitos do utilizador são aqueles que são discutidos em conversa com os utilizadores.
Estes requisitos estão diretamente relacionados com a performance: atraso, fiabilidade e capacidade:

- Prontidão
- Interatividade
- Qualidade de apresentação (UI)
- Adaptabilidade (Pequenas alterações)
- Funcionalidade
- Fiabilidade
- Custo (Orçamento)
- Crescimento futuro
- Suporte
- Segurança

# 2 - Requisitos da rede

O principal requisito e que está sempre presenta no planeamento das redes.

- Dependências de escalabilidade
- Dependências de localização
- Limitações de performance
- Dependências de suporte de serviço
- Dependências de interoperabilidade
- Integração de rede existente

# 3 - Componente de gestão

- Métodos de monitorização
- Protocolos de gestão
- Características a monitorizar
- Monitorização in-band e out-band
- Gestão centralizada vs Descentralizada
- Performance

# 4 - SLA

Service Level Agreement: É a formalização da QoS num contrato entre o cliente e o prestador de serviço.
Este acordo é importante pois estabelece os requisitos mínimos que deverão ser fornecidos.
Se o acordo não estiver a ser cumprido, o prestador de serviço deverá ser penalizado, mas essa verificação tem que ser feita do lado do cliente.

# 5 - Localização dos equipamentos

Saber a localização é importante para determinar a relação entre os utilizadores, as aplicações e a rede.
É importante para redes cujos componentes do sistema são outsourced.

A localização dos equipamentos é o primeiro passo para determinar características do sistema no que toca a fluxos de tráfego.

# 6 - Disponibilidade

99.5% -> 43.8 horas por ano de downtime

Não é garantido que um serviço esteja sempre disponível.
O sistema poderá estar em baixo neste caso até 43.8 horas num ano, sem contar com manutenções agendadas.

Não é aconselhável a clientes que necessitam que a rede esta sempre operacional. 
Para isso deverá contratar-se um serviço de tripla redundância: 99.999% (5.26 minutos por ano).

# 7 - MTTR

Mean Time to Repair.
É expressa em unidades de tempo como o tempo médio para reparar uma falha no sistema.
Juntamente com o MTBF, é possível calcular a disponibilidade em percentagem do serviço

# 8 - Desempenho numa rede

- Largura de Banda: Capacidade de transportar informação num circuito
- Taxa de transmissão: Quantidade de informação sem erros transmitida por unidade de tempo.
- Goodput: Quantidade de informação disponível para as aplicações (informação útil)

# 9 - Tipo de Fluxos

- Individual: Fluxo associado a uma única sessão de aplicação
- Composto: Combinação de vários fluxos (best-effort) individuais que partilham o mesmo caminho, ligação ou rede
- Backbone: É a combinação de vários fluxos compostos quando a rede origina um certo grau de hierarquia.

Num projeto de rede, a maioria dos fluxos identificados têm características de baixo desempenho ou best-effort.
Só alguns fluxos têm características de alto desempenho ou especificadas.

Fluxos de alto desempenho conduzem o projeto segundo uma perspetiva de serviço.

Fluxos de baixo desempenho conduzem o projeto segundo uma perspetiva de planeamento de capacidade.

# 10 - Modelos de Fluxo

Modelos de fluxo são caracterizados essencialmente pela sua direcionalidade e pela sua hierarquia.

- Peer-to-peer: Não existe hierarquia, necessidades de acesso entre eles equivalentes. Ex: teleconferência
- Client-Server: Têm direcionalidade e hierarquia, pedidos e respostas (2 sentidos), fluxos assimétricos
- Client-Server Hierárquico: À medida que o o modelo Client-Server fica mais hierárquico, em termos de adicionar camadas, então o seu modelo passa a ser representado desta forma
- Computação distribuída: Fala tudo para toda a gente


1. O SNMP é um protocolo de gestão de redes que inclui, neste momento, 3 versões

2. Gerado pelo agente

3. V (TCP ou UDP)

4. V

5. SNMPv3

6. O OID é o identificar de um objeto na MIB

7. V

8. V

# 1 - Modelo OSI

Opera sobre o modelo FCAPS

1. Gestão de falhas

- Deteção de localização da falha
- Isolamento da falha
- Minimizar o impacto da falha, reconfigurando a rede
- Reparar a falha

2. Gestão de contabilização

- Contabilização do tráfego nas fronteiras de rede
- Deteção de gastos excessivos de um utilizador ou grupo de utilizadores
- Utilização ineficiente dos recursos da rede
- Previsão dos recursos necessários p/a evolução da rede
- Fonte de informação para as operações de taxação

3. Gestão de configurações 

- Manutenção das versões de SW dos sistemas de rede
- Manutenção e configuração dos sistemas
- Alterações às configurações
- Atualizações de SW ou HW
- Escalonamento das alterações

4. Gestão do desempenho

- Monitorização
- Controlo para melhorar o desempenho da rede
- Verificação do SLA

5. Gestão de segurança

- Proteção da informação
- Controlo de acesso aos recursos
- Gestão centralizada ou distribuída
- Níveis hierárquicos de acesso
- Registo de logs
- Análise dos logs

# 2 - Problemas de segurança de um sistema SNMP

Há 3 categorias de problemas.
Nos problemas principais destacamos:

- Máscara/Autenticação de origem, onde o invasor assume a entidade de um sistema para aceder ao controlo deste.
Isto é abordado no SNM com a autenticação encriptada de utilizador.
O comprometimento da integridade de uma mensagem, resolvido com o módulo MEssage Processing sistema que verifica essa integridade.

Nos secundários:

-Modificação da ordem de chegada, resolvido no mesmo módulo, e packet sniffing, resolvido com encriptação das mensagens enviadas entre sistemas.

Finalmente, destacamos DoS, que é um problema comum em todos os sistemas hoje em dia, e analise de tráfego para detetar padrões.

# 3 - MIB Privada

A MIB é uma especificação standard de monitorização que possibilita a troca de dados de monitorização da rede entre vários sistemas. A MIB especifica os elementos de dados (as variáveis a gerir) que um sistema gerível precisa de ter, as operações permitidas em cada variável e qual o seu significado.

A MIB privada é aquela que contém objetos definidos por outras organizações. Fornece informações específicas dos equipamentos que estão a ser geridos como a configuração, as ????, sendo também possível reinicializar e desabilitar uma ou mais portas de um router.

Para se explorar as capacidades de uma MIB privada é necessário que esta informação exista no manager e no agente residente no sistema que se pretende gerir.

