<h1 align="center"> Sistema-Digital-TicTacToe</h1>
<p align="center">Projeto de console dedicado em plataforma de desenvolvimento de hardware</p>

<h2>Introdução</h2>

<p style="text-align:justify;">Nos últimos anos, os jogos digitais emergiram como uma forma de entretenimento profundamente influente e culturalmente significativa. Desde os primórdios dos jogos de computador e consoles de videogame até a era contemporânea dos jogos móveis e realidade virtual, a indústria de jogos digitais tem evoluído constantemente. Contudo, é importante o papel dos jogos digitais clássicos, que representam os pilares fundamentais da indústria, transcendendo fronteiras geográficas e geracionais.</p>

<p style="text-align:justify;">
Esses clássicos não apenas resistiram ao teste do tempo, mas também continuam a ser celebrados como marcos históricos que ajudaram a moldar o meio dos jogos digitais como o conhecemos hoje. Um desses emblemáticos passatempo é o conhecido Jogo Da Velha ou <i>Tic-Tac-Toe</i> que, apesar da sua origem remontar há mais de 3.500 anos no antigo Egito, e com sua dinâmica simples é um dos jogos mais populares do mundo.</p>

<p style="text-align:justify;">
Dessa maneira, este projeto tem como intuito desenvolver um console que implemente uma versão do clássico Jogo Da Velha como Problema 1 do componente curricular TEC499 Sistemas Digitais. Para executar o sistema, o Kit de desenvolvimento DE1-SoC é utilizado provendo uma interface aos jogadores para inicar uma partida acionando um botão e preencher o tabuleiro alternadamente através do mouse USB até que um empate ou uma vitória ocorram. As soluções, softwares e dispositivos utilizadas no desenvolvimento serão abordadas nas seções subsequentes.
</p>

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
Nessa seção são apresentados os softwares que auxiliaram no desenvolvimento do sistema.

<h3>Linguagem C</h3>
<p style="text-align:justify;">É uma linguagem de programação de propósito geral que combina abstrações e controles de baixo nível sobre o hardware resultando em ganho de eficiência. O software criado em 1970 por Dennis Ritchie é estreitamente associada ao sistema operacional UNIX, uma vez que as versões desse sistema foram escritas em linguagem C. Além disso, a sintaxe simples e a alta portabilidade desta linguagem entre dispositivos contribui para seu amplo uso em sistemas embarcados de recursos limitados.</p>

<h3>Compilador GNU</h3>
<p style="text-align:justify;">O <i>GNU Compiler Collection GCC</i>(Coleção de Compiladores GNU) ou GCC é um conjunto de compiladores de código aberto desenvolvido pelo Projeto GNU que oferecem suporte a uma gama de linguagens de programação, incluindo C, C++, Fortran, Ada, Go. Esta ferramenta otimiza a compilação, ou seja a produção de código de máquina, nas várias linguagens e arquiteturas de processadores suportadas.</p>

<h3>VS Code</h3>
<p style="text-align:justify;">O Visual Studio Code ou VS Code é editor de texto gratuito com suporte a várias linguagens, incluido Python, Java, C, C++, JavaScript. A ferramenta desenvolvida pela Microsoft dispõe de diversos recursos de depuração, destaque de erros, sugestões, personalização e demais recursos para auxiliar a codificação. Desse modo, o editor foi um dos ambientes utilizados no desenvolvimento do código fonte do jogo.</p>

<h3>Nano</h3>
<p style="text-align:justify;">Também, o editor de texto simples Nano, na versão 2.2.6, presente no Linux embarcado do Kit de desenvolvimento DE1-SoC foi utilizado para codificação da solução. O Nano é um software leve e que oferece uma interface de linha de comando intuitiva, tornando-o ideal para rápida edição de arquivos, scripts e outros documentos de texto.</p>

<h2>Arquitetura do Computador Utilizado nos Testes</h2>
Nesta seção, exploraremos o dispositivo embarcado utilizado bem como os componentes do Kit de Desenvolvimento DE1-SoC. 
<h3>O Kit de Desenvolvimento DE1-SoC</h3>
<p style="text-align:justify;">Equipado com um processador, USB, memória DDR3, Ethernet e uma gama de periféricos, o kit de desenvolvimento DE1-SoC (Figura 1) integra no mesmo Cyclone V sistema em chip (SoC) um <i>hard processor system</i> (HPS) a uma FPGA <i>(Field Programmable Gate Arrays)</i>. Este design permite uma grande flexibilidade da placa nas mais variadas aplicações</p> 
<figure>  
  <img src="docs/images/kit_desenvolvimento_DE1-SoC.jpg">
  <figcaption>
    <p style="text-align:center;"><b>Figura 1</b> - Kit de Desenvolvimento DE1-SoC</p>
    <p style="text-align:center;">Fonte: Terasic Technologies</p>
  </figcaption>
</figure>

<h3>Sistema Computacional DE1-SoC 2</h3>
<p>O diagrama de blocos do sistema computacional apresentado na figura 2 explicita os componentes  O HPS inclui um processador dual-core ARM Cortex-A9, Ethernet, USB FPGA Cyclone V System-on-Chip (SoC) da Intel  

 <!--consistindo em um processador dual-core ARM Cortex-A9 Altera’s SoC integrates an ARM-based  consisting of processor, peripherals and memory interfaces tied seamlessly with the FPGA fabric using a high-bandwidth interconnect backbone.
 um processador ARM Cortex-A9 dual-core com um FPGA Cyclone V da Intel. Essa placa oferece uma ampla gama de periféricos, incluindo porta VGA, porta Ethernet, USB, porta de áudio, entre outros, o que a torna ideal para projetos que envolvem tanto software quanto hardware. Ela é frequentemente utilizada em ambientes educacionais e de pesquisa para o desenvolvimento e aprendizado em sistemas embarcados e FPGA.-->
</p>
![Teste](docs/images/diagramaDE1SoC_FPGAcademy.png)

<figure>  
  <img src="docs/images/diagramaDE1SoC_FPGAcademy.png">
  <figcaption>
    <p style="text-align:center;"><b>Figura 2</b> - Diagrma de Blocos da DE1-SoC</p>
    <p style="text-align:center;">Fonte: FPGAcademy.org</p>
  </figcaption>
</figure>
<!-- 
*Threads do botao com teoria dos leitores/escritores
*Device drivers (parte da doc)
-->

<h4>Memória</h4>
<h4>Controlador USB</h4>
<h4>Botões</h4>
<h3>Dispositivos de Entrada e Saída Utilizados</h3>
<h4>Mouse</h4>
<!--Processo de leitura do arquivo dev/input, decodificação da struct, deslocamento relativo da posição-->
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
https://www.facom.ufu.br/~gustavo/ED1/Apostila_Linguagem_C.pdf
https://gcc.gnu.org/onlinedocs/gcc-14.1.0/gcc.pdf ou https://gcc.gnu.org/onlinedocs/
-->

