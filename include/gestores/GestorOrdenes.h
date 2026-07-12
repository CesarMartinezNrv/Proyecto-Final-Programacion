#ifndef GESTORORDENES_H
#define GESTORORDENES_H
#include <string>
#include "OrdenServicio.h"

class GestorOrdenes{

private:

    OrdenServicio** ordenes;
    int cantidad;
    int capacidad;

    void redimensionar();

public:

    GestorOrdenes(int capacidadInicial = 10);

    void agregarOrden(OrdenServicio* orden);

    OrdenServicio* buscarPorId(std::string id) const;

    void listarOrdenes() const;

    void listarOrdenesPendientes() const;

    void actualizarEstado(std::string idOrden,  std::string nuevoEstado);

    ~GestorOrdenes();

};

#endif