#ifndef GESTORTECNICOS_HPP
#define GESTORTECNICOS_HPP

#include "modelos/Tecnico.hpp"
#include <string>

class GestorTecnicos{
private:
    Tecnico** tecnicos;
    int capacidad;
    int cantidad;

    void redimensionar();

public:
    GestorTecnicos();
    ~GestorTecnicos();

    bool agregarTecnico(Tecnico* nuevoTecnico);
    Tecnico* buscarPorIdentificacion(std::string codigoPersona) const;
    Tecnico* buscarPorCedula(std::string cedula) const;
    Tecnico* buscarDisponible() const;
    bool eliminarTecnico(std::string codigoPersona);
    void imprimirRegistro() const;
    int getCantidad() const;

    void guardarArchivo(std::string nombreArchivo) const;
    void cargarArchivo(std::string nombreArchivo);
};

#endif
