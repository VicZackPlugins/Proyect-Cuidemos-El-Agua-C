# Catálogo de Proyectos en C basadas en los Objetivos de Desarrollo Sostenible (ODS)

**Curso:** Taller de Programación 1  
**Modalidad:** Programa de consola (terminal), con menú, vectores paralelos, matrices, funciones y archivos.

---

## 1. ¿De qué trata este catálogo?

Cada equipo desarrollará una pequeña aplicación de terminal que ayuda a resolver un problema real ligado a un **Objetivo de Desarrollo Sostenible (ODS)** de las Naciones Unidas. Los ODS son 17 metas mundiales para mejorar la vida de las personas y cuidar el planeta (por ejemplo: acabar con el hambre, cuidar el agua o combatir el cambio climático).

---

## 2. Conceptos que vas a usar

| Concepto | Qué significa |
| :--- | :--- |
| **Vectores paralelos** | Dos o más listas (arreglos 1D) donde la posición `i` de cada lista habla de **lo mismo**. Ejemplo: `nombre[2]`, `stock[2]` y `minimo[2]` son los datos del mismo alimento. |
| **Matriz** | Una tabla de filas y columnas. En estos proyectos, cada **fila** es un elemento (un alimento, una vacuna, un hogar...) y cada **columna** es un día o una semana. |
| **Archivo de datos** | Un archivo de texto donde el programa guarda todo antes de cerrar. Cuando vuelves a abrirlo, lo lee y **retoma donde quedaste**. |
| **Validar** | Revisar que un dato sea correcto (que esté en el rango permitido, que exista, que sea un número) y rechazarlo con un mensaje claro si no lo es. |

---

## 3. Estructura común de todos los proyectos

### 3.1 Tamaños máximos
Usa constantes al inicio del programa para que sea fácil cambiarlas:

```c
#define MAX_ELEMENTOS 8    // filas de la matriz y tamaño de los vectores
#define MAX_PERIODOS 7     // columnas de la matriz (días o semanas)
```

### 3.2 Datos que debe tener el programa

| Estructura | Cantidad | Para qué sirve |
| :--- | :---: | :--- |
| **Vectores paralelos** | 3 (uno de texto con los nombres y dos numéricos) | Guardan las características de cada elemento. |
| **Matriz** | 1 (`MAX_ELEMENTOS` $\times$ `MAX_PERIODOS`) | Guarda los registros de cada elemento en cada período. |
| **Variable `cantidad`** | 1 | Indica cuántos elementos están realmente en uso. |

> **Nota:** Los nombres se guardan en una matriz de caracteres (un nombre por fila). Para simplificar la lectura del archivo, escribe los nombres **sin espacios** (usa guion bajo: `Arroz_blanco`).

---

### 3.3 Menú único (el mismo en los 8 proyectos)

```text
========================================
    NOMBRE DEL PROGRAMA - ODS N°
========================================
1. ¿Qué ODS aborda este programa?
2. Configurar elementos
3. Registrar datos
4. Modificar un dato
5. [Operación principal del proyecto]
6. Ver tabla de datos
7. Ver estadísticas
8. Guardar datos
9. Ayuda y Acerca de
0. Salir
========================================
Elija una opción:
```

El menú se repite con un `do-while` hasta que el usuario elige `0`.

---

### 3.4 Qué hace cada opción

| Opción | Tipo de función | Qué debe hacer |
| :--- | :--- | :--- |
| **1. ¿Qué ODS aborda?** | Salida de información | Muestra en pantalla: el número y nombre del ODS, una explicación sencilla (4 a 6 líneas) y **cómo este programa ayuda** a esa meta. |
| **2. Configurar elementos** | Entrada de datos | Pide el nombre y los dos datos numéricos de cada elemento y los guarda en los **vectores paralelos**. |
| **3. Registrar datos** | Entrada de datos | Pide a qué elemento y período corresponde un dato nuevo y lo guarda en la **matriz**, aplicando las reglas de rechazo del proyecto. |
| **4. Modificar un dato** | Modificación | Permite corregir un dato ya registrado en la matriz. Muestra el valor anterior, pide el nuevo y valida. |
| **5. Operación principal** | Procesamiento | Recorre la matriz, calcula y **clasifica** cada elemento (por ejemplo, "Bien / Atención / Crítico"). Es la parte con más lógica del proyecto. |
| **6. Ver tabla** | Salida de información | Muestra la matriz como tabla ordenada, con nombres de filas y números de columnas, y con totales por fila. |
| **7. Estadísticas** | Procesamiento + salida | Calcula y muestra **al menos 4 estadísticas** (totales, promedios, máximos y quién los logra). |
| **8. Guardar datos** | Archivo | Escribe todo el estado actual en el archivo de datos. |
| **9. Ayuda y Acerca de** | Salida de información | Muestra dos cosas: **(a) Ayuda:** una explicación breve de qué hace cada opción del menú. **(b) Acerca de:** nombre y versión del programa, ODS que aborda, curso y **nombres de los integrantes del equipo**. |
| **0. Salir** | Control | Guarda automáticamente los datos y termina el programa. |

