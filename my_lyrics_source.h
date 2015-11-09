#ifndef _MY_LYRICS_SOURCE
#define _MY_LYRICS_SOURCE

#include "libxml\HTMLparser.h"
#include <string>

//see lyric_source_base.h for explanations of what you need to to in each method

//This is an example of how to create your own search_requirements.
//This allows you to safely store data between calls to PrepareSearch() and Search()
class custom_search_requirements : public search_requirements
{
public:
	pfc::string8 some_example_string;

	//This must be declared as an entrypoint service (otherwise you'll get a service duplication exception)
	FB2K_MAKE_SERVICE_INTERFACE_ENTRYPOINT( custom_search_requirements );
};

class my_lyrics_source : public lyric_source_base
{
	//do your http requests through this. It automatically uses the user's proxy/timeout settings 
	lyric_http_request::ptr m_pHttpClient;


	// for DOM scraping
	/*
	std::string m_content;
	bool m_scraping;
	xmlNode* my_lyrics_source::FindNode(xmlNode*& element);
	void my_lyrics_source::GetContent(xmlNode*& element);
	void my_lyrics_source::GetLyrics(xmlNode*& element);
	*/
public:

	my_lyrics_source() : lyric_source_base() {};
	~my_lyrics_source() {};

	void GetName( pfc::string_base& out ) { out = "www.azlyrics.com"; }

	const GUID GetGUID();

	bool PrepareSearch( const search_info* pQuery, lyric_result_client::ptr p_results, search_requirements::ptr& pRequirements );

	bool Search( const search_info* pQuery, search_requirements::ptr& pRequirements, lyric_result_client::ptr p_results );

	bool Load( lyric_container_base* lyric, request_source p_source );

	//return true if you want to be able to show a properties dialogue (in preferences)
	bool HasProperties() { return true; }

	//show your modal dialogue
	void ShowProperties( HWND parent );

	void SetHttpClient( lyric_http_request::ptr p_client ) { m_pHttpClient = p_client; }
};

#endif

