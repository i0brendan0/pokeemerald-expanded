EventScript_HiddenTree::
    goto_if_unset FLAG_HIDDEN_TREE_EXPLANATION, EventScript_HiddenTree_NotEnabled
    lockall
    msgbox Text_HiddenTreeAskShake, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, EventScript_HiddenTree_End
    special FindHiddenTreeResult
    goto_if_eq VAR_RESULT, FALSE, EventScript_HiddenTree_Empty
    special FindHiddenTreeItemOrPokemon
    goto_if_eq VAR_RESULT, TRUE, EventScript_HiddenTree_GotItem
    setwildbattle VAR_0x8000, VAR_0x8001
    waitstate
    setflag FLAG_FORCE_HIDDEN_ABILITY
    dowildbattle
    clearflag FLAG_FORCE_HIDDEN_ABILITY
EventScript_HiddenTree_Empty:
    msgbox Text_HiddenTreeEmpty, MSGBOX_DEFAULT
EventScript_HiddenTree_End:
    releaseall
EventScript_HiddenTree_NotEnabled:
    end
    
EventScript_HiddenTree_GotItem:
	callstd STD_FIND_ITEM
    releaseall
    end

Text_HiddenTreeAskShake:
    .string "This tree looks lively.\n"
    .string "Do you want to shake it?$"

Text_HiddenTreeEmpty:
    .string "There's nothing here.$"
