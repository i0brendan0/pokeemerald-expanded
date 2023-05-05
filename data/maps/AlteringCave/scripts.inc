AlteringCave_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AlteringCave_OnTransition
	.byte 0

AlteringCave_OnTransition:
	setflag FLAG_LANDMARK_ALTERING_CAVE
    goto_if_set FLAG_SET_ALTERING_CAVE, AlteringCave_PokemonAlreadySet
    setflag FLAG_SET_ALTERING_CAVE
	addvar VAR_ALTERING_CAVE_WILD_SET, 1
	goto_if_ne VAR_ALTERING_CAVE_WILD_SET, 10, AlteringCave_PokemonAlreadySet
	setvar VAR_ALTERING_CAVE_WILD_SET, 0
AlteringCave_PokemonAlreadySet:
	end

