#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <string.h>

typedef struct horario HORARIO;

struct horario
{
	int hora;
	int minuto;
	int horaf;
	int minutof;
};

typedef struct contato CONTATO;

struct contato
{
	char nome[20];
	char sobrenome[20];
	char fone[15];
	char placa[8];
	char marca[20];
	char modelo[20];
	
	HORARIO tempo;
	
};


int totcaixa;

void msgApresentacao();

void msgValor();

void msgCaixa();

void msgInicial();

void msgInclusao();

void msgSaida();

void msgListar();

void msgRegistro();

void msgPagamento();

void msgAtencao();

void msgEdicao();

void inserirDado(); 

void listar();

void registro();

void buscarNome();

void excluir();

void editar();

void pagamento(int horai, int minutoi, int horaf, int minutof);

void validacao();

void exclusaoTotal();

int totalCaixa(int horai, int minutoi, int horaf, int minutof); 

int menu();


int main(){
	
	setlocale(LC_ALL, "Portuguese");
	
	int inic;
	
	msgApresentacao();
	
	printf("Digite 1 para iniciar o programa ou qualquer outra tecla para sair.\n");
	
	scanf("%d", &inic);

	if(inic == 1)
	{
		menu();
	}
	else
	{
		msgSaida();
		getch();
	}

return 0;
}



int menu()
{
	int menu;
	
	do
	{
		msgInicial();
		
		printf("\n1. Adicionar cliente.\n");
		printf("\n2. Editar cliente.\n");
		printf("\n3. Buscar cliente pelo nome ou placa.\n");
		printf("\n4. Listar todos os clientes ativos.\n");
		printf("\n5. Pagamentos.\n");
		printf("\n6. Reiniciar arquivo.\n");
		printf("\n7. Listar todos os clientes do dia.\n");
		printf("\n8. Mostrar na tela o valor total em caixa.\n");
		printf("\n0. Sair.\n\n");
		
		printf("Escolha uma das op��es: \n\n");
		scanf("%d", &menu);
	
		
		switch(menu)
		{
			case 1:
				//inserir
				inserirDado();
				
				break;
				
			case 2:
				//editar
				editar();
				
				break;
				
			case 3:
				//buscar pela placa ou nome
				buscarNome();
				
				break;
				
			case 4:
				//listagem
				listar();
				
				break;
				
			case 5:
				//remover
				excluir();
				
				break;
				
			case 6:
				
				exclusaoTotal();
				
				break;
				
			case 7:
				
				registro();
				
				break;
				
			case 8:
				
				msgCaixa();
				
				break;
				
				
			case 0:
				
				msgSaida();
				
				return 0;
				
				break;
				
			default:
				
				printf("\nSelecione uma op��o v�lida: \n");
				
				break;
		}
		
	}while (menu != 0);
}

int validacao(const char* testePlaca)
{
	FILE* arqv;
	
	CONTATO ctt;
	
	arqv = fopen("clientes.txt", "rb");
	
	if(arqv == NULL)
	{
		printf("Problemas com abertura do arquivo!\n");
		return 0;
	}
	else
	{
		while(fread(&ctt, sizeof(CONTATO), 1, arqv) == 1)
		{
			if(strcmp(testePlaca, ctt.placa) == 0)
			{
				fclose(arqv);
				return 1;
			}
		}
	}

	fclose(arqv);
	
	return 0;
	
}


void inserirDado()
{
	FILE* arqv;

		
	CONTATO ctt;
	
	arqv = fopen("clientes.txt", "ab");

	
	int op;
	
	if ((arqv == NULL))
	{
		printf("Problemas com abertura do arquivo!\n");
	}
	else
	{
		do
		{
			msgInclusao();
			
			fflush(stdin);
			printf("NOME: \n");
			gets(ctt.nome);
			
			fflush(stdin);
			printf("SOBRENOME: \n");
			gets(ctt.sobrenome);
			
			fflush(stdin);
			printf("TELEFONE PARA CONTATO: \n");
			gets(ctt.fone);
			
			int teste;
			
			do
			{
				fflush(stdin);
				printf("PLACA DO VE�CULO: \n");
				gets(ctt.placa);
				
				teste = validacao(ctt.placa);
				
				if(teste)
				{
					printf("Placa j� inserida no sistema! Digite novamente:\n");
				}
				
			}
			while(teste);
			
			fflush(stdin);
			printf("MARCA DO VE�CULO: \n");
			gets(ctt.marca);
			
			fflush(stdin);
			printf("MODELO DO VE�CULO: \n");
			gets(ctt.modelo);
			
			fflush(stdin);
			printf("HOR�RIO DE ENTRADA: (24H)\n");
			printf("HORA:\n");
			scanf("%d", &ctt.tempo.hora);
			printf("MINUTOS:\n");
			scanf("%d", &ctt.tempo.minuto);
			
			fwrite(&ctt, sizeof(CONTATO), 1, arqv);

			
			printf("Deseja adicionar outro cliente? (1- Sim / 0- N�o)\n\n");
			
			scanf("%d", &op);
			
			
		}while(op == 1);
		
		
		fclose(arqv);
	}
}


