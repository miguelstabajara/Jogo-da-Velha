#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
void imprime_matriz(char mat[][3]);
void espacos_vazios(char mat[][3]);
void primeira_jogadaaleat(char mat[0][3]);
int jogada_player(char mat[0][3]);
int escolha_estrategia(char mat[][3]);
int finaliza_maquina(char mat[][3]);
int contra_ataque(char mat[][3]);
int estrategia_L(char mat[][3]);
int estrategia_V(char mat[][3]);
int finaliza_jogador(char mat[][3]);
int jogada_aleatoria(char mat[][3]);
int verifica_velha(char mat[][3]);

//Centralizar os textos na tela
void CenterText(const char *text){
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(console, &consoleInfo);
    int textLength = strlen(text);
    int consoleWidth = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
    int posX = (consoleWidth - textLength) / 2;
    int posY = consoleInfo.dwCursorPosition.Y;
    COORD newPos;
    newPos.X = posX;
    newPos.Y = posY;
    SetConsoleCursorPosition(console, newPos);
    printf("%s", text);
}

//Niveis do jogo
int velha_dificil(){ 
    char mat[3][3];
    int estrategia = 0, turno = 0;
    espacos_vazios(mat);
    primeira_jogadaaleat(mat);
    inicio:
    turno = 0;
    turno = verifica_velha(mat);
    if (turno == 4){
        imprime_matriz(mat);
        return 2; // Se o jogou chegou até aqui deu velha e a funçao retorna 2 para a main anunciar a velha
    }

    turno = jogada_player(mat);
    if (turno == 1){
        goto inicio;
    }
    turno = verifica_velha(mat);
    if (turno == 4){
        imprime_matriz(mat);
        return 2; // Se o jogou chegou até aqui deu velha e a funçao retorna 2 para a main anunciar a velha
    }
    turno = finaliza_jogador(mat);
    if (turno == 3){
        imprime_matriz(mat);
        return 1; // Retorna 1 para a main pois o jogador venceu
    }
    if (estrategia == 0){
        estrategia = escolha_estrategia(mat);
    }
    turno = finaliza_maquina(mat);
    if (turno == 2){
        imprime_matriz(mat);
        return 0; // Retorna 0 para a main pois a maquina venceu
    }
    turno = contra_ataque(mat);
    if (turno == 1){
        goto inicio;
    }

    if (estrategia == 1){
        turno = estrategia_L(mat);
    }
    else if (estrategia == 2){
        turno = estrategia_V(mat);
    }
    if (turno == 1){
        goto inicio;
    }
    jogada_aleatoria(mat);
    turno = verifica_velha(mat);
    if (turno == 4){
        imprime_matriz(mat);
        return 2; // Se o jogou chegou até aqui deu velha e a funçao retorna 2 para a main anunciar a velha
    }
    return 0;
}
int velha_medio(){
    char mat[3][3];
    int turno = 0;
    espacos_vazios(mat);
inicio:
    turno = 0;
    turno = verifica_velha(mat);
    if (turno == 4){
        imprime_matriz(mat);
        return 2; // Se o jogou chegou até aqui deu velha e a funçao retorna 2 para a main anunciar a velha
    }
    turno = jogada_player(mat);
    if (turno == 1){
        goto inicio;
    }
    turno = verifica_velha(mat);
    if (turno == 4){
        imprime_matriz(mat);
        return 2; // Se o jogou chegou até aqui deu velha e a funçao retorna 2 para a main anunciar a velha
    }
    turno = verifica_velha(mat);
    if (turno == 4){
        imprime_matriz(mat);
        return 2; // Se o jogou chegou até aqui deu velha e a funçao retorna 2 para a main anunciar a velha
    }
    turno = finaliza_jogador(mat);
    if (turno == 3){
        imprime_matriz(mat);
        return 1; // Retorna 1 para a main pois o jogador venceu
    }
    turno = finaliza_maquina(mat);
    if (turno == 2){
        imprime_matriz(mat);
        return 0; // Retorna 0 para a main pois a maquina venceu
    }
    turno = contra_ataque(mat);
    if (turno == 1){
        goto inicio;
    }
    turno = jogada_aleatoria(mat);
    if (turno == 1){
        goto inicio;
    }
    turno = verifica_velha(mat);
    if (turno == 4){
        imprime_matriz(mat);
        return 2; // Se o jogou chegou até aqui deu velha e a funçao retorna 2 para a main anunciar a velha
    }
    return 0;
}
int velha_facil()
{
    char mat[3][3];
    int turno = 0;
    espacos_vazios(mat);
inicio:
    turno = 0;
    turno = verifica_velha(mat);
    if (turno == 4){
        imprime_matriz(mat);
        return 2; // Se o jogou chegou até aqui deu velha e a funçao retorna 2 para a main anunciar a velha
    }
    turno = jogada_player(mat);
    if (turno == 1){
        goto inicio;
    }
    turno = verifica_velha(mat);
    if (turno == 4){
        imprime_matriz(mat);
        return 2; //Deu velha e a funçao retorna 2 para a main anunciar a velha
    }
    turno = finaliza_jogador(mat);
    if (turno == 3){
        imprime_matriz(mat);
        return 1; // Retorna 1 para a main pois o jogador venceu
    }
    turno = finaliza_maquina(mat);
    if (turno == 2){
        imprime_matriz(mat);
        return 0; // Retorna 0 para a main pois a maquina venceu
    }
    turno = jogada_aleatoria(mat);
    if (turno == 1){
        goto inicio;
    }
    turno = verifica_velha(mat);
    if (turno == 4){
        imprime_matriz(mat);
        return 2; // Se o jogou chegou até aqui deu velha e a funçao retorna 2 para a main anunciar a velha
    }
    return 0;
}

