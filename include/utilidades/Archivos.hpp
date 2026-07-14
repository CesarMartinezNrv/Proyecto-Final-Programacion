#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include <string>

// Clase encargada de administrar la lectura
// y escritura de la información en archivos de texto.
class Archivos{

public:

    // Guarda y carga la información de los clientes
    void guardarClientes();
    void cargarClientes();

    // Guarda y carga la información de los técnicos
    void guardarTecnicos();
    void cargarTecnicos();

    // Guarda y carga la información de los dispositivos
    void guardarDispositivos();
    void cargarDispositivos();

    // Guarda y carga la información de los servicios
    void guardarServicios();
    void cargarServicios();

    // Guarda y carga la información de las órdenes de servicio
    void guardarOrdenes();
    void cargarOrdenes();

    // Destructor
    ~Archivos();

};

#endif
