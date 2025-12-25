*Este proyecto ha sido creado como parte del currículo de 42 por macerver.*

# get_next_line

## Descripción
`get_next_line` es una función en C que lee y devuelve una línea completa desde un descriptor de archivo (`fd`) en cada llamada.

Objetivo del proyecto:
- Aprender a trabajar con `read()`, descriptores de archivo y memoria dinámica.
- Gestionar lecturas parciales usando un “buffer” de tamaño `BUFFER_SIZE`.
- Mantener el estado entre llamadas para poder devolver líneas sucesivas sin perder datos.

El proyecto incluye:
- Parte obligatoria: `get_next_line.c`, `get_next_line_utils.c`, `get_next_line.h`
- Parte bonus (multi-fd): `get_next_line_bonus.c`, `get_next_line_utils_bonus.c`, `get_next_line_bonus.h`

## Instrucciones

### Compilación (parte obligatoria)
```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c 
```

### Compilación (bonus)
```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c 
```

Notas:
- Puedes ajustar `BUFFER_SIZE` con `-D BUFFER_SIZE=<n>`.

## Algoritmo (explicación y justificación)

### Idea principal
La clave de `get_next_line` es conservar los bytes leídos que aún no forman una línea completa para reutilizarlos en la siguiente llamada.

Se usa un puntero estático (llamado `remember`):
- **Parte obligatoria**: un único `static char *remember;` (un solo `fd` a la vez).
- **Bonus**: `static char *remember[1024];` para mantener un remanente independiente por `fd`.

### Pasos por llamada
1. **Leer hasta encontrar un salto de línea o EOF**
	- Mientras el remanente no contenga `\n`, se hace `read(fd, buffer, BUFFER_SIZE)`.
	- El contenido leído se concatena al remanente.
	- Si `read()` devuelve `0`, es EOF; si devuelve `-1`, hay error.

2. **Extraer la línea a devolver**
	- Se busca el primer `\n` en el remanente.
	- La línea devuelta es el substring desde el inicio hasta `\n` (incluyéndolo si existe).

3. **Actualizar el remanente**
	- Se elimina del remanente la parte ya entregada y se conserva el resto.
	- Si no queda nada (resto vacío), se libera y se pone a `NULL`.

### Por qué este algoritmo
- Permite devolver líneas completas sin perder datos aunque `read()` entregue trozos arbitrarios.
- Evita re-lecturas: cada byte leído se conserva y se usa exactamente cuando corresponde.
- Es la solución estándar del proyecto porque separa claramente:
  - acumulación (lectura + concatenación)
  - extracción de línea
  - conservación del sobrante

### Complejidad
En cada llamada, el coste depende de los bytes necesarios hasta completar la línea.
- Tiempo: proporcional a los bytes procesados para esa línea (más el coste de concatenaciones/substring).
- Memoria: proporcional al tamaño del remanente acumulado (por `fd` en bonus).

## Recursos
- Manual de `read(2)` y `open(2)`: `man 2 read`, `man 2 open`
- Documentación sobre descriptores de archivo (Unix file descriptors): https://en.wikipedia.org/wiki/File_descriptor
- Video de: https://www.youtube.com/watch?v=4Ob7tCFaMHw&t=585s

### Uso de IA
Se utilizó IA como apoyo en tareas de:
- Al inicio del proyecto para entender la teoria sobre la lectura de archivos.
- Último repaso de casos límite (EOF, manejo de memoria, multi-fd en bonus) y de fugas de memoria.
- Redacción y estructuración de este `README.md` según los requisitos.
