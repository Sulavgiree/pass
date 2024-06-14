#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct user{
    char username[50];
    char password[50];
};


void registerf();
int loginf();
void forgotPassword();

int main(){
    int choice;
    printf("WELCOME TO OUR QUIZ BANK\n");
    printf("PLEASE REGISTER FIRST IF YOU ARE NEW USER\n");
    while(1){
        printf("1:Register\n 2:Login\n 3:Forgetpassword\n 4:Exit\n Enter your choice: ");
        scanf("%d",&choice);
        getchar();

        switch(choice){
            case 1:
                registerf();
                break;
            case 2:
                if(loginf()){
                    printf("Login successfull\n");
                }
                else{
                    printf("No username matching\n");
                }
                break;
            case 3:
                forgotPassword();
                break;
            case 4:
                printf("Dhanyabaad\n");
                exit(0);
            default:
                printf("Not valid choice\n");
        }
    }
}

void registerf(){
    FILE *ptr;
    struct user s;
    ptr=fopen("kist.txt","a");
    if(ptr==NULL){
        printf("File not opened");
        exit(1);
    }
    printf("Enter username: \n");
    scanf("%s",s.username);
    getchar();
    printf("Enter password: \n");
    scanf("%s",s.password);
    getchar();
    fwrite(&s,sizeof(struct user),1,ptr);
    fclose(ptr);
    printf("Welcome to our quiz family: \n");
}

int loginf(){
    FILE *ptr;
    struct user s;
    char username[100],password[50];
    int a=0;
    ptr=fopen("kist.txt","r");
    if(ptr==NULL){
        printf("File not opening: ");
        exit(1);
    }
    printf("Enter username: ");
    scanf("%s",username);
    getchar();  

    printf("Enter password: ");
    scanf("%s",password);
    getchar();  

    while(fread(&s,sizeof(struct user),1,ptr)){
        if(strcmp(s.username,username)==0 && strcmp(s.password,password)==0){
            printf("LOGIN SUCCESSFUL\n");
            a=1;
            break;
        }
    }
    fclose(ptr);
    if(a!=1){
        printf("No username and password found\n");
    }
    return a;
}

void forgotPassword() {
    FILE *ptr,*temp;
    struct user s;
    char username[50],newPassword[50];
    int a= 0;
    int found = 0; 
    ptr=fopen("kist.txt","r");
    temp=fopen("temp.txt","w");
    if (ptr==NULL||temp==NULL) {
        printf("Not opening file\n");
        return;
    }
    printf("Enter username: ");
    scanf("%s",username);
    getchar();  
    while (fread(&s,sizeof(struct user),1,ptr)) {
        if (strcmp(s.username, username) == 0) {
            found = 1;
            printf("Enter new password: ");
            scanf("%s",newPassword);
            getchar();
            strcpy(s.password, newPassword);
        }
        fwrite(&s,sizeof(struct user),1,temp);
    }
    fclose(ptr);
    fclose(temp);
    ptr=fopen("kist.txt","w"); 
    temp=fopen("temp.txt","r"); 
    while (fread(&s,sizeof(struct user),1,temp)) {
        fwrite(&s,sizeof(struct user),1,ptr); // temp ko content kist ma saareko
    }
    fclose(ptr);
    fclose(temp);
    if(found) {
        printf("Password reset success\n");
    } else {
        printf("Username not found\n");
    }
}
