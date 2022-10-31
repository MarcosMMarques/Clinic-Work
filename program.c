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
}medic_struct;

typedef struct{    //PACIENTE
    char cpf[12];
    char name[50];
    char birthdate[11];
    char telephone[12];
}patient_struct;

typedef struct{    //CONSULTA
    char crm[6];
    char cpf[12];
    char symptom[100];
    char forwading[100];
    char date[11];
}struct_medical_appointment;

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
    // mostrarDados();
}

char * touppername(char n[50]){
    int x = 0;
    while(n[x] != '\0'){
        if(x == 0){
            n[x] = toupper(n[x]);
        }
        if(n[x] == ' '){
            n[x+1] = toupper(n[x+1]);
        }
        x++;
    }
    return n;
}

void append(int quantity, int type){
    if(type == 1){
        for(int i=0;i<quantity;i++){
            medic_struct m;
            FILE *medic;   
            medic = fopen ("Medic.bin", "ab");
            printf("\nMedico: %d\n",i+1);
            printf("Digite o nome: ");
            scanf("%[^\n]%*c", m.name);

            strcpy(m.name, touppername(m.name));

            printf("Digite o CRM: ");
            scanf("%[^\n]%*c", m.crm);
            printf("Digite a data de nascimento: ");
            scanf("%[^\n]%*c", m.birthdate);
            printf("Digite o telefone: ");
            scanf("%[^\n]%*c", m.telephone);
            printf("Digite a especialidade: ");
            scanf("%[^\n]%*c", m.specialty);
            printf("Digite o valor de hora do trabalho: ");
            scanf("%f%*c", &m.price_hour_work);
            fwrite (&m, sizeof (medic_struct), 1, medic);
            fclose (medic);
        }
    }else if(type == 2){
        for(int i=0;i<quantity;i++){
            patient_struct p;
            FILE *patient;   
            patient = fopen ("Patient.bin", "ab");
            printf("\nPaciente: %d\n",i+1);
            printf("Digite o nome: ");
            scanf("%[^\n]%*c", p.name);

            strcpy(p.name, touppername(p.name));

            printf("Digite o cpf: ");
            scanf("%[^\n]%*c", p.cpf);
            printf("Digite a data de nascimento: ");
            scanf("%[^\n]%*c", p.birthdate);
            printf("Digite o telefone: ");
            scanf("%[^\n]%*c", p.telephone);
            fwrite (&p, sizeof (patient_struct), 1, patient);
            fclose (patient);
        }
    }
}
void search(char name[50], int type){
    strcpy(name, touppername(name));
    if(type == 1){
        medic_struct m;
        FILE *medic;
        medic = fopen ("Medic.bin", "rb");
        int response = 0;
	    while(fread(&m, sizeof (medic_struct), 1, medic)){
            if(strcmp(name, m.name) == 0){
                printf("\nNome: %s", m.name);
                printf("\nCRM: %s", m.crm);
                printf("\nData de Nascimento: %s",m.birthdate);
                printf("\nTelefone: %s", m.telephone);
                printf("\nEspecialidade: %s", m.specialty);
                printf("\nValor de Hora do Trabalho: R$ %.2f", m.price_hour_work);
                response = 1;
                fclose (medic);
                break;
            }
	    }
        if(response == 0){
            printf("\nMedico não encontrado.");
        }
    }else if(type == 2){
        patient_struct p;
        FILE *patient;
        patient = fopen ("Patient.bin", "rb");
        int response = 0;
	    while(fread(&p, sizeof (patient_struct), 1, patient)){
            if(strcmp(name, p.name) == 0){
                printf("\nNome: %s", p.name);
                printf("\nCPF: %s",p.cpf);
                printf("\nData de Nascimento: %s",p.birthdate);
                printf("\nTelefone: %s",p.telephone);
                response = 1;
                fclose (patient);
                break;
            }
	    }
        if(response == 0){
            printf("\nPaciente não encontrado.");
        }
    }
}

void patch(char name[50], int type){
    strcpy(name, touppername(name));
    if(type == 1){
        medic_struct m;
        FILE *medic;
        medic = fopen ("Medic.bin", "rb+");
        int control, response=0;
	    while(fread(&m, sizeof (medic_struct), 1, medic)){
            if(strcmp(name, m.name) == 0){
                response = 1;
                break;
            }
            control++;
	    }
        if(response){
            printf("Digite novamente o nome: ");
            scanf("%[^\n]%*c", m.name);

            strcpy(m.name, touppername(m.name));

            printf("Digite novamente o CRM: ");
            scanf("%[^\n]%*c", m.crm);
            printf("Digite novamente a data de nascimento: ");
            scanf("%[^\n]%*c", m.birthdate);
            printf("Digite novamente o telefone: ");
            scanf("%[^\n]%*c", m.telephone);
            printf("Digite novamente a especialidade: ");
            scanf("%[^\n]%*c", m.specialty);
            printf("Digite novamente o valor de hora do trabalho: ");
            scanf("%f%*c", &m.price_hour_work);
            fseek(medic, (control)*sizeof(medic_struct), SEEK_SET);
            fwrite (&m, sizeof(medic_struct), 1, medic);
        }else{
            printf("\nMeidoc nao encontrado.");
        }
        fclose (medic);
    }else if(type == 2){
        patient_struct p;
        FILE *patient;
        patient = fopen ("Patient.bin", "rb+");
        int control, response=0;
	    while(fread(&p, sizeof (patient_struct), 1, patient)){
            if(strcmp(name, p.name) == 0){
                response = 1;
                break;
            }
            control++;
	    }
        if(response){
            printf("Digite novamente o nome: ");
            scanf("%[^\n]%*c", p.name);

            strcpy(p.name, touppername(p.name));

            printf("Digite novamente o cpf: ");
            scanf("%[^\n]%*c", p.cpf);
            printf("Digite novamente a data de nascimento: ");
            scanf("%[^\n]%*c", p.birthdate);
            printf("Digite novamente o telefone: ");
            scanf("%[^\n]%*c", p.telephone);
            fseek(patient, (control)*sizeof(patient_struct), SEEK_SET);
            fwrite (&p, sizeof(patient_struct), 1, patient);
        }else{
            printf("\nPaciente nao encontrado.");
        }
        fclose (patient);
    }
}

