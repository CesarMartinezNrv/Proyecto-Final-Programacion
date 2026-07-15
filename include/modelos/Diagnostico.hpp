#ifndef DIAGNOSTICO_H
#define DIAGNOSTICO_H
#include "modelos/ServicioTecnico.hpp"
#include <string>

// Clase Diagnostico
// Hereda de ServicioTecnico y representa un servicio de
// diagnóstico realizado a un dispositivo.

class Diagnostico : public ServicioTecnico{

private:

    // Nivel de revisión realizado al equipo
    std::string nivel_revision;

    // Indica si el diagnóstico incluye un reporte
    bool requiere_reporte;

public:

    // Constructor
    Diagnostico(std::string identificacionServicio, std::string nombre, std::string descripcion, double precio, int duracion, std::string nivel, bool reporte);

    // Getters
    std::string getNivelRevision() const;
    bool getRequiereReporte() const;

    // Setters
    void setNivelRevision(std::string nivel);
    void setRequiereReporte(bool reporte);

    // Métodos sobrescritos de la clase base
    double calcularCosto() const override;
    std::string getTipo() const override;
    void mostrarInformacion() const override;
    std::string transformarArchivo() const override;

    // Destructor
    ~Diagnostico() override;

};

#endif
