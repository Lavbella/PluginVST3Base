Ibanez Tube Screamer JUCE Clone

Português | English

PortuguêsEste projeto é um clone digital do clássico pedal de distorção Ibanez Tube Screamer (TS-9), desenvolvido em C++ utilizando a framework JUCE 8 e CMake. O plugin utiliza técnicas de soft clipping cúbico para emular a saturação simétrica analógica e filtros DSP para recriar o famoso corte de graves e controlo de tonalidade do circuito original.

🗂️ Organização do ProjetoO código está estruturado de forma moderna e modular, eliminando o cabeçalho automático JuceHeader.h para garantir maior controlo sobre as dependências e tempos de compilação mais rápidos:

PluginProcessor.h / .cpp: Contém o motor de áudio, o loop de processamento de sinal (DSP), os filtros de corte e o gestor de parâmetros thread-safe (APVTS).

PluginEditor.h / .cpp: Trata da Interface Gráfica (GUI), desenhando os três botões rotativos (Drive, Tone, Level) com o visual verde clássico do pedal.

CMakeLists.txt: Script de configuração do CMake que gere os ficheiros e vincula os módulos do JUCE de forma privada.

🆔 Gestão de IDs Únicos no JUCE

Para evitar conflitos em DAWs (como o FL Studio), o projeto segue uma regra estrita de identificação de metadados:

PLUGIN_MANUFACTURER_CODE: Definido globalmente como MPlg. Identifica o fabricante/estúdio e agrupa todos os seus plugins no mixer.

PLUGIN_CODE: Definido estritamente com 4 caracteres únicos por produto (ex: TScr para este pedal). Isto impede que a DAW confunda as interfaces gráficas de plugins diferentes do mesmo autor.⚙️

Configurações Especiais Necessárias

Antes de compilar, garanta que a árvore de diretórios está organizada da seguinte forma:
📂 audioplugins/
 ┣ 📂 JUCE/                 <-- Pasta oficial do JUCE com as fontes/módulos
 ┗ 📂 IbanezTubeScreamer/   <-- Esta pasta do projeto

O arquivo CMakeLists.txt procura a biblioteca através do caminho relativo ../JUCE.

# 1. Limpar compilações anteriores (se existirem)
rmdir /s /q build

# 2. Configurar o CMake gerando a solução para Visual Studio 2022 em 64-bit
cmake -B build -G "Visual Studio 17 2022" -A x64

# 3. Compilar o plugin no modo de performance máxima (Release)
cmake --build build --config Release --target IbanezTubeScreamer_VST3

O ficheiro final compilado estará disponível em:build/IbanezTubeScreamer_artefacts/Release/VST3/Paudiog01.vst3

English

This project is a digital clone of the classic Ibanez Tube Screamer (TS-9) distortion pedal, developed in C++ using the JUCE 8 framework and CMake. The plugin utilizes cubic soft-clipping techniques to emulate analog symmetrical saturation, combined with DSP filters to recreate the original circuit's famous bass cut and tone control.


