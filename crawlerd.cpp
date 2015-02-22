
#include "crawlerd.h"

namespace crw {
	
	void Crawlerd::setParamsList(std::vector<std::string> &_required_params, std::vector<std::string> &_optional_params) {
		
		_required_params.push_back("initial_links_file");
	}
	
	void Crawlerd::loadInitialLinks() {
		
		std::string content;
		getFileContents(m_config["initial_links_file"], content);
		
		std::vector<std::string> urls;
		split(content, '\n', urls);
			
		try {
			
			for (int i = 0; i<urls.size(); i++) 
				if (urls[i].size() > 2) {
			
					Link link( urls[i] );
				
					//std::cout << "link: " << link.url << " domain: " << link.domain << std::endl;
				
					DomainLinks d_links(link.domain);
					d_links.addNewInternalLink(link);
					m_domains.insert(std::make_pair(link.domain, d_links));
				
				}
				
		} catch (IncorrectUrlEx ex) {
			
			std::cout << "Crawlerd::loadInitialLinks IncorrectUrlEx" << std::endl;
				
		} catch (...) {
			
			std::cout << "Crawlerd::loadInitialLinks unknown exception" << std::endl;
		}
	}
	
	void Crawlerd::onPage(PagePtr _page) {
		
		std::cout << "Crawlerd::onPage " << _page->link.url << std::endl;
		
		auto dit = m_domains.find(_page->link.domain);
		
		if (dit == m_domains.end()) {
			std::cout << "Crawlerd::onPage: got page for unknown domain " << _page->link.domain << std::endl;
			return;
		}
		
		if (!_page->success)
			dit->second.downloadFailed(_page->link);
		else
			dit->second.downloadSucceded(_page->link);
		
		//m_storage->savePage(_page);
	}
	
	void Crawlerd::doStart() {
		
		DomainLimits def_domain_limits;
		def_domain_limits.max_parallel = 1;
		def_domain_limits.max_minute = 10;
		def_domain_limits.max_hour = 200;
		def_domain_limits.max_all = 2000;
		
		m_crawler.reset(new Crawler(def_domain_limits, boost::bind(&Crawlerd::onPage, this, _1)));
		
		//m_storage->getDomainsLinks(m_domains);
		
		if (m_domains.size() == 0)
			loadInitialLinks();
		
		for (;;) {
			
			auto dit = m_domains.begin();
			auto end = m_domains.end();
			
			while (dit != end) {
				
				try {
					
					Link link = dit->second.getLinkToDownload();
					m_crawler->enqueueLink(link);
					
				} 
				catch (NoLinksEx ex) {
					
					//std::cout << "NoLinksEx " << std::endl;
					
				} catch (...) {
					
					// specify which
					std::cout << "Crawlerd::doStart: enqueue link exception \n";
				}
				
				dit++;
			}
			
			m_crawler->proceedEvents();
		}
	}
	
	Crawlerd::~Crawlerd() {
		
	}	
}
