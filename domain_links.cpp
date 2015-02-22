#include "domain_links.h"

namespace crw {

	DomainLinks::DomainLinks(const Domain &_domain):
	domain(_domain),
	inverted_domain(invertDomain(_domain)) {
		
	}

	void DomainLinks::addNewInternalLink(const Link &_link) {
	
		//std::cout << "DomainLinks::addNewInternalLink " << _link.url << std::endl;
	
		if (m_internal_links.find( _link.url ) == m_internal_links.end()) {
			m_internal_links.insert( std::make_pair( _link.url , _link ));
			m_download_queue.push(_link);
		}
	}

	void DomainLinks::addNewInternalLinks(const std::vector<Link> &_links) {
		
		for (int i = 0; i<_links.size(); i++) {
			
			if (m_internal_links.find( _links[i].url ) == m_internal_links.end()) {
				m_internal_links.insert( std::make_pair( _links[i].url , _links[i] ));
				m_download_queue.push(_links[i]);
			}
		}
	}

	void DomainLinks::addDownloadedLink(const Link &_link) {
		
		if (m_internal_links.find( _link.url ) == m_internal_links.end())
			m_internal_links.insert( std::make_pair( _link.url , _link ));
		
		if (m_downloaded_links.find( _link.url ) == m_downloaded_links.end())
			m_downloaded_links.insert( std::make_pair( _link.url , _link ));
	}
	
	void DomainLinks::addFailedLink(const Link &_link) {
		
		if (m_internal_links.find( _link.url ) == m_internal_links.end())
			m_internal_links.insert( std::make_pair( _link.url , _link ));
		
		if (m_failed_links.find( _link.url ) == m_failed_links.end())
			m_failed_links.insert( std::make_pair( _link.url , _link ));
	}

	Link DomainLinks::getLinkToDownload() {
		/*
		auto it = m_internal_links.begin();
		auto end = m_internal_links.end();
		
		while (it != end) {
			
			if (m_downloaded_links.find(it->first) == m_downloaded_links.end() &&
				m_failed_links.find(it->first) == m_failed_links.end()) {
					
					return it->second;
				}
 			
			it++;
		}
		*/
		
		if (m_download_queue.empty())
			throw NoLinksEx();
		
		Link link = m_download_queue.front();
		m_download_queue.pop();
		
		return link;
	}

	void DomainLinks::downloadSucceded(const Link &_link) {
		
		m_downloaded_links.insert( std::make_pair( _link.url, _link ));
	}

	void DomainLinks::downloadFailed(const Link &_link) {
		
		m_failed_links.insert( std::make_pair ( _link.url, _link ));
	}

}
