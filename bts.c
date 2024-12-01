#include <stdio.h>
#include <windows.h>
#include <string.h>

#define MAX_ABSCENCES 100
#define PASSWORD_FILE "password.txt"
#define DATA_FILE "data.txt"

struct matiere {
    float fin, linux[4], dev[4], math[4], win[4], ar[4], fr[4], eeje[4], com[4], eng[4], result, somme, module1, module2, module3;
};

struct abscencedate {
    int jour;
    int mois;
    int anne;
    int hours;
};

struct EtudiantDates {
    int day;
    int month;
    int year;
};

struct Etudiant {
    int ref;
    char nom[25];
    char prenom[25];
    char number[25];
    char adress[80];
    struct abscencedate date;
    struct EtudiantDates birthDate;
    struct matiere grades;
};

struct matiere mat;
struct Etudiant abscences[MAX_ABSCENCES];
struct EtudiantDates daten;
int count = 0;
int ref = 1;
char passwd[50];
char user[50] = "admin";
char upass[50];

void loadata();
void loadpassword();
void savepassword();
void login();
void savedata();
void logchange();
void loading();
void ajouter();
void ajouterabs();
void modification();
void suppression();
void affichertous();
void afficherseul();
void abse();
void ajoutnotes();
void noteaffiche();
void afficheetude(char nom[], char prenom[], int *found);
void affichenote();

void loadata() {
    FILE *file = fopen(DATA_FILE, "r");
    if (file) {
        while (fscanf(file, "%s %s %s %d/%d/%d %d/%d/%d %d",
                      abscences[count].nom,
                      abscences[count].prenom,
                      abscences[count].number,
                      &abscences[count].birthDate.day,
                      &abscences[count].birthDate.month,
                      &abscences[count].birthDate.year,
                      &abscences[count].date.jour,
                      &abscences[count].date.mois,
                      &abscences[count].date.anne,
                      &abscences[count].date.hours) == 10){


            for (int j = 0; j < 4; j++) {
                fscanf(file, "%f", &abscences[count].grades.linux[j]);
            }
            for (int j = 0; j < 4; j++) {
                fscanf(file, "%f", &abscences[count].grades.dev[j]);
            }
            for (int j = 0; j < 4; j++) {
                fscanf(file, "%f", &abscences[count].grades.math[j]);
            }
            for (int j = 0; j < 4; j++) {
                fscanf(file, "%f", &abscences[count].grades.win[j]);
            }
            for (int j = 0; j < 4; j++) {
                fscanf(file, "%f", &abscences[count].grades.ar[j]);
            }
            for (int j = 0; j < 4; j++) {
                fscanf(file, "%f", &abscences[count].grades.fr[j]);
            }
            for (int j = 0; j < 4; j++) {
                fscanf(file, "%f", &abscences[count].grades.eeje[j]);
            }
            for (int j = 0; j < 4; j++) {
                fscanf(file, "%f", &abscences[count].grades.com[j]);
            }
            for (int j = 0; j < 4; j++) {
                fscanf(file, "%f", &abscences[count].grades.eng[j]);
            }

            abscences[count].ref = ref++;
            count++;

            if (count >= MAX_ABSCENCES) {
                break;
            }
        }
        fclose(file);
    } else {
        printf("Error opening file for reading.\n");
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
    while (1) {
        printf("Entrer le user d'administration : ");
        scanf("%s", user);
        printf("Entrer le mot de pass d'administration : ");
        scanf("%s", upass);
        if (strcmp(upass, passwd) == 0 && strcmp(user, "admin") == 0) {
            printf("Login successful!\n");
            Sleep(1500);
            system("cls");
            break;
        } else {
            printf("Invalid password or username.\n");
            Sleep(1500);
            system("cls");
        }
    }
}

void savedata() {
    FILE *file = fopen(DATA_FILE, "w");
    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %s %s %d/%d/%d %d/%d/%d %d",
                abscences[i].nom,
                abscences[i].prenom,
                abscences[i].number,
                abscences[i].birthDate.day,
                abscences[i].birthDate.month,
                abscences[i].birthDate.year,
                abscences[i].date.jour,
                abscences[i].date.mois,
                abscences[i].date.anne,
                abscences[i].date.hours);

        for (int j = 0; j < 4; j++) {
            fprintf(file, " %.2f", abscences[i].grades.linux[j]);
        }
        for (int j = 0; j < 4; j++) {
            fprintf(file, " %.2f", abscences[i].grades.dev[j]);
        }
        for (int j = 0; j < 4; j++) {
            fprintf(file, " %.2f", abscences [i].grades.math[j]);
        }
        for (int j = 0; j < 4; j++) {
            fprintf(file, " %.2f", abscences[i].grades.win[j]);
        }
        for (int j = 0; j < 4; j++) {
            fprintf(file, " %.2f", abscences[i].grades.ar[j]);
        }
        for (int j = 0; j < 4; j++) {
            fprintf(file, " %.2f", abscences[i].grades.fr[j]);
        }
        for (int j = 0; j < 4; j++) {
            fprintf(file, " %.2f", abscences[i].grades.eeje[j]);
        }
        for (int j = 0; j < 4; j++) {
            fprintf(file, " %.2f", abscences[i].grades.com[j]);
        }
        for (int j = 0; j < 4; j++) {
            fprintf(file, " %.2f", abscences[i].grades.eng[j]);
        }
        fprintf(file, "\n");
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
        logchange();
    } else {
        strcpy(passwd, newPassword);
        savepassword();
        printf("Le mot de pass a etait change\n");
        Sleep(1500);
        system("cls");
    }
}

