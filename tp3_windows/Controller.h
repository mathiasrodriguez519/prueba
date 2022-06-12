int controller_loadFromText(char* path , LinkedList* pArrayListPassenger);
int controller_loadFromBinary(char* path , LinkedList* pArrayListPassenger);
int controller_addPassenger(LinkedList* pArrayListPassenger, int contadorBorrados, int contadorBorradosDespuesDeGuardar, int contadorLista, int usoGuardarPeroNoCargar, int ultimoId, int cargarDatos);
int controller_corregirId(LinkedList* pArrayListPassenger, int cantPasajerosAgregados);
int controller_editPassenger(LinkedList* pArrayListPassenger);
int controller_removePassenger(LinkedList* pArrayListPassenger);
int controller_ListPassenger(LinkedList* pArrayListPassenger);
int controller_sortPassenger(LinkedList* pArrayListPassenger);
int controller_saveAsText(char* path , LinkedList* pArrayListPassenger, int abiertoPreviamente);
int controller_saveAsBinary(char* path , LinkedList* pArrayListPassenger, int abiertoPreviamente);
int controller_controlarId(char* path, LinkedList* pArrayListPassenger, int cantAgregados, int cantBorrados, int *pUltimoId);
void controller_controlarRepetidos(LinkedList* pArrayListPassenger, int cantAgregados);


