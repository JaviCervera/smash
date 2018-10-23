Strict

Local icons$[] = ["image.png", "", "disk.png", "", "comment.png"]
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

SavePixmapPNG pixmap, "../toolbar.png", 9