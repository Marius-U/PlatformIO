#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>  // add the FreeRTOS functions for Semaphores (or Flags).
#include <AccessEnter.h>
#include <AccessExit.h>
#include <Parking.h>
#include <SafetyMonitor.h>
#include <Debugg.h>

// Declare a mutex Semaphore Handle which we will use to manage the Serial Port.
// It will be used to ensure only only one Task is accessing this resource at any time.
SemaphoreHandle_t xSerialSemaphore;


/* TaskAccess: 
 *    Access_Enter is processed by this task.
 */
void TaskAccess(void *pvParameters); 

/* TaskAccess: 
 *    Access_Exit is processed by this task.
 */
void TaskExit( void *pvParameters __attribute__((unused)) );

/* TaskParking: 
 *    Process changes caused by cars entering or exiting the parking.
 */
void TaskParking(void *pvParameters); 

/* TaskSafetyMonitor: 
 *    Monitor the safety conditions and take acctions to ensure 
 *    safety of users inside parking lot.
 */
void TaskSafetyMonitor(void *pvParameters); 


// the setup function runs once when you press reset or power the board
void setup() {


  // Semaphores are useful to stop a Task proceeding, where it should be paused to wait,
  // because it is sharing a resource, such as the Serial port.
  // Semaphores should only be used whilst the scheduler is running, but we can set it up here.
  if ( xSerialSemaphore == NULL )  // Check to confirm that the Serial Semaphore has not already been created.
  {
    xSerialSemaphore = xSemaphoreCreateMutex();  // Create a mutex semaphore we will use to manage the Serial Port
    if ( ( xSerialSemaphore ) != NULL )
      xSemaphoreGive( ( xSerialSemaphore ) );  // Make the Serial Port available for use, by "Giving" the Semaphore.
  }

  // Now set up two Tasks to run independently.
  xTaskCreate(
    TaskAccess
    ,  "Access"  // A name just for humans
    ,  128       // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  1         // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );

  xTaskCreate(
    TaskParking
    ,  "Parking"
    ,  128  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL );

    // xTaskCreate(
    // TaskExit
    // ,  "Exit"
    // ,  128  // Stack size
    // ,  NULL
    // ,  1  // Priority
    // ,  NULL );

#if(DEBUGG == STD_ON)
{
  debuggInit();
  debuggPrint("Setup done! Tasks should run!");
}
#endif
  // Now the Task scheduler, which takes over control of scheduling individual Tasks, is automatically started.
}

void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/


void TaskAccess( void *pvParameters __attribute__((unused)) )  // This is a Task.
{
  /*
    * Access:
    *  Process changes caused by cars entering or exiting the parking.
    */

  //call the init functions for needed driveres here
#if(DEBUGG == STD_ON)
  debuggPrint("Hello from TaskAccess!");
#endif

  accessEnterInit();
   UBaseType_t uxHighWaterMark;
  /* Inspect our own high water mark on entering the task. */
  uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
  Serial.print("HighWaterMark ");
  Serial.println(uxHighWaterMark);
  for (;;) // A Task shall never return or exit. We do not hace concurency to resources so no need of xSemaphore in this task.
  {
 #if(0)//(DEBUGG == STD_ON)
  debuggPrint("1");
#endif   
    //call main function of Access_Enter SWC
    uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
    Serial.print("HighWaterMark ");
    Serial.println(uxHighWaterMark);
    accessEnter_main();

    vTaskDelay(1);  // one tick delay (15ms) in between calls for stability
  }
}

void TaskExit( void *pvParameters __attribute__((unused)) )  // This is a Task.
{
  /*
    * Access:
    *  Process changes caused by cars entering or exiting the parking.
    */

  //call the init functions for needed driveres here
#if(DEBUGG == STD_ON)
  debuggPrint("Hello from TaskExit!");
#endif

  acessExitInit();

  for (;;) // A Task shall never return or exit. We do not hace concurency to resources so no need of xSemaphore in this task.
  {
 #if(0)//(DEBUGG == STD_ON)
  debuggPrint("2");
#endif   
    //call main function of Access_Exit SWC
    accessExit_main();

    vTaskDelay(1);  // one tick delay (15ms) in between calls for stability
  }
}

void TaskParking( void *pvParameters __attribute__((unused)) )  // This is a Task.
{
  /*
   * Parking: 
   *    Process changes caused by cars entering or exiting the parking.
   */
  #if(DEBUGG == STD_ON)
  debuggPrint("Hello from TaskParking!");
#endif

  UBaseType_t uxHighWaterMark;
  /* Inspect our own high water mark on entering the task. */
  uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
  Serial.print("Parking HighWaterMark ");
  Serial.println(uxHighWaterMark);
  //call the init functions for needed driveres here

  for (;;) // A Task shall never return or exit. We do not hace concurency to resources so no need of xSemaphore in this task.
  {
 #if(0)
  debuggPrint("3");
#endif  
    //call main function of Parking SWC
    uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
    Serial.print("Parking HighWaterMark ");
    Serial.println(uxHighWaterMark);
    vTaskDelay(1);  // one tick delay (15ms) in between calls for stability
  }
}

void TaskSafetyMonitor( void *pvParameters __attribute__((unused)) )  // This is a Task.
{
  /*
   * Safety Monitor: 
   *    Monitor the safety conditions and take acctions to ensure 
   *    safety of users inside parking lot.
   */

#if(DEBUGG == STD_ON)
  debuggPrint("Hello from TaskSafetyMonitor!");
#endif

  //call the init functions for needed driveres here

  for (;;) // A Task shall never return or exit. We do not hace concurency to resources so no need of xSemaphore in this task.
  {
   
    //call main function of SafetyMonitor SWC

    vTaskDelay(1);  // one tick delay (15ms) in between calls for stability
  }
}