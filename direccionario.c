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

ENT capEnt(){
    ENT nvo;
    printf("Ingresa el nombre de la entidad: ");
    scanf("%s", nvo.nomEnt);
    nvo.headAtr = nvo.headDato = nvo.link = EMPTY;
    return nvo;
}

void printEnt(char *nomEnt){
    ENT aux;
    FILE *diccionario;
    do{
        fread(&aux, sizeof(ENT), 1, diccionario);
    } while (aux.link > 0 && !strcmp(nomEnt, aux.nomEnt));
    if (!strcmp(nomEnt, aux.nomEnt))
        printf("Nombre de la entidad: %s", aux.nomEnt);
    else 
        printf("No se encontró la entidad\n");
}

void printAtr(ENT ent, ATR atr){
    long dir;
    FILE *diccionario;
    printf("Atributos de la entidad: %s", ent.nomEnt);
    fseek(diccionario, ent.headAtr, SEEK_SET);
    do{
        fread(&dir, sizeof(long), 1, diccionario);
    } while (dir != EMPTY);
}

void nomEntidad(char *nom){
    printf("Ingrese el nombre de la entidad: ");
    scanf("%s", nom);
}

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
    int res = 0;
    long head, pos;
    ENT aux, nvo;
    FILE *diccionario;
    if (openFile(nom)){
        nvo = capEnt();
        fseek(diccionario, -sizeof(ENT), SEEK_END);
        pos = ftell(diccionario);
        aux.link = pos;
        fwrite(&aux, sizeof(ENT), 1, diccionario);
        fwrite(&nvo, sizeof(ENT), 1, diccionario);
        closeFile(diccionario);
    }
    return res;
}

int bajaEnt(char *nom){
    int res = 0;
    long dir;
    ENT aux, prev;
    FILE *diccionario;
    char nomEnt[TAM];
    nomEntidad(nomEnt);
    if (openFile(nom)){
        do {
            fread(&aux, sizeof(ENT), 1, diccionario);
        } while (!strcmp(nomEnt, aux.nomEnt));
        fread(&prev, sizeof(ENT), 1, diccionario);
        dir = aux.link;
        fseek(diccionario, -sizeof(ENT)*2, SEEK_CUR);
        fread(&prev, sizeof(ENT), 1, diccionario);
        prev.link = dir;
        aux.link = EMPTY;   
        fseek(diccionario, -sizeof(ENT), SEEK_CUR);
        fwrite(&prev, sizeof(ENT), 1, diccionario);
        closeFile(diccionario);
    }
    return res;
}

int consultEnt(char *nom, char *nomEnt){
    int res = 0;
    ENT aux;
    FILE *diccionario;
    if(openFile(nom)){
        while(fread(&aux, sizeof(ENT), 1, diccionario) && !strcmp(nomEnt, aux.nomEnt))
        if (!strcmp(nomEnt, aux.nomEnt))
            printEnt(nomEnt);
        closeFile(diccionario);
    }
    return res;
}

int actuEntidad(char *nom){
    int res = 0;

    return res;
}
int reportEnt(char *nom){
    int res = 0;
    return res;
}