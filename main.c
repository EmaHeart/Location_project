#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

typedef struct voiture
{
    int Id;
    char marque[30];
    char Nom_de_utilisateur[40];
    int Model;
    char type_de_Carburant[20];
    int nombre_de_place;
    char Transmission[15];
    float prix_de_location;
    int disponibilite;
    struct voiture *next;
}Voiture;
const char fname[10] = "CSV.txt";
typedef struct
{
    char Username[40];
    char Password[20];
}User;

/*------------------------functions prototype-----------------------*/
void AppMenu(char[]);
int Login(User*);
void InterfaceApp();
void delay(int);
Voiture* UploadFileToList();
Voiture* AjoutVoiture(Voiture*, Voiture*);
void affiche(Voiture*);
void UploadListToFile(Voiture*);
int CheckMatr(int , Voiture*);
int ModifyMenu();
int main();
int SuppMenu();
Voiture* SupprimerParMatricule(Voiture*, int);
int RechercheMenu();
void SwapNodes(Voiture*, Voiture*);
void SortListByPrice(Voiture*);
void SortListByBrand(Voiture*);
/*------------------------function definition-------------------------*/
void affiche(Voiture* p)
{
    Voiture *Liste = p;
    while(Liste!=NULL)
    {
        printf("\n<< la voiture de matricule %d >> : %s || %s || %d || %s || %d || %s || %.2f || %d.\n", Liste->Id, Liste->marque, 
        Liste->Nom_de_utilisateur, Liste->Model, Liste->type_de_Carburant, Liste->nombre_de_place, Liste->Transmission, Liste->prix_de_location,
        Liste->disponibilite);
        Liste = Liste->next;
    }
}

Voiture* AjoutVoiture(Voiture* Liste, Voiture* car) {
    (Liste) = UploadFileToList();
    car->next = (Liste);
    (Liste) = car;
    return (Liste);
}

