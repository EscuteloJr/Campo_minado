#include<stdio.h>
#include<stdlib.h>

int z , maxLinha , maxColuna ;

// Funcao que inicialmente carrega o Tabuleiro , de 1 a (n x m )
//--------------------------------------------------------------INICIALIZAR O TABULEIRO----------------------------------------------//
void inicializar_Tabuleiro(int tabuleiro[][maxColuna] , int i , int j )
	{
			if ( i < maxLinha )
				if ( j < maxColuna )
					{
						    tabuleiro[i][j] = -100 ;
							inicializar_Tabuleiro( tabuleiro , i , j + 1  );	
					}
					else
						inicializar_Tabuleiro( tabuleiro , i + 1 , 0   );				
		 
	}
//----------------------------------------------------------VERIFICAR BOMBAS VIZINHAS---------------------------------------------//

int bombasVisinhas ( int tabuleiro[][maxColuna] , int i , int j  )
{
	int cont = 0;
		
	if ( j - 1 >= 0 )
	 	if ( tabuleiro[i][j -1] == -1 || tabuleiro[i][j-1] == -101 )
	  	  	cont++;
	  	  	
	if( j + 1 <= maxColuna -1)
		if ( tabuleiro[i][j +1] == -1 || tabuleiro[i][j+1] == -101 )
	  	  	cont++;
	  	  	
	if( i - 1 >= 0)	
	{
		if( j - 1 >= 0 )
			if ( tabuleiro[i-1][j -1] == -1 || tabuleiro[i-1][j-1] == -101 )
	  	  		cont++;
	  	  		
	  	if( j + 1 <= maxColuna - 1)  
		  if ( tabuleiro[i-1][j +1] == -1 || tabuleiro[i-1][j+1] == -101 )
	  	  	cont++;
	  	  	
	  	 if ( tabuleiro[i-1][j] == -1 || tabuleiro[i-1][j] == -101 )
	  	  	cont++; 					
	 }
	 if( i + 1 <= maxLinha - 1)
	 {
	 	if( j - 1 >= 0)  
		  if ( tabuleiro[i+1][j -1] == -1 || tabuleiro[i+1][j-1] == -102 )
	  	  	cont++;
	  	  	
	  	if( j + 1 <= maxColuna - 1)  
		  if ( tabuleiro[i+1][j +1] == -1 || tabuleiro[i+1][j+1] == -101 )
	  	  	cont++;
	  	  
	  if ( tabuleiro[i+1][j] == -1 || tabuleiro[i+1][j] == -101 )
	  	  	cont++;			
	  }	
	return cont;
}
/* Funcao que imprime o Tabuleiro a cada tentativa, atualizando
os numeros ja digitados pelo usuario como bomba=B e nao-bomba=* */
void desenhar1 (  )
{	  		 	
	int h ;
	for ( h = 1 ; h <= maxColuna ; h++ )
	if ( h == 1)
		printf("  +---");
	else if ( h == maxColuna ) 
	  	printf("---+\n");
	else
		printf("---");			
}
void desenhar2 (  )
{
	int h ;
	for ( h = 1 ; h <= maxColuna ; h++ )
			if ( h == maxColuna )
		     	printf("  %d\n", h);
		    else if ( h == 1) 
		    	printf("    %d", h);
			else
				printf("  %d", h);
}
//-----------------------------------------------------------VERIFICAR POSICOES ABERTAS--------------------------------------------------------//
int livres( int tabuleiro[][maxColuna] , int i , int j )
{
	if ( i < maxLinha ) 
		if ( j < maxColuna )
			{	
				if ( tabuleiro[i][j] >= 0 )
					return 1 + livres( tabuleiro , i , j + 1 ); 					
				return 0 +	livres( tabuleiro , i , j + 1 );
			}
		else
			return 0 + livres( tabuleiro , i + 1 , 0 );	
	return 0 ;					    	
}
//----------------------------------------------------------VERIFICAR POSICOES MARCADAS-------------------------------------------------------//
int marcadas( int tabuleiro[][maxColuna] , int i , int j )
{
	if ( i < maxLinha ) 
		if ( j < maxColuna )
			{	
				if ( tabuleiro[i][j] == -101 || tabuleiro[i][j] == -102 )
					return 1 + marcadas( tabuleiro , i , j + 1 ); 					
				return 0 +	marcadas( tabuleiro , i , j + 1 );
			}
		else
			return 0 + marcadas( tabuleiro , i + 1 , 0 );	
	return 0 ;					    	
}
//--------------------------------------------------------IMPRIMIR O TABULEIR0----------------------------------------------------------------//
void imprimir_Tabuleiro(int tabuleiro[][maxColuna] , int i , int j , int n )
{
			   	if ( i + j == 0 )
	 			{
	 				if ( n != 1 )
				    printf("Por enquanto : %d/%d marcadas e %d livres \n\n", marcadas(tabuleiro,0,0) , z , livres(tabuleiro,0,0) );
	 				desenhar2();
	 				desenhar1();
				 }
			   	if ( i < maxLinha ) 
					if ( j < maxColuna )
						{
							if ( j == 0 )
								printf("%d |", i+1);
							if (  tabuleiro[i][j] >= 0 )
								printf(" %d ",tabuleiro[i][j]); 
							else if ( tabuleiro[i][j] < 0 )	
									if ( tabuleiro[i][j] == -101 || tabuleiro[i][j] == -102)
											printf(" * ");
									else if ( tabuleiro[i][j] == -100 )		
										printf(" . ");
									else if (tabuleiro[i][j] == -1 )
										if ( n == 0 )
											printf(" . ");		
										else
											printf(" @ ");	 					
							imprimir_Tabuleiro( tabuleiro , i , j + 1 , n );
						}
					else
					{
						printf("| %d\n", i+1);
						imprimir_Tabuleiro( tabuleiro , i + 1 , 0 , n);	
					}
				if ( i >= maxLinha )
				{
					desenhar1 ();
					desenhar2 ();
				}				    		
}
//------------------------------------------------------------------ADICIONAR BOMBAS AO TABULEIRO--------------------------------------------//
void adicionar_Bombas(int tabuleiro[][maxColuna] , int numeroBombas , int semente  , int i , int j , int contador)
	{
		int  linha , coluna ,  numero ;
		if ( i  == 0 && j == 0)
			srand(semente);
			
			if ( i < maxLinha )
				if ( j < maxColuna )
					{
							if ( contador  <= numeroBombas)
							{
								numero =  rand() ;
								linha = numero % maxLinha   + 1 ;
								coluna = (( numero / maxLinha    ) % maxColuna   )+ 1 ;
								linha --;
								coluna --;
								tabuleiro[linha][coluna] = -1;
							}
							else 
								i = maxLinha;
							adicionar_Bombas( tabuleiro , numeroBombas , semente , i , j + 1 , contador+1 );	
					}
					else
						adicionar_Bombas( tabuleiro , numeroBombas , semente, i + 1 , 0  , contador );		
	}
