#include "tdas/extra.h"
#include "tdas/list.h"
#include "tdas/map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

typedef struct {
  char id[100];
  char title[100];
  List *genres;
  char director[300];
  float rating;
  int year;
} Film;

void borrarComillas(char *str) { 

    int len = strlen(str); //Obtenemos la longitud de la cadena

    if (str[0] == '"') { //SI el primer carácter es una comilla:

        memmove(str, str + 1, len); //Movemos el inicio de la cadena a un espacio a la derecha

        len--; //Bajamos en 1 el tamaño de la cadena

    }

    if (len > 0 && str[len - 1] == '"') { //Si el último carácter es una comilla

        str[len - 1] = '\0'; //Lo cambiamos al carácter nulo para que ahí termine la cadena.

    }

}

char *espacioInicial(char *str) {

    while (isspace((unsigned char)*str)) str++; //Mientras el primer carácter es un espacio, avanzamos el puntero del inicio de la cadena

    return str; //Retornamos la cadena cambiada

}
// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("****************************************");
  puts("****************************************");
  puts("****** Base de Datos de Películas ******");
  puts("****************************************");
  puts("****************************************");

  puts("\n1) Cargar Películas");
  puts("2) Buscar por id");
  puts("3) Buscar por género");
  puts("4) Buscar por director");
  puts("5) Buscar por década");
  puts("6) Buscar por década y género");
  puts("7) Salir");
}

/**
 * Compara dos claves de tipo string para determinar si son iguales.
 * Esta función se utiliza para inicializar mapas con claves de tipo string.
 *
 * @param key1 Primer puntero a la clave string.
 * @param key2 Segundo puntero a la clave string.
 * @return Retorna 1 si las claves son iguales, 0 de lo contrario.
 */
int is_equal_str(void *key1, void *key2) {
  return strcmp((char *)key1, (char *)key2) == 0;
}

/**
 * Compara dos claves de tipo entero para determinar si son iguales.
 * Esta función se utiliza para inicializar mapas con claves de tipo entero.
 *
 * @param key1 Primer puntero a la clave entera.
 * @param key2 Segundo puntero a la clave entera.
 * @return Retorna 1 si las claves son iguales, 0 de lo contrario.
 */
int is_equal_int(void *key1, void *key2) {
  return *(int *)key1 == *(int *)key2; // Compara valores enteros directamente
}

/**
 * Carga películas desde un archivo CSV y las almacena en un mapa por ID.
 */

void cargar_peliculas(Map *pelis_byid) {
  // Intenta abrir el archivo CSV que contiene datos de películas
  FILE *archivo = fopen("data/Top1500.csv", "r");
  if (archivo == NULL) {
    perror(
        "Error al abrir el archivo"); // Informa si el archivo no puede abrirse
    return;
  }

  char **campos;
  // Leer y parsear una línea del archivo CSV. La función devuelve un array de
  // strings, donde cada elemento representa un campo de la línea CSV procesada.
  campos = leer_linea_csv(archivo, ','); // Lee los encabezados del CSV

  // Lee cada línea del archivo CSV hasta el final
  while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
    // Crea una nueva estructura Film y almacena los datos de cada película
    Film *peli = (Film *)malloc(sizeof(Film));
    strcpy(peli->id, campos[1]);        // Asigna ID
    strcpy(peli->title, campos[5]);     // Asigna título
    strcpy(peli->director, campos[14]); // Asigna director
    peli->genres = list_create(); //Creamos la lista de géneros de la película

    borrarComillas(campos[11]); //Borramos las comillas en caso de que haya

    char *token = strtok(campos[11], ","); //Cortamos el campo de géneros hasta una coma

    while (token != NULL) { //Mientras token no sea NULL

        char *clean_token = espacioInicial(token);
          list_pushBack(peli->genres, strdup(clean_token)); //Ahora agregamos el género a la lista de géneros de la película

          token = strtok(NULL, ","); //Volvemos a cortar la siguiente parte de la cadena hasta la coma

      }
    
    peli->year =
        atoi(campos[10]); // Asigna año, convirtiendo de cadena a entero

    // Inserta la película en el mapa usando el ID como clave
    map_insert(pelis_byid, peli->id, peli);
  }
  fclose(archivo); // Cierra el archivo después de leer todas las líneas


  // Itera sobre el mapa para mostrar las películas cargadas
  MapPair *pair = map_first(pelis_byid);
  while (pair != NULL) {
    Film *peli = pair->value;
    printf("ID: %s, Título: %s, Director: %s, Año: %d\n", peli->id, peli->title,
           peli->director, peli->year);
    pair = map_next(pelis_byid); // Avanza al siguiente par en el mapa
  }
}

