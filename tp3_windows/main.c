#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Passenger.h"
#include "parser.h"
#include "UTN.h"

/****************************************************
    Menu:
     1. Cargar los datos de los pasajeros desde el archivo data.csv (modo texto).
     2. Cargar los datos de los pasajeros desde el archivo data.csv (modo binario).
     3. Alta de pasajero
     4. Modificar datos de pasajero
     5. Baja de pasajero
     6. Listar pasajeros
     7. Ordenar pasajeros
     8. Guardar los datos de los pasajeros en el archivo data.csv (modo texto).
     9. Guardar los datos de los pasajeros en el archivo data.csv (modo binario).
    10. Salir
*****************************************************/

int main()
{
	setbuf(stdout, NULL);

    int opcionMenu;
    int id = 0;
    int guardado = 1;
    int largo;
    int datosACargar = 0;
    int pasajerosAgregados = 0;
    int pasajerosBorrados = 0;
    int pasajerosAgregadosAntesDeGuardar = 0;
    int pasajerosBorradosDespuesDeGuardar = 0;
    int errorEdit;
    int errorRemover;
    int cantidadListaPasajeros = 0;
    int opcionSort;
    int ultimoId;

    LinkedList* listaPasajeros = ll_newLinkedList();

    do{
    	UTN_getInt(&opcionMenu,"\nMenu Principal:\n"
							"  1- Cargar los datos de los pasajeros desde el archivo data.csv (modo texto).\n"
							"  2- Cargar los datos de los pasajeros desde el archivo data.csv (modo binario).\n"
							"  3- Alta de pasajero.\n"
							"  4- Modificar datos de pasajero.\n"
							"  5- Baja de pasajero.\n"
							"  6- Listar pasajeros.\n"
							"  7- Ordenar pasajeros.\n"
							"  8- Guardar los datos de los pasajeros en el archivo data.csv (modo texto).\n"
							"  9- Guardar los datos de los pasajeros en el archivo data.csv (modo binario).\n"
							"  10- Salir.\n"
							"Ingrese una opcion: ", "\nError. Ingrese una opcion valida.\n", 1, 10);
    	largo = ll_len(listaPasajeros);

        switch(opcionMenu)
        {
            case 1:
            	if(datosACargar == 0)
            	{
					if(controller_loadFromText("data.csv",listaPasajeros) == 0)
					{
						datosACargar = 1;
						printf("\nLos datos han sido cargados exitosamente desde el modo texto.\n");
						if(pasajerosAgregados != 0 && id == 0)
						{
							if(controller_controlarId("data.csv", listaPasajeros, pasajerosAgregados, pasajerosBorrados, &ultimoId) != -1)
							{
								printf("\nSe corrigieron los id de los pasajeros agregados anteriormente correctamente.\n");
								id = 1;
							}
							else
							{
								printf("\nNo se pudieron corregir los id de los pasajeros agregados anteriormente.\n");
							}
						}
						else
						{
							controller_controlarRepetidos(listaPasajeros, pasajerosAgregadosAntesDeGuardar);
						}
					}
					else
					{
						printf("\nLos datos no se han podido cargar.\n");
					}
            	}
            	else
            	{
            		printf("\nYa cargó los datos.\n");
            	}
                break;

            case 2:
            	if(datosACargar == 0)
            	{
					if(controller_loadFromBinary("data.bin", listaPasajeros) == 0)
					{
						datosACargar = 1;
						printf("\nLos datos han sido cargados exitosamente desde el modo binario.\n");
						if(pasajerosAgregados != 0 && id == 0)
						{
							if(controller_controlarId("data.csv", listaPasajeros, pasajerosAgregados, pasajerosBorrados, &ultimoId) != -1)
							{
								printf("\nSe corrigieron los id de los pasajeros agregados anteriormente correctamente.\n");
								id = 1;
							}
							else
							{
								printf("\nNo se pudieron corregir los id de los pasajeros agregados anteriormente.\n");
							}
						}
						else
						{
							controller_controlarRepetidos(listaPasajeros, pasajerosAgregadosAntesDeGuardar);
						}
					}
					else
					{
						printf("\nLos datos no se han podido cargar.\n");
					}
            	}
            	else
            	{
            		printf("\nYa cargó los datos.\n");
            	}
            	break;

            case 3:
            	if(controller_addPassenger(listaPasajeros, pasajerosBorrados, pasajerosBorradosDespuesDeGuardar, cantidadListaPasajeros, id, ultimoId, datosACargar) == 0)
            	{
            		printf("\nSe ha agregado correctamente el pasajero.\n");
					guardado = 0;
					pasajerosAgregados++;
					if(datosACargar != 1)
					{
						pasajerosAgregadosAntesDeGuardar++;
					}
            	}
            	else
            	{
            		printf("\nNo se ha podido agregar al pasajero.\n");
            	}
            	printf("\nVolviendo al menu principal.\n");
				break;

            case 4:
            	if(largo != 0)
            	{
            		errorEdit = controller_editPassenger(listaPasajeros);
            		switch(errorEdit)
            		{
            		case -1:
            			printf("\nError. Se encontró un inconveniente en la lista.\n");
            			break;
            		case -2:
            			printf("Error. El id ingresado no coincide con ninguno en la lista\n");
            			break;
            		case -3:
            			printf("Error. Hubo un inconveniente al intentar obtener los datos del pasajero.\n");
            			break;
            		default:
            			guardado = 0;
            		}
            	}
            	else
            	{
            		printf("\nTodavía no ingresó ningún pasajero.\n");
            	}
            	printf("\nVolviendo al menu principal.\n");
				break;

            case 5:
            	errorRemover = controller_removePassenger(listaPasajeros);
            	switch(errorRemover)
            	{
            	case 0:
            		pasajerosBorrados++;
					printf("\nSe ha dado de baja correctamente al pasajero de la lista.\n");
					if(id == 2)
					{
						pasajerosBorradosDespuesDeGuardar++;
					}
					guardado = 0;
					break;
            	case -1:
            		printf("\nError. La lista se encuentra vacia.\n");
					break;

            	case -2:
            		printf("\nError. El id ingresado no coincide con ningun pasajero de la lista.\n");
            		break;

            	case -3:
            		printf("\nSe ha cancelado la bajada del pasajero de la lista.\n");
            		break;
            	}
            	printf("\nVolviendo al menu principal.\n");
				break;

            case 6:
            	if(controller_ListPassenger(listaPasajeros) != 0)
            	{
            		printf("\nError. La lista se encuentra vacía.\n");
					printf("\nVolviendo al menu principal.\n");
            	}
				break;

            case 7:
            	opcionSort = controller_sortPassenger(listaPasajeros);
            	switch(opcionSort)
            	{
            	case 1:
            		printf("\nSe ordenó correctamente los pasajeros por id.\n");
            		break;

            	case 2:
            		printf("\nSe ordenó correctamente los pasajeros por apellido.\n");
            		break;

            	case 3:
            		printf("\nSe ordenó correctamente los pasajeros por tipo de pasajero.\n");
            		break;

            	case 4:
            		printf("\nSe ordenó correctamente los pasajeros por codigo de vuelo.\n");
            		break;

            	default:
            		printf("\nError. No se pudo ordenar correctamente los pasajeros.\n");
            	}
				break;

            case 8:
                 printf("\nSe guardo con exito los datos de los pasajeros en el archivo data.csv (modo texto).\n");
                 guardado = 1;
                 if(datosACargar == 0)
                 {
                       controller_controlarId("data.csv", listaPasajeros, pasajerosAgregados, pasajerosBorrados, &ultimoId);
                 }
                 if(controller_saveAsText("data.csv", listaPasajeros, datosACargar) == 0)
                 {
            		    printf("\nSe guardo con exito los datos de los pasajeros en el archivo data.csv (modo texto).\n");
            			guardado = 1;
                 }
                 else
                 {
            			printf("\nError. No se pudo guardar los datos de los pasajeros en el archivo data.csv (modo texto).\n");
                 }
            	 break;

            case 9:
            	if(datosACargar == 0 && id == 0)
            	{
            		cantidadListaPasajeros = controller_controlarId("data.csv", listaPasajeros, pasajerosAgregados, pasajerosBorrados, &ultimoId);
            		if(cantidadListaPasajeros != -1)
            		{
            			id = 2;
            		}
            		else
            		{
            			printf("\nError.No se pudo corregir los id de los nuevos pasajeros ingresados al guardar.\n");
            		}
            	}
            	ll_sort(listaPasajeros, Passenger_sortById, 1);
            	if(controller_saveAsText("data.csv", listaPasajeros, datosACargar) == 0)
            	{
            		if(controller_saveAsBinary("data.bin", listaPasajeros, datosACargar) == 0)
            		{
						printf("\nSe guardo con exito los datos de los pasajeros en el archivo data.csv.\n");
						guardado = 1;
            		}
            	}
            	else
            	{
					printf("\nError. No se pudo guardar los datos de los pasajeros en el archivo data.csv.\n");
            	}
				break;

            default:
            	if(guardado == 0)
            	{
            		printf("\nError. No puede cerrar el sistema sin guardar los datos antes\n");
            	}
            	else
            	{
            		printf("\nCerrando sistema.\n");
            	}
        }
    }while(opcionMenu != 10 || guardado != 1);

    return 0;
}
