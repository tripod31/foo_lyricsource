# -*- coding: utf-8 -*-
from get_lyric.common import scraper_base
import io
import logging
from robobrowser import RoboBrowser

'''
get lyric from site
'''
class j_lyric_net(scraper_base):
    def __init__(self,artist,song):
        site = 'http://j-lyric.net/'
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
        form = browser.get_form(action='http://search.j-lyric.net/index.php')
        form['kt'].value = self.song
        form['ka'].value = self.artist
        browser.submit_form(form)
        
        #find song link
        node = browser.find(lambda tag:self.test_tag(tag,'a',self.song))
        if node is None:
            logging.warn(self.log_msg("song not found."))
            return False
        browser.follow_link(node)
        
        #find lyric
        node = browser.find('p',id="lyricBody")
        if node is None:
            logging.warn(self.log_msg("lyric not found."))
            return False
        
        buf = io.StringIO()
        self.get_text(node,buf)
        lyric = buf.getvalue()
        
        self.lyric=lyric
        
        return True