// Función para buscar y mostrar la información de una película por su ID en un mapa.
void buscar_por_id(Map *pelis_byid) {
  char id[100]; // Buffer para almacenar el ID de la película

  // Solicita al usuario el ID de la película
  printf("Ingrese el id de la película: ");
  scanf("%s", id); // Lee el ID del teclado

  // Busca el par clave-valor en el mapa usando el ID proporcionado
  MapPair *pair = map_search(pelis_byid, id);

  // Si se encontró el par clave-valor, se extrae y muestra la información de la película
  if (pair != NULL) {
    Film *peli = pair->value; // Obtiene el puntero a la estructura de la película
    // Muestra el título, director, año y géneros de la película
    printf("Título: %s, Director: %s, Año: %d\nGéneros:", peli->title, peli->director, peli->year);
    void *current = list_first(peli->genres);
    while (current != NULL) {
      printf(" %s", (char *)current); // Muestra cada género de la lista
      current = list_next(peli->genres);
    }
    printf("\n");
  } else {
    // Si no se encuentra la película, informa al usuario
    printf("La película con id %s no existe\n", id);
  }
}


void buscar_por_genero(Map *pelis_byid) {
  char genero[100];
  printf("Ingrese el género de películas a buscar: ");
  MapPair *pair = map_first(pelis_byid);
  int c;
  while ((c = getchar()) != '\n' && c != EOF) { }

  fgets(genero, sizeof(genero), stdin);
  genero[strcspn(genero, "\n")] = 0;

  for (int i = 0; genero[i]; i++) {
    genero[i] = tolower(genero[i]);
  }

  int found = 0;
  while (pair != NULL) {
    Film *peli = pair->value;
    void *current = list_first(peli->genres);
    while (current != NULL) {
      char current_genre[100];
      strcpy(current_genre, (char *)current);
      for (int i = 0; current_genre[i]; i++) {
        current_genre[i] = tolower(current_genre[i]);
      }
      if (strcmp(current_genre, genero) == 0) {
        printf("ID: %s, Título: %s, Año: %d\n", peli->id, peli->title, peli->year);
        found = 1;
        break;
      }
      current = list_next(peli->genres);
    }
    pair = map_next(pelis_byid);
  }

  if (!found) {
    printf("No se encontraron películas del género %s\n", genero);
  }
}


void buscar_por_director(Map *pelis_byid) {
  char director[300]; // Buffer para almacenar el nombre del director ingresado por el usuario
  printf("Ingrese el nombre del director de películas a buscar: ");

  // Solicita al usuario el nombre del director de películas a buscar
  do {
    
    fgets(director, sizeof(director), stdin);
    size_t len = strlen(director);
    if (len > 0 && director[len - 1] == '\n') {
      director[len - 1] = '\0';
    }
  } while (strlen(director) == 0);

  // Convertir el nombre del director ingresado por el usuario a minúsculas
  for (int i = 0; director[i]; i++) {
    director[i] = tolower(director[i]);
  }

  // Itera sobre el mapa para buscar películas dirigidas por el director especificado
  MapPair *pair = map_first(pelis_byid);
  int found = 0; // Variable para rastrear si se encontró alguna película dirigida por el director especificado
  while (pair != NULL) {
    Film *peli = pair->value;
    // Convertir el nombre del director almacenado en la película a minúsculas
    char director_peli[300];
    strcpy(director_peli, peli->director);
    for (int i = 0; director_peli[i]; i++) {
      director_peli[i] = tolower(director_peli[i]);
    }
    // Verifica si la película fue dirigida por el director especificado
    if (strcasecmp(director_peli, director) == 0) {
      // Si la película fue dirigida por el director especificado, la muestra y actualiza el indicador de encontrada
      printf("ID: %s, Título: %s, Año: %d\n", peli->id, peli->title, peli->year);
      found = 1;
    }
    pair = map_next(pelis_byid); // Avanza al siguiente par en el mapa
  }
  // Si no se encontraron películas dirigidas por el director especificado, informa al usuario
  if (!found) {
    printf("No se encontraron películas dirigidas por %s\n", director);
    sleep(3);
  }
}

