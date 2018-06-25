/*
    FreeRTOS V8.1.2 - Copyright (C) 2014 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that has become a de facto standard.             *
     *                                                                       *
     *    Help yourself get started quickly and support the FreeRTOS         *
     *    project by purchasing a FreeRTOS tutorial book, reference          *
     *    manual, or both from: http://www.FreeRTOS.org/Documentation        *
     *                                                                       *
     *    Thank you!                                                         *
     *                                                                       *
    ***************************************************************************

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>!AND MODIFIED BY!<< the FreeRTOS exception.

    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
    >>!   obliged to provide the source code for proprietary components     !<<
    >>!   outside of the FreeRTOS kernel.                                   !<<

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available from the following
    link: http://www.freertos.org/a00114.html

    1 tab == 4 spaces!

    ***************************************************************************
     *                                                                       *
     *    Having a problem?  Start by reading the FAQ "My application does   *
     *    not run, what could be wrong?"                                     *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                               *
     *                                                                       *
    ***************************************************************************


    http://www.FreeRTOS.org - Documentation, books, training, latest versions,
    license and Real Time Engineers Ltd. contact details.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.OpenRTOS.com - Real Time Engineers ltd license FreeRTOS to High
    Integrity Systems to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.
*/

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */

#define MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#include "FreeRTOS.h"
#include "os_task.h"
#include "os_queue.h"

#undef MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/*----------------------------------------------------------------------------*/

/* Set the privilege level to user mode if xRunningPrivileged is false.  */
/* TCJ: check must be against zero, see prvRaisePrivilege in portASM.asm */
#define portRESET_PRIVILEGE( xRunningPrivileged ) if( xRunningPrivileged == 0 ) portSWITCH_TO_USER_MODE()


/*----------------------------------------------------------------------------*/
#pragma SWI_ALIAS(prvRaisePrivilege, 1);
extern BaseType_t prvRaisePrivilege( void );

/*----------------------------------------------------------------------------*/

BaseType_t MPU_xTaskGenericCreate( TaskFunction_t pxTaskCode, const char * const pcName, const uint16_t usStackDepth, void * const pvParameters, UBaseType_t uxPriority, TaskHandle_t * const pxCreatedTask, StackType_t * const puxStackBuffer, const MemoryRegion_t * const xRegions )
{
	BaseType_t xReturn;
	BaseType_t xRunningPrivileged = prvRaisePrivilege();
	xReturn = xTaskGenericCreate( pxTaskCode, pcName, usStackDepth, pvParameters, uxPriority, pxCreatedTask, puxStackBuffer, xRegions );
	portRESET_PRIVILEGE( xRunningPrivileged );
	return xReturn;
}


/*----------------------------------------------------------------------------*/


void MPU_vTaskAllocateMPURegions( TaskHandle_t xTask, const xMemoryRegion * const xRegions )
{
	BaseType_t xRunningPrivileged = prvRaisePrivilege();
	vTaskAllocateMPURegions( xTask, xRegions );
	portRESET_PRIVILEGE( xRunningPrivileged );
}


/*----------------------------------------------------------------------------*/


#if ( INCLUDE_vTaskDelete == 1 )
	void MPU_vTaskDelete( TaskHandle_t pxTaskToDelete )
	{
		BaseType_t xRunningPrivileged = prvRaisePrivilege();
		vTaskDelete( pxTaskToDelete );
        portRESET_PRIVILEGE( xRunningPrivileged );
	}
#endif


/*----------------------------------------------------------------------------*/

#if ( INCLUDE_vTaskDelayUntil == 1 )
	void MPU_vTaskDelayUntil( TickType_t *pxPreviousWakeTime, const TickType_t xTimeIncrement )
	{
		BaseType_t xRunningPrivileged = prvRaisePrivilege();
		vTaskDelayUntil( pxPreviousWakeTime, xTimeIncrement );
        portRESET_PRIVILEGE( xRunningPrivileged );
	}
#endif


/*----------------------------------------------------------------------------*/

#if ( INCLUDE_vTaskDelay == 1 )
	void MPU_vTaskDelay( const TickType_t xTicksToDelay  )
	{
		BaseType_t xRunningPrivileged = prvRaisePrivilege();
		vTaskDelay( xTicksToDelay );
        portRESET_PRIVILEGE( xRunningPrivileged );
	}
#endif


/*----------------------------------------------------------------------------*/

