/*
 * main.c
 *
 *  Created on: 28 feb. 2019
 *      Author: utnso
 */

#include "tp0.h"
#include "utils.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/
	int conexion;
	char* ip;
	char* puerto;

	t_log* logger;
	t_config* config;

	logger = iniciar_logger();

	//Loggear "soy un log"
	log_info(logger, "Soy un log");

	config = leer_config();

	ip = config_get_string_value(config, "IP");
	puerto = config_get_string_value(config,"PUERTO");

	log_info(logger,"Lei la IP %s y el PUERTO %s\n", ip, puerto);


	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	//antes de continuar, tenemos que asegurarnos que el servidor esté corriendo porque lo necesitaremos para lo que sigue.

	//crear conexion
	conexion = crear_conexion(ip, puerto);

	//enviar mensaje
	enviar_mensaje("Hola", conexion);


	//recibir mensaje
	char *mensaje = recibir_mensaje(conexion);


	//loguear mensaje recibido
	log_info(logger, "El mensaje recibido es: %s\n", mensaje);

	terminar_programa(conexion, logger, config);
}

t_log* iniciar_logger(void)
{
	t_log *logger;
	if((logger = log_create("tp0.log", "TP0", 1, LOG_LEVEL_INFO)) == NULL){
		printf("No pude generar el log\n");
		exit(1);
	}
	return logger;
}

t_config* leer_config(void)
{
t_config *config;
if((config = config_create("./tp0.config")) == NULL){
	printf("No pude leer la config\n");
	exit(2);
}
return config;
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	//Y por ultimo, para cerrar, hay que liberar lo que utilizamos (conexion, log y config) con las funciones de las commons y del TP mencionadas en el enunciado
	if(logger != NULL){
		log_destroy(logger);
	}

	if(config != NULL){
		config_destroy(config);
	}

	if(conexion != NULL){
		liberar_conexion(conexion);
	}
}
