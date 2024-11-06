#include <stdio.h>
#include <windows.h>
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
};

struct abscence abscences[100];
int count = 0;
jour = 0, mois = 0 , anne = 0 , hours = 0;
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
    printf("Veuillez entrer le nom d'etudient : \n");
    scanf("%s", abscences[count].nom);
    printf("Veuillez entrer le prenom d'etudient : \n");
    scanf("%s", abscences[count].prenom);
    printf("Veuillez entrer le numero de telephone d'etudient : \n");
    scanf("%s", abscences[count].number);
    count++;
    loading();
    printf("Etudiant ajoute avec succes\n");
    Sleep(3000);
    system("cls");
}
void ajouterabs() {
    int option, newHours;
    char nom[25], prenom[25];
    printf("Veuillez entrer le nom d'etudient : ");
    scanf("%s", nom);
    printf("Veuillez entrer le prenom d'etudient : ");
    scanf("%s", prenom);

    for (int i = 0; i < count; i++) {
        if (strcmp(abscences[i].nom, nom) == 0 && strcmp(abscences[i].prenom, prenom) == 0) {
            printf("Voulez-vous ajouter ou supprimer des heures ? [ajouter : 1 | supprimer : 2] : ");
            scanf("%d", &option);
            if (option == 1) {
                printf("Veuillez entrer le jour de l'abscence d'etudient : \n");
                scanf("%d", &abscences[i].date.jour);
                printf("Veuillez entrer le mois de l'abscence d'etudient : \n");
                scanf("%d", &abscences[i].date.mois);
                printf("Veuillez entrer l'annee de l'abscence d'etudient : \n");
                scanf("%d", &abscences[i].date.anne);
                printf("Entrer le nombre d'heures l'etudient a rate : ");
                scanf("%d", &newHours);
                abscences[i].date.hours += newHours;
                loading();
                printf("Abscence ajoutee avec succes\n");
            } else if (option == 2) {
                printf("Entrer le nombre d'heures l'etudient a supprimer : ");
                scanf("%d", &newHours);
                if (abscences[i].date.hours >= newHours) {
                    abscences[i].date.hours -= newHours;
                    loading();
                    printf("Abscence supprimee avec succes\n");
                } else {
                    printf("Impossible de supprimer plus d'heures que ce qui est enregistre !\n");
                }
            } else {
                printf("Choix Invalide !\n");
            }
            return;
        }
    }
    printf("Le nom ou prenom est introuvable !\n");
    Sleep(3000);
    system("cls");
}
void modification() {
    char nom[25], prenom[25];
    printf("Veuillez entrer le nom d'etudient : ");
    scanf("%s", nom);
    printf("Veuillez entrer le prenom d'etudient : ");
    scanf("%s", prenom);

    for (int i = 0; i < count; i++) {
        if (strcmp(abscences[i].nom, nom) == 0 && strcmp(abscences[i].prenom, prenom) == 0) {
            printf("Veuillez entrer le nouveau nom d'etudient : \n");
            scanf("%s", abscences[i].nom);
            printf("Veuillez entrer le nouveau prenom d'etudient : \n");
            scanf("%s", abscences[i].prenom);
            printf("Veuillez entrer le nouveau numero de telephone d'etudient : \n");
            scanf("%s", abscences[i].number);
            loading();
            printf("Etudiant modifie avec succes\n");
            return; // Exit after modifying the student
        }
    }
    printf("Le nom ou prenom est introuvable !\n");
    Sleep(3000);
    system("cls");
}

void suppression() {
    char nom[25], prenom[25];
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
            return;
        }
    }
    printf("Le nom ou prenom est introuvable !\n");
    Sleep(3000);
    system("cls");
}
void afficher() {
    char nom[25], prenom[25];
    printf("Veuillez entrer le nom d'etudient : ");
    scanf("%s", nom);
    printf("Veuillez entrer le prenom d'etudient : ");
    scanf("%s", prenom);
    system("cls");
    for (int i = 0; i < count; i++) {
        if (strcmp(abscences[i].nom, nom) == 0 && strcmp(abscences[i].prenom, prenom) == 0) {
         printf(" ======================================Carte d'abscance=====================================\n");
            printf("|       Etudiant      |    Numero du telephone   |   Date d'abscence  |   Heures d'abscence |\n");
            printf("|-------------------------------------------------------------------------------------------|\n");
            printf("| %10s%10s| %-20s    | %02d/%02d/%04d         |       %02d heures      |\n",
                   abscences[i].nom, abscences[i].prenom, abscences[i].number,
                   abscences[i].date.jour, abscences[i].date.mois, abscences[i].date.anne,
                   abscences[i].date.hours);
            printf(" ========================================================================================\n");
            return;
        }
    }
    printf("Le nom ou prenom est introuvable !\n");
    Sleep(3000);
    system("cls");
}
int main (){
    int choice ;
    do {
        printf("\n 1. Ajouter un etudiant : \n");
        printf(" 2. ajouter l'abscence d'un etudiant : \n");
        printf(" 3. Afficher l'abscence d'un etudiant :\n");
        printf(" 4. Modifier les information d'un etudiant :\n");
        printf(" 5. Supprimer un etudiant :\n");
        printf(" 6. Quitter\n");
        printf("\n Entrez votre choix : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                ajouter();
                break;
            case 2:
                ajouterabs();
                break;
            case 3:
                afficher();
                break;
            case 4:
                modification();
                break;
            case 5:
                suppression();
                break;
            case 6:
                printf("Merci et au revoir!\n");
                return 0;
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
                Sleep(3000);
                system("cls");

}
    } while (choice != 6);
    return 0; }
