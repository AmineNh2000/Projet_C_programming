#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Employe
{
    int code;
    char nom[50];
    char prenom[50];
    char dateNaiss[50];
    char titrePost[50];
    float salaire;
    struct Employe *Next;
} Employe;

typedef struct List
{
    Employe * head ;
} List;

List * initList()
{
    List * liste = malloc(sizeof(List));
    liste->head=NULL;
    return liste;
};
FILE * pf ;

//Pour Ajoute un Nouvelle Employe a la fin de list
void AjouteEmplyee(List * liste,int codeE,char *nomE,char* prenomE,char* dateNaissE,char *titrePostE,float salaireE)
{
    Employe * nouveau = malloc(sizeof(Employe));
    nouveau->code=codeE;
    // nouveau->nom=nomE;
    strcpy(nouveau->nom,nomE);
    // nouveau->prenom=prenomE;
    strcpy(nouveau->prenom,prenomE);
    // nouveau->dateNaiss=dateNaissE;
    strcpy(nouveau->dateNaiss,dateNaissE);
    // nouveau->titrePost=titrePostE;
    strcpy(nouveau->titrePost,titrePostE);
    nouveau->salaire=salaireE;
    nouveau->Next=NULL;
    if(VerficationCodeEmploye(liste,codeE)!=-1)
    {
        printf("\n\nCode Employe est deja existe\n\n");
        return;
    }
    if(liste->head==NULL)
    {
        liste->head=nouveau;
    }
    else
    {
        Employe * tmp =liste->head;
        while(tmp->Next!=NULL)
        {
            tmp=tmp->Next;
        }
        tmp->Next=nouveau;
    }


}