void loading() {
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
    system("cls");
}

void ajouter() {
    if (count >= MAX_ABSCENCES) {
        printf("Limite de reservations atteinte!\n");
        return;
    }

    printf("Veuillez entrer le nom d'etudient : ");
    scanf("%24s", abscences[count].nom);

    printf("Veuillez entrer le prenom d'etudient : ");
    scanf("%24s", abscences[count].prenom);

    printf("Veuillez entrer le numero de telephone d'etudient : ");
    scanf("%24s", abscences[count].number);
    printf("entrer l'anne de naissance d'etudient : ");
    scanf("%d", &abscences[count].birthDate.year);
    printf("entrer le mois de naissance d'etudient : ");
    scanf("%d", &abscences[count].birthDate.month);
    printf("entrer le jour de naissance d'etudient : ");
    scanf("%d", &abscences[count].birthDate.day);

    abscences[count].date.hours = 0;
    abscences[count].ref = ref++;

    count++;
    loading();
    savedata();
    printf("Etudiant ajoute avec succes\n");
    Sleep(3000);
    system("cls");
}

void ajouterabs() {
    int option, newHours;
    char nom[25], prenom[25];
    if (count == 0) {
        printf("Aucun etudiant trouve , Vouillez entrer un !\n");
        Sleep(1500);
        system("cls");
        return;
    } else {
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
                    printf("Abscence ajoutee avec succes\n");
                    savedata();
                } else if (option == 2) {
                    printf("Entrer le nombre d'heures l'etudient a supprimer : ");
                    scanf("%d", &newHours);
                    if (abscences[i].date.hours >= newHours) {
                        abscences[i].date.hours -= newHours;
                        loading();
                        printf("Abscence supprimee avec succes\n");
                        savedata();
                    } else {
                        printf("Impossible de supprimer plus d'heures que ce qui est enregistre !\n");
                    }
                } else {
                    printf("Choix Invalide !\n");
                }
                return;
            }
        }
    }
    printf("Le nom ou prenom est introuvable !\n");
    Sleep(3000);
    system("cls");
}

