#include <stdio.h>
#include <windows.h>
#include <string.h>

#define MAX_ABSCENCES 100
#define PASSWORD_FILE "password.txt"
#define DATA_FILE "data.txt"

struct abscencedate {
    int jour;
    int mois;
    int anne;
    int hours;
};

struct abscence {

    char nom[25];
    char prenom[25];
    char number[25];
    struct abscencedate date;
    int ref;
};

struct abscence abscences[MAX_ABSCENCES];
int count = 0;
int ref = 1;
char passwd[50];
char user[50] = "admin";
char upass[50];
void loadata() {
    FILE *file = fopen(DATA_FILE, "r");
    if (file) {
        while (fscanf(file, "%s %s %s %d/%d/%d %d",
                      abscences[count].nom,
                      abscences[count].prenom,
                      abscences[count].number,
                      &abscences[count].date.jour,
                      &abscences[count].date.mois,
                      &abscences[count].date.anne,
                      &abscences[count].date.hours) == 7) {
            abscences[count].ref = ref++;
            count++;
            if (count >= MAX_ABSCENCES) {
                break;
            }
        }
        fclose(file);
    }
}
void loadpassword() {
    FILE *file = fopen(PASSWORD_FILE, "r");
    if (file) {
        fgets(passwd, sizeof(passwd), file);
         passwd[strcspn(passwd, "\n")] = 0;
        fclose(file);
    } else {
        strcpy(passwd, "admin123");
    }
}

void savepassword() {
    FILE *file = fopen(PASSWORD_FILE, "w");
    if (file) {
        fprintf(file, "%s\n", passwd);
        fclose(file);
    } else {
        printf("Error saving password to file.\n");
    }
}

void login() {
    printf("Entrer le user d'administration : ");
    scanf("%s", user);
    printf("Entrer le mot de pass d'administration : ");
    scanf("%s", upass);
    if (strcmp(upass, passwd) == 0 && strcmp(user, "admin") == 0) {
        printf("Login successful!\n");
        Sleep(1500);
        system("cls");
    } else {
        printf("Invalid password or username.\n");
        Sleep(1500);
        system("cls");
        login();
    }
}
void savedata() {
    FILE *file = fopen("data.txt", "w");
    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %s %s %d/%d/%d %d\n",
                abscences[i].nom,
                abscences[i].prenom,
                abscences[i].number,
                abscences[i].date.jour,
                abscences[i].date.mois,
                abscences[i].date.anne,
                abscences[i].date.hours);
    }
    fclose(file);
}
void logchange() {
    login();
    char newPassword[50];
    printf("Entrer le nouveau mot de pass : ");
    scanf("%s", newPassword);
    if (strcmp(newPassword, passwd) == 0) {
        printf("Le nouveau mot de pass doit etre different au ancien !\n");
        logchange() ;
    } else {
        strcpy(passwd, newPassword);
        savepassword();
        printf("Le mot de pass a etait change\n");
        Sleep(1500);
        system("cls");
    }
    return ;
}

void loading(){
            system("cls");
            printf("LOADING | ");
            Sleep(200);
            system("cls");
            printf("LOADING / ");
            Sleep(200);
            system("cls");
            printf("LOADING - ");
            Sleep(200);
            system("cls");
            printf("LOADING \\ ");
            Sleep(200);
            system("cls");}
