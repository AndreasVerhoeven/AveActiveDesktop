Dim url
url = "http://www.desktopfx.net"
url = InputBox("Which site do you want to use as your wallpaper?", "AveActiveDesktop", url)

Dim htmlDesktop
Set htmlDesktop = CreateObject("AveActiveDesktop.AveHtmlDesktop")
htmlDesktop.Set(url)