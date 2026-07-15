# Frontend demostrativo — Sistema de Gestión de Servicios Técnicos (SGST)

Panel administrativo web que representa visualmente el sistema de consola en C++ de este repositorio. Es una capa de demostración **independiente** del ejecutable C++: no lo reemplaza, no se conecta a él y no comparte datos con los archivos de `data/`.

## Objetivo

Mostrar, en una interfaz de navegador, las mismas entidades, atributos, relaciones y reglas que ya existen en el código C++ (`include/`, `src/`), para poder presentar y explicar el proyecto sin depender de la consola.

## Tecnologías utilizadas

- HTML5
- CSS3 (variables nativas, grid, flexbox, media queries)
- JavaScript vanilla (ES6, sin frameworks ni librerías)
- SVG propio (iconos y gráficos del dashboard, dibujados a mano)
- `localStorage` del navegador como único mecanismo de persistencia

No se usó ningún framework, gestor de paquetes, CDN, fuente externa ni paso de compilación. No hay `package.json`, ni Node, ni build step: los archivos se ejecutan tal cual.

## Estructura de archivos

```
frontend/
├── index.html   Estructura de la aplicación (barra lateral, barra superior, 7 secciones, modales)
├── styles.css   Todo el diseño visual: paleta, layout, componentes, responsive
├── app.js       Toda la lógica: datos, validaciones, render, eventos (18 secciones comentadas)
├── favicon.svg  Ícono de pestaña propio
└── README.md    Este documento
```

## Cómo ejecutarlo

1. Abre `frontend/index.html` directamente con doble clic, o arrástralo a un navegador (Chrome, Edge o Firefox actualizados).
2. No requiere servidor, instalación ni conexión a internet.
3. La primera vez que se abre, se generan datos de demostración automáticamente.

## Modo demostración local

La interfaz muestra permanentemente la etiqueta **MODO DEMOSTRACIÓN LOCAL** en la barra superior. Esto significa:

- Todos los datos se guardan únicamente en el `localStorage` del navegador donde se abrió el archivo.
- No hay servidor, API, base de datos ni comunicación con el ejecutable `proyecto.exe` ni con los archivos `.txt` de `data/`.
- Si se abre el mismo `index.html` en otro navegador o en otro computador, los datos no se comparten: cada navegador tiene su propia copia.
- Borrar el historial/datos de navegación de ese sitio elimina también los datos guardados aquí.

## Módulos disponibles

Cada módulo corresponde a operaciones reales del menú de `src/main.cpp`:

| Módulo | Clases C++ relacionadas | Operaciones implementadas |
|---|---|---|
| Dashboard | Cálculo sobre todas las colecciones | Estadísticas, gráficos SVG, accesos rápidos, actividad reciente |
| Clientes | `Persona`, `Cliente`, `GestorClientes` | Registrar, mostrar, buscar por código, buscar por nombre, filtrar por estado, ver detalle |
| Técnicos | `Persona`, `Tecnico`, `GestorTecnicos` | Registrar, mostrar, buscar por código, filtrar por disponibilidad, ver detalle |
| Dispositivos | `Dispositivo`, `GestorDispositivos` | Registrar, mostrar, buscar por identificación, buscar por marca/modelo, filtrar por cliente/tipo/estado, ver detalle |
| Servicios | `ServicioTecnico`, `Diagnostico`, `Reparacion`, `MantenimientoPreventivo`, `GestorServicios` | Registrar (formulario dinámico según tipo), mostrar, buscar por identificación, filtrar por tipo |
| Órdenes | `OrdenServicio`, `GestorOrdenes` | Crear orden, mostrar todas, mostrar pendientes, buscar por identificación, actualizar estado, filtros |
| Historial | `HistorialServicio` | Registrar, mostrar, buscar/filtrar por dispositivo, por técnico y por fecha |

No se incluyó edición ni eliminación en ningún módulo porque el menú real de `main.cpp` no expone esas operaciones (los métodos `eliminarCliente`, `eliminarTecnico`, `eliminarDispositivo` y `eliminarServicio` existen en las clases gestoras de C++ pero ningún menú los invoca).

## Datos de demostración

En la primera carga se generan automáticamente 4 clientes, 3 técnicos, 5 dispositivos, 5 servicios (de los tres tipos), 4 órdenes en distintos estados y 3 registros de historial, todos con nombres ficticios. Estos datos solo se cargan si `localStorage` está vacío: en cargas posteriores se respeta lo que el usuario haya registrado o modificado.

El botón **Restablecer datos de demostración** (pie de página) borra todo lo guardado y vuelve a cargar este conjunto inicial, previa confirmación en una ventana modal propia (no se usa `confirm()` del navegador).

## Validaciones implementadas

Replican las reglas encontradas en `Persona.cpp`, `Validaciones.cpp`, `Cliente.cpp`, `Dispositivo.cpp`, `ServicioTecnico`/subclases y `HistorialServicio.cpp`:

- Nombre, dirección, descripción, diagnóstico, solución, tipo, marca, modelo: no pueden estar vacíos.
- Teléfono: exactamente 10 dígitos numéricos que inician en `0`.
- Correo: no vacío, debe contener `@` y `.`, no puede iniciar con `@` ni terminar en `.`.
- Cédula: exactamente 10 dígitos numéricos.
- Estado de atención del cliente: solo `activo` o `inactivo`.
- Estado del dispositivo: solo `activo`, `en reparacion` o `dado de baja`.
- Estado de la orden: solo `Pendiente`, `En proceso` o `Finalizada`.
- Precio base, duración, costo de repuesto y horas de mano de obra: si se ingresa un valor negativo, se ajusta a 0 automáticamente (igual que en los constructores de C++).
- Costo del historial: debe ser mayor a 0.
- Identificaciones (cliente, técnico, dispositivo, servicio, orden): no pueden estar vacías ni duplicarse.

