<h1 align="center"> Sistema-Digital-TicTacToe</h1>
<p align="center">Projeto de console dedicado em plataforma de desenvolvimento de hardware</p>

<h2>Sobre</h2>
<p>
Nos últimos anos, os jogos digitais emergiram como uma forma de entretenimento profundamente influente e culturalmente significativa. Desde os primórdios dos jogos de computador e consoles de videogame até a era contemporânea dos jogos móveis e realidade virtual, a indústria de jogos digitais tem evoluído constantemente. Entretanto, os jogos digitais clássicos representam os pilares fundamentais da indústria, transcendendo fronteiras geográficas e geracionais. Esses jogos clássicos não apenas resistiram ao teste do tempo, mas também continuam a ser celebrados como marcos históricos que ajudaram a moldar o meio dos jogos digitais como o conhecemos hoje.

Desse modo, este projeto tem como intuito desenvolver um console que implemente uma versão do clássico jogo da velha ou <i>tic-tac-toe</i> como Problema 1 do componente curricular TEC499 Sistemas Digitais. Para isso, é utilizado o Kit de desenvolvimento DE1-SoC para executar o sistema em uma interface em modo texto, que possa ser visualizada via terminal.

Os requisitos
<!--Neste contexto dinâmico, explorar os jogos digitais não apenas como formas de entretenimento, mas também como expressões artísticas, ferramentas educacionais e plataformas sociais, revela a diversidade e o potencial impacto dessa forma de mídia na sociedade contemporânea.-->
O jogo deve ser executado em uma interface em modo texto, que possa ser visualizada via terminal. O jogo deve permitir a interação de dois jogadores, de forma que a escolha da posição de marcação no tabuleiro em cada jogada (assim como a confirmação da jogada) deva ser captada por um mouse conectado a uma das portas USB existentes no Kit de desenvolvimento DE1-SoC. Para acessar e controlar o jogo (iniciar, pausar, continuar, etc.) o usuário pode utilizar os botões e chaves disponíveis na placa. Os LEDs e displays 7-segmentos também podem ser utilizados para representação de outras informações, caso necessário. 

Este projeto tem o intuito de desenvolver um jogo inspirado no Breakout. É utilizada a placa FPGA DE1-SoC para executar o sistema e disponibilizar a interface de controle ao usuário. Um acelerômetro embutido na placa permite captar a movimentação pretendida pelo usuário. Botões são utilizados para executar comandos no jogo. E os dados de imagem são transmitidos por um cabo VGA para um monitor CRT, sendo ele, o dispositivo que fará a exibição das telas ao usuário.

Os requisitos para elaboração do sistema são apresentados a seguir:

O código carregado na DE1-SoC deve ser feito em linguagem C;
Um acelerômetro deve captar a movimentação feita na placa para alterar a posição da barra que irá colidir com a bola;
Os botões devem ser utilizados para executar comandos no jogo;
Os dados de imagem devem ser transmitidos de um cabo VGA para um monitor CRT.

</p>
<h3>Requisitos</h3>
<p>
  <ul>
    <li>O código deve ser escrito em linguagem C;</li>
    <li>O sistema só poderá utilizar os componentes disponíveis na placa.</li>
  </ul>
</p>
<h2>Equipe</h2>
<ul>
  <li>Brenda</li>
  <li>Camila</li>
  <li>Maike</li>
</ul>
<details open>
<summary>Sumário</summary>

* softwar
* 2

</details>

<h2>Softwares Utilizados</h2>
<h3>Linguagem C</h3>
<h3>Compilador GNU</h3>
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