void AppMenu(char u[])
{
    Voiture *Liste;
    char Choix;
    Liste = UploadFileToList();
    while(1)
    {
        system("cls");
        printf("\t\t\t\t\t\t\t\t\t\t username : %s", u);
        printf("\n\t\t*****************************************\n");
        printf("\n\t\t*****************************************\n");
        printf("\n\t\t*******************Menu******************\n");
        printf("\n\t\t*****************************************\n");
        printf("\n\t\t*****************************************\n");
        printf("\t\tA- Ajouter.\n");
        printf("\t\tB- Modifier.\n");
        printf("\t\tC- Supprimer.\n");
        printf("\t\tD- Afficher.\n");
        printf("\t\tE- Recherche.\n");
        printf("\t\tF- Trier.\n");
        printf("\t\tG- deconnection.\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("your choice: ");
        printf("\n");
        scanf(" %c", &Choix);
        switch (Choix)
        {
        case 'A':{    // AJOUTER  UNE VOITURE
        Voiture *car;
            car = (Voiture*)malloc(sizeof(Voiture));
            printf("\nles info a ajouter: \n");
            printf("Entrez l'ID de la voiture : ");
            if (scanf("%d", &car->Id) != 1) {
                printf("Entrée invalide!\n");
                AppMenu(u);}
            printf("Entrez la marque de la voiture : ");
            if (scanf("%s", car->marque) != 1) {
                printf("Entrée invalide!\n");
                AppMenu(u);}
            printf("Entrez le nom d'utilisateur : ");
            if (scanf("%s", car->Nom_de_utilisateur) != 1) {
                    printf("Entrée invalide!\n");
                    AppMenu(u);}
            printf("Entrez le modèle de la voiture : ");
            if (scanf("%d", &car->Model) != 1) {
                printf("Entrée invalide!\n");
                AppMenu(u);}
            printf("Entrez le type de carburant : ");
            if (scanf("%s", car->type_de_Carburant) != 1) {
                printf("Entrée invalide!\n");
                AppMenu(u);}
            printf("Entrez le nombre de places : ");
            if (scanf("%d", &car->nombre_de_place) != 1) {
                printf("Entrée invalide!\n");
                AppMenu(u);}
            printf("Entrez le type de transmission : ");
            if (scanf("%s", car->Transmission) != 1) {
                printf("Entrée invalide!\n");
                AppMenu(u);}
            printf("Entrez le prix de location par jour : ");
            if (scanf("%f", &car->prix_de_location) != 1) {
                printf("Entrée invalide!\n");
                AppMenu(u);}
            printf("Entrez la disponibilité (1 pour disponible, 0 pour non disponible) : ");
            if (scanf("%d", &car->disponibilite) != 1) {
                printf("Entrée invalide!\n");
                AppMenu(u);}
            printf("Enregistrement réussi!\n"); // If all inputs are successful
            Liste = UploadFileToList();
            while(CheckMatr(car->Id, Liste))
            {
                int newM;
                printf("\n----------matricule entrer est deja exist.\n");
                printf("\nenter new matricule: \n");
                scanf("%d", &newM);
                car->Id = newM;
            }
            system("cls");
            printf("\n\n");
            printf("\n\t*********************************************\n");
            printf("\n\t*********     voiture ajoutee      **********\n");
            printf("\n\t*********     matricule : %d       **********\n", car->Id);
            printf("\n\t*********     Marque : %s          **********\n", car->marque);
            printf("\n\t*********     nom_uti : %s         **********\n",  car->Nom_de_utilisateur);
            printf("\n\t*********     Model : %d           **********\n", car->Model);
            printf("\n\t*********     type_C : %s          **********\n",  car->type_de_Carburant);
            printf("\n\t*********     nbPlace : %d         **********\n",   car->nombre_de_place);
            printf("\n\t*********     Transmision : %s     **********\n", car->Transmission);
            printf("\n\t*********     prixLoc : %.2f       **********\n", car->prix_de_location);
            printf("\n\t*********     disponibilite : %d   **********\n", car->disponibilite);
            printf("\n\t***********************************\n");
            Liste = AjoutVoiture(Liste, car);
            UploadListToFile(Liste);
            break;}
        case 'B':{
            int choice = ModifyMenu();
            switch (choice)
            {
            case 1:
            {
                int id_matric;
                printf("\nentrer le matricule de la voiture vous voulez modifiez: \n");
                scanf("%d",&id_matric);
                int c = CheckMatr(id_matric,Liste);
                if(c)
                {
                    Voiture* tmp = Liste;
                    while(tmp != NULL)
                    {
                        if(tmp->Id == id_matric)
                        {
                            printf("entrer les nouvelles donnees de la voiture de Id : %d\n", tmp->Id);                            
                            printf("Entrez la marque de la voiture : ");
                            if (scanf("%s", tmp->marque) != 1) {
                                printf("Entrée invalide!\n");
                                AppMenu(u);
                            }
                            printf("Entrez le nom d'utilisateur : ");
                            if (scanf("%s", tmp->Nom_de_utilisateur) != 1) {
                                printf("Entrée invalide!\n");
                                AppMenu(u);
                            }
                            printf("Entrez le modèle de la voiture : ");
                            if (scanf("%d", &tmp->Model) != 1) {
                                printf("Entrée invalide!\n");
                                AppMenu(u);
                            }
                            printf("Entrez le type de carburant : ");
                            if (scanf("%s", tmp->type_de_Carburant) != 1) {
                                printf("Entrée invalide!\n");
                                AppMenu(u);
                            }
                            printf("Entrez le nombre de places : ");
                            if (scanf("%d", &tmp->nombre_de_place) != 1) {
                                printf("Entrée invalide!\n");
                                AppMenu(u);
                            }
                            printf("Entrez le type de transmission : ");
                            if (scanf("%s", tmp->Transmission) != 1) {
                                printf("Entrée invalide!\n");
                                AppMenu(u);
                            }
                            printf("Entrez le prix de location par jour : ");
                            if (scanf("%f", &tmp->prix_de_location) != 1) {
                                printf("Entrée invalide!\n");
                                AppMenu(u);
                            }
                            printf("Entrez la disponibilité (1 pour disponible, 0 pour non disponible) : ");
                            if (scanf("%d", &tmp->disponibilite) != 1) {
                                printf("Entrée invalide!\n");
                                AppMenu(u);
                            }
                            break;
                        }
                        tmp = tmp->next;
                    }
                    printf("\nUploaded Successfully.\n");
                    UploadListToFile(Liste);
                }
                else
                {
                    printf("\nCe Matricule n'existe pas dans notre base de donnees.\n");
                }
                break;
            }
            case 2:
            {
                AppMenu(u);
                break;
            }
            default:
                break;
            }
            break;
        }
        case 'C':{
            Voiture *sup1 = Liste, *sup2;
            int choice_delete = SuppMenu();
            switch (choice_delete)
            {
                case 1:{
                    int matri_to_delete;
                    printf("\nEnter the matricule to delete:\n");
                    scanf("%d", &matri_to_delete);

                    if (!CheckMatr(matri_to_delete, Liste)) {
                        printf("\nThis matricule does not exist.\n");
                        system("pause");
                    } else {
                        Voiture *sup1 = Liste, *sup2 = NULL;
                        while (sup1 != NULL) {
                            if (sup1->Id == matri_to_delete) {
                            if (sup2 != NULL) {
                                sup2->next = sup1->next;}
                            else {
                                Liste = sup1->next;
                            }
                            free(sup1);
                            break;
                            }
                            sup2 = sup1;
                            sup1 = sup1->next;
                    }

                    if (!CheckMatr(matri_to_delete, Liste)) {
                        printf("\nDeletion successful!!!\n");
                        UploadListToFile(Liste);
                    }
                    }
                }
                break;
                case 2:{
                    int model_to_delete;
                    printf("\nEnter the model to delete:\n");
                    scanf("%d", &model_to_delete);

                    Voiture *current = Liste;
                    Voiture *previous = NULL;

                    while (current != NULL) {
                        if (current->Model == model_to_delete) {
        
                            if (previous != NULL) {
                                previous->next = current->next;
                                free(current); 
                                current = previous->next; 
                            } else {
                                Liste = current->next;
                                free(current); 
                                current = Liste; 
                            }
                        } else {
                            previous = current;
                            current = current->next;
                        }
                    }
                    UploadListToFile(Liste);
                    }
                    break;
                }
        break;}
        case 'D':
        {
            affiche(Liste);
            system("pause");
            break;
        }
        case 'E':
            {
                affiche(Liste);
                int I = RechercheMenu();
                Voiture *tmp1 = Liste;
                switch (I)
                {
                    case 1:{
                        while (tmp1 != NULL)
                        {
                            if(tmp1->disponibilite == 1)
                            {
                                printf("\n << la voiture de matricule %d >> : %s || %s || %d || %s || %d || %s || %.2f || %d.\n", tmp1->Id, tmp1->marque, tmp1->Nom_de_utilisateur
                            , tmp1->Model, tmp1->type_de_Carburant, tmp1->nombre_de_place, tmp1->Transmission, tmp1->prix_de_location,
                            tmp1->disponibilite);

                            }
                            tmp1 = tmp1->next;
                        }
                        system("pause");
                        break;
                    }
                    case 2:
                    {
                        char brand[30];
                        printf("enter the brand you looking for: ");
                        scanf("%s", brand);
                        printf("les voiture de marque %s: \n", brand);
                        while (tmp1 != NULL)
                        {
                            if(!strcmp(brand,tmp1->marque))
                            {
                                printf("\n << la voiture de matricule %d >> : %s || %s || %d || %s || %d || %s || %.2f || %d.\n", tmp1->Id, tmp1->marque, tmp1->Nom_de_utilisateur
                            , tmp1->Model, tmp1->type_de_Carburant, tmp1->nombre_de_place, tmp1->Transmission, tmp1->prix_de_location,
                            tmp1->disponibilite);
                            }
                            tmp1 = tmp1->next;
                        }
                        system("pause");
                        break;
                    }
                default :
                    printf("\nerror!!\n");
                    break;
            }
        break;
            }
        case 'F':
        {
            int c;
            printf("\nsort by:\n");
            printf("1- price.\n");
            printf("2- brand. \n");
            printf("your choice: ");
            scanf("%d", &c);
            switch (c)
            {
                case 1:
                {
                    SortListByPrice(Liste);
                    affiche(Liste);
                    UploadListToFile(Liste);
                    system("pause");
                    break;
                }
                case 2:
                {
                    SortListByBrand(Liste);
                    affiche(Liste);
                    UploadListToFile(Liste);
                    system("pause");
                    break;
                }
            }
            break;
        }
        case 'G':{
            system("cls");
            printf("\n*****************************************\n");
            printf("\n****************disconnected*************\n");
            printf("\n*****************Succesfully*************\n");
            printf("\n*****************************************\n");
            system("pause");
            system("cls");
            main();
        }
        default:
            printf("\nIncorrect Input.\n");
            break;
        }
    }
}

void delay(int number_of_seconds)
{
    int milli_seconds = 1000 * number_of_seconds;
    // Storing start time
    clock_t start_time = clock();
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}

void InterfaceApp()
{
    printf("\n*************************************************\n");
    printf("\n*************************************************\n");
    printf("\n*******************Welcome to our****************\n");
    printf("\n*********************Users app*******************\n");
    printf("\n*************************************************\n");
    printf("\n*************************************************\n");
    system("pause");
    system("cls");
}

Voiture* UploadFileToList() {
    Voiture* Liste = NULL;
    Voiture* p = NULL;
    FILE* file = fopen("CSV.txt", "r");
    if (!file) {
        printf("Error opening the file.");
        return NULL;
    }

    while (1) {
        p = (Voiture*)malloc(sizeof(Voiture));
        if (!p) {
            printf("Memory allocation failed.");
            fclose(file);
            free(Liste);
            return NULL;
        }

        int result = fscanf(file, "%d %s %s %d %s %d %s %f %d",
                            &p->Id, p->marque, p->Nom_de_utilisateur,
                            &p->Model, p->type_de_Carburant,
                            &p->nombre_de_place, p->Transmission,
                            &p->prix_de_location, &p->disponibilite);
        if (result != 9) {
            free(p);
            break;
        }
        p->next = Liste;
        Liste = p;
    }
    fclose(file);
    return Liste;
}

int Login(User* check)
{
    User u;
    int c=0;
    FILE *file;
    file = fopen("Users.txt","rt");
    if(file == NULL)
    {
        exit(1);
    }
    while (fscanf(file, "%s %s", u.Username, u.Password) != EOF)
    {
        if(!strcmp(u.Username,check->Username) && !strcmp(u.Password,check->Password)){
             c=1;
            return c;
        }
    }
    return c;
}

void UploadListToFile(Voiture* Liste) {
    FILE* file = fopen("CSV.txt", "w");
    Voiture* current = (Liste);
    if (file == NULL){
        printf("Error opening file.\n");
        exit(1);
    }
    while (current != NULL) {
        fprintf(file, "%d %s %s %d %s %d %s %.2f %d\n", current->Id, current->marque,
                current->Nom_de_utilisateur, current->Model, current->type_de_Carburant,
                current->nombre_de_place, current->Transmission, current->prix_de_location,
                current->disponibilite);
        current = current->next;
    }
    printf("\nUpload successfully");
    fclose(file);
}

int ModifyMenu()
{
    int i;
    system("cls");
    printf ("||--------------------------------------||\n") ;
    printf ("||--------------------------------------||\n") ;
    printf ("||---BIENVENUE DANS LE MENU\"MODIFY\"---||\n") ;
    printf ("||--------------------------------------||\n") ;
    printf ("||--------------------------------------||\n") ;
    printf ("||------Veuillez modifier via ----------||\n") ;
    printf ("||--------------------------------------||\n") ;
    printf ("||   1. par matricul                    ||\n") ;
    printf ("||   2. RETURN                          ||\n") ;
    printf ("||--------------------------------------||\n") ;
    printf ("||--------------------------------------||\n") ;
    printf("votre choix: \t\t");
    scanf("%d", &i);
    return i;
}

int CheckMatr(int c, Voiture *p) {
    int flag = 0;
    Voiture *Liste = p;

    while (Liste != NULL) {
        if (Liste->Id == c) {
            flag = 1;
            return flag;
        }
        Liste = Liste->next;
    }
    return flag;
}

int SuppMenu()
{
    int i;
    system("cls");
    printf ("||--------------------------------------||\n") ;
    printf ("||--------------------------------------||\n") ;
    printf ("||---BIENVENUE DANS LE MENU\"Supprr\"---||\n") ;
    printf ("||--------------------------------------||\n") ;
    printf ("||--------------------------------------||\n") ;
    printf ("||------Veuillez supprimer via ---------||\n") ;
    printf ("||--------------------------------------||\n") ;
    printf ("||   1. par matricul                    ||\n") ;
    printf ("||   2. par model                       ||\n") ;
    printf ("||   0. RETURN                          ||\n") ;
    printf ("||--------------------------------------||\n") ;
    printf ("||--------------------------------------||\n") ;
    printf("votre choix: \t\t");
    scanf("%d", &i);
    return i;
}

int RechercheMenu(){
    int I;
    system("cls");
    printf("\nWelcome to Car Search App\n");
    printf("\nMenu:\n");
    printf("1. Search by disponibilite\n");
    printf("2. Search by Brand\n");
    printf("3. Exit\n");
    printf("------------------------------------------");
    printf("\n\t\tEnter your choice: ");
    scanf("%d", &I);
    return I;
}

void SortListByPrice(Voiture* Liste) {
    int swapped;
    Voiture* ptr1;
    Voiture* lptr = NULL;
    
    if (Liste == NULL)
        return;
    do {
        swapped = 0;
        ptr1 = Liste;

        while (ptr1->next != lptr) {
            // Compare prices of adjacent nodes and swap if necessary
            if (ptr1->prix_de_location > ptr1->next->prix_de_location) {
                SwapNodes(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void SwapNodes(Voiture* a, Voiture* b) {
    int temp_id = a->Id;
    a->Id = b->Id;
    b->Id = temp_id;
    char temp_marque[100];
    strcpy(temp_marque, a->marque);
    strcpy(a->marque, b->marque);
    strcpy(b->marque, temp_marque);
    char temp_nom[100];
    strcpy(temp_nom, a->Nom_de_utilisateur);
    strcpy(a->Nom_de_utilisateur, b->Nom_de_utilisateur);
    strcpy(b->Nom_de_utilisateur, temp_nom);
    int temp_model = a->Model;
    a->Model = b->Model;
    b->Model = temp_model;
    char temp_carburant[100];
    strcpy(temp_carburant, a->type_de_Carburant);
    strcpy(a->type_de_Carburant, b->type_de_Carburant);
    strcpy(b->type_de_Carburant, temp_carburant);
    int temp_places = a->nombre_de_place;
    a->nombre_de_place = b->nombre_de_place;
    b->nombre_de_place = temp_places;
    char temp_transmission[100];
    strcpy(temp_transmission, a->Transmission);
    strcpy(a->Transmission, b->Transmission);
    strcpy(b->Transmission, temp_transmission);
    float temp_price = a->prix_de_location;
    a->prix_de_location = b->prix_de_location;
    b->prix_de_location = temp_price;
    int temp_disponibilite = a->disponibilite;
    a->disponibilite = b->disponibilite;
    b->disponibilite = temp_disponibilite;
}

void SortListByBrand(Voiture* Liste) {
    int swapped;
    Voiture* ptr1;
    Voiture* lptr = NULL;

    // Checking for empty list
    if (Liste == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = Liste;

        while (ptr1->next != lptr) {
            // Compare brands of adjacent nodes and swap if necessary
            if (strcmp(ptr1->marque, ptr1->next->marque) > 0) {
                SwapNodes(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

/*--------------------------main--------------------------------*/
int main()
{
    User *user1;
    InterfaceApp();
    user1 = (User*)malloc(sizeof(User));
    printf("\nUsername\t:\t");
    scanf("%s", user1->Username);
    printf("\nPassword\t:\t");
    int i=0;
    char x;
    while ((x = getch()) != 13 && i < 20) {
        user1->Password[i] = x;
        printf("*");
        i++;
    }
    user1->Password[i] = '\0';
    int c;
    c = Login(user1);
    if((c)==1)
    {
        printf("\n*****************************************\n");
        printf("\n*******************Login*****************\n");
        printf("\n*****************Succesfully*************\n");
        printf("\n*****************************************\n");
        delay(1);
        system("cls");
        AppMenu(user1->Username);
    }
    else
    {
        printf("\nERROR!\n");
        exit(1);
    }
    return 0;
}
