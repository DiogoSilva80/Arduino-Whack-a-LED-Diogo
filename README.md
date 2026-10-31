Whack-a-LED - Projeto Arduino
O Whack-a-LED é um jogo interativo desenvolvido para a plataforma Arduino, conforme documentado no ficheiro "Projeto de TI.docx". O utilizador interage através de um botão, com o objetivo de acertar em LEDs que se acendem numa sequência aleatória. A partida termina quando o jogador consegue acertar em todos os LEDs ou quando o botão é pressionado de forma contínua durante 2 segundos.   
Projeto de TI.docx
+ 2

Configuração de Hardware e Variáveis

Os pinos dos LEDs são definidos pelas variáveis ledMenor e ledMaior.   
Projeto de TI.docx

O botão de interação encontra-se mapeado na variável buttonPin.   
Projeto de TI.docx

O tempo de resposta do botão e a frequência de troca dos LEDs são geridos, respetivamente, por debounceDelay e delayLED.   
Projeto de TI.docx

Arquitetura de Funções

setup(): Configura os pinos e inicializa a comunicação série.   
Projeto de TI.docx

flashAllLEDs(): Pisca todos os LEDs simultaneamente para sinalizar eventos, como o início e o fim do jogo.   
Projeto de TI.docx

startGame(): Inicia o jogo, reinicia as pontuações e desliga todos os LEDs.   
Projeto de TI.docx

lightRandomLED(): Seleciona e acende um LED aleatoriamente, garantindo que não repete o LED anterior.   
Projeto de TI.docx

turnOffCurrentLED(): Desliga o LED que se encontra atualmente aceso.   
Projeto de TI.docx

keepLEDsOn(): Mantém acesos os LEDs nos quais o jogador já acertou e atualiza as variáveis de estado.   
Projeto de TI.docx

updateButtonState(): Implementa o debounce e armazena o tempo inicial da pressão do botão.   
Projeto de TI.docx

loop(): Verifica permanentemente se o jogo está ativo. Alterna os LEDs, valida acertos e atualiza a pontuação, ou invoca endGame() se detetar uma pressão de 2 segundos no botão.   
Projeto de TI.docx
+ 1

Lacunas e Melhorias Futuras

O sistema apresenta dificuldades lógicas no reinício do jogo quando o botão é pressionado durante 2 segundos, devido a conflitos não resolvidos na validação da variável gamestarted e da função endGame().   
Projeto de TI.docx

A temporização atual bloqueia o processamento através da função delay(), estando planeada a transição para millis() para tornar o jogo mais responsivo.   
Projeto de TI.docx

Futuras atualizações poderão incluir limites de tempo ou vidas por ronda para tornar as regras de vitória mais desafiantes.   
Projeto de TI.docx
