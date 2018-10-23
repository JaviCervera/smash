Strict

Rem
Local icons$[] = ["arrow_left.png", "", "folder_up.png"]
Local WIDTH = 16 * icons$.Dimensions()[0]
Local HEIGHT = 16
Local pixmap:TPixmap = CreatePixmap(WIDTH, HEIGHT, PF_RGBA8888)
Local c = 0
For Local icon$ = EachIn icons$
	If icon$ <> ""
		Local iconpng:TPixmap = LoadPixmap(icon$)
		pixmap.Paste iconpng, 16 * c, 0
		iconpng = Null
	End If
	c :+ 1
Next
SavePixmapPNG pixmap, "../requester_toolbar.png", 9
End Rem

Local icons$[] = ["page.png", "folder.png", "cd.png"]
Local WIDTH = 16 * icons$.Dimensions()[0]
Local HEIGHT = 16
Local pixmap:TPixmap = CreatePixmap(WIDTH, HEIGHT, PF_RGBA8888)
Local c = 0
For Local icon$ = EachIn icons$
	If icon$ <> ""
		Local iconpng:TPixmap = LoadPixmap(icon$)
		pixmap.Paste iconpng, 16 * c, 0
		iconpng = Null
	End If
	c :+ 1
Next
SavePixmapPNG pixmap, "../requester_icons.png", 9