#if ( INCLUDE_uxTaskPriorityGet == 1 )
	UBaseType_t MPU_uxTaskPriorityGet( TaskHandle_t pxTask )
	{
		UBaseType_t uxReturn;
		BaseType_t xRunningPrivileged = prvRaisePrivilege();
		uxReturn = uxTaskPriorityGet( pxTask );
        portRESET_PRIVILEGE( xRunningPrivileged );
		return uxReturn;
	}
#endif


/*----------------------------------------------------------------------------*/

#if ( INCLUDE_vTaskPrioritySet == 1 )
	void MPU_vTaskPrioritySet( TaskHandle_t xTask, UBaseType_t uxNewPriority )
	{
		BaseType_t xRunningPrivileged = prvRaisePrivilege();
		vTaskPrioritySet( xTask, uxNewPriority );
        portRESET_PRIVILEGE( xRunningPrivileged );
	}
#endif


/*----------------------------------------------------------------------------*/

#if ( INCLUDE_vTaskSuspend == 1 )
	void MPU_vTaskSuspend( TaskHandle_t pxTaskToSuspend )
	{
		BaseType_t xRunningPrivileged = prvRaisePrivilege();
		vTaskSuspend( pxTaskToSuspend );
        portRESET_PRIVILEGE( xRunningPrivileged );
	}
#endif


/*----------------------------------------------------------------------------*/

#if ( INCLUDE_vTaskSuspend == 1 )
	void MPU_vTaskResume( TaskHandle_t pxTaskToResume )
	{
		BaseType_t xRunningPrivileged = prvRaisePrivilege();
		vTaskResume( pxTaskToResume );
        portRESET_PRIVILEGE( xRunningPrivileged );
	}
#endif


/*----------------------------------------------------------------------------*/

void MPU_vTaskSuspendAll( void )
{
	BaseType_t xRunningPrivileged = prvRaisePrivilege();
	vTaskSuspendAll();
    portRESET_PRIVILEGE( xRunningPrivileged );
}


/*----------------------------------------------------------------------------*/

BaseType_t MPU_xTaskResumeAll( void )
{
	BaseType_t xReturn;
	BaseType_t xRunningPrivileged = prvRaisePrivilege();
	xReturn = xTaskResumeAll();
    portRESET_PRIVILEGE( xRunningPrivileged );
    return xReturn;
}


/*----------------------------------------------------------------------------*/

portTickType MPU_xTaskGetTickCount( void )
{
	portTickType xReturn;
	BaseType_t xRunningPrivileged = prvRaisePrivilege();
	xReturn = xTaskGetTickCount();
    portRESET_PRIVILEGE( xRunningPrivileged );
	return xReturn;
}


/*----------------------------------------------------------------------------*/

UBaseType_t MPU_uxTaskGetNumberOfTasks( void )
{
	UBaseType_t uxReturn;
	BaseType_t xRunningPrivileged = prvRaisePrivilege();
	uxReturn = uxTaskGetNumberOfTasks();
    portRESET_PRIVILEGE( xRunningPrivileged );
	return uxReturn;
}


/*----------------------------------------------------------------------------*/

#if ( ( configUSE_TRACE_FACILITY == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS == 1 ) )
	void MPU_vTaskList( char *pcWriteBuffer )
	{
		BaseType_t xRunningPrivileged = prvRaisePrivilege();
		vTaskList( pcWriteBuffer );
		portRESET_PRIVILEGE( xRunningPrivileged );
	}
#endif


/*----------------------------------------------------------------------------*/

#if ( configGENERATE_RUN_TIME_STATS == 1 )
	void MPU_vTaskGetRunTimeStats( char *pcWriteBuffer )
	{
		BaseType_t xRunningPrivileged = prvRaisePrivilege();
		vTaskGetRunTimeStats( pcWriteBuffer );
        portRESET_PRIVILEGE( xRunningPrivileged );
	}
#endif

/*----------------------------------------------------------------------------*/

#if ( configUSE_APPLICATION_TASK_TAG == 1 )
	void MPU_vTaskSetApplicationTaskTag( TaskHandle_t xTask, TaskHookFunction_t pxTagValue )
	{
		BaseType_t xRunningPrivileged = prvRaisePrivilege();
		vTaskSetApplicationTaskTag( xTask, pxTagValue );
        portRESET_PRIVILEGE( xRunningPrivileged );
	}
#endif


/*----------------------------------------------------------------------------*/

