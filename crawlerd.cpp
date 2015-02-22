
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
		
		std::cout << "Crawlerd::onPage " << _page->link.url << std::endl
			<< "links: " << _page->outbound_links_in.size() << std::endl;
		
		auto dit = m_domains.find(_page->link.domain);
		
		if (dit == m_domains.end()) {
			std::cout << "Crawlerd::onPage: got page for unknown domain " << _page->link.domain << std::endl;
			return;
		}
		
		if (!_page->success) {
			dit->second.downloadFailed(_page->link);
			return;
		}
			
		dit->second.downloadSucceded(_page->link);
		dit->second.addNewInternalLinks(_page->outbound_links_in);
		m_storage->savePage(_page);
	}
	
	void Crawlerd::flushDomainsLinks() {
		
		std::cout << "Crawlerd::flushDomainsLinks size: " << m_domains.size() << std::endl;
		
		auto it = m_domains.begin();
		auto end = m_domains.end();
		
		while (it != end) {
			
			try {
				
				m_storage->saveDomainLinks(it->second);
			
			} catch (...) {
				
				std::cout << "Crawlerd::flushDomainsLinks m_storage->saveDomainLinks exception\n";
			}
			it++;
		}
	}
	
	void Crawlerd::doStart() {
		
		mongo::client::initialize();
		
		m_storage.reset(new CrawlerdMongo("localhost", "local"));
		
		m_flush_data_task.reset(new hiaux::RegularTask (3, boost::bind(&Crawlerd::flushDomainsLinks, this)));
		
		//DomainLinks links("test.mediatoday.ru");
		//links.addNewInternalLink(Link("http://test.mediatoday.ru/index.php"));
		//m_storage->saveDomainLinks(links);
		
		DomainLimits def_domain_limits;
		def_domain_limits.max_parallel = 1;
		def_domain_limits.max_minute = 30;
		def_domain_limits.max_hour = 1000;
		def_domain_limits.max_all = 3000;
		
		m_crawler.reset(new Crawler(def_domain_limits, boost::bind(&Crawlerd::onPage, this, _1)));
		
		m_storage->getDomainsLinks(m_domains);
		
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
			m_flush_data_task->checkRun();
		}
	}
	
	Crawlerd::~Crawlerd() {
		
	}	
}
