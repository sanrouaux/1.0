#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <conio.h>
#include "Biblioteca.h"
#include "Fecha.h"
#include "Director.h"
#include "Pelicula.h"
#include "Menu.h"

void mostrarMenuPrincipal(void)
{
    printf("Menu de opciones:\n");
    printf("1) Altas peliculas\n");
    printf("2) Modificar datos de una pelicula\n");
    printf("3) Baja de pelicula\n");
    printf("4) Nuevo director\n");
    printf("5) Eliminar director\n");
    printf("6) Listar\n");
    printf("7) Salir\n");
}

void mostrarMenuModificar(void)
{
    printf("1) Titulo\n");
    printf("2) Anio\n");
    printf("3) Nacionalidad\n");
    printf("4) Director");
}

void mostrarMenuListar(void)
{
    printf("1) Peliculas\n");
    printf("2) Directores\n");
}

int menuPrincipal(void)
{
    int opcion;
    printf("BIENVENIDO\n");
    printf("\n");
    mostrarMenuPrincipal();
    opcion = pedirEntero("\nIntroduzca una opcion: ", "\nOpcion invalida, introduzca una opcion: ", 1, 7);
    return opcion;
}

void menuBajaPelicula(ePelicula listadoPeliculas[], int cantidadPeliculas)
{
    int id;
    int indice;
    id = pedirEntero("\nIntroduzca la id a buscar: ", "\nError id invalida. Introduzca la id a buscar: ", 1, 1000);
    indice = buscarPorId_ePelicula(listadoPeliculas, cantidadPeliculas, id);
    if(indice > -1)
    {
        baja_ePelicula(listadoPeliculas, cantidadPeliculas, indice);
    }else
    {
        printf("\nId inexistente.\n");
    }
}

void menuModificarPelicula(ePelicula listadoPeliculas[], int cantidadPeliculas, eDirector listadoDirectores[], int cantidadDirectores)
{
    int opcion;
    int id;
    int indice;
    id = pedirEntero("\nIntroduzca la id a buscar: ", "\nError id invalida. Introduzca la id a buscar: ", 1, 1000);
    indice = buscarPorId_ePelicula(listadoPeliculas, cantidadPeliculas, id);
    if(indice > -1)
    {
        printf("\n");
        mostrarMenuModificar();
        opcion = pedirEntero("\nIntroduzca una opcion: ", "\nOpcion invalida, introduzca una opcion: ", 1, 4);
        modificar_ePelicula(listadoPeliculas, cantidadPeliculas, listadoDirectores, cantidadDirectores, opcion, indice);
        printf("\n");
    }else
    {
        printf("\nId inexistente.\n");
    }
}

void menuBajaDirector(eDirector listadoDirectores[], int cantidadDirectores, ePelicula listadoPeliculas[], int cantidadPeliculas)
{
    char nombreAuxiliar[TAM_NOMBRE_DIRECTOR];
    int indice;
    int indicePelicula;
    pedirArrayLetrasConEspacio(nombreAuxiliar, TAM_NOMBRE_DIRECTOR, "Introduzca el nombre del director:\n",
    "Error nombre invalido. Introduzca el nombre nuevamente:\n");
    capitalizarArrayLetras(nombreAuxiliar);
    indice = buscarNombre_eDirector(listadoDirectores, cantidadDirectores, nombreAuxiliar);
    if(indice > -1)
    {
        baja_eDirector(listadoDirectores, cantidadDirectores, indice);
        if(contarAltas_ePelicula(listadoPeliculas, cantidadPeliculas) > 0)
        {
            for(indicePelicula = 0; indicePelicula < cantidadPeliculas; indicePelicula++)
            {
                if(strcmp(listadoPeliculas[indicePelicula].director, listadoDirectores[indice].nombre) == 0)
                {
                    listadoPeliculas[indicePelicula].estado = LIBRE;
                }
            }
        }
    }else
    {
        printf("\nDirector no encontrado.\n");
    }
}

void menuListar(ePelicula listadoPeliculas[], int cantidadPeliculas, eDirector listadoDirectores[], int cantidadDirectores)
{
    int opcion;
    mostrarMenuListar();
    opcion = pedirEntero("\nIntroduzca una opcion: ", "\nOpcion invalida, introduzca una opcion: ", 1, 2);
    printf("\n");
    switch(opcion)
    {
        case 1:
            if(contarAltas_ePelicula(listadoPeliculas, cantidadPeliculas) > 0)
            {
                mostrarListado_ePelicula(listadoPeliculas, cantidadPeliculas);
            }else
            {
                printf("\nNo se ha ingresado una pelicula todavia.\n");
            }
            break;
        case 2:
            mostrarListado_eDirector(listadoDirectores, cantidadDirectores);
            break;
    }
}