#if ( configUSE_APPLICATION_TASK_TAG == 1 )
	pdTASK_HOOK_CODE MPU_xTaskGetApplicationTaskTag( TaskHandle_t xTask )
	{
		pdTASK_HOOK_CODE xReturn;
		BaseType_t xRunningPrivileged = prvRaisePrivilege();
		xReturn = xTaskGetApplicationTaskTag( xTask );
        portRESET_PRIVILEGE( xRunningPrivileged );
		return xReturn;
	}
#endif


/*----------------------------------------------------------------------------*/

#if ( configUSE_APPLICATION_TASK_TAG == 1 )
	BaseType_t MPU_xTaskCallApplicationTaskHook( TaskHandle_t xTask, void *pvParameter )
	{
		BaseType_t xReturn;
		BaseType_t xRunningPrivileged = prvRaisePrivilege();
		xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
        portRESET_PRIVILEGE( xRunningPrivileged );
		return xReturn;
	}
#endif


/*----------------------------------------------------------------------------*/

#if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 )
	UBaseType_t MPU_uxTaskGetStackHighWaterMark( TaskHandle_t xTask )
	{
		UBaseType_t uxReturn;
		BaseType_t xRunningPrivileged = prvRaisePrivilege();
		uxReturn = uxTaskGetStackHighWaterMark( xTask );
        portRESET_PRIVILEGE( xRunningPrivileged );
		return uxReturn;
	}
#endif


/*----------------------------------------------------------------------------*/

#if ( INCLUDE_xTaskGetCurrentTaskHandle == 1 )
	TaskHandle_t MPU_xTaskGetCurrentTaskHandle( void )
	{
		TaskHandle_t xReturn;
		BaseType_t xRunningPrivileged = prvRaisePrivilege();
		xReturn = xTaskGetCurrentTaskHandle();
        portRESET_PRIVILEGE( xRunningPrivileged );
		return xReturn;
	}
#endif


/*----------------------------------------------------------------------------*/

#if ( INCLUDE_xTaskGetSchedulerState == 1 )
	BaseType_t MPU_xTaskGetSchedulerState( void )
	{
		BaseType_t xReturn;
		BaseType_t xRunningPrivileged = prvRaisePrivilege();
		xReturn = xTaskGetSchedulerState();
        portRESET_PRIVILEGE( xRunningPrivileged );
		return xReturn;
	}
#endif


/*----------------------------------------------------------------------------*/

QueueHandle_t MPU_xQueueGenericCreate( const UBaseType_t uxQueueLength, const UBaseType_t uxItemSize, const uint8_t ucQueueType )
{
	QueueHandle_t xReturn;
	BaseType_t xRunningPrivileged = prvRaisePrivilege();
	xReturn = xQueueGenericCreate( uxQueueLength, uxItemSize, ucQueueType );
	portRESET_PRIVILEGE( xRunningPrivileged );
	return xReturn;
}


/*----------------------------------------------------------------------------*/

BaseType_t MPU_xQueueGenericSend( QueueHandle_t xQueue, const void * const pvItemToQueue, TickType_t xTicksToWait, const BaseType_t xCopyPosition )
{
	BaseType_t xReturn;
	BaseType_t xRunningPrivileged = prvRaisePrivilege();
	xReturn = xQueueGenericSend( xQueue, pvItemToQueue, xTicksToWait, xCopyPosition );
	portRESET_PRIVILEGE( xRunningPrivileged );
	return xReturn;
}


/*----------------------------------------------------------------------------*/

UBaseType_t MPU_uxQueueMessagesWaiting( const QueueHandle_t xQueue )
{
	BaseType_t xRunningPrivileged = prvRaisePrivilege();
	UBaseType_t uxReturn;
	uxReturn = uxQueueMessagesWaiting( xQueue );
	portRESET_PRIVILEGE( xRunningPrivileged );
	return uxReturn;
}


/*----------------------------------------------------------------------------*/

BaseType_t MPU_xQueueGenericReceive( QueueHandle_t xQueue, void * const pvBuffer, TickType_t xTicksToWait, const BaseType_t xJustPeeking )
{
	BaseType_t xRunningPrivileged = prvRaisePrivilege();
	BaseType_t xReturn;
	xReturn = xQueueGenericReceive( xQueue, pvBuffer, xTicksToWait, xJustPeeking );
	portRESET_PRIVILEGE( xRunningPrivileged );
	return xReturn;
}


/*----------------------------------------------------------------------------*/

#if ( configUSE_MUTEXES == 1 )
	QueueHandle_t MPU_xQueueCreateMutex( const uint8_t ucQueueType )
	{
		xQueueHandle xReturn;
		BaseType_t xRunningPrivileged = prvRaisePrivilege();
		xReturn = xQueueCreateMutex( ucQueueType );
		portRESET_PRIVILEGE( xRunningPrivileged );
		return xReturn;
	}
