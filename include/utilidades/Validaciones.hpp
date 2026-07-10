#ifndef VALIDACIONES_HPP
#define VALIDACIONES_HPP

#include <string>

namespace Validaciones{
    bool validarTextoNoVacio(std::string texto);
    bool validarTelefono(std::string telefono);
    bool validarCorreo(std::string correo);
    bool validarCedula(std::string cedula);
    bool validarCosto(double costo);
}

#endif
