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
    // Devuelve true si fue agregada o false si el puntero
    // es nulo o ya existe una orden con la misma identificacion.
    bool agregarOrden(OrdenServicio* orden);

    // Busca una orden por su identificador.
    // Devuelve nullptr si no existe.
    OrdenServicio* buscarPorIdentificacion(const std::string& identificacion) const;

    // Muestra todas las órdenes registradas.
    void listarOrdenes() const;

    // Muestra únicamente las órdenes pendientes.
    void listarOrdenesPendientes() const;

    // Cambia el estado de una orden.
    // Devuelve true si se actualizó correctamente.
    bool actualizarEstado(const std::string& identificacionOrden, const std::string& nuevoEstado);

    // Devuelve el número de órdenes almacenadas.
    int getCantidad() const;

    // Guarda todas las ordenes en un archivo de texto.
    void guardarArchivo(std::string nombreArchivo) const;

    // Carga las ordenes almacenadas previamente en un archivo,
    // enlazandolas con los clientes, tecnicos, dispositivos
    // y servicios ya cargados en sus respectivos gestores.
    void cargarArchivo(std::string nombreArchivo, GestorClientes& gestorClientes, GestorTecnicos& gestorTecnicos, GestorDispositivos& gestorDispositivos, GestorServicios& gestorServicios);
};

#endif
