#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define LIMITE_1 10
#define LIMITE_2 11
#define LIMITE_3 100

struct voo{
    char codigo_voo[LIMITE_1];
    int capacidade_voo;
    int dia, ano, mes;
    int hora, minuto;
    int status_voo;
};

struct reserva{
    char numero_reserva[LIMITE_2];
    struct voo linha_karman;
    char cpf_passageiro[12];
    char nome_passageiro[LIMITE_3];
    char sexo;
    int dia_nascimento, mes_nascimento, ano_nascimento;
};

void mensagem_menu();
void cadastrar_voo();
void cadastrar_reserva();
void consultar_voo();
void consultar_reserva();
void consultar_passageiro();
void cancelar_voo(void);
void cancelar_reserva(void);
void excluir_voo(void);
void sair();
void limpar_tela();
void gravar_arquivo_voo(struct voo viagem);

struct voo funcao_cadastrar_voo();
struct reserva funcao_cadastrar_reserva();
int funcao_validar_cpf(struct reserva cadeira);
int funcao_validar_data(struct voo viagem);
int funcao_validar_data_2(struct reserva cadeira);
int funcao_validar_codigo(struct voo viagem);
int funcao_validar_numero(struct reserva cadeira);
int funcao_validar_sexo(struct reserva cadeira);
int funcao_validar_nome(struct reserva cadeira);

int main(){

    int escolha;

    mensagem_menu();
    fflush(stdin);
    scanf("%d", &escolha);

    switch(escolha){
        case 1:
            cadastrar_voo();
            break;
        case 2:
            cadastrar_reserva();
            break;
        case 3:
            consultar_voo();
            break;
        case 4:
            consultar_reserva();
            break;
        case 5:
            consultar_passageiro();
        case 6:
            cancelar_voo();
            break;
        case 7:
            cancelar_reserva();
            break;
        case 8:
            excluir_voo();
            break;
        case 9:
            sair();
            break;
    }
    return 0;
}

struct voo funcao_cadastrar_voo(){

    struct voo viagem;
    FILE *arquivo_do_voo;
    FILE *arquivo_do_voo_bin;
    struct tm *data_hora_atual;
    time_t segundos;

    time(&segundos);
    data_hora_atual = localtime(&segundos);
    arquivo_do_voo = fopen("arquivo_1.txt", "at");
    arquivo_do_voo_bin = fopen("arquivo_1b.dat", "ab");
    printf("\n Preencha os requisitos abaixo:\n");

    printf(" 1- Insira o codigo do voo. (Exemplo: JEB-1234): ");
    fflush(stdin);
    fgets(viagem.codigo_voo,  LIMITE_1, stdin);

    if(funcao_validar_codigo(viagem) == 0){
        while(funcao_validar_codigo(viagem) != 1){
            printf("\n     Codigo de voo deve ser no formato JEB-XXXX. Preencha novamente.\n\n");
            printf(" 1- Insira o codigo do voo novamente: ");
            fflush(stdin);
            fgets(viagem.codigo_voo, LIMITE_1, stdin);
        }
    }
    /*
    digitado = viagem.codigo_voo;
    //Procurar o codigo digitado no arquivo da reserva
    while( !feof(arquivo_do_voo) ){
        fflush(stdin);
        fgets(auxiliar, 100, arquivo_do_voo);//A variavel auxiliar ir� receber do arquivo_do_voo
        strcmp(auxiliar, digitado);
        //printf("%s", auxiliar_2);
        if( strcmp(auxiliar, digitado) == 0){
            variavel = 1;
            //printf("%s", auxiliar_2);
            break;
        }else{
            variavel = 0;
        }
    }
    */


    if(funcao_validar_codigo(viagem) == 1){

        fprintf(arquivo_do_voo, "%s\n", viagem.codigo_voo);
    }

    printf(" 2- Insira a capacidade do voo. (Limite: 12 passageiros): ");
    fflush(stdin);
    scanf("%d", &viagem.capacidade_voo);

    if(viagem.capacidade_voo > 12 || viagem.capacidade_voo <= 0){
        while(viagem.capacidade_voo > 12 || viagem.capacidade_voo <= 0){
            if(viagem.capacidade_voo > 12){
                printf("\n    Limite de 12 passageiros. Preencha novamente.\n\n");
                //Novo cadastramento da capacidade m�xima de passageiros
                printf(" 2- Insira a capacidade do voo novamente: ");
                fflush(stdin);
                scanf("%d", &viagem.capacidade_voo);
            }else{
                if(viagem.capacidade_voo <= 0){
                    printf("\n    Minimo de 1 passageiro. Preencha novamente.\n\n");
                    //Novo cadastramento da capacidade m�xima de passageiros
                    printf(" 2- Insira a capacidade do voo novamente: ");
                    fflush(stdin);
                    scanf("%d", &viagem.capacidade_voo);
                }
            }
        }
    }
    if( (viagem.capacidade_voo <= 12) && (viagem.capacidade_voo > 0) ){
        //Escrever a capacidade do voo no arquivo_1
        fprintf (arquivo_do_voo, "%d\n", viagem.capacidade_voo);
    }
    //Voo: Dia do voo:
    printf(" 3- Insira o dia do voo: ");
    fflush(stdin);
    scanf("%d", &viagem.dia);//Leitura do dia
    //Primeira verifica��o do dia digitado
    if(viagem.dia > 31 || viagem.dia <= 0){
        while(viagem.dia > 31 || viagem.dia <= 0){
            printf("\n    Dia informado incorreto.\n\n");
            //Novo cadastramento do dia do voo
            printf(" 3- Insira o dia do voo novamente: ");
            fflush(stdin);
            scanf("%d", &viagem.dia);//Leitura do dia novamente
        }
    }
    if(viagem.dia <= 31 && viagem.dia > 0){
        //Escrever o dia do voo no arquivo_1
        fprintf (arquivo_do_voo, "%d\n", viagem.dia);
    }
    //Voo: M�s do voo:
    printf(" 4- Insira o mes do voo: ");
    fflush(stdin);
    scanf("%d", &viagem.mes);//Leitura do m�s
    //Primeira verifica��o do mes digitado
    if(viagem.mes > 12 || viagem.mes <= 0){
        while(viagem.mes > 12 || viagem.mes <= 0){
            printf("\n    M�s informado incorreto.\n\n");
            //Novo cadastramento do m�s do voo
            printf(" 4- Insira o m�s do voo novamente: ");
            fflush(stdin);
            scanf("%d", &viagem.mes);//Leitura do m�s novamente
        }
    }
    if(viagem.mes <= 12 && viagem.mes > 0){
        //Escrever o m�s do voo no arquivo_1
        fprintf(arquivo_do_voo, "%d\n" , viagem.mes);
    }