#endif


/*----------------------------------------------------------------------------*/

#if configUSE_COUNTING_SEMAPHORES == 1
	QueueHandle_t MPU_xQueueCreateCountingSemaphore( const UBaseType_t uxMaxCount, const UBaseType_t uxInitialCount )
	{
		xQueueHandle xReturn;
		BaseType_t xRunningPrivileged = prvRaisePrivilege();

		xReturn = xQueueCreateCountingSemaphore( uxMaxCount, uxInitialCount );
		portRESET_PRIVILEGE( xRunningPrivileged );
		return xReturn;
	}
#endif


/*----------------------------------------------------------------------------*/

#if ( configUSE_RECURSIVE_MUTEXES == 1 )
	BaseType_t MPU_xQueueTakeMutexRecursive( xQueueHandle xMutex, portTickType xBlockTime )
	{
		BaseType_t xReturn;
		BaseType_t xRunningPrivileged = prvRaisePrivilege();

		xReturn = xQueueTakeMutexRecursive( xMutex, xBlockTime );
		portRESET_PRIVILEGE( xRunningPrivileged );
		return xReturn;
	}
#endif


/*----------------------------------------------------------------------------*/

#if ( configUSE_RECURSIVE_MUTEXES == 1 )
	BaseType_t MPU_xQueueGiveMutexRecursive( xQueueHandle xMutex )
	{
		BaseType_t xReturn;
		BaseType_t xRunningPrivileged = prvRaisePrivilege();

		xReturn = xQueueGiveMutexRecursive( xMutex );
		portRESET_PRIVILEGE( xRunningPrivileged );
		return xReturn;
	}
#endif


/*----------------------------------------------------------------------------*/

#if configUSE_ALTERNATIVE_API == 1
	BaseType_t MPU_xQueueAltGenericSend( xQueueHandle pxQueue, const void * const pvItemToQueue, portTickType xTicksToWait, BaseType_t xCopyPosition )
	{
		BaseType_t xReturn;
		BaseType_t xRunningPrivileged = prvRaisePrivilege();

		xReturn = 	BaseType_t xQueueAltGenericSend( pxQueue, pvItemToQueue, xTicksToWait, xCopyPosition );
		portRESET_PRIVILEGE( xRunningPrivileged );
		return xReturn;
	}
#endif


/*----------------------------------------------------------------------------*/

#if ( configUSE_ALTERNATIVE_API == 1 )
	BaseType_t MPU_xQueueAltGenericReceive( xQueueHandle pxQueue, void * const pvBuffer, portTickType xTicksToWait, BaseType_t xJustPeeking )
	{
		BaseType_t xReturn;
		BaseType_t xRunningPrivileged = prvRaisePrivilege();

		xReturn = xQueueAltGenericReceive( pxQueue, pvBuffer, xTicksToWait, xJustPeeking );
		portRESET_PRIVILEGE( xRunningPrivileged );
		return xReturn;
	}
#endif


/*----------------------------------------------------------------------------*/

#if ( configQUEUE_REGISTRY_SIZE > 0 )
	void MPU_vQueueAddToRegistry( xQueueHandle xQueue, signed char *pcName )
	{
		BaseType_t xRunningPrivileged = prvRaisePrivilege();

		vQueueAddToRegistry( xQueue, pcName );

		portRESET_PRIVILEGE( xRunningPrivileged );
	}
#endif

/*----------------------------------------------------------------------------*/

void MPU_vQueueDelete( xQueueHandle xQueue )
{
	BaseType_t xRunningPrivileged = prvRaisePrivilege();

	vQueueDelete( xQueue );

	portRESET_PRIVILEGE( xRunningPrivileged );
}

/*----------------------------------------------------------------------------*/

BaseType_t MPU_xQueueGenericReset( QueueHandle_t xQueue, BaseType_t xNewQueue )
{
	BaseType_t xReturn;
	BaseType_t xRunningPrivileged = prvRaisePrivilege();

	xReturn = xQueueGenericReset( xQueue, xNewQueue );
	portRESET_PRIVILEGE( xRunningPrivileged );
	return xReturn;
}

/*----------------------------------------------------------------------------*/

