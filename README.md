# Comandos básicos

## Makefile

`make compactador` - Para compilar o programa de irá compactar arquivos

`make descompactador` - Para compilar o programa que irá descompactar arquivos

## Execução do programa

O programa roda diretamente no terminal, e a única interação com ele é a chamada do programa, juntamente dos argumentos

`./compactador *nome_do_arquivo.txt*` - Para utilizar o compactador, basta executá-lo e passar como argumento o arquivo que você gostaria de compactar (qualquer formato).

`./descompactador *nome_do_arquivo.txt.comp` - Após compactar um arquivo, será gerado um arquivo de mesmo nome do anterior, porém com extensão `.comp`. Você deverá passar arquivos desse formato como argumento.
