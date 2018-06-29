#include<stdio.h>
#include <locale.h>
#define max 20

int adj[ max ][ max ], n; //declaração de matriz e número de vértices
int visitados[max]; // array para armazenar vértices visitados, usado para verificar se existe ciclo euleriano

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

int verificarVertices( ){ // Verifica se o grau de todos os vértices é par e retorna 1 caso for verdadeiro
	int i;
	for ( i = 1; i <= n; i++){
		if ( exibirGrauVertice( i ) % 2 != 0 ){
			return 0;
		}
	}
	return 1;
}

int exibirGrauVertice( int u ){ // Mostra grau do vértice que é passado por parâmetro
    int i, grau = 0;
    for ( i = 0;i <= n;i++ ){
        if( adj[ u ][ i ] == 1){
        	grau++;
    	}
    }
	return grau;
}

void inserirVertice(){ // Função para inserir vértices no grafo
    int i;
    n++; //Aumenta o numero de vértices do grafo
    printf( "\n*********************************\n" );	
    printf( "Inserido vértice de nº %d \n", n );
    printf( "*********************************\n" );
    for ( i = 1;i <= n;i++ ){
        adj[ i ][ n ] = 0;
        adj[ n ][ i ] = 0;
    }
}

void excluirVertice( char u ){ // Função para excluir vértices do grafo
    int i, j;
    if ( n == 0 ){
        printf( "\n*********************************\n" );
   	    printf( "Grafo vazio\n" );
        printf( "*********************************\n" );
        return ;
    }
    if ( u > n ){
    	
        printf( "Vértice não presente no grafo.\n" );
        return ;
    }
    for ( i = u;i <= n - 1;i++ )
        for ( j = 1;j <= n;j++ ){
                adj[ j ][ i ] = adj[ j ][ i + 1 ]; /* Puxar colunas para a esquerda */
                adj[ i ][ j ] = adj[ i + 1 ][ j ]; /* Puxar linhas pra cima */
        }
    n--;
}

void inserirAresta( char u, char v ){ // Função para inserir arestas no grafo
    if ( u > n ){
    	printf( "\n*********************************\n" );
        printf( "Vértice de origem não existe.\n" );
        printf( "*********************************\n" );
        return ;
    }
    if ( v > n ){
    	printf( "\n*********************************\n" );
   	    printf( "Vértice de destino não existe.\n" );
        printf( "*********************************\n" );
        return ;
    }
    adj[ u ][ v ] = 1;
    adj[ v ][ u ] = 1;
}

void excluirAresta( char u, char v ){ // Função para excluir arestas do grafo
    if ( u > n || v > n || adj[ u ][ v ] == 0 ){
    	printf ("\n*********************************\n" );
   	    printf( "Aresta não existe\n" );
        printf( "*********************************\n" );
        return ;
    }
    adj[ u ][ v ] = 0;
}

int verificarGrafoConexo(int source){ // Função para verificar se o grafo é conexo
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
        printf( "1.Inserir novo vértice\n" );
        printf( "2.Inserir aresta (ex.: 1 1)\n" );
        printf( "3.Excluir vértice\n" );
        printf( "4.Excluir aresta (ex.: 1 1)\n" );
        printf( "5.Exibir contagem de vértices e arestas\n" );
        printf( "6.Exibir grau do vértice\n" );        
        printf( "7.Exibir grafo\n" );        
        printf( "8.Verificar se o grafo possui ciclo euleriano\n" );      
		printf( "9.Sair\n" );    
        printf( "---------------------------------" );	
        printf( "\n" );
        printf( "Digite a opção desejada : " );
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
                printf( "Digite o vértice a ser excluído : " );
                fflush( stdin );
                scanf( "%d", &vertice );
                excluirVertice( vertice );
                break;
            case 4:
                printf( "Digite os vértices da aresta a ser excluída : " );
                fflush( stdin );
                scanf( "%d %d", &origem, &destino );
                excluirAresta( origem, destino );
                break;
            case 5:
            	printf( "\n*********************************\n" );
            	printf( "Número de vértices: %d, número de arestas : %d", n, exibirContagemArestas() );                
                break;
            case 6:
                printf( "Digite o vértice a ser verificado o grau : " );
                fflush( stdin );
                scanf( "%d", &vertice );
                printf( "\n*********************************\n" );
			    printf( "Vértice possui grau %d\n", exibirGrauVertice(vertice));
			    printf( "*********************************\n" );
                break;                
            case 7:
                exibirGrafo();
                break;          	
  		    case 8:
                for(i = 0; i < max; i++){
                    visitados[i] = 0;
                }
                int total = verificarGrafoConexo(1); // Salvar na variável total o retorno da função verifica... e começar pelo vértice 1
                //printf("\ntotal: %d", total);
                //printf("\nn: %d ", n);
                //printf("\nverificar vertices: %d ", verificarVertices( ) );
               	if ( !(total < n) && verificarVertices( ) == 1 && n != 1 ){ // Comparar se o retorno da função verifica... 
				   	//é maior que a quantidade de vértices e se o grau de todos os vértices é par
				   	printf( "\n*********************************\n" );
					printf( "Ciclo euleriano presente no grafo." );                						
					printf( "\n*********************************\n" );
				}
               	else{
               		printf( "\n*********************************\n" );
               		printf( "Não existe ciclo euleriano no grafo." );
               		printf( "\n*********************************\n" );
               	}
                break;
			case 9:
                return ; 				            
            default:
                printf( "Opção inválida.\n" );
                break;
        } 
    }
}
