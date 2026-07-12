#ifndef ARCHIVOS_H
#define ARCHIVOS_H
#include <string>

class Archivos{

public:

    void guardarClientes();
    void cargarClientes();

    void guardarTecnicos();
    void cargarTecnicos();

    void guardarDispositivos();
    void cargarDispositivos();

    void guardarServicios();
    void cargarServicios();

    void guardarOrdenes();
    void cargarOrdenes();

    ~Archivos();

};

#endif