    printf(" 5- Insira o ano do voo: ");
    fflush(stdin);
    scanf("%d", &viagem.ano);

    if(viagem.ano < (data_hora_atual -> tm_year + 1900) || viagem.ano > 2121 ){
        while(viagem.ano < (data_hora_atual -> tm_year + 1900) || viagem.ano > 2121 ){
            printf("\n    Ano informado incorreto.\n\n");
            //Novo cadastramento do ano do voo.
            printf(" 4- Insira o ano do voo novamente: ");
            fflush(stdin);
            scanf("%d", &viagem.ano);//Leitura do ano novamente
        }
    }
    if( (viagem.ano >= (data_hora_atual -> tm_year + 1900) ) && (viagem.ano <= 2121 ) ){
        //Escrever o ano do voo no arquivo_1
        fprintf(arquivo_do_voo, "%d\n" , viagem.ano);
    }
    if(funcao_validar_data(viagem) == 0){
        printf("\n    Data inexiste no calendario gregoriano. \n\n");
    }

    printf(" 6- Insira a hora de embarque do voo: ");
    fflush(stdin);
    scanf("%d", &viagem.hora);

    if(viagem.hora > 23 || viagem.hora <= 0){
        while(viagem.hora > 23 || viagem.hora <= 0){
            printf("\n    Hora informada incorreta.\n\n");
            //Se a hora estiver errada, novo cadastramento da hora do voo
            printf(" 4- Insira a hora de embarque do voo novamente: ");
            fflush(stdin);
            scanf("%d", &viagem.hora);//Leitura da hora novamente
        }
    }
    if( (viagem.hora <= 23) && (viagem.hora > 0) ){

        fprintf(arquivo_do_voo, "%d\n" , viagem.hora);
    }

    printf(" 7- Insira os minutos do hor�rio de embarque do voo: ");
    fflush(stdin);
    scanf("%d", &viagem.minuto);//Leitura dos minutos
    //Primeira verifica��o do minuto digitado
    if(viagem.minuto > 59 || viagem.minuto <= 0){
        while(viagem.minuto > 59 || viagem.minuto <= 0){
            printf("\n    Minuto informado incorreto.\n\n");
            //Novo cadastramento da minuto do voo
            printf(" 4- Insira os minutos do hor�rio de embarque do voo novamente: ");
            fflush(stdin);
            scanf("%d", &viagem.minuto);//Leitura do minuto novamente
        }
    }
    if( (viagem.minuto <= 59) && (viagem.minuto > 0) ){
        //Escrever os minutos do voo no arquivo_1
        fprintf(arquivo_do_voo, "%d\n" , viagem.minuto);
    }

    printf(" 8- Insira status do voo. (1 para ativo; 0 para cancelado): ");
    fflush(stdin);
    scanf("%d", &viagem.status_voo);//Leitura do status
    //Escrever o status do voo no arquivo_1
    //Interpretar o status do voo
    if(viagem.status_voo == 1){
        fprintf(arquivo_do_voo, "%d\n" , viagem.status_voo);
    }else{
        if(viagem.status_voo == 0){
            fprintf(arquivo_do_voo, "%d\n", viagem.status_voo);
        }
    }
    fseek(arquivo_do_voo_bin, 0, SEEK_SET);
    fwrite(&viagem, sizeof(struct voo), 1, arquivo_do_voo_bin);

    fclose(arquivo_do_voo);
    fclose(arquivo_do_voo_bin);
    return viagem;
}

struct reserva funcao_cadastrar_reserva(){

    struct reserva cadeira;
    struct voo viagem;
    FILE *arquivo_da_reserva;
    FILE *arquivo_da_reserva_bin;
    FILE *arquivo_do_voo;
    FILE *arquivo_do_voo_bin;
    int variavel;
    char *digitado;
    int bandeira;
    char auxiliar[100];

