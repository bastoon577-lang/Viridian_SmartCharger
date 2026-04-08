#include "hal_utils.h"

//< Déclaration des variables globales
static SIGNAL_ANALYZER_t rd_analyze, gn_analyze;

/**
 * \fn void hal_init(void)
 */
void hal_init(void) {
  pinMode(GPIO_DMD_RESET,INPUT_PULLUP);                       // Déclaration de l'entrée GPIO de Reboot

  /*
   * Le Viridian étant dépourvue de BUS de communication: 
   *  L'analyse de son état de charge passe par l'analyse des signaux :
   *    - LED Rouge,
   *    - LED Verte.
   *  Le pilotage du courant de charge passe par le piloatge de la tension sur 
   *  l'entrée IC du Viridian.
   */
  pinMode(GPIO_RD,INPUT_PULLUP);                              // Déclaration de l'entrée GPIO_RD
  pinMode(GPIO_GN,INPUT_PULLUP);                              // Déclaration de l'entrée GPIO_GN

  pinMode(PWM_VIRIDIAN,OUTPUT);                               // Déclaration de la sortie PWM sur Ic
  analogWriteFreq(40000);                                     // Initialisation de la fréquence PWM à 40KHz
}

/**
 * \fn void hal_disable_interrupt(void)
 */
void hal_disable_interrupt(void) {
  noInterrupts();
}

/**
 * \fn void hal_enable_interrupt(void)
 */
void hal_enable_interrupt(void) {
  interrupts();
}

/**
 * \fn void hal_evse_init(void)
 */
void hal_evse_init(void) {
  hal_evse_update_output(0);
}

/**
 * \fn void hal_evse_update_input(void)
 */
void hal_evse_update_input(void) {
  viridian_signal_update(&rd_analyze,hal_get_rd());
  viridian_signal_update(&gn_analyze,hal_get_gn());
}

/**
 * \fn void hal_evse_update_input(uint8_t current)
 */
void hal_evse_update_output(uint8_t current) {
  if(current == 0) {											                    // Un blocage est demandé
    /*************************************************************************************************************
     *        Pilotage de l'entrée IC du Viridian en appliquant une tension :        
     *          Inférieur à 0,8018 V, le Viridian réduit la capacité de puissance à 7A pendant 5 secondes,
     *          puis se positionne en 'Status A' (Attente d'un VE) jusqu'à une reprise de IC > 0,8018 V.
     *        Le tirage à l'état haut du signal PWM permet l'obtension d'un U_IC = ~ 0,655 V
     ************************************************************************************************************/
    analogWrite(PWM_VIRIDIAN,255);                            // Tirage du signal PWM sur Ic (Viridian) à l'état haut
  } else {														                        // Autrement, attribution du courant de consigne
  
    // Le pilotage PWM sur IC n'étant pas linéaire, il est nécessaire d'établir une table de valeurs correspondantes
    // Intensités correspondantes         6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32
    const uint8_t adjust_pwm_value[] = {220,210,200,181,171,160,152,141,134,127,120,113,105,100, 95, 90, 85, 82, 78, 74, 70, 68, 65, 60, 57, 54, 50};
    uint8_t table_index = current-6;
  
    if(current < MINIMAL_CHARGE_CURRENT || current > MAXIMAL_CHARGE_CURRENT)
      return;
    
    /*************************************************************************************************************
     *        Pilotage de l'entrée IC du Viridian en appliquant une tension suivant:        
     *          Max_VE_Current | IC_Voltage
     *              32 A       |  2,1132 V
     *              31 A       |  2,0554 V
     *              ....       |  ........
     *               6 A       |  0,8018 V
     ************************************************************************************************************/
    analogWrite(PWM_VIRIDIAN,adjust_pwm_value[table_index]);  // Pilotage de la sortie PWM
  }
}

/**
 * \fn CHARGE_STATE_EVSE_e hal_evse_get_state
 */
CHARGE_STATE_EVSE_e hal_evse_get_state(void) {
  return viridian_get_state(&rd_analyze,&gn_analyze);
}

/**
 * \fn bool hal_get_reboot(void)
 */
bool hal_get_reboot(void) {
  return digitalRead(GPIO_DMD_RESET);
}

/**
 * \fn bool hal_get_rd(void)
 */
bool hal_get_rd(void) {
  return !digitalRead(GPIO_RD);
}

/**
 * \fn bool hal_get_gn(void)
 */
bool hal_get_gn(void) {
  return !digitalRead(GPIO_GN);
}
