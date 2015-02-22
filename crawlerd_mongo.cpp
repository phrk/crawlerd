#include "crawlerd_mongo.h"

namespace crw {

	CrawlerdMongo::CrawlerdMongo(const std::string &_endpoint, const std::string &_db) {
		
		m_domains_ns = _db + ".domains";
		m_pages_ns = _db + ".pages";
		m_c.connect(_endpoint);
		 
	}

	void CrawlerdMongo::getDomainsLinks(std::map<Domain, DomainLinks> &_domains) {
		
	}
	
	void CrawlerdMongo::saveDomainLinks(const DomainLinks &_domains) {
		
		mongo::BSONObjBuilder b;
		b.append("domain", _domains.domain);
		b.append("_id", _domains.inverted_domain);
		
		{
			mongo::BSONArrayBuilder internal_urls;
	
			auto it = _domains.m_internal_links.begin();
			auto end = _domains.m_internal_links.end();
			
			while (it != end) {
				
				internal_urls.append(it->second.inverted_url);
				it++;
			}
			
			b.append("internal_urls_inv", internal_urls.obj() );
		}
		
		{
			mongo::BSONArrayBuilder downloaded_urls;
	
			auto it = _domains.m_downloaded_links.begin();
			auto end = _domains.m_downloaded_links.end();
			
			while (it != end) {
				
				downloaded_urls.append(it->second.inverted_url);
				it++;
			}
			
			b.append("downloaded_urls_inv", downloaded_urls.obj() );
		}
		
		{
			mongo::BSONArrayBuilder failed_urls;
	
			auto it = _domains.m_failed_links.begin();
			auto end = _domains.m_failed_links.end();
			
			while (it != end) {
				
				failed_urls.append(it->second.inverted_url);
				it++;
			}
			
			b.append("failed_urls_inv", failed_urls.obj() );
		}
		
		std::string query = "{\"_id\":\"";
		query.append(_domains.inverted_domain);
		query.append("\"}");
		m_c.update(m_domains_ns, query, b.obj(), true);
	}
	
	void CrawlerdMongo::savePage (PagePtr _page) {
		
		mongo::BSONObjBuilder b;
		//b.append("domain", _domains.domain);
		b.append("_id", _page->link.inverted_url);
		b.append("html", _page->content.html);
		b.append("text", _page->content.text);
		
		std::string query = "{\"_id\":\"";
		query.append(_page->link.inverted_url);
		query.append("\"}");
		m_c.update(m_pages_ns, query, b.obj(), true);
	}
	
	CrawlerdMongo::~CrawlerdMongo() {
		
	}	

}