//Tabuleiro
void imprime_matriz(char mat[][3]){
    char buffer[20];
    CenterText("+------------------------------+\n");
    CenterText("\n");
    CenterText("  A   B   C\n");
    sprintf(buffer, "1  %c | %c | %c\n", mat[0][0], mat[0][1], mat[0][2]);
    CenterText(buffer);
    CenterText("  ---+---+---\n");
    sprintf(buffer, "2  %c | %c | %c\n", mat[1][0], mat[1][1], mat[1][2]);
    CenterText(buffer);
    CenterText("  ---+---+---\n");
    sprintf(buffer, "3  %c | %c | %c\n", mat[2][0], mat[2][1], mat[2][2]);
    CenterText(buffer);
    CenterText("\n");
    CenterText("+------------------------------+\n");
}

//Espaços vazios matriz
void espacos_vazios(char mat[][3])
{
    int i, j;
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            mat[i][j] = ' ';
        }
    }
}

//Faz a primeira jogada aleatoria no modo dificil
void primeira_jogadaaleat(char mat[0][3])
{
    int aleat_1;
    srand(time(NULL));
    aleat_1 = (rand() % 3);
    if (aleat_1 == 0){
        mat[0][0] = 'O';
    }
    else if (aleat_1 == 1){
        mat[2][0] = 'O';
    }
    else if (aleat_1 == 2){
        mat[0][2] = 'O';
    }
    else if (aleat_1 == 3){
        mat[2][2] = 'O';
    }
}

//Realiza jogada do jogador
int jogada_player(char mat[0][3])
{
    int y, p;
    char x;
    char buffer[20];
    CenterText("+------------------------------+\n");
    CenterText("\n");
    CenterText("Player [X] | [O] Maquina\n\n");
    CenterText("  A   B   C\n");
    sprintf(buffer, "1  %c | %c | %c\n", mat[0][0], mat[0][1], mat[0][2]);
    CenterText(buffer);
    CenterText("  ---+---+---\n");
    sprintf(buffer, "2  %c | %c | %c\n", mat[1][0], mat[1][1], mat[1][2]);
    CenterText(buffer);
    CenterText("  ---+---+---\n");
    sprintf(buffer, "3  %c | %c | %c\n", mat[2][0], mat[2][1], mat[2][2]);
    CenterText(buffer);
    CenterText("\n");
    CenterText("+------------------------------+\n");

    CenterText("Jogada: ");
    scanf("%d %c", &y, &x);
    CenterText("\n");
    //Passa a coordenada de x(char) e y para coordenada da matriz
    setbuf(stdin, NULL);
    if ((y < 1) && (y > 3)){
        system("cls");
        CenterText("Jogada invalida, insira novamente!\n");
        return 1; // Retorna 1 para variavel turno para o player jogar
    }
    else if ((x == 'A') || (x == 'a')){
        y -= 1;
        p = 0;
        if (mat[y][p] == ' '){
            system("cls");
            mat[y][p] = 'X';
        }
        else{
            CenterText("Jogada invalida, insira novamente!\n");
            return 1; 
        }
    }
    else if ((x == 'b') || (x == 'B')){
        p = 1;
        y -= 1;
        if (mat[y][p] == ' '){
            system("cls");
            mat[y][p] = 'X';
        }
        else{
            CenterText("Jogada invalida, insira novamente!\n");
            return 1; 
        }
    }
    else if ((x == 'c') || (x == 'C')){
        p = 2;
        y -= 1;
        if (mat[y][p] == ' '){
            system("cls");
            mat[y][p] = 'X';
        }
        else{
            CenterText("Jogada invalida, insira novamente!\n");
            return 1; 
        }
    }
    else{
        system("cls");
        CenterText("Jogada invalida, insira novamente!\n");
        return 1; 
    }
    return 0;
}

