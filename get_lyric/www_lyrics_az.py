# -*- coding: utf-8 -*-
from get_lyric.common import scraper_base
import io
import logging
from robobrowser import RoboBrowser

'''
get lyric from "www.lyrics.az"
'''
class www_lyrics_az(scraper_base):
    def __init__(self,artist,song):
        site = 'https://www.lyrics.az/'
        super().__init__(site,artist,song)
    
    '''
    return value:

    True:success
    Faluse:error
    '''
    def get_lyric(self):    
        browser = RoboBrowser(parser="html.parser",history=True)
        browser.open(self.site)
        
        #search artist
        form = browser.get_form(action='/')
        form['keyword'].value = self.artist
        browser.submit_form(form)
        
        #click artist
        node = browser.find(lambda tag:self.test_tag(tag,'a',self.artist))
        if node is None:
            logging.warn(self.log_msg("artist not found."))
            return False
        browser.follow_link(node)
        
        #click "View All Songs"
        node = browser.find('a',text='View All songs')
        if node is None:
            logging.warn(self.log_msg("[View All Songs]link not found"))
            return False
        browser.follow_link(node)
        
        #find song link
        node = browser.find(lambda tag:self.test_tag(tag,'a',self.song))
        if node is None:
            logging.warn(self.log_msg("song not found."))
            return False
        browser.follow_link(node)
        
        #find lyric
        node = browser.find('span',id="lyrics")
        if node is None:
            logging.warn(self.log_msg("lyric not found."))
            return False
        
        buf = io.StringIO()
        self.get_text(node,buf)
        lyric = buf.getvalue()
        if lyric.startswith("We haven't lyrics of this song."):
            logging.warn(self.log_msg("lyric not found."))
            return False
        
        lyric=lyric.replace("´", "'")   #remove character that can't be passed to dll
        self.lyric=lyric
        
        return True
