#ifndef DICCIONARIO_H
#define DICCIONARIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
int openFile(FILE **diccionario, char *modo, char *nom);
int closeFile(FILE *diccionario);
long posIniLec(FILE *diccionario);

// Operaciones del Diccionario
int creaDiccionario(FILE **diccionario);
void nomDiccionario(char *nom);
int iniDicc(FILE **diccionario);

// Menús
void menuGeneral(FILE **diccionario);
void menuSeleccion(FILE **diccionario);
int menuEntidad(FILE **diccionario);
int menuAtributo(FILE **diccionario);

// Operaciones de Entidades
ENT capEnt();
void nomEntidad(char *nom);
void printEnt(FILE *diccionario, char *nomEnt);
int altaEnt(FILE **diccionario);
int bajaEnt(FILE **diccionario);
int consultEnt(FILE *diccionario);
int actuEntidad(FILE **diccionario);
int reporteEnt(FILE *diccionario);

// Operaciones de Atributos
void printAtr(FILE *diccionario, ENT ent, ATR atr);  // Corregida la firma
int altaAtr(FILE **diccionario, ENT ent);  // Sugerida
int bajaAtr(FILE **diccionario, ENT ent);  // Sugerida
int consultaAtr(FILE *diccionario, ENT ent);  // Sugerida
int actualizaAtr(FILE **diccionario, ENT ent);  // Sugerida
int reporteAtr(FILE *diccionario, ENT ent);  // Sugerida

#endif // DICCIONARIO_H