//estrategias
int escolha_estrategia(char mat[][3])
{
    if (mat[1][1] == 'X'){
        return 1; // Retorna 1 para a variavel estrategia
    }
    else{
        return 2; // Retorna 2 para a variavel estrategia
    }
}
int finaliza_maquina(char mat[][3])
{
    int linha_1, soma, f, coluna_1, j, i;
    //Analise de linha para maquina vencer
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            if (j == 0){
                soma = 0;
            }
            if (mat[i][j] == 'O'){
                soma = soma + 1;
            }
            if (soma == 2){
                linha_1 = i;
                for (f = 0; f < 3; f++){
                    if (mat[linha_1][f] == ' '){
                        mat[linha_1][f] = 'O';
                        return 2; // Retorna 2 para a variavel turno
                    }
                }
            }
        }
    }

    //Analise de coluna para maquina vencer
    for (j = 0; j < 3; j++){
        for (i = 0; i < 3; i++){
            if (i == 0){
                soma = 0;
            }
            if (mat[i][j] == 'O'){
                soma = soma + 1;
            }
            if (soma == 2){
                coluna_1 = j;
                for (f = 0; f < 3; f++){
                    if ((mat[f][coluna_1] == ' ')){
                        mat[f][coluna_1] = 'O';
                        return 2; // Retorna 2 para a variavel turno
                    }
                }
            }
        }
    }

    //Analise da coluna principal para a maquina vencer
    j = 0;
    soma = 0;
    for (i = 0; i < 3; i++){
        if (mat[i][j] == 'O'){
            soma = soma + 1;
        }
        if (soma == 2){
            if ((mat[0][0] == 'O') && (mat[1][1] == 'O') && (mat[2][2] == ' ')){
                mat[2][2] = 'O';
                return 2; // Retorna 2 para a variavel turno
            }
            else if ((mat[0][0] == 'O') && (mat[2][2] == 'O') && (mat[1][1] == ' ')){
                mat[1][1] = 'O';
                return 2; // Retorna 2 para a variavel turno
            }
            else if ((mat[1][1] == 'O') && (mat[2][2] == 'O') && (mat[0][0] == ' ')){
                mat[0][0] = 'O';
                return 2; // Retorna 2 para a variavel turno
            }
        }
        j++;
    }

    //Analise da diagonal secundaria para a maquina vencer
    j = 2;
    soma = 0;
    for (i = 0; i < 3; i++){
        if (mat[i][j] == 'O'){
            soma = soma + 1;
        }
        if (soma == 2){
            if ((mat[0][2] == 'O') && (mat[1][1] == 'O') && (mat[2][0] == ' ')){
                mat[2][0] = 'O';
                return 2; // Retorna 2 para a variavel turno
            }
            else if ((mat[0][2] == 'O') && (mat[2][0] == 'O') && (mat[1][1] == ' ')){
                mat[1][1] = 'O';
                return 2; // Retorna 2 para a variavel turno
            }
            else if ((mat[1][1] == 'O') && (mat[2][0] == 'O') && (mat[0][2] == ' ')){
                mat[0][2] = 'O';
                return 2; // Retorna 2 para a variavel turno
            }
        }
        j--;
    }
    return 0;
}
int contra_ataque(char mat[][3])
{
    int linha, coluna, i, j, f, soma;
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            if (j == 0){
                soma = 0;
            }
            if (mat[i][j] == 'X'){
                soma = soma + 1;
            }
            if (soma == 2){
                linha = i;
                for (f = 0; f < 3; f++){
                    if (mat[linha][f] == ' '){
                        mat[linha][f] = 'O';
                        return 1; // Retorna 1 para variavel turno para o player jogar
                    }
                }
            }
        }
    }

    //Analise de coluna para contra ataque
    for (j = 0; j < 3; j++){
        for (i = 0; i < 3; i++){
            if (i == 0){
                soma = 0;
            }
            if (mat[i][j] == 'X'){
                soma = soma + 1;
            }
            if (soma == 2){
                coluna = j;
                for (f = 0; f < 3; f++)
                {
                    if ((mat[f][coluna] == ' '))
                    {
                        mat[f][coluna] = 'O';
                        return 1; // Retorna 1 para variavel turno para o player jogar
                    }
                }
            }
        }
    }

    //Analise da diagonal principal para contra ataque
    j = 0;
    soma = 0;
    for (i = 0; i < 3; i++){
        if (mat[i][j] == 'X'){
            soma = soma + 1;
        }
        if (soma == 2){
            if ((mat[0][0] == 'X') && (mat[1][1] == 'X') && (mat[2][2] == ' ')){
                mat[2][2] = 'O';
                return 1; // Retorna 1 para variavel turno para o player jogar
            }
            else if ((mat[0][0] == 'X') && (mat[2][2] == 'X') && ((mat[1][1] == ' '))){
                mat[1][1] = 'O';
                return 1; 
            }
            else if ((mat[1][1] == 'X') && (mat[2][2] == 'X') && (mat[0][0] == ' ')){
                mat[0][0] = 'O';
                return 1; 
            }
        }
        j++;
    }

    //Analise da diagonal secundaria para contra ataque
    j = 2;
    soma = 0;
    for (i = 0; i < 3; i++){
        if (mat[i][j] == 'X'){
            soma = soma + 1;
        }
        if (soma == 2){
            if ((mat[0][2] == 'X') && (mat[1][1] == 'X') && (mat[2][0] == ' ')){
                mat[2][0] = 'O';
                return 1; // Retorna 1 para variavel turno para o player jogar
            }
            else if ((mat[0][2] == 'X') && (mat[2][0] == 'X') && ((mat[1][1] == ' '))){
                mat[1][1] = 'O';
                return 1; // Retorna 1 para variavel turno para o player jogar
            }
            else if ((mat[1][1] == 'X') && (mat[2][0] == 'X') && (mat[0][2] == ' ')){
                mat[0][2] = 'O';
                return 1; // Retorna 1 para variavel turno para o player jogar
            }
        }
        j--;
    }
    return 0;
}
int estrategia_L(char mat[][3])
{
    if ((mat[0][0] != 'X') && (mat[2][0] == 'O') && (mat[0][2] != 'X')){
        if (mat[0][2] == ' '){
            mat[0][2] = 'O';
            return 1; // Retorna 1 para variavel turno para o player jogar
        }
        if (mat[0][0] == ' '){
            mat[0][0] = 'O';
            return 1; 
        }
    }

    if ((mat[0][0] != 'X') && (mat[2][0] != 'X') && (mat[2][2] == 'O')){
        if (mat[0][0] == ' '){
            mat[0][0] = 'O';
            return 1; 
        }
        if (mat[2][0] == ' '){
            mat[2][0] = 'O';
            return 1; 
        }
    }
    if ((mat[0][0] == 'O') && (mat[0][2] != 'X') && (mat[2][2] != 'X')){
        if (mat[2][2] == ' '){
            mat[2][2] = 'O';
            return 1; 
        }
        if (mat[0][2] == ' '){
            mat[0][2] = 'O';
            return 1; 
        }
    }
    if ((mat[2][2] != 'X') && (mat[2][0] != 'X') && (mat[0][2] == 'O')){
        if (mat[2][0] == ' '){
            mat[2][0] = 'O';
            return 1; 
        }
        if (mat[2][2] == ' '){
            mat[2][2] = 'O';
            return 1; 
        }
    }
    return 0;
}
int estrategia_V(char mat[][3])
{
    if ((mat[0][0] != 'X') && (mat[1][1] != 'X') && (mat[0][2] != 'X')){
        if (mat[0][0] == ' '){
            mat[0][0] = 'O';
            return 1; 
        }
        if ((mat[1][1] == ' ')){
            mat[1][1] = 'O';
            return 1; 
        }
        if (mat[0][2] == ' '){
            mat[0][2] = 'O';
            return 1;
        }
    }
    if ((mat[2][0] != 'X') && (mat[1][1] != 'X') && (mat[2][2] != 'X')){
        if (mat[2][0] == ' ')
        {
            mat[2][0] = 'O';
            return 1; 
        }
        if ((mat[1][1] == ' ')){
            mat[1][1] = 'O';
            return 1; 
        }
        if (mat[2][2] == ' '){
            mat[2][2] = 'O';
            return 1; 
        }
    }

    if ((mat[2][0] != 'X') && (mat[1][1] != 'X') && (mat[0][0] != 'X')){
        if (mat[0][0] == ' '){
            mat[0][0] = 'O';
            return 1; 
        }
        if ((mat[1][1] == ' ')){
            mat[1][1] = 'O';
            return 1; 
        }
        if (mat[2][0] == ' '){
            mat[2][0] = 'O';
            return 1; 
        }
    }
    if ((mat[2][2] != 'X') && (mat[1][1] != 'X') && (mat[0][2] != 'X')){
        if (mat[2][2] == ' '){
            mat[2][2] = 'O';
            return 1; 
        }
        if ((mat[1][1] == ' ')){
            mat[1][1] = 'O';
            return 1; 
        }
        if (mat[0][2] == ' '){
            mat[0][2] = 'O';
            return 1; 
        }
    }
    return 0;
}
int finaliza_jogador(char mat[][3])
{
    int i, j, soma;
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            if (j == 0){
                soma = 0;
            }
            if (mat[i][j] == 'X'){
                soma = soma + 1;
            }
            if (soma == 3){
                return 3; // Retorna 3 para a variavel turno pois o jogador venceu
            }
        }
    }
    
    //Analise de coluna para maquina vencer
    for (j = 0; j < 3; j++){
        for (i = 0; i < 3; i++){
            if (i == 0){
                soma = 0;
            }
            if (mat[i][j] == 'X'){
                soma = soma + 1;
            }
            if (soma == 3){
                return 3; // Retorna 3 para a variavel turno pois o jogador venceu
            }
        }
    }

    //Analise da coluna principal para a maquina vencer
    if ((mat[0][0] == 'X') && (mat[1][1] == 'X') && (mat[2][2]) == 'X')
    {
        return 3; // Retorna 3 para a variavel turno pois o jogador venceu
    }
    /*Analise da diagonal secundaria para a maquina vencer*/
    if ((mat[0][2] == 'X') && (mat[1][1] == 'X') && (mat[2][0]) == 'X')
    {
        return 3; // Retorna 3 para a variavel turno pois o jogador venceu
    }
    return 0;
}
int jogada_aleatoria(char mat[][3])
{

    int x, i, j;
    x = 0;
    srand(time(NULL));
    x = rand() % 8;
    if ((x == 1) && (mat[0][0] == ' ')){
        mat[0][0] = 'O';
        return 1;
    }
    else if ((x == 2) && (mat[0][1] == ' ')){
        mat[0][1] = 'O';
        return 1;
    }
    else if ((x == 3) && (mat[0][2] == ' ')){
        mat[0][2] = 'O';
        return 1;
    }
    else if ((x == 4) && (mat[1][0] == ' ')){
        mat[1][0] = 'O';
        return 1;
    }
    else if ((x == 5) && (mat[1][1] == ' ')){
        mat[1][1] = 'O';
        return 1;
    }
    else if ((x == 6) && (mat[1][2] == ' ')){
        mat[1][2] = 'O';
        return 1;
    }
    else if ((x == 7) && (mat[2][0] == ' ')){
        mat[2][0] = 'O';
        return 1;
    }
    else if ((x == 8) && (mat[2][1] == ' ')){
        mat[2][1] = 'O';
        return 1;
    }
    else if ((x == 9) && (mat[2][2] == ' ')){
        mat[2][2] = 'O';
        return 1;
    }
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++)
        {
            if (mat[i][j] == ' ')
            {
                mat[i][j] = 'O';
                return 1;
            }
        }
    }
    return 0;
}
int verifica_velha(char mat[][3])
{
    int i, j, soma = 0;
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            if (mat[i][j] != ' '){
                soma = soma + 1;
            }
            else if (mat[i][j] == ' '){
                return 0;
            }
        }
    }
    if (soma == 9){
        return 4;
    }
    return 0;
}