    //Abrir o arquivo da reserva
    arquivo_da_reserva = fopen ("arquivo_2.txt", "at");
    //Abrir o arquivo da reserva binario
    arquivo_da_reserva_bin = fopen("arquivo_2b.dat", "ab");
    printf(" Preencha os requisitos abaixo:\n");//Uma reserva tem os seguintes requisitos para serem preenchidos:
    //Reserva: N�mero da reserva:
    printf(" 1- Insira o n�mero da reserva. (Exemplo: GB-123456): ");//Mensagem para o cadastro do membro codigo_voo[] da struct voo.
    fflush(stdin);
    fgets(cadeira.numero_reserva, LIMITE_2, stdin);//Leitura do n�mero da reserva.
    if(funcao_validar_numero(cadeira) == 0){
        while(funcao_validar_numero(cadeira) != 1){
            printf("\n    Numero da reserva deve ser no formato GB-XXXXXX. Preencha novamente.\n\n");
            printf(" 1- Insira o numero da reserva novamente: ");
            fflush(stdin);
            fgets(cadeira.numero_reserva, LIMITE_2, stdin);
        }
    }
    if(funcao_validar_numero(cadeira) == 1){
        //Escrever o codigo do voo no arquivo do voo arquivo_2
        fprintf(arquivo_da_reserva, "%s\n", cadeira.numero_reserva);
    }
    /*
    //Forma 1 de fazer:
    //Reserva: Codigo do voo:
    arquivo_do_voo_bin = fopen("arquivo_1b.dat", "rb");//Abrir arquivo binario para leitura
    if(arquivo_do_voo_bin){
        printf(" 2- Insira o c�digo do voo.");
        fflush(stdin);
        fgets(cadeira.linha_karman.codigo_voo, LIMITE_1, stdin);//Ler o codigo do voo
        if(funcao_validar_codigo(cadeira.linha_karman) == 0){//Se o codigo for invalido
            while(funcao_validar_codigo(cadeira.linha_karman) != 1){
                printf("\n     Codigo de voo deve ser no formato JEB-XXXX. Preencha novamente.\n\n");
                printf(" 2- Insira o codigo do voo novamente: ");
                fflush(stdin);
                fgets(cadeira.linha_karman.codigo_voo, LIMITE_1, stdin);//Repetir a leitura
            }
        }
    }
    //Se o codigo for valido
    if(funcao_validar_codigo(cadeira.linha_karman) == 1){
        if(arquivo_do_voo_bin){
            fseek(arquivo_do_voo_bin, 0 , SEEK_SET);//Posicionar no inicio do arquivo do voo
            while( !feof(arquivo_do_voo_bin) ){//Enquanto n�o chegar no fim do arquivo arquivo_do_voo.
                fread(&viagem, sizeof(struct voo), 1, arquivo_do_voo_bin);
                if(strstr(registrado, viagem.codigo_voo) != NULL ){//Comparar o codigo digitado com o codigo do arquivo_1
                    bandeira = 1;
                    break;
                }
                if (strstr(registrado, viagem.codigo_voo) == NULL){
                    bandeira = 0;
                }
            }
            if (bandeira == 1){
                printf("\n    C�digo registrado no banco de dados.\n\n");
                fprintf(arquivo_da_reserva, "%s\n", cadeira.linha_karman.codigo_voo);
            }
            if (bandeira == 0){
                printf("\n      Codigo n�o encontrado.\n\n");
            }
            fclose(arquivo_do_voo_bin);//Fechar o arquivo do voo
        }else{
            printf("\n    Erro ao abrir o arquivo do voo.\n\n");
        }
    }
    */
    //Forma 2 de fazer.
    //Reserva: Codigo do voo:
    arquivo_do_voo = fopen("arquivo_1.txt", "r");//Abrir o arquivo do voo para leitura
    digitado = cadeira.linha_karman.codigo_voo;
    printf(" 2- Insira o c�digo do voo: ");
    fflush(stdin);
    fgets(cadeira.linha_karman.codigo_voo, LIMITE_1, stdin);//Leitura do c�digo do voo
    if(funcao_validar_codigo(cadeira.linha_karman) == 0){
        while(funcao_validar_codigo(cadeira.linha_karman) != 1){
            printf("\n     Codigo de voo deve ser no formato JEB-XXXX. Preencha novamente.\n\n");
            printf(" 2- Insira o codigo do voo novamente: ");
            fflush(stdin);
            fgets(cadeira.linha_karman.codigo_voo, LIMITE_1, stdin);//Leitura do c�digo do voo novamente
        }
    }
    if(funcao_validar_codigo(cadeira.linha_karman) == 1){
        while( !feof(arquivo_do_voo) ){
            fflush(stdin);
            fgets(auxiliar, 100, arquivo_do_voo);//A variavel auxiliar ir� receber do arquivo_do_voo
            strcmp(auxiliar, digitado);
            //printf("%s", auxiliar);
            if( strcmp(auxiliar, digitado) == 0){
                variavel = 1;
                //Escrever o codigo do voo no arquivo do voo arquivo_1
                fprintf(arquivo_da_reserva, "%s\n", cadeira.linha_karman.codigo_voo);
                break;
            }else{
                variavel = 0;
            }
        }
        if(variavel == 0){
            printf("\n     Codigo n�o encontrado.\n\n");
        }
    }
    fclose(arquivo_do_voo);//Fechar o arquivo do voo

    printf(" 3- Insira o CPF do passageiro. (Somente numeros): ");
    fflush(stdin);
    fgets(cadeira.cpf_passageiro, 12, stdin);//Leitura do CPF
    if( (funcao_validar_cpf(cadeira) == 0) ){
        while( (funcao_validar_cpf(cadeira) != 1) ){
             printf("\n    CPF informado incorreto.\n\n");
            //Novo cadastramento do CPF
            printf(" 3- Insira o CPF do passageiro novamente: ");
            fflush(stdin);
            fgets(cadeira.cpf_passageiro, 12, stdin);//Leitura do CPF novamente
        }
    }
    if( (funcao_validar_cpf(cadeira) == 1) ){
        //Escrever o CPF do usu�rio no arquivo_2
        fprintf(arquivo_da_reserva, "%s\n", cadeira.cpf_passageiro);
    }