void buscar_por_decada(Map *pelis_byid) {
  char decada[5]; // Buffer para almacenar la década ingresada por el usuario
  printf("Ingrese la década de películas a buscar (ejemplo: 1980, 2010): ");

  // Solicita al usuario la década de películas a buscar
  do {
    fgets(decada, sizeof(decada), stdin);
    size_t len = strlen(decada);
    if (len > 0 && decada[len - 1] == '\n') {
      decada[len - 1] = '\0';
    }
  } while (strlen(decada) == 0);

  // Convertir la década ingresada por el usuario a un número entero
  int decada_int = atoi(decada);

  // Itera sobre el mapa para buscar películas estrenadas en la década especificada
  MapPair *pair = map_first(pelis_byid);
  int found = 0; // Variable para rastrear si se encontró alguna película estrenada en la década especificada
  while (pair != NULL) {
    Film *peli = pair->value;
    // Determina la década de estreno de la película
    int decada_estreno = peli->year / 10 * 10;

    // Verifica si la película fue estrenada en la década especificada
    if (decada_estreno == decada_int) {
      // Si la película fue estrenada en la década especificada, la muestra y actualiza el indicador de encontrada
      printf("ID: %s, Título: %s, Año: %d\n", peli->id, peli->title, peli->year);
      found = 1;
    }
    pair = map_next(pelis_byid); // Avanza al siguiente par en el mapa
  }
  // Si no se encontraron películas estrenadas en la década especificada, informa al usuario
  if (!found) {
    printf("No se encontraron películas estrenadas en la década %s\n", decada);
    sleep(3);
  }
}

void buscar_por_decada_y_genero(Map *pelis_byid) {
  char decada[5];
  char genero[100];
  
  printf("Ingrese la década de películas a buscar (ejemplo: 1980, 2010): ");
  do {
    fgets(decada, sizeof(decada), stdin);
    size_t len = strlen(decada);
    if (len > 0 && decada[len - 1] == '\n') {
      decada[len - 1] = '\0';
    }
  } while (strlen(decada) == 0);

  // Convertir la década ingresada por el usuario a un número entero
  int decada_int = atoi(decada);

  
  printf("Ingrese el género de películas a buscar: ");
  int c;
  while ((c = getchar()) != '\n' && c != EOF) { }

  fgets(genero, sizeof(genero), stdin);
  genero[strcspn(genero, "\n")] = 0;

  for (int i = 0; genero[i]; i++) {
    genero[i] = tolower(genero[i]);
  }

  MapPair *pair = map_first(pelis_byid);
  int found = 0;
  while (pair != NULL) {
    Film *peli = pair->value;
    int decada_estreno = peli->year / 10 * 10;

    if (decada_estreno == decada_int) {
      void *current = list_first(peli->genres);
      while (current != NULL) {
        char current_genre[100];
        strcpy(current_genre, (char *)current);
        for (int i = 0; current_genre[i]; i++) {
          current_genre[i] = tolower(current_genre[i]);
        }
        if (strcmp(current_genre, genero) == 0) {
          printf("ID: %s, Título: %s, Año: %d\n", peli->id, peli->title, peli->year);
          found = 1;
          break;
        }
        current = list_next(peli->genres);
      }
    }
    pair = map_next(pelis_byid);
  }

  if (!found) {
    printf("No se encontraron películas estrenadas en la década %s del género %s\n", decada, genero);
  }
}

int main() {
  char opcion; // Variable para almacenar una opción ingresada por el usuario
               // (sin uso en este fragmento)

  // Crea un mapa para almacenar películas, utilizando una función de
  // comparación que trabaja con claves de tipo string.
  Map *pelis_byid = map_create(is_equal_str);

  // Recuerda usar un mapa por criterio de búsqueda

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion);

    switch (opcion) {
    case '1':
      cargar_peliculas(pelis_byid);
      break;
    case '2':
      buscar_por_id(pelis_byid);
      break;
      case '3':
      fflush(stdin); // Limpiar el buffer de entrada antes de solicitar la entrada del género
      buscar_por_genero(pelis_byid);
      break;
    case '4':
      buscar_por_director(pelis_byid);
      break;
    case '5':
      buscar_por_decada(pelis_byid);
      break;
    case '6':
      buscar_por_decada_y_genero(pelis_byid);
      break;
    default:
      printf("Muchas gracias.\n");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '7');

  return 0;
}

// 7:16 AM 5/5/2024 ---- Todas mis funciones finalmente estan hechas.... mds.....
// 7:17 AM 5/5/2024 ---- Ahora solo falta ordenar un poco y que todo sea mas legible....
