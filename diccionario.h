#ifndef DICCIONARIO_H
#define DICCIONARIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constantes
#define EMPTY -1
#define TAM 20

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

typedef struct {
    long dat;
    long link;
} DAT;

// Manejo de archivos
int abreArch(FILE **diccionario, char *modo, char *nom);
int cierraArch(FILE *diccionario);
void nomArch(char *nom);
int iniArch(FILE **diccionario);
int diccRepetido(FILE **diccionario, char *nom);
long leeHead(FILE *diccionario);

// Utilidades
int opValida(int nMax);
void muestraDato(long head, long hAtr, FILE *diccionario);
void muestraValor(void *dato, int tipo);

// Operaciones del Diccionario
int creaDiccionario(FILE **diccionario, char *nom);

// Menús
int menuGeneral(FILE **diccionario, char *nom);
int menuSeleccion(FILE **diccionario);
int menuEnt(FILE **diccionario);
int menuAtr(FILE **diccionario);
int menuDat(FILE **diccionario);

// Utilidad entidades
ENT creaEntidad();
void nomEnt(char *nom);

// Utilidad atributos
ATR creaAtributo();
void nomAtr(char *nom);

// Operaciones de Entidades
int altaEnt(FILE **diccionario);
int bajaEnt(FILE **diccionario);
int consultaEnt(FILE *diccionario);
int actualizaEnt(FILE **diccionario);
int reporteEnt(FILE *diccionario);

// Operaciones de Atributos
int altaAtr(FILE **diccionario);
int bajaAtr(FILE **diccionario);
int consultaAtr(FILE *diccionario);
int actualizaAtr(FILE **diccionario);
int reporteAtr(FILE *diccionario);

// Operaciones de Datos
int altaDat(FILE **diccionario);
int bajaDat(FILE **diccionario);
int consultaDat(FILE *diccionario);
int actualizaDat(FILE **diccionario);
int reporteGen(FILE *diccionario);

#endif // DICCIONARIO_H