    printf(" 4- Insira o nome do passageiro: ");
    fflush(stdin);
    fgets(cadeira.nome_passageiro, 100, stdin);//Leitura do nome.
    fprintf(arquivo_da_reserva, "%s\n", cadeira.nome_passageiro);

    printf(" 5- Insira o sexo do passageiro (M para masculino; F para feminino): ");
    fflush(stdin);
    scanf("%c", &cadeira.sexo);//Leitura do sexo.
    if( (funcao_validar_sexo(cadeira) == 0) ){
        while( (funcao_validar_sexo(cadeira) != 1) ){
            printf("\n    Sexo informado incorreto.\n\n");
            printf(" 5- Insira o sexo novamente: ");
            fflush(stdin);
            scanf("%c", &cadeira.sexo);
        }
    }
    if( ( funcao_validar_sexo(cadeira) == 1 ) ){
        fprintf(arquivo_da_reserva, "%c\n", cadeira.sexo);
    }

    printf(" 6- Insira o dia de nascimento do passageiro: ");
    fflush(stdin);
    scanf("%d", &cadeira.dia_nascimento);//Leitura do dia.

    if(cadeira.dia_nascimento > 31 || cadeira.dia_nascimento <= 0){
        while(cadeira.dia_nascimento > 31 || cadeira.dia_nascimento <= 0){
            printf("\n    Dia informado incorreto.\n\n");
            //Novo cadastramento do dia do voo
            printf(" 3- Insira o dia de nascimento novamente: ");
            fflush(stdin);
            scanf("%d", &cadeira.dia_nascimento);//Leitura do dia novamente
        }
    }
    if( cadeira.dia_nascimento <= 31 && cadeira.dia_nascimento > 0){

        fprintf(arquivo_da_reserva, "%d\n", cadeira.dia_nascimento);
    }

    printf(" 7- Insira o m�s de nascimento do passageiro: ");
    fflush(stdin);
    scanf("%d", &cadeira.mes_nascimento);

    if( (cadeira.mes_nascimento > 12) || (cadeira.mes_nascimento <= 0) ){
        while(cadeira.mes_nascimento > 12 || cadeira.mes_nascimento <= 0){
            printf("\n    M�s informado incorreto.\n\n");

            printf(" 4- Insira o m�s de nascimento novamente: ");
            fflush(stdin);
            scanf("%d", &cadeira.mes_nascimento);
        }
    }
    if( (cadeira.mes_nascimento <= 12) && (cadeira.mes_nascimento > 0) ){

        fprintf(arquivo_da_reserva, "%d\n" , cadeira.mes_nascimento);
    }

    printf(" 8- Insira o ano de nascimento do passageiro: ");
    fflush(stdin);
    scanf("%d", &cadeira.ano_nascimento);

    if( (cadeira.ano_nascimento < 1956 ) || (cadeira.ano_nascimento > 2003 ) ){
        while( (cadeira.ano_nascimento < 1956) || (cadeira.ano_nascimento > 2003) ){
            printf("\n    Ano informado incorreto.\n\n");
            printf(" 8- Insira o ano de nascimento novamente: ");
            fflush(stdin);
            scanf("%d", &cadeira.ano_nascimento);
        }
    }
    if(cadeira.ano_nascimento >= 1956 && cadeira.ano_nascimento <= 2003){
        if(funcao_validar_data_2(cadeira) == 0){
            printf("\n    Data inexiste no calendario gregoriano. \n\n");
            while(funcao_validar_data_2(cadeira) != 1){
                printf(" 8- Insira o ano de nascimento novamente: ");
                fflush(stdin);
                scanf("%d", &cadeira.ano_nascimento);
            }
        }else{
            fprintf(arquivo_da_reserva, "%d\n", cadeira.ano_nascimento);
        }
    }

    printf(" 9- Insira status do voo. (1 para ativo; 0 para cancelado): ");
    fflush(stdin);
    scanf("%d", &cadeira.linha_karman.status_voo);


    fseek(arquivo_da_reserva_bin, 0, SEEK_SET);

    fwrite(&cadeira, sizeof(struct reserva), 1, arquivo_da_reserva_bin);

    fclose(arquivo_da_reserva_bin);
    fclose(arquivo_da_reserva);

    return cadeira;
}

int funcao_validar_cpf(struct reserva cadeira){

    int inteiro_cpf[12];
    int i, digito_1, resto_1, resto_2, digito_2, valor, soma_1, soma_2;

    soma_1 = 0;
    soma_2 = 0;

    for(i = 0; i < 11; i++){
        inteiro_cpf[i] = cadeira.cpf_passageiro[i] - 48;
    }

    for(i = 0; i <= 8; i++){
        soma_1 = soma_1 + inteiro_cpf[i]*(10-i);
    }
        resto_1 = soma_1 % 11;
    if( (resto_1 == 0) || (resto_1 == 1) ){
        digito_1 = 0;
    }else{
        digito_1 = 11 - resto_1;
    }

    for(i=0;i<10;i++){
        soma_2 = soma_2 + inteiro_cpf[i]*(11-i);
    }
    valor=(soma_2/11)*11;
    resto_2 = soma_2 - valor;
    if( (resto_2 == 0) || (resto_2 == 1) ){
        digito_2 = 0;
    }else{
        digito_2 = 11 - resto_2;
    }

    if( (digito_1 == inteiro_cpf[9]) && (digito_2 == inteiro_cpf[10]) ){
        return 1;
    }else{
        return 0;
    }
}

