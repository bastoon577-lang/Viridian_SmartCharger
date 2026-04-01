# Viridian_SmartCharger

Développement d'un système de recharge VE basé sur les plateformes :
* [ESP01](https://www.captain-arduino.fr/esp8266-01s/),
* [Viridian](https://www.amazon.fr/Viridian-EV-EPC20L10-Contr%C3%B4leur-Blanc/dp/B097BTRGYL).

*******
Table des matières
 1. [Mes motivations](#motivation)
 2. [Concept du SmartCharger](#concept)
 3. [Clone du projet](#clone)
 4. [Compile du projet](#build)
*******

<div id='motivation'/> 

## Mes motivations
J'ai souhaité développer un système de recharge intelligent pour véhicule électrique capable d'adapter la puissance de recharge en temps réel, et ainsi éviter tout risque de surcharge du réseau électrique.

<div id='concept'/> 

## Concept du SmartCharger
Veuillez consulter le [Wiki du projet](https://github.com/bastoon577-lang/Viridian_SmartCharger/wiki) pour plus d'informations concernant le concept.

Ce projet fonctionne de paire avec le projet [Module TIC](https://github.com/bastoon577-lang/Module_TIC/wiki), et permet la lecture des données issues du compteur Linky au travers du réseau LAN en utilisant le réseau Wifi.

<div id='clone'/> 

## Clone du projet

Le clonage du projet passe par les étapes suivantes:
```
git clone https://github.com/bastoon577-lang/Viridian_SmartCharger.git
cd Viridian_SmartCharger/
git submodule update --init --recursive
```

<div id='build'/> 

## Compilation du projet

Veuillez vous référer au [Wiki de compilation](https://github.com/bastoon577-lang/Viridian_SmartCharger/wiki/Compilation-du-Viridian_SmartCharger).
 
 ###### Auteur : *Sébastien DALIGAULT*. 
