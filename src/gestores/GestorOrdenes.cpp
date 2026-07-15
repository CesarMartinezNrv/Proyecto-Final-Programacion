#include "gestores/GestorOrdenes.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

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
bool GestorOrdenes::agregarOrden(OrdenServicio* orden) {
    // Si el puntero es nulo, se niega el proceso.
    if (orden == nullptr) {
        return false;
    }
    // Si ya existe una orden con la misma identificacion, se niega el proceso.
    if (buscarPorIdentificacion(orden->getIdentificacionOrden()) != nullptr) {
        std::cout << "ERROR. Ya existe una orden con esa identificacion." << std::endl;
        return false;
    }
    // Si el arreglo está lleno,
    // primero se aumenta su tamaño.
    if (cantidad == capacidad) {
        redimensionar();
    }
    ordenes[cantidad] = orden;
    cantidad++;
    return true;
}
// Busca una orden utilizando su ID.
OrdenServicio* GestorOrdenes::buscarPorIdentificacion(const std::string& identificacion) const {
    for (int i = 0; i < cantidad; i++) {
        if (ordenes[i]->getIdentificacionOrden() == identificacion) {
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
bool GestorOrdenes::actualizarEstado(const std::string& identificacionOrden,
                                     const std::string& nuevoEstado) {
    // Primero se busca la orden.
    OrdenServicio* orden = buscarPorIdentificacion(identificacionOrden);
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

// Guarda todas las ordenes en un archivo de texto.
void GestorOrdenes::guardarArchivo(std::string nombreArchivo) const {
    std::ofstream archivo(nombreArchivo);
    if (archivo.is_open() == false) {
        std::cout << "ERROR. No se pudo abrir el archivo para guardar las ordenes." << std::endl;
        return;
    }
    for (int i = 0; i < cantidad; i++) {
        archivo << ordenes[i]->transformarArchivo() << std::endl;
    }
    archivo.close();
}

// Carga las ordenes almacenadas previamente en un archivo,
// enlazandolas con los clientes, tecnicos, dispositivos
// y servicios ya cargados en sus respectivos gestores.
void GestorOrdenes::cargarArchivo(std::string nombreArchivo, GestorClientes& gestorClientes, GestorTecnicos& gestorTecnicos, GestorDispositivos& gestorDispositivos, GestorServicios& gestorServicios) {
    std::ifstream archivo(nombreArchivo);
    if (archivo.is_open() == false) {
        std::cout << "AVISO. No existe archivo previo de ordenes, se inicia vacio." << std::endl;
        return;
    }
    std::string linea;
    while (std::getline(archivo, linea)) {
        if (linea == "") {
            continue;
        }
        std::stringstream flujo(linea);
        std::string identificacionOrden, fecha, problema, diagnosticoTexto, estadoTexto, identificacionCliente, identificacionDispositivo, identificacionServicio, identificacionTecnico;
        std::getline(flujo, identificacionOrden, '|');
        std::getline(flujo, fecha, '|');
        std::getline(flujo, problema, '|');
        std::getline(flujo, diagnosticoTexto, '|');
        std::getline(flujo, estadoTexto, '|');
        std::getline(flujo, identificacionCliente, '|');
        std::getline(flujo, identificacionDispositivo, '|');
        std::getline(flujo, identificacionServicio, '|');
        std::getline(flujo, identificacionTecnico, '|');

        Cliente* cliente = gestorClientes.buscarPorIdentificacion(identificacionCliente);
        Dispositivo* dispositivo = gestorDispositivos.buscar(identificacionDispositivo);
        ServicioTecnico* servicio = gestorServicios.buscarPorIdentificacion(identificacionServicio);

        if (cliente == nullptr || dispositivo == nullptr || servicio == nullptr) {
            std::cout << "AVISO. No se pudo restaurar la orden " << identificacionOrden << " porque falta un cliente, dispositivo o servicio relacionado." << std::endl;
            continue;
        }

        OrdenServicio* nuevaOrden = new OrdenServicio(identificacionOrden, fecha, problema, cliente, dispositivo, servicio);
        nuevaOrden->registrarDiagnostico(diagnosticoTexto);
        nuevaOrden->setEstado(estadoTexto);

        if (identificacionTecnico != "") {
            Tecnico* tecnico = gestorTecnicos.buscarPorIdentificacion(identificacionTecnico);
            if (tecnico != nullptr) {
                nuevaOrden->asignarTecnico(tecnico);
            }
        }

        if (agregarOrden(nuevaOrden) == false) {
            delete nuevaOrden;
        }
    }
    archivo.close();
}
