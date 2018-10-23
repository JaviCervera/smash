Incbin "requester_icons.png"

Function RequestDrives$[]()
	Global drives$[]
	If drives.Dimensions() <> Null Then Return drives$
	For Local i = Asc("A") To Asc("Z")
		If FileType(Chr(i) + ":") = FILETYPE_DIR
			If drives.Dimensions() = Null Then drives$ = [""] Else drives$ = drives$[..drives$.Dimensions()[0]+1]
			drives$[drives$.Dimensions()[0]-1] = Chr(i) + ":"
		End If
	Next
	Return drives$
End Function

Function RequestDirs$[](dir$)
	Local d = ReadDir(dir$)
	Local dirs$[]
	Repeat
		Local file$ = NextFile$(d)
		If file$ = "" Then Exit
		If FileType(dir$ + "/" + file$) = FILETYPE_DIR And file$ <> "."
			If dirs.Dimensions() = Null Then dirs$ = [""] Else dirs$ = dirs$[..dirs$.Dimensions()[0]+1]
			dirs$[dirs$.Dimensions()[0]-1] = file$
		End If
	Forever
	CloseDir d
	Return dirs$
End Function

Function RequestFiles$[](dir$, ext$ = "")
	Local d = ReadDir(dir$)
	Local files$[]
	Repeat
		Local file$ = NextFile$(d)
		If file$ = "" Then Exit
		If FileType(dir$ + "/" + file$) = FILETYPE_FILE
			If ext$ = "" Or (ext$ <> "" And Lower$(ExtractExt$(file$)) = Lower$(ext$))
				If files.Dimensions() = Null Then files$ = [""] Else files$ = files$[..files$.Dimensions()[0]+1]
				files$[files$.Dimensions()[0]-1] = file$
			End If
		End If
	Forever
	CloseDir d
	Return files$
End Function

Function RequestFileFont$()
	Local ret$ = ""
	Local curdir$ = CurrentDir$()
?Win32
	Local windir$ = GetEnv_("WINDIR")
	ChangeDir windir$ + "/Fonts"
?MacOS
	ChangeDir("/Library/Fonts")
?Linux
	ChangeDir("/usr/share/fonts/")
?
	Local win:TGadget = CreateWindow("Font:", ClientWidth(Desktop())/2 - 200, ClientHeight(Desktop())/2 - 150, 400, 300, Ui.win, WINDOW_TITLEBAR | WINDOW_CLIENTCOORDS)
	Local label:TGadget = CreateLabel(CurrentDir$(), 4, 4, ClientWidth(win) - 8, 20, win)
	Local listbox:TGadget = CreateListBox(4, 24, ClientWidth(win) - 8, ClientHeight(win) - 28, win)
	SetGadgetIconStrip listbox, LoadIconStrip("incbin::requester_icons.png")

	Local dirs$[] = RequestDirs(CurrentDir$())
	Local files$[] = RequestFiles(CurrentDir$(), "ttf")
	For Local dir$ = EachIn dirs$
		AddGadgetItem listbox, dir$, 0, 1
	Next
	For Local file$ = EachIn files$
		AddGadgetItem listbox, file$, 0, 0
	Next

	Local selItem = -1
	Repeat
		Select WaitEvent()
			Case EVENT_GADGETACTION
				Select EventSource()
					Case listbox
						If SelectedGadgetItem(listbox) = selItem
							If FileType(GadgetItemText$(listbox, SelectedGadgetItem(listbox))) = FILETYPE_DIR
								ChangeDir GadgetItemText$(listbox, SelectedGadgetItem(listbox))
								SetGadgetText label, CurrentDir$()
								ClearGadgetItems listbox
								Local dirs$[] = RequestDirs(CurrentDir$())
								Local files$[] = RequestFiles(CurrentDir$(), "ttf")
								For Local dir$ = EachIn dirs$
									AddGadgetItem listbox, dir$, 0, 1
								Next
								For Local file$ = EachIn files$
									AddGadgetItem listbox, file$, 0, 0
								Next
								If GadgetItemText$(listbox, 0) <> ".." Then InsertGadgetItem listbox, 0, "<" + Left$(CurrentDir$(), 2) + ">", 0, 2
								selItem = -1
							Else If FileType(GadgetItemText$(listbox, SelectedGadgetItem(listbox))) = FILETYPE_FILE
								ret$ = CurrentDir$() + "/" + GadgetItemText$(listbox, SelectedGadgetItem(listbox))
								Exit
							Else If Left$(GadgetItemText$(listbox, SelectedGadgetItem(listbox)), 1) = "<"
								ClearGadgetItems listbox
								Local drives$[] = RequestDrives()
								For Local drive$ = EachIn drives$
									AddGadgetItem listbox, drive$, 0, 2
								Next
							End If
						End If
						selItem = SelectedGadgetItem(listbox)
				End Select
			Case EVENT_WINDOWCLOSE
				ret$ = ""
				Exit
		End Select
	Forever
	ActivateWindow Ui.win
	FreeGadget win
	ChangeDir curdir$
	Return ret$
End Function