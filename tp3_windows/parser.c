#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Passenger.h"

/** \brief Parsea los datos los datos de los pasajeros desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int parser_PassengerFromText(FILE* pFile , LinkedList* pArrayListPassenger)
{
	int retorno = -1;

	if(pFile != NULL)
	{
		if(pArrayListPassenger != NULL)
		{
			Passenger* pasajeroNuevo;
			char id[DATOSTAM];
			char nombre[NOMBRESTAM];
			char apellido[NOMBRESTAM];
			char precio[DATOSTAM];
			char estadoVuelo[DATOSTAM];
			char tipoVuelo[DATOSTAM];
			char codigoVuelo[DATOSTAM];

			fscanf(pFile,"%[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]\n", id, nombre, apellido, precio, codigoVuelo, tipoVuelo, estadoVuelo);
			while(1)
			{
				if(fscanf(pFile,"%[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]\n", id, nombre, apellido, precio, codigoVuelo, tipoVuelo, estadoVuelo) == 7)
				{
					if(strcmp(tipoVuelo,"FirstClass") == 0)
					{
						strcpy(tipoVuelo, "1");
					}
					else
					{
						if(strcmp(tipoVuelo,"ExecutiveClass") == 0)
						{
							strcpy(tipoVuelo, "2");
						}
						else
						{
							strcpy(tipoVuelo, "3");
						}
					}

					pasajeroNuevo = Passenger_newParametros(id, nombre, tipoVuelo, apellido, precio, codigoVuelo, estadoVuelo);

					if(pasajeroNuevo != NULL)
					{
						ll_add(pArrayListPassenger, pasajeroNuevo);
						retorno = 0;
					}
				}

				if(feof(pFile) != 0)
				{
					break;
				}
			}
		}
	}

    return retorno;
}

/** \brief Parsea los datos los datos de los pasajeros desde el archivo data.bin (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int parser_PassengerFromBinary(FILE* pFile , LinkedList* pArrayListPassenger)
{
	int retorno = -1;

	if(pFile != NULL)
	{
		if(pArrayListPassenger != NULL)
		{
			while(1)
			{
				Passenger* pasajeroAux = Passenger_new();
				if(pasajeroAux != NULL)
				{
					if(fread(pasajeroAux, sizeof(Passenger), 1, pFile) != 0)
					{
						ll_add(pArrayListPassenger, pasajeroAux);

					}

					retorno = 0;
				}
				if(feof(pFile) != 0)
				{
					break;
				}
			}
		}
	}

    return retorno;
}