#if ( configUSE_QUEUE_SETS == 1 )
	QueueSetHandle_t MPU_xQueueCreateSet( const UBaseType_t uxEventQueueLength )
	{
		QueueSetHandle_t xReturn;
		BaseType_t xRunningPrivileged = prvRaisePrivilege();

		xReturn = xQueueCreateSet( uxEventQueueLength );
		portRESET_PRIVILEGE( xRunningPrivileged );
		return xReturn;
	}
#endif

/*----------------------------------------------------------------------------*/

#if ( configUSE_QUEUE_SETS == 1 )
	QueueSetMemberHandle_t MPU_xQueueSelectFromSet( QueueSetHandle_t xQueueSet, TickType_t const xTicksToWait )
	{
		QueueSetMemberHandle_t xReturn;
		BaseType_t xRunningPrivileged = prvRaisePrivilege();

		xReturn = xQueueSelectFromSet( xQueueSet, xTicksToWait );
		portRESET_PRIVILEGE( xRunningPrivileged );
		return xReturn;
	}
#endif

/*----------------------------------------------------------------------------*/

#if ( configUSE_QUEUE_SETS == 1 )
	BaseType_t MPU_xQueueAddToSet( QueueSetMemberHandle_t xQueueOrSemaphore, QueueSetHandle_t xQueueSet )
	{
		BaseType_t xReturn;
		BaseType_t xRunningPrivileged = prvRaisePrivilege();

		xReturn = xQueueAddToSet( xQueueOrSemaphore, xQueueSet );
		portRESET_PRIVILEGE( xRunningPrivileged );
		return xReturn;
	}
#endif

/*----------------------------------------------------------------------------*/

#if ( configUSE_QUEUE_SETS == 1 )
	BaseType_t MPU_xQueueRemoveFromSet( QueueSetMemberHandle_t xQueueOrSemaphore, QueueSetHandle_t xQueueSet )
	{
		BaseType_t xReturn;
		BaseType_t xRunningPrivileged = prvRaisePrivilege();

		xReturn = xQueueRemoveFromSet( xQueueOrSemaphore, xQueueSet );
		portRESET_PRIVILEGE( xRunningPrivileged );
		return xReturn;
	}
#endif

/*----------------------------------------------------------------------------*/

BaseType_t MPU_xQueuePeekFromISR( QueueHandle_t xQueue,  void * const pvBuffer )
{
	BaseType_t xReturn;
	BaseType_t xRunningPrivileged = prvRaisePrivilege();

	xReturn = xQueuePeekFromISR( xQueue, pvBuffer );
	portRESET_PRIVILEGE( xRunningPrivileged );
	return xReturn;
}

/*----------------------------------------------------------------------------*/

#if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )
	void* MPU_xQueueGetMutexHolder( QueueHandle_t xSemaphore )
	{
		BaseType_t xRunningPrivileged = prvRaisePrivilege();

		xQueueGetMutexHolder( xSemaphore );
		portRESET_PRIVILEGE( xRunningPrivileged );
	}
#endif

/*----------------------------------------------------------------------------*/

#if ( configQUEUE_REGISTRY_SIZE > 0 )
	void MPU_vQueueUnregisterQueue( QueueHandle_t xQueue )
	{
		BaseType_t xRunningPrivileged = prvRaisePrivilege();

		xReturn = vQueueUnregisterQueue( xQueue );
		portRESET_PRIVILEGE( xRunningPrivileged );
	}
#endif

/*----------------------------------------------------------------------------*/

void *MPU_pvPortMalloc( size_t xSize )
{
	void *pvReturn;
	BaseType_t xRunningPrivileged = prvRaisePrivilege();

	pvReturn = pvPortMalloc( xSize );

	portRESET_PRIVILEGE( xRunningPrivileged );

	return pvReturn;
}


/*----------------------------------------------------------------------------*/

void MPU_vPortFree( void *pv )
{
	BaseType_t xRunningPrivileged = prvRaisePrivilege();

	vPortFree( pv );

	portRESET_PRIVILEGE( xRunningPrivileged );
}


/*----------------------------------------------------------------------------*/

void MPU_vPortInitialiseBlocks( void )
{
	BaseType_t xRunningPrivileged = prvRaisePrivilege();

	vPortInitialiseBlocks();

	portRESET_PRIVILEGE( xRunningPrivileged );
}


/*----------------------------------------------------------------------------*/

size_t MPU_xPortGetFreeHeapSize( void )
{
	size_t xReturn;
	BaseType_t xRunningPrivileged = prvRaisePrivilege();

	xReturn = xPortGetFreeHeapSize();

	portRESET_PRIVILEGE( xRunningPrivileged );

	return xReturn;
}

/*----------------------------------------------------------------------------*/
