<div align="center">

```
 █████╗ ██████╗ ██████╗       ██████╗  ██████╗ ██╗███████╗ ██████╗ ███╗   ██╗
██╔══██╗██╔══██╗██╔══██╗      ██╔══██╗██╔═══██╗██║██╔════╝██╔═══██╗████╗  ██║
███████║██████╔╝██████╔╝█████╗██████╔╝██║   ██║██║███████╗██║   ██║██╔██╗ ██║
██╔══██║██╔══██╗██╔═══╝ ╚════╝██╔═══╝ ██║   ██║██║╚════██║██║   ██║██║╚██╗██║
██║  ██║██║  ██║██║           ██║     ╚██████╔╝██║███████║╚██████╔╝██║ ╚████║
╚═╝  ╚═╝╚═╝  ╚═╝╚═╝           ╚═╝      ╚═════╝ ╚═╝╚══════╝ ╚═════╝ ╚═╝  ╚═══╝
                                                                    T O O L
```

# ARP Poison Tool · ESP32

**Ferramenta educacional de ARP Spoofing para microcontroladores ESP32**

[![Status](https://img.shields.io/badge/status-em%20desenvolvimento-yellow?style=flat-square)](https://github.com/)
[![Platform](https://img.shields.io/badge/platform-ESP32-blue?style=flat-square&logo=espressif)](https://www.espressif.com/)
[![IDE](https://img.shields.io/badge/IDE-Arduino-teal?style=flat-square&logo=arduino)](https://www.arduino.cc/)
[![License](https://img.shields.io/badge/license-Educational%20Only-red?style=flat-square)](./LICENSE)
[![Language](https://img.shields.io/badge/linguagem-C%2B%2B-orange?style=flat-square&logo=cplusplus)](https://isocpp.org/)

> ⚠️ **AVISO:** Este projeto é estritamente para fins educacionais. O uso em redes sem autorização explícita é **ilegal**.

</div>

---

## 📖 Sobre o Projeto

Este projeto é uma **ferramenta de aprendizado** desenvolvida para o microcontrolador **ESP32**, criada para demonstrar na prática como funciona o protocolo **ARP (Address Resolution Protocol)** e como a ausência de autenticação nesse protocolo permite ataques de **ARP Spoofing** (envenenamento de cache ARP).

A ferramenta permite, via **Monitor Serial**, definir alvos em tempo real, enviando pacotes ARP Reply forjados para redirecionar o tráfego de uma rede local para o próprio ESP32.

### 🔬 O que é ARP Spoofing?

O protocolo ARP é responsável por mapear endereços IP a endereços MAC dentro de uma rede local. Por não possuir mecanismo de autenticação, um atacante pode enviar respostas ARP falsas para "envenenar" a tabela ARP de outros dispositivos, fazendo-os acreditar que o MAC do atacante corresponde ao IP do roteador — permitindo interceptar o tráfego (ataque Man-in-the-Middle).

---

## 🚀 Funcionalidades

| Funcionalidade | Descrição |
|---|---|
| 🖥️ **Interface Serial Interativa** | Configuração dinâmica de alvos via Monitor Serial |
| 📶 **Wi-Fi Customizável** | SSID e senha configuráveis por linha de comando |
| ☠️ **Envio de Pacotes ARP Forjados** | Envenenamento contínuo da tabela ARP dos alvos |
| 💡 **Feedback Visual via LED** | Indicador de status no pino GPIO 2 (LED nativo) |

---

## 🛠️ Requisitos de Hardware

```
┌─────────────────────────────────────────┐
│              ESP32 DevKit               │
│                                         │
│  ┌─────┐   GPIO 2 ──── LED (nativo)    │
│  │ USB │   GND ─────── GND              │
│  └──┬──┘                               │
│     │                                   │
│  Serial (115200 baud)                   │
└─────────────────────────────────────────┘
```

| Componente | Especificação |
|---|---|
| **Microcontrolador** | ESP32 (qualquer modelo com Wi-Fi) |
| **LED** | GPIO 2 — LED nativo da placa |
| **Cabo USB** | Para alimentação e comunicação serial |

---

## 💻 Instalação e Uso

### 1. Pré-requisitos

- [Arduino IDE](https://www.arduino.cc/en/software) instalada
- Suporte ao ESP32 configurado no Gerenciador de Placas
- Biblioteca `esp32ARP` instalada via Gerenciador de Bibliotecas

### 2. Instalando a Biblioteca

Na Arduino IDE:
```
Sketch → Incluir Biblioteca → Gerenciar Bibliotecas...
→ Pesquisar: "esp32ARP"
→ Instalar
```

### 3. Carregando o Código

```bash
# Clone o repositório
git clone https://github.com/fiilipe-sh/ESP32-ARP-Poisoning-Tool.git

# Abra o arquivo .ino na Arduino IDE
# Selecione a placa: ESP32 Dev Module
# Selecione a porta COM correta
# Clique em Upload
```

### 4. Configurando via Serial

Após o upload, abra o Monitor Serial com baud rate **115200** e siga as instruções:

```
============================================
   ARP Poison Tool - ESP32
   [*] Iniciando configuração...
============================================

> Digite o SSID da rede: MinhaRede
> Digite a senha Wi-Fi: ********
> [+] Conectado! IP: 192.168.1.105

> Digite o IP da Vítima:  192.168.1.10
> Digite o IP do Roteador: 192.168.1.1
> Digite o MAC da Vítima:  AA:BB:CC:DD:EE:FF

> [*] Iniciando envenenamento ARP...
> [+] Pacote enviado! LED piscando...
```

---

## 📂 Estrutura do Código

```
ARP-Poison-Tool/
│
├── ARP-Poison-Tool.ino     # Código principal
├── README.md               # Este arquivo
└── LICENSE                 # Licença educacional
```



### Fluxo de Operação

```
[BOOT] → [Serial Init] → [Configuração Wi-Fi]
    → [Conexão à Rede] → [Coleta de Alvos]
    → [Loop: Envia ARP Reply Forjado] → [Pisca LED]
    → [Aguarda 4s] → [Repete]
```

---

## 🧠 Como o Ataque Funciona

```
ANTES do envenenamento:
  Vítima  ──→  Roteador  ──→  Internet

APÓS o envenenamento:
  Vítima  ──→  ESP32  ──→  Roteador  ──→  Internet
               (MitM)
```

O ESP32 envia pacotes ARP Reply não solicitados para a vítima, associando o IP do roteador ao próprio MAC address do ESP32. Com isso, todo tráfego da vítima destinado ao roteador passa a ser enviado ao ESP32 primeiro.

---

## 🛡️ Como se Defender

Para mitigar ataques de ARP Spoofing em redes modernas:

- **Switches gerenciáveis** com Dynamic ARP Inspection (DAI) habilitado
- **Entradas ARP estáticas** para dispositivos críticos (roteador, servidores)
- **Segmentação de rede** com VLANs para isolar dispositivos
- **Ferramentas de monitoramento** como `arpwatch` para detectar mudanças suspeitas
- **Uso de VPN** para criptografar o tráfego mesmo em redes comprometidas

---

## 🤝 Contribuições

O projeto está em desenvolvimento ativo! Contribuições são bem-vindas.

### Roadmap / Melhorias Desejadas

- [ ] **Scan automático de IPs** — descoberta de hosts ativos na rede
- [ ] **Interface Web (AsyncWebServer)** — configuração via navegador
- [ ] **MITM completo** — reencaminhamento de pacotes com IP forwarding
- [ ] **Modo furtivo** — variação de intervalo de envio para evasão
- [ ] **Log de tráfego** — captura de pacotes interceptados

### Como Contribuir

```bash
# 1. Fork este repositório
# 2. Crie uma branch para sua feature
git checkout -b feature/scan-automatico

# 3. Commit suas mudanças
git commit -m "feat: implementa scan automático de IPs via ARP broadcast"

# 4. Abra um Pull Request descrevendo as mudanças
```

Também sinta-se à vontade para abrir uma **Issue** com bugs, sugestões ou dúvidas.

---

## ⚖️ Aviso Legal (Disclaimer)

```
╔══════════════════════════════════════════════════════════════╗
║                    ⚠  AVISO LEGAL  ⚠                        ║
╠══════════════════════════════════════════════════════════════╣
║                                                              ║
║  ESTE SOFTWARE É FORNECIDO EXCLUSIVAMENTE PARA FINS          ║
║  EDUCACIONAIS E DE PESQUISA EM SEGURANÇA DA INFORMAÇÃO.      ║
║                                                              ║
║  O uso desta ferramenta em redes de terceiros, sem           ║
║  autorização explícita e documentada do proprietário,        ║
║  é CRIME previsto na Lei nº 12.737/2012 (Lei Carolina        ║
║  Dieckmann) e no Art. 154-A do Código Penal Brasileiro.      ║
║                                                              ║
║  O autor NÃO SE RESPONSABILIZA por danos, perdas ou          ║
║  uso indevido deste código.                                  ║
║                                                              ║
║  Use APENAS em redes próprias ou com autorização formal.     ║
║                                                              ║
╚══════════════════════════════════════════════════════════════╝
```

---

## 📚 Referências

- [RFC 826 — An Ethernet Address Resolution Protocol](https://datatracker.ietf.org/doc/html/rfc826)
- [ESP32 Technical Reference Manual — Espressif](https://www.espressif.com/en/support/documents/technical-documents)
- [Arduino ESP32 Core — GitHub](https://github.com/espressif/arduino-esp32)
- [OWASP — ARP Spoofing](https://owasp.org/www-community/attacks/ARP_spoofing)

---

<div align="center">

**Desenvolvido para fins educacionais — Entender para defender.**

*"Conhecer o ataque é o primeiro passo para construir a defesa."*

</div>
