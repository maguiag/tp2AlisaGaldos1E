#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "utn.h"
#include "ArrayEmployees.h"
//prototipos privados
static int obtenerEspacioLibre(Employee* list, int limite);
static int proximoId(void);

/** \brief Inicializa la estructura
 *
 * \param  Empleados* Estructura que representa empleado
 * \param limite int cantidad maxima de items en la estructura.
 * \return [-1] Error [0] Ok
 *
 */
int initEmployees(Employee* list,int limite)
{
    int retorno = -1;
    int i;
    if(limite>0 && list!=NULL)
    {
        retorno = 0;
        for(i=0; i<limite; i++)
        {
            list[i].isEmpty=1;
        }
    }
    return retorno;
}

/** \brief Busca los espacios libres en el array de la estructura
 *
 * \param  Empleados* Estructura que representa empleado.
 * \param limite int cantidad maxima de items en la estructura.
 * \return  [-1] Error [0] Ok.
 *
 */
static int obtenerEspacioLibre(Employee* list, int limite)
{
    int retorno = -1;
    int i;
    if(limite>0 && list!=NULL)
    {
        for(i=0; i<limite; i++)
        {
            if(list[i].isEmpty==1)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}
/** \brief Incrementa el Id
 *
 * \return int devuelve el valor del Id que va a ser usado en el próximo alta.
 *
 */
static int proximoId()
{
    static int proximoId;
    proximoId++;
    return proximoId;
}

/** \brief Carga empleado al array
 *
 * \param Empleados*, maxima de iems en la estructura, id, nombre
 * \param apellido, salario, sector
 * \return [0] Ok, -2 si null && <0, -3 si pBuffer[i].isEmpty==0
 *
 */
int addEmployee(Employee* list, int len, int id, char name[],char lastName[],float salary,int sector)
{
    int i;
    int retorno=-1;
    char auxName[51];
    char auxLastName[51];
    int auxSector;
    float auxSalary;


    if(list!=NULL && len>0)
    {
        i=obtenerEspacioLibre(list,len);
        if(i>0)
        {
            if(!getValidString("\nIngrese nombre: ","\nError\n","\nErrror\n",auxName,51,2))
            {
                if(!getValidString("\nIngrese apellido: ","\nError \n","\nError",auxLastName,51,2))
                {
                    if(!getValidInt("\nIngrese el sector(1-Sistemas 2-Administracion 3-RRHH): \n","Error\n",&auxSector,0,4,2))
                    {
                        if(!getValidFloat("\nIngrese el salario del empleado: ","Ese no es un salario valido\n",&auxSalary,0,99999999,2)
                          )
                        {
                            strncpy(list[i].name,auxName,51);
                            strncpy(list[i].lastName,auxLastName,51);
                            list[i].salary=auxSalary;
                            list[i].sector=auxSector;
                            list[i].id=proximoId();
                            list[i].isEmpty=0;
                            retorno =0;
                            printf("carga exitosa");

                        }
                    }
                }
            }
        }
    }
    return retorno;
}



/** \brief Encuentra Empleado segun Id
 *
 * \param Empleados*, cant max de elementos del array y el id
 * \return [0] si ok, [-1] si eror
 *
 */

int findEmployeeById(Employee* list, int len,int id)
{
    int i;
    int retorno=-1;
    if(list!=NULL && len >0)
    {
        for(i=0; i<len; i++)
            if(list[i].id==id && list[i].isEmpty==0)
            {
                return i;// posicion del id buscado
                break;
            }
    }
    return retorno;

}

/** \brief modifica empleado
 *
 * \param Empleados*
 * \param len
 * \param id a modificar
 * \return  1 si error, [0] Ok.
 *
 */

int modifyEmployee(Employee* list, int len, int idAModif)
{
    char rta;
    int retorno=-1;
    int index=findEmployeeById(list,len,idAModif);
    char auxNombre[51];
    char auxLastName[51];
    float auxSalary;
    int auxSector;

    if(index>=0)
    {
        if(list!=NULL && len>0)
        {
            fflush(stdin);
            {
                fflush(stdin);
                if(!getValidInt("Seleccione el elemento a modificar: \n1-Nombre\n2-Apellido\n3-Salario\n4-Sector\n5-Cancelar\n",
                                "error",&rta,0,6,2));
                {
                    switch(rta)
                    {
                    case 1:
                        printf("A modificar el nombre: %s\n", list[idAModif-1].name);
                        if(!getValidString("Ingrese modificacion nombre \n","error","Error",auxNombre,51,2))
                        {
                            strncpy(list[idAModif-1].name,auxNombre,51);
                        }
                        break;
                    case 2:
                        printf("A modificar el apellido: %s\n", list[idAModif-1].lastName);
                        if(!getValidString("Ingrese modificacion apellido \n","error","Error",auxLastName,51,2))
                        {
                            strncpy(list[idAModif-1].lastName,auxLastName,51);
                        }
                        break;
                    case 3:
                        printf("A modificar el salario: %f\n", list[idAModif-1].salary);
                        if(!getValidFloat("Ingrese nuevo salario \n","error",&auxSalary,0,999999999,2));
                        {
                            list[idAModif-1].salary=auxSalary;
                        }
                        break;
                    case 4:
                        printf("A modificar el sector: %d\n", list[idAModif-1].sector);
                        if(!getValidInt("Ingrese nuevo sector 1(Sistemas) 2(Administracion) 3(RRHH): \n","error",&auxSector,0,4,2));
                        {
                            list[idAModif-1].sector=auxSector;
                        }
                        break;
                    case 5:
                        printf("Volviendo al menu principal");
                        break;
                    }
                }
            }
        }
    }
    return 0;
}


/** \brief Remueve empleado del array
 *
 * \param *Empleados, cant max de elem en el array
 * \param id
 * \return  [0] si ok, [-1] si error
 *
 */

int removeEmployee(Employee* list, int len, int id)
{
    int retorno=-1;
    int i;

    if(len>0 && list!=NULL)
    {
        retorno=-2;
        for(i=0; i<len; i++)
        {
            if(!list[i].isEmpty && list[i].id==id)
            {
                list[i].isEmpty=1;
                retorno=0;
                break;
            }
        }
    }

    return retorno;
}

/** \brief Ordena Empleados
 *
 * \param *Empleados, cant max de elem en el array
 * \param orden
 * \return [0] si ok, [-1] si error
 *
 */

int sortEmployees(Employee* list, int len, int order)
{
    int retorno=-1;
    int i;
    int flag;

    Employee auxiliarEstructura;

    if(len>0 && list!=NULL)
    {
        do
        {
            flag=0;
            for(i=0; i<len; i++)
            {
                if(!list[i].isEmpty && !list[i+1].isEmpty)
                {
                    if((strcmp(list[i].lastName, list[i+1].lastName)>0 && order) ||
                            (strcmp(list[i].lastName, list[i+1].lastName)<0 && !order))
                    {
                        auxiliarEstructura =list[i];
                        list[i] = list[i+1];
                        list[i+1] =auxiliarEstructura;
                        flag=1;
                    }
                }
            }
        }
        while(flag);
    }

    return retorno;
}

/** \brief Inprime array Empleados
 *
 * \param *Empleados
 * \param cant maxima de elem del array
 * \return [0] si ok, [-1] si error
 *
 */

int printEmployees(Employee* list,int len)
{
    int i;
    int retorno=-1;
    if(len>0 && list!=NULL)
    {
        printf("\n\n Listado de Empleados \n");
        for(i=0; i<len; i++)
        {
            if(list[i].isEmpty==0)
            {
                fflush(stdin);
                printf("Id: %d\tNombre: %s\tApellido: %s\tSalario: %.2f\tSector: %d\n",list[i].id,
                       list[i].name,
                       list[i].lastName,
                       list[i].salary,
                       list[i].sector);
            }
        }
        printf("\n");
        return 0;
    }
    return retorno;
}

/** \brief informa promedio y salariosobre promedio
 *
 * \param *Empleado
 * \param limite int cantidad maxima del array
 * \return [0] si ok, [-1] si error
 *
 */

int promedioSalarios(Employee* list, int len)
{
    int retorno = -1;
    int i;
    float resultadoFinal=0;
    float promedio;
    float cantidadSuperanPromedio=0;
    float contadorSalarios=0;

    if(list != NULL && len > 0)
    {
        for(i=0; i<len; i++)
        {
            if(list[i].isEmpty==0)
            {
                resultadoFinal = resultadoFinal+list[i].salary;
                contadorSalarios++;
                promedio = resultadoFinal/contadorSalarios;

                if(list[i].salary > promedio)
                {
                    cantidadSuperanPromedio++;
                }
            }
        }
        retorno = 0;
        printf("\n1-El total de los salarios es: %.2f \n2-El promedio de los salarios es: %.2f \n3-La cantidad que superan el salario promedio son: %.2f\n\n"
               ,resultadoFinal,promedio,cantidadSuperanPromedio);
    }
    return retorno;
}


/** \brief Muestra los campos de la estructura para cada empleado
 *
 * \param Empleado*
 * \param  int cantidad maxima del array
 * \return int [-1] Error [0] Ok.
 *
 */

int employee_mostrar(Employee* list,int len)
{
    int retorno = -1;
    int i;
    if(len > 0 && list != NULL)
    {
        retorno = 0;
        for(i=0; i<len; i++)
        {
            if(!list[i].isEmpty)
                printf("Id: %d\tNombre: %s\tApellido: %s\tSalario: %.2f\tSector: %d\n",list[i].id,
                       list[i].name,
                       list[i].lastName,
                       list[i].salary,
                       list[i].sector);

        }
    }
    return retorno;
}


/** \brief Fuerza el alta de employee
 *
 * \param array employee* puntero al array
 * \param limite int limite definido para el array
 * \param name char* fuerza el nombre, lastname char* fuerza el apellido
 * \param float salary fuerza el sueldo, int sector fuerza el sector
 * \return int [0] OK [-1] ERROR
 *
 */

int employee_altaForzada(Employee* list,int len,char* name,char* lastName,float salary,int sector)
{

    int i;
    int retorno=-1;


    if(len>0 && list!=NULL)
    {
        i=obtenerEspacioLibre(list,len);
        if(i>=0)
        {

            strcpy(list[i].name,name);
            strcpy(list[i].lastName,lastName);
            list[i].salary=salary;
            list[i].sector=sector;
            list[i].id=proximoId();
            list[i].isEmpty=0;
        }
        retorno=0;
    }
    return retorno;
}

