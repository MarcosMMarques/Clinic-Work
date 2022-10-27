#include<stdio.h>
#include<stdlib.h>

typedef struct{    //LOGIN
    char user_email[30];
    char password[20];
}registration;

typedef struct{    //MEDICO
    char crm[6];
    char name[50];
    char specialty[20];
    char birthdate[11];
    float price_hour_work;
    char telephone[12];
}medic;

typedef struct{    //PACIENTE
    char cpf[12];
    char name[50];
    char birthdate[11];
    char telephone[12];
}patient;

typedef struct{    //CONSULTA
    char crm[6];
    char cpf[12];
    char symptom[100];
    char forwading[100];
    char date[11];
}medical_appointment;

void mostrarDados(){
	registration user;
        FILE *login;
        login = fopen ("Login.bin", "rb");
	printf("\nListagem de Usuarios Cadastrados");
	while(fread(&user, sizeof (registration), 1, login)){
		printf("\n Name: %s\n Password: %s\n", user.user_email, user.password);
	}
	
	fclose (login);
}

// void Login(){
   
//     switch(option){
//         case 1:     //Médico
//             break;
           
//         case 2:     //Paciente
//             break;
           
//         case 3:     //Consulta
//             break;
//     }
   
// }

void registeruser(int quantify_already_exists){
    registration user;
    FILE *login;   
    login = fopen ("Login.bin", "ab");
    printf("Digite o email: ");
    scanf("%[^\n]%*c", user.user_email);
    printf("Digite a senha: ");
    scanf("%[^\n]", user.password);
    fwrite (&user, sizeof (registration), 1, login);
    fclose (login);
    mostrarDados();
}

// void verifylogin(){
// }

// void appendmedic(){
// }

// void searchname(){

// }

int main(){
    int option, loop=1, aux=0;
    while(loop){
        printf("*******************************************\n");
        printf("O que deseja fazer? Digite a opção Desejada:\n");
        printf("Efetuar Login (1)\n");
        printf("Cadastrar Novo Usuário (2)\n");
        printf("Sair do Programa (0)\n");
        printf("*******************************************\n");
        scanf("%d%*c",&option);
        switch(option){
            case 0:      //Encerrar
                loop = 0;
                break;
    
            case 1:      //Login
                break;
        
            case 2:      //Cadastro
                registeruser(aux);
                aux++;

                // scanf("%s%*c",name);
                // printf("%d",fwrite(name , sizeof(name), 2, archive_login));
                // fclose(archive_login);

                // char leitura[800];
                // archive_login = fopen ("login-archive.bin", "rb");
                // printf("\n%d\n",fread(leitura, sizeof(leitura), 2, archive_login));
                // printf("%s", leitura);
                // fclose(archive_login);
                
                break;
        }
    }

    return 0;
}