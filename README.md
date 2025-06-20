# Agenda de Contactos en C

Este es un proyecto desarrollado en lenguaje C que simula una agenda de contactos en consola. Permite agregar, buscar, modificar, eliminar y mostrar contactos utilizando archivos binarios y memoria dinámica. Además, incluye mejoras visuales con colores para una mejor experiencia de usuario en terminal.

## 🧩 Funcionalidades

- Agregar nuevos contactos
- Buscar contactos por nombre o número
- Modificar información de un contacto existente
- Eliminar contactos
- Mostrar todos los contactos ordenados alfabéticamente
- Guardado en archivo binario
- Interfaz mejorada con colores usando la API de Windows

## 🛠️ Tecnologías utilizadas

- Lenguaje C
- Manejo de punteros
- Funciones: `realloc`, `fseek`, `ftell`, `fwrite`, `fread`
- Estructuras (`struct`)
- Consola de Windows (`SetConsoleTextAttribute` para colores)

## 🖼️ Capturas y descripción de funciones

### 📋 `mostrarMenu()`
Muestra el menú principal y ejecuta las opciones seleccionadas por el usuario.

### ➕ `agregarContacto()`
Guarda un nuevo contacto en el archivo binario pidiendo nombre, número, email y dirección.

### 🔍 `buscarContacto()`
Permite buscar un contacto:
- Opción 1: por nombre
- Opción 2: por número

### ✏️ `modificarContacto()`
Permite modificar un contacto existente buscando por nombre y actualizando sus datos.

### ❌ `eliminarContacto()`
Elimina un contacto del archivo binario.

### 📑 `mostrarContactos()`
Muestra una lista de todos los contactos ordenados alfabéticamente.

## ▶️ Cómo compilar

1. Asegurate de tener un compilador como `gcc` instalado.
2. Ejecutá los siguientes comandos:

```bash
gcc agenda.c -o agenda
./agenda
```

## 👨‍💻 Autor

Martin Robledo
