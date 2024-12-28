# Configurar entorno Allegro 5 sobre Windows y CLion 

### Probemas conocidos

La mayoría de los problemas que se han presentado han sido porque la versión del compilardor GCC utilizado sobre Windows no es compatible con la versión de Allegro 5.
Por ello varias opciones:

- Utilizar la versión de MinGW que viene con el instalador de Allegro 5.
- Descargar una versión de MinGW que sea la misma con la que se ha compilado Allegro 5.

### Configuración de CLion

#### Toolchain

CLion viene configurado con un compilador de C/C++ por defecto, pero este compilador puede que no sea compatible con la versión en la cual se ha compilado Allegro 5. 
Por ello, lo mejor es configurar el ToolChain que se configure dentro del entorno de desarrollo

## Pasos

1. Instalar MSYS2. 
   - Descargar el instalador de MSYS2 desde la página oficial: [MSYS2](https://www.msys2.org/)
   - Ejecutar el instalador y seguir las instrucciones.
   - Una vez instalado, MSYS2 viene con diferentes Environment, y tiene un terminal propio cada uno.
   - Abrir el terminal propio de ese entorno, y ejecutar los commandos en él.
     (En nuestro caso suponemos que se utiliza el entorno `MINGW64`)
   
2. Instalar MinGW64.
   - Ejecutar el siguiente comando:
     ```bash
     pacman -S mingw-w64-x86_64-gcc
     ```
     
3. Instalar Allegro 5.
   - Ejecutar el siguiente comando:
     ```bash
     pacman -S mingw-w64-x86_64-allegro
     ```

    Esto instalará Allegro 5 en el entorno de MinGW64, y se podrá utilizar en CLion.
    
    Rutas de instalación:
    - MinGW64: `C:\msys64\mingw64`
      - Allegro 5 (.h): `C:\msys64\mingw64\include\allegro5`
      - Allegro 5: (lib) `C:\msys64\mingw64\lib`
      - Allegro 5: (dll) `C:\msys64\mingw64\bin`

4. Configurar CLion con el Toolchain de MinGW64.
   - Abrir CLion y dirigirse a `File -> Settings -> Toolchains`
   - Crear un nuevo Toolchain con el botón `+` y seleccionar `MinGW64` y dar un nuevo nombre. (Ejemplo: `MinGW64-ALLEGRO5`)
   - En `toolset` seleccionar la ruta `C:\msys64\mingw64` y automáticamente se detectará el compilador y todo lo demás. 
   - Guardar los cambios.

5. Configurar el proyecto de CLion.

    - Abrir el proyecto en CLion.
    - Dirigirse a `File -> Settings -> Build, Execution, Deployment -> CMake`
    - En `CMake Profiles` agregar un nuevo perfil con el botón `+` y seleccionar `Debug-mingw-propio`.:
    - En `Toolchain` seleccionar el Toolchain creado anteriormente.
    - Guardar los cambios.

6. Configurar el archivo `CMakeLists.txt` del proyecto.

    - Agregar las siguientes líneas al archivo `CMakeLists.txt`:
    ```cmake
    set (SOURCE_FILES src/*.cpp src/*.h)  # Incluir todos ficheros .cpp y .h de la carpeta src 
   
    include_directories(src)  # Incluye la carpeta src
    # Vincula las bibliotecas de Allegro
    include_directories(${MSYS2_PATH}/include/allegro5) # Incluye .h de Allegro
    link_directories(${MSYS2_PATH}/lib) # Incluye las librerías de Allegro
    file(GLOB LIBRARIES "${MSYS2_PATH}/lib/*.dll.a") # Incluye las librerías .dll.a de Allegro  
    message("LIBRARIES = ${LIBRARIES}")  # Mensaje de depuración
    message("PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")

    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
    
    add_executable(${PROJECT_NAME} ${SOURCE_FILES})  # Nombre del ejecutable)

    TARGET_LINK_LIBRARIES(${PROJECT_NAME}  allegro_acodec allegro_audio allegro_color allegro_dialog allegro_image allegro_main allegro_memfile allegro_physfs allegro_primitives allegro_ttf allegro_font allegro)
    ```

Y con esto ya se debería poder compilar y ejecutar el proyecto en CLion.


