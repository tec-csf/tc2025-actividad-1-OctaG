/*
  Octavio Garduza Labastida
  A01021660

  Actividad 1

  Programa que simula un hospital utilizando memoria dinámica.

  Para modificar el puntero dentro de las funciones revise el siguiente link:
  https://stackoverflow.com/questions/766893/how-do-i-modify-a-pointer-that-has-been-passed-into-a-function-in-c
*/

#include <stdio.h>
#include <stdlib.h>

#define N 5 //Define el número de camas iniciales

typedef struct {
    char * nombre;
    char * apellidoPaterno;
    char * apellidoMaterno;
    char * telefono;
    int edad;
    int camaAsignada;
}paciente;

typedef struct{
    int numero;
}cama;


void ingresarPaciente(paciente ** inicio, paciente ** fin, int * cantidad,
                      cama **camasOcupadas, cama **finalCamasOcupadas,
                      cama **camasDisponibles, cama **finalCamasDisponibles);

//Libera la memoria utilizada por el paciente y pone su cama disponible
void darDeAlta(paciente **inicio, paciente **fin, int *cantidad,
               cama **camasDisponibles, cama **finalCamasDisponibles,
               cama **finalCamasOcupadas);

//Busca el paciente con el número de cama como llave
void buscarPaciente(paciente * inicio , paciente * fin);

void imprimirPaciente(paciente * paciente);

void imprimirPacientes(paciente * inicio , paciente * fin);

//Aumenta el número de camas en 5
void agregarCamas(cama **inicio, cama **fin);

//Regresa el número de camas disponibles/ocupadas
int contabilizarCamas(cama * inicio , cama * fin);

//Regresa el número de la primera cama disponible
int getCamaDisponible(cama *camasDisponibles);

void setAtributosDeCama(cama **inicio, cama **fin, int comienzo);

void setAtributosDePaciente(paciente ** inicio, paciente ** fin, int * cantidad,
                            cama **camasOcupadas, cama **finalCamasOcupadas,
                            cama **camasDisponibles, cama **finalCamasDisponibles);



int main(int argc, const char * argv[]){

  paciente * hospital;
  paciente * final_hospital;


  cama * camasDisponibles = (cama *) malloc(sizeof(cama) * N); //N camas
  cama * finalCamasDisponibles = camasDisponibles + N;

  setAtributosDeCama(&camasDisponibles, &finalCamasDisponibles, 0);

  cama * camasOcupadas = (cama *) malloc(sizeof(cama) * 0);
  cama * finalCamasOcupadas = camasOcupadas;

  int cantidad = 0;
  int opcion = 0;

  printf("\n\n--- BIENVENIDO AL SISTEMA ---\n\n");
  printf("¿Cuántos pacientes desea ingresar para comenzar?: ");
  scanf("%d", &cantidad);
  printf("\n\n");

  hospital = (paciente *) malloc(sizeof(paciente) * cantidad);
  final_hospital = hospital + cantidad;

  setAtributosDePaciente(&hospital, &final_hospital, &cantidad, &camasOcupadas, &finalCamasOcupadas, &camasDisponibles, &finalCamasDisponibles);
  do{
      printf("\nMENU:\nIngresar paciente (1)\nListado de pacientes ingresados (2)\nBuscar paciente por cama asignada (3)\nNúmero de camas disponbles (4)\nDar de alta (5)\nAgregar camas (6)\nSalir (0)\nSeleccione una opción: ");
      scanf("%d",&opcion);

      switch(opcion){
          case 0: break;
          case 1:
            printf("\n\n--- Ingresar nuevo paciente ---\n\n");
            ingresarPaciente(&hospital, &final_hospital, &cantidad, &camasOcupadas, &finalCamasOcupadas, &camasDisponibles, &finalCamasDisponibles);
            printf("\n\n");
            break;
          case 2:
            imprimirPacientes(hospital, final_hospital);
            break;
          case 3:
            buscarPaciente(hospital, final_hospital);
            break;
          case 4:
            printf("\n\n--- Resumen de disponibilidad ---\n\n");
            printf("\nCamas ocupadas: %d\n", contabilizarCamas(camasOcupadas, finalCamasOcupadas));
            printf("\nCamas disponibles: %d\n\n", contabilizarCamas(camasDisponibles, finalCamasDisponibles));
            break;
          case 5:
            darDeAlta(&hospital, &final_hospital, &cantidad, &camasDisponibles, &finalCamasDisponibles, &finalCamasOcupadas);
            break;
          case 6:
            agregarCamas(&camasDisponibles, &finalCamasDisponibles);
            break;
          default:
            printf("Opción no válida\n");
            break;
      }

  } while (opcion != 0);

  //Liberar la memoria
  for (paciente *aux = hospital; aux < final_hospital; ++aux) {
      free(aux->nombre);
      free(aux->apellidoPaterno);
      free(aux->apellidoMaterno);
      free(aux->telefono);
  }

  free(hospital);
  free(camasDisponibles);
  free(camasOcupadas);

  return 0;
}//Fin de main

void ingresarPaciente(paciente **inicio, paciente **final, int *cantidad,
                      cama **camasOcupadas, cama **finalCamasOcupadas, cama **camasDisponibles, cama **finalCamasDisponibles){

    *inicio = (paciente *) realloc(*inicio, sizeof(paciente) * (*cantidad + 1));
    *final = *inicio + *cantidad + 1;
    paciente *aux = *inicio + *cantidad;
    ++*cantidad;

    setAtributosDePaciente(&aux, final, cantidad, camasOcupadas, finalCamasOcupadas, camasDisponibles, finalCamasDisponibles);
}

