#include "diccionario.h"

int main(){
    int res = 0;
    FILE *diccionario;
    menuGeneral(&diccionario);
    closeFile(diccionario);
    return 0;
}

// Manejo archivos
int openFile(FILE **diccionario, char *modo, char *nom){
    int res = 0;
    *diccionario = fopen(nom, modo);
    printf("Abriendo...");
    if (*diccionario){
        res = 1;
        printf("Diccionario abierto\n");
    }
    else
        printf("Error al abrir diccionario\n");
    return res;
}

int closeFile(FILE *diccionario){
    fclose(diccionario);
    return 1;
}

long posIniLec(FILE *diccionario){
    long head;
    fseek(diccionario, 0, SEEK_SET);
    fread(&head, sizeof(long), 1, diccionario);
    return head;
}

// Diccionario
void nomDiccionario(char *nom){
    printf("Ingrese el nombre del diccionario: ");
    scanf("%s", nom);
    strcat(nom, ".dic");
}

int iniDicc(FILE **diccionario){
    long aux = EMPTY;
    fwrite(&aux, sizeof(long), 1, *diccionario);
    return 1;
}

int creaDiccionario(FILE **diccionario){
    int res, op = 4;
    char nom[TAM];
    nomDiccionario(nom);
    *diccionario = fopen(nom, "rb");
    if (*diccionario){
        printf("\tEl diccionario ya existe\n");
        printf("1. Sobreescribirlo\n");
        printf("2. Abrir el diccionario existente\n");
        printf("3. Salir\n");
        printf("Ingrese la opción que desea: ");
        scanf("%d", &op);
        closeFile(*diccionario);
    }
    do{
        switch (op){
            case 1: *diccionario = fopen(nom, "wb");
                    printf("Sobreescribiendo...");
                    if (diccionario){
                        printf("Diccionario creado\n");
                        iniDicc(diccionario);
                        res = 1;
                    } else printf("Error al abrir diccionario\n");

            break;
            case 2: res = openFile(diccionario, "ab", nom);
            break;
            case 3: printf("Saliendo..Adiós c:\n");
                    res = 0;
            break;
            case 4: res = openFile(diccionario, "wb", nom);
            break;
            default:printf("Opción inválida\n");
                    printf("Ingrese la opción que desea: ");
                    scanf("%d", &op);
            break;
        } 
    } while(op < 1 || op > 4);
    return res;
}

// Menús
void menuGeneral(FILE **diccionario){
    int op;
    char nom[TAM];
    printf("\tMenú\n");
    printf("1. Crear Diccionario\n");
    printf("2. Abrir Diccionario\n");
    printf("3. Salir\n");
    do{
        printf("Ingrese la opción que desea: ");
        scanf("%d", &op);
        switch (op){
            case 1: if(creaDiccionario(diccionario))
                        menuSeleccion(diccionario);
            break;
            case 2: nomDiccionario(nom);
                    *diccionario = fopen(nom, "rb");
                    if (*diccionario){
                        closeFile(*diccionario);
                        openFile(diccionario,"ab", nom);
                        menuSeleccion(diccionario);
                    }
                    else{
                        printf("El diccionario no existe\n");
                        closeFile(*diccionario);
                        op = 0;
                    }
            break;
            case 3: printf("Saliendo..Adiós c:\n");
            break;
            default: printf("Opción inválida\n");
            break;
        }
    } while ( op < 1 || op > 3);
}

void menuSeleccion(FILE **diccionario){
    int op, aux;
    printf("\tMenú de Selección\n");
    printf("1. Trabajar Entidades\n");
    printf("2. Trabajar Atributo\n");
    printf("3. Trabajar Dato\n");
    printf("4. Salir\n");
    do{
        printf("Ingrese la opción que desea: ");
        scanf("%d", &op);
        switch (op){
            case 1: do{
                        aux = menuEntidad(diccionario);
                    } while (aux);
            break;
            case 2: do{
                        aux = menuAtributo(diccionario);
                    } while (aux);
            break;
            // Opcion atributos
            case 3: 
            break;
            case 4: printf("Saliendo..Adiós c:\n");
            break;
            default: printf("Opción inválida\n");
            break;
        }
    } while(op < 1 || op > 4);    
}

int menuEntidad(FILE **diccionario){
    int op, res = 1;
    printf("\tMenú Entidades\n");
    printf("1. Alta\n");
    printf("2. Baja\n");
    printf("3. Consulta\n");
    printf("4. Actualizar\n");
    printf("5. Reporte\n");
    printf("6. Salir\n");
    do {
        printf("Ingrese la opción que desea: ");
        scanf("%d", &op);
        switch (op){
            case 1: res = altaEnt(diccionario);
                    if (res) printf("Entidad dada de alta\n");
                    else printf("Error\n");
            break;
            case 2: res = bajaEnt(diccionario);
                    if (res) printf("Entidad dada de baja\n");
                    else printf("Error\n");
            break;
            case 3: res = consultEnt(*diccionario);
            break;
            case 4: res = actuEntidad(diccionario);
                    if (res) printf("Entidad actualizada\n");
                    else printf("Error\n");
            break;
            case 5: res = reporteEnt(*diccionario);
            break;
            case 6: printf("Saliendo..Adiós:)\n");
                    res = 0;
            break;
            default: printf("Opción inválida\n");
            break;
        }
    } while( op < 1 || op > 6);
    return res;
}

