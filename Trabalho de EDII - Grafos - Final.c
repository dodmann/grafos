#include<stdio.h>
#include <locale.h>
#define max 20

int adj[ max ][ max ], n; //declara��o de matriz e n�mero de v�rtices
int visitados[max]; // array para armazenar v�rtices visitados, usado para verificar se existe ciclo euleriano

void exibirGrafo(){
    int i, j;
    printf( "\n*********************************\n" );
    for ( i = 1;i <= n;i++ ){
        for ( j = 1;j <= n;j++ )
            printf( "%4d", adj[ i ][ j ] );
        printf("\n");
    }
    printf( "*********************************\n" );
}

int exibirContagemArestas(){ // Conta a quantidade de arestas do grafo
    int i, j, arestas;
    for ( i = 0;i <= n;i++ ){
        for ( j = 1;j <= n;j++ )
            if( adj[ i ][ j ] == 1){
            	arestas++;	            	
        	}
    }
	return arestas/2;
}

int verificarVertices( ){ // Verifica se o grau de todos os v�rtices � par e retorna 1 caso for verdadeiro
	int i;
	for ( i = 1; i <= n; i++){
		if ( exibirGrauVertice( i ) % 2 != 0 ){
			return 0;
		}
	}
	return 1;
}

int exibirGrauVertice( int u ){ // Mostra grau do v�rtice que � passado por par�metro
    int i, grau = 0;
    for ( i = 0;i <= n;i++ ){
        if( adj[ u ][ i ] == 1){
        	grau++;
    	}
    }
	return grau;
}

void inserirVertice(){ // Fun��o para inserir v�rtices no grafo
    int i;
    n++; //Aumenta o numero de v�rtices do grafo
    printf( "\n*********************************\n" );	
    printf( "Inserido v�rtice de n� %d \n", n );
    printf( "*********************************\n" );
    for ( i = 1;i <= n;i++ ){
        adj[ i ][ n ] = 0;
        adj[ n ][ i ] = 0;
    }
}

void excluirVertice( char u ){ // Fun��o para excluir v�rtices do grafo
    int i, j;
    if ( n == 0 ){
        printf( "\n*********************************\n" );
   	    printf( "Grafo vazio\n" );
        printf( "*********************************\n" );
        return ;
    }
    if ( u > n ){
    	
        printf( "V�rtice n�o presente no grafo.\n" );
        return ;
    }
    for ( i = u;i <= n - 1;i++ )
        for ( j = 1;j <= n;j++ ){
                adj[ j ][ i ] = adj[ j ][ i + 1 ]; /* Puxar colunas para a esquerda */
                adj[ i ][ j ] = adj[ i + 1 ][ j ]; /* Puxar linhas pra cima */
        }
    n--;
}

void inserirAresta( char u, char v ){ // Fun��o para inserir arestas no grafo
    if ( u > n ){
    	printf( "\n*********************************\n" );
        printf( "V�rtice de origem n�o existe.\n" );
        printf( "*********************************\n" );
        return ;
    }
    if ( v > n ){
    	printf( "\n*********************************\n" );
   	    printf( "V�rtice de destino n�o existe.\n" );
        printf( "*********************************\n" );
        return ;
    }
    adj[ u ][ v ] = 1;
    adj[ v ][ u ] = 1;
}

void excluirAresta( char u, char v ){ // Fun��o para excluir arestas do grafo
    if ( u > n || v > n || adj[ u ][ v ] == 0 ){
    	printf ("\n*********************************\n" );
   	    printf( "Aresta n�o existe\n" );
        printf( "*********************************\n" );
        return ;
    }
    adj[ u ][ v ] = 0;
}

int verificarGrafoConexo(int source){ // Fun��o para verificar se o grafo � conexo
        int i = 0;
        int total = 1;        
        visitados[source] = 1;
        //printf("source %d \n", source);
        
        while(i <= n){
            if(adj[source][i] != 0 && visitados[i] != 1){
                //printf("%d %d;", adj[source][i],visitados[i]);
                total = total + verificarGrafoConexo(i);
            }
            i++;
        }
        return total;
}

int main(){
	setlocale( LC_ALL, "Portuguese" );
    int opcao;
    int vertice, origem, destino;
    int i;   
	
	//Menu
    while ( 1 ){
    	printf( "\n------------Grafos---------------\n" );		
        printf( "1.Inserir novo v�rtice\n" );
        printf( "2.Inserir aresta (ex.: 1 1)\n" );
        printf( "3.Excluir v�rtice\n" );
        printf( "4.Excluir aresta (ex.: 1 1)\n" );
        printf( "5.Exibir contagem de v�rtices e arestas\n" );
        printf( "6.Exibir grau do v�rtice\n" );        
        printf( "7.Exibir grafo\n" );        
        printf( "8.Verificar se o grafo possui ciclo euleriano\n" );      
		printf( "9.Sair\n" );    
        printf( "---------------------------------" );	
        printf( "\n" );
        printf( "Digite a op��o desejada : " );
        scanf( "%d", &opcao );
        
        switch ( opcao ){
            case 1:
                inserirVertice();
                break;
            case 2:
                printf( "Digite a aresta a ser inserida : " );
                fflush( stdin );
                scanf( "%d %d", &origem, &destino );
                inserirAresta( origem, destino );
                break;
            case 3:
                printf( "Digite o v�rtice a ser exclu�do : " );
                fflush( stdin );
                scanf( "%d", &vertice );
                excluirVertice( vertice );
                break;
            case 4:
                printf( "Digite os v�rtices da aresta a ser exclu�da : " );
                fflush( stdin );
                scanf( "%d %d", &origem, &destino );
                excluirAresta( origem, destino );
                break;
            case 5:
            	printf( "\n*********************************\n" );
            	printf( "N�mero de v�rtices: %d, n�mero de arestas : %d", n, exibirContagemArestas() );                
                break;
            case 6:
                printf( "Digite o v�rtice a ser verificado o grau : " );
                fflush( stdin );
                scanf( "%d", &vertice );
                printf( "\n*********************************\n" );
			    printf( "V�rtice possui grau %d\n", exibirGrauVertice(vertice));
			    printf( "*********************************\n" );
                break;                
            case 7:
                exibirGrafo();
                break;          	
  		    case 8:
                for(i = 0; i < max; i++){
                    visitados[i] = 0;
                }
                int total = verificarGrafoConexo(1); // Salvar na vari�vel total o retorno da fun��o verifica... e come�ar pelo v�rtice 1
                //printf("\ntotal: %d", total);
                //printf("\nn: %d ", n);
                //printf("\nverificar vertices: %d ", verificarVertices( ) );
               	if ( !(total < n) && verificarVertices( ) == 1 && n != 1 ){ // Comparar se o retorno da fun��o verifica... 
				   	//� maior que a quantidade de v�rtices e se o grau de todos os v�rtices � par
				   	printf( "\n*********************************\n" );
					printf( "Ciclo euleriano presente no grafo." );                						
					printf( "\n*********************************\n" );
				}
               	else{
               		printf( "\n*********************************\n" );
               		printf( "N�o existe ciclo euleriano no grafo." );
               		printf( "\n*********************************\n" );
               	}
                break;
			case 9:
                return ; 				            
            default:
                printf( "Op��o inv�lida.\n" );
                break;
        } 
    }
}
