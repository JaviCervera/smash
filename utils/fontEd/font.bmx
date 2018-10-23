
Function CreateFontPixmap:TPixmap(pixmapsize = 256)
	Local firstChar = 0, lastChar = 255
	Local charCount = lastChar - firstChar + 1

	Local testString$ = ""
	For Local i = 0 Until charCount
		testString$ :+ Chr$(firstChar + i)
	Next

	Local win:TGadget = CreateWindow("", 0, 0, 100, 100, Null) ; HideGadget win
	Local canvas:TGadget = CreateCanvas(0, 0, pixmapsize, pixmapsize, win)
	SetGraphics CanvasGraphics(canvas)
	Cls
	Local f:TImageFont = LoadImageFont(Ui.fntFile$, Ui.fntSize, Ui.fntFlags)
	SetImageFont f
	Local x = 0, y = 0
	For Local i = 0 Until charCount
		SetColor 255, 255, 255; DrawText Chr$(firstChar + i), x, y
		SetColor 255, 255, 0; Plot x, y
		SetColor 255, 0, 0; Plot x + TextWidth(Chr$(firstChar + i)) + 1, y + TextHeight(Chr$(firstChar + i)) + 1
		
		x :+ pixmapsize/16
		If x >= pixmapsize Then x = 0; y :+ pixmapsize/16
	Next
	Flip
	Local pixmap:TPixmap = GrabPixmap(0, 0, GraphicsWidth(), GraphicsHeight())
	FreeGadget win
	Return pixmap
End Function