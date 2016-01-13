#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import re
from robobrowser import RoboBrowser
import argparse
from bs4 import element
import io
import logging

'''
www.lyrics.azからlyricを取得
'''

'''
beautifulsoupのnodeを指定してそのタグ以下の内容をテキストで返す
buf    StringIO:テキストを戻すためのバッファ
'''
def get_text(node,buf):
    if isinstance(node,element.Tag):
        if node.name == "br":
            buf.write("\n")
        for e in node.contents:
            get_text(e,buf)
    if isinstance(node,element.NavigableString):
        t = re.sub(r'[\n\xa0]','',node.string)
        buf.write(t)

def remove_unwanted_chars(str):
    str=re.sub('\(.*\)','',str) #(・・・)
    str=re.sub('\[.*\]','',str) #[・・・]
    str= re.sub('[\*\(\)\[\]]',"",str)
    return str

def get_lyric(artist,song):
    #引数から不要な文字を除く
    artist = remove_unwanted_chars(artist)
    song = remove_unwanted_chars(song)
    
    browser = RoboBrowser(parser="html.parser",history=True)
    browser.open('https://www.lyrics.az/')
    
    #search by artist
    form = browser.get_form(action='/')
    form['keyword'].value = artist
    browser.submit_form(form)
    
    #find artist
    artists = browser.find_all('a',text=re.compile(r'%s' % artist,re.IGNORECASE))
    if artists is None or len(artists)==0:
        logging.info("artist not found.artist:[%s]song:[%s]" % (artist,song))
        return ""
    browser.follow_link(artists[0])
    
    #find song
    songs = browser.find_all('a',text=re.compile(r'%s' % song,re.IGNORECASE))
    if songs is None or len(songs)==0:
        logging.info("song not found.artist:[%s]song:[%s]" % (artist,song))
        return ""
    browser.follow_link(songs[0])
    
    lyrics = browser.find_all('span',id="lyrics")
    if lyrics is None or len(lyrics)==0:
        logging.info("lyric not found.artist:[%s]song:[%s]" % (artist,song))
        return ""
    buf = io.StringIO()
    get_text(lyrics[0],buf)
    ret = buf.getvalue()
    return ret

if __name__ == '__main__':
    #引数
    parser = argparse.ArgumentParser()
    parser.add_argument('--artist')
    parser.add_argument('--song')
    
    args=parser.parse_args()
    logging.basicConfig(filename='get_lyric.log',level=logging.INFO)
    
    lyric=""
    try:
        lyric=get_lyric(args.artist, args.song)
    except Exception as e:
        logging.error("artist:[%s]song:[%s]error:[%s]" % (args.artist,args.song,e))
    if len(lyric)>0:
        print(lyric,end="")
