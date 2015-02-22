#ifndef _CRAWLERD_DOMAIN_H_
#define _CRAWLERD_DOMAIN_H_

#include "hiconfig.h"
#include "crawler/link.h"

#include "hiaux/structs/hashtable.h"
#include "hiaux/strings/string_utils.h"

#include <boost/noncopyable.hpp>

#include <queue>

namespace crw {

	class NoLinksEx {
	};

	class DomainLinks  {
	
	public:
	
		hiaux::hashtable <Url, Link> m_internal_links;
		hiaux::hashtable <Url, Link> m_downloaded_links;
		hiaux::hashtable <Url, Link> m_failed_links;
		
		std::queue<Link> m_download_queue;
		
		Domain domain;
		Domain inverted_domain;
		
		DomainLinks(const Domain &_domain);
		
		void addNewInternalLink(const Link &_link);
		void addNewInternalLinks(const std::vector<Link> &_links);
		void addDownloadedLink(const Link &_link);
		void addFailedLink(const Link &_link);
		
		Link getLinkToDownload();
		void downloadSucceded(const Link &_link);
		void downloadFailed(const Link &_link);
	};

}

#endif