void listar()
{
	FILE* arqv;
	
	CONTATO ctt;
	
	arqv = fopen("clientes.txt", "rb");
	
	msgListar();
	
	
	if (arqv == NULL)
	{
		printf("Problemas com abertura do arquivo!\n");
	}
	else
	{
		while(fread(&ctt, sizeof(CONTATO), 1, arqv) == 1)
		{			
			
			printf("NOME: %s\n", ctt.nome);
			printf("SOBRENOME: %s\n", ctt.sobrenome);
			printf("FONE: %s\n", ctt.fone);
			printf("PLACA: %s\n", ctt.placa);
			printf("MARCA: %s\n", ctt.marca);
			printf("MODELO: %s\n", ctt.modelo);
			printf("HOR�RIO DE ENTRADA: %d:%d\n", ctt.tempo.hora, ctt.tempo.minuto);
			
			printf("---------------------------------------------------------------------\n\n");
		}
	}
	
	fclose(arqv);
	
	getch();
}

void registro()
{
	FILE* arqv2;
	
	CONTATO ctt;
	
	arqv2 = fopen("registro.txt", "r");
	
	msgRegistro();
	
	if (arqv2 == NULL)
	{
		printf("Problemas com abertura do arquivo!\n");
	}
	else
	{
		while(fread(&ctt, sizeof(CONTATO), 1, arqv2) == 1)
		{			
			
			printf("NOME: %s\n", ctt.nome);
			printf("SOBRENOME: %s\n", ctt.sobrenome);
			printf("FONE: %s\n", ctt.fone);
			printf("PLACA: %s\n", ctt.placa);
			printf("MARCA: %s\n", ctt.marca);
			printf("MODELO: %s\n", ctt.modelo);
			printf("HOR�RIO DE ENTRADA: %d:%d\n", ctt.tempo.hora, ctt.tempo.minuto);
			printf("HORARIO DE SAIDA: %d:%d\n", ctt.tempo.horaf, ctt.tempo.minutof);
			
			printf("---------------------------------------------------------------------\n\n");
		}
	}
	
	fclose(arqv2);
	
	getch();
}

void buscarNome()
{
    FILE* arqv;
    CONTATO ctt;
    char nome[20];
    int encontrado = 0;

    arqv = fopen("clientes.txt", "rb");

	msgListar();
	
    if (arqv == NULL)
    {
        printf("Problemas com a abertura do arquivo!\n");
    }
    else
    {
        fflush(stdin);
        printf("\nPesquise pelo nome ou placa: \n\n");
        fgets(nome, 20, stdin);
        nome[strcspn(nome, "\n")] = '\0';

        while(fread(&ctt, sizeof(CONTATO), 1, arqv) == 1)
        {
            if(strcmp(nome, ctt.nome) == 0 || strcmp(nome, ctt.placa) == 0)
            {
                printf("NOME: %s\n", ctt.nome);
                printf("SOBRENOME: %s\n", ctt.sobrenome);
                printf("FONE: %s\n", ctt.fone);
                printf("PLACA: %s\n", ctt.placa);
                printf("MARCA: %s\n", ctt.marca);
                printf("MODELO: %s\n", ctt.modelo);
                printf("HOR�RIO DE ENTRADA: %d:%d\n", ctt.tempo.hora, ctt.tempo.minuto);

                printf("---------------------------------------------------------------------\n\n");

                encontrado = 1; 
            }
        }

        if (!encontrado)
        {
            printf("\nCliente n�o encontrado.\n");
        }
    }

    fclose(arqv);
    getch();
}