void modification() {
    char nom[25], prenom[25] , nnom[25] ,nprenom[25], nnum[25];
    if (count == 0) {
        printf("Aucun etudiant trouve , Vouillez entrer un !\n");
        Sleep(1500);
        system("cls");
        return;
    } else {
        login();
        printf("Veuillez entrer le nom d'etudient : ");
        scanf("%s", nom);
        printf("Veuillez entrer le prenom d'etudient : ");
        scanf("%s", prenom);

        for (int i = 0; i < count; i++) {
            if (strcmp(abscences[i].nom, nom) == 0 && strcmp(abscences[i].prenom, prenom) == 0) {
                 printf("Veuillez entrer le nouveau nom d'etudient : ");
            scanf("%s", nnom);
            strcpy(abscences[i].nom, nnom);
            printf("Veuillez entrer le nouveau prenom d'etudient : ");
            scanf("%s", nprenom);
            strcpy(abscences[i].prenom, nprenom);
            printf("Veuillez entrer le nouveau numero de telephone d'etudient : ");
            scanf("%s", nnum);
            strcpy(abscences[i].number, nnum);
            printf("entrer l'anne de naissance d'etudient : ");
            scanf("%d", &abscences[i].birthDate.year);
            printf("entrer le mois de naissance d'etudient : ");
            scanf("%d", &abscences[i].birthDate.month);
            printf("entrer le jour de naissance d'etudient : ");
            scanf("%d", &abscences[i].birthDate.day);
                loading();
                savedata();
                printf("Etudiant modifie avec succes\n");
                return;
            }
        }
        printf("Le nom ou prenom est introuvable !\n");
        Sleep(3000);
        system("cls");
    }
}

void suppression() {
    char nom[25], prenom[25];
    if (count == 0) {
        printf("Aucun etudiant trouve , Vouillez entrer un !\n");
        Sleep(1500);
        system("cls");
        return;
    } else {
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
                count--;
                loading();
                printf("Etudiant supprime avec succes\n");
                savedata();
                Sleep(1500);
                system("cls");
                return;
            }
        }
        printf("Le nom ou prenom est introuvable !\n");
        Sleep(3000);
        system("cls");
    }
}

void affichertous() {
    char opttion[5];
    printf(" ================================================Carte d'abscance===============================================\n");
    printf("|       Ref         |       Etudiant      |    Numero du telephone  |   Date d'abscence  |   Heures d'abscence  |\n");
    for (int i = 0; i < count; i++) {
        printf("|---------------------------------------------------------------------------------------------------------------|\n");
        printf("|     %10d    | %10s %10s | %-20s    |     %02d/%02d/%04d     |       %02d heures    |\n",
               abscences[i].ref, abscences[i].nom, abscences[i].prenom, abscences[i].number,
               abscences[i].date.jour, abscences[i].date.mois, abscences[i].date.anne,
               abscences[i].date.hours);
    }
    printf(" ===============================================================================================================\n\n");
    printf("Entrer q pour revenir au menu : ");
    scanf("%s", opttion);

    while (strcmp(opttion, "q") != 0 && strcmp(opttion, "Q") != 0) {
        printf("Choix invalide !\n");
        printf("Entrer q pour revenir au menu : ");
        scanf("%s", opttion);
    }
    system("cls");
    return ;
}