void patient(){
    int loop = 1, option;
    char name[50];
    while(loop){
        printf("\n*******************************************\n");
        printf("O que deseja fazer? Digite a opção Desejada:\n");
        printf("Inserir novo paciente (1)\n");
        printf("Buscar pelo nome (2)\n");
        printf("Alterar dados de um determinado paciente (3)\n");
        printf("Voltar (0)\n");
        printf("*******************************************\n");
        scanf("%d%*c",&option);
        system("clear");
        switch(option){
            case 0:      
                return;
    
            case 1:
                int aux;
                printf("\nDigite quantos pacientes quer adicionar: ");
                scanf("%d%*c",&aux);      
                append(aux, 2);
                break;  

            case 2:
                printf("\nDigite o nome do paciente: ");
                scanf("%[^\n]%*c", name);      
                search(name, 2); //Retornar um array para ser utilizado na função patch
                break;
            
            case 3:
                printf("\nDigite o nome do paciente: ");
                scanf("%[^\n]%*c", name);  
                patch(name, 2);
                break;
        }
    }
}

void list(){
        medic_struct m;
        FILE *medic;
        medic = fopen ("Medic.bin", "rb");
        int count=0;
	    while(fread(&m, sizeof (medic_struct), 1, medic)){
            count++;
	    }
        char *specialty_array[count];
        int response = 1;
        int aux=0;
        medic = fopen ("Medic.bin", "rb");
        while(fread(&m, sizeof (medic_struct), 1, medic)){
            for(int i=0;i<aux;i++){
                if(strcmp(specialty_array[i], m.specialty) == 0){
                    response = 0;
                }
            }
            if(response){
                specialty_array[aux] = malloc(strlen(m.specialty));
                strcpy(specialty_array[aux], m.specialty);
                aux++;
            }
            response = 1;
	    }
        for(int i=0;i<aux;i++){
            printf("%s:\n", specialty_array[i]);
            medic = fopen ("Medic.bin", "rb");
	        while(fread(&m, sizeof (medic_struct), 1, medic)){
                if(strcmp(specialty_array[i], m.specialty) == 0){
                    printf(" %s\n", m.name);
                }
	        }
        }
        fclose (medic);

}

void medic(){
    int loop = 1, option;
    char name[50];
    while(loop){
        printf("\n*******************************************\n");
        printf("O que deseja fazer? Digite a opção Desejada:\n");
        printf("Inserir novo medico (1)\n");
        printf("Buscar pelo nome (2)\n");
        printf("Alterar dados de um determinado medico (3)\n");
        printf("Lista medicos por especialidade (4)\n");
        printf("Voltar (0)\n");
        printf("*******************************************\n");
        scanf("%d%*c",&option);
        system("clear");
        switch(option){
            case 0:      
                return;
    
            case 1:
                int aux;
                printf("\nDigite quantos medicos quer adicionar: ");
                scanf("%d%*c",&aux);      
                append(aux, 1);
                break;  

            case 2:
                printf("\nDigite o nome do medico: ");
                scanf("%[^\n]%*c", name);      
                search(name, 1); //Retornar um array para ser utilizado na função patch
                break;
            
            case 3:
                printf("\nDigite o nome do medico: ");
                scanf("%[^\n]%*c", name);  
                patch(name, 1);
                break;
            
            case 4:
                list();
        }
    }
}

void logged(){
    int option, loop=1, aux=0;
    while(loop){
        printf("*******************************************\n");
        printf("Listagem de menus:\n");
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
                medic();
                break;
        
            case 2:
                patient();      
                break;
            
            case 3:
                // medical_appointment();
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
            case 0:      
                loop = 0;
                break;
    
            case 1:      
                int loop_login = 1;
                registration user;
                while(loop_login <= 3){
                    printf("Digite o email: ");
                    scanf("%[^\n]%*c", user.user_email);
                    printf("Digite a senha: ");
                    scanf("%[^\n]%*c", user.password);
                    int response = login(user.user_email, user.password);
                    
                    if(loop_login == 3){
                        return 0;
                    }

                    if(response != 400){
                        printf("\nSenha errada, digite novamente! (Tentativas Restantes: %d)\n", 3 - loop_login);
                        loop_login++;
                    }else{
                         logged();
                         break;
                    }
                }
                break;
        
            case 2:      
                registeruser();
                break;
        }
    }

    return 0;
}