//----------------------------------------------------------------DESMARCAR AS POSICOES DO TABULEIRO-----------------------------------//	
void explodir( int tabuleiro [][maxColuna] , int i, int j)
{
	if ( i < maxLinha )
		if(j < maxColuna )
		{
			if ( tabuleiro[i][j] != -1)
				tabuleiro[i][j] = bombasVisinhas (tabuleiro,  i , j  );
			explodir(  tabuleiro  , i, j + 1);	
		}
		else
			explodir(  tabuleiro  , i +1, 0);
}
void abrir ( int tabuleiro [][maxColuna] , int i, int j)
{
	if ( tabuleiro[i][j] == -100 )
		tabuleiro[i ][j ] = bombasVisinhas (tabuleiro,  i , j  );
		
	if ( j - 1 >= 0 )
	 	if ( tabuleiro[i][j -1]  == -100 )
	  	  	tabuleiro[i][j -1] = bombasVisinhas (tabuleiro,  i , j -1 );
	  	  	
	if( j + 1 <= maxColuna -1)
		if ( tabuleiro[i][j +1] == -100 )
	  	  	tabuleiro[i][j +1] = bombasVisinhas (tabuleiro,  i , j +1 );
	  	  	
	if( i - 1 >= 0)	
	{
		if( j - 1 >= 0 )
			if ( tabuleiro[i-1][j -1]  == -100 )
	  	  		tabuleiro[i-1][j -1] = bombasVisinhas (tabuleiro,  i-1 , j -1 );
	  	  		
	  	if( j + 1 <= maxColuna - 1)  
		  if ( tabuleiro[i-1][j +1]  == -100 )
	  	  	tabuleiro[i-1][j +1] = bombasVisinhas (tabuleiro,  i-1 , j +1 );
	  	  	
	  	 if ( tabuleiro[i-1][j]  == -100 )
	  	  	tabuleiro[i-1][j +1] = bombasVisinhas (tabuleiro,  i-1 , j );  					
	 }
	 if( i + 1 <= maxLinha - 1)
	 {
	 	if( j - 1 >= 0)  
		  if ( tabuleiro[i+1][j -1] == -100  )
	  	  	tabuleiro[i+1][j -1] = bombasVisinhas (tabuleiro,  i+1 , j -1 );
	  	  	
	  	if( j + 1 <= maxColuna - 1)  
		  if ( tabuleiro[i+1][j +1]  == -100 )
	  	  	tabuleiro[i+1][j +1] = bombasVisinhas (tabuleiro,  i+1 , j +1 );
	  	  
	  if ( tabuleiro[i+1][j]  == -100  )
	  	  	tabuleiro[i+1][j] = bombasVisinhas (tabuleiro,  i+1 , j );			
	  }					 	
	
}
//----------------------------------------------JOGADAS --------------------------------------------------------------------------------//		
int verificar( int tabuleiro[][maxColuna] , int cond , char chutes[] , int vetor[] , int numeroDeChutes )	
	{
	   int numero , linha , coluna ;
	   if ( tabuleiro[vetor[0]][vetor[1]] < 0 )
	   {
	   	if ( cond == 1 )//Abrir
		{
					if (tabuleiro[vetor[0]][vetor[1]] == -1 )
						{
							if( numeroDeChutes == 1 )
							{
							 numero =  rand() ;
							 	linha = ((numero % maxLinha )+ 1);
							 	coluna = ((( numero / maxLinha  ) % maxColuna )+ 1);
							 while( tabuleiro[linha -1 ][ coluna -1 ] == -1 ){
							 	numero =  rand() ;
							 	linha = ((numero % maxLinha )+ 1);
							 	coluna = ((( numero / maxLinha  ) % maxColuna )+ 1);
							 }	
							 tabuleiro[ linha - 1][coluna - 1 ] = -1;	
							 tabuleiro[vetor[0]][vetor[1]] = bombasVisinhas (  tabuleiro ,  vetor[0] ,  vetor[1] );
							}
							else
							return -1 ;
					}
					else if (tabuleiro[vetor[0]][vetor[1]] == -101 || tabuleiro[vetor[0]][vetor[1]] == -102)
						printf("Sem Efeito\n");
					else
					abrir (  tabuleiro , vetor[0] ,  vetor[1]  );
					return 0;	
		}
		else if ( cond == 2 )//Descmarcar
		{
			if ( tabuleiro[vetor[0]][vetor[1]] != -101 && tabuleiro[vetor[0]][vetor[1]] != -102  )
				printf("Sem Efeito\n");
			else	
				{	
					if ( tabuleiro[vetor[0]][vetor[1]]  == -101)
						tabuleiro[vetor[0]][vetor[1]] = -1  ;	
					else	
					tabuleiro[vetor[0]][vetor[1]] = -100 ; 	
					return 0 ;	
				}
		}
		else if ( cond == 3 )//Marcar
		{
			if ( tabuleiro[vetor[0]][vetor[1]] == -101 || tabuleiro[vetor[0]][vetor[1]] == -102  )
			{
				printf("Sem Efeito\n");
				return 0 ;
			}
			
			else
			{
				if ( tabuleiro[vetor[0]][vetor[1]] == -1  )
				tabuleiro[vetor[0]][vetor[1]]  = -101 ;
				else	
				tabuleiro[vetor[0]][vetor[1]]  = -102 ;	
				return 0 ;
					}		
			

		}
		else
			return - 1;
	   }
	   else
	   		printf("Sem Efeito\n");
		
	}
