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
 * \fn void hal_toggle_led(void)
 * \brief Non utilisé sur Viridian
 */
void hal_toggle_led(void);

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
 * \fn CHARGE_STATE_EVSE_e hal_evse_get_state(void)
 * \brief fonction de scrutation de l'état de charge du Viridian
 */
CHARGE_STATE_EVSE_e hal_evse_get_state(void);

/**
 * \fn void hal_lock_current(void)
 * \brief Fonction permettant le pilotage de la sortie PWM IC à l'état haut
 *        pour permettre le blocage du Viridian
 */
void hal_lock_current(void);

/**
 * \fn void hal_set_current(int current)
 * \brief Fonction permettant le pilotage de la sortie PWM IC du Viridian
 * \param in, la valeur de courant souhaitée
 */
void hal_set_current(uint8_t current);

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
