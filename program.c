#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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

int login(char email[30], char password[20]){
    registration user;
    FILE *login;
    login = fopen ("Login.bin", "rb");
    int authorization=0;
	while(fread(&user, sizeof (registration), 1, login)){
		if(strcmp(email, user.user_email) == 0 && strcmp(password,user.password) == 0){
            authorization = 400;
            break;
        }
	}
    return authorization;
}

void registeruser(){
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

void logged(){
    int option, loop=1, aux=0;
    while(loop){
        printf("*******************************************\n");
        printf("Menu:\n");
        printf("Medico (1)\n");
        printf("Paciente (2)\n");
        printf("Consulta (3)\n");
        printf("Deslogar (0)\n");
        printf("*******************************************\n");
        scanf("%d%*c",&option);
        system("clear");
        switch(option){
            case 0:      
                return;
    
            case 1:      
                
                break;
        
            case 2:      
                break;
            
            case 3:
                break;
        }
    }
}

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
        system("clear");
        switch(option){
            case 0:      //Encerrar
                loop = 0;
                break;
    
            case 1:      //Login
                int loop_login;
                registration user;
                printf("Digite o email: ");
                scanf("%[^\n]%*c", user.user_email);
                printf("Digite a senha: ");
                scanf("%[^\n]", user.password);
                loop_login = 1;
                while(loop_login <= 3){
                    int response = login(user.user_email, user.password);
                    if(response != 400){
                        loop_login++;
                    }
                    else{
                         logged();
                         break;
                    }
                    if(loop_login){
                        return 0;
                    }
                }
                break;
        
            case 2:      //Cadastro
                registeruser();
                break;
        }
    }

    return 0;
}