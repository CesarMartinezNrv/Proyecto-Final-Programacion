#ifndef CONSTANTES_HPP
#define CONSTANTES_HPP

#include <string>

namespace Constantes{
    constexpr int LONGITUD_TELEFONO{10};
    constexpr int LONGITUD_CEDULA{10};
    constexpr int CAPACIDAD_INICIAL{4};

    const std::string ARCHIVO_CLIENTES{"data/clientes.txt"};
    const std::string ARCHIVO_TECNICOS{"data/tecnicos.txt"};
    const std::string ARCHIVO_DISPOSITIVOS{"data/dispositivos.txt"};
    const std::string ARCHIVO_HISTORIAL{"data/historial_servicios.txt"};
}

#endif