//Menus
struct jogadores{
    char nomep[50];
    int vit;
    int der;
};
char* addNovoNome(){
    struct jogadores dados[100]; 
    char *n, nome[50], linha[100];
    int vitoria=0, derrotas=0,i,cont=0;
    FILE *ranking;
    inicio:
    setbuf(stdin,NULL);
    CenterText("Digite o nome do jogador: ");
    gets(nome);
    n = nome;
    ranking = fopen("ranking.txt", "a+");

    if (ranking == NULL) {
        printf("##ERRO##");
        return n;
    }
    //Separa os nomes do arquivo para verificar repetição
     while (fgets(linha, sizeof(linha), ranking) != NULL) {
        char *p = strtok(linha, ",");
        strcpy(dados[cont].nomep, p);
        cont++;
    }
    for(i=0;i<cont;i++){
        if(strcmp(dados[i].nomep,nome)==0){
            CenterText("Nome ja existente, tente novamente\n");
            goto inicio;
        }
    }

    fprintf(ranking, "%s,%d,%d\n", nome,vitoria,derrotas);
    fclose(ranking);

    CenterText("Jogador adicionado\n");
    system("cls");
    return(n);
}

struct jogadores1{
    char nomep[50];
    int vit;
    int der;
};
char* addNomeExistente(){
    struct jogadores dados[100]; 
    char linha[100];
    char nome[50];
    char *n = malloc(sizeof(char) * 20);
    int i,cont=0;
    FILE *ranking;
    n = nome;
    do{
    setbuf(stdin,NULL);
    CenterText("Nome do jogador: ");
    gets(nome);

    ranking = fopen("ranking.txt", "a+");

    if (ranking == NULL) {
        printf("##ERRO##");
        return 0;
    }
    //Separa os nomes do arquivo para verificar repetição
    while (fgets(linha, sizeof(linha), ranking) != NULL) {
        char *p = strtok(linha, ",");
        strcpy(dados[cont].nomep, p);
        cont++;
    }
    for(i=0;i<cont;i++){
        if(strcmp(dados[i].nomep,nome)==0){
            CenterText("Jogador identificado!\n");
             fclose(ranking);
             system("cls");
             return(n);
        }
    }
    fclose(ranking);
    CenterText("Jogador nao encontrado, digite novamente.\n");
    }while(1);
    
}