int funcao_validar_data(struct voo viagem){

    struct tm *data_hora_atual;
    time_t segundos;

    time(&segundos);
    data_hora_atual = localtime(&segundos);

    if (viagem.ano >= (data_hora_atual->tm_year+1900) && viagem.ano <= 2121 ){

        if (viagem.mes >= 1 && viagem.mes <= 12){

            if ((viagem.dia >= 1 && viagem.dia <= 31) && (viagem.mes == 1 || viagem.mes== 3 || viagem.mes== 5 || viagem.mes == 7 || viagem.mes == 8 || viagem.mes == 10 || viagem.mes == 12))
                return 1;
            else if ((viagem.dia >= 1 && viagem.dia <= 30) && (viagem.mes == 4 || viagem.mes == 6 || viagem.mes == 9 || viagem.mes == 11))
                return 1;
            else if ((viagem.dia >= 1 && viagem.dia <= 28) && (viagem.mes == 2))
                return 1;
            else if (viagem.dia == 29 && viagem.mes == 2 && (viagem.ano % 400 == 0 || (viagem.ano % 4 == 0 && viagem.ano % 100 != 0)))
                return 1;
            else
                return 0;
        }else{
            return 0;
        }
    }else{
        return 0;
    }
}

int funcao_validar_data_2(struct reserva cadeira){

    if (cadeira.ano_nascimento > 1956 && cadeira.ano_nascimento < 2003 ){

        if (cadeira.mes_nascimento >= 1 && cadeira.mes_nascimento <= 12){

            if ((cadeira.dia_nascimento >= 1 && cadeira.dia_nascimento <= 31) && (cadeira.mes_nascimento == 1 || cadeira.mes_nascimento == 3 || cadeira.mes_nascimento == 5 || cadeira.mes_nascimento == 7 || cadeira.mes_nascimento == 8 || cadeira.mes_nascimento == 10 || cadeira.mes_nascimento == 12))
                return 1;
            else if ((cadeira.dia_nascimento >= 1 && cadeira.dia_nascimento <= 30) && (cadeira.mes_nascimento== 4 || cadeira.mes_nascimento == 6 || cadeira.mes_nascimento == 9 || cadeira.mes_nascimento  == 11))
                return 1;
            else if ((cadeira.dia_nascimento >= 1 && cadeira.dia_nascimento <= 28) && (cadeira.mes_nascimento == 2))
                return 1;
            else if (cadeira.dia_nascimento == 29 && cadeira.mes_nascimento == 2 && (cadeira.ano_nascimento % 400 == 0 || (cadeira.ano_nascimento % 4 == 0 && cadeira.ano_nascimento % 100 != 0)))
                return 1;
            else
                return 0;
        }else{
            return 0;
        }
    }else{
        return 0;
    }
}

int funcao_validar_codigo(struct voo viagem){
    if(viagem.codigo_voo[0] == 'J'){
    }else{
        return 0;
    }

    if(viagem.codigo_voo[1] == 'E'){
    }else{
        return 0;
    }

    if(viagem.codigo_voo[2] == 'B'){
    }else{
        return 0;
    }

    if(viagem.codigo_voo[3] == '-'){
    }else{
        return 0;
    }

    if(viagem.codigo_voo[4] > '0' && viagem.codigo_voo[4] <= '9'){
    }else{
        return 0;
    }

    if(viagem.codigo_voo[5] >= '0' && viagem.codigo_voo[5] <= '9'){
    }else{
        return 0;
    }

    if(viagem.codigo_voo[6] >= '0' && viagem.codigo_voo[6] <= '9'){
    }else{
        return 0;
    }

    if(viagem.codigo_voo[7] >= '0' && viagem.codigo_voo[7]  <= '9'){
    }else{
        return 0;
    }
    return 1;
}

int funcao_validar_numero(struct reserva cadeira){
    if(cadeira.numero_reserva[0] == 'G'){
    }else{
        return 0;
    }

    if(cadeira.numero_reserva[1] == 'B'){
    }else{
        return 0;
    }

    if(cadeira.numero_reserva[2] == '-'){
    }else{
        return 0;
    }

    if(cadeira.numero_reserva[3] > '0' && cadeira.numero_reserva[3] <= '9'){
    }else{
        return 0;
    }

    if(cadeira.numero_reserva[4] >= '0' && cadeira.numero_reserva[4] <= '9'){
    }else{
        return 0;
    }

    if(cadeira.numero_reserva[5] >= '0' && cadeira.numero_reserva[5] <= '9'){
    }else{
        return 0;
    }

    if(cadeira.numero_reserva[6] >= '0' && cadeira.numero_reserva[6] <= '9'){
    }else{
       return 0;
    }

    if(cadeira.numero_reserva[7] >= '0' && cadeira.numero_reserva[7] <= '9'){
    }else{
        return 0;
    }

    if(cadeira.numero_reserva[8] >= '0' && cadeira.numero_reserva[8] <= '9'){
    }else{
        return 0;
    }
    return 1;
}

int funcao_validar_sexo(struct reserva cadeira){
    switch(cadeira.sexo){
        case 'M':
            return 1;
            break;
        case 'm':
            return 1;
            break;
        case 'F':
            return 1;
            break;
        case 'f':
            return 1;
            break;
        default:
            return 0;
            break;
    }
}

