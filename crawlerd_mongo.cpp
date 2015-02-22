#include "crawlerd_mongo.h"

namespace crw {

	CrawlerdMongo::CrawlerdMongo(const std::string &_endpoint, const std::string &_db) {
		
		m_domains_ns = _db + ".domains";
		m_pages_ns = _db + ".pages";
		m_c.connect(_endpoint);
		 
	}

	void CrawlerdMongo::getDomainsLinks(std::map<Domain, DomainLinks> &_domains) {
		
		std::auto_ptr<mongo::DBClientCursor> cursor = m_c.query(m_domains_ns, "{}");
		
		while (cursor->more()) {
		//   cout << cursor->next().toString() << endl;
			
			try {
			
				mongo::BSONObj obj = cursor->next();
				mongo::BSONElement bdomain = obj.getField("domain");
				
				DomainLinks domain_links( bdomain.str() );
				
				
				{
					mongo::BSONObj binteranal = obj.getField("internal_urls_inv").Obj();
					if (!binteranal.couldBeArray()) {
					
						std::cout << "CrawlerdMongo::getDomainsLinks !binteranal.couldBeArray()\n";
						continue;
					}
				
					std::vector<mongo::BSONElement> v;
					binteranal.elems(v);
				
					for (int i = 0; i<v.size(); i++) {
						
						//std::cout << "link: " << v[i].toString() << std::endl;
					
						try {
							//std::string val;
							//v[i].Val(val);
							//std::cout << "adding link: " << v[i].str() << std::endl;
							domain_links.addNewInternalLink( Link( v[i].str(), true) );
						} catch (...) {
							std::cout << "link constriction exception\n";
							continue;
						}
						
					}
				}
				
				{
					mongo::BSONObj bdownloaded_urls_inv = obj.getField("downloaded_urls_inv").Obj();
					if (!bdownloaded_urls_inv.couldBeArray()) {
					
						std::cout << "CrawlerdMongo::getDomainsLinks !bdownloaded_urls_inv.couldBeArray()\n";
						continue;
					}
				
					std::vector<mongo::BSONElement> v;
					bdownloaded_urls_inv.elems(v);
				
					for (int i = 0; i<v.size(); i++) {
						
						domain_links.addDownloadedLink( Link( v[i].str(), true) );
					}
				}
			
				{
					mongo::BSONObj bfailed_urls_inv = obj.getField("failed_urls_inv").Obj();
					if (!bfailed_urls_inv.couldBeArray()) {
					
						std::cout << "CrawlerdMongo::getDomainsLinks !bfailed_urls_inv.couldBeArray()\n";
						continue;
					}
				
					std::vector<mongo::BSONElement> v;
					bfailed_urls_inv.elems(v);
				
					for (int i = 0; i<v.size(); i++) {
						
						domain_links.addDownloadedLink( Link( v[i].str(), true) );
					}
				}
				
				_domains.insert( make_pair(domain_links.domain, domain_links) );
				std::cout << "CrawlerdMongo::getDomainsLinks reading domain: " << domain_links.domain << std::endl;
			
			} catch (...) {
				
				std::cout << "CrawlerdMongo::getDomainsLinks unknown exception\n";
			}
		}
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
