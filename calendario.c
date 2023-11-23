#include <stdio.h>

// Verifica se o ano é bissexto
int anoBissexto(int ano);

// Verifica se o valor está entre mínimo e máximo. Se não estiver, devolve uma mensagem indicando a gama de valores que pode ser introduzido
int checkValor(int input, int min, int max, char descricao[]);

// Mostra o calendário para o mês e ano introduzido (utiliza <mostrarCalendarioDoMes>)
void mostrarCalendario(int ano, int mes);

// Apenas para a formatação do calendário coloca um número x de "#"
void mostrarCerquilha(int tamanho);

// Apresenta os dias do mês de acordo com o mês.
void mostrarCalendarioDoMes(int diasDoMes, int diaDaSemana);

// Calcula em que dia da semana um dia específico cai. A função é utilizada dentro de <mostrarCalendarioDoMes> para determinar em que dia da semana o primeiro dia do mês começa
int calcularDiaDaSemana(int dia, int mes, int ano);

// Calcula o século
int calcularSeculo(int ano);

//////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// MAIN ///////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

int main(void)
{
  int mes;
  int ano;
  int diasDosMeses[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  char meses[][30] = {"JANEIRO", "FEVEREIRO", "MARÇO", "ABRIL", "MAIO", "JUNHO", "JULHO", "AGOSTO", "SETEMBRO", "OUTUBRO", "NOVEMBRO", "DEZEMBRO"};

  printf("Por favor indique o ano: ");
  scanf("%d", &ano);

  while (checkValor(ano, 1600, 3999, "ano") != 1)
  {
    scanf("%d", &ano);
  }

  printf("Por favor, indique o mês: ");

  scanf("%d", &mes);

  while (checkValor(mes, 1, 12, "mês") != 1)
  {
    scanf("%d", &mes);
  }

  putchar('\n');

  printf("%s: %d\n", meses[mes - 1], ano);
  mostrarCalendario(ano, mes);
  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// FUNCTIONS ///////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

// VERIFICA SE O ANO É BISSEXTO
int anoBissexto(int ano)
{
  if (ano % 400 == 0)
  {
    return 1;
  }
  else if (ano % 100 == 0)
  {
    return 0;
  }
  else if (ano % 4 == 0)
  {
    return 1;
  }
  return 0;
}

// VERIFICA SE O VALOR INTRODUZIDO ESTÁ ENTRE O MÍNIMO E O MÁXIMO
int checkValor(int input, int min, int max, char descricao[])
{
  if (input > max || input < min)
  {
    printf("Por favor, introduza um %s entre %d e %d\n", descricao, min, max);
    return 0;
  }
  return 1;
}

// MOSTRA O CALENDÁRIO
void mostrarCalendario(int ano, int mes)
{
  char diasDaSemanaArr[7] = {'D', 'S', 'T', 'Q', 'Q', 'S', 'S'};
  int diaDaSemana = calcularDiaDaSemana(1, mes, ano);
  int bissexto = anoBissexto(ano);
  int diasDosMeses[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (bissexto == 1)
  {
    diasDosMeses[1] = 29;
  }

  mostrarCerquilha(23);

  putchar('\n');

  printf("# ");

  for (int i = 0; i < 7; i++)
  {
    if (i == 6) // Por conta da formatacao entre S e #
    {
      printf("%c ", diasDaSemanaArr[i]);
      break;
    }
    printf("%c  ", diasDaSemanaArr[i]);
  }
  putchar('#');
  putchar('\n');

  mostrarCerquilha(23);
  putchar('\n');

  // Passando os valores para <mostrarCalendarioDoMes>
  mostrarCalendarioDoMes(diasDosMeses[mes - 1], diaDaSemana);
  putchar('\n');
}

// MOSTRA A CERQUILHA
void mostrarCerquilha(int tamanho)
{
  for (int i = 0; i < tamanho; i++)
  {
    putchar('#');
  }
}

// CALCULA EM QUE DIA DA SEMANA O DIA ESTÁ (PARA QUE POSSAMOS FORMATAR O CALENDÁRIO)
int calcularDiaDaSemana(int dia, int mes, int ano)
{
  if (ano < 0 || mes > 13 || dia < 1 || dia > 31 || ano > 9999)
  {
    return -1;
  }

  int codigosDosMesesArr[12] = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};
  int seculo = calcularSeculo(ano);
  int bissexto = anoBissexto(ano);

  int codigoDoSeculo;
  int codigoDoAno;
  int codigoDoAnoDividido;
  int codigoDoMes;
  int diaDaSemana;

  // CODIGO DO SECULO
  if ((seculo - 1) % 4 == 0)
  {
    codigoDoSeculo = 6;
  }
  else if ((seculo - 1) % 4 == 1)
  {
    codigoDoSeculo = 4;
  }
  else if ((seculo - 1) % 4 == 2)
  {
    codigoDoSeculo = 2;
  }
  else if ((seculo - 1) % 4 == 3)
  {
    codigoDoSeculo = 0;
  }

  // CODIGOS DO ANO
  codigoDoAno = (ano % 100);
  codigoDoAnoDividido = codigoDoAno / 4;

  // CODIGO DO MES
  codigoDoMes = codigosDosMesesArr[mes - 1];

  diaDaSemana = (codigoDoAno + codigoDoAnoDividido + dia + codigoDoMes + codigoDoSeculo) % 7;

  if (bissexto == 1)
  {
    return diaDaSemana - 1;
  }

  return diaDaSemana;
}

int calcularSeculo(int ano)
{
  int seculo = ano / 100;
  if (ano % 100 == 0)
  {
    return seculo;
  }
  return seculo + 1;
}

void mostrarCalendarioDoMes(int diasDoMes, int diaDaSemana)
{
  int i;
  int dia = 1;
  putchar('#');

  for (i = 0; i < 42; i++)
  {
    if (i % 7 == 0 && i != 0) // Coloca '#' e \n nos locais apropriados
    {
      putchar('#');
      putchar('\n');
      if (i < 38)
      {
        putchar('#');
      }
    }
    if (dia <= diasDoMes)
    {
      if (i >= diaDaSemana)
      {
        printf("%2d ", dia++);
      }
      else
      {
        printf("   ");
      }
    }
    else // Coloca os espaços ao final dos dias
    {
      printf("   ");
    }
  }
  putchar('#');
  putchar('\n');
  mostrarCerquilha(23);
}
