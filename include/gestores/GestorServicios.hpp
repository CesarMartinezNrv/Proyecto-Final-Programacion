#ifndef GESTORSERVICIOS_HPP
#define GESTORSERVICIOS_HPP
#include "modelos/ServicioTecnico.hpp"
#include <string>

// Clase encargada de administrar todos los servicios técnicos.
// Utiliza un arreglo dinámico de punteros para almacenar los servicios.
class GestorServicios {

private:

    // Arreglo dinámico de punteros a ServicioTecnico.
    // Cada posición apunta a un objeto derivado como Diagnostico,
    // Reparacion o MantenimientoPreventivo.
    ServicioTecnico** servicios;

    // Número actual de servicios almacenados.
    int cantidad;

    // Capacidad máxima del arreglo antes de redimensionarlo.
    int capacidad;

    // Función privada que aumenta el tamaño del arreglo
    // cuando ya no existe espacio disponible.
    void redimensionar();

public:

    // Constructor.
    // Recibe una capacidad inicial (por defecto es 5)
    // y reserva memoria para el arreglo dinámico.
    GestorServicios(int capacidadInicial = 5);

    // Destructor.
    // Libera toda la memoria dinámica utilizada por el gestor.
    ~GestorServicios();

    // Agrega un nuevo servicio al arreglo.
    // Recibe un puntero a un objeto ServicioTecnico.
    void agregarServicio(ServicioTecnico* servicio);

    // Busca un servicio utilizando su identificador.
    // Devuelve un puntero al servicio encontrado.
    // Si no existe, devuelve nullptr.
    ServicioTecnico* buscarPorId(const std::string& id) const;

    // Recorre el arreglo e imprime la información
    // de todos los servicios registrados.
    void listarServicios() const;

    // Elimina un servicio utilizando su ID.
    // Devuelve true si fue eliminado correctamente
    // o false si no se encontró.
    bool eliminarServicio(const std::string& id);

    // Devuelve la cantidad de servicios almacenados.
    int getCantidad() const;
};

#endif
