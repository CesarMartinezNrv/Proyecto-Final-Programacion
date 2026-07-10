#include "modelos/HistorialServicio.hpp"
#include <fstream>
#include <sstream>

HistorialServicio** HistorialServicio::registros = nullptr;
int HistorialServicio::capacidad = 0;
int HistorialServicio::cantidad = 0;

HistorialServicio::HistorialServicio() : identificacionServicio{""}, identificacionDispositivo{""}, identificacionTecnico{""}, fecha{""}, descripcion{""}, diagnostico{""}, solucion{""}, costo{0.0}{}

HistorialServicio::HistorialServicio(std::string identificacionServicio,
std::string identificacionDispositivo,
std::string identificacionTecnico,
std::string fecha,
std::string descripcion,
std::string diagnostico,
std::string solucion,
double costo) : identificacionServicio{identificacionServicio}, identificacionDispositivo{identificacionDispositivo}, identificacionTecnico{identificacionTecnico}, fecha{fecha}{
    setDescripcion(descripcion);
    setDiagnostico(diagnostico);
    setSolucion(solucion);
    setCosto(costo);
}

//Getters
std::string HistorialServicio::getIdServicio() const{ return identificacionServicio;}
std::string HistorialServicio::getIdentificacionDispositivo() const{ return identificacionDispositivo;}
std::string HistorialServicio::getIdTecnico() const{ return identificacionTecnico;}
std::string HistorialServicio::getFecha() const{ return fecha;}
std::string HistorialServicio::getDescripcion() const{ return descripcion;}
std::string HistorialServicio::getDiagnostico() const{ return diagnostico;}
std::string HistorialServicio::getSolucion() const{ return solucion;}
double HistorialServicio::getCosto() const{ return costo;}

//Setters
bool HistorialServicio::setDescripcion(std::string nuevaDescripcion){
    if(validarTextoNoVacio(nuevaDescripcion) == false){
        std::cout<<"ERROR. La descripcion no puede estar vacia."<<std::endl;
        return false;
    }
    descripcion = nuevaDescripcion;
    return true;
}

bool HistorialServicio::setDiagnostico(std::string nuevoDiagnostico){
    if(validarTextoNoVacio(nuevoDiagnostico) == false){
        std::cout<<"ERROR. El diagnostico no puede estar vacio."<<std::endl;
        return false;
    }
    diagnostico = nuevoDiagnostico;
    return true;
}

bool HistorialServicio::setSolucion(std::string nuevaSolucion){
    if(validarTextoNoVacio(nuevaSolucion) == false){
        std::cout<<"ERROR. La solucion no puede estar vacia."<<std::endl;
        return false;
    }
    solucion = nuevaSolucion;
    return true;
}

bool HistorialServicio::setCosto(double nuevoCosto){
    if(validarCosto(nuevoCosto) == false){
        std::cout<<"ERROR. El costo debe ser mayor a cero."<<std::endl;
        return false;
    }
    costo = nuevoCosto;
    return true;
}

void HistorialServicio::mostrarInformacion() const{
    std::cout<<*this;
}

std::string HistorialServicio::aTextoArchivo() const{
    return identificacionServicio+"|"+identificacionDispositivo+"|"+identificacionTecnico+"|"+fecha+"|"+descripcion+"|"+diagnostico+"|"+solucion+"|"+std::to_string(costo);
}

//Sobrecarga que permite imprimir el historial directamente con cout
std::ostream& operator<<(std::ostream& salida, const HistorialServicio& historial){
    salida<<"ID servicio: "<<historial.identificacionServicio<<std::endl;
    salida<<"ID dispositivo: "<<historial.identificacionDispositivo<<std::endl;
    salida<<"ID tecnico: "<<historial.identificacionTecnico<<std::endl;
    salida<<"Fecha: "<<historial.fecha<<std::endl;
    salida<<"Descripcion: "<<historial.descripcion<<std::endl;
    salida<<"Diagnostico: "<<historial.diagnostico<<std::endl;
    salida<<"Solucion: "<<historial.solucion<<std::endl;
    salida<<"Costo: "<<historial.costo<<std::endl;
    return salida;
}

