/*
 ============================================================================
 Name        : TP1.c
 Author      : RUBEN DARIO ZEVALLOS LAMBRESCHT
 Version     : 1 DIVISON H
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

#ifdef __linux__
#define SO "Linux"
#define LIMPIAR_CONSOLA system("clear");
#define LIMPIAR_BUFFER __fpurge(stdin);
#include <stdio_ext.h>
#elif _WIN32
#define SO "Windows"
#define LIMPIAR_CONSOLA system("cls");
#define LIMPIAR_BUFFER fflush(stdin);
#define LIMPIAR_SALIDA	setbuf(stdout, NULL);
#elif __APPLE__
#define SO "OSX"
#define LIMPIAR_CONSOLA system("clear");
#define LIMPIAR_BUFFER fpurge(stdin);
#endif





#define DEBITO 0
#define CREDITO 1
#define BTC 2
#define PRECIOBTC 4606954.55
#define PRECIO_FORZADO_AA 162965
#define PRECIO_FORZADO_LT 159339
#define DISTANCIA_FORZADA 7090
int main(void) {
	#ifdef _WIN32
		LIMPIAR_SALIDA
	#endif
	int opcion;
	int cantidadKilometros;
	cantidadKilometros = 0;
	float precioAA;
	precioAA = 0;
	float precioLT;
	precioLT = 0;
	float debitoAA;
	float debitoLT;
	float creditoAA;
	float creditoLT;
	float btcAA;
	float btcLT;
	float precioUnitarioAA;
	float precioUnitarioLT;
	int valido; // variable para validar que tengo todos los valores cargados antes de calcular
	valido = -1;
	do
	{//creacion del menu principal
		printf("Bienvenidos al TP1 Alumno: Zevallos Lambrescht Ruben Division 1ºH\n");
		printf("1. Ingresar Kilometros: (km=%d)\n",cantidadKilometros);
		printf("2. Ingresar Precio de Vuelos: (Aerolineas=%.2f, Latam=%.2f\n", precioAA, precioLT);
		printf("3. Calcular todos los costos:\n");
		printf("4. Informar Resultados\n");
		printf("5. Carga forzada de datos\n");
		printf("6. Salir\n");
		#ifdef __linux__
			LIMPIAR_BUFFER
		#elif _WIN32
			LIMPIAR_BUFFER
		#elif __APPLE__
		LIMPIAR_BUFFER
		#endif
		//solicito opcion del menu para interactuar
		utn_getNumeroInt(&opcion, "Ingrese opcion deseada\n", "Opcion invalida\n", 1, 6, 2);
		switch (opcion)
		{
		case 1: // solicitar cantidad de kilometros
			if(!utn_getNumeroInt(&cantidadKilometros, "Ingrese la cantidad de Km del viaje: \n", "Valor Inválido\n", 0, 20000, 2))
			{
				valido = 0; //si salio bien la validacion
			}
			else
			{
				valido = 1; //si salio mal la validacion
			}
			break;
		case 2:

			if(!utn_getNumeroFloat(&precioAA, "Precio vuelo Aerolineas:\n" , "Valor incorrecto, se espera valores positivos.\n", 0, 1500000, 3))
			{
				valido = 0; //si salio bien la validacion
			}
			else
			{
				valido = 2; //si salio mal la validacion
			}
			if(!utn_getNumeroFloat(&precioLT, "Precio vuelo Latam:\n" , "Valor incorrecto, se espera valores positivos.\n", 0, 1500000, 3))
			{
				valido = 0; //si salio bien la validacion
			}
			else
			{
				valido = 3; //si salio mal la validacion
			}
			break;
		case 3:
			switch (valido)
			{
				case 0:
					//realizo los calculos para aerolineas
					if(!calculoPrecio(precioAA ,DEBITO ,&debitoAA, PRECIOBTC) && !calculoPrecio(precioAA,CREDITO , &creditoAA, PRECIOBTC) && !calculoPrecio(precioAA,BTC, &btcAA, PRECIOBTC))
					{
						precioUnitarioAA=precioAA/cantidadKilometros;
					}
					//realizo los calculos para latam
					if(!calculoPrecio(precioLT ,DEBITO ,&debitoLT, PRECIOBTC) && !calculoPrecio(precioLT,CREDITO , &creditoLT, PRECIOBTC) && !calculoPrecio(precioLT,BTC, &btcLT, PRECIOBTC))
					{
						precioUnitarioLT=precioLT/cantidadKilometros;
					}
					break;
				case 1:
					//mensaje de error si hay un dato no valido en los km del vuelo
					printf("Error en validacion distancia.\n");
					break;
				case 2:
					//mensaje de error si hay dificultades con el precio de AA
					printf("Error en validacion precio Aerolineas.\n");
					break;
				case 3:
					//mensaje de error si hay dificultades con el precio de LA
					printf("Error en validacion precio Latam.\n");
					break;
			}
			break;
		case 4://muestro los valores calcluados previamente validados
			if (valido==0)
			{
				menuOp4(cantidadKilometros,precioAA, precioLT, debitoAA, creditoAA, btcAA, precioUnitarioAA, debitoLT, creditoLT, btcLT, precioUnitarioLT);
			}
			else
			{
				printf("No se puede mostrar los valores si peviamente no se cargaron los valores necesarios\n");
			}
			break;
		case 5:
			//carga forzada, realizando los calculos con los parametros indicados en el enunciado
			calculoPrecio(PRECIO_FORZADO_AA ,DEBITO ,&debitoAA, PRECIOBTC);
			calculoPrecio(PRECIO_FORZADO_AA,CREDITO , &creditoAA, PRECIOBTC);
			calculoPrecio(PRECIO_FORZADO_AA,BTC, &btcAA, PRECIOBTC);
			precioUnitarioAA=PRECIO_FORZADO_AA/(float)DISTANCIA_FORZADA;
			calculoPrecio(PRECIO_FORZADO_LT ,DEBITO ,&debitoLT, PRECIOBTC);
			calculoPrecio(PRECIO_FORZADO_LT,CREDITO , &creditoLT, PRECIOBTC);
			calculoPrecio(PRECIO_FORZADO_LT,BTC, &btcLT, PRECIOBTC);
			precioUnitarioLT=PRECIO_FORZADO_LT/(float)DISTANCIA_FORZADA;
			menuOp4(DISTANCIA_FORZADA,PRECIO_FORZADO_AA, PRECIO_FORZADO_LT, debitoAA, creditoAA, btcAA, precioUnitarioAA, debitoLT, creditoLT, btcLT, precioUnitarioLT);
			break;
		}
	}while(opcion != 6);

	return EXIT_SUCCESS;
}
