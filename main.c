/*
* PROGRAMME DE GESTION D'UN ENSEMBLE D'ATHLETES
* Le 30 Juin 2021
* Mamadou Saliou Diallo & Mamadou Moustapha Diallo
*/


/*                   DIRECTIVES DE PREPROCESSEUR                */
/****************************************************************/
#define NMAX 50

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/*           CONSTANTES ET DEFINITION DE LA STRUCTURE           */
/****************************************************************/
typedef struct
{
    int id, age;
    char nom[16], prenom[31];
    float record;
} Athlete;

/*                   PROTOTYPES DES FONCTIONS                   */
/****************************************************************/

// préliminaires
float calculRecordMoyen(Athlete *a, int nbElem);
float calculerRecordMax(Athlete *a, int nbElem);
int estInscritAthlete(Athlete *a, int nbElem , int id);

// fonctionnalités principales
void ajouter(Athlete *a, int *nbElem);
void afficher(Athlete *a, int nbElem);
void afficher_participants(Athlete *a, int nbElem);
void trier_record(Athlete *a, int nbElem);
void afficher_record_max(Athlete *a, int nbElem);
void afficher_record_moyen(Athlete *a, int nbElem);

// sauvegarde
void save(Athlete *a, int nbElem);
void update(Athlete *a, int *nbElem);


/*                      PROGRAMME PRINCIPAL                     */
/****************************************************************/

int main(int argc, char *arg[]){
    Athlete a[NMAX];
    int choix;
    int choixValide = 0;
    int nbElem = 0;

    update(a, &nbElem);

    do
    {
        puts("Menu principal\n");

        puts(" 1. Ajout d'un nouveau athlete");
        puts(" 2. Affichage de tous les athletes");
        puts(" 3. Affichage des athletes par ordre croissant des records");
        puts(" 4. Athlete pouvant participer a la competition");
        puts(" 5. Record moyen de tous les athletes");
        puts(" 6. Le plus grand record");
       
        puts(" 0. Quitter");

        choix = -100;
        
        printf("\n     Votre choix : ");
        scanf("%d", &choix);
        fflush(stdin);

        choixValide = choix >= 0 && choix <= 6;


        if(!choixValide)
        {
            system("CLS");
            puts("Choix invalide, reprenez SVP !\n");
        }
        else if(choixValide && choix != 0)
        {
            system("CLS");

            switch(choix)
            {
            case 1 : ajouter(a, &nbElem); break;
            case 2 : afficher(a, nbElem); break;
            case 3 : trier_record(a, nbElem); break;
            case 4 : afficher_participants(a, nbElem); break;
            case 5 : afficher_record_moyen(a, nbElem); break;
            case 6 : afficher_record_max(a, nbElem); break;
            }

            printf("\n");
            system("PAUSE");
            system("CLS");
        }
    }
    while(choix != 0);

    puts("\nVous avez choisi de quitter ! Merci !\n");

    save(a, nbElem);
    return 0;
}
/****************************************************************/



/*                   DEFINITION DES FONCTIONS                   */
/****************************************************************/


/*FONCTIONS PRELIMINAIRES*/


int comparateur(const void* a, const void* b){
    return ((Athlete*)a)->record - ((Athlete*)b)->record;
}

int estInscritAthlete(Athlete *a, int nbElem, int id){
    int ind = -1;
    // code

    if(nbElem > 0)
    {
        int i = 0;

        while(i < nbElem && ind == -1)
        {
            if(id == a[i].id)
                ind = i;

            i++;
        }
    }

    return ind;
}

float calculRecordMoyen(Athlete *a, int nbElem){
    float moyenne = 0;

    int i = 0;
    for (i = 0; i < nbElem; i++){
        moyenne += a[i].record;
    }

    return moyenne / nbElem;
}

float calculerRecordMax(Athlete *a, int nbElem){
    float max = 0;

    int i = 0;
    for(; i < nbElem; i++){
        if(a[i].record > max)
            max = a[i].record;
    }

    return max;
}

/*FONCTIONS DU MENU*/