int funcao_validar_nome(struct reserva cadeira){

    int i; //Contador

    for(i = 0; i < 30; i++){
        if( ( cadeira.nome_passageiro[i] >= 'A' || 'a' || ' ' ) &&(cadeira.nome_passageiro[i] <= 'Z' || 'z' || ' ' ) ){
            printf("%s", cadeira.nome_passageiro);
        }else{
            return 0;
        }
        return 1;
    }
}

void mensagem_menu(){
    printf(" Voo - linha Karman \n");
    printf(" 1) Cadastrar voo       2) Cadastrar reserva        3) Consultar voo\n");
    printf(" 4) Consultar reserva   5) Consultar passageiro     6) Cancelar voo\n");
    printf(" 7) Cancelar reserva    8) Excluir voo              9) Sair\n");
    printf(" Digite entre 1 e 9 para fazer uma escolha: ");
}

void cadastrar_voo(){

    struct voo viagem;
    char resposta;

    printf("\n 1) Cadastrar voo.");
    do{
        viagem = funcao_cadastrar_voo();
        //Verificar resposta do cadastrante:
        printf("    Deseja cadastrar mais um voo? (S para sim ou N para nao): ");
        fflush(stdin);
        scanf("%c", &resposta);

    }while( (resposta == 'S') || (resposta == 's') );
    //Se a resposta for negativa, retornar� ao menu.
    if( (resposta == 'N') || (resposta == 'n') ){
        limpar_tela();
        main();//Chamada da fun��o principal
    }
}

void cadastrar_reserva(){

    struct reserva cadeira;
    char resposta;

    printf("\n 2) Cadastrar reserva.");
    do{
        cadeira = funcao_cadastrar_reserva();
        //Verificar resposta do cadastrante:
        printf("\n Deseja consultar mais um voo? (S para sim ou N para nao): ");
        fflush(stdin);
        scanf("%c", &resposta);
    }while( (resposta == 'S') || (resposta == 's') );
    if( (resposta == 'N') || (resposta == 'n') ){
        limpar_tela();
        main();
    }
}

void consultar_voo(){

    struct voo viagem;
    int bandeira;
    int variavel;
    FILE *arquivo_do_voo;
    FILE *arquivo_do_voo_bin;
    char *digitado;
    char auxiliar[100];
    char resposta;

    arquivo_do_voo_bin = fopen("arquivo_1b.dat", "rb");
    arquivo_do_voo = fopen("arquivo_1.txt", "rt");

    do{

        if(variavel == 0){
            printf(" 1- Insira o codigo do voo novamente: ");
        }else{
            printf("\n 3) Consultar voo.\n");
            printf(" 1- Digite o voo que deseja consultar. (Formato JEB-XXXX): ");
        }
        fflush(stdin);
        fgets(viagem.codigo_voo,  LIMITE_1, stdin);
        if(funcao_validar_codigo(viagem) == 0){
           while(funcao_validar_codigo(viagem) != 1){
                printf("\n     Codigo de voo deve ser no formato JEB-XXXX. Preencha novamente.\n\n");
                printf(" 1- Insira o codigo do voo novamente: ");
                fflush(stdin);
                fgets(viagem.codigo_voo, LIMITE_1, stdin);
            }
        }
        //Armazenar o valor digitado na variavel digitado
        digitado = viagem.codigo_voo;

        while( !feof(arquivo_do_voo) ){
            fflush(stdin);
            fgets(auxiliar, 100, arquivo_do_voo);
            printf("%s", auxiliar);
            strcmp(auxiliar, digitado);
            //printf("%s", auxiliar);
            if( strcmp(auxiliar, digitado) == 0){
                variavel = 1;
                //printf("%s", auxiliar);
                break;
            }else{
                variavel = 0;
            }
        }
            if(variavel == 0){
                printf("\n     Codigo nao encontrado. Refaca a operacao.\n\n");
                consultar_voo();
            }
        //Se o codigo digitado for valido
        if(funcao_validar_codigo(viagem) == 1){
            //Enquanto nao chegar no fim do arquivo
            fseek(arquivo_do_voo_bin, 0, SEEK_SET);
            while(fread(&viagem, sizeof(struct voo), 1, arquivo_do_voo_bin)){
                if(strcmp(auxiliar, digitado) == 0){
                    //printf("%s", viagem.codigo_voo);
                //if(strstr(viagem.codigo_voo, digitado) != NULL){
                    bandeira = 1;
                    printf("\n Informacoes:\n\n");
                    printf("    %s\n    Capacidade: %d\n    Data: %d/%d/%d\n    Hora: %d:%d\n    Status: %d\n", viagem.codigo_voo, viagem.capacidade_voo, viagem.dia, viagem.mes, viagem.ano, viagem.hora, viagem.minuto, viagem.status_voo);
                    break;
                }else{
                    bandeira = 0;
                }
            }
            if(bandeira == 0){
                if(variavel == 1){
                    printf("\n      Codigo nao encontrado.\n\n");
                }
            }
        }
        printf("\n Deseja consultar mais um voo? (S para sim ou N para nao): ");
        //Ler resposta do usuario se deseja continuar o encerrar a procura de voos
        scanf("%c", &resposta);
    }while(resposta == 's' || resposta == 'S');
    if(resposta == 'n' || resposta == 'N' || resposta != 'S' || resposta != 's'){
        //Fechar o arquivo do voo texto
        fclose(arquivo_do_voo);
        //Fechar arquivo do voo binario
        fclose(arquivo_do_voo_bin);
        limpar_tela();
        main();
    }
}
/*
    arquivo_do_voo = fopen("arquivo_1.txt", "rt");
    // 1) Usu�rio ir� procurar o voo que deseja consultar:
    printf(" 1- Digite o voo que deseja consultar: ");
    fflush(stdin);
    fgets(viagem.codigo_voo,  LIMITE_1, stdin);
    if(funcao_validar_codigo(viagem) == 0){
       while(funcao_validar_codigo(viagem) != 1){
            printf("\n     Codigo de voo deve ser no formato JEB-XXXX. Preencha novamente.\n\n");
            printf(" 1- Insira o codigo do voo novamente: ");
            fflush(stdin);
           fgets(viagem.codigo_voo, LIMITE_1, stdin);
        }
    }
    digitado = viagem.codigo_voo;
    buscado = viagem.capacidade_voo;
    //Se o codigo digitado for valido
    if(funcao_validar_codigo(viagem) == 1){
        //Enquanto nao chegar no fim do arquivo do voo
        while(!feof(arquivo_do_voo) ){
            fflush(stdin);
            //Buscar o codigo do voo e armazenar na variavel auxliar
            fgets(auxiliar, sizeof(struct voo), arquivo_do_voo);//A variavel auxiliar ir� receber do arquivo_do_voo
            //Buscar a capacidade do voo e armazenar na variavel auxiliar_2
            fgets(auxiliar_2, sizeof(struct voo), arquivo_do_voo);
            strcmp(auxiliar, digitado);
            if(strcmp(auxiliar, digitado) == 0){
                bandeira = 1;
                printf("\n     Voo localizado.\n\n");
                printf(" Informacoes do voo: \n");
                printf("%s", viagem.codigo_voo);
                break;
            }else{
                bandeira = 0;
            }
            if( strcmp(auxiliar_2, buscado) == 0 ){
                printf("%d", viagem.capacidade_voo);
            }
        //printf(" %s\n Capacidade: %d\n Data: %d/%d/%d\n Hora: %d:%d\n Status: %d\n", viagem.codigo_voo, viagem.capacidade_voo, viagem.dia, viagem.mes, viagem.ano, viagem.hora, viagem.minuto, viagem.status_voo);
        }
        if(bandeira == 0){
            printf("\n     Codigo n�o encontrado.\n\n");
        }
    fclose(arquivo_do_voo);//Fechar arquivo do voo
    }
}
*/

