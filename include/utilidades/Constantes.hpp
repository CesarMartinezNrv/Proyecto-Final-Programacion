#ifndef CONSTANTES_HPP
#define CONSTANTES_HPP

#include <string>

namespace Constantes{
    inline constexpr int LONGITUD_TELEFONO{10};
    inline constexpr int LONGITUD_CEDULA{10};
    inline constexpr int CAPACIDAD_INICIAL{4};

    inline const std::string ARCHIVO_CLIENTES{"data/clientes.txt"};
    inline const std::string ARCHIVO_TECNICOS{"data/tecnicos.txt"};
    inline const std::string ARCHIVO_DISPOSITIVOS{"data/dispositivos.txt"};
    inline const std::string ARCHIVO_HISTORIAL{"data/historial_servicios.txt"};
}

#endif
