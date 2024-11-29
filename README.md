# Sistema de Monitoramento e Lembretes para Auxiliar Idosos na Tomada de Medicamentos

## Descrição
Este projeto aborda o desafio da adesão medicamentosa em idosos, propondo um sistema integrado que combina tecnologias web, dispositivos embarcados e o protocolo Zigbee. O objetivo é emitir lembretes audiovisuais eficientes, promovendo uma melhor gestão de medicamentos e maior qualidade de vida.

## Funcionalidades
- Cadastro de idosos, medicamentos e horários via plataforma web.
- Emissão de alertas sonoros e visuais com integração à Alexa.
- Comunicação confiável e de baixa latência utilizando o protocolo Zigbee.
- Sistema modular, com potencial para futuras expansões, como monitoramento de saúde em tempo real.

## Tecnologias Utilizadas
- **Web**: Plataforma para cadastro e gerenciamento centralizado.
- **Hardware**:
  - ESP8266 para controle de dispositivos.
  - Amplificador de áudio e alto-falantes.
  - Lâmpada inteligente integrada ao hub Zigbee.
- **Protocolo Zigbee**: Comunicação de baixa energia e alta confiabilidade.
- **Assistente Virtual Alexa**: Controle de dispositivos de iluminação.
- **Servidor Web**: Hospedagem e gerenciamento de dados.

## Arquitetura do Sistema
1. **Sistema Web**: Gerencia informações de idosos e medicamentos.
2. **ESP8266**: Controla dispositivos de áudio e luz.
3. **Hub Zigbee**: Conecta dispositivos à Alexa.
4. **Assistente Alexa**: Interação com lâmpadas inteligentes.

## Como Funciona
1. **Cadastro de Informações**: O responsável cadastra idosos, medicamentos e horários na plataforma web.
2. **Emissão de Alertas**: O servidor envia informações ao ESP32, que reproduz alertas sonoros e ativa a lâmpada no horário correto.
3. **Lembretes Audiovisuais**: Mensagens de áudio e luzes reforçam os lembretes de medicação.

## Motivação
Com o envelhecimento populacional, soluções que promovam a adesão medicamentosa são essenciais para reduzir riscos associados à polifarmácia e melhorar a qualidade de vida dos idosos.

## Contribuição
O projeto alia tecnologias de IoT e automação para simplificar a gestão medicamentosa, promovendo independência e segurança para a terceira idade.

## Como Contribuir
1. Faça um fork deste repositório.
2. Crie uma branch para suas alterações: `git checkout -b minha-feature`.
3. Realize um pull request para análise.

## Licença
Este projeto é licenciado sob os termos da [MIT License](LICENSE).

---

**Autores**  
- Augusto Muller - [Email](mailto:am0125717@setrem.com.br)
- Dionathan da Rosa - [Email](mailto:dr0107530@setrem.com.br)
- Eduardo Matheus Seibt - [Email](mailto:es0125903@setrem.oom.br)
