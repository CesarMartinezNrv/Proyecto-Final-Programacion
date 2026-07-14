#ifndef GESTORCLIENTES_HPP
#define GESTORCLIENTES_HPP

#include "modelos/Cliente.hpp" //Se necesita la clase cliente
#include <string>


class GestorClientes{
private:
    Cliente** clientes; //arreglo dinamico que contien objetos cliente
    int capacidad;
    int cantidad;
    void redimensionar();

public:
    //Constructor
    GestorClientes();
    //Destructor
    ~GestorClientes();
    bool agregarCliente(Cliente* nuevoCliente);
    Cliente* buscarPorIdentificacion(std::string codigoPersona) const;
    Cliente* buscarPorCedula(std::string cedula) const;
    bool eliminarCliente(std::string codigoPersona);
    void imprimirRegistro() const;
    int getCantidad() const;

    void guardarArchivo(std::string nombreArchivo) const;
    void cargarArchivo(std::string nombreArchivo);
};

#endif
