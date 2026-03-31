#include "viridian_utils.h"

/*
 * Le Viridian étant dépourvue de BUS de communication, l'ESP01 utilise:
 *  - Les LED Rouge et Verte pour l'analyse de l'état de charge,
 *  - L'entrée Ic pour le pilotage du courant.
 */

/**
 * \fn void viridian_signal_update(SIGNAL_ANALYZER_t *s, bool level)
 * \brief Fonction permettant l'analyse de signaux numériques (notamment GPIO_RD & GPIO_GN)
 * \param out s, le pointeur du signal concerné
 * \param in level, le niveau lue sur la GPIO
 */
void viridian_signal_update(SIGNAL_ANALYZER_t *s, bool level) {
  if(level)
    s->high_count++;
  else
    s->low_count++;

  if(level != s->last_state) {
    s->last_state = level;
    s->edge_count++;
  }
}

/**
 * \fn SIGNAL_ANALYZER_t viridian_signal_get_type(SIGNAL_ANALYZER_t *s)
 * \brief Fonction de classification de signal
 * \param in le pointeur du signal à analyser
 * \return 
 *        Le type de signal, un élément de l'énumération SIGNAL_TYPE_e
 */
SIGNAL_TYPE_e viridian_signal_get_type(SIGNAL_ANALYZER_t *s) {
  SIGNAL_TYPE_e ret = SIG_LOW;
  
  if(s->edge_count < PWM_EDGE_THRESHOLD) {
    if(s->high_count > s->low_count)
      ret = SIG_HIGH;
    else
      ret = SIG_LOW;
  } else {
    ret = SIG_PWM;
  }

  s->high_count = 0;
  s->edge_count = 0;
  s->low_count = 0;

  return ret;
}

/**
 * \fn CHARGE_STATE_EVSE_e viridian_get_state(SIGNAL_ANALYZER_t *rd, SIGNAL_ANALYZER_t *gn)
 */
CHARGE_STATE_EVSE_e viridian_get_state(SIGNAL_ANALYZER_t *rd, SIGNAL_ANALYZER_t *gn){
  CHARGE_STATE_EVSE_e ret;
  SIGNAL_TYPE_e red, green;

  green = viridian_signal_get_type(gn);
  red = viridian_signal_get_type(rd);

  if(red == SIG_PWM || red == SIG_HIGH)
    ret = evse_Fault;
  else if(green == SIG_PWM || green == SIG_HIGH)
    ret = evse_Charging;
  else if(red == SIG_LOW && green == SIG_LOW)
    ret = evse_Not_Connected;
  else
    ret = evse_Not_Connected;
    
  return ret;
}
