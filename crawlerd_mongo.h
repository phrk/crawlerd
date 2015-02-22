#ifndef _CRAWLERD_MONGO_H_
#define _CRAWLERD_MONGO_H_

#include "hiconfig.h"
#include "crawlerd_storage.h"

#include "mongo/client/dbclient.h"

namespace crw {

class CrawlerdMongo : public CrawlerdStorage  {
	
	mongo::DBClientConnection m_c;
	
	std::string m_domains_ns;
	std::string m_pages_ns;
	
public:
	
	CrawlerdMongo(const std::string &_endpoint, const std::string &_db);
	
	virtual void getDomainsLinks(std::map<Domain, DomainLinks> &_domains);
	virtual void saveDomainLinks(const DomainLinks &_domains);
	virtual void savePage (PagePtr _page);
	
	virtual ~CrawlerdMongo();
	
};


}

#endif