void consultar_reserva(){
    //Declara��es
    struct reserva cadeira;
    int bandeira_2;
    int variavel_2;
    FILE *arquivo_da_reserva;
    FILE *arquivo_da_reserva_bin;
    char *digitado_2;
    char auxiliar_2[100];
    char resposta_2;

    arquivo_da_reserva_bin = fopen("arquivo_2b.dat", "rb");
    arquivo_da_reserva = fopen("arquivo_2.txt", "rt");
    do{
        //Se o codigo nao existir no arquivo da reserva na primeira rodagem
        if(variavel_2 == 0){
            printf(" 1- Insira o numero da reserva novamente: ");
        }else{
            printf("\n 4) Consultar reserva.\n");//Mensagem de item escolhido
            printf(" 1- Digite a reserva que deseja consultar: ");
        }
        //Consultar codigo
        fflush(stdin);
        fgets(cadeira.numero_reserva,  LIMITE_2, stdin);
        if(funcao_validar_numero(cadeira) == 0){
            while(funcao_validar_numero(cadeira) != 1){
                printf("\n    Numero da reserva deve ser no formato GB-XXXXXX. Preencha novamente.\n\n");
                printf(" 1- Insira o numero da reserva novamente: ");
                fflush(stdin);
                fgets(cadeira.numero_reserva,  LIMITE_2, stdin);
            }
        }
        //Armazenar o valor digitado na variavel digitado
        digitado_2 = cadeira.numero_reserva;
        //Procurar o codigo digitado no arquivo da reserva
        while( !feof(arquivo_da_reserva) ){
            fflush(stdin);
            fgets(auxiliar_2, 100, arquivo_da_reserva);//A variavel auxiliar ir� receber do arquivo_do_voo
            strcmp(auxiliar_2, digitado_2);
            //printf("%s", auxiliar_2);
            if( strcmp(auxiliar_2, digitado_2) == 0){
                variavel_2 = 1;
                //printf("%s", auxiliar_2);
                break;
            }else{
                variavel_2 = 0;
            }
        }
            if(variavel_2 == 0){
                printf("\n     Numero nao encontrado. Refaca a operacao.\n\n");
                consultar_reserva();
            }
        //Se o numero digitado for valido
        if(funcao_validar_numero(cadeira) == 1){
            fseek(arquivo_da_reserva_bin, 0, SEEK_SET);
            while(fread(&cadeira, sizeof(struct reserva), 1, arquivo_da_reserva_bin)){
                if(strcmp(auxiliar_2, digitado_2) == 0){
                    bandeira_2 = 1;
                    printf("\n Informacoes:\n\n");
                    printf("    %s\n    Codigo do voo: %s\n    CPF: %s\n    Nome: %s\n    Sexo: %c\n    Data de nascimento: %d/%d/%d\n", cadeira.numero_reserva, cadeira.linha_karman.codigo_voo, cadeira.cpf_passageiro, cadeira.nome_passageiro, cadeira.sexo, cadeira.dia_nascimento, cadeira.mes_nascimento, cadeira.ano_nascimento);
                    break;
                }else{
                    bandeira_2 = 0;
                }
            }
            if(bandeira_2 == 0){
                if(variavel_2 == 1){
                    printf("\n      Numero nao encontrado.\n\n");
                }
            }
        }
        printf("\n Deseja consultar mais um voo? (S para sim ou N para nao): ");
        scanf("%c", &resposta_2);
    }while(resposta_2 == 's' || resposta_2 == 'S');
    if(resposta_2 == 'n' || resposta_2 == 'N' || resposta_2 != 'S' || resposta_2 != 's'){
        //Fechar o arquivo do voo texto
        fclose(arquivo_da_reserva);
        //Fechar arquivo do voo binario
        fclose(arquivo_da_reserva_bin);
        limpar_tela();
        main();
    }
}