void pagamento(int horai, int minutoi, int horaf, int minutof) {
    
	CONTATO ctt;
    int tempoTotal, difhoras, totFinal, totInicial;
    float total;
    
    totInicial = ((horai*60) + minutoi);
	totFinal = ((horaf*60) + minutof);
	
	difhoras = totFinal - totInicial;
    
    if (difhoras < 0)
    {
    	difhoras = (1440 - totInicial) + totFinal;
	}

	tempoTotal = difhoras/60;

    total = 5 + (2*tempoTotal);

    printf("\nTotal a pagar R$ = %.2f\n", total);
    
}

int totalCaixa(int horai, int minutoi, int horaf, int minutof) 
{
    
	CONTATO ctt;
    int tempoTotal, difhoras, totFinal, totInicial;
    float total;
    
    totInicial = ((horai*60) + minutoi);
	totFinal = ((horaf*60) + minutof);
	
	difhoras = totFinal - totInicial;
    
    if (difhoras < 0)
    {
    	difhoras = (1440 - totInicial) + totFinal;
	}

	tempoTotal = difhoras/60;

    total = 5 + (2*tempoTotal);
    
    return total;
	
}

void excluir() {
    FILE* arqvorigem;
    FILE* arqvtemp;
    FILE* arqv2;

    CONTATO ctt;
	
	int encontrado = 0;
    char placa[8];
    int hf, mf, pgt;

    arqvorigem = fopen("clientes.txt", "rb");

    arqvtemp = fopen("clientestemp.txt", "ab");
    
    arqv2 = fopen("registro.txt", "ab");
    
    msgPagamento();

    if ((arqvorigem == NULL) || (arqvtemp == NULL) || (arqv2 == NULL)) 
	{
        printf("\nProblemas com a abertura do arquivo.\n");
    } else 
	{
		
        fflush(stdin);
        printf("Digite a placa do ve�culo: \n");
        fgets(placa, sizeof(placa), stdin);
        placa[strcspn(placa, "\n")] = '\0';
        

        while (fread(&ctt, sizeof(CONTATO), 1, arqvorigem)) 
		{
            if (strcmp(placa, ctt.placa) == 0) 
			{
                printf("NOME: %s\n", ctt.nome);
                printf("SOBRENOME: %s\n", ctt.sobrenome);
                printf("FONE: %s\n", ctt.fone);
                printf("PLACA: %s\n", ctt.placa);
                printf("MARCA: %s\n", ctt.marca);
                printf("MODELO: %s\n", ctt.modelo);
                printf("HOR�RIO DE ENTRADA: %d:%d\n", ctt.tempo.hora, ctt.tempo.minuto);
                printf("\n");
                printf("DIGITE O HOR�RIO DE SA�DA: (24H)\n");
				printf("HORA\n");
                scanf("%d", &ctt.tempo.horaf);
                printf("MINUTO\n");
                scanf("%d", &ctt.tempo.minutof);

                pagamento(ctt.tempo.hora, ctt.tempo.minuto, ctt.tempo.horaf, ctt.tempo.minutof);
				printf("\n");
                printf("O valor foi pago? (1- Sim / 0- N�o)\n");
                scanf("%d", &pgt);
                
                encontrado = 1;

                if (pgt == 1) 
				{
					totcaixa += totalCaixa(ctt.tempo.hora, ctt.tempo.minuto, ctt.tempo.horaf, ctt.tempo.minutof);
					printf("\nPagamento efetuado com sucesso!\n");
					fwrite(&ctt, sizeof(CONTATO), 1, arqv2);
                    
                } 
				else 
				{
					printf("Pagamento n�o efetuado.\n");
                    fwrite(&ctt, sizeof(CONTATO), 1, arqvtemp);
                    
                }
            } 
			else 
			{	
				fwrite(&ctt, sizeof(CONTATO), 1, arqvtemp);
            }
        }
        
        if(!encontrado)
        {
        	printf("Cliente n�o encontrado.\n");
		}
    
    }

    fclose(arqvorigem);
    fclose(arqvtemp);
	fclose(arqv2);

    remove("clientes.txt");
    rename("clientestemp.txt", "clientes.txt");

    getch();
}

