#include "gestores/GestorServicios.hpp"
#include "modelos/Diagnostico.hpp"
#include "modelos/Reparacion.hpp"
#include "modelos/MantenimientoPreventivo.hpp"
#include <iostream>
#include <fstream>

// Constructor de la clase.
// Recibe una capacidad inicial para el arreglo dinámico.
GestorServicios::GestorServicios(int capacidadInicial) {

    // Se guarda la capacidad inicial del arreglo.
    capacidad = capacidadInicial;

    // Al inicio no existen servicios registrados.
    cantidad = 0;

    // Se reserva memoria dinámica para un arreglo de punteros
    // que almacenará objetos de tipo ServicioTecnico.
    servicios = new ServicioTecnico*[capacidad];
}

// Destructor.
// Se ejecuta automáticamente al destruir el objeto GestorServicios.
GestorServicios::~GestorServicios() {

    // Se elimina cada objeto ServicioTecnico creado con new.
    for (int i = 0; i < cantidad; i++) {
        delete servicios[i];
    }

    // Finalmente se libera el arreglo de punteros.
    delete[] servicios;
}

// Función privada encargada de aumentar la capacidad del arreglo.
void GestorServicios::redimensionar() {

    // Se duplica la capacidad actual.
    capacidad *= 2;

    // Se crea un nuevo arreglo con la nueva capacidad.
    ServicioTecnico** nuevo = new ServicioTecnico*[capacidad];

    // Se copian las direcciones de memoria de los servicios
    // del arreglo antiguo al nuevo.
    for (int i = 0; i < cantidad; i++) {
        nuevo[i] = servicios[i];
    }

    // Se elimina únicamente el arreglo viejo.
    // NO se eliminan los objetos porque siguen existiendo
    // y ahora son apuntados por el nuevo arreglo.
    delete[] servicios;

    // El puntero principal ahora apunta al nuevo arreglo.
    servicios = nuevo;
}

// Agrega un nuevo servicio al gestor.
void GestorServicios::agregarServicio(ServicioTecnico* servicio) {

    // Si el arreglo está lleno,
    // primero se aumenta su capacidad.
    if (cantidad == capacidad) {
        redimensionar();
    }

    // Se guarda el puntero al nuevo servicio
    // en la siguiente posición disponible.
    servicios[cantidad] = servicio;

    // Se incrementa el número de servicios registrados.
    cantidad++;
}

// Busca un servicio mediante su ID.
ServicioTecnico* GestorServicios::buscarPorId(const std::string& id) const {

    // Se recorre todo el arreglo.
    for (int i = 0; i < cantidad; i++) {

        // Se compara el ID buscado con el ID del servicio.
        if (servicios[i]->getIdServicio() == id) {

            // Si coincide, se devuelve el puntero encontrado.
            return servicios[i];
        }
    }

    // Si no existe ningún servicio con ese ID,
    // se devuelve nullptr.
    return nullptr;
}

// Muestra todos los servicios registrados.
void GestorServicios::listarServicios() const {

    // Si no hay servicios almacenados,
    // se informa al usuario.
    if (cantidad == 0) {
        std::cout << "No existen servicios registrados." << std::endl;
        return;
    }

    // Se recorre el arreglo.
    for (int i = 0; i < cantidad; i++) {

        // Gracias al polimorfismo, cada objeto ejecuta
        // su propia versión de mostrarInformacion().
        servicios[i]->mostrarInformacion();

        std::cout << std::endl;
    }
}

// Elimina un servicio utilizando su ID.
bool GestorServicios::eliminarServicio(const std::string& id) {

    // Se busca el servicio.
    for (int i = 0; i < cantidad; i++) {

        if (servicios[i]->getIdServicio() == id) {

            // Se libera la memoria del objeto encontrado.
            delete servicios[i];

            // Se recorren los elementos restantes
            // una posición hacia la izquierda para
            // evitar dejar espacios vacíos.
            for (int j = i; j < cantidad - 1; j++) {
                servicios[j] = servicios[j + 1];
            }

            // Se reduce la cantidad de elementos.
            cantidad--;

            // La eliminación fue exitosa.
            return true;
        }
    }

    // No se encontró el servicio solicitado.
    return false;
}

// Devuelve el número de servicios registrados.
int GestorServicios::getCantidad() const {

    return cantidad;
}