struct jogadores2{
    char nomep[50];
    int vit;
    int der;
};
void addVitoria(char nome1[][50]){
    struct jogadores2 dados[100]; 
    char linha[100];
    int i,cont=0;
    FILE *ranking;


    ranking = fopen("ranking.txt", "r+");

    if (ranking == NULL) {
        printf("##ERRO##");
        return;
    }
    
    //Lê as linhas do arquivo
    while (fgets(linha, sizeof(linha), ranking) != NULL) {
        //Separa as linhas do arquivo em strings para vitoria, derrota e nome. E troca o tipo de char para int em derrota e vitoria
        char *p = strtok(linha, ",");
        strcpy(dados[cont].nomep, p);
        p = strtok(NULL, ",");
        dados[cont].vit = atoi(p);
        p = strtok(NULL, ",");
        dados[cont].der = atoi(p);
        //Procura o nome da pessoa para adicionar o ponto
        if(strcmp(dados[cont].nomep,nome1)==0){
            dados[cont].vit = (dados[cont].vit)+1;
        }
        cont++;
    }
    fclose(ranking);
    
    //Reescreve o arquivo com as novas informações
    ranking = fopen("ranking.txt", "w+");
    if (ranking == NULL) {
        printf("##ERRO##");
        return;
    }
    for(i=0;i<cont;i++){
        fprintf(ranking, "%s,%d,%d\n", dados[i].nomep,dados[i].vit,dados[i].der);
    }
    fclose(ranking);
}

