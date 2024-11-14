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

int main(){

    return 0;
}

// Archivos
int openFile(char *nom){
    int res = 0;
    strcat(nom, ".dic");
    if (fopen(nom, "ab"))
        res = 1;
    return res;
}

int closeFile(FILE *diccionario){
    fclose(diccionario);
    return 1;
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
void nomEntidad(char *nom){
    printf("Ingrese el nombre de la entidad: ");
    scanf("%s", nom);
}

ENT capEnt(){
    ENT nvo;
    char nom[TAM];
    nomEntidad(nom);
    strcat(nvo.nomEnt, nom);
    nvo.headAtr = nvo.headDato = nvo.link = EMPTY;
    return nvo;
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

// Diccionario
void nomDiccionario(char *nom){
    printf("Ingrese el nombre del diccionario: ");
    scanf("%s", nom);
}

int iniDicc(char *nom){
    FILE *diccionario;
    int res = 0;
    long aux = EMPTY;
    if (openFile(nom)){
        strcat(nom, ".dic");
        if (fopen(nom, "ab")){
            fwrite(&aux, sizeof(long), 1, diccionario);
            res = 1;
        }
        closeFile(diccionario);
    }
    return res;
}

int altaEnt(char *nom){
    int res;
    long head, pos;
    ENT aux, nvo;
    FILE *diccionario;
    res = openFile(nom);
    if (res){
        printf("\tAlta de entidad\n");
        nvo = capEnt();
        fseek(diccionario, -sizeof(ENT), SEEK_END);
        pos = ftell(diccionario);
        fread(&aux, sizeof(ENT), 1, diccionario);
        aux.link = pos;
        fseek(diccionario, -sizeof(ENT), SEEK_END);
        fwrite(&aux, sizeof(ENT), 1, diccionario);
        fwrite(&nvo, sizeof(ENT), 1, diccionario);
        closeFile(diccionario);
    }
    return res;
}

int bajaEnt(char *nom){
    int res;
    long dir;
    ENT aux, prev;
    FILE *diccionario;
    char nomEnt[TAM];
    res = openFile(nom);
    if (res){
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
        }
        closeFile(diccionario);
    }
    return res;
}

int consultEnt(char *nom){
    int res;
    char nomEnt[TAM];
    ENT aux;
    FILE *diccionario;
    res = openFile(nom);
    if(res){
        printf("\tConsulta de entidad\n");
        nomEntidad(nomEnt);
        while(fread(&aux, sizeof(ENT), 1, diccionario) && strcmp(nomEnt, aux.nomEnt));
        if (!strcmp(nomEnt, aux.nomEnt))
            printEnt(nomEnt);
        closeFile(diccionario);
    }
    return res;
}

int actuEntidad(char *nom){
    int res;
    char nomEnt[TAM], nvoNomEnt[TAM];
    ENT aux;
    FILE *diccionario;
    res = openFile(nom);
    if (res){
        printf("\tActualiza de entidad\n");
        nomEntidad(nomEnt);
        while(fread(&aux, sizeof(ENT), 1, diccionario) && strcmp(nomEnt, aux.nomEnt));
        if (!strcmp(nomEnt, aux.nomEnt)){
            printf("\tActualiza Entidad\n");
            nomEntidad(nvoNomEnt);
            fseek(diccionario, -sizeof(ENT), SEEK_CUR);
            strcpy(aux.nomEnt, nvoNomEnt);
        }
    }
    return res;
}

int reportEnt(char *nom){
    int res;
    ENT aux;
    FILE *diccionario;
    res = openFile(nom);
    if(res){
        while(fread(&aux, sizeof(ENT), 1, diccionario))
            printEnt(aux.nomEnt);
        closeFile(diccionario);
    }
    return res;
}