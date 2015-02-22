#ifndef _CRAWLERD_STORAGE_H_
#define _CRAWLERD_STORAGE_H_

#include "hiconfig.h"
#include "crawler/link.h"
#include "crawler/page.h"
#include "domain_links.h"


#include <boost/noncopyable.hpp>

namespace crw {

class CrawlerdStorage  {
public:
	
	virtual void getDomainsLinks(std::map<Domain, DomainLinks> &_domains) = 0;
	virtual void saveDomainLinks(const DomainLinks &_domains) = 0;
	virtual void savePage (PagePtr _page) = 0;
	
	virtual ~CrawlerdStorage();
	
};

typedef boost::shared_ptr<CrawlerdStorage> CrawlerdStoragePtr;

}

#endif