struct jogadores3{
    char nomep[50];
    int vit;
    int der;
};
void addDerrota(char nome1[][50]){
    struct jogadores3 dados[100]; 
    char linha[100];
    int i,cont=0;
    FILE *ranking;

    ranking = fopen("ranking.txt", "r+");

    if (ranking == NULL) {
        printf("##ERRO##");
        return;
    }
    
    //Lê as linhas do arquivo
    while (fgets(linha, sizeof(linha), ranking) != NULL) {
        //Separa as linhas do arquivo em strings para vitoria, derrota e nome. E troca o tipo de char para int em derrota e vitoria
        char *p = strtok(linha, ",");
        strcpy(dados[cont].nomep, p);
        p = strtok(NULL, ",");
        dados[cont].vit = atoi(p);
        p = strtok(NULL, ",");
        dados[cont].der = atoi(p);
        //Procura o nome da pessoa para adicionar o ponto
        if(strcmp(dados[cont].nomep,nome1)==0){
            dados[cont].der = (dados[cont].der)+1;
        }
        cont++;
    }
    fclose(ranking);
    
    //Reescreve o arquivo com as novas informações
    ranking = fopen("ranking.txt", "w+");
    if (ranking == NULL) {
        printf("##ERRO##");
        return;
    }
    for(i=0;i<cont;i++){
        fprintf(ranking, "%s,%d,%d\n", dados[i].nomep,dados[i].vit,dados[i].der);
    }
    fclose(ranking);

}

