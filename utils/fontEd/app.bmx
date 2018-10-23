Type App
	Function Init()
		'RequestDrives()
		Ui.Init
	End Function
	
	Function Loop()
		WaitEvent()
		Ui.Loop
	End Function
	
	Function Finish()
		Ui.Finish
	End Function
	
	Function Quit()
		Finish
		End
	End Function
End Type
