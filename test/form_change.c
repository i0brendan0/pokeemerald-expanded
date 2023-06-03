#include "global.h"
#include "test_battle.h"

SINGLE_BATTLE_TEST("Xerneas changes into Active Form upon battle start")
{
    GIVEN {
        ASSUME(P_GEN_6_POKEMON == TRUE);
        PLAYER(SPECIES_XERNEAS);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } THEN {
        EXPECT_EQ(player->species, SPECIES_XERNEAS_ACTIVE);
    }
}

SINGLE_BATTLE_TEST("Zacian changes into its Crowned Form when holding the Rusted Sword upon battle start")
{
    u16 item;
    PARAMETRIZE { item = ITEM_NONE; }
    PARAMETRIZE { item = ITEM_RUSTED_SWORD; }
    GIVEN {
        ASSUME(P_GEN_8_POKEMON == TRUE);
        PLAYER(SPECIES_ZACIAN) { Item(item); };
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } THEN {
        if (item == ITEM_NONE)
            EXPECT_EQ(player->species, SPECIES_ZACIAN);
        else
            EXPECT_EQ(player->species, SPECIES_ZACIAN_CROWNED_SWORD);
    }
}

SINGLE_BATTLE_TEST("Zacian's Iron Head becomes Behemoth Blade upon form change")
{
    GIVEN {
        ASSUME(P_GEN_8_POKEMON == TRUE);
        PLAYER(SPECIES_ZACIAN) { Item(ITEM_RUSTED_SWORD); Moves(MOVE_IRON_HEAD, MOVE_CELEBRATE); };
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } THEN {
        ASSUME(player->species == SPECIES_ZACIAN_CROWNED_SWORD); // Assumes form change worked.
        EXPECT_EQ(player->moves[0], MOVE_BEHEMOTH_BLADE);
    }
}

SINGLE_BATTLE_TEST("Zamazenta changes into its Crowned Form when holding the Rusted Shield upon battle start")
{
    u16 item;
    PARAMETRIZE { item = ITEM_NONE; }
    PARAMETRIZE { item = ITEM_RUSTED_SHIELD; }
    GIVEN {
        ASSUME(P_GEN_8_POKEMON == TRUE);
        PLAYER(SPECIES_ZAMAZENTA) { Item(item); };
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } THEN {
        if (item == ITEM_NONE)
            EXPECT_EQ(player->species, SPECIES_ZAMAZENTA);
        else
            EXPECT_EQ(player->species, SPECIES_ZAMAZENTA_CROWNED_SHIELD);
    }
}

SINGLE_BATTLE_TEST("Zamazenta's Iron Head becomes Behemoth Bash upon form change")
{
    GIVEN {
        ASSUME(P_GEN_8_POKEMON == TRUE);
        PLAYER(SPECIES_ZAMAZENTA) { Item(ITEM_RUSTED_SHIELD); Moves(MOVE_IRON_HEAD, MOVE_CELEBRATE); };
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } THEN {
        ASSUME(player->species == SPECIES_ZAMAZENTA_CROWNED_SHIELD); // Assumes form change worked.
        EXPECT_EQ(player->moves[0], MOVE_BEHEMOTH_BASH);
    }
}

SINGLE_BATTLE_TEST("Aegislash reverts to Shield Form upon switching out")
{
    GIVEN {
        ASSUME(P_GEN_6_POKEMON == TRUE);
        PLAYER(SPECIES_AEGISLASH);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
        TURN { SWITCH(player, 1); }
        TURN { SWITCH(player, 0); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_STANCE_CHANGE);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_FORM_CHANGE, player);
        MESSAGE("Aegislash used Tackle!");
        MESSAGE("Foe Wobbuffet used Celebrate!");
    } THEN {
        EXPECT_EQ(player->species, SPECIES_AEGISLASH);
    }
}

SINGLE_BATTLE_TEST("Aegislash reverts to Shield Form upon fainting")
{
    GIVEN {
        ASSUME(P_GEN_6_POKEMON == TRUE);
        PLAYER(SPECIES_AEGISLASH) { HP(1); };
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_GUST); SEND_OUT(player, 1);}
    } SCENE {
        MESSAGE("Foe Wobbuffet used Gust!");
        MESSAGE("Aegislash fainted!");
    } THEN {
        EXPECT_EQ(GetMonData(&PLAYER_PARTY[0], MON_DATA_SPECIES), SPECIES_AEGISLASH);
    }
}
