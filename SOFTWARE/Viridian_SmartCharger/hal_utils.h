#ifndef __HAL_UTILS__
#define __HAL_UTILS__

#include <ESP8266WiFi.h>
#include <Arduino.h>

#include "viridian_utils.h"

//< Define du HARDWARE
#define HW_NAME                   "VIRIDIAN"

//< Define des In/Out
#define GPIO_DMD_RESET            0                     // GPIO du bouton Reset
#define GPIO_RD                   1                     // GPIO de la LED Rouge Viridian
#define PWM_VIRIDIAN              2                     // PWM de pilotage Viridian
#define GPIO_GN                   3                     // GPIO de la LED Verte Viridian

//< Define de bornes de courants de charge VE
#define MINIMAL_CHARGE_CURRENT    6                     // Courant de charge minimal
#define MAXIMAL_CHARGE_CURRENT    32                    // Courant de charge maximal

/**
 * \fn void hal_init(void)
 * \brief Fonction permettant d'initialiser la HAL
 */
void hal_init(void);

/**
 * \fn void hal_disable_interrupt(void)
 * \brief Fonction permettant de désactiver les interruptions
 */
void hal_disable_interrupt(void);

/**
 * \fn void hal_enable_interrupt(void)
 * \brief Fonction permettant d'activer les interruptions
 */
void hal_enable_interrupt(void);

/**
 * \fn void hal_evse_init(void)
 * \brief Fonction permettant l'initialisation du service Viridian
 */
void hal_evse_init(void);

/**
 * \fn void hal_evse_update_input(void)
 * \brief Fonction de scrutation des entrées des signaux GPIO_RD et GPIO_GN.
 *        /!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\
 *        Ces entrées sont scrutées en mode polling et non en mode interruptif !
 *        En effet, le mode interruptif n'est absolument pas compatible avec les mécanismes
 *        implémentés, et fait litérallement planter l'ESP8266 !!!
 *        /!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\/!\
 */
void hal_evse_update_input(void);

/**
 * \fn void hal_evse_update_output(uint8_t current)
 * \brief Fonction permettant le réglage de la consigne de courant
 *        du service Viridian
 * \param in, le courant de consigne I E [0,32]
 */
void hal_evse_update_output(uint8_t current);

/**
 * \fn CHARGE_STATE_EVSE_e hal_evse_get_state(void)
 * \brief fonction de scrutation de l'état de charge du Viridian
 */
CHARGE_STATE_EVSE_e hal_evse_get_state(void);

/**
 * \fn bool hal_get_reboot(void)
 * \brief Fonction permettant de lire l'état de la GPIO de Reboot
 * \return
 *        L'état de la GPIO Reboot
 */
bool hal_get_reboot(void);

/**
 * \fn bool hal_get_rd(void)
 * \brief Fonction permettant de lire l'état de la GPIO_RD
 * \return
 *        L'état de la GPIO_RD
 */
bool hal_get_rd(void);

/**
 * \fn bool hal_get_gn(void)
 * \brief Fonction permettant de lire l'état de la GPIO_GN
 * \return
 *        L'état de la GPIO_GN
 */
bool hal_get_gn(void);

#endif
