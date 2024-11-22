#ifndef DICCIONARIO_H
#define DICCIONARIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definición de constantes
#define EMPTY -1
#define TAM 30

// Definición de estructuras
typedef struct {
    char nomEnt[TAM];
    long headAtr;
    long headDato;
    long link;
} ENT;

typedef struct {
    char nomAtr[TAM];
    int tipo;  // 1 char, 2 entero, 3 flotante, 4 cadena
    int tam;
    long link;
} ATR;

// Manejo de archivos
int abreArch(FILE **diccionario, char *modo, char *nom);
int cierraArch(FILE *diccionario);
void nomArch(char *nom);
int iniArch(FILE **diccionario);
int diccRepetido(FILE **diccionario, char *nom);
long leeHead(FILE *diccionario);

// Utilidades
int opValida(int nMax);

// Operaciones del Diccionario
int creaDiccionario(FILE **diccionario, char *nom);

// Menús
int menuGeneral(FILE **diccionario, char *nom);
int menuSeleccion(FILE **diccionario);
int menuEnt(FILE **diccionario);
int menuAtr(FILE **diccionario);

// Utilidad entidades
ENT creaEntidad();
void nomEnt(char *nom);
void muestraEnt(FILE *diccionario, char *nomEnt);

// Operaciones de Entidades
int altaEnt(FILE **diccionario);
int bajaEnt(FILE **diccionario);
int consultEnt(FILE *diccionario);
int actuEntidad(FILE **diccionario);
int reporteEnt(FILE *diccionario);

// Operaciones de Atributos (por implementar)
int altaAtr(FILE **diccionario, ENT *ent);
int bajaAtr(FILE **diccionario, ENT *ent);
int consultaAtr(FILE *diccionario, ENT *ent);
int actualizaAtr(FILE **diccionario, ENT *ent);
int reporteAtr(FILE *diccionario, ENT *ent);

#endif // DICCIONARIO_H