int menuAtributo(FILE **diccionario){
    int op;
    printf("\tMenú de atributos\n");
    printf("1. Alta\n");
    printf("2. Baja\n");
    printf("3. Consulta\n");
    printf("4. Actualizar\n");
    printf("5. Reporte\n");
    printf("6. Salir\n");
    printf("Ingrese la opción que desea: ");
    scanf("%d", &op);
    return op;   
}

// Entidades
ENT capEnt(){
    ENT nvo;
    char nom[TAM];
    nomEntidad(nom);
    strcpy(nvo.nomEnt, nom);
    nvo.headAtr = nvo.headDato = nvo.link = EMPTY;
    return nvo;
}

void nomEntidad(char *nom){
    printf("Ingrese el nombre de la entidad: ");
    scanf("%s", nom);
}

void printEnt(FILE *diccionario, char *nomEnt){
    ENT aux;
    long head;
    int band;
    head = posIniLec(diccionario);
    fseek(diccionario, head, SEEK_SET);
    printf("Hola\n");
    while(fread(&aux, sizeof(ENT), 1, diccionario)){
        if (!strcmp(nomEnt, aux.nomEnt)){
            printf("Nombre de la entidad: %s", aux.nomEnt);
            band = 1;
        }
        fseek(diccionario, aux.link, SEEK_SET);
    }
    if (!band)
        printf("No se encontró la entidad\n");
}

int altaEnt(FILE **diccionario){
    ENT nvo, aux;
    long pos, head;
    printf("\tAlta de entidad\n");
    fseek(*diccionario, 0, SEEK_CUR);
    fread(&head, sizeof(long), 1, *diccionario);
    fseek(*diccionario, 0, SEEK_END);
    pos = ftell(*diccionario);
    if (head == EMPTY){
        head = pos;
        fseek(*diccionario, 0, SEEK_SET);
        fwrite(&head, sizeof(long), 1, *diccionario);
    }
    else{
        fseek(*diccionario, head, SEEK_SET);
        while(fread(&aux, sizeof(ENT), 1, *diccionario) && aux.link != EMPTY)
        fseek(*diccionario, aux.link, SEEK_SET);
        aux.link = pos;
        fseek(*diccionario, -sizeof(ENT), SEEK_CUR);
        fwrite(&aux, sizeof(ENT), 1, *diccionario);
    }
    nvo = capEnt();
    fwrite(&nvo, sizeof(ENT), 1, *diccionario);
    return 1;
}

int bajaEnt(FILE **diccionario){
    int res = 0;
    long dirAct, dirPrev, head;
    char nomEnt[TAM];
    ENT aux, prev;
    printf("\tBaja de entidad\n");
    nomEntidad(nomEnt);
    head = posIniLec(*diccionario);
    fseek(*diccionario, head, SEEK_SET);
    while (fread(&aux, sizeof(ENT), 1, *diccionario)){    
        dirAct = ftell(*diccionario) - sizeof(ENT);
        if (!strcmp(nomEnt,aux.nomEnt)){
            if (dirAct == head){
                head = aux.link;
                fseek(*diccionario, 0, SEEK_SET);
                fwrite(&head, sizeof(long), 1, *diccionario);
            }
            else {
                fseek(*diccionario, dirPrev, SEEK_SET);
                fread(&prev, sizeof(ENT), 1, *diccionario);
                prev.link = aux.link;
                fseek(*diccionario, dirPrev, SEEK_SET);
                fwrite(&aux, sizeof(ENT), 1, *diccionario);
            }
        }
        dirPrev = dirAct;
        fseek(*diccionario, aux.link, SEEK_SET);
    }
    return res;
}

int consultEnt(FILE *diccionario){
    int res;
    char nomEnt[TAM];
    printf("\tConsulta de entidad\n");
    nomEntidad(nomEnt);
    printEnt(diccionario, nomEnt);
    return 1;
}

int actuEntidad(FILE **diccionario){
    int res = 0;
    char nomEnt[TAM], nvoNomEnt[TAM];
    ENT aux;
    fseek(*diccionario, 0, SEEK_SET);
    printf("\tActualiza de entidad\n");
    nomEntidad(nomEnt);
    while(fread(&aux, sizeof(ENT), 1, *diccionario) && strcmp(nomEnt, aux.nomEnt));
    if (!strcmp(nomEnt, aux.nomEnt)){
        printf("\tActualiza Entidad\n");
        nomEntidad(nvoNomEnt);
        fseek(*diccionario, -sizeof(ENT), SEEK_CUR);
        strcpy(aux.nomEnt, nvoNomEnt);
        fwrite(&aux, sizeof(ENT), 1, *diccionario);
        res = 1;
    }
    return res;
}

int reporteEnt(FILE *diccionario){
    ENT aux;
    fseek(diccionario, 0, SEEK_SET);
    printf("\t--- Reporte de Entidades ---\n");
    while(fread(&aux, sizeof(ENT), 1, diccionario)){
        printf("Nombre: %s\n", aux.nomEnt);
        fseek(diccionario, aux.link, SEEK_SET);
    }
    return 1;
}

// Antributos
void printAtr(FILE *diccionario, ENT ent, ATR atr){
    long dir;
    printf("Atributos de la entidad: %s", ent.nomEnt);
    fseek(diccionario, ent.headAtr, SEEK_SET);
    do{
        fread(&dir, sizeof(long), 1, diccionario);
    } while (dir != EMPTY);
}

