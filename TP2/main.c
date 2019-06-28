#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "ArrayEmployees.h"
#include "utn.h"

#define QTY 20

//int menu(int *opcion);
int main()
{

int opcion=0;
int opcionInformes=0;
char auxName[51];
char auxlastName[51];
float auxSalary;
int auxSector;
int auxId;
float total;
float promedio;
int masQPromedio;
char seguir='s';


Employee employees[QTY];
initEmployees(employees,QTY);

employee_altaForzada(employees,QTY,"Jose","Gomez",35000,1);
employee_altaForzada(employees,QTY,"Juan","Perez",40000,2);
employee_altaForzada(employees,QTY,"Ana","Mena",60000,1);
employee_altaForzada(employees,QTY,"Maria","Paz",60000,2);

 do
     {
        //system("clear");
      //  menu(&opcion);
        printf("1- ALTA de un Empleado\n");
        printf("2- MODIFICACION de un Empleado\n");
        printf("3- BAJA de un Empleado\n");
        printf("4- lista ORDENADA\n");
        printf("5- INFORMES salario\n");
        printf("6- SALIR\n");
        scanf("%d",&opcion);
        switch(opcion)
        {
        case 1:
            addEmployee(employees,QTY,auxId,auxName,auxlastName,auxSalary,auxSector);
            break;
        case 2:
            employee_mostrar(employees,QTY);
            //printEmployees(employees,QTY);
            getValidInt("\nIngrese el Id del Empleado a modificar: ","\nError\n",&auxId,0,99999999,1);
            modifyEmployee(employees,QTY,auxId);
            break;
        case 3:
            getValidInt("\nIngrese el Id del Empleado a borrar: ","\nError\n",&auxId,0,99999999,1);
            removeEmployee(employees,QTY,auxId);
            //removeEmployee(employees,QTY,auxId);
            break;
        case 4:
            sortEmployees(employees,QTY,1);
            printEmployees(employees,QTY);
            break;
        case 5:
            promedioSalarios(employees,QTY);
            break;

        case 6:
            seguir='n';
            break;
        }
    } while(seguir=='s');
    return 0;
}