void editar()
{
	FILE* arqv;
	
	CONTATO ctt;
	
	arqv = fopen("clientes.txt", "rb+");
	
	int i = 1;
	int indice;
	
	msgEdicao();
	
	if (arqv == NULL)
    {
        printf("Problemas com a abertura do arquivo!\n");
    }
    else
    {
    	while(fread(&ctt, sizeof(CONTATO), 1, arqv) == 1)
    	{
    		printf("\n----------- %d -----------\n", i);
			printf("NOME: %s\n", ctt.nome);
    		printf("SOBRENOME: %s\n", ctt.sobrenome);
    		printf("TELEFONE: %s\n", ctt.fone);
    		printf("--------------------------\n\n");
    		i++;	
		}
		if(i>1)
		{
    		do{
				printf("Que contato deseja alterar? (Digite o valor do �ndice ou 0 para sair)\n");
	    		
	    		scanf("%d", &indice);
	    		fflush(stdin);
	    		
	    		
	    		printf("\n");
	    		
	    		if(indice<0 || indice>i)
	    		{
	    			printf("Opcao invalida. Tente novamente.\n");
				}
				
				
	    		
			}while(indice<0 || indice>i);
    		
    		indice--;
    		
    		if((indice >= 0) && (indice < i-1))
    		{
    			int op;
    			do
				{
					printf("1. Editar nome\n");
					printf("2. Editar sobrenome\n");
					printf("3. Editar telefone\n");
					printf("0. Sair.\n\n");
					
					printf("Escolha uma op��o:\n");
					scanf("%d", &op);
					
					if(op == 1)
					{
						printf("Digite o novo nome:\n");
						fflush(stdin);
						scanf("%s", ctt.nome);
						printf("\n");
						
						fseek(arqv, indice * sizeof(CONTATO), SEEK_SET);
						fwrite(&ctt, sizeof(CONTATO), 1, arqv);
						
						printf("Op��o alterada com sucesso!\n");
						getch();
						printf("\n\n");
						
					}
					else if(op == 2)
					{
						printf("Digite o novo sobrenome:\n");
						fflush(stdin);
						scanf("%s", ctt.sobrenome);
						printf("\n");
						
						fseek(arqv, indice * sizeof(CONTATO), SEEK_SET);
						fwrite(&ctt, sizeof(CONTATO), 1, arqv);
						
						printf("Op��o alterada com sucesso!\n");
						getch();
						printf("\n\n");
						
					}
					else if(op == 3)
					{
						printf("Digite o novo telefone:\n");
						fflush(stdin);
						scanf("%s", ctt.fone);
						printf("\n");
						
						fseek(arqv, indice * sizeof(CONTATO), SEEK_SET);
						fwrite(&ctt, sizeof(CONTATO), 1, arqv);
						
						printf("Op��o alterada com sucesso!\n");
						getch();
						printf("\n\n");
						
						
					}
					else if(op == 0)
					{
						break;
					}
					else
					{
						printf("Digite uma op��o v�lida.\n\n");
					}
					
				}
				while(op != 0);
			}
		}
		else
		{
			printf("Sem clientes para editar.\n");
			getch();	
		}
    		fclose(arqv);
		
    }
    
    fclose(arqv);
	
}

void exclusaoTotal() {
    FILE* arqv;
    FILE* arqvtemp;
    FILE* arqv2;
    FILE* arqv2temp;
    
    CONTATO ctt;

    arqv = fopen("clientes.txt", "rb");
    arqvtemp = fopen("clientestemp.txt", "ab");
    arqv2 = fopen("registro.txt", "r");
    arqv2temp = fopen("registrotemp.txt", "a");
	
    int op;
	
	msgAtencao();
	
    if ((arqv == NULL) || (arqvtemp == NULL) || (arqv2 == NULL) || (arqv2temp == NULL)) 
	{
        printf("\nProblemas com a abertura do arquivo.\n");
    } 
	else 
	{
        printf("Tem certeza que deseja excluir todos os clientes inseridos? (1- Sim / 0- N�o) \n");
        scanf("%d", &op);

        if (op == 1) 
		{
            while (fread(&ctt, sizeof(CONTATO), 1, arqv) == 1) 
			{
            }
            while (fread(&ctt, sizeof(CONTATO), 1, arqv2) == 1) 
			{
            }
        } 
		else 
		{
            fclose(arqv);
            fclose(arqvtemp);
            fclose(arqv2);
            fclose(arqv2temp);
            
            return;
        }
    }

    fclose(arqv);
    fclose(arqvtemp);
    fclose(arqv2);
	fclose(arqv2temp);
	
    remove("clientes.txt");
    rename("clientestemp.txt", "clientes.txt");
	remove("registro.txt");
	rename("registrotemp.txt", "registro.txt");
	
	
    printf("----------------------------------------------------\n");
    printf("         Clientes exclu�dos com sucesso!\n");
    printf("----------------------------------------------------\n");
    getch();
}