void afficherseul() {
    char nom[25], prenom[25] ,opttion[5];
    int found = 0;
    printf(" Veuillez entrer le nom d'etudient : ");
    scanf("%s", nom);
    printf("Veuillez entrer le prenom d'etudient : ");
    scanf("%s", prenom);
    system("cls");
    for (int i = 0; i < count; i++) {
        if (strcmp(abscences[i].nom, nom) == 0 && strcmp(abscences[i].prenom, prenom) == 0) {
            found = 1;
            printf(" ================================================Carte d'abscance===============================================\n");
            printf("|       Ref         |       Etudiant      |    Numero du telephone   |   Date d'abscence  |   Heures d'abscence |\n");
            printf("|---------------------------------------------------------------------------------------------------------------|\n");
            printf("|     %10d    | %10s %10s | %-20s    |     %02d/%02d/%04d     |       %02d heures      |\n",
                   abscences[i].ref, abscences[i].nom, abscences[i].prenom, abscences[i].number,
                   abscences[i].date.jour, abscences[i].date.mois, abscences[i].date.anne,
                   abscences[i].date.hours);
            printf(" ===============================================================================================================\n\n");
           printf("Entrer q pour revenir au menu : ");
    scanf("%s", opttion);

    while (strcmp(opttion, "q") != 0 && strcmp(opttion, "Q") != 0) {
        printf("Choix invalide !\n");
        printf("Entrer q pour revenir au menu : ");
        scanf("%s", opttion);
    }

    if (!found) {
        printf("Le nom ou prénom est introuvable !\n");
        Sleep(3000);
        system("cls");
    }
    system("cls");
    return ;
}
}
}
void abse() {
    int option;
    if (count == 0) {
        printf("Aucun etudiant trouve , Vouillez entrer un !\n");
        Sleep(1500);
        system("cls");
        return;
    } else {
        printf("  1 - recherche d'un etudiant      | 2 - lister tout les etudiants : ");
        scanf("%d", &option);
        if (option == 1) {
            system("cls");
            afficherseul();
        } else if (option == 2) {
            system("cls");
            affichertous();
        } else {
            printf("Choix Invalide\n");
        }
    }
}

