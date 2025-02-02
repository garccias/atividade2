# ⏱️ Atividade 2: Temporizador de um Disparo (One Shot)

## 📜 Descrição
Nesta atividade, utilizando a função `add_alarm_in_ms()` presente na ferramenta Pico SDK, projetamos um sistema de temporização para o acionamento de LEDs, que é ativado ao clicar em um botão (pushbutton).

## 🧩 Componentes Utilizados
1. **Microcontrolador:** Raspberry Pi Pico W.
2. **03 LEDs:** Azul, Vermelho e Verde.
3. **03 Resistores:** 330 Ω.
4. **Botão:** Pushbutton.

## 🎯 Requisitos do projeto
1. **Acionamento dos LEDs**  
2. **Temporizador do Alarme** 
3. **Funções de Call-back** 
4. **Restrição de Clique no Botão**
5. **Experimento com LED RGB
6. ** Software Debounce**
7. 
## 🚀 Como Executar o Projeto
1. Clone este repositório:
    ```bash
    git clone https://github.com/garccias/atividade2.git
    cd atividade2
    ```
2. Compile o projeto utilizando CMake e Ninja:
    ```bash
    mkdir build
    cd build
    cmake -G "Ninja" ..
    ninja
    ```
3. Carregue o arquivo `.uf2` gerado na placa Raspberry Pi Pico W.


