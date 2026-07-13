# Descripcion de clases

## Persona (include/modelos/Persona.hpp)
Clase base abstracta para `Cliente` y `Tecnico`. Almacena codigo, nombre, telefono, correo y cedula, con validacion en cada setter. Define los metodos virtuales puros `tipoDePersona()`, `imprimirInformacionPersona()` y `transformarArchivo()`, que cada clase derivada debe implementar.

## Cliente (include/modelos/Cliente.hpp)
Hereda de `Persona`. Agrega direccion, fecha de registro, estado de atencion y un contador de dispositivos registrados.

## Tecnico (include/modelos/Tecnico.hpp)
Hereda de `Persona`. Agrega especialidad, disponibilidad y contador de servicios atendidos.

## Dispositivo (include/modelos/Dispositivo.hpp)
Clase independiente que representa un dispositivo de un cliente: tipo, marca, modelo, numero de serie y estado (`activo`, `en_reparacion`, `dado_de_baja`).

## HistorialServicio (include/modelos/HistorialServicio.hpp)
Registra cada servicio tecnico realizado a un dispositivo: descripcion, diagnostico, solucion y costo. Administra internamente un arreglo dinamico estatico compartido por todos los registros del sistema.

## GestorClientes / GestorTecnicos / GestorDispositivos (include/gestores/)
Cada gestor administra un arreglo dinamico de punteros a su clase correspondiente (`Cliente`, `Tecnico`, `Dispositivo`): alta, baja, busqueda y persistencia en archivo de texto delimitado por `|`.

## Validaciones y Constantes (include/utilidades/)
Funciones de validacion reutilizables (texto no vacio, telefono, correo, cedula, costo) y constantes compartidas del proyecto (longitudes de campos, capacidad inicial de los arreglos dinamicos, rutas de los archivos de datos en `data/`).
