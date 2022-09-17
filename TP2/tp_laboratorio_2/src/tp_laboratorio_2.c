/*
 ============================================================================
 Name        : tp_laboratorio_2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ArrayPassenger.h"
#include "UTN.h"

#define PASAJEROSMAXIMOS 2000
#define TIPODEPASAJEROSENESTADODEVUELOMAXIMO 3

int main(void)
{
	int opcionMenu;
	int id = 0;
	char nombre[51];
	char apellido[51];
	float precio;
	char codigoDeVuelo[10];
	int estadoVuelo;
	int tipoDePasajero;
	int opcionMenuModificar;
	int opcionIdModificar;
	int idAModificar;
	int opcionMenuInformar;
	int opcionIdAEliminar;
	int idAEliminar;
	float precioTotal;
	float precioPromedio;
	int pasajerosArribaDelPromedio;

	Passenger listaDePasajeros[PASAJEROSMAXIMOS];
	StatusFlightAndTypePassenger estadoDelVueloYTipoDePasajero[TIPODEPASAJEROSENESTADODEVUELOMAXIMO];

	setbuf(stdout, NULL);

	if(initPassengers(listaDePasajeros, PASAJEROSMAXIMOS) != 0)
	{
		printf("\nError al inicializar la estructura Passenger.\n");
	}

	if(initStatusFlightAndTypePassenger(estadoDelVueloYTipoDePasajero, TIPODEPASAJEROSENESTADODEVUELOMAXIMO) != 0)
	{
		printf("\nError al inicializar la estructura StatusFlightAndTypePassenger.\n");
	}

	do
	{
		printf("\nMenu principal: \n"
				"1. ALTA de pasajero.\n"
				"2. MODIFICAR pasajero.\n"
				"3. BAJA de pasajero.\n"
				"4. INFORMAR.\n"
				"5. Carga forzada de datos.\n"
				"6. Salir del menu.\n"
				"Ingrese una opcion: ");
		fflush(stdin);
		scanf("%d",&opcionMenu);

		switch(opcionMenu)
		{
			case 1:
				id++;
				UTN_getName(nombre, "Ingrese el nombre: ", "Error. Ingrese el nombre correctamente.\n");
				UTN_getName(apellido, "Ingrese el apellido: ", "Error. Ingese el apellido correctamente.\n");
				UTN_getFloat(&precio, "Ingrese el precio del vuelo: ", "Error. Ingrese un dato valido.\n", 1, 999999999999999);
				UTN_getInt(&tipoDePasajero, "Ingrese 1 si es Menor (menos de 18 años), 2 si es Adulto(entre 18 y 60 años), 3 si es Anciano(mayor de 60 años): ",
						"Error. Ingrese una opción valida.\n", 1, 3);
				UTN_getflycode(codigoDeVuelo, "Ingrese el codigo del vuelo: ");
				UTN_getInt(&estadoVuelo, "Ingrese 1 si el vuelo se encuentra Activo, 2 si esta Inactivo o 3 si se encuentra Demorado: ",
						"Error. Ingrese una opción valida.\n",1,3);
				if(addPassenger(listaDePasajeros,  PASAJEROSMAXIMOS,  id,  nombre, apellido, precio, tipoDePasajero, codigoDeVuelo, estadoVuelo) == 0)
				{
					printf("\nSe agrego al pasajero con exito.\n");
				}
				else
				{
					printf("\nError al ingresar el pasajero.\n");
				}
				break;
			case 2:
				do
				{
					printf("\nMenu de modificaciones de datos del pasajero:\n"
							"1- Nombre.\n"
							"2- Apellido.\n"
							"3- Precio.\n"
							"4- Tipo de pasajero.\n"
							"5- Código del vuelo.\n"
							"6- Salir al menu.\n"
							"Ingrese una opcion: ");
					fflush(stdin);
					scanf("%d", &opcionMenuModificar);
					switch(opcionMenuModificar)
					{
						case 1:
						case 2:
						case 3:
						case 4:
						case 5:
							printf("Indique el ID del pasajero a modificar: ");
							fflush(stdin);
							scanf("%d", &opcionIdModificar);
							idAModificar = findPassengerById(listaDePasajeros, PASAJEROSMAXIMOS, opcionIdModificar);
							if (idAModificar > -1)
							{
								if(modificarPasajero(listaDePasajeros, PASAJEROSMAXIMOS, idAModificar, opcionMenuModificar) == 0)
								{
									printf("\nSe modifico al pasajero con exito.\n");
								}
								else
								{
									printf("\nError al intentar modificar el pasajero.\n");
								}
							}
							else
							{
								printf("\nError, ingrese un id ya cargado anteriormente.\n");
							}
							break;
						case 6:
							printf("\nVolviendo al menu.\n");
							break;
						default:
							printf("\nIngrese una opcion valida.\n");
					}
				}while(opcionMenuModificar != 6);
				break;
			case 3:
				printf("Ingrese el ID del pasajero que desea dar de baja: ");
				fflush(stdin);
				scanf("%d", &opcionIdAEliminar);
				idAEliminar = findPassengerById(listaDePasajeros, PASAJEROSMAXIMOS, opcionIdAEliminar);
				if (idAEliminar > -1)
				{
					if(removePassenger(listaDePasajeros, PASAJEROSMAXIMOS, idAEliminar) == 0)
					{
						printf("\nSe ha dado de baja con exito al pasajero.\n");
					}
					else
					{
						printf("\nHubo un error al intentar dar de baja al pasajero.\n");
					}
				}
				else
				{
					printf("\nEl ID ingresado no coincide con ningún pasajero de la lista.\n\n");
				}
				break;
			case 4:
				do
				{
					printf("\nMenú para informar pasajeros:\n"
							"1- Listado de pasajeros ordenados alfabéticamente por Apellido y Tipo de pasajero.\n"
							"2- Total y promedio de los precios de los pasajes, y cuántos pasajeros superan el precio promedio.\n"
							"3- Listado de los pasajeros por Código de vuelo y estados de vuelos 'ACTIVO'\n"
							"4- Volver al menú principal\n"
							"Elija una opción: ");
					fflush(stdin);
					scanf("%d",&opcionMenuInformar);
					switch(opcionMenuInformar)
					{
					case 1:
						if(sortPassengersByLastName(listaDePasajeros, PASAJEROSMAXIMOS, 1) == 0)
						{
							if(printPassenger(listaDePasajeros, estadoDelVueloYTipoDePasajero ,PASAJEROSMAXIMOS, TIPODEPASAJEROSENESTADODEVUELOMAXIMO) != 0)
							{
								printf("\nNo hay pasajeros cargados.\n");
							}
						}
						else
						{
							printf("\nNo se pudo ordenar a los pasajeros por apellido.\n");
						}
						break;
					case 2:
						if(promedioPasajero(listaDePasajeros, PASAJEROSMAXIMOS, &precioTotal, &precioPromedio) == 0)
						{
							pasajerosArribaDelPromedio = sobrePrecio(listaDePasajeros, PASAJEROSMAXIMOS, precioPromedio);
							printf("\nEl precio total de los vuelos es de $%.2f.\nEn promedio cada vuelo salio $%.2f."
								"\nEn total hay %d pasajeros que pagan por encima del promedio.\n", precioTotal, precioPromedio, pasajerosArribaDelPromedio);
						}
						else
						{
							printf("\nNo se pudieron realizar los calculos.\n");
						}
						break;
					case 3:
						if(sortPassengersByCode(listaDePasajeros, PASAJEROSMAXIMOS, 1) == 0)
						{
							if(printPassenger(listaDePasajeros, estadoDelVueloYTipoDePasajero ,PASAJEROSMAXIMOS, TIPODEPASAJEROSENESTADODEVUELOMAXIMO) != 0)
							{
								printf("\nLa lista de pasajeros esta vacia.\n");
							}
						}
						else
						{
							printf("\nNo se pudo ordenar a los pasajeros por codigo de vuelo.\n");
						}
						break;
					case 4:
						printf("\nVolviendo al menu.\n");
						break;
					default:
						printf("Ingrese una opcion valida.\n");
					}
				}while(opcionMenuInformar != 4);
				break;
			case 5:
				id++;
				addPassenger(listaDePasajeros, PASAJEROSMAXIMOS, id, "Mathias", "Rodriguez", 15601.23, 1, "PSLWE-53", 2);
				id++;
				addPassenger(listaDePasajeros, PASAJEROSMAXIMOS, id, "Nicolas", "Grillo", 24031.35, 1, "DWGT-13", 1);
				id++;
				addPassenger(listaDePasajeros, PASAJEROSMAXIMOS, id, "Emilia", "Lopez", 31150.50, 1, "BFSE-64", 3);
				id++;
				addPassenger(listaDePasajeros, PASAJEROSMAXIMOS, id, "Franco", "Rossi", 17164.31, 2, "QSHT-62", 3);
				id++;
				addPassenger(listaDePasajeros, PASAJEROSMAXIMOS, id, "Emilio", "Gonzalez", 30518, 1, "CSTI-34", 2);
				id++;
				addPassenger(listaDePasajeros, PASAJEROSMAXIMOS, id, "Lionel", "Messi", 32051.31, 2, "AALD-90", 1);
				id++;
				addPassenger(listaDePasajeros, PASAJEROSMAXIMOS, id, "Steph", "Curry", 19081, 3, "MXNC-12", 2);
				id++;
				addPassenger(listaDePasajeros, PASAJEROSMAXIMOS, id, "Iara", "Bosso", 25031.24, 3, "CSJH-18", 1);
				id++;
				addPassenger(listaDePasajeros, PASAJEROSMAXIMOS, id, "Ivan", "Maciel", 25151.13, 1, "TDGR-39", 1);
				id++;
				addPassenger(listaDePasajeros, PASAJEROSMAXIMOS, id, "Sandra", "Honorato", 33654.13, 2, "PLOK-68", 1);
				printf("\nCarga lista.\n");
				break;
			case 6:
				printf("\nSaliendo.\n");
				break;
			default:
				printf("\nIngrese una opcion valida.\n");
		}

	}while(opcionMenu != 6);

	return 0;
}
