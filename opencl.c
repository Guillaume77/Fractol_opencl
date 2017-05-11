/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:59:19 by gubourge          #+#    #+#             */
/*   Updated: 2017/05/10 18:25:39 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fractol.h"

int		cl_erreur_log(t_cl *cl, cl_int error_code)
{	
	char	 *log;
	size_t	 longueur_Log;

	dprintf(2, "%d\n", error_code);
	// Si erreur de compilation, alors... Affichage du LOG de compilation
	clGetProgramBuildInfo (cl->programme,
							   cl->TOUS_peripheriqueID,
							   CL_PROGRAM_BUILD_LOG,
							   0,
							   NULL,
							   &longueur_Log);
	log = (char *)malloc(longueur_Log);
	clGetProgramBuildInfo (cl->programme,
							   cl->TOUS_peripheriqueID,
							   CL_PROGRAM_BUILD_LOG,
							   longueur_Log,
							   log,
							   NULL);
	ft_putstr("\n[IMPRESSION DU JOURNAL DE COMPILATION]\n\n");
	ft_putstr(log);
	ft_putstr("\n\n");
	ft_putstr("[FIN DU JOURNAL]\n\n"); 
	return (-1);
}

int		cl_create_platform(t_cl *cl)
{
	cl_int	error_code;

	// Création de la plateforme de travail
	if ((error_code = clGetPlatformIDs(1, &cl->plateformeID, NULL)) != CL_SUCCESS)
		return (error_code);
	// Rechercher les PÉRIPHÉRIQUES dans le système, tout type confondu.
	if ((error_code = clGetDeviceIDs(cl->plateformeID,
								CL_DEVICE_TYPE_GPU,
								1,
								&cl->TOUS_peripheriqueID,
						&cl->TOUS_qtePeripheriques)) != CL_SUCCESS)
		return (error_code);
	// Création du contexte de travail
//	cl->proprietes[0] = (cl_context_properties)CL_CONTEXT_PLATFORM;
//	cl->proprietes[1] = (cl_context_properties)cl->plateformeID;
//	cl->proprietes[2] = 0;
	cl->contexte = clCreateContext(NULL,
							   1,
							   &cl->TOUS_peripheriqueID,
							   NULL,
							   NULL,
							   &error_code);
	if (error_code != CL_SUCCESS)
		return (error_code);
	return (0);
}

int		cl_create_program(t_cl *cl, const char *file_buffer, size_t source_size)
{
	cl_int	error_code;

	// Création de la file d'exécution pour le CPU
	cl->file_execution = clCreateCommandQueue(cl->contexte,
										  cl->TOUS_peripheriqueID,
										  CL_QUEUE_PROFILING_ENABLE,
										  &error_code);
	if (error_code != CL_SUCCESS)
		return (error_code);
	// Construire le programme avec la fonction auCarre pour le CPU
	cl->programme = clCreateProgramWithSource(cl->contexte,
										  1,
										  (const char **)&file_buffer,
											  (const size_t *)&source_size,
										  &error_code);
	if (error_code != CL_SUCCESS)
		return (error_code);	
	// Compilation du programme
	error_code = clBuildProgram(cl->programme,
								1,
								&cl->TOUS_peripheriqueID,
								NULL,
								NULL,
								NULL);
	if (error_code != CL_SUCCESS)
		return (error_code);
	return (0);
}
