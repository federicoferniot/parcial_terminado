#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "publicacion.h"
#include "utn.h"
#include "cliente.h"


/** \brief Muestra clientes y cantidad de publicaciones
 *
 * \param clientes Cliente*
 * \param publicaciones Publicacion*
 * \param limite_cli int
 * \param limite_pub int
 * \return int
 *
 */
int informe_mostrarClientes(Cliente* clientes, Publicacion* publicaciones, int limite_cli, int limite_pub)
{
    int retorno = -1;
    int i, cantidadPub;
    if(limite_cli > 0 && clientes != NULL)
    {
        retorno = 0;
        for(i=0;i<limite_cli;i++)
        {
            if(!clientes[i].isEmpty)
            {
                cantidadPub = pub_cantidadPublicacionesPorIdCliente(publicaciones, limite_pub, clientes[i].idCliente);
                printf(" Id: %d Nombre y Apellido: %s %s Cuit: %d Numero Publicaciones: %d\n",clientes[i].idCliente, clientes[i].nombre, clientes[i].apellido, clientes[i].cuit, cantidadPub);
            }
        }
    }
    return retorno;
}

/** \brief Informa clientes con maximo avisos activos
 *
 * \param clientes Cliente*
 * \param publicaciones Publicacion*
 * \param limite_cli int
 * \param limite_pub int
 * \return int
 *
 */
int informe_clienteMasAvisosActivos(Cliente* clientes, Publicacion* publicaciones, int limite_cli, int limite_pub)
{
    int retorno = -1;
    int i, idClienteMax=-1, auxCantPub;
    int maxPub;
    int primerCliente=0;
    if(limite_cli > 0 && clientes != NULL)
    {
        printf("\nMas avisos activos:\n");
        retorno = 0;
        for(i=0;i<limite_cli;i++)
        {
            if(!clientes[i].isEmpty)
            {
                if(primerCliente==0)
                {
                    maxPub = pub_cantidadPublicacionesPorIdCliente(publicaciones, limite_pub, clientes[i].idCliente);
                    if(maxPub>0)
                    {
                        idClienteMax = clientes[i].idCliente;
                        primerCliente=1;
                    }

                }
                else
                {
                    auxCantPub = pub_cantidadPublicacionesPorIdCliente(publicaciones, limite_pub, clientes[i].idCliente);
                    if(auxCantPub>maxPub)
                    {
                        maxPub=auxCantPub;
                        idClienteMax=clientes[i].idCliente;
                    }
                }
            }
        }
        if(idClienteMax!=-1)
        {
            cliente_mostrarPorId(clientes, limite_cli, idClienteMax);
        }
        else
        {
            printf("No se encontraron\n");
        }
    }
    return retorno;
}

int informe_clienteMasAvisosPausados(Cliente* clientes, Publicacion* publicaciones, int limite_cli, int limite_pub)
{
    int retorno = -1;
    int i, idClienteMax=-1, auxCantPub;
    int maxPub;
    int primerCliente=0;
    if(limite_cli > 0 && clientes != NULL)
    {
        retorno = 0;
        printf("\nMas avisos pausados:\n");
        for(i=0;i<limite_cli;i++)
        {
            if(!clientes[i].isEmpty)
            {
                if(primerCliente==0)
                {
                    maxPub = pub_cantidadPublicacionesPausadasPorIdCliente(publicaciones, limite_pub, clientes[i].idCliente);
                    if(maxPub>0)
                    {
                        idClienteMax = clientes[i].idCliente;
                        primerCliente=1;
                    }

                }
                else
                {
                    auxCantPub = pub_cantidadPublicacionesPorIdCliente(publicaciones, limite_pub, clientes[i].idCliente);
                    if(auxCantPub>maxPub)
                    {
                        maxPub=auxCantPub;
                        idClienteMax=clientes[i].idCliente;
                    }
                }
            }
        }
        if(idClienteMax!=-1)
        {
            cliente_mostrarPorId(clientes, limite_cli, idClienteMax);
        }
        else
        {
            printf("No se encontraron\n");
        }
    }
    return retorno;
}

int informe_clienteMasAvisos(Cliente* clientes, Publicacion* publicaciones, int limite_cli, int limite_pub)
{
    int retorno = -1;
    int i, idClienteMax=-1, auxCantPub;
    int maxPub;
    int primerCliente=0;
    if(limite_cli > 0 && clientes != NULL)
    {
        printf("\nMas avisos:\n");
        retorno = 0;
        for(i=0;i<limite_cli;i++)
        {
            if(!clientes[i].isEmpty)
            {
                if(primerCliente==0)
                {
                    maxPub = pub_cantidadPublicacionesPorIdCliente(publicaciones, limite_pub, clientes[i].idCliente);
                    idClienteMax = clientes[i].idCliente;
                    primerCliente=1;
                }
                else
                {
                    auxCantPub = pub_cantidadPublicacionesPorIdCliente(publicaciones, limite_pub, clientes[i].idCliente);
                    if(auxCantPub>maxPub)
                    {
                        maxPub=auxCantPub;
                        idClienteMax=clientes[i].idCliente;
                    }
                }
            }
        }
        if(idClienteMax!=-1)
        {
            cliente_mostrarPorId(clientes, limite_cli, idClienteMax);
        }
        else
        {
            printf("No se encontraron\n");
        }
    }
    return retorno;
}

int informe_cantidadPublicacionesPorRubro(Publicacion* publicaciones, int limite)
{
    int retorno=-1;
    int cantidadPublicaciones=0;
    int i,rubro;
    if(!getValidInt("\nRubro?", "\nNo es un rubro", &rubro, 0, 100, 2))
    {
        if(limite > 0 && publicaciones != NULL)
        {
            for(i=0;i<limite;i++)
            {
                if(!publicaciones[i].isEmpty && publicaciones[i].estado && publicaciones[i].numeroRubro == rubro)
                    cantidadPublicaciones++;
            }
        }
        printf("\nCantidad de publicaciones para el rubro: %d", cantidadPublicaciones);
    }
    return retorno;
}
