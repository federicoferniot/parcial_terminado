#include "publicacion.h"
#include "cliente.h"

int informe_mostrarClientes(Cliente* clientes, Publicacion* publicaciones, int limite_cli, int limite_pub);
int informe_clienteMasAvisosActivos(Cliente* clientes, Publicacion* publicaciones, int limite_cli, int limite_pub);
int informe_clienteMasAvisosPausados(Cliente* clientes, Publicacion* publicaciones, int limite_cli, int limite_pub);
int informe_clienteMasAvisos(Cliente* clientes, Publicacion* publicaciones, int limite_cli, int limite_pub);
int informe_cantidadPublicacionesPorRubro(Publicacion* publicaciones, int limite);
int informe_rubroMasPublicacionesActivas(Publicacion* publicaciones, int limite);
int informe_rubroMenosPublicacionesActivas(Publicacion* publicaciones, int limite);
