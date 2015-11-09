This is the lyricsource componet for foo_uie_lyrics3.dll.It retrives lyrics from www.azlyrics.com. 

Component dll:
Release/foo_lyricsource.dll

Development enviroment:
Visual studio Express 2015 for Windows Desktop
Windows10pro64bit
foobar2000 1.3.9
foo_uie_lyric3 0.4.5

Original source:
https://code.google.com/p/foo-uie-lyrics3/downloads/detail?name=foo_uie_lyrics3%20SDK.zip&can=2&q=
https://foo-uie-lyrics3.googlecode.com/files/foo_uie_lyrics3%20SDK.zip
What I changed mainly are my_lyrics_source.cpp/h.

Requirements:
iconv and libxml2.
download
http://xmlsoft.org/sources/win32/iconv-1.9.2.win32.zip
http://xmlsoft.org/sources/win32/libxml2-2.7.8.win32.zip

Place these dll file to the directory that is conteind in PATH enviromment,or the directory where foobar2000.exe resides.
libxml2.dll
iconv.dll
