# foo_lyricsource.dll
This is the lyricsource componet for foo_uie_lyrics3.dll.It retrives lyrics from "www.azlyrics.com"  

**Component dll**  
Release/foo_lyricsource.dll  

**Development enviroment**  
Visual studio Express 2015 for Windows Desktop  
Windows10pro64bit  
foobar2000 1.3.9  
foo_uie_lyric3 0.4.5  

**Original source**  
https://code.google.com/p/foo-uie-lyrics3/downloads/detail?name=foo_uie_lyrics3%20SDK.zip&can=2&q=  
https://foo-uie-lyrics3.googlecode.com/files/foo_uie_lyrics3%20SDK.zip  
What I changed mainly are my_lyrics_source.cpp/h.  

**Requirements**  
iconv and libxml2.  
download  
http://xmlsoft.org/sources/win32/iconv-1.9.2.win32.zip  
http://xmlsoft.org/sources/win32/libxml2-2.7.8.win32.zip  
Place these dll files to the directory that is containd in PATH enviromment,or the directory where foobar2000.exe resides.  
libxml2.dll  
iconv.dll  

**Configuration**  
After installing the new component and placing the 2 DLLs in the Foobar directory, Go to Preferences > Tools > Lyric Show 3 and add "www.azlyrics.com" from 'Available Sources' to 'Search Order'.  
I would suggest deactivating those source by moving it back to 'Available Sources'.  
"Online DB: Google Search"  
"Online DB: Timestamped2"  

**To Use "External Command" Source(Added:2016/01/13)**  
Place get_lyrics.py to the directory where foobar2000.exe resides.  
To use this script,you need to install python3,and required libraries.  
To install libraries,After you installed python3,in command prompt:  
>pip install robobrowser beautifulsoup

**To modify get_lyric.py**  
Currentry this python script search lyric from "www.lyrics.az".You can modify the script.  
The script is executed by foo_lyricsource.dll,with argument format:  
>python get_lyrics.py --artist "artist" --song "song"  

and the script put lyric string to standard output.If standard output is none,The dll consider it found no matched lyric.

**ChangeLog**  
2015/11/11  
1st release  

2015/11/25  
Fix for access violation error.If download_page() fails,it aborts to process.

2016/01/13  
Currently,I can't access to "www.azlyrics.com".Maybe connection from my country is blocked?  
So I added "external command" source.Explanation is above.  
I can't test "www.azlyrics.com" source now.So I'm not sure the source works well.