void ajouter() {
    if (count >= 100) {
        printf("Limite de reservations atteinte!\n");
        return;
    }
    else{
        printf("Veuillez entrer le nom d'etudient : ");
        scanf("%s", abscences[count].nom);
        printf("Veuillez entrer le prenom d'etudient : ");
        scanf("%s", abscences[count].prenom);
        printf("Veuillez entrer le numero de telephone d'etudient : ");
        scanf("%s", abscences[count].number);
        abscences[count].date.hours = 0;
        abscences[count].ref = ref++;
        count++;
        loading();
        loading();
        savedata();
        printf("Etudiant ajoute avec succes\n");
        Sleep(3000);
        system("cls");
    }
}
void ajouterabs() {
    int option, newHours;
    char nom[25], prenom[25];
    if (count == 0) {
        printf("Aucun etudiant trouve , Vouillez entrer un !\n");
        Sleep(1500);
        system("cls");
        return;
    }
    else{
        printf("Veuillez entrer le nom d'etudient : ");
        scanf("%s", nom);
        printf("Veuillez entrer le prenom d'etudient : ");
        scanf("%s", prenom);

        for (int i = 0; i < count; i++) {
            if (strcmp(abscences[i].nom, nom) == 0 && strcmp(abscences[i].prenom, prenom) == 0) {
                printf("Voulez-vous ajouter ou supprimer des heures ? [ajouter : 1 | supprimer : 2] : ");
                scanf("%d", &option);
                if (option == 1) {
                    printf("Veuillez entrer le jour de l'abscence d'etudient : ");
                    scanf("%d", &abscences[i].date.jour);
                    printf("Veuillez entrer le mois de l'abscence d'etudient : ");
                    scanf("%d", &abscences[i].date.mois);
                    printf("Veuillez entrer l'annee de l'abscence d'etudient : ");
                    scanf("%d", &abscences[i].date.anne);
                    printf("Entrer le nombre d'heures l'etudient a rate : ");
                    scanf("%d", &newHours);
                    abscences[i].date.hours += newHours;
                    loading();
                    loading();
                    printf("Abscence ajoutee avec succes\n");
                    savedata();
                } else if (option == 2) {
                    printf("Entrer le nombre d'heures l'etudient a supprimer : ");
                    scanf("%d", &newHours);
                    if (abscences[i].date.hours >= newHours) {
                        abscences[i].date.hours -= newHours;
                        loading();
                        loading();
                        printf("Abscence supprimee avec succes\n");
                        savedata();
                    } else {
                        printf("Impossible de supprimer plus d'heures que ce qui est enregistre !\n");
                    }
                } else {
                    printf("Choix Invalide !\n");
                }
                return;}
        }
    }
    printf("Le nom ou prenom est introuvable !\n");
    Sleep(3000);
    system("cls");
}
void modification() {
    char nom[25], prenom[25];
    if (count == 0) {
        printf("Aucun etudiant trouve , Vouillez entrer un !\n");
        Sleep(1500);
        system("cls");
        return;
    }
    else{
        login();
        printf("Veuillez entrer le nom d'etudient : ");
        scanf("%s", nom);
        printf("Veuillez entrer le prenom d'etudient : ");
        scanf("%s", prenom);

        for (int i = 0; i < count; i++) {
            if (strcmp(abscences[i].nom, nom) == 0 && strcmp(abscences[i].prenom, prenom) == 0) {
                printf("Veuillez entrer le nouveau nom d'etudient : ");
                scanf("%s", abscences[i].nom);
                printf("Veuillez entrer le nouveau prenom d'etudient : ");
                scanf("%s", abscences[i].prenom);
                printf("Veuillez entrer le nouveau numero de telephone d'etudient : ");
                scanf("%s", abscences[i].number);
                loading();
                loading();
                printf("Etudiant modifie avec succes\n");
                return;
            }
            else {
                printf("Le nom ou prenom est introuvable !\n");
                Sleep(3000);
                system("cls");
}
}
}
}
void suppression() {
    char nom[25], prenom[25];
    if (count == 0) {
        printf("Aucun etudiant trouve , Vouillez entrer un !\n");
        Sleep(1500);
        system("cls");
        return;
    }
    else{
        login();
        printf("Veuillez entrer le nom d'etudient : ");
        scanf("%s", nom);
        printf("Veuillez entrer le prenom d'etudient : ");
        scanf("%s", prenom);

        for (int i = 0; i < count; i++) {
            if (strcmp(abscences[i].nom, nom) == 0 && strcmp(abscences[i].prenom, prenom) == 0) {
                for (int j = i; j < count - 1; j++) {
                    abscences[j] = abscences[j + 1];
                }
                abscences[count].ref = ref--;
                count--;
                loading();
                loading();
                printf("Etudiant supprime avec succes\n");
                savedata();
                return;
            }
        }
        printf("Le nom ou prenom est introuvable !\n");
        Sleep(3000);
        system("cls");
        }
}
void affichertous() {
    char opttion[10];
        printf(" ================================================Carte d'abscance===============================================\n");
            printf("|       Ref         |       Etudiant      |    Numero du telephone  |   Date d'abscence  |   Heures d'abscence  |\n");
            for (int i = 0; i < count; i++) {
            printf("|---------------------------------------------------------------------------------------------------------------|\n");
            printf("|     %10d    | %10s%10s| %-20s    |     %02d/%02d/%04d     |       %02d heures      |\n",
                    abscences[i].ref,abscences[i].nom, abscences[i].prenom, abscences[i].number,
                   abscences[i].date.jour, abscences[i].date.mois, abscences[i].date.anne,
                   abscences[i].date.hours);
                   }
            printf(" ===============================================================================================================\n");
            printf("entrer Q pour quitter :");
            scanf("%s" , opttion);
             if (strcmp(opttion, "q") == 0 || strcmp(opttion, "Q") == 0) {
                system("cls");
                return;
            } else {
                printf("Choix Invalide !\n");
                Sleep(1500);
                system("cls");
                affichertous ();
        }
}
void afficherseul() {
    char nom[25], prenom[25] , opttion[10];
        printf("Veuillez entrer le nom d'etudient : ");
        scanf("%s", nom);
        printf("Veuillez entrer le prenom d'etudient : ");
        scanf("%s", prenom);
        system("cls");
        for (int i = 0; i < count; i++) {
            if (strcmp(abscences[i].nom, nom) == 0 && strcmp(abscences[i].prenom, prenom) == 0) {
             printf(" ================================================Carte d'abscance===============================================\n");
                printf("|       Ref         |       Etudiant      |    Numero du telephone   |   Date d'abscence  |   Heures d'abscence |\n");
                printf("|---------------------------------------------------------------------------------------------------------------|\n");
                printf("|     %10d    | %10s%10s| %-20s    |     %02d/%02d/%04d     |       %02d heures      |\n",
                        abscences[i].ref,abscences[i].nom, abscences[i].prenom, abscences[i].number,
                       abscences[i].date.jour, abscences[i].date.mois, abscences[i].date.anne,
                       abscences[i].date.hours);
                printf(" ===============================================================================================================\n");
            }

            else{
                printf("Le nom ou prenom est introuvable !\n");
                Sleep(3000);
                system("cls");
            }
        printf("entrer Q pour quitter :");
        scanf("%s" , opttion);
            if (strcmp(opttion, "q") == 0 || strcmp(opttion, "Q") == 0) {
                system("cls");
                return;
            }
            else {
                printf("Choix Invalide !\n");
                Sleep(1500);
                system("cls");
                affichertous ();
}}}
void afficher(){
    int option;
    if (count == 0) {
        printf("Aucun etudiant trouve , Vouillez entrer un !\n");
        Sleep(1500);
        system("cls");
        return;
    }
    else{
        printf ("  1 - rechere d'un etudiant      | 2 - lister tout les etudiants : ");
        scanf("%d" , &option);
        if(option == 1 ){
            system("cls");
            afficherseul();
        }
        else if (option == 2){
            system("cls");
            affichertous();
        }
        else{
            printf("Choix Invalid");
        }
}}
int main (){
    int choice ;
    loadpassword();
    loadata();
    do {
        printf("       ====================ABSENCE===================\n");
        printf("      |  1. Ajouter l'abscence d'un etudiant :       |\n");
        printf("      |  2. Afficher l'abscence d'un etudiant :      |\n");
        printf("      |  3. Ajouter un etudiant :                    |\n");
        printf("      |  4. Modifier les information d'un etudiant : |\n");
        printf("      |  5. Supprimer un etudiant :                  |\n");
        printf("      |  6. Changer le mot de pass d'administration  |\n");
        printf("      |  7. Quitter                                  |\n");
        printf("       ==============================================\n\n");
        printf(" Entrez votre choix : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                ajouterabs();
                break;
            case 2:
                afficher();
                break;
            case 3:
                ajouter();
                break;
            case 4:
                modification();
                break;
            case 5:
                suppression();
                break;
            case 6:
                logchange();
                break;
            case 7:
                printf("Merci et au revoir!\n");
                return 0;
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
                Sleep(3000);
                system("cls");

}
    } while (choice != 6);
    return 0; }