---

### 3.5 Funciones mínimas sugeridas

Cada requerimiento debe estar en su **propia función**. `main` solo muestra el menú y llama a las funciones.

| Función (nombre sugerido) | Responsabilidad |
| :--- | :--- |
| `mostrarMenu()` | Imprime el menú. |
| `mostrarODS()` | Opción 1. |
| `configurarElementos(...)` | Opción 2. |
| `registrarDato(...)` | Opción 3. |
| `modificarDato(...)` | Opción 4. |
| `operacionPrincipal(...)` | Opción 5. |
| `mostrarTabla(...)` | Opción 6. |
| `calcularEstadisticas(...)` | Opción 7. |
| `guardarArchivo(...)` | Opción 8 y al salir. |
| `cargarArchivo(...)` | Se ejecuta **al iniciar** el programa. |
| `mostrarAyudaYAcercaDe()` | Opción 9. |
| `leerEnteroEnRango(...)` | Pide un número y repite hasta que esté entre un mínimo y un máximo. |
| `leerRealEnRango(...)` | Igual, pero para números con decimales. |

---

### 3.6 Archivo de datos

Al iniciar, el programa intenta abrir el archivo:
* **Si existe:** carga los datos y avisa `"Datos cargados correctamente"`.
* **Si no existe:** avisa `"No hay datos guardados, se inicia vacío"` y sigue funcionando.
* **Si está mal escrito o tiene valores fuera de rango:** avisa del problema y **no se cae** (inicia vacío).

#### Formato sugerido (ejemplo genérico):
```text
3                           <- cantidad de elementos
Arroz 120.5 50.0            <- nombre, dato1, dato2 del elemento 0
Fideos 80.0 30.0            <- elemento 1
Lentejas 45.0 20.0          <- elemento 2
10.0 5.0 0.0 8.0 0.0 0.0 0.0 <- fila 0 de la matriz
0.0 0.0 12.0 0.0 0.0 0.0 0.0 <- fila 1 de la matriz
0.0 3.0 0.0 0.0 0.0 0.0 0.0  <- fila 2 de la matriz
```

---

### 3.6.1 Reglas de validación comunes

* Si el usuario escribe letras donde se espera un número, el programa **no se cae**: avisa y vuelve a pedir el dato (revisa lo que devuelve `scanf`).
* Un elemento o período que no existe se rechaza.
* Nunca se divide por cero: antes de cada división, el programa comprueba el divisor.
* Cada proyecto tiene sus propias **reglas de rechazo** (al menos 3), indicadas más abajo.

---

### 3.7 Restricciones del lenguaje C

* **Librerías permitidas:** `<stdio.h>`, `<stdlib.h>`, `<string.h>`, `<math.h>`.
* **Solo se permiten arreglos (vectores y matrices).** NO se permiten `struct`, punteros declarados por el estudiante ni `malloc` / `free`.
* Se puede usar `FILE *` y las funciones de `<stdio.h>` para el archivo (`fopen`, `fclose`, `fprintf`, `fscanf`, etc.).
* El menú va en un `do-while` con `switch`.

---

## 4. Especificación del Proyecto Asignado

# Proyecto 4 — Cuidemos el Agua

### ODS 6: Agua Limpia y Saneamiento

#### La situación
Un comité de agua potable rural quiere ayudar a las familias a **ahorrar agua** y detectar **posibles fugas**. Cada familia anota cuántos litros consume cada día.

---

### Vectores paralelos

| Vector | Contenido |
| :--- | :--- |
| `nombre[]` | Nombre de la familia u hogar. |
| `personas[]` | Cantidad de personas que viven en el hogar. |
| `limiteDiario[]` | Litros diarios recomendados para el hogar. |

---

### Matriz

* **`consumoLitros[hogar][dia]`:** Litros consumidos cada día (7 columnas).

---

### Qué hacen las opciones específicas

* **3. Registrar datos:** registra el consumo en litros de un hogar en un día.
* **4. Modificar un dato:** corrige el consumo de un día.
* **5. Detectar excesos y fugas:** para cada hogar cuenta los días en que superó el límite diario. Además, marca **POSIBLE FUGA** si algún día el consumo fue más del **doble del promedio** de ese hogar (hay que calcular el promedio de la fila y compararlo día por día).
* **7. Estadísticas:** consumo total de todos los hogares, hogar con mayor consumo, consumo promedio por persona por día y cantidad total de días con exceso.

---

### Reglas de rechazo

1. El consumo no puede ser negativo.
2. El consumo diario no puede superar los 5000 litros.
3. Las personas deben estar entre 1 y 20.
4. El hogar y el día deben existir.
5. El promedio por persona no se calcula si hay 0 personas.

---

### Archivo
Nombre y dos valores por hogar, seguido de la matriz.
