foo_lyricsource.dll
=====
This is the lyricsource componet for foo_uie_lyrics3.dll.It retrives lyrics from sites.  

Component dll  
-----
Release/foo_lyricsource.dll  

Development enviroment  
-----
Visual studio Express 2015 for Windows Desktop  
Windows10pro64bit  
foobar2000 1.3.9  
foo_uie_lyric3 0.4.5  

Original source
-----
<https://code.google.com/p/foo-uie-lyrics3/downloads/detail?name=foo_uie_lyrics3%20SDK.zip&can=2&q=>  
<https://foo-uie-lyrics3.googlecode.com/files/foo_uie_lyrics3%20SDK.zip>  
What I changed mainly are my_lyrics_source.cpp/h.  

Requirements  
-----
iconv and libxml2.  
download  
<http://xmlsoft.org/sources/win32/iconv-1.9.2.win32.zip>  
<http://xmlsoft.org/sources/win32/libxml2-2.7.8.win32.zip>  
Place these dll files to the directory that is containd in PATH enviromment,or the directory where foobar2000.exe resides.  

    libxml2.dll  
    iconv.dll  

Foobar2000 Configuration  
-----
After installing the new component and placing the 2 DLLs in the Foobar directory, Go to Preferences > Tools > Lyric Show 3 and add "www.azlyrics.com" from 'Available Sources' to 'Search Order'.  
I would suggest deactivating those source by moving it back to 'Available Sources'.  

    "Online DB: Google Search"  
    "Online DB: Timestamped2"  

To Use "External Command" Source  
-----
####foobar2000 configuration
Same as abobe,except,source name is "External Command".  

####Place python script
From <https://github.com/tripod31/get_lyric>,Place those files to the directory where foobar2000.exe resides.  

    get_lyric.py  
    "get_lyric" directory  

####Install python3
Download installer from https://www.python.org/.  
Make sure that those directories are in your PATH enviromnevt.  

    [python installed dir]  
    [python installed dir]\script  
For example,python installed dir is like "c:\python"

####Install required libraries of python  
In command prompt:  

    pip install robobrowser beautifulsoup

About "get_lyric.py"
-----
This python script search lyric from sites.  
The script is executed by foo_lyricsource.dll,with this argument format:  

    python get_lyrics.py --artist "artist" --song "song"  

and the script put lyric string to standard output.If standard output is none,The dll consider it found no matched lyric.  
This script put some debug imformation to "get_lyric.log" at the same directory.  
ChangeLog  
-----
####2015/11/11  
1st release  

####2015/11/25  
Fix for access violation error.If download_page() fails,it aborts to process.

####2016/01/13  
Added "external command" source.Explanation is above.  
Currently,I can't access to "<http://www.azlyrics.com>".I can't test "<http://www.azlyrics.com>" source now.So I'm not sure the source works well.
