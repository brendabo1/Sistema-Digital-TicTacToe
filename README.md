<h1 align="center"> Sistema-Digital-TicTacToe</h1>
<p align="center">Projeto de console dedicado em plataforma de desenvolvimento de hardware</p>

<h2>Sobre</h2>
<p>
Nos últimos anos, os jogos digitais emergiram como uma forma de entretenimento profundamente influente e culturalmente significativa. Desde os primórdios dos jogos de computador e consoles de videogame até a era contemporânea dos jogos móveis e realidade virtual, a indústria de jogos digitais tem evoluído constantemente. Contudo, é importante o papel dos jogos digitais clássicos, que representam os pilares fundamentais da indústria, transcendendo fronteiras geográficas e geracionais. 

Esses clássicos não apenas resistiram ao teste do tempo, mas também continuam a ser celebrados como marcos históricos que ajudaram a moldar o meio dos jogos digitais como o conhecemos hoje. Um desses emblemáticos passatempo é o Jogo Da Velha ou <i>Tic-Tac-Toe</i> que, apesar da sua origem remontar há mais de 3.500 anos no antigo Egito, e com sua dinâmica simples é um dos jogos mais populares do mundo. 

Dessa maneira, este projeto tem como intuito desenvolver um console que implemente uma versão do clássico do Jogo Da Velha como Problema 1 do componente curricular TEC499 Sistemas Digitais. Para executar o sistema, o Kit de desenvolvimento DE1-SoC é utilizado provendo uma interface aos jogadores para inicar uma partida acionando um botão e preencher o tabuleiro alternadamente através do mouse USB até que um empate ou uma vitória ocorram. As soluções, os softwares e dispositivos utilizadas no desenvolvimento serão abordadas nas seções subsequentes.

<h3>Requisitos</h3>

A solução deve atender às condições e aos requisitos predetermminados, de modo que o jogo deve:
<ul>
  <li>Ser executado em uma interface em modo texto, que possa ser visualizada via terminal</li>
  <li>Permitir a interação de dois jogadores</li>
  <li>Captar a posição de marcação da jogada no tabuleiro, assim como a confirmação da ação, por meio de um mouse conectado a uma das portas USB da placa</li>
  <li>Utilizar os botões e chaves disponíveis na placa para iniciar, terminar e demais controles.</li>
  <li>Ter seu código escrito em linguagem C;</li>
  <li>Só poderá utilizar os componentes disponíveis na placa DE1-SoC.</li>
</ul>
O jogo deve permitir a interação de dois jogadores, de forma que a escolha da posição de marcação no tabuleiro em cada jogada (assim como a confirmação da jogada) deva ser captada por um mouse conectado a uma das portas USB existentes no Kit de desenvolvimento DE1-SoC. Para acessar e controlar o jogo (iniciar, pausar, continuar, etc.) o usuário pode utilizar os botões e chaves disponíveis na placa. Os LEDs e displays 7-segmentos também podem ser utilizados para representação de outras informações, caso necessário. 

<!--Neste contexto dinâmico, explorar os jogos digitais não apenas como formas de entretenimento, mas também como expressões artísticas, ferramentas educacionais e plataformas sociais, revela a diversidade e o potencial impacto dessa forma de mídia na sociedade contemporânea.-->

<h2>Equipe</h2>
<ul>
  <li>Brenda Barbosa</li>
  <li>Camila</li>
  <li>Maike</li>
</ul>
<!-- Sumário pra configurar depois
<details open>
  <summary>Sumário</summary>
  <ol>
    <li>xkmx</li>
    <li>
      <ol type="1">
        <li>nlsc</li>
        <li>m sx</li>
      </ol>
  </li>
  </ol>
</details>
-->


<h2>Softwares Utilizados</h2>
<h3>Linguagem C</h3>
<h3>Compilador GNU</h3>
<h3>VS Code</h3>
<h3>Nano</h3>
<!-- versao gnu 2.2.6-->

<h2>Arquitetura do Computador utilizado nos Testes</h2>
<!-- 
*Threads do botao com teoria dos leitores/escritores
*Device drivers (parte da doc)
-->
<h3>Arquitetura da DE1-SoC 2</h3>
<h4>Memória</h4>
<h3>Periféricos da Placa DE1-SoC Utilizados</h3>
<h3>Dispositivos de Entrada e Saída Utilizados</h3>
<h4>USB</h4>
<h3>Drivers</h3>
<!--Acho que nem precisa dessa seção. Não usamos drivers da placa-->
<h2>O Jogo</h2>
<h3>Interface do Usuário</h3>
<h3>Algoritmos do jogo </h3>
<h3>O Tabuleiro</h3>
<h2>Solução Geral</h2>
<h2>Testes</h2>

<h2>Descrição de instalação, configuração de ambiente e execução</h2>
<h2>Referências</h2>
<!--
https://www.gadoo.com.br/dicas/tic-tac-toe/
-->

