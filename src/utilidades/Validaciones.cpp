#include "utilidades/Validaciones.hpp"
#include "utilidades/Constantes.hpp"
#include <cctype>

namespace Validaciones{

bool validarTextoNoVacio(std::string texto){
    return texto != "";
}

bool validarTelefono(std::string telefono){
    if(telefono.size() != Constantes::LONGITUD_TELEFONO){
        return false;
    }
    for(int i{0}; i < (int)telefono.size(); i++){
        if(isdigit(telefono[i]) == false){
            return false;
        }
    }
    if(telefono[0] != '0'){
        return false;
    }
    return true;
}

bool validarCorreo(std::string correo){
    if(validarTextoNoVacio(correo) == false){
        return false;
    }
    if(correo.find("@") == std::string::npos){
        return false;
    }
    if(correo.find(".") == std::string::npos){
        return false;
    }
    if(correo[0] == '@'){
        return false;
    }
    if(correo[correo.size() - 1] == '.'){
        return false;
    }
    return true;
}

bool validarCedula(std::string cedula){
    if(cedula.size() != Constantes::LONGITUD_CEDULA){
        return false;
    }
    for(int i{0}; i < (int)cedula.size(); i++){
        if(isdigit(cedula[i]) == false){
            return false;
        }
    }
    return true;
}

bool validarCosto(double costo){
    return costo > 0;
}

}