void ajoutnotes() {
    char nom[25], prenom[25];
    if (count == 0) {
        printf("Aucun etudiant trouve , Vouillez entrer un !\n");
        Sleep(1500);
        system("cls");
        return;
    } else {
        printf("Veuillez entrer le nom d'etudient : ");
        scanf("%s", nom);
        printf("Veuillez entrer le prenom d'etudient : ");
        scanf("%s", prenom);

        for (int i = 0; i < count; i++) {
            if (strcmp(abscences[i].nom, nom) == 0 && strcmp(abscences[i].prenom, prenom) == 0) {
                printf("Entrer les notes pour %s %s:\n", abscences[i].nom, abscences[i].prenom);

                printf("Entrer la premier note de Linux : ");
                scanf("%f", &abscences[i].grades.linux[0]);
                printf("Entrer la deuxieme note de Linux : ");
                scanf("%f", &abscences[i].grades.linux[1]);
                printf("Entrer la troisieme note de Linux : ");
                scanf("%f", &abscences[i].grades.linux[2]);
                printf("Entrer la quatrieme note de Linux : ");
                scanf("%f", &abscences[i].grades.linux[3]);
                printf("Entrer la premier note de developpement d'application : ");
                scanf("%f", &abscences[i].grades.dev[0]);
                printf("Entrer la deuxieme note de developpement d'application : ");
                scanf("%f", &abscences[i].grades.dev[1]);
                printf("Entrer la troisieme note de developpement d'application : ");
                scanf("%f", &abscences[i].grades.dev[2]);
                printf("Entrer la quatrieme note de developpement d'application : ");
                scanf("%f", &abscences[i].grades.dev[3]);
                printf("Entrer la premier note de math : ");
                scanf("%f", &abscences[i].grades.math[0]);
                printf("Entrer la deuxieme note de math : ");
                scanf("%f", &abscences[i].grades.math[1]);
                printf("Entrer la troisieme note de math : ");
                scanf("%f", &abscences[i].grades.math[2]);
                printf("Entrer la quatrieme note de math : ");
                scanf("%f", &abscences[i].grades.math[3]);
                printf("Entrer la premier note de windows : ");
                scanf("%f", &abscences[i].grades.win[0]);
                printf("Entrer la deuxieme note de windows : ");
                scanf("%f", &abscences[i].grades.win[1]);
                printf("Entrer la troisieme note de windows : ");
                scanf("%f", &abscences[i].grades.win[2]);
                printf("Entrer la quatrieme note de windows : ");
                scanf("%f", &abscences[i].grades.win[3]);
                printf("Entrer la premier note de arabe : ");
                scanf("%f", &abscences[i].grades.ar[0]);
                printf("Entrer la deuxieme note de arabe: ");
                scanf("%f", &abscences[i].grades.ar[1]);
                printf("Entrer la troisieme note de arabe : ");
                scanf("%f", &abscences[i].grades.ar[2]);
                printf("Entrer la quatrieme note de arabe : ");
                scanf("%f", &abscences[i].grades.ar[3]);
                printf("Entrer la premier note de francais : ");
                scanf("%f", &abscences[i].grades.fr[0]);
                printf("Entrer la deuxieme note de francais : ");
                scanf("%f", &abscences[i].grades.fr[1]);
                printf("Entrer la troisieme note de francais : ");
                scanf("%f", &abscences[i].grades.fr[2]);
                printf("Entrer la quatrieme note de francais : ");
                scanf("%f", &abscences[i].grades.fr[3]);
                printf("Entrer la premier note de eeje : ");
                scanf("%f", &abscences[i].grades.eeje[0]);
                printf("Entrer la deuxieme note de eeje : ");
                scanf("%f", &abscences[i].grades.eeje[1]);
                printf("Entrer la troisieme note de eeje : ");
                scanf("%f", &abscences[i].grades.eeje[2]);
                printf("Entrer la quatrieme note de eeje : ");
                scanf("%f", &abscences[i].grades.eeje[3]);
                printf("Entrer la premier note de com : ");
                scanf("%f", &abscences[i].grades.com[0]);
                printf("Entrer la deuxieme note de com : ");
                scanf("%f", &abscences[i].grades.com[1]);
                printf("Entrer la troisieme note de com : ");
                scanf("%f", &abscences[i].grades.com[2]);
                printf("Entrer la quatrieme note de com : ");
                scanf("%f", &abscences[i].grades.com[3]);
                printf("Entrer la premier note de anglais : ");
                scanf("%f", &abscences[i].grades.eng[0]);
                printf("Entrer la deuxieme note de anglais : ");
                scanf("%f", &abscences[i].grades.eng[1]);
                printf("Entrer la troisieme note de anglais : ");
                scanf("%f", &abscences[i].grades.eng[2]);
                printf("Entrer la quatrieme note de anglais : ");
                scanf("%f", &abscences[i].grades.eng[3]);
                loading();
                savedata();
                printf("Les notes on été enregistrer ");
                system("cls");
                return;
            }
        }
        printf("Le nom ou prenom est introuvable !\n");
        Sleep(3000);
        system("cls");
    }
}
void affichenote() {
    int found = 0;
    char nom[25],prenom[25] , opttion[5];
    if (count == 0) {
        printf("Aucun etudiant trouve , Vouillez entrer un !\n");
        Sleep(1500);
        system("cls");
        return;
    } else {
        printf("Veuillez entrer le nom d'etudient : ");
        scanf("%s", nom);
        printf("Veuillez entrer le prenom d'etudient : ");
        scanf("%s", prenom);
        system("cls");
    for (int i = 0; i < count; i++) {
        if (strcmp(abscences[i].nom, nom) == 0 && strcmp(abscences[i].prenom, prenom) == 0) {
            found = 1;
            printf(" ============================ Notes de l'etudiant ==============================\n");
            printf("| Nom: %s | Prenom: %s | Date de Naissance : %02d/%02d/%02d                   |\n", abscences[i].nom, abscences[i].prenom , abscences[i].birthDate.day,abscences[i].birthDate.month,abscences[i].birthDate.year);
            printf("-----------------------------------------------------------------------------\n");
            printf("| Matiere                    | 1er Exam | 2eme Exam | 3eme Exam | 4eme Exam     |\n");
            printf("---------------------------------------------------------------------------------\n");
            printf("| LINUX                      | %.2f     | %.2f     | %.2f     | %.2f        |\n",abscences[i].grades.linux[0], abscences[i].grades.linux[1], abscences[i].grades.linux[2], abscences[i].grades.linux[3]);
            printf("| DEVELOPPEMENT D'APPLICATION| %.2f     | %.2f     | %.2f     | %.2f        |\n",abscences[i].grades.dev[0], abscences[i].grades.dev[1],abscences[i].grades.dev[2], abscences[i].grades.dev[3]);
            printf("| MATH                       | %.2f     | %.2f     | %.2f     | %.2f        |\n",abscences[i].grades.math[0], abscences[i].grades.math[1],abscences[i].grades.math[2], abscences[i].grades.math[3]);
            printf("| WINDOWS                    | %.2f     | %.2f     | %.2f     | %.2f        |\n",abscences[i].grades.win[0], abscences[i].grades.win[1],abscences[i].grades.win[2], abscences[i].grades.win[3]);
            printf("| ARABE                      | %.2f     | %.2f     | %.2f     | %.2f        |\n",abscences[i].grades.ar[0], abscences[i].grades.ar[1],abscences[i].grades.ar[2], abscences[i].grades.ar[3]);
            printf("| FRANCAIS                   | %.2f     | %.2f     | %.2f     | %.2f        |\n",abscences[i].grades.fr[0], abscences[i].grades.fr[1],abscences[i].grades.fr[2], abscences[i].grades.fr[3]);
            printf("| EEJE                       | %.2f     | %.2f     | %.2f     | %.2f        |\n",abscences[i].grades.eeje[0], abscences[i].grades.eeje[1],abscences[i].grades.eeje[2], abscences[i].grades.eeje[3]);
            printf("| COMMUNICATION              | %.2f     | %.2f     | %.2f     | %.2f        |\n",abscences[i].grades.com[0], abscences[i].grades.com[1],abscences[i].grades.com[2], abscences[i].grades.com[3]);
            printf("| ANGLAIS                    | %.2f     | %.2f     | %.2f     | %.2f        |\n",abscences[i].grades.eng[0], abscences[i].grades.eng[1],abscences[i].grades.eng[2], abscences[i].grades.eng[3]);
            printf(" -------------------------------------------------------------------------------\n\n");

    printf("Entrer q pour revenir au menu : ");
    scanf("%s", opttion);

    while (strcmp(opttion, "q") != 0 && strcmp(opttion, "Q") != 0) {
        printf("Choix invalide !\n");
        printf("Entrer q pour revenir au menu : ");
        scanf("%s", opttion);
    }

    if (!found) {
        printf("Le nom ou prénom est introuvable !\n");
        Sleep(3000);
        system("cls");
    }
    system("cls");
    return ;
}
}}}
int main() {
    int choice;
    char opttion[5];
    loadpassword();
    count = 0;
    loadata();
    do {
        printf("       ================ADMINISTRATION================\n");
        printf("      |  1. Afficher les notes d'un etudiant :       |\n");
        printf("      |  2. Afficher l'abscence d'un etudiant :      |\n");
        printf("      |  3. Ajouter les notes d'un etudiant :        |\n");
        printf("      |  4. Ajouter un etudiant :                    |\n");
        printf("      |  5. Modiffier l'abscence d'un etudiant :     |\n");
        printf("      |  6. Modifier les information d'un etudient : |\n");
        printf("      |  7. Supprimer un etudiant :                  |\n");
        printf("      |  8. Changer le mot de pass d'administration  |\n");
        printf("      |  9. Quitter                                  |\n");
        printf("       ==============================================\n\n");
        printf(" Entrez votre choix : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                system("cls");
                affichenote();
                break;
            case 2:
                system("cls");
                abse();
                break;
            case 3:
                system("cls");
                ajoutnotes();
                break;
            case 4:
                system("cls");
                ajouter();
                break;
            case 5:
                system("cls");
                ajouterabs();
                break;
            case 6:
                system("cls");
                modification();
                break;
            case 7:
                system("cls");
                suppression();
                break;
            case 8:
                system("cls");
                logchange();
                break;
            case 9:
                printf("Merci et au revoir!\n");
                return 0;
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
                Sleep(3000);
                system("cls");
        }
    } while (choice != 9);
}
