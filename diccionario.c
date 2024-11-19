#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define EMPTY -1
#define TAM 30

// Entidad: estructuras
// Atributos: nombre de las cosas 
// Datos: lo que contienen :D 

typedef struct{
    char nomEnt[TAM];
    long headAtr;
    long headDato;
    long link;
} ENT;

typedef struct{
    char nomAtr[TAM];
    int tipo; //1 char, 2 entero, 3 flotante, 4 cadena
    int tam;
    long link;
} ATR;

// Declaraciones
// Manejo archivos
int openFile(FILE **diccionario);
int closeFile(FILE *diccionario);
// Diccionario
int creaDiccionario(FILE **diccionario);
void nomDiccionario(char *nom);
int iniDicc(FILE **diccionario);
// Menús
int menuGeneral();
int menuSeleccion();
int menuEntidad();
int menuAtributo();
// Entidades
ENT capEnt();
void nomEntidad(char *nom);
void printEnt(char *nomEnt);
int altaEnt(FILE *diccionario);
int bajaEnt(FILE *diccionario);
int consultEnt(FILE *diccionario);
int actuEntidad(FILE *diccionario);
void reportEnt(FILE *diccionario);
// Atributos
void printAtr(ENT ent, ATR atr);

int main(){
    int op, res = 0;
    FILE *diccionario;
        op = menuGeneral();
        switch (op){
            case 1: res = creaDiccionario(&diccionario);
            break;
            case 2: res = openFile(&diccionario);
            break;
            case 3: printf("Saliendo..Adiós:)\n");
                    res = 0;
            break;
            default:printf("Opción inválida\n");
                    printf("Ingrese la opción que desea: ");
                    scanf("%d", &op);
            break;
        }
    if (res){
            op = menuSeleccion();
            switch (op){
                case 1: menuEntidad();
                break;
                case 2: menuAtributo();
                break;
                // Opcion atributos
                case 3: 
                break;
                default:printf("Opción inválida\n");
                        printf("Ingrese la opción que desea: ");
                        scanf("%d", &op);
                break;
            }
        closeFile(diccionario);
    }
    return 0;
}