//--------------------------------------------------------VERIFICAR OD DADOS DE ENTRADA--------------------------------------------//
int verificarDados ( int maxLinha , int maxColuna , int z , int semente )
	{
		if ( maxLinha >= 3 )
		  if( maxLinha <= 90 )
		  	if ( maxColuna >= 3 )
		  		if ( maxColuna <= 90 )
		  			if ( z <= maxLinha * maxColuna )
		  			 	if ( semente >= 1 )
		  			 		if ( semente <= 65535)
		  			 			 return 1 ;
		return 0 ;  			 			 
	}
//------------------------------------------------------LER OS CHUTES DO JOGADOR--------------------------------------------------//
void lerChutes ( char chutes[] , int vetorint[] )
	{
		printf("\nProximo Chute  :  \n");
 		scanf("%s%d%d",&chutes[0],&vetorint[0],&vetorint[1]);
 		vetorint[0] -= 1;
		vetorint[1] -= 1;
	}
//------------------------------------------------------VERIFICAR OS CHUTES DO JOGADOR-------------------------------------------//	
int validarChutes ( char chutes[]  , int numeroChutes , int vetor [] )	
	{
		int cond = 0 ;
		
		if( chutes[0] == 'A' )
			cond = 1;
		else if( chutes[0] == 'a' )
			cond = 1;
		else if( chutes[0] == 'D' )
			cond = 2;
		else if( chutes[0] == 'd' )
			cond = 2;
		else if( chutes[0] == 'M' )
			cond = 3;
		else if( chutes[0] == 'm' )
			cond = 3;
		if ( cond != 0 )
		{
			if ( numeroChutes == 1 )
				cond = 1 ;
			if ( vetor[0]  < 0  || vetor[0]  > maxLinha - 1  )
			    	cond = 0 ;
			if( vetor[1]  < 0  || vetor[1]  > maxColuna - 1  )
					cond = 0 ; 
			}
		return cond ;		
	}