void consultar_passageiro(){
    //Declara��es
    struct reserva cadeira;
    int bandeira_3;
    int variavel_3;
    FILE *arquivo_da_reserva;
    FILE *arquivo_da_reserva_bin;
    char *digitado_3;
    char auxiliar_3[100];
    char resposta;

    do{
        //Abrir arquivos para leitura em binario e texto
        arquivo_da_reserva_bin = fopen("arquivo_2b.dat", "rb");
        arquivo_da_reserva = fopen("arquivo_2.txt", "rt");
        if(variavel_3 == 0){
            printf(" 1- Insira o CPF do passageiro novamente: ");
        }else{
            printf("\n 5) Consultar passageiro.\n");
            printf(" 1- Insira o CPF do passageiro. (Somente numeros): ");
        }
        //Consultar CPF
        fflush(stdin);
        fgets(cadeira.cpf_passageiro, 13, stdin);//Leitura do CPF
        //printf("%s", cadeira.cpf_passageiro);
        if( (funcao_validar_cpf(cadeira) == 0) ){
            while( (funcao_validar_cpf(cadeira) != 1) ){
                printf("\n    CPF informado incorreto.\n\n");
                //Novo cadastramento do CPF
                printf(" 1- Insira o CPF do passageiro novamente: ");
                fflush(stdin);
                fgets(cadeira.cpf_passageiro, 13, stdin);//Leitura do CPF novamente
            }
        }
        //Armazenar o valor digitado na variavel digitado
        digitado_3 = cadeira.cpf_passageiro;
        //printf("%s", cadeira.cpf_passageiro);
        //printf("%s", cadeira.cpf_passageiro);
        //Procurar o codigo digitado no arquivo da reserva
        while( !feof(arquivo_da_reserva) ){
            fflush(stdin);
            fgets(auxiliar_3, 100, arquivo_da_reserva);//A variavel auxiliar ir� receber do arquivo_do_voo
            strcmp(auxiliar_3, digitado_3);
            //printf("%s", auxiliar_3);
            //printf("%s", digitado_3);
            if( strcmp(auxiliar_3, digitado_3) == 0 ){
                variavel_3 = 1;
                //printf("%s", auxiliar_3);
                break;
            }else{
                variavel_3 = 0;
            }
        }
        if(variavel_3 == 0){
            printf("\n     CPF nao encontrado. Refaca a operacao.\n\n");
            consultar_passageiro();
        }
        //Se o CPF digitado for valido
        if(funcao_validar_cpf(cadeira) == 1){
            fseek(arquivo_da_reserva_bin, 0, SEEK_SET);
            while(fread(&cadeira, sizeof(struct reserva), 1, arquivo_da_reserva_bin)){
                if(strstr(auxiliar_3, digitado_3) != NULL ){
                    bandeira_3 = 1;
                    printf("\n Informacoes:\n\n");
                    printf("    %s\n", cadeira.cpf_passageiro);
                    printf("    Nome: %s\n", cadeira.nome_passageiro);
                    printf("    Sexo: %c\n", cadeira.sexo);
                    printf("    Data de nascimento: %d/%d/%d\n", cadeira.dia_nascimento, cadeira.mes_nascimento, cadeira.ano_nascimento);
                    break;
                }else{
                    bandeira_3 = 0;
                }
            }
            if(bandeira_3 == 0){
                if(variavel_3 == 1){
                    printf("\n      CPF nao encontrado.\n\n");
                }
            }
        }
        //Fechar o arquivo do voo texto
        fclose(arquivo_da_reserva);
        //Fechar arquivo do voo binario
        fclose(arquivo_da_reserva_bin);
        printf("\n Deseja consultar mais um voo? (S para sim ou N para nao): ");
        scanf("%c", &resposta);
    }while(resposta == 's' || resposta == 'S');
       if(resposta == 'n' || resposta == 'N' || resposta != 'S' || resposta != 's'){
        limpar_tela();
        main();
    }
}

void cancelar_voo(void){
    printf("\nCancelamento de voo.\n");
    return;
}

void cancelar_reserva(void){
    printf("\nCancelamento de reserva.\n");
    return;
}

void excluir_voo(void){
    printf("\nExclus�o de voo.\n");
    return;
}

void sair(){
    printf("\n Encerrado com sucesso.\n");
    system("cls || clear");
    return;
}

void limpar_tela(){
    system("cls || clear");
}

void gravar_arquivo_voo(struct voo viagem){//Nao usado neste programa

    FILE *arquivo_do_voo_bin;
    FILE *arquivo_do_voo;

    arquivo_do_voo = fopen("arquivo_1.txt", "r+b");
    arquivo_do_voo_bin = fopen("arquivo_1b.dat", "ab");
    if(arquivo_do_voo_bin){
        fseek(arquivo_do_voo_bin, 0, SEEK_SET);
        //fwrite(&viagem, sizeof(viagem), 1, arquivo_do_voo_bin);//Escrever em modo bin�rio no novo arquivo
        fclose(arquivo_do_voo);
        fclose(arquivo_do_voo_bin);
    }else{
        printf("\n      Erro ao abrir o arquivo do voo para registro em bin�rio.\n\n");
    }
}