void msgCaixa()
{
	FILE* arqv2;

	arqv2 = fopen("registro.txt", "rb");
	
	system("cls");
	
	printf("--------------------------------------------------------------------------\n");
	
	printf("            VALOR TOTAL EM CAIXA R$ = %d\n", totcaixa);
	
	printf("--------------------------------------------------------------------------\n\n");
	
	fclose(arqv2);
	
	getch();
}

void msgApresentacao()
{
	system("cls");
	
	printf("--------------------------------------------------------------------------\n");
	
	printf("BEM-VINDO, PROJETO DESENVOLVIDO NA DISCIPLINA INTRODU��O A PROGRAMA��O.\n");
	printf("O PROJETO E UMA CRUD QUE CONSISTE EM UM SISTEMA PARA CONTROLE DE CLIENTES DE UM ESTACIONAMENTO.\n");
	printf("NESSE APLICATIVO VOC� PODE INCLUIR UM CLIENTE, LISTAR TODOS OS CLIENTES, FILTRAR POR NOME OU \nPLACA DO VE�CULO, EXCLUIR TODO O REGISTRO E VER O TOTAL A SER PAGO POR CADA CLIENTE. \n");
	printf("NESSE PROGRAMA O VALOR DO ESTACIONAMENTO � DADO POR UM VALOR FIXO + UM VALOR QUE VARIA DE ACORDO \nCOM A QUANTIDADE DE HORAS EM QUE O CLIENTE PERMANECEU NO ESTACIONAMENTO TAL COMO UM ESTACIONAMENTO DE SHOPPING.\n");
	printf("O VALOR DO ESTACIONAMENTO � FIXO EM R$5 EM AT� 1 HORA DE USO MAIS R$2 PARA CADA HORA ADICIONAL");
	printf("\n\n");
	printf("--------------------------------------------------------------------------\n\n");
}



void msgInicial()
{

	system("cls");
	
	printf("--------------------------------------------------------------------------\n");
	
	printf("      MENU DE OP��ES // SISTEMA PARA CLIENTES DE ESTACIONAMENTO\n");
	
	printf("--------------------------------------------------------------------------\n\n");
	
}

void msgInclusao()
{
	
	system("cls");
	
	printf("--------------------------------------------------------------------------\n");
	
	printf("                        INCLUS�O DE CLIENTES\n");
	
	printf("--------------------------------------------------------------------------\n\n");
	
}

void msgSaida()
{
	
	system("cls");
	
	printf("--------------------------------------------------------------------------\n");
	
	printf("                OBRIGADO POR UTILIZAR NOSSO SERVI�O\n");
	
	printf("--------------------------------------------------------------------------\n\n");
	
}

void msgListar()
{
	
	system("cls");
	
	printf("--------------------------------------------------------------------------\n");
	
	printf("                LISTA DE CLIENTES ATIVOS\n");
	
	printf("--------------------------------------------------------------------------\n\n");
	
}

void msgRegistro()
{
	
	system("cls");
	
	printf("--------------------------------------------------------------------------\n");
	
	printf("                REGISTRO DE TODOS OS CLIENTES\n");
	
	printf("--------------------------------------------------------------------------\n\n");
	
}

void msgAtencao()
{
	system("cls");
	
	printf("--------------------------------------------------------------------------\n");
	
	printf("   ATEN��O! VOCE EST� PRESTES A EXCLUIR TODOS OS REGISTROS DO ARQUIVO!\n");
	
	printf("--------------------------------------------------------------------------\n\n");
}

void msgPagamento()
{
	system("cls");
	
	printf("--------------------------------------------------------------------------\n");
	
	printf("                       TELA DE PAGAMENTO\n");
	
	printf("--------------------------------------------------------------------------\n\n");
}



void msgEdicao()
{
	system("cls");
	
	printf("--------------------------------------------------------------------------\n");
	
	printf("                    TELA DE EDI��O DE REGISTRO\n");
	
	printf("--------------------------------------------------------------------------\n\n");
}
