/*
 * ArrayPassenger.c
 *
 *  Created on: 10 may. 2022
 *      Author: mathi
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ArrayPassenger.h"
#include "UTN.h"

#define ESPACIOLIBRE 1
#define ESPACIOOCUPADO 0

int initPassengers(Passenger* list, int len)
{
	int retorno = -1;
	int i;

	if (list != NULL)
	{
		if (len >= 0)
		{
			for (i = 0; i < len; i++)
			{
				list[i].isEmpty = ESPACIOLIBRE;
			}
			retorno = 0;
		}
	}

	return retorno;
}

int addPassenger(Passenger* list, int len, int id, char name[],char lastName[],float price,int typePassenger, char flycode[], int statusFlight)
{
	int retorno = -1;
	Passenger aux;
	int espacioLibre;

	if (list != NULL)
	{
		if (len >= 0)
		{
			espacioLibre = encontrarEspacioVacio(list, len);
			if (espacioLibre >= 0)
			{
				aux.id = id;
				strcpy(aux.name, name);
				strcpy(aux.lastName, lastName);
				aux.price = price;
				strcpy(aux.flycode, flycode);
				aux.typePassenger = typePassenger;
				aux.isEmpty = ESPACIOOCUPADO;
				aux.statusFlight = statusFlight;

				list[espacioLibre] = aux;
				retorno = 0;
			}
		}
	}

	return retorno;
}

int encontrarEspacioVacio(Passenger* list, int len)
{
	int retorno = -1;
	int i;

	if (list != NULL)
	{
		if (len >= 0)
		{
			for (i = 0; i < len; i++)
			{
				if(list[i].isEmpty == ESPACIOLIBRE)
				{
					retorno = i;
					break;
				}
			}
		}
	}

	return retorno;
}

int findPassengerById(Passenger* list, int len,int id)
{
	int retorno = -1;

	if(list != NULL)
	{
		if(len >= 0)
		{
			for(int i = 0; i < len; i++)
			{
				if(list[i].id == id)
				{
					retorno = i;
					break;
				}
			}
		}
	}

	return retorno;
}

int removePassenger(Passenger* list, int len, int id)
{
	int retorno = -1;
	if(list != NULL)
	{
		if(len >= 0)
		{
			list[id].isEmpty = ESPACIOLIBRE;
			retorno = 0;
		}
	}
	return retorno;
}

int initStatusFlightAndTypePassenger(StatusFlightAndTypePassenger* statusType, int len)
{
	int retorno = -1;
	if (statusType != NULL)
	{
		if (len >= 0)
		{
			statusType[0].statusFlight = 1;
			strcpy(statusType[0].descriptionSF, "Activo");
			statusType[0].typePassenger = 1;
			strcpy(statusType[0].descriptionTP, "Menor");

			statusType[1].statusFlight = 2;
			strcpy(statusType[1].descriptionSF, "Inactivo");
			statusType[1].typePassenger = 2;
			strcpy(statusType[1].descriptionTP, "Adulto");

			statusType[2].statusFlight = 3;
			strcpy(statusType[2].descriptionSF, "Demorado");
			statusType[2].typePassenger = 3;
			strcpy(statusType[2].descriptionTP, "Anciano");

			retorno = 0;
		}
	}
	return retorno;
}

int sortPassengersByLastName(Passenger* list, int len, int order)
{
	int retorno = -1;
	Passenger aux;

	if (list != NULL)
	{
		if (len >= 0)
		{
			if (order == 1)
			{
				for (int i = 0; i < len; i++)
				{
					for(int j = i + 1; j < len - 1; j++)
					{
						if (strcmp(list[i].lastName, list[j].lastName) > 0)
						{
							aux = list[j];
							list[j] = list[i];
							list[i] = aux;
						}
						if(strcmp(list[i].lastName, list[j].lastName) == 0)
						{
							if(list[i].typePassenger > list[j].typePassenger)
							{
								aux = list[j];
								list[j] = list[i];
								list[i] = aux;
							}
						}
					}
				}
			}
			else
			{
				for (int i = 0; i < len; i++)
				{
					for(int j = i + 1; j < len - 1; j++)
					{
						if (strcmp(list[i].lastName, list[j].lastName) < 0)
						{
							aux = list[j];
							list[j] = list[i];
							list[i] = aux;
						}
						if(strcmp(list[i].lastName, list[j].lastName) == 0)
						{
							if(list[i].typePassenger > list[j].typePassenger)
							{
								aux = list[j];
								list[j] = list[i];
								list[i] = aux;
							}
						}
					}
				}
			}
			retorno = 0;
		}
	}

	return retorno;
}

int printPassenger(Passenger* list, StatusFlightAndTypePassenger* statusType ,int length, int lenStatusType)
{
	int retorno = -1;
	int i;

	if (list != NULL)
	{
		if (length >= 0)
		{
			printf("\nID     Nombre \t\t Apellido \t    Precio \t Codigo de Vuelo\tTipo de Pasajero \tEstado del vuelo\n");
			for (i = 0; i < length; i++)
			{
				if(list[i].isEmpty == ESPACIOOCUPADO)
				{
					for(int j = 0; j < lenStatusType; j++)
					{
						if(list[i].statusFlight == statusType[j].statusFlight)
						{
							for(int k = 0; k < lenStatusType; k++)
							{
								if(list[i].typePassenger == statusType[k].typePassenger)
								{
									printf("%-6d %-17s %-18s %-12.2f %-22s %-23s %s\n", list[i].id, list[i].name, list[i].lastName,
												list[i].price, list[i].flycode, statusType[k].descriptionTP, statusType[j].descriptionSF);
									break;
								}
							}
							break;
						}
					}
					retorno = 0;
				}
			}
		}
	}

	return retorno;
}

int sortPassengersByCode(Passenger* list, int len, int order)
{
	Passenger aux;
	int retorno = -1;

	if (list != NULL)
		{
			if (len >= 0)
			{
				if (order == 1)
				{
					for (int i = 0; i < len; i++)
					{
						for(int j = i + 1; j < len - 1; j++)
						{
							if (strcmp(list[i].flycode, list[j].flycode) > 0)
							{
								aux = list[j];
								list[j] = list[i];
								list[i] = aux;
							}
							if(strcmp(list[i].flycode, list[j].flycode) == 0)
							{
								if(list[i].statusFlight > list[j].statusFlight)
								{
									aux = list[j];
									list[j] = list[i];
									list[i] = aux;
								}
							}
						}
					}
				}
				else
				{
					for (int i = 0; i < len; i++)
					{
						for(int j = i + 1; j < len - 1; j++)
						{
							if (strcmp(list[i].flycode, list[j].flycode) < 0)
							{
								aux = list[j];
								list[j] = list[i];
								list[i] = aux;
							}
							if(strcmp(list[i].flycode, list[j].flycode) == 0)
							{
								if(list[i].statusFlight > list[j].statusFlight)
								{
									aux = list[j];
									list[j] = list[i];
									list[i] = aux;
								}
							}
						}
					}
				}
				retorno = 0;
			}
		}

	return retorno;
}

int modificarPasajero(Passenger* list, int len, int i, int opcion)
{
	int retorno = -1;
	char nombreNuevo[51];
	float precioNuevo;
	int nuevoTipoDePasajero;

	if (list != NULL)
	{
		if (len >= 0)
		{
			switch(opcion)
			{
				case 1:
					UTN_getName(nombreNuevo, "Ingrese el nuevo nombre: ",
							"Error, ingrese el nombre correctamente.\n");
					strcpy(list[i].name, nombreNuevo);
					break;
				case 2:
					UTN_getName(nombreNuevo, "Ingrese el nuevo apellido: ",
							"Error, ingrese el apellido correctamente.\n");
					strcpy(list[i].lastName, nombreNuevo);
					break;
				case 3:
					UTN_getFloat(&precioNuevo, "Ingrese el nuevo precio del vuelo: ",
							"Error, ingrese un dato valido.\n", 1, 999999999999999);
					list[i].price = precioNuevo;
					break;
				case 4:
					UTN_getInt(&nuevoTipoDePasajero, "Ingrese 1 si el vuelo se encuentra Activo, 2 si esta Inactivo o 3 si se encuentra Demorado: "
					, "Error, ingrese una opción valida.\n", 1, 3);
					list[i].typePassenger = nuevoTipoDePasajero;
					break;
				default:
					UTN_getflycode(list[i].flycode, "Ingrese el nuevo codigo del vuelo: ");
			}
			retorno = 0;
		}
	}
	return retorno;
}

int promedioPasajero(Passenger* list, int len, float* totalPrice, float* promedio)
{
	int retorno = -1;
	int contador = 0;
	float precioTotal;

	if(list != NULL)
	{
		if(len > 0)
		{
			for(int i = 0; i < len; i++)
			{
				if(list[i].isEmpty == ESPACIOOCUPADO && list[i].price >= 0)
				{
					contador++;
					precioTotal+= list[i].price;
					retorno = 0;
				}
			}
		}
	}
	*promedio = precioTotal / contador;
	*totalPrice = precioTotal;

	return retorno;
}

int sobrePrecio(Passenger* list, int len, float promedio)
{
	int retorno = -1;
	int contador = 0;

	if(list != NULL)
	{
		if(len > 0)
		{
			for(int i = 0; i < len; i++)
			{
				if(list[i].isEmpty == ESPACIOOCUPADO && list[i].price > promedio)
				{
					contador++;
					retorno = contador;
				}
			}
		}
	}

	return retorno;
}
