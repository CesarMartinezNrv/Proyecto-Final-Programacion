#ifndef GESTORORDENES_H
#define GESTORORDENES_H
#include <string>
#include "modelos/OrdenServicio.hpp"
#include "gestores/GestorClientes.hpp"
#include "gestores/GestorTecnicos.hpp"
#include "gestores/GestorDispositivos.hpp"
#include "gestores/GestorServicios.hpp"

// Clase encargada de administrar todas las órdenes de servicio.
// Utiliza un arreglo dinámico de punteros.

class GestorOrdenes {

private:

    // Arreglo dinámico de punteros a OrdenServicio.
    OrdenServicio** ordenes;

    // Número de órdenes registradas.
    int cantidad;

    // Capacidad máxima del arreglo.
    int capacidad;

    // Aumenta el tamaño del arreglo cuando se llena.
    void redimensionar();

public:

    // Constructor.
    // Reserva memoria para el arreglo dinámico.
    GestorOrdenes(int capacidadInicial = 5);

    // Destructor.
    // Libera toda la memoria dinámica utilizada.
    ~GestorOrdenes();

    // Agrega una nueva orden.
    void agregarOrden(OrdenServicio* orden);

    // Busca una orden por su identificador.
    // Devuelve nullptr si no existe.
    OrdenServicio* buscarPorId(const std::string& id) const;

    // Muestra todas las órdenes registradas.
    void listarOrdenes() const;

    // Muestra únicamente las órdenes pendientes.
    void listarOrdenesPendientes() const;

    // Cambia el estado de una orden.
    // Devuelve true si se actualizó correctamente.
    bool actualizarEstado(const std::string& idOrden, const std::string& nuevoEstado);

    // Devuelve el número de órdenes almacenadas.
    int getCantidad() const;
};

#endif
