#ifndef GESTORDISPOSITIVOS_HPP
#define GESTORDISPOSITIVOS_HPP

#include "modelos/Dispositivo.hpp"
#include <string>

class GestorDispositivos{
private:
    Dispositivo** dispositivos; //apunta a un arreglo dinamico que contiene direcciones de punteros
    /*
            dispositivos
                  |
                  v
    +--------------+--------------+--------------+--------------+
    | Dispositivo* | Dispositivo* | Dispositivo* | Dispositivo* |
    +------|-------+------|-------+------|-------+--------------+
           |              |              |
           v              v              v
         DIS001         DIS002         DIS003
    */
    int capacidad; 
    int cantidad;

    void redimensionar();

public:
    //Constructor
    GestorDispositivos();
    //Destructor
    ~GestorDispositivos();


    bool agregarDispositivo(Dispositivo* nuevoDispositivo);
    //Sobrecarga para busca por identificacion  o por combinacion de marca y modelo
    //Busca en base al codigo de identificacion
    Dispositivo* buscar(const std::string& identificacionDispositivo) const;
    //Busca en base a la marca y modelo ingresado
    Dispositivo* buscar(const std::string& marca, const std::string& modelo) const;
    void mostrarPorCliente(std::string identificacionCliente) const;
    bool eliminarDispositivo(std::string identificacionDispositivo);
    void imprimirRegistro() const;
    int getCantidad() const;
    void guardarArchivo(std::string nombreArchivo) const;
    void cargarArchivo(std::string nombreArchivo);
};

#endif
