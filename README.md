# Ibanez Tube Screamer JUCE Clone

[Português](#português) | [English](#english)

---

## Português

Este projeto é um clone digital do clássico pedal de distorção **Ibanez Tube Screamer (TS-9)**, desenvolvido em C++ utilizando a framework **JUCE 8**, **CMake** e **VSCode**. O plugin utiliza técnicas de *soft clipping* cúbico para emular a saturação simétrica analógica e filtros DSP para recriar o famoso corte de graves e controlo de tonalidade do circuito original.

### 🗂️ Organização do Projeto

O código está estruturado de forma moderna e modular, eliminando o cabeçalho automático `JuceHeader.h` para garantir maior controlo sobre as dependências e tempos de compilação mais rápidos:

*   **`PluginProcessor.h` / `.cpp`**: Contém o motor de áudio, o loop de processamento de sinal (DSP), os filtros de corte e o gestor de parâmetros *thread-safe* (**APVTS**).
*   **`PluginEditor.h` / `.cpp`**: Trata da Interface Gráfica (GUI), desenhando os três botões rotativos (*Drive*, *Tone*, *Level*) com o visual verde clássico do pedal.
*   **`CMakeLists.txt`**: Script de configuração do CMake que gere os ficheiros e vincula os módulos do JUCE de forma privada.

### 🆔 Gestão de IDs Únicos no JUCE

Para evitar conflitos em DAWs (como o FL Studio), o projeto segue uma regra estrita de identificação de metadados:

*   **`PLUGIN_MANUFACTURER_CODE`**: Definido globalmente como `MPlg`. Identifica o fabricante/estúdio e agrupa todos os seus plugins no mixer.
*   **`PLUGIN_CODE`**: Definido estritamente com 4 caracteres únicos por produto (ex: `TScr` para este pedal). Isto impede que a DAW confunda as interfaces gráficas de plugins diferentes do mesmo autor.

### ⚙️ Configurações Especiais Necessárias

Antes de compilar, garanta que a árvore de diretórios está organizada da seguinte forma:

```text
📂 audioplugins/
 ┣ 📂 JUCE/                 <-- Pasta oficial do JUCE com as fontes/módulos
 ┗ 📂 IbanezTubeScreamer/   <-- Esta pasta do projeto
```

O arquivo `CMakeLists.txt` procura a biblioteca através do caminho relativo `../JUCE`.

### 🛠️ Compilação pela Linha de Comando (Windows - MSVC 2022)

Para compilar o plugin sem depender de IDEs, abra o terminal (Prompt de Comando ou PowerShell) na raiz do projeto e execute os seguintes comandos:

```bash
# 1. Limpar compilações anteriores (se existirem)
rmdir /s /q build

# 2. Configurar o CMake gerando a solução para Visual Studio 2022 em 64-bit
cmake -B build -G "Visual Studio 17 2022" -A x64

# 3. Compilar o plugin no modo de performance máxima (Release)
cmake --build build --config Release --target IbanezTubeScreamer_VST3
```

O ficheiro final compilado estará disponível em:
`build/IbanezTubeScreamer_artefacts/Release/VST3/Paudiog01.vst3`

---
### 🚚 Instalação Automática pós-Compilação

Se deseja que o CMake copie o plugin automaticamente para a pasta oficial do Windows após o processo de build, pode ativar o bloco de automação no final do ficheiro `CMakeLists.txt`. 

#### Passos para Ativar:
1. Abra o `CMakeLists.txt` e descomente (remova o símbolo `#`) as linhas do bloco `CONFIGURAÇÃO DE CÓPIA AUTOMÁTICA`.
2. Abra o seu terminal como **Administrador** (obrigatório para dar permissões de escrita na pasta `Program Files`).
3. Execute o comando de build normalmente:
   ```bash
   cmake --build build --config Release --target IbanezTubeScreamer_VST3
   ```

O CMake irá compilar o código e mover automaticamente a pasta `Paudiog01.vst3` para o diretório padrão do sistema:
`C:\Program Files\Common Files\VST3\Paudiog01.vst3`

Depois, basta abrir o gestor de plugins da sua DAW (ex: FL Studio), ativar a opção **"Verify plugins"** e fazer um novo scan.



## English

This project is a digital clone of the classic **Ibanez Tube Screamer (TS-9)** distortion pedal, developed in C++ using the **JUCE 8** framework, **CMake** and **VSCode**. The plugin utilizes cubic soft-clipping techniques to emulate analog symmetrical saturation, combined with DSP filters to recreate the original circuit's famous bass cut and tone control.

### 🗂️ Project Architecture

The codebase follows a modern, modular structure, bypassing the automated `JuceHeader.h` file to achieve better dependency control and faster compilation times:

*   **`PluginProcessor.h` / `.cpp`**: Houses the audio engine, signal processing loop (DSP), EQ filters, and the thread-safe parameter manager (**APVTS**).
*   **`PluginEditor.h` / `.cpp`**: Manages the Graphical User Interface (GUI), drawing the three rotary knobs (*Drive*, *Tone*, *Level*) styled after the classic green chassis.
*   **`CMakeLists.txt`**: The CMake build script that organizes source files and links JUCE modules privately.

### 🆔 Unique ID Management in JUCE

To prevent GUI and scanning conflicts inside DAWs (like FL Studio), the project adheres to strict metadata routing rules:

*   **`PLUGIN_MANUFACTURER_CODE`**: Globally set to `MPlg`. This identifies your studio/brand, grouping your products together in the DAW's mixer database.
*   **`PLUGIN_CODE`**: Strictly set to 4 unique characters per plugin (e.g., `TScr` for this pedal). This ensures the DAW never mixes up interfaces between your different creations.

### ⚙️ Required Project Environment

Before building, ensure your local directory tree matches this structure:

```text
📂 audioplugins/
 ┣ 📂 JUCE/                 <-- Official JUCE SDK folder containing modules
 ┗ 📂 IbanezTubeScreamer/   <-- This repository's folder
```

The `CMakeLists.txt` file is pre-configured to look for the framework using the relative path `../JUCE`.

### 🛠️ Command Line Compilation (Windows - MSVC 2022)

To compile the plugin cleanly using your terminal (Command Prompt or PowerShell), navigate to the root directory of this repository and run the following commands:

```bash
# 1. Clean previous build caches (if any exist)
rmdir /s /q build

# 2. Configure CMake and generate standard Visual Studio 2022 64-bit solution files
cmake -B build -G "Visual Studio 17 2022" -A x64

# 3. Compile the production-ready binary with maximum optimization (Release mode)
cmake --build build --config Release --target IbanezTubeScreamer_VST3
```

Your freshly built VST3 target bundle will be generated inside:
`build/IbanezTubeScreamer_artefacts/Release/VST3/Paudiog01.vst3`

# 3. Compile the production-ready binary with maximum optimization (Release mode)
cmake --build build --config Release --target IbanezTubeScreamer_VST3

Your freshly built VST3 target bundle will be generated inside:build/IbanezTubeScreamer_artefacts/Release/VST3/Paudiog01.vst3

### 🚚 Automatic Post-Build Installation

If you want CMake to automatically deploy the plugin to the official Windows VST3 folder right after the build sequence finishes, you can enable the automation block at the bottom of the `CMakeLists.txt` file.

#### How to Enable:
1. Open `CMakeLists.txt` and uncomment (remove the `#` symbol) the lines under the `CONFIGURAÇÃO DE CÓPIA AUTOMÁTICA` section.
2. Open your terminal as an **Administrator** (required to grant write permissions inside the `Program Files` directory).
3. Run the build command as usual:
   ```bash
   cmake --build build --config Release --target IbanezTubeScreamer_VST3
   ```

CMake will compile the binaries and automatically move the entire `Paudiog01.vst3` bundle straight into your system's default directory:
`C:\Program Files\Common Files\VST3\Paudiog01.vst3`

Once done, simply open your DAW's plugin manager (e.g., FL Studio), turn on **"Verify plugins"**, and perform a fresh scan.
