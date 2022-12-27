#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

int main(int argc, char** argv) {
  // Crea una cadena que contenga el código binario
  char code[] = "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41";

  // Mapea el código binario en la memoria del proceso
  void* mem = mmap(NULL, sizeof(code), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (mem == MAP_FAILED) {
    perror("mmap failed");
    return 1;
  }

  // Copia el código binario en el espacio mapeado
  memcpy(mem, code, sizeof(code));

  // Cambia los permisos de memoria a lectura y ejecución
  if (mprotect(mem, sizeof(code), PROT_READ | PROT_EXEC) != 0) {
    perror("mprotect failed");
    return 1;
  }

  // Define una función que apunte al código mapeado
  void (*func)() = mem;

  // Ejecuta el código binario
  func();

  // Limpia la memoria mapeada
  munmap(mem, sizeof(code));
  return 0;
}