void readData(List *liste)
{
    FILE *pf = fopen("employees.txt", "r");

    if (pf == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    int code;
    char nom[50], prenom[50], dateNaiss[50], titrePost[50];
    float salaire;

    while (fscanf(pf,"%d %s %s %s %s %f \n", &code, nom, prenom, dateNaiss, titrePost, &salaire) == 6)
    {

        AjouteEmplyee(liste, code, nom, prenom, dateNaiss, titrePost, salaire);
    }

    fclose(pf);
}

void Affiche(List * liste)
{
    if(liste->head==NULL)
    {
        printf("List est Vide\n\n");
        return;
    }

    Employe * tmp = liste->head;
    while(tmp!=NULL)
    {

        printf("%d %s %s %s %s %.2f \n",tmp->code,tmp->nom,tmp->prenom,tmp->dateNaiss,tmp->titrePost,tmp->salaire);
        tmp=tmp->Next;
    }
}
//Pour Vérifie si Le Code Employe est existe ou non (si oui return postion , si non -1)
int VerficationCodeEmploye(List * liste, int CodeE)
{
    Employe * tmp = liste->head;
    int postion=0;
    while(tmp != NULL)
    {

        if(tmp->code==CodeE)
        {
            return postion;
        }
        tmp=tmp->Next;
        postion++;
    }
    return -1;
}


void SupprimeEmploye(List * liste,int CodeE)
{
    int postion = VerficationCodeEmploye(liste,CodeE);
    if(postion==-1)
    {
        printf("Le Code n'est existe pas\n");
        return;
    }

    if(postion==0)
    {
        liste->head=liste->head->Next;
        printf("Supprime avec succes\n");
        return;
    }
    Employe * employe = liste->head;
    while(employe!=NULL)
    {
        if(employe->Next==NULL)
        {
            free(employe->Next);
            employe->Next=NULL;
            printf("Supprime avec succes\n");
            return;
        }
        else if(employe->Next->code==CodeE)
        {

            Employe * deleted = employe->Next;
            employe->Next=employe->Next->Next;
            free(deleted);
            printf("Supprime avec succes\n");
            return;
        }
        employe=employe->Next;

    }
}
int sizeList(List * list)
{
    int size=0;
    while(list->head=NULL)
    {
        list->head=list->head->Next;
        size++;
    }
    return size;
}

void saveFile(List * list)
{
    FILE *pf = fopen("employees.txt", "w");

    if (pf == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    Employe *em = list->head;
    while (em != NULL)
    {
        fprintf(pf, "%d %s %s %s %s %2.f\n", em->code, em->nom, em->prenom,em->dateNaiss, em->titrePost, em->salaire);
        em = em->Next;
    }

    fclose(pf);
    printf("les Donnes est enregestre.\n");
}
void rechercheParCode(List *liste, int Code)
{
    Employe *em = liste->head;

    while (em != NULL)
    {
        if (em->code == Code)
        {
            printf("%d %s %s %s %s %2.f \n", em->code, em->nom, em->prenom,em->dateNaiss, em->titrePost, em->salaire);
            return;
        }
        em = em->Next;
    }

    printf("Le code n'existe pas\n");
}

void rechercheParNom(List *liste, char *nom)
{
    Employe *em = liste->head;
    int count = 0;

    while (em != NULL)
    {
        if (strcmp(em->nom, nom) == 0)
        {
            printf("%d %s %s %s %s %2.f \n", em->code, em->nom, em->prenom,em->dateNaiss, em->titrePost, em->salaire);
            count++;
        }
        em = em->Next;
    }

    if (count == 0)
    {
        printf("Employe n'existe pas\n");
        return ;

    }
}


void rechercheParPrenom(List *liste, char *prenom)
{
    Employe *em = liste->head;
    int count = 0;

    while (em != NULL)
    {
        if (strcmp(em->prenom, prenom) == 0)
        {
            printf("%d %s %s %s %s %2.f \n", em->code, em->nom, em->prenom,em->dateNaiss, em->titrePost, em->salaire);
            count++;
        }
        em = em->Next;
    }

    if (count == 0)
    {
        printf("Employe n'existe pas\n");
        return ;

    }
}
void MiseAjourEmplyee(List * liste,int codeE,char *titrePostE,float salaireE)
{
    Employe * em =liste->head;
    if(VerficationCodeEmploye(liste,codeE)==-1)
    {
        printf("Le Code n'exsite pas");
        return;
    }
    while(em!=NULL)
    {
        if(em->code==codeE)
        {
            strcpy(em->titrePost,titrePostE);
            em->salaire=salaireE;
            printf("mise a jour avec succes");
            return;
        }
        em=em->Next;
    }

}

int main()
{
    int code;
    char nom[50];
    char prenom[50];
    char dateNaiss[50];
    char titrePost[50];
    float salaire;
    List * EmployeList = initList();
    int operation,opTitre;

    readData(EmployeList);
    printf("\t ==============Bienvenu===============\n\n");
    do{
    printf("\n------------Menu--------------\n");
    printf("1. Afficher la list\n");
    printf("2. Ajouter employe \n");
    printf("3. Supprimer employe\n");
    printf("4. Rechercher par code\n");
    printf("5. Rechercher par nom\n");
    printf("6. Rechercher par prenom\n");
    printf("7. Mise a jour d'un Employe\n");
    printf("8. Sauvegarder\n");
    printf("9. Sauvegarder et Exit\n");
    printf("------------------------------\n");
        printf("\nEnter your choice: ");
        scanf("%d",&operation);
        switch(operation)
        {
        case 1:
            Affiche(EmployeList);
            break;
        case 2:

            printf("Code : ");
            scanf("%d",&code);
            printf("Nom : ");
            scanf("%s",&nom);
            printf("Prenom : ");
            scanf("%s",&prenom);
            printf("Date Naissance : ");
            scanf("%s",&dateNaiss);
            printf("Titre Poste : ");
            scanf("%s",&titrePost);
            printf("Salaire : ");
            scanf("%f",&salaire);
            AjouteEmplyee(EmployeList,code,nom,prenom,dateNaiss,titrePost,salaire);
            break;
        case 3:
            printf("Donne Code Employe : ");
            scanf("%d",&code);
            SupprimeEmploye(EmployeList,code);
            break;
        case 4:
            printf("Donne le Code : ");
            scanf("%d",&code);
            rechercheParCode(EmployeList,code);
            break;
        case 5:
            printf("Donne le Nom : ");
            scanf("%s",&nom);
            rechercheParNom(EmployeList,nom);
            break;
        case 6:
            printf("Donne le Prenom : ");
            scanf("%s",&prenom);
            rechercheParPrenom(EmployeList,prenom);
            break;
        case 7:
            printf("Pour Mise a jour l'employe ,Entere les information suivant : \n");
            printf("Donne Le Code d'employe: ");
            scanf("%d",&code);
            printf(" Les titres de postes possibles sont :\n\n 1 -President,   2 - VP-Sales ,  3 - VP-Marketing ,  4 -Sales-Manager  ,  5 - Sales-Rep \n\n");
            do
            {
                printf("Donne le numero de titre : ");
                scanf("%d",&opTitre);

            }
            while(opTitre<0 || opTitre>5);
            switch(opTitre)
            {
            case 1:
                strcpy(titrePost,"President");
                break;
            case 2:
                strcpy(titrePost,"VP-Sales");
                break;
            case 3:
                strcpy(titrePost,"VP-Marketing");
                break;
            case 4:
                strcpy(titrePost,"Sales-Manager");
                break;
            case 5:
                strcpy(titrePost,"Sales-Rep");
                break;

            }
            printf("Salaire : ");
            scanf("%f",&salaire);
            MiseAjourEmplyee(EmployeList,code,titrePost,salaire);
            break;
        case 8:
            saveFile(EmployeList);
            break;
        case 9:

            break;

        default:
            printf("Out of range\n");
            break;
        }
    }while(operation!=9);

    saveFile(EmployeList);
    system("pause");
    exit(0);
    return 0;
}
