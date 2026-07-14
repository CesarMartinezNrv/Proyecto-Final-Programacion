#ifndef GESTORDISPOSITIVOS_HPP
#define GESTORDISPOSITIVOS_HPP

#include "modelos/Dispositivo.hpp"
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

    //Sobrecarga: busca por identificador unico o por combinacion de marca y modelo
    Dispositivo* buscar(const std::string& identificacionDispositivo) const;
    Dispositivo* buscar(const std::string& marca, const std::string& modelo) const;

    void mostrarPorCliente(std::string idCliente) const;
    bool eliminarDispositivo(std::string identificacionDispositivo);
    void imprimirRegistro() const;
    int getCantidad() const;
    void guardarArchivo(std::string nombreArchivo) const;
    void cargarArchivo(std::string nombreArchivo);
};

#endif
