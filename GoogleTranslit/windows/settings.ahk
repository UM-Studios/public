#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
;SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.

#include ocr.ahk

config := a_appdata . "\translitSettings.ini"
	
hkeys := {openSettings: "!+s", showTranslit: "!t", copyTranslit: "!+t", showTranslate: "!r", copyTranslate: "!+r"}

ids := ocr("ShowAvailableLanguages")
langs := []
for key, val in ids {
	langs.Insert(val, key)
}

set()
Gui,add,Text,x2 y4, OCR Language:
Gui,add,DropDownList, x100 y2 w200 vlangSelect
Gui,add,Text,x2 y44, Show Settings:
Gui,add,Hotkey, x100 y40 w200 vopenSettingsH
Gui,add,Text,x2 y84, Show Translit:
Gui,add,Hotkey, x100 y80 w200 vshowTranslitH
Gui,add,Text,x2 y124, Copy Translit:
Gui,add,Hotkey, x100 y120 w200 vcopyTranslitH
Gui,add,Text,x2 y164, Show Translate:
Gui,add,Hotkey, x100 y160 w200 vshowTranslateH
Gui,add,Text,x2 y204, Copy Translate:
Gui,add,Hotkey, x100 y200 w200 vcopyTranslateH
Gui,add,button, x50 y250 w80 gApply, Apply
Gui,add,button, x180 y250 w80 gCancel, Cancel
get()
GuiControl,,openSettingsH,%openSettings%
GuiControl,,showTranslitH,%showTranslit%
GuiControl,,copyTranslitH,%copyTranslit%
GuiControl,,showTranslateH,%showTranslate%
GuiControl,,copyTranslateH,%copyTranslate%
name := langs[language]
GuiControl,choosestring,langSelect,%name%

Gui,Show,,Translit Settings

return

esc::ExitApp
GuiClose:
ExitApp

Apply() {
	global hkeys, config, ids, langSelect
	Gui, Submit
	id := ids[langSelect]
	iniwrite, %id%, %config%, Language, language
	for key, val in hkeys {
		set := %key%H
		iniwrite, %set%, %config%, Hotkeys, %key%
	}
	set()
}

Cancel() {
	Gui, Cancel
}

get() {
	global ids
	choices := "|"
	for key, val in ids {
		choices .= key . "|"
	}
	GuiControl,,langSelect,%choices%
}

set() {
	global ids, hkeys, language, config
	iniread, language, %config%, Language, language
	if (language = "ERROR") {
		for key, val in ids {
			iniwrite, %key%, %config%, Language, language
			iniread, language, %config%, Language, language
			break
		}
	}
	for key, val in hkeys {
		iniread, %key%, %config%, Hotkeys, %key%
		if (%key% = "ERROR") {
			iniwrite, %val%, %config%, Hotkeys, %key%
			iniread, %key%, %config%, Hotkeys, %key%
		}
	}
}