// Manejo archivos
int openFile(FILE **diccionario){
    int res = 0;
    char nom[TAM];
    nomDiccionario(nom);
    *diccionario = fopen(nom, "ab");
    printf("Abriendo...");
    if (diccionario){
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

// Diccionario
void nomDiccionario(char *nom){
    printf("Ingrese el nombre del diccionario: ");
    scanf("%s", nom);
    strcat(nom, ".dic");
}

int iniDicc(FILE **diccionario){
    int res = 0;
    long aux = EMPTY;
    fwrite(&aux, sizeof(long), 1, *diccionario);
    return 1;
}

int creaDiccionario(FILE **diccionario){
    int res, op = 1;
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
    switch (op){
        case 1: *diccionario = fopen(nom, "wb");
                printf("Sobreescribiendo...");
                if (diccionario){
                    printf("Diccionario creado\n");
                    iniDicc(diccionario);
                    res = 1;
                } else printf("Error al abrir diccionario\n");

        break;
        case 2: *diccionario = fopen(nom, "ab");
                printf("Abriendo...");
                if (diccionario){
                    printf("Diccionario abierto\n");
                    res = 1;
                } else printf("Error al abrir diccionario\n");
        break;
        case 3: printf("Saliendo..Adiós:)\n");
                res = 0;
        break;
        default:printf("Opción inválida\n");
        break;
    }
    return res;
}

// Menús
int menuGeneral(){
    int op;
    printf("\tMenú\n");
    printf("1. Crear Diccionario\n");
    printf("2. Abrir Diccionario\n");
    printf("3. Salir\n");
    printf("Ingrese la opción que desea: ");
    scanf("%d", &op);
    return op;
}

int menuSeleccion(){
    int op;
    printf("\tMenú de Selección\n");
    printf("1. Trabajar Entidades\n");
    printf("2. Trabajar Atributo\n");
    printf("3. Trabajar Dato\n");
    printf("Ingrese la opción que desea: ");
    scanf("%d", &op);
    return op;
    
}

int menuEntidad(){
    int op;
    printf("\tMenú Entidades\n");
    printf("1. Alta\n");
    printf("2. Baja\n");
    printf("3. Consulta\n");
    printf("4. Actualizar\n");
    printf("5. Reporte\n");
    printf("Ingrese la opción que desea: ");
    scanf("%d", &op);
    return op;
    
}

int menuAtributo(){
    int op;
    printf("\tMenú de atributos\n");
    printf("1. Alta\n");
    printf("2. Baja\n");
    printf("3. Consulta\n");
    printf("4. Actualizar\n");
    printf("5. Reporte\n");
    printf("Ingrese la opción que desea: ");
    scanf("%d", &op);
    return op;   
}

// Entidades
ENT capEnt(){
    ENT nvo;
    char nom[TAM];
    nomEntidad(nom);
    strcat(nvo.nomEnt, nom);
    nvo.headAtr = nvo.headDato = nvo.link = EMPTY;
    return nvo;
}

void nomEntidad(char *nom){
    printf("Ingrese el nombre de la entidad: ");
    scanf("%s", nom);
}

void printEnt(char *nomEnt){
    ENT aux;
    FILE *diccionario;
    while(fread(&aux, sizeof(ENT), 1, diccionario) && strcmp(nomEnt, aux.nomEnt));
    if (!strcmp(nomEnt, aux.nomEnt))
        printf("Nombre de la entidad: %s", aux.nomEnt);
    else 
        printf("No se encontró la entidad\n");
}

int altaEnt(FILE *diccionario){
    int res;
    long head, pos;
    ENT aux, nvo;
    printf("\tAlta de entidad\n");
    nvo = capEnt();
    fseek(diccionario, 0, SEEK_END);
    pos = ftell(diccionario);
    fseek(diccionario, -sizeof(ENT), SEEK_CUR);
    fread(&aux, sizeof(ENT), 1, diccionario);
    aux.link = pos;
    fseek(diccionario, -sizeof(ENT), SEEK_END);
    fwrite(&aux, sizeof(ENT), 1, diccionario);
    fwrite(&nvo, sizeof(ENT), 1, diccionario);
    res = 1;
    return res;
}

int bajaEnt(FILE *diccionario){
    int res = 0;
    long dir;
    char nomEnt[TAM];
    ENT aux, prev;
    printf("\tBaja de entidad\n");
    nomEntidad(nomEnt);
    while(fread(&aux, sizeof(ENT), 1, diccionario) && strcmp(nomEnt, aux.nomEnt));
    if ( !strcmp(nomEnt, aux.nomEnt)){
        fseek(diccionario, -sizeof(ENT)*2, SEEK_CUR);
        fread(&prev, sizeof(ENT), 1, diccionario);
        dir = aux.link;
        prev.link = dir;
        aux.link = EMPTY;   
        fseek(diccionario, -sizeof(ENT), SEEK_CUR);
        fwrite(&prev, sizeof(ENT), 1, diccionario);
        res = 1;
    }
    return res;
}

int consultEnt(FILE *diccionario){
    int res = 0;
    char nomEnt[TAM];
    ENT aux;
    printf("\tConsulta de entidad\n");
    nomEntidad(nomEnt);
    while(fread(&aux, sizeof(ENT), 1, diccionario) && strcmp(nomEnt, aux.nomEnt));
    if (!strcmp(nomEnt, aux.nomEnt)){
        printEnt(nomEnt);
        res = 1;
    }
    return res;
}

int actuEntidad(FILE *diccionario){
    int res = 0;
    char nomEnt[TAM], nvoNomEnt[TAM];
    ENT aux;
    printf("\tActualiza de entidad\n");
    nomEntidad(nomEnt);
    while(fread(&aux, sizeof(ENT), 1, diccionario) && strcmp(nomEnt, aux.nomEnt));
    if (!strcmp(nomEnt, aux.nomEnt)){
        printf("\tActualiza Entidad\n");
        nomEntidad(nvoNomEnt);
        fseek(diccionario, -sizeof(ENT), SEEK_CUR);
        strcpy(aux.nomEnt, nvoNomEnt);
        res = 1;
    }
    return res;
}

void reportEnt(FILE *diccionario){
    ENT aux;
    while(fread(&aux, sizeof(ENT), 1, diccionario))
        printEnt(aux.nomEnt);
}

// Antributos
void printAtr(ENT ent, ATR atr){
    long dir;
    FILE *diccionario;
    printf("Atributos de la entidad: %s", ent.nomEnt);
    fseek(diccionario, ent.headAtr, SEEK_SET);
    do{
        fread(&dir, sizeof(long), 1, diccionario);
    } while (dir != EMPTY);
}

