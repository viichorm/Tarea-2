# Base de Datos de Películas 

# Descripción

Este programa en C permite a los usuarios cargar películas desde un archivo CSV y realizar búsquedas por diferentes criterios, como ID, género, director ,década de estreno y finalmente utilizando los dos criterios que son la decada y el genero. Proporciona un menú interactivo que permite al usuario seleccionar entre varias opciones de búsqueda y visualización de películas.

# Cómo compilar y ejecutar

Para compilar y ejecutar el programa, sigue estos pasos:

1. Clona este repositorio en tu máquina local.
2. Abre una terminal y navega hasta el directorio del repositorio clonado.
3. Compila el código utilizando un compilador de C compatible (por ejemplo, `gcc main.c tdas/*.c -o main`).
4. Ejecuta el programa compilado (`./main`).

En caso de no poder compilar u ejecutar correctamente, puede acceder directamente al replit donde se desarrollo el programa 
**[ACCEDER AL REPLIT](https://replit.com/@VicenteMart1neZ/Tarea22)**

# Funcionalidades

## Funcionando correctamente:

 - **Cargar Películas**: Permite cargar películas desde un archivo CSV y almacenarlas en un mapa por ID.
- **Buscar por ID**: Permite al usuario buscar una película por su ID y muestra su información detallada.
- **Buscar por género**: Permite al usuario buscar películas por género y muestra las coincidencias encontradas.
- **Buscar por director**: Permite al usuario buscar películas por el nombre del director y muestra las coincidencias encontradas.
- **Buscar por década**: Permite al usuario buscar películas estrenadas en una década específica y muestra las coincidencias encontradas.
- **Buscar por década y género**: Permite al usuario buscar películas por género y década de estreno, mostrando las coincidencias encontradas.

## Problemas conocidos:

- No se reportan problemas generales en las funcionalidades implementadas. Detalles como casos muy especiales, pueden estar afectados a la ejecucion del programa.

## A mejorar:

- Mejorar la eficiencia de las búsquedas y la carga de películas para manejar grandes volúmenes de datos.
- Implementar opciones de edición y eliminación de películas en el menú principal.
- Mejorar la presentación de la información mostrada al usuario para que sea más legible y atractiva.

# Ejemplo de uso



## **Opción 1: Cargar Películas**
- El usuario selecciona la opción "Cargar Películas" desde el menú principal.
- El programa carga las películas desde el archivo CSV proporcionado y las almacena en un mapa por ID.
- Se muestra un mensaje indicando la carga exitosa de las películas.

```
Ingrese su opción: 1

Lista de peliculas cargadas correctamente

Presione Enter para continuar...
```


## **Opción 2: Buscar por ID**


- El usuario selecciona la opción "Buscar por ID" desde el menú principal.
- Se le solicita al usuario que ingrese el ID de la película que desea buscar.
- El programa muestra la información detallada de la película correspondiente al ID proporcionado.
  
```
Ingrese su opción: 2
Ingrese el id de la película: tt0040982

Título: You Gotta Stay Happy, Director: H.C. Potter, Walter Lantz", Año: 1948
Géneros: Comedy Romance

Presione Enter para continuar...

```

## **Opción 3: Buscar por género**


- El usuario selecciona la opción "Buscar por género" desde el menú principal.
- Se le solicita al usuario que ingrese el género de películas que desea buscar.
- El programa muestra las películas encontradas que coinciden con el género especificado.


```
Ingrese su opción: 3
Ingrese el género de películas a buscar: romance

*Listado de peliculas con el genero romance

Presione Enter para continuar...
```


## **Opción 4: Buscar por director**


- El usuario selecciona la opción "Buscar por director" desde el menú principal.
- Se le solicita al usuario que ingrese el nombre del director de películas que desea buscar.
- El programa muestra las películas dirigidas por el director especificado.

```
Ingrese su opción: 4
Ingrese el nombre del director de películas a buscar: Clint eastwood
ID: tt0105695, Título: Unforgiven, Año: 1992
ID: tt0327056, Título: Mystic River, Año: 2003
ID: tt0405159, Título: Million Dollar Baby, Año: 2004
ID: tt0075029, Título: The Outlaw Josey Wales, Año: 1976
ID: tt0107808, Título: A Perfect World, Año: 1993
ID: tt0498380, Título: Letters from Iwo Jima, Año: 2006
ID: tt1616195, Título: J. Edgar, Año: 2011
ID: tt1212419, Título: Hereafter, Año: 2010
ID: tt0086383, Título: Sudden Impact, Año: 1983
ID: tt0824747, Título: Changeling, Año: 2008
ID: tt0076070, Título: The Gauntlet, Año: 1977
ID: tt0119668, Título: Midnight in the Garden of Good and Evil, Año: 1997
ID: tt0068699, Título: High Plains Drifter, Año: 1973
ID: tt0309377, Título: Blood Work, Año: 2002
ID: tt0118548, Título: Absolute Power, Año: 1997

Presione Enter para continuar...
```

## **Opción 5: Buscar por década**

- El usuario selecciona la opción "Buscar por década" desde el menú principal.
- Se le solicita al usuario que ingrese la década de películas que desea buscar.



- El programa muestra las películas estrenadas en la década especificada.

```
Ingrese su opción: 5
Ingrese la década de películas a buscar (ejemplo: 1980, 2010): 2010

*Listado de peliculas de la decada del 2010 (2010 hasta 2019)

Presione Enter para continuar...
```


## **Opción 6: Buscar por década y género**


- El usuario selecciona la opción "Buscar por década y género" desde el menú principal.
- Primero ingresa la decada y posteriormente el genero
- El programa muestra las películas encontradas que coinciden con la década y género especificados.

```
Ingrese la década de películas a buscar (ejemplo: 1980, 2010): 2010
Ingrese el género de películas a buscar: Romance

ID: tt1605783, Título: Midnight in Paris, Año: 2011
ID: tt1311071, Título: Kill Your Darlings, Año: 2013
ID: tt1120985, Título: Blue Valentine, Año: 2010
ID: tt1655442, Título: The Artist, Año: 2011
ID: tt1532503, Título: Beginners, Año: 2010
ID: tt1570728, Título: Crazy, Stupid, Love., Año: 2011
ID: tt1334260, Título: Never Let Me Go, Año: 2010
ID: tt1045658, Título: Silver Linings Playbook, Año: 2012
ID: tt1748122, Título: Moonrise Kingdom, Año: 2012
ID: tt1616195, Título: J. Edgar, Año: 2011
ID: tt1229822, Título: Jane Eyre, Año: 2011
ID: tt1212419, Título: Hereafter, Año: 2010
ID: tt0758752, Título: Love & Other Drugs, Año: 2010
ID: tt1412386, Título: The Best Exotic Marigold Hotel, Año: 2011
ID: tt1336617, Título: Cyrus, Año: 2010
ID: tt1758692, Título: Like Crazy, Año: 2011

Presione Enter para continuar...
```


## Contribuciones ##

**Vicente Martinez**:
- Desarrollo en solitario del codigo, juntos con las funciones.

![d63ac5bcd7d3832dfb44ad829317fbff2ba5b6cf_128](https://github.com/viichorm/Tarea-2/assets/125922459/986606ce-420d-4121-84f2-3cf7e7251010)





  
