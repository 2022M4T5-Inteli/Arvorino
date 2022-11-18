#include <iostream>
#include <ctime>

using namespace std;

// int iniciaHorario()
// {
//   time_t timer;
//   struct tm *horarioLocal;

//   time(&timer); // Obtem informações de data e hora
//   horarioLocal = localtime(&timer); // Converte a hora atual para a hora local

//   int dia = horarioLocal->tm_mday;
//   int mes = horarioLocal->tm_mon + 1;
//   int ano = horarioLocal->tm_year + 1900;

//   int hora = horarioLocal->tm_hour-3;
//   int min  = horarioLocal->tm_min;
//   int sec  = horarioLocal->tm_sec;

//   println("Horário: ") hora << ":" << min << ":" << sec << endl;
//   cout << "Data: "    << dia  << "/" << mes << "/" << ano << endl;

//   return 0;
// }