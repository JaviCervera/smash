Strict

Framework MaxGui.MaxGui
Import MaxGui.Drivers
Import BRL.Max2D
Import BRL.GLMax2D
Import BRL.FreeTypeFont
Import BRL.PNGLoader
Import BRL.Retro
Import BRL.EventQueue

?Win32
Import "xpmanifest.o"
?

Include "app.bmx"
Include "font.bmx"
Include "requester.bmx"
Include "ui.bmx"

Const VERSION$ = "1.0"
Const ABOUT$ = "Smash Font Editor - Version " + VERSION$
Const WINTITLE$ = "Font Editor"
Const WINWIDTH = 400
Const WINHEIGHT = 200

App.Init
Repeat
	App.Loop
Forever