void titulo()
{ 
    CenterText("\n");
    CenterText("\n");
    CenterText("\n");
    CenterText("      +-------+  +------+  +------+  +------+ \n");
    CenterText("     |__. .__|  |      |  |  .__.|  |      |\n");
    CenterText("        | |     | +--+ |  | |       | +--+ |\n");
    CenterText("        | |     | |  | |  | |  +-+  | |  | |\n");
    CenterText("     +--+ |     | +--+ |  | |  | |  | +--+ |\n");
    CenterText("     |    |     |      |  | +--+ |  |      |\n");
    CenterText("     +----+     +------+  +------+  +------+\n");
    CenterText("----> DA <----\n");
    CenterText("     +--+  +--+   +------+  +---+  +--+   +--+      +   \n");
    CenterText("      |  |  |  |   |  ____|  |   |  |  |   |  |     / \\   \n");
    CenterText("      +  +  +  +   | |__.    |   |  |  +---+  |    /   \\  \n");
    CenterText("        \\  +  /     |  __|    |   |  |         |   /  +  \\  \n");
    CenterText("        \\   /      | |____.  |   |  |  +---+  |  +  + +  +\n");
    CenterText("         \\ /       |      |  |   |  |  |   |  |  |  | |  |\n");
    CenterText("          +        +------+  +---+  +--+   +--+  +--+ +--+\n");
    CenterText("\n");
    CenterText("\n");
}
int Nivel()
{
    int modo, vencedor;
    do
    {
        CenterText("+------------------------------+\n");
        CenterText("|          Escolha nivel       |\n");
        CenterText("|                              |\n");
        CenterText("| [1] Facil                    |\n");
        CenterText("| [2] Medio                    |\n");
        CenterText("| [3] Dificil                  |\n");
        CenterText("| [4] Sair                     |\n");
        CenterText("|                              |\n");
        CenterText("+------------------------------+\n");
        CenterText("Opcao: ");
        scanf("%d", &modo);

        switch (modo)
        {
        case 1:
            system("cls");
            vencedor = velha_facil(); // Inicializa o jogo facil
            return vencedor;
        case 2:
            system("cls");
            vencedor = velha_medio(); // Inicializa o jogo no medio
            return vencedor;
        case 3:
            system("cls");
            vencedor = velha_dificil(); // Inicializa o jogo dificil
            return vencedor;
        case 4:
            // sair();
            vencedor = printf("sair.\n");
            return vencedor;
        default:
            printf("opcao invalida.\n");
            break;
        }
    } while (modo < 0 || modo > 5);
    return 0;
}

