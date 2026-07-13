#ifndef MANTENIMIENTOPREVENTIVO_H
#define MANTENIMIENTOPREVENTIVO_H
#include <string>
#include "modelos/ServicioTecnico.hpp"

class MantenimientoPreventivo : public ServicioTecnico{

private:

    bool incluye_limpieza;
    bool incluye_pasta_termica;

    static constexpr double RECARGO_LIMPIEZA = 20.0;
    static constexpr double RECARGO_PASTA = 35.0;

public:
    MantenimientoPreventivo(std::string id, std::string nombre, std::string descripcion, double precioBase, int duracion, bool limpieza, bool pasta);

    bool getIncluyeLimpieza() const;
    bool getIncluyePastaTermica() const;

    void setIncluyeLimpieza(bool limpieza);
    void setIncluyePastaTermica(bool pasta);

    double calcularCosto() const override;

    std::string getTipo() const override;

    void mostrarInformacion() const override;

    std::string transformarArchivo() const override;

    ~MantenimientoPreventivo() override;

};

#endif