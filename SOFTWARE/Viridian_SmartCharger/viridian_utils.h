#ifndef __VIRIDIAN_UTILS__
#define __VIRIDIAN_UTILS__

#include <stdint.h>

#define PWM_EDGE_THRESHOLD 5

//< Enumération de l'état de charge de l'EVSE
typedef enum 
{
  evse_Not_Connected,
  evse_Connected,
  evse_Charging,
  evse_Fault,
}CHARGE_STATE_EVSE_e;

//< Structure d'analyse de signal issue du Viridian
typedef struct
{
  uint32_t edge_count;
  uint32_t high_count;
  uint32_t low_count;
  uint8_t last_state;
} SIGNAL_ANALYZER_t;

//< Enumération de type de signal issue du Viridian
typedef enum
{
  SIG_LOW,
  SIG_HIGH,
  SIG_PWM
} SIGNAL_TYPE_e;

/**
 * \fn void viridian_signal_update(SIGNAL_ANALYZER_t *s, bool level)
 * \brief Cette fonction permet de lire périodiquement les signaux du Viridian LEDs Rouge et Verte (pas de Bleue !!!)
 *          - Bleu clignotant  : Attente d'un VE              (Pas Rouge et pas Vert)
 *          - Bleu fixe        : VE connecté mais non prêt    (Pas Rouge et pas Vert)
 *          - Vert fixe        : VE en charge
 *          - Rouge clignotant : Ventilation VE en cours, la charge est stoppée
 *          - Rouge fixe       : Défaut détécté
 *        En vue d'effectuer una analyse final par la fonction viridian_get_state()
 */
void viridian_signal_update(SIGNAL_ANALYZER_t *s, bool level);

/**
 * \fn SIGNAL_TYPE_e viridian_signal_get_type(SIGNAL_ANALYZER_t *s)
 * \brief Cette fonction permet d'effectuer l'analyse de l'état de charge du Viridian
 * \return
 *		  Un élément de l'énumération SIGNAL_TYPE_e
 */
SIGNAL_TYPE_e viridian_signal_get_type(SIGNAL_ANALYZER_t *s);

/**
 * \fn CHARGE_STATE_EVSE_e viridian_get_state(SIGNAL_ANALYZER_t *rd, SIGNAL_ANALYZER_t *gn)
 * \brief Cette fonction permet l'analyse de l'état de charge du Viridian par
 *        la lecture des signaux LEDs Rouge et Verte (pas de Bleue !!!)
 *          - Bleu clignotant  : Attente d'un VE              (Pas Rouge et pas Vert)
 *          - Bleu fixe        : VE connecté mais non prêt    (Pas Rouge et pas Vert)
 *          - Vert fixe        : VE en charge
 *          - Rouge clignotant : Ventilation VE en cours, la charge est stoppée
 *          - Rouge fixe       : Défaut détécté
 * \return 
 *        Un élément de l'énumération CHARGE_STATE_EVSE_e
 */
CHARGE_STATE_EVSE_e viridian_get_state(SIGNAL_ANALYZER_t *rd, SIGNAL_ANALYZER_t *gn);

#endif
