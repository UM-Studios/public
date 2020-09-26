#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.
DetectHiddenWindows, On
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

return

~LButton::tooltip

OpenSettings:
   Hotkey, %openSettings%,,Off
   Hotkey, %showTranslit%,,Off
   Hotkey, %copyTranslit%,,Off
   Hotkey, %showTranslate%,,Off
   Hotkey, %copyTranslate%,,Off
   Gui,Show,,Translit Settings
return
ShowTranslit:
   show("lit")
return
CopyTranslit:
   show("lit", true)
return
ShowTranslate:
   show("late")
return
CopyTranslate:
   show("late", true)
return

Guiclose:
   Reload
return

Apply() {
   global hkeys, config, ids, langSelect
   Gui, Submit
   id := ids[langSelect]
   iniwrite, %id%, %config%, Language, language
   for key, val in hkeys {
      set := %key%H
      iniwrite, %set%, %config%, Hotkeys, %key%
   }
   Reload
}

Cancel() {
	Gui, Cancel
    Reload
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
   global ids, hkeys, language, config, openSettings, showTranslit, copyTranslit, showTranslate, copyTranslate
   iniread, language, %config%, Language, language
   if (language = "ERROR" or language = "") {
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
   Hotkey, %openSettings%, OpenSettings
   Hotkey, %showTranslit%, ShowTranslit
   Hotkey, %copyTranslit%, CopyTranslit
   Hotkey, %showTranslate%, ShowTranslate
   Hotkey, %copyTranslate%, CopyTranslate
}

RemoveToolTip:
tooltip 
return

show(type, copy := false) {
   global language
   clipsave := ClipboardAll
   clipboard := 
   send ^c
   clipwait, 0
   if !errorlevel {
      text := clipboard
   }
   else {
      runwait, explorer.exe ms-screenclip:
      winwaitactive, Screen snipping
      winwaitnotactive, Screen snipping
      hBitmap := Clipmage()
      DllCall("CloseClipboard")
      ;msgbox % hBitmap
      if (abs(hBitmap) > 4){
         pIRandomAccessStream := HBitmapToRandomAccessStream(hBitmap)
         ;msgbox % pIRandomAccessStream
         DllCall("DeleteObject", "uint", hBitmap)
         ;msgbox % language
         text := ocr(pIRandomAccessStream, language)
         if (text = "") {
            tooltip couldn't recognize text
            clipboard := clipsave
            ;settimer, RemoveToolTip, -600
            return
         }
      }
      else {
         tooltip invalid input
         clipboard := clipsave
         ;settimer, RemoveToolTip, -600
         return
      }
   }
   lit := translit(text, type)
   if (lit = 0) {
      output := text
   }
   else{
      if !IsObject(lit){
         output := lit
      }
      else
      output := clipboard
   }
   if copy
      clipboard := output
   else
      clipboard := clipsave
   tooltip % output
}

translit(str, type, from := "auto", to := "en")  {
   static JS := CreateScriptObj(), _ := JS.( GetJScript() ) := JS.("delete ActiveXObject; delete GetObject;")
   json := SendRequest(JS, str, to, from, proxy := "")
   oJSON := JS.("(" . json . ")")
   if(type = "lit")
      trans := oJSON[0][oJSON[0].length -1][oJSON[0][oJSON[0].length -1].length - 1]
   if(type = "late")
      trans := oJSON[0][0][0]
   return trans
}

SendRequest(JS, str, tl, sl, proxy) {
   ComObjError(false)
   http := ComObjCreate("WinHttp.WinHttpRequest.5.1")
   ( proxy && http.SetProxy(2, proxy) )
   http.open( "POST", "https://translate.google.com/translate_a/single?client=webapp&sl="
      . sl . "&tl=" . tl . "&hl=" . tl
      . "&dt=at&dt=bd&dt=ex&dt=ld&dt=md&dt=qca&dt=rw&dt=rm&dt=ss&dt=t&ie=UTF-8&oe=UTF-8&otf=0&ssel=0&tsel=0&pc=1&kc=1"
      . "&tk=" . JS.("tk").(str), 1 )
   http.SetRequestHeader("Content-Type", "application/x-www-form-urlencoded;charset=utf-8")
   http.SetRequestHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:47.0) Gecko/20100101 Firefox/47.0")
   http.send("q=" . URIEncode(str))
   http.WaitForResponse(-1)
   Return http.responsetext
}

URIEncode(str, encoding := "UTF-8")  {
   VarSetCapacity(var, StrPut(str, encoding))
   StrPut(str, &var, encoding)

   While code := NumGet(Var, A_Index - 1, "UChar")  {
      bool := (code > 0x7F || code < 0x30 || code = 0x3D)
      UrlStr .= bool ? "%" . Format("{:02X}", code) : Chr(code)
   }
   Return UrlStr
}

GetJScript()
{
   script =
   (
      var TKK = ((function() {
        var a = 561666268;
        var b = 1526272306;
        return 406398 + '.' + (a + b);
      })());

      function b(a, b) {
        for (var d = 0; d < b.length - 2; d += 3) {
            var c = b.charAt(d + 2),
                c = "a" <= c ? c.charCodeAt(0) - 87 : Number(c),
                c = "+" == b.charAt(d + 1) ? a >>> c : a << c;
            a = "+" == b.charAt(d) ? a + c & 4294967295 : a ^ c
        }
        return a
      }

      function tk(a) {
          for (var e = TKK.split("."), h = Number(e[0]) || 0, g = [], d = 0, f = 0; f < a.length; f++) {
              var c = a.charCodeAt(f);
              128 > c ? g[d++] = c : (2048 > c ? g[d++] = c >> 6 | 192 : (55296 == (c & 64512) && f + 1 < a.length && 56320 == (a.charCodeAt(f + 1) & 64512) ?
              (c = 65536 + ((c & 1023) << 10) + (a.charCodeAt(++f) & 1023), g[d++] = c >> 18 | 240,
              g[d++] = c >> 12 & 63 | 128) : g[d++] = c >> 12 | 224, g[d++] = c >> 6 & 63 | 128), g[d++] = c & 63 | 128)
          }
          a = h;
          for (d = 0; d < g.length; d++) a += g[d], a = b(a, "+-a^+6");
          a = b(a, "+-3^+b+-f");
          a ^= Number(e[1]) || 0;
          0 > a && (a = (a & 2147483647) + 2147483648);
          a `%= 1E6;
          return a.toString() + "." + (a ^ h)
      }
   )
   Return script
}

CreateScriptObj() {
   static doc
   doc := ComObjCreate("htmlfile")
   doc.write("<meta http-equiv='X-UA-Compatible' content='IE=9'>")
   Return ObjBindMethod(doc.parentWindow, "eval")
}