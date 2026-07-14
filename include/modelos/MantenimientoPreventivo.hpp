#ifndef MANTENIMIENTOPREVENTIVO_H
#define MANTENIMIENTOPREVENTIVO_H
#include <string>
#include "modelos/ServicioTecnico.hpp"

// Clase MantenimientoPreventivo
// Hereda de ServicioTecnico y representa un servicio
// de mantenimiento preventivo para un dispositivo.

class MantenimientoPreventivo : public ServicioTecnico{

private:

    // Indica si el servicio incluye limpieza interna
    bool incluye_limpieza;

    // Indica si se realiza cambio de pasta térmica
    bool incluye_pasta_termica;

    // Recargos adicionales del servicio
    static constexpr double RECARGO_LIMPIEZA = 20.0;
    static constexpr double RECARGO_PASTA = 35.0;

public:

    // Constructor
    MantenimientoPreventivo(std::string idServicio,std::string nombre, std::string descripcion,double precioBase, int duracion, bool limpieza, bool pasta);

    // Getters
    bool getIncluyeLimpieza() const;
    bool getIncluyePastaTermica() const;

    // Setters
    void setIncluyeLimpieza(bool limpieza);
    void setIncluyePastaTermica(bool pasta);

    // Métodos sobrescritos de la clase base
    double calcularCosto() const override;
    std::string getTipo() const override;
    void mostrarInformacion() const override;

    // Destructor
    ~MantenimientoPreventivo() override;

};

#endif
