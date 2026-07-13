#ifndef GESTORSERVICIOS_HPP
#define GESTORSERVICIOS_HPP

#include "modelos/ServicioTecnico.hpp"
#include <string>

class GestorServicios{

private:

    ServicioTecnico** servicios;
    int capacidad;
    int cantidad;

    void redimensionar();

    //Extrae el campo que va desde posicion hasta el siguiente '|' y avanza posicion
    std::string extraerCampo(const std::string& linea, size_t& posicion) const;

public:

    GestorServicios(int capacidadInicial = 10);

    bool agregarServicio(ServicioTecnico* servicio);

    ServicioTecnico* buscarPorId(std::string id) const;

    void listarServicios() const;

    void eliminarServicio(std::string id);

    //Persistencia con delimitador "|", primer campo indica la subclase concreta
    void guardarArchivo(const std::string& nombreArchivo) const;
    void cargarArchivo(const std::string& nombreArchivo);

    ~GestorServicios();

};

#endif
