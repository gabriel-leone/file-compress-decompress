#include "compress.h"

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("Por favor, forneça o nome do arquivo como argumento.\n");
    return 1;
  }

  char *nome_do_arquivo = argv[1];

  while (1)
  {
    compress(nome_do_arquivo);
    system("pause");
    break;
  }
  system("cls");
}