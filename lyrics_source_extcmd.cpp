#include "StdAfx.h"
#include "lyrics_source_extcmd.h"

#include <regex>
#include "util.h"

//You must use your own GUID, this one is for example purposes only (in VS2010 Tools->Create GUID).
// {FD993696-0826-45C9-9D72-1B0640093474}
const GUID search_requirements_extcmd::class_guid =
{ 0xfd993696, 0x826, 0x45c9,{ 0x9d, 0x72, 0x1b, 0x6, 0x40, 0x9, 0x34, 0x74 } };

static const service_factory_t< search_requirements_extcmd > search_requirements_extcmd_factory;

//You must use your own GUID, this one is for example purposes only.
// {7D128420-3641-4038-BE43-3536FC67E57C}
static const GUID guid =
{ 0x7d128420, 0x3641, 0x4038,{ 0xbe, 0x43, 0x35, 0x36, 0xfc, 0x67, 0xe5, 0x7c } };

static const source_factory<lyrics_source_extcmd> lyrics_source_extcmd_factory;

//Each different source must return it's own unique GUID
const GUID lyrics_source_extcmd::GetGUID()
{
	return guid;
}

bool lyrics_source_extcmd::PrepareSearch( const search_info* pQuery, lyric_result_client::ptr p_results, search_requirements::ptr& pRequirements )
{
	TRACK_CALL_TEXT( "lyrics_source_extcmd::PrepareSearch" );
	
	//If you need to save some data, use the search requirements interface (see lyrics_source_extcmd.h).
	//This creates the instance of your custom search requirements.
	search_requirements_extcmd::ptr requirements = static_api_ptr_t< search_requirements_extcmd >().get_ptr();

	//Set some data
	requirements->some_example_string = "Custum Search:\n";

	//Copy the requirements so the lyrics plugin can provide them for the Search() function.
	pRequirements = requirements.get_ptr();

	//return true on success, false on failure
	return true;
}


std::string lyrics_source_extcmd::removeUnwantedStr(std::string& str) {
	std::string ret;
	ret = util::removeStrRegex(str, "\"");
	return ret;
}

std::string lyrics_source_extcmd::exec_extcmd(std::string artist,std::string song)
{
	std::string lyric = "";
	std::string cmd = "python get_lyric.py --artist \"" + removeUnwantedStr(artist) + "\""
		+ " --song \"" + removeUnwantedStr(song) + "\"";
	WCHAR cmdW[255];
	int err = util::char2wide(cmd.c_str(),cmdW );
	bool ret = util::create_cmd_process(cmdW,lyric);

	return lyric;
}

bool lyrics_source_extcmd::Search( const search_info* pQuery, search_requirements::ptr& pRequirements, lyric_result_client::ptr p_results )
{
	TRACK_CALL_TEXT( "lyrics_source_extcmd::Search" );
	//do a search

	search_requirements_extcmd::ptr requirements = reinterpret_cast<search_requirements_extcmd*>( pRequirements.get_ptr() );

	std::string artist,title;

	artist = pQuery->artist;
	title = pQuery->title;
	
	std::string lyrics;

	lyrics = exec_extcmd(artist,title);

	if (lyrics.length() > 0) {
		//then we use the results client to provide an interface which contains the new lyric 
		lyric_container_base* new_lyric = p_results->AddResult();

		//This is only for demonstration purposes, you should should set these to what you search source returns.
		new_lyric->SetFoundInfo(pQuery->artist, pQuery->album, pQuery->title);

		//These tell the user about where the lyric has come from. This is where you should save a web address/file name to allow you to load the lyric
		new_lyric->SetSources("External Command", "External Command Source", GetGUID(), ST_INTERNET);

		//Copy the lyric text into here
		new_lyric->SetLyric(lyrics.c_str());
	}

	return true;
}

bool lyrics_source_extcmd::Load( lyric_container_base* lyric, request_source p_source )
{
	//Load the lyric

	//This gets the source info you set in Search(), 
	pfc::string8 source, source_private;
	lyric->GetSources( source, source_private );

	//You should set this if the lyric loads properly.
	lyric->SetLoaded();

	//return true on success, false on failure
	return true;
}

void lyrics_source_extcmd::ShowProperties( HWND parent )
{
	//This displays the standard internet source properties.
	static_api_ptr_t< generic_internet_source_properties >()->run( parent );

	return;
}
