#include "decompress.h"

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("Por favor, forneça o nome do arquivo como argumento.\n");
    return 1;
  }

  char *nome_do_arquivo = argv[1];

  decompress(nome_do_arquivo);

  printf("Pressione qualquer tecla para continuar . . .\n");
  getchar();

  system("@cls||clear");

  return 0;
}