struct jogadores4{
    char nomep[50];
    int vit;
    int der;
};
void ranking(){
    struct jogadores4 dados[100];
    char linha[100],temp[100];
    int i,cont=0,var1,var2,j;
    FILE *ranking;

    ranking = fopen("ranking.txt", "r+");
    if (ranking == NULL) {
        printf("##ERRO##");
        return;
    }
    
    //Lê as linhas do arquivo
    while(fgets(linha, sizeof(linha), ranking) != NULL) {
        //Separa as linhas do arquivo em strings para vitoria, derrota e nome. E troca o tipo de char para int em derrota e vitoria
        char *p = strtok(linha, ",");
        strcpy(dados[cont].nomep, p);
        p = strtok(NULL, ",");
        dados[cont].vit = atoi(p);
        p = strtok(NULL, ",");
        dados[cont].der = atoi(p);
        cont++;
    }
    //Ordena as estruturas da maior vitoria para a menor vitoria
    fclose(ranking);
    for (i=0;i<cont;i++){
        for (j=i;j<cont;j++){
            if (dados[i].vit < dados[j].vit){
                strcpy(temp,dados[i].nomep);
                var1 = dados[i].vit;
                var2 = dados[i].der;
                strcpy(dados[i].nomep,dados[j].nomep);
                dados[i].vit = dados[j].vit;
                dados[i].der = dados[j].der;
                strcpy(dados[j].nomep, temp);
                dados[j].vit = var1;
                dados[j].der = var2;
            }
        }
    }
    //Imprime o ranking
    printf("---------------------RANKING----------------------\n");
    printf("POSICAO     JOGADOR     VITORIA     DERROTA\n");
    for(i=0;i<cont;i++){
        printf("--------------------------------------------------\n"); 
        printf("[%d]",i+1);
        printf("%15s",dados[i].nomep);
        printf("%10d",dados[i].vit);
        printf("%12d\n",dados[i].der);
    }
    printf("--------------------------------------------------\n"); 
    sleep(5);
}

void sobre()
{
    
    CenterText("+------------------------------+\n");
    CenterText("|             SOBRE            |\n");
    CenterText("|                              |\n");
    CenterText("| Versao: 1.0                  |\n");
    CenterText("| Autores:  Amanda, Anna,      |\n");
    CenterText("|           Miguel e Sara      |\n");
    CenterText("|                              |\n");
    CenterText("+------------------------------+\n");
    sleep(5);
}

//Main
int main()
{
    int opcao, vencedor,opcaonome,k,restart;
    char nome1[50];
    do{
         k = 0;
        do{
            titulo();
            do{
                vencedor=3;
                CenterText("+------------------------------+\n");
                CenterText("|          BEM-VINDO(a)        |\n");
                CenterText("|                              |\n");
                CenterText("| [1] Iniciar jogo             |\n");
                CenterText("| [2] Ranking                  |\n");
                CenterText("| [3] Sobre                    |\n");
                CenterText("| [4] Sair                     |\n");
                CenterText("|                              |\n");
                CenterText("+------------------------------+\n");
                CenterText("Opcao: ");
                scanf("%d", &opcao);

                switch (opcao){
                case 1:
                    system("cls");
                    invalida:
                    CenterText("+------------------------------+\n");
                    CenterText("|      Registro de jogador     |\n");
                    CenterText("|                              |\n");
                    CenterText("| [1] Entrar nome existente    |\n");
                    CenterText("| [2] Adicionar novo nome      |\n");
                    CenterText("|                              |\n");
                    CenterText("+------------------------------+\n");
                    CenterText("Opcao: ");
                    scanf("%d",&opcaonome);
                    if(opcaonome==1){
                        strcpy(nome1,addNomeExistente());
                    }
                    else if(opcaonome==2){
                        strcpy(nome1,addNovoNome());
                    }
                    else{
                        CenterText("Jogador nao encontrado, digite novamente");
                        goto invalida;
                    }
                    restart:
                    vencedor = Nivel();
                    break;
                case 2:
                    system("cls");
                    ranking();
                    break;
                case 3:
                    system("cls");
                    sobre();
                    break;
                case 4:
                    // sair();
                    exit(0);
                    break;
                default:
                    CenterText("opcao invalida.\n");
                    break;
                }
            } while (opcao < 0 || opcao > 5);

            if (vencedor == 0){
                CenterText("A maquina venceu\n\n");
                addDerrota(nome1);
                sleep(2);
                CenterText("Escolha opcao:\n");
                CenterText("[1] Jogar novamente\n");
                CenterText("[2] Voltar para o menu\n");
                CenterText("Opcao: ");
                scanf("%d",&restart);
                if(restart==1){
                    system("cls");
                    goto restart;
                }
                k=1;
            }
            else if(vencedor==1){
                CenterText("Voce venceu\n\n");
                addVitoria(nome1);
                sleep(2);
                CenterText("Escolha opcao:\n");
                CenterText("[1] Jogar novamente\n");
                CenterText("[2] Voltar para o menu\n");
                CenterText("Opcao: ");
                scanf("%d",&restart);
                if(restart==1){
                    system("cls");
                    goto restart;
                }
                k=1;
            }
            else if(vencedor==2){
                CenterText("Deu velha\n\n");
                sleep(2);
                k=1;
            }
            
        }while(k==0);
    }while(1);
    return 0;
}