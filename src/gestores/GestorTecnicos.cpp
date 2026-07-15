#include "gestores/GestorTecnicos.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

//Constructor
GestorTecnicos::GestorTecnicos() : tecnicos{nullptr}, capacidad{0}, cantidad{0}{}
//Destructor (Libera memoria dinamica)
GestorTecnicos::~GestorTecnicos(){
    for(int i{0}; i < cantidad; i++){
        delete tecnicos[i];
        tecnicos[i] = nullptr;
    }
    delete[] tecnicos;
    tecnicos = nullptr;
}


void GestorTecnicos::redimensionar(){
    int nuevaCapacidad{0};

    if(capacidad == 0){
        nuevaCapacidad = 2;
    }
    else{
        nuevaCapacidad = capacidad * 2;
    }

    Tecnico** nuevoArreglo = new Tecnico*[nuevaCapacidad];
    for(int i{0}; i < cantidad; i++){
        nuevoArreglo[i] = tecnicos[i]; //Asigna las direcciones de memoria de los tecnicos en
                                       //el nuevo arreglo
    }
    delete[] tecnicos; //Elimina el viejo arreglo de punteros
    tecnicos = nuevoArreglo;
    capacidad = nuevaCapacidad;
}

bool GestorTecnicos::agregarTecnico(Tecnico* nuevoTecnico){
    if(nuevoTecnico == nullptr){ //Si el puntero es null, negar el proceso
        return false;
    }
    if(buscarPorIdentificacion(nuevoTecnico->getCodigoPersona()) != nullptr){
        std::cout<<"ERROR. Ya existe un tecnico con ese codigo."<<std::endl;
        return false; //Si se encuentra un tecnico con el mismo codigo, se niega el proceso
    }
    if(cantidad == capacidad){
        redimensionar(); //Si el arreglo esta lleno, se redimensiona para expandirlo
    }
    tecnicos[cantidad] = nuevoTecnico; //Se agrega el puntero
    cantidad++; //aumenta la cantidad ocupada en el arreglo
    return true;
}

Tecnico* GestorTecnicos::buscarPorIdentificacion(std::string codigoPersona) const{
    for(int i{0}; i < cantidad; i++){
        if(tecnicos[i]->getCodigoPersona() == codigoPersona){
            return tecnicos[i]; //Si se encuentra el mismo codigo en el arreglo, retorna la direccion 
        }                       //del tecnico encontrado
    }
    return nullptr; //Si no encuentra nada retorna null
}

Tecnico* GestorTecnicos::buscarPorCedula(std::string cedula) const{
    for(int i{0}; i < cantidad; i++){
        if(tecnicos[i]->getCedula() == cedula){
            return tecnicos[i];
        }
    }
    return nullptr;
}

Tecnico* GestorTecnicos::buscarDisponible() const{
    //Recorre el arreglo buscando el tecnico que tenga el atributo EstadoDisponible = true;
    for(int i{0}; i < cantidad; i++){ 
        if(tecnicos[i]->getEstadoDisponible() == true){
            return tecnicos[i]; //Retorna la direccion de memoria
        }
    }
    return nullptr;
}

bool GestorTecnicos::eliminarTecnico(std::string codigoPersona){
    for(int i{0}; i < cantidad; i++){ //Recorre el arreglo buscando el mismo codigo que coincida
        if(tecnicos[i]->getCodigoPersona() == codigoPersona){
            delete tecnicos[i]; //Si lo encuentra borra la direccion de memoria
            for(int j{i}; j < cantidad - 1; j++){
                tecnicos[j] = tecnicos[j + 1]; //Moviliza todas las direcciones de memoria hacia la izquierda
            }
            tecnicos[cantidad - 1] = nullptr; //Donde se borró al tecnico se apunta a null para no tener comportamientos 
            cantidad--;                       //inesperados
            return true;
        }
    }
    return false; //Si no encuentra nada, retorna falso
}

void GestorTecnicos::imprimirRegistro() const{
    for(int i{0}; i < cantidad; i++){
        tecnicos[i]->imprimirInformacionPersona();
        std::cout<<"----------------------------"<<std::endl;
    }
}

int GestorTecnicos::getCantidad() const{
    return cantidad;
}

void GestorTecnicos::guardarArchivo(std::string nombreArchivo) const{
    std::ofstream archivo(nombreArchivo);
    if(archivo.is_open() == false){
        std::cout<<"ERROR. No se pudo abrir el archivo para guardar los tecnicos."<<std::endl;
        return;
    }
    for(int i{0}; i < cantidad; i++){
        //Se ingresa la informacion de cada tecnico en una linea de texto
        archivo<<tecnicos[i]->transformarArchivo()<<std::endl;
    }
    archivo.close();
}


void GestorTecnicos::cargarArchivo(std::string nombreArchivo){
    std::ifstream archivo(nombreArchivo);
    if(archivo.is_open() == false){
        std::cout<<"AVISO. No existe archivo previo de tecnicos, se inicia vacio."<<std::endl;
        return;
    }
    std::string linea;
    while(std::getline(archivo, linea)){
        if(linea == ""){
            continue;
        }
        std::stringstream flujo(linea); //Permiete leer el string como cin>>
        //Variables locales que almacen los atribitos
        std::string codigoPersona, nombre, numeroDeTelefono, correo, cedula, especialidad, disponibleTexto, serviciosTexto;
        //Estructurra de getline (origen, destino, hasta donde)
        std::getline(flujo, codigoPersona, '|');
        std::getline(flujo, nombre, '|');
        std::getline(flujo, numeroDeTelefono, '|');
        std::getline(flujo, correo, '|');
        std::getline(flujo, cedula, '|');
        std::getline(flujo, especialidad, '|');
        std::getline(flujo, disponibleTexto, '|');
        std::getline(flujo, serviciosTexto, '|');
        Tecnico* nuevoTecnico = new Tecnico(codigoPersona, nombre, numeroDeTelefono, correo, cedula, especialidad);
        if(disponibleTexto == "0"){ //Si existe un 0 significa que esta ocupado
            nuevoTecnico->marcarComoOcupado();
        }
        //Restauracion
        for(int i{0}; i < std::stoi(serviciosTexto); i++){ //Transofrma el tipo string a entero
            nuevoTecnico->registrarServicioAtendido();
            //Actualiza el numero de registros atentidos
        }
        agregarTecnico(nuevoTecnico); //Agrega la direccion del tecno al arreglo 
    }
    archivo.close();
}
