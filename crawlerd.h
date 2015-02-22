#ifndef _CRAWLERD_H_
#define _CRAWLERD_H_

#include "crawler/crawler.h"

#include "hiaux/strings/string_utils.h"
#include "hiaux/tools/Daemon.h"

#include "domain_links.h"
#include "crawlerd_storage.h"

namespace crw {

	class Crawlerd : public Daemon {
	
		CrawlerdStoragePtr m_storage;
		std::map<Domain, DomainLinks> m_domains;
		CrawlerPtr m_crawler;
		
		void loadInitialLinks();
		
		void onPage(PagePtr page);
		
	public:
		
		virtual void setParamsList(std::vector<std::string> &_required_params, std::vector<std::string> &_optional_params);
		virtual void doStart();
		//virtual void connHandler(HttpConnectionPtr _conn, HttpRequestPtr _req);
		virtual ~Crawlerd();
	};
	
}

#endif
