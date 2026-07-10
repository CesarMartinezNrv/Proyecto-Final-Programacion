#ifndef GESTORDISPOSITIVOS_HPP
#define GESTORDISPOSITIVOS_HPP

#include "Dispositivo.hpp"
#include <string>

class GestorDispositivos{
private:
    Dispositivo** dispositivos;
    int capacidad;
    int cantidad;

    void redimensionar();

public:
    GestorDispositivos();
    ~GestorDispositivos();

    bool agregarDispositivo(Dispositivo* nuevoDispositivo);
    Dispositivo* buscarPorIdentificacion(std::string identificacionDispositivo) const;
    void mostrarPorCliente(std::string idCliente) const;
    bool eliminarDispositivo(std::string identificacionDispositivo);
    void mostrarTodos() const;
    int getCantidad() const;
    void guardarArchivo(std::string nombreArchivo) const;
    void cargarArchivo(std::string nombreArchivo);
};

#endif