Los errores se muestran debajo de cada campo (no solo con `alert`), junto con resaltado del campo inválido, notificaciones tipo toast y ventanas de confirmación propias para acciones importantes.

### Decisiones sobre reglas que van más allá del C++ original

Estas tres reglas se agregaron en el frontend porque el enunciado de este encargo las pidió explícitamente, aunque el C++ original no las implementa exactamente así:

1. **Número de serie único por dispositivo.** `GestorDispositivos::agregarDispositivo` en C++ solo valida que la identificación no se repita; no revisa el número de serie. El frontend sí lo valida, como mejora de integridad de datos.
2. **El dispositivo debe pertenecer al cliente seleccionado al crear una orden.** `crearOrden` en C++ busca el dispositivo únicamente por identificación, sin verificar el dueño. El frontend filtra el selector de dispositivos según el cliente elegido y valida la relación antes de guardar.
3. **Asignación de técnicos ocupados.** El C++ real no impide asignar un técnico marcado como ocupado a una orden (`asignarTecnico` no hace ninguna verificación). El frontend respeta ese comportamiento: permite la asignación igual, pero muestra un aviso informativo con la disponibilidad actual del técnico.

## Estructura de `localStorage`

Cada colección se guarda en su propia clave (no todo en una sola cadena):

| Clave | Contenido |
|---|---|
| `sgst_clientes` | Arreglo de clientes |
| `sgst_tecnicos` | Arreglo de técnicos |
| `sgst_dispositivos` | Arreglo de dispositivos |
| `sgst_servicios` | Arreglo de servicios (con discriminador `tipo`) |
| `sgst_ordenes` | Arreglo de órdenes de servicio |
| `sgst_historial` | Arreglo de registros de historial |
| `sgst_configuracion` | Objeto de configuración (estado del menú lateral, marca de inicialización) |
| `sgst_actividad` | Arreglo de eventos recientes para el panel de actividad |

Si alguna clave contiene un valor que no se puede interpretar como JSON válido (datos corruptos), la aplicación no se rompe: registra la clave como dañada, la reemplaza por una lista vacía y muestra una notificación explicando lo ocurrido.

## Diseño responsive

Probado visualmente en cuatro anchos de referencia:

- Escritorio (1440 px): panel lateral fijo, cuadrícula de estadísticas y gráficos en varias columnas.
- Laptop (1024 px): se reducen columnas de paneles y formularios a una sola columna donde corresponde.
- Tablet (~860 px): el menú lateral se convierte en panel deslizante (off-canvas) con fondo superpuesto.
- Celular (~390 px): una sola columna en tarjetas, formularios y tablas con scroll horizontal controlado, botones de ancho completo y barra superior simplificada.

## Accesibilidad

- Etiquetas `label` asociadas a todos los campos de formulario.
- Navegación completa por teclado, incluyendo apertura/cierre de menú y modales con foco atrapado dentro del modal mientras está abierto.
- `Escape` cierra modales, confirmaciones y el menú móvil.
- Foco visible reforzado (`:focus-visible`) en toda la aplicación.
- Atributos ARIA donde aportan valor real (`aria-current`, `aria-modal`, `aria-live`, `aria-expanded`, `role="alert"`/`role="status"`).
- Respeta `prefers-reduced-motion`: desactiva animaciones y transiciones si el sistema operativo lo solicita.

## Limitaciones técnicas

- No hay integración directa con el ejecutable de C++: los datos del frontend y los datos de `data/*.txt` son completamente independientes.
- No hay servidor ni backend: todo corre en el navegador.
- Los datos no se sincronizan entre dispositivos ni navegadores.
- `HistorialServicio` no valida en C++ que el servicio, dispositivo o técnico referenciados existan realmente; el frontend respeta esa misma falta de validación relacional en ese módulo específico.
- La búsqueda por dispositivo/técnico en Historial se implementó como un **filtro** que muestra todas las coincidencias (mejor para navegar en una tabla web), mientras que en C++ `buscarPorDispositivo`/`buscarPorTecnico` devuelven solo el primer registro encontrado.

## Integración futura con el proyecto en C++ (solo como posibilidad)

Este frontend no se comunica con C++ hoy. Si en el futuro se quisiera una integración real, un camino posible sería:

1. Construir una API HTTP (por ejemplo con un pequeño servidor en C++, o un proceso intermedio) que exponga los `Gestor*` como endpoints REST (`GET /clientes`, `POST /ordenes`, etc.).
2. Sustituir las funciones `guardar*`/`cargar*` de `app.js` por llamadas `fetch` a esa API, manteniendo la misma forma de los objetos ya usada aquí.
3. Mantener la validación en el frontend como primera línea, pero validar también en el servidor antes de escribir en los archivos `.txt`.

Esto es solo una posibilidad de diseño; no está implementado en este frontend.

## Cómo restablecer los datos

1. Baja hasta el pie de página de cualquier sección.
2. Haz clic en **Restablecer datos de demostración**.
3. Confirma la acción en la ventana que aparece (explica exactamente qué se va a borrar).
4. Los datos vuelven al conjunto de demostración inicial.

## Navegadores compatibles

Probado sobre motores modernos con soporte de ES6, CSS Grid y `localStorage`:

- Google Chrome / Microsoft Edge (versiones recientes, basados en Chromium)
- Mozilla Firefox (versión reciente)
- Safari (versión reciente)

No se garantiza compatibilidad con Internet Explorer.
