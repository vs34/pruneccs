#include "CcsIgnoreReader.hh"
#include "Sta.hh"
#include "LibertyReader.hh"
#include "LibertyWriter.hh"
#include <iostream>

using namespace sta;

// expose protected function
class MySta : public Sta {
public:
    using Sta::readLibertyFile;
    
    CcsIgnoreReader* STAMakeReader(const char *infile){
        CcsIgnoreReader *reader = new CcsIgnoreReader(infile, true , network_);
        return reader;
    }
};

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cout << "Usage: libprune <input.lib> <output.lib>\n";
        return 1;
    }

    const char *infile  = argv[1];
    const char *outfile = argv[2];

    // required sta init
    initSta();
    MySta *sta = new MySta();
    Sta::setSta(sta);
    sta->makeComponents();

    CcsIgnoreReader *reader = sta->STAMakeReader(infile);
    // read
    LibertyLibrary *lib = reader->readLibertyFile(infile);
    if (!lib) {
        std::cerr << "Failed to read liberty file.\n";
        return 1;
    }

    // write (this is the correct function, not a class!)
    writeLiberty(lib, outfile, sta);

    std::cout << "done.\n";
    return 0;
}

