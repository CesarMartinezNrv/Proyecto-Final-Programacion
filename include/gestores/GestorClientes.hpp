#ifndef GESTORCLIENTES_HPP
#define GESTORCLIENTES_HPP

#include "modelos/Cliente.hpp"
#include <string>

//Administra un arreglo dinamico de punteros a Cliente
class GestorClientes{
private:
    Cliente** clientes;
    int capacidad;
    int cantidad;

    void redimensionar();

public:
    GestorClientes();
    ~GestorClientes();

    bool agregarCliente(Cliente* nuevoCliente);
    Cliente* buscarPorIdentificacion(std::string codigoPersona) const;
    Cliente* buscarPorCedula(std::string cedula) const;
    bool eliminarCliente(std::string codigoPersona);
    void mostrarTodos() const;
    int getCantidad() const;

    //Persistencia con delimitador "|"
    void guardarArchivo(std::string nombreArchivo) const;
    void cargarArchivo(std::string nombreArchivo);
};

#endif