void HistorialServicio::redimensionar(){
    int nuevaCapacidad{capacidad == 0 ? 4 : capacidad * 2};
    HistorialServicio** nuevoArreglo{new HistorialServicio*[nuevaCapacidad]};
    for(int i{0}; i < cantidad; i++){
        nuevoArreglo[i] = registros[i];
    }
    delete[] registros;
    registros = nuevoArreglo;
    capacidad = nuevaCapacidad;
}

bool HistorialServicio::agregar(HistorialServicio* nuevoRegistro){
    if(nuevoRegistro == nullptr){
        return false;
    }
    if(cantidad == capacidad){
        redimensionar();
    }
    registros[cantidad] = nuevoRegistro;
    cantidad++;
    return true;
}

HistorialServicio* HistorialServicio::buscarPorDispositivo(std::string identificacionDispositivo){
    for(int i{0}; i < cantidad; i++){
        if(registros[i]->getIdentificacionDispositivo() == identificacionDispositivo){
            return registros[i];
        }
    }
    return nullptr;
}

HistorialServicio* HistorialServicio::buscarPorTecnico(std::string identificacionTecnico){
    for(int i{0}; i < cantidad; i++){
        if(registros[i]->getIdTecnico() == identificacionTecnico){
            return registros[i];
        }
    }
    return nullptr;
}

void HistorialServicio::mostrarTodos(){
    for(int i{0}; i < cantidad; i++){
        std::cout<<*registros[i];
        std::cout<<"----------------------------"<<std::endl;
    }
}

void HistorialServicio::guardarArchivo(std::string nombreArchivo){
    std::ofstream archivo(nombreArchivo);
    if(archivo.is_open() == false){
        std::cout<<"ERROR.No se pudo abrir el archivo para guardar el historial."<<std::endl;
        return;
    }
    for(int i{0}; i < cantidad; i++){
        archivo<<registros[i]->aTextoArchivo()<<std::endl;
    }
    archivo.close();
}

void HistorialServicio::cargarArchivo(std::string nombreArchivo){
    std::ifstream archivo(nombreArchivo);
    if(archivo.is_open() == false){
        std::cout<<"No existe archivo previo de historial, se inicia vacio."<<std::endl;
        return;
    }
    std::string linea;
    while(std::getline(archivo, linea)){
        if(linea == ""){
            continue;
        }
        std::stringstream flujo(linea);
        std::string identificacionServicio, identificacionDispositivo, idTecnico, fecha, descripcion, diagnostico, solucion, costoTexto;
        std::getline(flujo, identificacionServicio, '|');
        std::getline(flujo, identificacionDispositivo, '|');
        std::getline(flujo, idTecnico, '|');
        std::getline(flujo, fecha, '|');
        std::getline(flujo, descripcion, '|');
        std::getline(flujo, diagnostico, '|');
        std::getline(flujo, solucion, '|');
        std::getline(flujo, costoTexto, '|');
        double costo{std::stod(costoTexto)};
        HistorialServicio* nuevoRegistro{new HistorialServicio(identificacionServicio, identificacionDispositivo, idTecnico, fecha, descripcion, diagnostico, solucion, costo)};
        agregar(nuevoRegistro);
    }
    archivo.close();
}

void HistorialServicio::liberarMemoria(){
    for(int i{0}; i < cantidad; i++){
        delete registros[i];
        registros[i] = nullptr;
    }
    delete[] registros;
    registros = nullptr;
    capacidad = 0;
    cantidad = 0;
}

int HistorialServicio::getCantidad(){
    return cantidad;
}

bool HistorialServicio::validarTextoNoVacio(std::string texto) const{
    return texto != "";
}

bool HistorialServicio::validarCosto(double costo) const{
    return costo > 0;
}

HistorialServicio::~HistorialServicio(){}
