ChangeDeoxysForm::
    lockall
    msgbox ChangeDeoxysForm_Text_Beginning, MSGBOX_YESNO
    compare VAR_RESULT, YES
    goto_if_eq ChangeDeoxysForm_Start
ChangeDeoxysForm_End:
    msgbox ChangeDeoxysForm_Text_End, MSGBOX_DEFAULT
    releaseall
    end

ChangeDeoxysForm_Start:
    msgbox ChangeDeoxysForm_Text_Select, MSGBOX_DEFAULT
    special ChoosePartyMon
    waitstate
    compare VAR_0x8004, 255
    goto_if_eq ChangeDeoxysForm_End
    special TryChangeDeoxysForm
    compare VAR_RESULT, TRUE
    goto_if_eq ChangeDeoxysForm_Success
    goto ChangeDeoxysForm_End

ChangeDeoxysForm_Success:
    playmoncry SPECIES_DEOXYS, 0
    msgbox ChangeDeoxysForm_Text_Success, MSGBOX_DEFAULT
    waitmoncry
    waitbuttonpress
    goto ChangeDeoxysForm_End

ChangeDeoxysForm_Text_Beginning:
    .string "Do you want to change\nyour Deoxys?$"

ChangeDeoxysForm_Text_End:
    .string "...$"

ChangeDeoxysForm_Text_Select:
    .string "Select a Deoxys.$"

ChangeDeoxysForm_Text_Success:
    .string "... It is done.$"
