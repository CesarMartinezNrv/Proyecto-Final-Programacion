#include "gestores/GestorOrdenes.hpp"
#include <iostream>
#include <fstream>

// Constructor.
// Inicializa el arreglo dinámico de órdenes.

GestorOrdenes::GestorOrdenes(int capacidadInicial) {
    capacidad = capacidadInicial;
    cantidad = 0;
    // Reserva memoria para el arreglo de punteros.
    ordenes = new OrdenServicio*[capacidad];
}
// Destructor.
// Libera toda la memoria utilizada.
GestorOrdenes::~GestorOrdenes() {
    // Elimina cada objeto OrdenServicio.
    for (int i = 0; i < cantidad; i++) {
        delete ordenes[i];
    }
    // Libera el arreglo de punteros.
    delete[] ordenes;
}
// Duplica la capacidad del arreglo.
void GestorOrdenes::redimensionar() {
    capacidad *= 2;
    // Se crea un nuevo arreglo más grande.
    OrdenServicio** nuevo = new OrdenServicio*[capacidad];
    // Se copian todas las direcciones.
    for (int i = 0; i < cantidad; i++) {
        nuevo[i] = ordenes[i];
    }
    // Se elimina el arreglo antiguo.
    delete[] ordenes;
    // El puntero principal apunta al nuevo arreglo.
    ordenes = nuevo;
}
// Agrega una nueva orden al gestor.
void GestorOrdenes::agregarOrden(OrdenServicio* orden) {
    // Si el arreglo está lleno,
    // primero se aumenta su tamaño.
    if (cantidad == capacidad) {
        redimensionar();
    }
    ordenes[cantidad] = orden;
    cantidad++;
}
// Busca una orden utilizando su ID.
OrdenServicio* GestorOrdenes::buscarPorId(const std::string& id) const {
    for (int i = 0; i < cantidad; i++) {
        if (ordenes[i]->getIdOrden() == id) {
            return ordenes[i];
        }
    }
    return nullptr;
}
// Muestra todas las órdenes registradas.
void GestorOrdenes::listarOrdenes() const {
    if (cantidad == 0) {
        std::cout << "No existen órdenes registradas." << std::endl;
        return;
    }
    for (int i = 0; i < cantidad; i++) {
        ordenes[i]->mostrarInformacion();
        std::cout << std::endl;
    }
}
// Muestra únicamente las órdenes cuyo estado es "Pendiente".
void GestorOrdenes::listarOrdenesPendientes() const {
    for (int i = 0; i < cantidad; i++) {
        if (ordenes[i]->getEstado() == "Pendiente") {
            ordenes[i]->mostrarInformacion();
            std::cout << std::endl;
        }
    }
}
// Actualiza el estado de una orden.
bool GestorOrdenes::actualizarEstado(const std::string& idOrden,
                                     const std::string& nuevoEstado) {
    // Primero se busca la orden.
    OrdenServicio* orden = buscarPorId(idOrden);
    // Si existe, se cambia el estado.
    if (orden != nullptr) {
        orden->setEstado(nuevoEstado);
        return true;
    }
    // Si no existe, devuelve false.
    return false;
}
// Devuelve el número de órdenes almacenadas.
int GestorOrdenes::getCantidad() const {
    return cantidad;
}