void setAtributosDeCama(cama **inicio, cama **fin, int comienzo){
    cama *aux;
    int c = comienzo; //Numero de la primera cama
    for(aux = *fin; aux >= *inicio; --aux) {
        aux->numero = c;
        ++c;
    }
}

void setAtributosDePaciente(paciente **inicio, paciente **fin, int *cantidad,
                            cama **camasOcupadas, cama **finalCamasOcupadas,
                            cama **camasDisponibles, cama **finalCamasDisponibles){

  paciente *aux;
  for(aux = *inicio; aux < *fin; ++aux) {
    aux->nombre = (char *) malloc(sizeof(char) * 25);

    printf("Ingrese el nombre del paciente: ");
    scanf("%s", aux->nombre);

    aux->apellidoPaterno = (char *) malloc(sizeof(char) * 25);

    printf("Ingrese el apellido paterno del paciente: ");
    scanf("%s", aux->apellidoPaterno);

    aux->apellidoMaterno = (char *) malloc(sizeof(char) * 25);

    printf("Ingrese el apellido materno del paciente: ");
    scanf("%s", aux->apellidoMaterno);

    aux->telefono = (char *) malloc(sizeof(char) * 10);

    printf("Ingrese el teléfono de contacto del paciente: ");
    scanf("%s", aux->telefono);

    printf("Ingrese la edad del paciente: ");
    scanf("%d", &aux->edad);

    //Si hay camas disponibles
    if(contabilizarCamas(*camasDisponibles, *finalCamasDisponibles) > 0){
        *camasOcupadas = (cama *) realloc(*camasOcupadas, sizeof(cama) * 1);
        ++*finalCamasOcupadas;
        --*finalCamasDisponibles;
        aux->camaAsignada = getCamaDisponible(*finalCamasDisponibles); //Asigna el número de la primera cama disponible;
    }else{
        printf("No hay más camas disponibles. A este paciente no se le asignará cama");
        aux->camaAsignada = 0;
    }
    printf("\n");
  }
}

int getCamaDisponible(cama *finalCamasDisponibles){return finalCamasDisponibles->numero;}

void imprimirPaciente(paciente * paciente){

    if(paciente->nombre){
      printf("Nombre: %s %s %s\nTeléfono de contacto: %s\nEdad: %d\nCama asignada: %d\n\n",
        paciente->nombre,
        paciente->apellidoPaterno,
        paciente->apellidoMaterno,
        paciente->telefono,
        paciente->edad,
        paciente->camaAsignada);
      printf("------------------------------\n");
    }
}

void imprimirPacientes(paciente * inicio, paciente * fin){
  paciente * aux;
  // Mostrar los libros
  printf("\n\n--- Listado de Pacientes ---\n\n");
  for(aux = inicio; aux < fin; ++aux){
      imprimirPaciente(aux);
  }
}

void buscarPaciente(paciente * inicio , paciente * fin){
  paciente *aux;
  int encontrado = 0;
  int camaBuscada;

  printf("\n\n--- Busqueda de pacientes ---\n\n");

  printf("\nIngrese el número de cama que desea buscar: ");
  scanf("%d", &camaBuscada);

  //Mostrar los pacientes
  printf("\n--- Paciente en la cama %d ---\n\n", camaBuscada);
  for(aux = inicio; aux <= fin; ++aux){
    if(aux->camaAsignada == camaBuscada){
      imprimirPaciente(aux);
      encontrado = 1;
    }
  }
  if(encontrado == 0){
    printf("La cama número %d no tiene un paciente o no existe\n", camaBuscada);
  }
}

void darDeAlta(paciente **inicio, paciente **fin, int *cantidad,
               cama **camasDisponibles, cama **finalCamasDisponibles,
               cama **finalCamasOcupadas){

  paciente *aux;
  cama *ultimaCamaDisponible = *finalCamasDisponibles;

  int camaBuscada;
  int encontrado = 0;

  printf("\n\n--- Dar de alta a un paciente---\n\n");

  printf("\nIngrese el número de cama del paciente al que desea dar de alta: ");
  scanf("%d", &camaBuscada);

  for(aux = *inicio; aux <= *fin; ++aux){
    if(aux->camaAsignada == camaBuscada){
      encontrado = 1;
      //Igualar a null para no imprimir
      aux->nombre = NULL;
      aux->apellidoPaterno = NULL;
      aux->apellidoMaterno = NULL;
      aux->telefono = NULL;
      //Liberar memoria
      free(aux->nombre);
      free(aux->apellidoPaterno);
      free(aux->apellidoMaterno);
      free(aux->telefono);
      //Agregar una cama a disponibles
      *camasDisponibles = (cama *) realloc(*camasDisponibles, sizeof(cama) * (*cantidad + 1));
      ++*finalCamasDisponibles;
      ultimaCamaDisponible->numero = camaBuscada;
      --*finalCamasOcupadas;
    }
  }
  if(encontrado == 0){
    printf("\nLa cama buscada no tiene un paciente o no existe\n");
  }
}


int contabilizarCamas(cama *inicio, cama *fin){
    cama *aux = inicio;
    while (aux++ != fin){};
    return (aux - inicio - 1);
}

void agregarCamas(cama **inicio, cama **fin){
    printf("\n");
    cama *preFin = *fin; //Apunta a la última cama antes del incremento
    *inicio = (cama *) realloc(*inicio, sizeof(cama) * 5);
    *fin +=5;
    setAtributosDeCama(inicio, fin, getCamaDisponible(preFin));
    printf("\nSe han agregado 5 camas exitosamente\n");
}