void afficher_record_moyen(Athlete *a, int nbElem){
    puts("Record moyen de tous les athletes");
    puts("------------------------------------------------------------");
    
    if(nbElem != 0){
        printf(" : %.2f\n", calculRecordMoyen(a, nbElem));
    }
    else{
        puts("Aucun athlete dans la liste !");
    }
}

void ajouter(Athlete *a, int *nbElem){
    if(*nbElem == NMAX)
        puts("Ajout impossible, liste pleine !");
    else
    {
        puts("Entrez les informations de l'athlete\n");

        do{
            printf("Entrez l'identifiant : ");
            scanf("%d", &a[*nbElem].id);
            fflush(stdin);

            if(estInscritAthlete(a, *nbElem, a[*nbElem].id) != -1){
                puts("L'identifiant est deja utilise ! choisir un autre !\n");
            }
            else{
                break;
            }
        }
        while(1);

        printf("Entrez le prenom : ");
        scanf("%30s", a[*nbElem].prenom);
        fflush(stdin);

        printf("Entrez le nom : ");
        scanf("%15s", a[*nbElem].nom);
        fflush(stdin);
        


        printf("Entrez l'age : ");
        scanf("%d", &a[*nbElem].age);
        fflush(stdin);

        do
        {
            printf("Entrez le record personnel : ");
            scanf("%f", &a[*nbElem].record);
            fflush(stdin);
        }
        while(a[*nbElem].record <= 0);

        //puts("Calcul du record moyen");
        //a[*nbElem].recordM = calculRecordMoyen();

        (*nbElem)++;
    }
}

void afficher(Athlete *a, int nbElem){
    puts("Liste des athletes");
    puts("------------------------------------------------------------");
    if(nbElem == 0)
        puts("Liste vide !");
    else
    {
        int i;
        puts("ID    Prenom                Nom         Age    Record\n");
        for(i = 0; i < nbElem; i++)
        {
            printf("%-4d  %-20s  %-10s  %-5d  %.2f\n",
                   a[i].id,
                   a[i].prenom,
                   a[i].nom,
                   a[i].age,
                   a[i].record
            );

        }
    }
}

void trier_record(Athlete *a, int nbElem){
    qsort(a, nbElem, sizeof(Athlete), comparateur);

    puts("Tri effectue avec succes ...");
}

void afficher_participants(Athlete *a, int nbElem){
    int i = 0;
    float recordMoyen = calculRecordMoyen(a, nbElem);

    puts("Liste des athletes qui vont participer a la competition");
    printf("Record Moyen : %.2f\n", recordMoyen);
    puts("------------------------------------------------------------");

    if(nbElem == 0)
        puts("Liste vide !");
    else
    {
        int i;
        puts("ID    Prenom                Nom         Age    Record\n");
        for(i = 0; i < nbElem; i++)
        {
            if(a[i].record >= recordMoyen) continue;
            printf("%-4d  %-20s  %-10s  %-5d  %.2f\n",
                   a[i].id,
                   a[i].prenom,
                   a[i].nom,
                   a[i].age,
                   a[i].record
            );

        }
    }
}

void afficher_record_max(Athlete *a, int nbElem){
    puts("Record maximal de tous les athletes");
    puts("------------------------------------------------------------");
    
    if(nbElem != 0){
        printf(" : %.2f\n", calculerRecordMax(a, nbElem));
    }
    else{
        puts("Aucun athlete dans la liste !");
    }
}


/*SAUVEGARDE*/
/*****************************************************/

void save(Athlete *a, int nbElem)
{
    FILE *f;
    if(nbElem != 0)
    {
        f = fopen("database", "wb");
        if(f != NULL )
        {
            fwrite((int*) &nbElem, sizeof(int), 1, f);
            fwrite((Athlete*)a, sizeof(Athlete), nbElem, f);
        }
        fclose(f);
    }
}

void update(Athlete *a, int *nbElem)
{
    FILE *f = fopen("database", "rb");
    if(f != NULL)
    {
        fread((int*)nbElem, sizeof(int), 1, f);
        fread((Athlete *)a, sizeof(Athlete), *nbElem, f);
    }
    fclose(f);
}
