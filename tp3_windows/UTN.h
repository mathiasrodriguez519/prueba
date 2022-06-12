/*
 * UTN.h
 *
 *  Created on: 07 jun. 2022
 *      Author: mathi
 */

#ifndef UTN_H_
#define UTN_H_

/// @brief Le pide al usuario que ingrese el codigo del vuelo
///
/// @param codigoDeVuelo puntero que devuelve el codigo de vuelo ingresado
/// @param mensaje mensaje que donde se imprime la peticion
void UTN_getflycode(char codigoDeVuelo[10], char* mensaje);

/// @brief pide al usuario un dato a traves de string y cambia el ultimo bit de '\n' a '\0'
///
/// @param cadena puntero por donde se devuelve el string obtenido
/// @param longitud tama�o del string
/// @return devuelve -1 si hubo un error - 0 si esta ok

int myGets(char* cadena, int longitud);

/// @brief transforma el string obtenido de chequearNumero y myGets a un entero
///
/// @param pResultado puntero por donde se devuelve el entero obtenido
/// @return devuelve -1 si hubo un error en esta funcion o en alguna de las anteriores - 0 si esta ok

int tomarEntero(int* pResultado);

/// @brief recorre el string para verificar que todos sus digitos sean numericos
///
/// @param cadena puntero por donde devuelve el string analizado
/// @return devuelve 0 si hubo un error o si se encontro algun digito que no es numerico - 1 si esta ok

int chequearNumero(char* cadena);

/// @brief pide al usuario que ingrese un entero usando tomarEntero, verifica que este dentro de los parametros establecidos
/// 	   y devuelve el entero generado
///
/// @param pResultado puntero por el cual devuelve el entero generado
/// @param mensaje mensaje que se imprime para pedir el dato al usuario
/// @param mensajeError mensaje que se imprime si no se ingresa un entero
/// @param minimo parametro que delimita el numero minimo a ingresar
/// @param maximo parametro que delimita el numero maximo a ingresar
/// @return devuelve -1 si hubo un error - 0 si esta ok

int UTN_getInt(int *pResultado, char *mensaje, char *mensajeError, int minimo, int maximo);

/// @brief verifica el string obtenido de chequearNumero y myGets
///
/// @param pResultado pResultado puntero por donde se devuelve el string obtenido
/// @return devuelve -1 si hubo un error en esta funcion o en alguna de las anteriores - 0 si esta ok

int tomarFloat(char *pResultado);

/// @brief pide al usuario que ingrese un flotante usando tomarFloat, verifica que este dentro de los parametros establecidos
/// 	   y duevle el string generado
///
/// @param pResultado puntero por el cual devuelve el string generado
/// @param mensaje mensaje que se imprime para pedir el dato al usuario
/// @param mensajeError mensaje que se imprime si no se ingresa un flotante
/// @return devuelve -1 si hubo un error - 0 si esta ok

int UTN_getFloat(char *pResultado, char *mensaje, char *mensajeError);

/// @brief pide al usuario que ingrese un nombre, verifica que no se hayan ingresados caracteres
/// 	   que no sean letras y devuelve el nombre generado
///
/// @param cadena puntero por donde se devuelve el nombre generado
/// @param mensaje mensaje que se imprime para pedirle al usuario que ingrese el dato
/// @param mensajeError mensaje que se imprime si hay caracteres que no son letras
/// @return devuelve -1 si hubo un error - 0 si esta ok

int UTN_getName(char* cadena, char* mensaje, char* mensajeError);

/// @brief transforma toda la cadena a minuscula y solo pasa a mayuscula la inicial de cada nombre ingresado
///
/// @param cadena puntero por el cual devuelve la cadena con las mayusculas corregidas

void chequearMayuscula(char* cadena);

#endif /* UTN_H_ */
