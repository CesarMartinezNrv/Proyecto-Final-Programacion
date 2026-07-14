#ifndef REPARACION_H
#define REPARACION_H
#include <string>
#include "modelos/ServicioTecnico.hpp

// Clase Reparacion
// Hereda de ServicioTecnico y representa un servicio
// de reparación de un dispositivo.

class Reparacion : public ServicioTecnico{

private:

    // Costo de los repuestos utilizados
    double costo_repuesto;

    // Horas de trabajo empleadas en la reparación
    double horas_mano_obra;

    // Valor fijo por cada hora de mano de obra
    static constexpr double VALOR_HORA = 25.0;

public:

    // Constructor
    Reparacion(std::string idServicio, std::string nombre, std::string descripcion, double precioBase, int duracion, double costoRepuesto, double horasManoObra);

    // Getters
    double getCostoRepuesto() const;
    double getHorasManoObra() const;

    // Setters
    void setCostoRepuesto(double costo);
    void setHorasManoObra(double horas);

    // Métodos sobrescritos de la clase base
    double calcularCosto() const override;
    std::string getTipo() const override;
    void mostrarInformacion() const override;

    // Destructor
    ~Reparacion() override;

};

#endif
