import sys
sys.path.insert(0, '../hiaux/hibuilder/')

from hibuilder import HiBuilder

env = Environment()

b = HiBuilder("crawlerd", "clang++")

hicore_path = "../../"
hiaux_path = "../../"

b.addPath(hicore_path)
b.addPath(hiaux_path)
b.addPath("../")
b.addPath("./")

b.connectLib("../crawler/")
b.connectLib("../hiaux/tools/")

#b.connectLib("../HttpServer/")
#b.addPath("../HttpServer")


#b.connectLib("../../threads/")

b.addPath("/usr/local/include/")

#b.connectLib(hicore_path+"thirdparty/http-parser/")

b.addCCFlags(["-Wc++11-extensions", "-Wreturn-type", "-Wc++11-long-long"])
b.addLinkFlags(["-L/usr/local/lib/"])

b.addCppGlob("*.cpp")

b.build(Program)
