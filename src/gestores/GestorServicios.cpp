#include "gestores/GestorServicios.hpp"
#include "modelos/Diagnostico.hpp"
#include "modelos/Reparacion.hpp"
#include "modelos/MantenimientoPreventivo.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

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
bool GestorServicios::agregarServicio(ServicioTecnico* servicio) {

    // Si el puntero es nulo, se niega el proceso.
    if (servicio == nullptr) {
        return false;
    }

    // Si ya existe un servicio con la misma identificacion, se niega el proceso.
    if (buscarPorIdentificacion(servicio->getIdentificacionServicio()) != nullptr) {
        std::cout << "ERROR. Ya existe un servicio con esa identificacion." << std::endl;
        return false;
    }

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

    return true;
}

// Busca un servicio mediante su ID.
ServicioTecnico* GestorServicios::buscarPorIdentificacion(const std::string& identificacion) const {

    // Se recorre todo el arreglo.
    for (int i = 0; i < cantidad; i++) {

        // Se compara la identificacion buscada con la del servicio.
        if (servicios[i]->getIdentificacionServicio() == identificacion) {

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
bool GestorServicios::eliminarServicio(const std::string& identificacion) {

    // Se busca el servicio.
    for (int i = 0; i < cantidad; i++) {

        if (servicios[i]->getIdentificacionServicio() == identificacion) {

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

// Guarda todos los servicios en un archivo de texto.
void GestorServicios::guardarArchivo(std::string nombreArchivo) const {
    std::ofstream archivo(nombreArchivo);
    if (archivo.is_open() == false) {
        std::cout << "ERROR. No se pudo abrir el archivo para guardar los servicios." << std::endl;
        return;
    }
    for (int i = 0; i < cantidad; i++) {
        archivo << servicios[i]->transformarArchivo() << std::endl;
    }
    archivo.close();
}

// Carga los servicios almacenados previamente en un archivo.
void GestorServicios::cargarArchivo(std::string nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (archivo.is_open() == false) {
        std::cout << "AVISO. No existe archivo previo de servicios, se inicia vacio." << std::endl;
        return;
    }
    std::string linea;
    while (std::getline(archivo, linea)) {
        if (linea == "") {
            continue;
        }
        std::stringstream flujo(linea);
        std::string tipo, identificacion, nombreServicio, descripcion, precioBaseTexto, duracionTexto, campoExtra1, campoExtra2;
        std::getline(flujo, tipo, '|');
        std::getline(flujo, identificacion, '|');
        std::getline(flujo, nombreServicio, '|');
        std::getline(flujo, descripcion, '|');
        std::getline(flujo, precioBaseTexto, '|');
        std::getline(flujo, duracionTexto, '|');
        std::getline(flujo, campoExtra1, '|');
        std::getline(flujo, campoExtra2, '|');

        double precioBase = std::stod(precioBaseTexto);
        int duracion = std::stoi(duracionTexto);

        ServicioTecnico* nuevoServicio = nullptr;

        if (tipo == "Diagnostico") {
            bool reporte;
            if (campoExtra2 == "1") {
                reporte = true;
            }
            else {
                reporte = false;
            }
            nuevoServicio = new Diagnostico(identificacion, nombreServicio, descripcion, precioBase, duracion, campoExtra1, reporte);
        }
        else if (tipo == "Reparacion") {
            nuevoServicio = new Reparacion(identificacion, nombreServicio, descripcion, precioBase, duracion, std::stod(campoExtra1), std::stod(campoExtra2));
        }
        else if (tipo == "MantenimientoPreventivo") {
            bool limpieza;
            if (campoExtra1 == "1") {
                limpieza = true;
            }
            else {
                limpieza = false;
            }
            bool pasta;
            if (campoExtra2 == "1") {
                pasta = true;
            }
            else {
                pasta = false;
            }
            nuevoServicio = new MantenimientoPreventivo(identificacion, nombreServicio, descripcion, precioBase, duracion, limpieza, pasta);
        }

        if (nuevoServicio != nullptr) {
            agregarServicio(nuevoServicio);
        }
    }
    archivo.close();
}
