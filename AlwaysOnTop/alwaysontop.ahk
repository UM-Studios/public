SetKeyDelay, -1
SetWorkingDir %A_ScriptDir%

^SPACE::  ;toggle alwaysontop for active window
	Winset, Alwaysontop, , A
return

hide := 0
CapsLock:: ;toggle transparency for all AOT windows.
	WinGet, win, list,
	if (hide = 0){
		Loop % win {
			WinGet, style, Exstyle, % "ahk_id" win%A_Index%
			WinGetClass, class, % "ahk_id" win%A_Index%
			if (style & 0x8 and class != "Shell_TrayWnd"){
				Winset, ExStyle, +0x80020, % "ahk_id" win%A_Index%
				Winset, Transparent, 50, % "ahk_id" win%A_Index%
			}
		}
	hide := 1
	}
	else{
		Loop % win {
			Winset, ExStyle, -0x20, % "ahk_id" win%A_Index%
			Winset, Transparent, 255, % "ahk_id" win%a_index%
		}
	hide := 0
	}
return