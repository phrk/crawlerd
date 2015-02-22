#include "hiconfig.h"
#include "crawlerd.h"


void onCalledServer(crw::HttpClientA<int>::JobInfo _ji) {
	
	std::cout << "onCalledServer \n";
	if (!_ji.success)
		std::cout << "not success\n";
	
	std::cout << "resp: " << _ji.resp << std::endl;
}

int main (int argv, char **argc) {
	
/*	crw::HttpClientA<int> cl(boost::bind(&onCalledServer, _1));
	
	cl.call(0, "http://ya.ru");
	cl.call(0, "http://google.ru");
	cl.kick();
*/	
	crw::Crawlerd* d = new crw::Crawlerd();
	d->start("crawlerd.conf", argv, argc);
	//d->start();
	
	return 0;
}