/*
                ------------------------------------------------------MAIN-------------------------------------------------------
*/	
int main ()
	{
		int semente ;
		
		do {
			printf("Digite o tamanho do Tabuleiro \nDefinido por (m x n) e o numero de minas  ");
			printf("\nNumero de Linhas m : \n");
			scanf("%d",&maxLinha);
			printf("Numero de Colunas n :\n");
			scanf("%d",&maxColuna);
			printf("Numero de Minas z :\n");
			scanf("%d",&z);
			printf("Digite a Semente s :\n");
			scanf("%d",&semente);
			printf("\n\nNumero de linhas ( 3 <= m <= 90 ) : %d \nNumero de Colunas ( 3 <= n <= 90 ) : %d \nNumero de Minas ( 1 <= z <= %d) : %d \nSemente (1 <= s <= 65535 ) : %d\n\n",maxLinha , maxColuna , maxLinha*maxColuna , z , semente);
			
		}while(verificarDados ( maxLinha , maxColuna ,  z ,  semente ) == 0);
		
			int tabuleiro[maxLinha][maxColuna] , escolha = 0 , contador = 2 , numeroDeChutes = 0 , vetorint[2] ;
			char chutes [1] ;
			inicializar_Tabuleiro( tabuleiro , 0 , 0  );
			adicionar_Bombas(tabuleiro,z, semente ,0 ,0 , 1);
			imprimir_Tabuleiro(tabuleiro , 0 , 0 , 0);
			
			do{
				
			if ( livres(tabuleiro,0,0) != maxLinha*maxColuna - z ) 
			{
				
				lerChutes (  chutes ,  vetorint );
				numeroDeChutes++;
				system("cls"); // Limpa a tela 
					if ( validarChutes(chutes , numeroDeChutes , vetorint) != 0 )
				{
					if ( 	verificar( tabuleiro ,  validarChutes(chutes , numeroDeChutes , vetorint ) , chutes , vetorint , numeroDeChutes ) == -1 )
					{
						system("cls"); // Limpa a tela 
						printf("BOOOOOM! Voce Acaba de Pisar uma Mina\n");
						explodir(tabuleiro ,  0 ,  0 );
	 					imprimir_Tabuleiro(tabuleiro ,  0 ,  0 , 1 );
						escolha = -1;
					}	
					else
						imprimir_Tabuleiro(tabuleiro , 0 , 0 , 0 );	
				}
				else
					printf("Sem Efeito\n");
			}
			else
			{
				printf("Parabens Ganhou");
		  		escolha = -1;
			}
			
		}while ( escolha != -1 );
		
		return 0 ;
	}
